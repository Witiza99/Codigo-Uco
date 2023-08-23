/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>
#include <iostream>
#include <algorithm>
#include <string>


//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>


//processImg [-i] [-c <float=1.0>] [-b <float=0.0>] [-g <float=1.0>] <input img> <output img>
/////////////////////
//Manejo de argumentos
const cv::String keys =
	"{help h usage ? |      | uso: ./main [flags] imagenEntrada ImagenSalida}"
	"{interactive i  |      | activa el modo interactivo}"
	"{contraste c    | 1.0  | contraste}"
	"{brillo b       | 0.0  | brilloo}"
	"{gamma g        | 1.0  | ganma}"
	"{@image1        |<none>| imagen de entrada.}"
	"{@image2        |<none>| imagen de salida.}"
;
/////////////////////
struct Datos{
	cv::Mat vectorImg[2];
	int opciones[3];
};

void normalizacion(cv::Mat &img, cv::Mat &normalizado){
	//normalizo la imagen
	for(int i=0;i<img.rows;i++){//columnas
		for(int j=0;j<img.cols;j++){//filas
			cv::Vec3b v1 = img.at<cv::Vec3b>(i,j);
			cv::Vec3f v2 = normalizado.at<cv::Vec3f>(i,j);
			v2[0]=(float)v1[0]/255;
			v2[1]=(float)v1[1]/255;
			v2[2]=(float)v1[2]/255;
			normalizado.at<cv::Vec3f>(i,j)=v2;//almaceno el resultado
		}
	}
}

void desnormalizacion(cv::Mat &normalizado){
	//normalizo la imagen
	for(int i=0;i<normalizado.rows;i++){//columnas
		for(int j=0;j<normalizado.cols;j++){//filas
			cv::Vec3f v = normalizado.at<cv::Vec3f>(i,j);
			v[0]=(float)v[0]*255;
			if(v[0]>255){v[0]=255;}
			else if(v[0]<0){v[0]=0;}
			v[1]=(float)v[1]*255;
			if(v[1]>255){v[1]=255;}
			else if(v[1]<0){v[1]=0;}
			v[2]=(float)v[2]*255;
			if(v[2]>255){v[2]=255;}
			else if(v[2]<0){v[2]=0;}
			normalizado.at<cv::Vec3f>(i,j)=v;//almaceno el resultado
		}
	}
}

void modificarImagen(cv::Mat &normalizado,const float &C,const float &B, const float &G){//modifica la imagen con los parametros dados
	for(int i=0;i<normalizado.rows;i++){//columnas
		for(int j=0;j<normalizado.cols;j++){//filas
			cv::Vec3f v = normalizado.at<cv::Vec3f>(i,j);
			v[0] = C*pow(v[0],G) + B;//uso la formula
			v[1] = C*pow(v[1],G) + B;
			v[2] = C*pow(v[2],G) + B;
			normalizado.at<cv::Vec3f>(i,j)=v;//almaceno el resultado
		}
	}
}

//trackbar para todos los parametros
void on_trackbar( int, void* userdata)
{
  struct Datos *datos=static_cast<struct Datos *>(userdata);
  float brillo = ((float)datos->opciones[0]-100)/100;
  float contraste = (float)datos->opciones[1]/100;
  float gamma = (float)datos->opciones[2]/100;

  cv::Mat imgAux=datos->vectorImg[0];
  cv::Mat imgAux2=datos->vectorImg[1];
  imgAux.copyTo(imgAux2);
  modificarImagen(imgAux2,contraste,brillo,gamma);
  cv::imshow("copia_img", imgAux2);
}


/*void mode_i(cv::Mat &normalizado){

	struct Datos *datospuntero;
	struct Datos datos;
	normalizado.copyTo(datos.vectorImg[0]);
	datos.vectorImg[0].copyTo(datos.vectorImg[1]);
	datospuntero=&datos;

	datos.opciones[0]=100;
	datos.opciones[1]=100;
	datos.opciones[2]=100;

	cv::createTrackbar( "brightness", "copia_img", &datos.opciones[0], 200, on_trackbar, datospuntero);
	cv::createTrackbar( "contrast", "copia_img", &datos.opciones[1], 200, on_trackbar,datospuntero);
	cv::createTrackbar( "Gamma", "copia_img", &datos.opciones[2], 200, on_trackbar,datospuntero);
	on_trackbar(0, datospuntero);
}*/

int main (int argc, char* const* argv){
  int retCode=EXIT_SUCCESS;

  try {
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Modifica la imagen");
	if(parser.has("help")){
		parser.printMessage();
		return 0;
	}
	float C = parser.get<float>("c"), B = parser.get<float>("b"), G = parser.get<float>("g");
	bool interactivo = parser.has("i");
	cv::String img_name = parser.get<cv::String>(0);
	cv::String img_name2 = parser.get<cv::String>(1);

	if (!parser.check()){
		parser.printErrors();
		return 0;
	}

    cv::Mat img;
   	img = cv::imread(img_name, cv::IMREAD_COLOR);
    if (img.empty())
    {
       std::cerr << "Error: no he podido abrir el fichero '" << img_name << "'." << std::endl;
       return EXIT_FAILURE;
    }

    //creo la ventana y cargo la imagen
	cv::namedWindow("IMG");
	cv::namedWindow("copia_img");
	cv::imshow("IMG", img);

	struct Datos *datospuntero;
	struct Datos datos;

	//creo copia para la normalizacion
	cv::Mat normalizado(img.rows,img.cols,CV_32FC3);
	datos.vectorImg[0]=normalizado;
	normalizacion(img, datos.vectorImg[0]);
	datos.vectorImg[0].copyTo(datos.vectorImg[1]);
	datospuntero=&datos;

	//guardo la imagen en el caso de que la tecla pulsada no sea esc
	if(interactivo==true){
		//mode_i(normalizado);//modo interactivo

		datos.opciones[0]=100;
		datos.opciones[1]=100;
		datos.opciones[2]=100;

		cv::createTrackbar( "brightness", "copia_img", &datos.opciones[0], 200, on_trackbar, datospuntero);
		cv::createTrackbar( "contrast", "copia_img", &datos.opciones[1], 200, on_trackbar,datospuntero);
		cv::createTrackbar( "Gamma", "copia_img", &datos.opciones[2], 200, on_trackbar,datospuntero);
		on_trackbar(0, datospuntero);
	}else{
		if((C<0)||(C>2.0)){
			std::cout<<"Valor introducido fuera de rango, se dispone a asignar valor por defecto."<<std::endl;
			C=1;
		}//si los valores no estan entre mis condiciones los configuro
		if((B<(-1.0))||(B>1.0)){
			std::cout<<"Valor introducido fuera de rango, se dispone a asignar valor por defecto."<<std::endl;
			B=0;
			}//si los valores no estan entre mis condiciones los configuro
		if((G<0)||(G>2.0)){
			std::cout<<"Valor introducido fuera de rango, se dispone a asignar valor por defecto."<<std::endl;
			G=1;
			}//si los valores no estan entre mis condiciones los configuro
		modificarImagen(datospuntero->vectorImg[1],C,B,G);
		cv::imshow("copia_img", datospuntero->vectorImg[1]);
	}

	//guardo la imagen en el caso de que la tecla pulsada no sea esc
	int key=0;
	key=cv::waitKey(0) & 0xff;
	if(key!=27){
		datospuntero->vectorImg[1].copyTo(datospuntero->vectorImg[0]);
		desnormalizacion(datospuntero->vectorImg[0]);
		imwrite(img_name2, datospuntero->vectorImg[0]);
	}
	cv::destroyAllWindows();

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
