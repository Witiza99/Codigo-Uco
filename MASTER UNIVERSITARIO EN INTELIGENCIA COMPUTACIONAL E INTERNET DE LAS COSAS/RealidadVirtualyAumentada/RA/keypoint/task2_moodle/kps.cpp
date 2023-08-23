// This program reads a model image and a scene image, and computes and matches keypoints. Then, it draws the matches between the two images.

// (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

#include "rva.h"

using namespace std;

// Main function
int main(int argc, char ** argv) {

    // Get the arguments: model and scene images path using OpenCV
    cv::CommandLineParser parser(argc, argv, "{@model | ../data/modelbookocv3_01.jpg | input model image}{@scene | ../data/opencv3_scene.png | input scene image}");
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

    // Print the number of keypoints for the model and the scene
    cout << "Model keypoints: " << keypoints_model.size() << endl;
    cout << "Scene keypoints: " << keypoints_scene.size() << endl;

    // Match the descriptors
    std::vector<cv::DMatch> matches;
    rva_matchDesc(descriptors_model, descriptors_scene, matches);

    // Print the number of matches
    cout << "Matches: " << matches.size() << endl;

    // Draw the matches
    cv::Mat img_matches;
    rva_dibujaMatches(img_model, img_scene, keypoints_model, keypoints_scene, matches, img_matches);

    // Show the matches
    cv::imshow("Matches", img_matches);
    cv::waitKey(0);

    return 0;
}
