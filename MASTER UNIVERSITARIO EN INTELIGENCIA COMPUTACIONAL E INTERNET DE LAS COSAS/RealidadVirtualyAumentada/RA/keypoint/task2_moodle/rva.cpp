// (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#include <iostream>
#include <opencv2/opencv.hpp>

#include "rva.h"


void rva_calculaKPsDesc(cv::Mat &img, std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors)
{
    auto Detector=cv::AKAZE::create(cv::AKAZE::DESCRIPTOR_MLDB,  0,  3, 1e-4f,8 );
    Detector ->detectAndCompute(img, cv::Mat(), keypoints, descriptors);
}

void rva_matchDesc(cv::Mat &descriptors1, cv::Mat &descriptors2, std::vector<cv::DMatch> &matches)
{
    auto matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
    matcher ->match(descriptors1, descriptors2, matches);
    
}

void rva_dibujaMatches(cv::Mat &img1, cv::Mat &img2, std::vector<cv::KeyPoint> &keypoints1, std::vector<cv::KeyPoint> &keypoints2, std::vector<cv::DMatch> &matches, cv::Mat &img_matches)
{
    cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
}
