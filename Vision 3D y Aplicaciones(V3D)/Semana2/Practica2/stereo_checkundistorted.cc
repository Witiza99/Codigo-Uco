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

namespace fs = std::filesystem;

using namespace cv;

const String keys = 
    "{help h usage ?    |      | print this message             }"
    "{@imagenentrada    |<none>| imagen en estereo              }"
    "{@archivocalibrado |<none>| archivo con la calibracion     }"
    ;
Mat img;
Mat img_line;
Mat imgGray;
Mat img_line_rectificado;


//Structure that contains the Stereo Pair Calbration information.
//This will be calculated using stereo_calibrate
struct StereoParams{
   Mat mtxL,distL,R_L,T_L;
   Mat mtxR,distR,R_R,T_R;
   Mat Rot, Trns, Emat, Fmat;
};


void mouseEventHandler(int event, int x, int y, int flags, void* param)
{
    if  ( event == EVENT_LBUTTONDOWN ){
        img_line = img.clone();
        Point2f p1(0, y);
        Point2f p2(img.cols, y);
        line(img_line, p1, p2, Scalar(255, 0, 0), 2, FILLED);

        //refresh the image window
        cv::imshow("Original",img_line);
    }
}

void mouseEventHandlerv2(int event, int x, int y, int flags, void* param)
{
    if  ( event == EVENT_LBUTTONDOWN ){
        img_line_rectificado = imgGray.clone();
        Point2f p1(0, y);
        Point2f p2(imgGray.cols, y);
        line(img_line_rectificado, p1, p2, Scalar(255, 0, 0), 2, FILLED);

        //refresh the image window
        cv::imshow("Rectified",img_line_rectificado);
    }
}

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

        /*Mat mtxL,distL,R_L,T_L;
        Mat mtxR,distR,R_R,T_R;
        Mat Rot, Trns, Emat, Fmat;*/

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

        rectifyStereoImages(datos,imgGray1,imgGray2);

        //fusionamos las imagenes en una sola
        Mat imgGraytmp(Size(imgGray1.cols*2,imgGray1.rows), imgGray1.type());

        imgGray = imgGraytmp;

        imgGray1.copyTo(imgGray(Rect(0, 0, imgGray1.cols, imgGray1.rows)));
        imgGray2.copyTo(imgGray(Rect(imgGray2.cols, 0, imgGray2.cols, imgGray2.rows)));

        cvtColor(imgGray, imgGray, COLOR_GRAY2BGR);

        namedWindow("Rectified", 1);
        //Set the callback function for any mouse event
        setMouseCallback("Rectified", mouseEventHandlerv2, NULL);

        //Show the image
        imshow("Rectified", imgGray);

        namedWindow("Original", 1);

        //Set the callback function for any mouse event
        setMouseCallback("Original", mouseEventHandler, NULL);

        //Show the image
        imshow("Original", img);

        //Wait until user press some key
        waitKey(0);


        key = (char) waitKey();



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
