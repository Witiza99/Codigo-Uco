// This is the header file for the RVA functions
// (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#ifndef _RVA_H
#define _RVA_H

// Include some OpenCV headers
#include <opencv2/opencv.hpp>

cv::Mat rva_compute_homography(std::vector<cv::Point2f> points_image1, std::vector<cv::Point2f> points_image2);

void rva_draw_contour(cv::Mat image, std::vector<cv::Point2f> points, cv::Scalar color, int thickness);

void rva_deform_image(const cv::Mat& im_input, cv::Mat & im_output, cv::Mat homography);

// ======================
// Functions for task 2
// ======================

//! This function extract keypoint descriptors from an image
//! \param img: input image
//! \param keypoints: vector of keypoints
//! \param descriptors: matrix of descriptors
void rva_calculaKPsDesc(cv::Mat &img, std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors);

//! This function matches two sets of descriptors
//! \param descriptors1: matrix of descriptors of the first image
//! \param descriptors2: matrix of descriptors of the second image
//! \param matches: vector of matches

void rva_matchDesc(cv::Mat &descriptors1, cv::Mat &descriptors2, std::vector<cv::DMatch> &matches);

//! This function draws the matches between two images
//! \param img1: first image
//! \param img2: second image
//! \param keypoints1: vector of keypoints of the first image
//! \param keypoints2: vector of keypoints of the second image
//! \param matches: vector of matches
//! \param img_matches: output image with the matches

void rva_dibujaMatches(cv::Mat &img1, cv::Mat &img2, std::vector<cv::KeyPoint> &keypoints1, std::vector<cv::KeyPoint> &keypoints2, std::vector<cv::DMatch> &matches, cv::Mat &img_matches);


#endif