// This is the header file for the RVA functions
// (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#ifndef _RVA_H
#define _RVA_H

// Include some OpenCV headers
#include <opencv2/opencv.hpp>

cv::Mat rva_compute_homography(std::vector<cv::Point2f> points_image1, std::vector<cv::Point2f> points_image2);

void rva_draw_contour(cv::Mat image, std::vector<cv::Point2f> points, cv::Scalar color, int thickness);

void rva_deform_image(const cv::Mat& im_input, cv::Mat & im_output, cv::Mat homography);


#endif