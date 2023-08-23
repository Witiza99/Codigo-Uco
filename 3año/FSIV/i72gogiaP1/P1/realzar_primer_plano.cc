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

const cv::String keys =
    "{help h usage ? |      | print this message.   }"
    "{@image         |<none>| image to show.         }"
    "{@image1        |<none>| image name.         }"
    ;
cv::Mat img;
void on_mouse(int event, int x, int y, int flags, void *userdata)
{
	cv::Mat copia_img;
	img.copyTo(copia_img);
	cv::Point aux(x, y);
	if (event == cv::EVENT_LBUTTONDOWN)
    {
        static_cast<cv::Point*>(userdata)[0]=aux;

    }else if (event == cv::EVENT_LBUTTONUP)
    {    
		static_cast<cv::Point*>(userdata)[1]=aux;
		cv::rectangle(copia_img, static_cast<cv::Point*>(userdata)[0], static_cast<cv::Point*>(userdata)[1], cv::Scalar(255, 255, 0), 2, 8, 0);
		cv::imshow("IMG", copia_img);//cambiar parametro
		cv::waitKey(0) & 0xff;
		img.copyTo(copia_img);//permito que se pueda hacer varias veces el cuadro sin que se queden los anteriores
    }
}

int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Application name v1.0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      cv::String img_name = parser.get<cv::String>(0);

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }
      cv::String img_name2 = parser.get<cv::String>(1);


    img = cv::imread(img_name, cv::IMREAD_COLOR);
      
      if (img.empty())
      {
         std::cerr << "Error: no he podido abrir el fichero '" << img_name << "'." << std::endl;
         return EXIT_FAILURE;
      }

      //creo la ventana y cargo la imagen
	    cv::namedWindow("IMG");
	    cv::imshow("IMG", img);

	    //creación de todo lo relacionado con el vector de coordenadas que voy a mandar
	    ///////////////////////////////////////////////////////
	    cv::Point pt1(-1, -1);
	    cv::Point pt2(-1, -1);
		cv::Point coords[2];
		coords[0]=pt1;
		coords[1]=pt2;
		/////////////////////////////////////////////////////////
	    //Conectamos a la ventana un callback para gestionar el raton.
	    cv::setMouseCallback ("IMG", on_mouse, coords);
	    cv::rectangle(img, coords[0], coords[1], cv::Scalar(255, 255, 0), 2, 8, 0);

	    //muestro la imagen
	    int key=0;
    	key=cv::waitKey(0) & 0xff;

    	//creo imagen donde voy a trabajar
	    cv::Mat copia_img;
	    img.copyTo(copia_img);

		//cabio la imagen al gris
		int media;
		cv::Point minimo(std::min(coords[0].x, coords[1].x), std::min(coords[0].y, coords[1].y));
		cv::Point maximo(std::max(coords[0].x, coords[1].x), std::max(coords[0].y, coords[1].y));
		std::cout<<minimo.x<<","<<minimo.y<<"   "<<maximo.x<<","<<maximo.y<<std::endl;
		for(int j=0;j<copia_img.rows;j++){//altura
			for(int i=0;i<copia_img.cols;i++){//anchura
				if(not((i>minimo.x)&&(i<maximo.x)&&(j>minimo.y)&&(j<maximo.y))){
					cv::Vec3b v = copia_img.at<cv::Vec3b>(j,i);
					media=(int)((v[0]+v[1]+v[2])/3);
					v[0]=media;
					v[1]=media;
					v[2]=media;
					copia_img.at<cv::Vec3b>(j,i)=v;
				}
			}
		}
		//creo un rectangulo para que se vea mejor la zona con color
		cv::rectangle(copia_img, coords[0], coords[1], cv::Scalar(255, 255, 0), 2, 8, 0);
		cv::imshow("IMG", copia_img);//cambiar parametro

		//guardo la imagen en el caso de que la tecla pulsada no sea esc
		key=cv::waitKey(0) & 0xff;
		if(key!=27){
			imwrite(img_name2, copia_img);
		}

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}



