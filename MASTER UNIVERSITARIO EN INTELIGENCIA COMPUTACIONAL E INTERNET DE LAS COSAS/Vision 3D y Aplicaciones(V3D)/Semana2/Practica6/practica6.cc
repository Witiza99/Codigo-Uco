#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/highgui/highgui_c.h>


//#include "opencv2/sfm/fundamental.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <sstream> 
#include <filesystem>
#include <fstream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

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

float epipolarLineSqDist(const cv::Point2f &kp1,const cv::Point2f &kp2,const cv::Mat &F){
    if(F.empty())return 0;
       // Epipolar line in second image l = x1'F = [a b c]
       auto a = kp1.x*F.at<float>(0,0)+kp1.y*F.at<float>(1,0)+F.at<float>(2,0);
       auto b = kp1.x*F.at<float>(0,1)+kp1.y*F.at<float>(1,1)+F.at<float>(2,1);
       auto den = a*a+b*b;
       if(den==0) return std::numeric_limits<float>::max();
       auto c = kp1.x*F.at<float>(0,2)+kp1.y*F.at<float>(1,2)+F.at<float>(2,2);
       auto num = a*kp2.x+b*kp2.y+c;
       return num*num/den;
    };

std::vector<cv::DMatch>  KpMatch( std::vector<cv::KeyPoint> keypoints_query ,cv::Mat descriptors_query, std::vector<cv::KeyPoint> keypoints_train, cv::Mat descriptors_train, cv::Mat F=cv::Mat()){
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
                    if((epipolarLineSqDist(keypoints_train[m1.trainIdx].pt,keypoints_query[m1.queryIdx].pt,F))<4){
                        good_matches.push_back(m1);//guardo el mejor match
                    }
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

    F.convertTo(F, CV_32FC1);

    return F;

}

void __recoverPose(cv::Mat E, std::vector<cv::Point2f> points_query, std::vector<cv::Point2f> points_train, cv::Mat camK, cv::Mat &R, cv::Mat &t)
{
    
    //normalize the 2d points
    cv::undistortPoints(points_query,points_query,camK,cv::Mat::zeros(1,5,CV_64F));
    cv::undistortPoints(points_train,points_train,camK,cv::Mat::zeros(1,5,CV_64F));
    //obtain R|t from the Essential Matrix
    cv::recoverPose(E, points_query,points_train,R,t);
}

//given two keypoints, the camera matrix K and the R|t transform from query to train
//obtains the corresponding 3d point
//returns true if the 3dpoint is correct and false otherwise
bool  Triangulateaux(const cv::KeyPoint &kp_query,const cv::KeyPoint & kp_train, const cv::Mat &kin,const cv::Mat &rin, const cv::Mat &tin,cv::Point3f &p3d){
    auto getcosParallax=[](  cv::Point3d  p3d,const cv::Mat &R,const cv::Mat &t){
        cv::Mat r64,t64;
        R.convertTo(r64,CV_64F);
        t.convertTo(t64,CV_64F);
        cv::Mat O1 = cv::Mat::zeros(3,1,CV_64F);
        cv::Mat O2 = -R.t()*t;
        cv::Mat p3dC1(3,1,CV_64F,&p3d);
        cv::Mat normal1 = p3dC1 - O1;
        float dist1 = cv::norm(normal1);

        cv::Mat normal2 = p3dC1 - O2;
        float dist2 = cv::norm(normal2);
        return normal1.dot(normal2)/(dist1*dist2);
    };
    auto project=[](const cv::Point3f p,cv::Mat &P ){
        cv::Point3f res;
        double *p34=P.ptr<double>(0);
        res.x=p.x*p34[0]+p.y*p34[1]+p.z*p34[2]+p34[3];
        res.y=p.x*p34[4]+p.y*p34[5]+p.z*p34[6]+p34[7];
        res.z=p.x*p34[8]+p.y*p34[9]+p.z*p34[10]+p34[11];
        res.x/=res.z;
        res.y/=res.z;
        return cv::Point2f(res.x,res.y);
    };
    //make it 64f
    cv::Mat R,K,t;
    if(R.total()==3)
        cv::Rodrigues(rin,R);
    else rin.convertTo(R,CV_64F);
    R.convertTo(R,CV_64F);
    kin.convertTo(K,CV_64F);
    tin.convertTo(t,CV_64F);
     // Camera 1 Projection Matrix K[I|0]
    cv::Mat P1(3,4,CV_64F,cv::Scalar(0));
    K.copyTo(P1.rowRange(0,3).colRange(0,3));


    // Camera 2 Projection Matrix K[R|t]
    cv::Mat P2(3,4,CV_64F);
    R.copyTo(P2.rowRange(0,3).colRange(0,3));
    t.copyTo(P2.rowRange(0,3).col(3));
    P2 = K*P2;


    cv::Mat A(4,4,CV_64F);

    A.row(0) = kp_query.pt.x*P1.row(2)-P1.row(0);
    A.row(1) = kp_query.pt.y*P1.row(2)-P1.row(1);
    A.row(2) = kp_train.pt.x*P2.row(2)-P2.row(0);
    A.row(3) = kp_train.pt.y*P2.row(2)-P2.row(1);

    cv::Mat u,w,vt;
    cv::SVD::compute(A,w,u,vt,cv::SVD::MODIFY_A| cv::SVD::FULL_UV);
    cv::Mat x3D = vt.row(3).t();
    x3D = x3D.rowRange(0,3)/x3D.at<double>(3);

    p3d= cv::Point3f(x3D.at<double>(0),x3D.at<double>(1),x3D.at<double>(2));;
    //check the point
    if( p3d.z<0) return false;//behind the camera
    if( getcosParallax (p3d,R,t)<0.99) return false;//too little parallax
    //check the reprojection error is low

    auto pp1=project(p3d,P1);
    if( cv::norm(pp1-kp_query.pt )>1.5) return false;
    auto pp2=project(p3d,P2);
    if( cv::norm(pp2-kp_train.pt )>1.5) return false;
    return true;
}


