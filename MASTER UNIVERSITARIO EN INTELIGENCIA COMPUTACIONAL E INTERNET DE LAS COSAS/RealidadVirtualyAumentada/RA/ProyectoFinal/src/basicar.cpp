// This program reads a model image, a video and a patch image, and overlays the patch on the model object in the video frames.
// Se añadio, grabar la salida, capturar imagenes, elegir entre distintos keypoints y la capacidad de dibujar una casa en 3d.
// Se comento la funcionalidad de imprimir una imagen en 3 dimensiones (con la homografía funciona más rapido y con mayor sencillez)

// Esqueleto (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <string> 

#include "rva.h"

using namespace std;

const cv::String keys =
"{help h usage ? |      | print this message   }"
"{@model         |<none>| Path to image model.}"
"{@video         |<none>| Path to video scene.}"
"{patch          |<none>| Path to image patch.}"
"{video2         |<none>| Path to a second video.}"
"{ancho          |<none>| ancho patron.}"
"{largo          |<none>| largo patron.}"
"{calibracion    |<none>| archivo calibracion.}"
"{kp_float       |<none>| tipo de kp, si no se activa por defecto binario.}"
"{save           |<none>| grabo la pantalla.}"
;

// Main function
int main(int argc, char ** argv) {

    // Get the arguments: model, video and patch using OpenCv parser
    cv::CommandLineParser parser(argc, argv, keys);
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    //parametros introducidos aparte (ancho, largo, archivo de configuracion, guardado de la salida, tipo de keypoint a utilizar)
    int ancho = 0;
    int largo = 0;
    ancho = parser.get<int>("ancho");
    largo = parser.get<int>("largo");
    std::string archivo_calibracion = parser.get<std::string>("calibracion");  


    bool tipo_kp_float = parser.get<bool>("kp_float");  
    bool save = parser.get<bool>("save");
    

    // Video2 has priority over patch
    bool use_calibracion = !archivo_calibracion.empty();

    string model_path = parser.get<string>(0);
    string video_path = parser.get<string>(1);
    
    // Patch argument is available?
    string patch_path = parser.get<string>("patch");

    // Second video argument is available?
    string video2_path = parser.get<string>("video2");

    // Video2 has priority over patch
    bool use_video2 = !video2_path.empty();
    bool use_patch = !patch_path.empty() && !use_video2;

    if (!use_video2 && !use_patch) {
        cout << "Error: no patch or video2" << endl;
        return -1;
    }

    // Load the images in color
    cv::Mat img_model = cv::imread(model_path, cv::IMREAD_COLOR);

    cv::Mat img_patch;
    if (use_patch)
        img_patch = cv::imread(patch_path, cv::IMREAD_COLOR);

    // Check if the images are loaded
    // *** TODO: COMPLETAR ***
    if (img_patch.empty() && !use_video2)
    {
        std::cerr << "Error: could not open image ["
                  << patch_path << "]." << std::endl;
        return EXIT_FAILURE;
    }

    // Change resolution of the image model to half
    cv::resize(img_model, img_model, cv::Size(), 0.5, 0.5);

    // Resize the patch to the size of the model
    if (use_patch)
        cv::resize(img_patch, img_patch, img_model.size());

    // Create the video capture
    cv::VideoCapture cap(video_path);
    if (!cap.isOpened()) {
        cout << "Error: video not loaded: " + video_path << endl;
        return -1;
    }

    // If use video2, create the video capture
    cv::VideoCapture cap2;
    if (use_video2) {
        try{
            cap2.open(stoi(video2_path));//comprueba si es una webcam
        }
        catch(...){
            cap2.open(video2_path);//si no es una webcam abrira un video
        }
        
        if (!cap2.isOpened()) {
            cout << "Error: video not loaded: " + video2_path << endl;
            return -1;
        }
    }


    //preparo guardado si se desea guardar en video
    //inicializo fuera para evitar problemas de compilacion
    cv::VideoWriter outputVideo;
    if(save){
        cv::Size S = cv::Size((int) cap.get(cv::CAP_PROP_FRAME_WIDTH),
              (int) cap.get(cv::CAP_PROP_FRAME_HEIGHT));// Acquire input size
        /*cv::Size S = cv::Size((int) cap.get(cv::CAP_PROP_FRAME_WIDTH*0.5),// Acquire input size
              (int) cap.get(cv::CAP_PROP_FRAME_HEIGHT)*0.5);*/// Acquire input size
        int codec = static_cast<int>(cap.get(cv::CAP_PROP_FOURCC));// Acquire codec
        string filename = "Salida.avi";// name of the output video file
        //int fps = 5;
        int fps = cap.get(cv::CAP_PROP_FPS);// Acquire fps
        outputVideo.open(filename, codec, fps, S, true);

        if (!outputVideo.isOpened())
        {
            cout  << "Could not open the output video for write: " << video_path << endl;
            return -1;
        }
    }


    // Pre-compute keypoints and descriptors for the model image
    std::vector<cv::KeyPoint> keypoints_model;
    cv::Mat descriptors_model;
    rva_calculaKPsDesc(img_model, keypoints_model, descriptors_model, tipo_kp_float);

    // For each video frame, detect the object and overlay the patch
    cv::Mat img_scene;

    //Load camera calibration parameters.
        cv::Mat camera_matrix;
        cv::Mat dist_coeffs;
        cv::Mat rvec;
        cv::Mat tvec;
        vector<cv::Point3f> pt3d;
        vector<cv::Point2f> _2dpoints;
    //necesario crear las variables fuera del if para no tener errores de compilacion

    if (use_calibracion){//si se utiliza la calibracion
    
        cv::FileStorage fs(archivo_calibracion, cv::FileStorage::READ);//compruebo y leo los datos de calib del fichero
        if(! fs.isOpened())
        {
            std::cerr << "El archivo no se ha podido abrir" << std::endl;
            return EXIT_FAILURE;
        }

        fsiv_load_calibration_parameters(fs, camera_matrix, dist_coeffs, rvec, tvec);//cargo los parametros de calibracion de la camara

        //calculos las esquinas en 3d de mi patron
        if(ancho == 0 || largo == 0){
            cout << "Ni el ancho ni el largo puede ser 0" << endl;
            return -1;
        }else{
            pt3d = fsiv_generate_3d_calibration_points(ancho, largo);//calculo los puntos 3d del patron en el mundo real
        }
    }
    
    int n_captura = 0;//numero de la captura
    int key;//tecla pulsada

    while (cap.read(img_scene)) {//mientras tengamos imagenes en el video
        // To speed up processing, resize the image to half
        //cv::resize(img_scene, img_scene, cv::Size(),0.5,0.5);

        // Compute keypoints and descriptors for the scene image
        std::vector<cv::KeyPoint> keypoints_scene;
        cv::Mat descriptors_scene;
        rva_calculaKPsDesc(img_scene, keypoints_scene, descriptors_scene, tipo_kp_float);

        // Match the descriptors
        std::vector<cv::DMatch> matches;
        rva_matchDesc(descriptors_model, descriptors_scene, matches, tipo_kp_float);

        try{//para evitar casos en los que no se encuentren los keypoints

            // Compute the bounding-box of the model in the scene
            cv::Mat H;
            std::vector<cv::Point2f> pts_obj_in_scene;
            rva_localizaObj(img_model, img_scene, keypoints_model, keypoints_scene, matches, H, pts_obj_in_scene);

            if (use_calibracion){//si se utiliza la calibracion

                // Compute camera pose
                solvePnP(pt3d, pts_obj_in_scene, camera_matrix, dist_coeffs, rvec, tvec);//calculo la pose de la camara

                //saco los puntos 2d para los puntos 3d de mi patron, solo en el caso de la imagen para 3d
                _2dpoints.clear();
                //projectPoints(pt3d, rvec, tvec, camera_matrix, dist_coeffs, _2dpoints);*/
            }
            
            // Warp the patch to the object using OpenCV
            if (use_video2) { 
                cap2 >> img_patch;//si el video es más corto se quedara en color negro
                cv::resize(img_patch, img_patch, img_model.size());//ajusto el frame del video al tamaño del pattern          
            }

            if (!img_patch.empty())
            {
                if (use_calibracion){
                    //rva_dibujaPatch_con_calib(img_scene, img_patch, H, img_scene, _2dpoints);//imagen en 3d sobre la escena
                    rva_dibujaCasita_con_calib(img_scene, camera_matrix, dist_coeffs, rvec, tvec, _2dpoints);//casita en 3d sobre la escena

                }else{
                    rva_dibujaPatch_sin_calib(img_scene, img_patch, H, img_scene, pts_obj_in_scene);//imagen en 2d sobre la escena
                }
                
            }    

            // Draw the bounding-box        
            rva_draw_contour(img_scene, pts_obj_in_scene, cv::Scalar(0, 255, 0), 4);

        }catch(...)
        {
            cout<<"No hay matches, no se encuentra el objeto"<<endl;
        }

        //grabo pantalla
        if(save){
            outputVideo.write(img_scene);
        }

        // Show the result
        cv::imshow("AugmentedReality", img_scene);

        // Check pressed keys to take action
        key = cv::waitKey(1);

        if (key == 27 || key == 113){//q o esc para terminar el programa
            break; 
        }else if(key == 115){//s para realizar una captura de pantalla, se pueden hacer varias
            cout<<"Guardando captura..."<<endl;
            cv::imwrite("CapturaPantalla" + to_string(n_captura) + ".jpg", img_scene);
            n_captura++;
            cout<<n_captura<<endl;
        }
    }

    // The camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
