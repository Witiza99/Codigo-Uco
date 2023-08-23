// This program reads a model image and a scene image, and finds the bounding-box of the model in the scene

// (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

#include "rva.h"

using namespace std;

// Main function
int main(int argc, char ** argv) {

    // Get the arguments: model and scene images path using OpenCV
    cv::CommandLineParser parser(argc, argv, "{@model | ../data/patron.jpg | input model image}{@scene | ../data/escena_imagen.jpg | input scene image}");
    cv::String model_path = parser.get<cv::String>(0);
    cv::String scene_path = parser.get<cv::String>(1);

    // Load the images
    cv::Mat img_model = cv::imread(model_path, cv::IMREAD_GRAYSCALE);
    cv::Mat img_scene = cv::imread(scene_path, cv::IMREAD_GRAYSCALE);

    // Check if the images are loaded
    if (img_model.empty() || img_scene.empty()) {
        cout << "Error: images not loaded" << endl;
        return -1;
    }

    // Compute keypoints and descriptors for the model image
    std::vector<cv::KeyPoint> keypoints_model;
    cv::Mat descriptors_model;
    rva_calculaKPsDesc(img_model, keypoints_model, descriptors_model);

    // Compute keypoints and descriptors for the scene image
    std::vector<cv::KeyPoint> keypoints_scene;
    cv::Mat descriptors_scene;
    rva_calculaKPsDesc(img_scene, keypoints_scene, descriptors_scene);

    // Match the descriptors
    std::vector<cv::DMatch> matches;
    rva_matchDesc(descriptors_model, descriptors_scene, matches);

    // Compute the bounding-box of the model in the scene
    cv::Mat H;
    std::vector<cv::Point2f> pts_obj_in_scene;
    rva_localizaObj(img_model, img_scene, keypoints_model, keypoints_scene, matches, H, pts_obj_in_scene);

    // Draw the bounding-box on the color image    
    cv::Mat img_scene_col = cv::imread(scene_path, cv::IMREAD_COLOR);
    rva_draw_contour(img_scene_col, pts_obj_in_scene, cv::Scalar(0, 255, 0), 4);

    // Show the scene
    cv::imshow("Detected", img_scene_col);
    cv::waitKey(0);

    // Save the scene with the localized object
    //  *** TODO: COMPLETAR ***
    imwrite("Salida.png", img_scene_col);
    return 0;
}
