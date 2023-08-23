#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <sstream> 

using namespace cv;

const String keys =
    "{help h usage ? |      | print this message                 }"
    "{@input         |<none>| input, Video                       }"
    "{@rows          |<none>| filas  de calibracion              }"
    "{@cols          |<none>| columnas de calibracion            }"
    "{@size          |<none>| tamaño del cuadro de calibracion   }"
    "{@nimg          |<none>| cantidad de imagenes de calibracion}"
    ;


static void calcChessboardCorners(Size boardSize, float squareSize, std::vector<cv::Point3f>& corners)
{
	corners.clear();
    for( int i = 0; i < boardSize.height; i++ )
        for( int j = 0; j < boardSize.width; j++ )
            corners.push_back(Point3f(float(j*squareSize), float(i*squareSize), 0)); 
}

static void saveparams(const std::string& filename, const Mat& cameraMatrix, const Mat& distCoeffs,
					   const std::vector<Mat>& rvecs,const std::vector<Mat>& tvecs, const double& RMS)
{
		FileStorage fs( filename, FileStorage::WRITE );
		fs << "Calibrate-Accuracy" << RMS;
		fs << "camera-matrix" << cameraMatrix;
		fs << "distortion-coefficients" << distCoeffs;
		fs << "Rotation-Vector" << rvecs;
		fs << "Translation-vector" << tvecs;

		if( !rvecs.empty() && !tvecs.empty() ){

			CV_Assert(rvecs[0].type() == tvecs[0].type());
			Mat bigmat((int)rvecs.size(), 6, rvecs[0].type());
			for( int i = 0; i < (int)rvecs.size(); i++ ){
				Mat r = bigmat(Range(i, i+1), Range(0,3));
				Mat t = bigmat(Range(i, i+1), Range(3,6));

				CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
				CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
      
				r = rvecs[i].t();
				t = tvecs[i].t();
        }
        cvWriteComment( *fs, "Rotation vector + Translation vector", 0 );
        fs << "extrinsic_parameters" << bigmat;
    }
		fs.release();
}

