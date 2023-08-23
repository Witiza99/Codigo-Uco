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
    "{verbose        |      | activate verbose mode.}"
    "{i intrinsics   |      | Calibrate only extrinsics parameters. Using intrinsics from given file (-i=intr-file).}"
    "{s size         |<none>| square size.}"
    "{r rows         |<none>| number of board's rows.}"
    "{c cols         |<none>| number of board's cols.}"
    "{@output        |<none>| filename for output intrinsics file.}"
    "{@input1        |<none>| first board's view.}"
    "{@input2        |      | second board's view.}"
    "{@inputn        |      | ... n-idx board's view.}"
    ;

int
main (int argc, char* const* argv)
{
    int retCode=EXIT_SUCCESS;

    try {        
        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Calibrate the intrinsics parameters of a camera.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return EXIT_SUCCESS;
        }
        float square_size = parser.get<float>("s");
        int rows = parser.get<int>("r");
        int cols = parser.get<int>("c");
        bool verbose = parser.has("verbose");
        std::string output_fname = parser.get<cv::String>("@output");
        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        //Get the inputs.
        //find the second argument without '-' at begin.
        int input = 1;
        bool found = false;
        while (input<argc && !found)
            found = argv[input++][0] != '-';
        CV_Assert(input<argc);
        std::vector<std::string> input_fnames;        
        for (; input<argc; ++input)
            input_fnames.push_back(std::string(argv[input]));

        //TODO

        std::vector<cv::Mat> imagenes;
        for(int i=0; i< input_fnames.size();i++){
            cv::Mat img;
            img =imread(input_fnames[i], cv::IMREAD_COLOR);
            if (img.empty()){
                std::cerr << "La imagen no se ha podido abrir" << std::endl;
                return EXIT_FAILURE;
            }
            imagenes.push_back(img);
        }


        if (parser.has("i"))
        {
            //TODO
            //Make extrinsic calibration.
            //Remenber: only one view is needed.
            std::vector<cv::Point3f> pt3d;
            std::vector<cv::Point2f> corner_points;
            cv::Size board_size(cols-1,rows-1);
            cv::Size camera_size;
            float error;
            cv::Mat camera_matrix;
            cv::Mat dist_coeffs;
            cv::Mat rvec;
            cv::Mat tvec;

            cv::FileStorage fs(output_fname, cv::FileStorage::READ);
            if(! fs.isOpened())
            {
                std::cerr << "El archivo no se ha podido abrir" << std::endl;
                return EXIT_FAILURE;
            }
            fsiv_load_calibration_parameters(fs, camera_size, error,camera_matrix,dist_coeffs,rvec,tvec);

            pt3d = fsiv_generate_3d_calibration_points(board_size, square_size);

            for (int  i = 0; i < imagenes.size(); i++){
                if(fsiv_find_chessboard_corners(imagenes[i], board_size, corner_points)){
                    std::cout << "Image Found"<< std::endl;
                    fsiv_compute_camera_pose(pt3d,corner_points,camera_matrix,dist_coeffs,rvec,tvec);
                    if (verbose)
                    {
                        //TODO
                        //Show WCS axis.
                        cv::namedWindow("Ejes");
                        int longlinea = 2;
                       
                        fsiv_draw_axes(imagenes[i],camera_matrix, dist_coeffs, rvec, tvec, square_size,longlinea);
                        cv::imshow("Ejes", imagenes[i]);
                        cv::waitKey(0);
                        //
                    }
                }else{
                    std::cout << "Image Not Found"<< std::endl;
                }  
            }
            //
            
        }
        else
        {
            //TODO
            //Make an intrisic calibration.
            //Remember: For each view (at least two) you must find the
            //chessboard to get the 3D -> 2D matches.
            std::vector<cv::Point3f> pt3d;
            std::vector<cv::Point2f> corner_points;
            std::vector<std::vector<cv::Point2f>> vcorner_points;
            std::vector<std::vector<cv::Point3f>> vpt3d;
            cv::Size board_size(cols-1,rows-1);
            cv::Size camera_size(imagenes[0].cols,imagenes[0].rows);

            pt3d = fsiv_generate_3d_calibration_points(board_size, square_size);
            for (int  i = 0; i < imagenes.size(); i++){
                if(fsiv_find_chessboard_corners(imagenes[i], board_size, corner_points)){
                    vcorner_points.push_back(corner_points);
                    vpt3d.push_back(pt3d);
                    std::cout << "Image Found"<< std::endl;
                }else{
                    std::cout << "Image Not Found"<< std::endl;
                }
            }

            cv::Mat camera_matrix = cv::Mat::eye(3, 3, CV_64F);
            cv::Mat dist_coeffs = cv::Mat::zeros(1, 5, CV_64F);
            std::vector<cv::Mat> rvecs;
            std::vector<cv::Mat> tvecs;
            float error;
            error = fsiv_calibrate_camera(vcorner_points, vpt3d, camera_size, camera_matrix, dist_coeffs, NULL, NULL);
            //
            cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64F);
            //rvecs[0].copyTo(rvec);

            cv::Mat tvec = cv::Mat::zeros(3, 1, CV_64F);
            //tvecs[0].copyTo(tvec);
            cv::FileStorage fs(output_fname, cv::FileStorage::WRITE);
            fsiv_save_calibration_parameters(fs, camera_size,error, camera_matrix, dist_coeffs, rvec, tvec);

            if (verbose)
            {
                //TODO
                //Show WCS axis.
                cv::namedWindow("Ejes");
                int longlinea = 2;
                for (int  i = 0; i < imagenes.size(); i++){
                    fsiv_draw_axes(imagenes[i],camera_matrix, dist_coeffs, rvec, tvec, square_size,longlinea);
                    cv::imshow("Ejes", imagenes[i]);
                    cv::waitKey(0);
                }
                //

                //
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Capturada excepcion: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
