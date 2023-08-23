#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/highgui/highgui_c.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <sstream> 
#include <filesystem>
#include <fstream>
#include <cmath>


namespace fs = std::filesystem;

//Structure that contains the Stereo Pair Calbration information.
//This will be calculated using stereo_calibrate
struct Params{
   cv::Mat camera_matrix;
   cv::Mat distortion_coefficients;
};

Params readCameraParams(cv::String n_fichero){
    cv::FileStorage intr(n_fichero, cv::FileStorage::READ);
    if(! intr.isOpened())
    {
        std::cerr << "El archivo no se ha podido abrir" << std::endl;
    }

    Params datos;

    intr["camera_matrix"] >> datos.camera_matrix;
    intr["distortion_coefficients"] >> datos.distortion_coefficients;


    return datos;
}


cv::Mat removeDistortion(cv::Mat input, Params datos){
    cv::Mat output;
    cv::undistort(input, output, datos.camera_matrix, datos.distortion_coefficients);
    return output;
}

std::vector<cv::DMatch>  KpMatch( std::vector<cv::KeyPoint> keypoints_query ,cv::Mat descriptors_query, std::vector<cv::KeyPoint> keypoints_train, cv::Mat descriptors_train){
    std::vector<std::vector<cv::DMatch>> matches;
    auto matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
    matcher->knnMatch(descriptors_query, descriptors_train, matches, 2);

    //filtro que elimina los matches innecesarios //mirar
    // good matches search: 
    std::vector<cv::DMatch> good_matches;

    for (int i = 0; i < matches.size(); i++){ 
        if (matches[i].size() < 2)      
        continue;

        const cv::DMatch &m1 = matches[i][0];   
        const cv::DMatch &m2 = matches[i][1];
        if(m1.distance < 80){
            if(abs(keypoints_query[m1.queryIdx].octave - keypoints_train[m1.queryIdx].octave) <= 2){
                float porcentaje_diferencia = ((m2.distance-m1.distance)/m2.distance)*100;
                if(porcentaje_diferencia>20){
                    good_matches.push_back(m1);//guardo el mejor match
                }
            } 
        }  
    }
    return good_matches;
}

cv::Mat fundamental(cv::Mat img1, cv::Mat img2){

    std::vector<cv::KeyPoint> keypoints_query;
    std::vector<cv::KeyPoint> keypoints_train;
    cv::Mat descriptors_query;
    cv::Mat descriptors_train;
    std::vector<cv::DMatch> salidas;
    std::vector<cv::DMatch> salidas_sin_outliers;
    cv::Mat salidasinFiltro;
    cv::Mat salidaconFiltro;

    auto Detector=cv::AKAZE::create(cv::AKAZE::DESCRIPTOR_MLDB,  0,  3, 1e-4f,8 );
    Detector ->detectAndCompute(img1, cv::Mat(), keypoints_query, descriptors_query);
    Detector ->detectAndCompute(img2, cv::Mat(), keypoints_train, descriptors_train);

    salidas = KpMatch(keypoints_query, descriptors_query, keypoints_train, descriptors_train);
    std::cout<<"salidas_con_outliers"<<std::endl;
    std::cout<<salidas.size()<<std::endl;

    std::vector<cv::Point2f> points_query,points_train;//rellenar

    for (int i = 0; i < salidas.size(); i++){ 
        points_query.push_back(keypoints_query[salidas[i].queryIdx].pt);
        points_train.push_back(keypoints_train[salidas[i].trainIdx].pt);
    }

    cv::Mat inliers;
    cv::Mat F = cv::findFundamentalMat(points_query,points_train,cv::FM_RANSAC,0.999,1.0,inliers);
    for(int i=0; i<inliers.total(); i++){
        if( !inliers.ptr<uchar>(0)[i]){
            //ES OUTLIER      
        }else{
            salidas_sin_outliers.push_back(salidas[i]);
        }
    }
    std::cout<<"salidas_sin_outliers"<<std::endl;
    std::cout<<salidas_sin_outliers.size()<<std::endl;
    cv::drawMatches(img1,keypoints_query,img2,keypoints_train,salidas,salidasinFiltro);
    cv::drawMatches(img1,keypoints_query,img2,keypoints_train,salidas_sin_outliers, salidaconFiltro);

    cv::imshow("imagensinFiltro", salidasinFiltro);
    cv::imshow("imagenconFiltro", salidaconFiltro);

    cv::waitKey(0);

    return F;

}