int main (int argc, char* const* argv){

	int retCode=EXIT_SUCCESS;

	try {    

	  CommandLineParser parser(argc, argv, keys);
	  parser.about("Captura imagenes");
	  if (parser.has("help"))
	  {
	      parser.printMessage();
	      return 0;
	  }
	  std::string input = parser.get<std::string>(0);
	  int rows = parser.get<int>(1);
      int cols = parser.get<int>(2);
      float size = parser.get<float>(3);
      int nimg = parser.get<int>(4);
	  if (!parser.check())
	  {
	      parser.printErrors();
	      return 0;
	  }

	  VideoCapture cam;

	  if(input.size()==1){
	    int valor = atoi(input.c_str());
	    cam.open(valor);
	  }else{
	    cam.open(input);
	  }

	  if(! cam.isOpened())
	  {
	    std::cout << "La camara no se ha podido abrir" << std::endl;
	    return EXIT_FAILURE;
	  }

		//no necesario solo permite guardar con mayor calidad
		std::vector<int> compression_params;
	    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	    compression_params.push_back(100);
	    //

	    namedWindow("Video");
		Mat frame;
		cam >> frame;

		bool SaveImage;
		int contador = 0;
		std::string direccion = "//home//antoniogg//Escritorio//FSIV//p4//calibrado//imagenes//img";
		std::stringstream Saveimgs;
		int key = 0;

		while(!frame.empty() && contador < nimg){

			cam >> frame;
			
			if(key == 10){//se activa con el enter por ENTER

				Saveimgs << direccion << contador << ".jpg";
				SaveImage = imwrite(Saveimgs.str().c_str(), frame, compression_params);
				Saveimgs = std::stringstream();
				contador++;
				if (!SaveImage){
					printf("!image %d saved failed!\n",contador);

				}else{
					printf("!image %d saved successful!\n",contador);
				}
			}
			imshow("Video", frame);
			key = cv::waitKey(20) & 0xff;
		}
		cvDestroyWindow("Video");
		cam.release();//cierro el video o camara
		if(contador < nimg){
			std::cout << "El numero de imagenes ha sido insuficiente, salgo del programa" << std::endl;
	  		return EXIT_FAILURE;
		}
		getchar();

		//apartir de aqui se calibra la camara y se guarda aparte permite comparar la camara calibrada y sin calibrar

		cv::Size patternsize = cv::Size(cols-1,rows-1);//esquinas interiores del tablero de ajedrez
		std::vector<cv::Point3f> corners3D;
		std::vector<cv::Point2f> corners2D;//findChessboardCorners guarda los puntos del tablero aqui
		std::vector<std::vector<cv::Point2f>> coord2D;//Ubicacion de las esquinas detectadas en la imagen
		std::vector<std::vector<cv::Point3f>> coord3D;//Ubicacion real de los puntos 3D

		std::stringstream imgs;

		calcChessboardCorners(patternsize,size,corners3D);

		Mat img, imgGray;
		bool found;

		for (int  i = 0; i < nimg; i++){

			imgs << direccion << i << ".jpg";
			img = imread(imgs.str().c_str());
			cvtColor(img, imgGray, COLOR_BGR2GRAY);
			imgs=std::stringstream();

			found = findChessboardCorners(imgGray,patternsize,corners2D,CALIB_CB_ADAPTIVE_THRESH + 
				                                                        CALIB_CB_NORMALIZE_IMAGE + 
																		CALIB_CB_FAST_CHECK);
			if( found) {
		
				cornerSubPix(imgGray, corners2D, Size(11, 11), Size(-1, -1),TermCriteria( 
					                                                        TermCriteria::EPS + 
																			TermCriteria::COUNT, 30, 0.1 ));
				drawChessboardCorners(img,patternsize,Mat(corners2D),found);
				coord2D.push_back(corners2D);
				coord3D.push_back(corners3D);
			} 
			 namedWindow("image");
			 imshow("image", img);
			 waitKey(1500);
		}

		cvDestroyWindow("image");

		Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
		Mat distCoeffs = Mat::zeros(8, 1, CV_64F);
		std::vector<Mat> rvecs;
		std::vector<Mat> tvecs;
	   
		double rms = calibrateCamera(coord3D, coord2D, img.size(), cameraMatrix,
	                  distCoeffs, rvecs, tvecs, 
										CALIB_FIX_PRINCIPAL_POINT +
										CALIB_FIX_ASPECT_RATIO +
										CALIB_ZERO_TANGENT_DIST 
										,TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 30, 2.22e-16));

		std::cout << "RMS: " << rms << std::endl;
		std::cout << "Camera-matrix: " << cameraMatrix << std::endl;
		std::cout << "Distortion-coefficients: " << distCoeffs << std::endl;

		saveparams("//home//antoniogg//Escritorio//FSIV//p4//calibrado//imagenes//Datos_cam.yml",cameraMatrix,distCoeffs,
					rvecs,tvecs,rms);

		int aux;
		std::cout<<"¿Quieres comprobar las diferencias de la camara calibrada y no calibrada?[SI=1/NO=0]"<<std::endl;
		std::cin >> aux;

		if(aux ==1){
			Mat imageUndistorted,image;

			VideoCapture cam;

			if(input.size()==1){
				int valor = atoi(input.c_str());
				cam.open(valor);
			}else{
				cam.open(input);
			}

			if(! cam.isOpened())
			{
				std::cout << "La camara no se ha podido abrir" << std::endl;
				return EXIT_FAILURE;
			}

			namedWindow("imgOriginal");
			namedWindow("imgCalibrada");

			cam >> image;
			key = 0;

			while(!image.empty() && key !=27){
			    
			    undistort(image, imageUndistorted, cameraMatrix, distCoeffs);//corrigo distorsion radial

			    imshow("imgOriginal", image);
			    imshow("imgCalibrada", imageUndistorted);
    
			    cam >> image;
			    key = cv::waitKey(20) & 0xff;
			}
		}
		waitKey(0);
		getchar();
	}
	catch (std::exception& e)
	{
	std::cerr << "Capturada excepcion: " << e.what() << std::endl;
	retCode = EXIT_FAILURE;
	}
	return retCode;
}
