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
    "{help h usage ? |      | print this message                     }"
    "{@directorioent |<none>| directorio con las imagenes de entrada }"
    "{@ficherosalida |<none>| nombre del fichero de salida           }"
    ;

static void calcChessboardCorners(Size boardSize, float squareSize, std::vector<cv::Point3f>& corners)
{
    corners.clear();
    for(int i = 0; i < boardSize.height; i++ ){
        for( int j = 0; j < boardSize.width; j++ ){
            corners.push_back(Point3f(float(j*squareSize), float(i*squareSize), 0)); 
        }
    }
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
        cv::String nombreficherosalida = parser.get<cv::String>("@ficherosalida");
        if (!parser.check()){
            parser.printErrors();
            return 0;
        }
        cv::String directorioentrada = parser.get<cv::String>("@directorioent");
        if (!parser.check()){
            parser.printErrors();
            return 0;
        }

        Mat imgGray;
        int rows = 5;
        int cols = 7;
        float size = 0.02875;
        bool found1, found2 = false;
        char key = 0;
        std::vector<std::string> imagenesajedrez;

        //apartir de aqui se calibra la camara y se guarda aparte permite comparar la camara calibrada

        Size patternsize = Size(cols,rows);//esquinas interiores del tablero de ajedrez

        std::vector<Point2f> img1corners2D,img2corners2D;//findChessboardCorners guarda los puntos del tablero aqui
        std::vector<std::vector<Point2f>> img1coord2D,img2coord2D;//Ubicacion de las esquinas detectadas en la imagen

        std::vector<Point3f> corners3D;
        std::vector<std::vector<Point3f>> coord3D;//Ubicacion real de los puntos 3D

        calcChessboardCorners(patternsize,size,corners3D);

        //creamos vector con todas las rutas de los archivos
        for (const auto & entry : fs::directory_iterator(directorioentrada))
            imagenesajedrez.push_back(entry.path());

        Mat imgejemplosize;

        for (int i = 0; i < imagenesajedrez.size(); i++){
            std::cout << imagenesajedrez[i] << std::endl;
            Mat img = cv::imread(imagenesajedrez[i]);//Carga la imagen desde archivo.
            if (img.empty()){
                std::cerr << "Error: no he podido abrir el fichero '" << imagenesajedrez[i] << "'." << std::endl;
                return EXIT_FAILURE;
            }

            Mat img1, img2;

            Rect imgRoi1(0,0,(img.cols/2),img.rows);
            Rect imgRoi2((img.cols/2),0,(img.cols/2),img.rows);

            Mat imgcortada1 = img(imgRoi1);
            Mat imgcortada2 = img(imgRoi2);

            //cambio la imagen para que se divida en dos
            cvtColor(imgcortada1, img1, COLOR_BGR2GRAY);
            cvtColor(imgcortada2, img2, COLOR_BGR2GRAY);       
            
            imgejemplosize = imgcortada1;

            found1 = findChessboardCorners(img1,patternsize,img1corners2D, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE);
            found2 = findChessboardCorners(img2,patternsize,img2corners2D, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE);

            if(found1){
                cornerSubPix(img1, img1corners2D, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 60, 1e-6));
                drawChessboardCorners(img1,patternsize,Mat(img1corners2D),found1);
            }
            
            if(found2){
                cornerSubPix(img2, img2corners2D, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 60, 1e-6));
                drawChessboardCorners(img2,patternsize,Mat(img2corners2D),found2);
            }

            imshow("image1", img1);
            imshow("image2", img2);
            
 
            key = (char) waitKey(10);
            
            if(found1 && found2){
                key = (char) waitKey(0);
            }

            if(key == 27){
                break;
            }

            if(found1 == 1 && found2 == 1){ //si se encuentran los dos chestboard
                img1coord2D.push_back(img1corners2D);
                img2coord2D.push_back(img2corners2D);
                coord3D.push_back(corners3D);
                std::cout << "Exito " << std::endl;
            }
        }

        destroyAllWindows();

        //Calibrates and saves calibration data
        std::cout << "Starting Calibration..." << std::endl;
        
        Mat K1, K2, R, F, E, T;
        Mat D1, D2;

        //arreglar la calibracion
        stereoCalibrate(coord3D, img1coord2D, img2coord2D, K1, D1, K2, D2, imgejemplosize.size(), R, T, E, F,0,
                TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 60, 1e-6));
        
        FileStorage fs1(nombreficherosalida, FileStorage::WRITE);
        fs1 << "LEFT_K" << K1;
        fs1 << "LEFT_D" << D1;
        fs1 << "RIGTH_K" << K2;
        fs1 << "RIGTH_D" << D2;
        fs1 << "R" << R;
        fs1 << "T" << T;
        fs1 << "E" << E;
        fs1 << "F" << F;
        
        std::cout << "Calibration completed" << std::endl;

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