std::vector<cv::Point3f> Triangulate(cv::Mat img1, cv::Mat img2, cv::Mat F, Params datos){
    std::vector<cv::KeyPoint> keypoints_query;
    std::vector<cv::KeyPoint> keypoints_train;
    cv::Mat descriptors_query;
    cv::Mat descriptors_train;
    std::vector<cv::DMatch> salidas;
    std::vector<cv::DMatch> salidas_sin_outliers;
    std::vector<cv::DMatch> salida_final;


    auto Detector=cv::AKAZE::create(cv::AKAZE::DESCRIPTOR_MLDB,  0,  3, 1e-4f,8 );
    Detector ->detectAndCompute(img1, cv::Mat(), keypoints_query, descriptors_query);
    Detector ->detectAndCompute(img2, cv::Mat(), keypoints_train, descriptors_train);

    salidas = KpMatch(keypoints_query, descriptors_query, keypoints_train, descriptors_train, F);
    std::cout<<"salidas_con_outliers_y_F"<<std::endl;
    std::cout<<salidas.size()<<std::endl;

    std::vector<cv::Point2f> points_query,points_train;//rellenar

    for (int i = 0; i < salidas.size(); i++){ 
        points_query.push_back(keypoints_query[salidas[i].queryIdx].pt);
        points_train.push_back(keypoints_train[salidas[i].trainIdx].pt);
    }

    cv::Mat inliers;
    cv::Mat E;
    cv::findFundamentalMat(points_query,points_train,cv::FM_RANSAC,0.999,1.0,inliers);


    datos.camera_matrix.convertTo(datos.camera_matrix, CV_32FC1);
    E = datos.camera_matrix.t() * F * datos.camera_matrix;
    //cv::sfm::essentialFromFundamental(F, datos.camera_matrix, datos.camera_matrix, E);

    for(int i=0; i<inliers.total(); i++){
        if( !inliers.ptr<uchar>(0)[i]){
            //ES OUTLIER      
        }else{
            salidas_sin_outliers.push_back(salidas[i]);
        }
    }
    std::cout<<"salidas_sin_outliers_y_F"<<std::endl;
    std::cout<<salidas_sin_outliers.size()<<std::endl;

    points_query.clear();
    points_train.clear();

    for (int i = 0; i < salidas_sin_outliers.size(); i++){ 
        points_query.push_back(keypoints_query[salidas_sin_outliers[i].queryIdx].pt);
        points_train.push_back(keypoints_train[salidas_sin_outliers[i].trainIdx].pt);
    }

    cv::Mat R,t;
    E.convertTo(E, CV_64FC1);
    __recoverPose(E, points_query, points_train, datos.camera_matrix, R, t);
    std::vector<cv::Point3f> ptos_triangulados;//rellenar
    for(int i=0;i<salidas_sin_outliers.size();i++){
        cv::Point3f p3d;
        if(Triangulateaux(keypoints_query[salidas_sin_outliers[i].queryIdx], keypoints_train[salidas_sin_outliers[i].trainIdx], datos.camera_matrix, R, t, p3d)){//mirar esto
            salida_final.push_back(salidas_sin_outliers[i]);//guardo el match pero no hace falta
            ptos_triangulados.push_back(p3d);
        } 
    }
    std::cout<<"salida_final"<<std::endl;
    std::cout<<salida_final.size()<<std::endl;
    std::cout<<"ptos_triangulados"<<std::endl;
    std::cout<<ptos_triangulados.size()<<std::endl;
    return ptos_triangulados;
}

//funcion para guardar objeto
void writeToOBJ(cv::String path,std::vector<cv::Point3f> points){

   std::ofstream file(path,std::ios::binary);
   for(auto p:points)
       file<<"v "<<p.x<<" "<<p.y<<" "<<p.z<<std::endl;
}

//funcion para guardar objeto
void writeToPCD(cv::String path,std::vector<cv::Point3f> v_points){

    pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.width    = v_points.size();
    cloud.height   = 1;
    cloud.is_dense = false;
    cloud.points.resize (cloud.width * cloud.height);
    for (size_t i = 0; i < cloud.points.size(); i++) {
        cloud.points[i].x = v_points[i].x;
        cloud.points[i].y = v_points[i].y;
        cloud.points[i].z = v_points[i].z;
    }
    pcl::io::savePCDFile<pcl::PointXYZ>(path, cloud);
}



//ESQUEMA DE LA FUNCION MAIN
int main(int argc,char **argv){   
    cv::Mat im1=cv::imread(argv[1]);
    cv::Mat im2=cv::imread(argv[2]);
    auto CP=readCameraParams(argv[3]);
    im1=removeDistortion(im1,CP);
    im2=removeDistortion(im2,CP);
    cv::Mat F=fundamental(im1,im2);
    std::vector<cv::Point3f> vpoints=Triangulate(im1,im2,F,CP);
    writeToPCD(argv[4],vpoints);
    while(cv::waitKey(0)!=27) ;
}