void __imshow(std::string wn,const cv::Mat &im,cv::Size ss)
{

    if( im.size()==ss) cv::imshow(wn,im);
    else{
        cv::Mat resized;
        cv::resize(im,resized,ss);
        cv::imshow(wn,resized);
    }
}
void showEpipolar(cv::Mat centralImage,cv::Mat otherImage,cv::Mat F){

    if(F.empty())return;

    struct CallBackInfo
    {
        cv::Mat imA,imB;
        cv::Mat F;
    };

    CallBackInfo *cbi=new CallBackInfo{centralImage,otherImage,F};

    cv::Mat Mixed(centralImage.rows,centralImage.cols*2,CV_8UC3);
    if( centralImage.channels()==1){
        cv::cvtColor(centralImage,Mixed.colRange(0,centralImage.cols),cv::COLOR_GRAY2BGR);
        cv::cvtColor(otherImage,Mixed.colRange(centralImage.cols,2*centralImage.cols ),cv::COLOR_GRAY2BGR);
    }
    else{
        centralImage.copyTo(Mixed.colRange(0,centralImage.cols));
        otherImage.copyTo(Mixed.colRange(centralImage.cols,2*centralImage.cols));
    }

     cv::namedWindow("Fundamental");
    __imshow("Fundamental",Mixed,cv::Size{1600,600});

    cv::setMouseCallback("Fundamental",[](int event, int x, int y, int flags, void* _cbi)->void{
        if(x<800){
            CallBackInfo *cbi=(CallBackInfo*)_cbi;

            int sX=float(x)*float(cbi->imB.cols)/800.;
            int sY=float(y)*(float(cbi->imB.rows)/600.);

            //find epipolar line
            cv::Mat P= (cv::Mat_<double>(3,1) << sX, sY, 1);
            cv::Mat L=cbi->F*P;//epipolar line
            double a=L.at<double>(0,0);
            double b=L.at<double>(0,1);
            double c=L.at<double>(0,2);
            int x0=0;
            int y0=(a*x0+c)/-b;
            int x1=cbi->imB.cols;
            int y1=(a*x1+c)/-b;
            cv::Mat imBcopy;
            cbi->imB.copyTo(imBcopy);
            //cv::cvtColor(cbi->imB,imBcopy,cv::COLOR_BGR2BGR);
            cv::line(imBcopy,cv::Point(x0,y0),cv::Point(x1,y1),{0,0,244},2);

            cv::Mat Mixed(cbi->imA.rows,cbi->imA.cols*2,CV_8UC3);
            cbi->imA.copyTo(Mixed.colRange(0,cbi->imA.cols));
            //cv::cvtColor(cbi->imA,Mixed.colRange(0,cbi->imA.cols),cv::COLOR_BGR2BGR);
            imBcopy.copyTo(Mixed.colRange(cbi->imA.cols,2*cbi->imA.cols ));

            cv::namedWindow("Fundamental");
            __imshow("Fundamental",Mixed,cv::Size{1600,600});
        }else{


        }
    },cbi
    );
}


//ESQUEMA DE LA FUNCION MAIN
int main(int argc,char **argv){   
    cv::Mat im1=cv::imread(argv[1]);
    cv::Mat im2=cv::imread(argv[2]);
    auto CP=readCameraParams(argv[3]);
    im1=removeDistortion(im1,CP);
    im2=removeDistortion(im2,CP);
    cv::Mat F=fundamental(im1,im2);
    showEpipolar(im1,im2,F);
    while(cv::waitKey(0)!=27) ;
}
