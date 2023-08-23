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


//processImg [-i] [-c <int=0>] [-g <float=1.0>] <input img> <output img>
/////////////////////
//Manejo de argumentos
const cv::String keys =
	"{help h usage ? |      | uso: ./main [flags] imagenEntrada ImagenSalida}"
	"{interactive i  |      | activa el modo interactivo}"
	"{f 		     | 0    | tipo}"
	"{g 	         | 1.0  | ganancia}"
	"{convolve c     | 0    | convolve}"
	"{@image1        |<none>| imagen de entrada.}"
	"{@image2        |<none>| imagen de salida.}"
;
/////////////////////

cv::Mat create_sharp_filter(int tipo, float g){//funcion para crear la máscara
	cv::Mat mask(3,3,CV_32FC1);//mascara 3*3 de un solo canal
	if(tipo==0){
		mask.at<float>(0,0)=mask.at<float>(0,2)=mask.at<float>(2,0)=mask.at<float>(2,2)=0;
		mask.at<float>(0,1)=mask.at<float>(1,0)=mask.at<float>(1,2)=mask.at<float>(2,1)=-1;
		mask.at<float>(1,1)=g+4;
	}else{
		mask.at<float>(0,0)=mask.at<float>(0,2)=mask.at<float>(2,0)=mask.at<float>(2,2)=mask.at<float>(0,1)=mask.at<float>(1,0)=mask.at<float>(1,2)=mask.at<float>(2,1)=-1;
		mask.at<float>(1,1)=g+8;
	}
	return mask;
}

void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type=0){

	assert(in.type()==CV_32FC1);
	assert(filter.type()==CV_32FC1);

	int padrows = filter.rows-1;
	int padcols = filter.cols-1;

	cv::Mat aux = cv::Mat::zeros(in.rows+padrows, in.cols+padcols, CV_32F);
	cv::Mat reserva = cv::Mat::zeros(in.rows+padrows, in.cols+padcols, CV_32F);
	if(border_type==1){
		//codigo de interpolacion
	}else{
		for(int i=(padrows/2);i<aux.rows-(padrows/2);i++){
			for(int j=(padcols/2);j<aux.cols-(padcols/2);j++){
				aux.at<float>(i,j) = in.at<float>(i-(padrows/2),j-(padcols/2));
				reserva.at<float>(i,j) = in.at<float>(i-(padrows/2),j-(padcols/2));
			}
		}
	}

	for(int i=(padrows/2);i<aux.rows-(padrows/2);i++){//filas
		for(int j=(padcols/2);j<aux.cols-(padcols/2);j++){//columnas
			//std::cin.ignore();
			//std::cin.ignore();
			float suma = 0.0;
			int aux1=0;
			for(int w=-padrows/2;w<=padrows/2;w++){
				int aux2=0;
				for(int z=-padcols/2;z<=padcols/2;z++){
					suma = suma + aux.at<float>(i+w,j+z)*filter.at<float>(aux1,aux2);//se podria usar la matriz in ya que no se modifica pero no la uso ya que usted decía que no era correcto por eso me apoyo en matriz auxiliar
					//std::cout<<i<<", "<<w<<", "<<j<<", "<<z<<", "<<aux.at<float>(i+w,j+z)<<"*"<<filter.at<float>(aux1,aux2)<<", "<<aux1<<", "<<aux2<<std::endl;
					aux2++;				
				}
				aux1++;
			}
			reserva.at<float>(i,j)=suma;//almaceno el resultado
		}
	}

	//quito el padding
	out.create(in.rows, in.cols, in.type());
	for(int i=0;i<out.rows;i++){
		for(int j=0;j<out.cols;j++){
			out.at<float>(i,j) = reserva.at<float>(i+(padrows/2),j+(padcols/2));
		}
	}
}

int main (int argc, char* const* argv){
  int retCode=EXIT_SUCCESS;

  try {
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Aplica sharp mask");
	if(parser.has("help")){
		parser.printMessage();
		return 0;
	}
	int f = parser.get<int>("f"), c = parser.get<int>("c");
	float g = parser.get<float>("g");
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

	//creo copia para la normalizacion
	cv::Mat normalizado;
	img.convertTo(normalizado, CV_32FC3, 1/255.0);

	//guardo la imagen en el caso de que la tecla pulsada no sea esc
	if(interactivo==true){
		//codigo de modo interactivo
	}else{
		if((f<0)||(f>1)){
			std::cout<<"Valor introducido fuera de rango, se dispone a asignar valor por defecto."<<std::endl;
			f=0;
		}//si los valores no estan entre mis condiciones los configuro
		if(g<0.0){
			std::cout<<"Valor introducido fuera de rango, se dispone a asignar valor por defecto."<<std::endl;
			g=0.0;
		}//si los valores no estan entre mis condiciones los configuro
		
		cv::Mat mask = create_sharp_filter(f, g);

		std::vector<cv::Mat> separocanales(3);//creo matrices para cada canal, para enviarlos
		std::vector<cv::Mat> fusioncanales(3);//creo matrices para cada canal, para recibirlos

		//divido canales
		cv::split(normalizado, separocanales);

		//llamo a mi funcion convolve
		convolve(separocanales[0], mask, fusioncanales[0], c);
		convolve(separocanales[1], mask, fusioncanales[1], c);
		convolve(separocanales[2], mask, fusioncanales[2], c);

		//uno canales
		cv::merge(fusioncanales, normalizado);
		cv::imshow("copia_img", normalizado);
	}

	//guardo la imagen en el caso de que la tecla pulsada no sea esc
	int key=0;
	key=cv::waitKey(0) & 0xff;
	if(key!=27){
		normalizado.convertTo(normalizado, CV_8UC3, 255.0/1);
		imwrite(img_name2, normalizado);
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
