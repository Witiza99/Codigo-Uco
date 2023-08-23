/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

vector<Point3f> create_obj_points(int cols, int rows, float size){
  vector<Point3f> aux;
    for( int i = 0; i < rows; i++ ){
        for( int j = 0; j < cols; j++ ){
            aux.push_back(Point3f(float(j*size),float(i*size), 0)); 
        }
    }
  return aux;
}

void draw_model(Mat &img, float size, int rows, int cols, Mat const& camera_mat, Mat const& dist_coefs, Mat const& rvec, Mat const& tvec, string archivo, Mat const &imgM = {0,0,0}){

  vector<Point2f> img_points;
  vector<Point3f> ejes;
  img_points.clear();
  ejes.clear();

  
  if(archivo== "vacio"){
  	ejes.push_back(Point3f(0,0,0));
	ejes.push_back(Point3f(size,0,0));
	ejes.push_back(Point3f(0,size,0));
	ejes.push_back(Point3f(0,0,-(size)));

	projectPoints(ejes, rvec, tvec, camera_mat, dist_coefs, img_points);

    //coordenadas
    line(img, img_points[0], img_points[1], Scalar(0,0,255), 2);
    line(img, img_points[0], img_points[2], Scalar(0,255,0), 2);
    line(img, img_points[0], img_points[3], Scalar(255,0,0), 2);

  }else if(archivo == "imagen"){

    //para hacer la parte de la imagen
    Mat matriz_trans;
    Mat aux;
    vector<Point2f> dst_p;
    dst_p.clear();
    ejes.push_back(Point3f(-size,-size,0));
    ejes.push_back(Point3f(-size, rows*size,0));
	ejes.push_back(Point3f(cols*size, rows*size,0));
	ejes.push_back(Point3f(cols*size,-size,0));
	
	projectPoints(ejes, rvec, tvec, camera_mat, dist_coefs, img_points);
    //puntos de la imagen a introducir
    dst_p.push_back(Point2f(0.0, 0.0));
    dst_p.push_back(Point2f(0.0, imgM.rows));
    dst_p.push_back(Point2f(imgM.cols, imgM.rows));
    dst_p.push_back(Point2f(imgM.cols, 0.0));
    

    matriz_trans=getPerspectiveTransform(dst_p, img_points);

    warpPerspective(imgM, aux, matriz_trans, Size(img.cols,img.rows));
    vector<Point> img_points_int;
    for(int i = 0; i < img_points.size(); i++){
    	img_points_int.push_back(Point((int)img_points[i].x,(int)img_points[i].y)); 
    }

    fillConvexPoly(img,img_points_int,Scalar(0,0,0));
   	img=img|aux;
  }
}

const String keys =
    "{help h usage ? |      | print this message                 }"
    "{@rows          |<none>| filas  de calibracion              }"
    "{@cols          |<none>| columnas de calibracion            }"
    "{@size          |<none>| tamaño del cuadro de calibracion   }"
    "{@calibfile     |<none>| archivo parametros intrinsecos     }"
    "{@input         |<none>| input, Video                       }"
    "{i              |      | imagen a renderizar                }"
    "{v              |      | video a renderizar                 }"
    ;

int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    

      CommandLineParser parser(argc, argv, keys);
      parser.about("Application name v1.0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      string i = parser.get<string>("i");
      string v = parser.get<string>("v");
      cout<<v<<endl;
      int rows = parser.get<int>(0);
      int cols = parser.get<int>(1);
      float size = parser.get<float>(2);
      string calibfile = parser.get<string>(3);
      string input = parser.get<string>(4);
      
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    /*Ahora toca que tu rellenes con lo que hay que hacer ...*/

      //compruebo si pasa video o imagen
      string archivo;
      cv::Mat imgM;
      VideoCapture vidM;
      int flag_a = 0;

      if(i.size()>0){       
        imgM =imread(i, cv::IMREAD_COLOR);
        archivo = "imagen";
        if (imgM.empty())
        {
          cerr << "La imagen no se ha podido abrir" << endl;
          return EXIT_FAILURE;
        }
      }else if(v.size()>0){
        vidM.open(v);
        archivo = "imagen";
        if(! vidM.isOpened())
        {
          cerr << "El archivo de video no se ha podido abrir" << endl;
          return EXIT_FAILURE;
        }
        }else{
          archivo = "vacio";
        }

      VideoCapture vid;

      if(input.size()==1){
        int valor = atoi(input.c_str());
        vid.open(valor);
      }else{
        vid.open(input);
      }

      if(! vid.isOpened())
      {
        cerr << "El archivo de video o camara no se ha podido abrir" << endl;
        return EXIT_FAILURE;
      }

      FileStorage intr(calibfile, FileStorage::READ);
      if(! intr.isOpened())
      {
        cerr << "El archivo no se ha podido abrir" << endl;
        return EXIT_FAILURE;
      }

      Mat camera_mat;
      Mat dist_coefs;
      intr["camera-matrix"] >> camera_mat;
      intr["distortion-coefficients"] >> dist_coefs;

      namedWindow("Video");
      Mat frame;

      if(v.size()>0){
          vidM >> imgM;
      }
      vid >> frame;
      int key = 0;

      vector<Point3f> obj_pts = create_obj_points(cols-1, rows-1, size);
      
      while (!frame.empty() && key !=27 && flag_a==0)
      {
        vector<Point2f> corners;
        //detectar tablero
        if(findChessboardCorners(frame, Size(cols-1,rows-1), corners))
        {
          Mat gray;
          cvtColor(frame, gray, COLOR_BGR2GRAY);
          cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
          Mat rvec, tvec;
          solvePnP(obj_pts, corners, camera_mat, dist_coefs, rvec, tvec);
          
          draw_model(frame, size, rows-1, cols-1, camera_mat, dist_coefs, rvec, tvec, archivo, imgM);
          if(v.size()>0){
          	vidM >> imgM;
          	if(imgM.empty()){
          		flag_a=1;
          	}
          }

          imshow("Video", frame);
        }
        else
          imshow("Video", frame);

        key = cv::waitKey(20) & 0xff;
        vid >> frame; 
      }
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
