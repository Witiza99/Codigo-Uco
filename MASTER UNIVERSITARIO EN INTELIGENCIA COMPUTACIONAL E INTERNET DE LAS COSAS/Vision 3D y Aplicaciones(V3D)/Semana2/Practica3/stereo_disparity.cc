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

namespace fs = std::filesystem;

using namespace cv;

const String keys = 
    "{help h usage ?        |      | print this message             }"
    "{@imagenentrada        |<none>| imagen en estereo              }"
    "{@archivocalibrado     |<none>| archivo con la calibracion     }"
    "{@nombrearchivosalida  |<none>| nombre del archivo de salida   }"
    ;

//Structure that contains the Stereo Pair Calbration information.
//This will be calculated using stereo_calibrate
struct StereoParams{
   Mat mtxL,distL,R_L,T_L;
   Mat mtxR,distR,R_R,T_R;
   Mat Rot, Trns, Emat, Fmat;
};

//funcion para rectificar
void rectifyStereoImages(const StereoParams &sti,cv::Mat &left,cv::Mat &rigth){
   cv::Mat rect_l, rect_r, proj_mat_l, proj_mat_r, Q;
   cv::Mat Left_Stereo_Map1, Left_Stereo_Map2;
   cv::Mat Right_Stereo_Map1, Right_Stereo_Map2;
   cv::stereoRectify(sti.mtxL, sti.distL,sti.mtxR,sti.distR,left.size(),sti.Rot,sti.Trns,
                     rect_l,rect_r,proj_mat_l,proj_mat_r,
                     Q,cv::CALIB_ZERO_DISPARITY, 0);
   cv::initUndistortRectifyMap(sti.mtxL,sti.distL,rect_l,proj_mat_l,
                               left.size(),CV_16SC2,
                               Left_Stereo_Map1,Left_Stereo_Map2);
   cv::initUndistortRectifyMap(sti.mtxR,sti.distR,
                               rect_r,proj_mat_r,
                               left.size(),CV_16SC2,
                               Right_Stereo_Map1,Right_Stereo_Map2);
   cv::Mat AuxImage, Right_nice;
   cv::remap(left, AuxImage, Left_Stereo_Map1, Left_Stereo_Map2,
             cv::INTER_LANCZOS4,cv::BORDER_CONSTANT,0);
   AuxImage.copyTo(left);
   cv::remap(rigth,  AuxImage,  Right_Stereo_Map1,  Right_Stereo_Map2,
             cv::INTER_LANCZOS4,cv::BORDER_CONSTANT,0);
   AuxImage.copyTo(rigth);
}

//funcion para guardar objeto
void writeToOBJ(cv::String path,std::vector<cv::Point3f> points){

   std::ofstream file(path,std::ios::binary);
   for(auto p:points)
       file<<"v "<<p.x<<" "<<p.y<<" "<<p.z<<std::endl;
}


int main (int argc, char* const* argv){

    int retCode=EXIT_SUCCESS;

    try {    

        CommandLineParser parser(argc, argv, keys);
        parser.about("Captura imagenes");
        if (parser.has("help")){
            parser.printMessage();
            return 0;
        }
        cv::String imagenentrada = parser.get<cv::String>("@imagenentrada");
        if (!parser.check()){
            parser.printErrors();
            return 0;
        }
        cv::String archivocalibrado = parser.get<cv::String>("@archivocalibrado");
        if (!parser.check()){
            parser.printErrors();
            return 0;
        }

        FileStorage intr(archivocalibrado, FileStorage::READ);
        if(! intr.isOpened())
        {
        std::cerr << "El archivo no se ha podido abrir" << std::endl;
        return EXIT_FAILURE;
        }

        StereoParams datos;

        intr["LEFT_K"] >> datos.mtxL;
        intr["LEFT_D"] >> datos.distL;
        intr["RIGTH_K"] >> datos.mtxR;
        intr["RIGTH_D"] >> datos.distR;
        intr["R"] >> datos.Rot;
        intr["T"] >> datos.Trns;
        intr["E"] >> datos.Emat;
        intr["F"] >> datos.Fmat;

        cv::String nombrearchivosalida = parser.get<cv::String>("@nombrearchivosalida");
        if (!parser.check()){
            parser.printErrors();
            return 0;
        }

        Mat img;
        Mat imgGray1, imgGray2;
        int key = 0;


        img = cv::imread(imagenentrada);//Carga la imagen desde archivo.
        if (img.empty()){
            std::cerr << "Error: no he podido abrir el fichero '" << imagenentrada << "'." << std::endl;
            return EXIT_FAILURE;
        }

        Rect imgRoi1(0,0,(img.cols/2),img.rows);
        Rect imgRoi2((img.cols/2),0,(img.cols/2),img.rows);

        Mat img1 = img(imgRoi1);
        Mat img2 = img(imgRoi2);

        //cambio la imagen para que se divida en dos
        cvtColor(img1, imgGray1, COLOR_BGR2GRAY);
        cvtColor(img2, imgGray2, COLOR_BGR2GRAY);

        //rectifico imagenes
        rectifyStereoImages(datos,imgGray1,imgGray2);

        //calculo disparidad
        Mat disp, disparity;

        // Creating an object of StereoSGBM algorithm
        Ptr<StereoBM> SBM = StereoBM::create();
        SBM->compute(imgGray1, imgGray2, disp);

        // Converting disparity values to CV_32F from CV_16S
        disp.convertTo(disparity,CV_32F, 1.0);
        disparity=disparity/16.f;

        //aplicamos formula para obtener puntos 3d a partir de la disparidad
        std::vector<Point3f> puntosvalidos;
        Point3f Pt3valido;
        double X,Y,Z,f,valor_disparidad,cx,cy,B;
        f = datos.mtxL.at<double>(0,0);
        cx = datos.mtxL.at<double>(0,2);
        cy = datos.mtxL.at<double>(1,2);
        B = norm(datos.Trns);

        /*
        std::cout<<"matriz"<<std::endl;
        for(int i=0;i<datos.mtxL.rows;i++){
            for(int j=0;j<datos.mtxL.cols;j++){
                std::cout<<datos.mtxL.at<double>(i,j)<<std::endl;
            }
        }
        std::cout<<"fin"<<std::endl;
        std::cout<<B<<std::endl;
        std::cout<<f<<std::endl;
        std::cout<<cx<<std::endl;
        std::cout<<cy<<std::endl;*/

        for(int i=0;i<disparity.rows;i++){
            for(int j=0;j<disparity.cols;j++){
                valor_disparidad = disparity.at<float>(i,j);
                if( valor_disparidad > 10){
                    //std::cout<<valor_disparidad<<std::endl;
                    Z = B * f/valor_disparidad;
                    X = (j-cx) * Z/f;
                    Y = (i-cy) * Z/f;

                    Pt3valido = Point3d(X,Y,Z);
                    puntosvalidos.push_back(Pt3valido);
                }
            }
        }

        writeToOBJ(nombrearchivosalida,puntosvalidos);

        /*
        //Show the image
        imshow("Original", disparity);

        //Wait until user press some key
        waitKey(0);

        key = (char) waitKey();*/

    }
    catch (std::exception& e){
        std::cerr << "Capturada excepcion: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    catch (...){
        std::cerr << "Capturada excepcion desconocida!" << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
