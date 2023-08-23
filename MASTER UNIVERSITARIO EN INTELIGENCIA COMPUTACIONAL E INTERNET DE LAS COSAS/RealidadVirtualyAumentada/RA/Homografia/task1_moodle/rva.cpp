// (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#include <iostream>
#include <opencv2/opencv.hpp>

#include "rva.h"

// CREA TUS FUNCIONES AQUI

cv::Mat rva_compute_homography(std::vector<cv::Point2f> points_image1, std::vector<cv::Point2f> points_image2){
	return cv::findHomography(points_image1, points_image2);
}

void rva_draw_contour(cv::Mat image, std::vector<cv::Point2f> points, cv::Scalar color, int thickness){
	cv::line(image, points[0], points[1], color, thickness);
	cv::line(image, points[1], points[2], color, thickness);
	cv::line(image, points[2], points[3], color, thickness);
	cv::line(image, points[3], points[0], color, thickness);
}

void rva_deform_image(const cv::Mat& im_input, cv::Mat & im_output, cv::Mat homography){
	cv::warpPerspective(im_input, im_output, homography, cv::Size(im_output.cols,im_output.rows));
}