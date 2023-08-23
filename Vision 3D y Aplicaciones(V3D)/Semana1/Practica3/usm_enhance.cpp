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
//#include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"

const cv::String keys =
    "{help h usage ? |      | print this message.}"
    "{i interactive  |      | Interactive mode.}"
    "{r radius       |1     | Window's radius. Default 1.}"
    "{g gain         |1.0   | Enhance's gain. Default 1.0}"
    "{f filter       |0     | Filter type: 0->Box, 1->Gaussian. Default 0.}"
    "{@input         |<none>| input image.}"
    "{@output        |<none>| output image.}"
    ;


int
main (int argc, char* const* argv)
{
    int retCode=EXIT_SUCCESS;

    try {
        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Apply an unsharp mask enhance to an image.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return EXIT_SUCCESS;
        }

        //TODO: Get the CLI parameters.
        //Remenber: use parser.get< type >("xxx") for values.
        //  or parser.has("xxx") for flags.
        //
        int r = parser.get<int>("radius");
        float g = parser.get<float>("gain");
        int f = parser.get<int>("filter");
        cv::String input_n = parser.get<cv::String>("@input");
        cv::String output_n = parser.get<cv::String>("@output");
        //

        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        cv::Mat in;
        cv::Mat unsharp_mnask;
        cv::Mat out;

        //TODO: Load the input image as it is in the file.
        in = cv::imread(input_n, cv::IMREAD_ANYCOLOR);
        //

        if (in.empty())
        {
            std::cerr << "Error: could not open input image." << std::endl;
            return EXIT_FAILURE;
        }

        //TODO: use your function fsiv_usm_enhance()
        //Remenber: if the input is in RGB you we want only process the "luma".
        //Hint: use HSV color space to this. See cv::cvtColor.
        //Remenber: save the unsharp mask in "unsharp_mask" variable.
        cv::Mat hsv;
        //llamar a la funcion que convierte la matriz

        if(in.channels()==1){

            hsv = in.clone();

            hsv.convertTo(hsv,CV_32F, 1.0/255.0);

            out = fsiv_usm_enhance(hsv, g, r, f, &unsharp_mnask);

            out.convertTo(out, CV_8U, 255.0, 0.0);

        }else{

            cvtColor(in, hsv, cv::COLOR_BGR2HSV);
            hsv.convertTo(hsv,CV_32F, 1.0/255.0);

            std::vector<cv::Mat> channels;
            split(hsv, channels);

            out = fsiv_usm_enhance(channels[2], g, r, f, &unsharp_mnask);

            channels[2] = out.clone();

            merge(channels, hsv);
            hsv.convertTo(hsv, CV_8U, 255.0, 0.0);
            cvtColor(hsv, out, cv::COLOR_HSV2BGR);
        }        

        //

        cv::namedWindow("INPUT", cv::WINDOW_GUI_EXPANDED);
        cv::imshow ("INPUT", in);
        cv::namedWindow("OUTPUT", cv::WINDOW_GUI_EXPANDED);
        cv::imshow ("OUTPUT", out);
        cv::namedWindow("UNSHARP MASK", cv::WINDOW_GUI_EXPANDED);
        cv::imshow ("UNSHARP MASK", unsharp_mnask);
        int k = cv::waitKey(0)&0xff;
        if (k!=27)
        {
            //TODO
            //Almacena la imagen.
            bool SaveImage;
            SaveImage = imwrite(output_n, out);
            if (!SaveImage){
                    printf("!image saved failed!\n");

                }else{
                    printf("!image saved successful!\n");
                }
            //
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Capturada excepcion: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
