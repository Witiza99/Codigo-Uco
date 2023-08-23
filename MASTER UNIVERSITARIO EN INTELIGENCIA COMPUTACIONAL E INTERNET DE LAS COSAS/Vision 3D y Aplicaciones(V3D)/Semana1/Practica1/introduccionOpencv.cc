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

const char * keys =
    "{help h usage ? |      | print this message   }"
    "{@image1        |      | imagen para sacar sus valores max y min  }"
    "{funcion f      |0     | funcionamiento del programa, 1 recorriendo imagen, 2 funcion de opencv   }"
    ;

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
      int funcion = parser.get<int>("funcion");
      cv::String img1 = parser.get<cv::String>("@image1");
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

      //Carga la imagen desde archivo.
      //En funcion de como se compilo opencv podra
      //cargar mas o menos formatos graficos.
      cv::Mat img = cv::imread(img1, cv::IMREAD_ANYCOLOR);
      if (img.empty())
      {
         std::cerr << "Error: no he podido abrir el fichero '" << img1 << "'." << std::endl;
         return EXIT_FAILURE;
      }

      //se divide la matriz en canales
      std::vector<cv::Mat> canales;

      //De-entrelaza la imagen (si lo está), guardando cada canal
      //como una matriz diferente.
      //la operación contraria es cv::merge()
      cv::split(img, canales);

    /*Código para indicar valor max y min de la imagen dada, para canal y de dos formas distintas*/
      double max;
      double min;
      cv::Point minID;
      cv::Point maxID;

      //funcion 1 donde se busca el max y min directamente en la imagen
      if (funcion == 1){
        //creamos variables para almacenar los puntos max y min
        int xmax, ymax;
        int xmin, ymin;

        for(size_t c = 0; c<canales.size(); ++c){//recorremos todos los canales
          //variables que almacenan el maximo y minimo del canal
          float max = 0;
          float min = 999;

          std::cout << "Canal " << c << ":" << std::endl;
          for(int i=0;i<canales[c].rows;i++){//columnas
            for(int j=0;j<canales[c].cols;j++){//filas
              const float valor = canales[c].at<uchar>(i,j);

              //se comprueba max y minimo y en el caso de encontrar nuevo valor se cambia
              if (valor > max){
                max = valor;
                xmax = j;
                ymax = i;
              }
              if (valor < min){
                min = valor;
                xmin = j;
                ymin = i;
              }
            }
          }
        //imprimimos resultados
        std::cout<<"El valor máximo es: "<<max<<std::endl;
        std::cout<<"Su posicion es: ["<<xmax<<", "<<ymax<<"]"<<std::endl;
        std::cout<<"El valor minimo es: "<<min<<std::endl;
        std::cout<<"Su posicion es: ["<<xmin<<", "<<ymin<<"]"<<std::endl;
        }

      //funcion 1 donde se busca el max y min con funcion de opencv
      }else if(funcion == 2){
        for(size_t c = 0; c<canales.size(); ++c){//recorremos todos los canales
          std::cout << "Canal " << c << ":" << std::endl;
          cv::minMaxLoc(canales[c],&min,&max,&minID,&maxID);
          //imprimimos resultados
          std::cout<<"El valor máximo es: "<<max<<std::endl;
          std::cout<<"Su posicion es: "<<maxID<<std::endl;
          std::cout<<"El valor minimo es: "<<min<<std::endl;
          std::cout<<"Su posicion es: "<<minID<<std::endl;
        }
      }else{
        std::cerr << "No se ha introducido la opcion correcta para el funcionamiento del programa, pruebe con 1 o 2" << std::endl;
        return EXIT_FAILURE;
      }

    
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Capturada excepcion desconocida!" << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
