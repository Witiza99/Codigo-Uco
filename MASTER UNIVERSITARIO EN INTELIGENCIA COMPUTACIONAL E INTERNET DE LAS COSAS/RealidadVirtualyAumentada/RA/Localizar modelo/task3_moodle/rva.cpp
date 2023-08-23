// (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#include <iostream>
#include <opencv2/opencv.hpp>

#include "rva.h"


// TASK 1
cv::Mat rva_compute_homography(std::vector<cv::Point2f> points_image1, std::vector<cv::Point2f> points_image2){
	return cv::findHomography(points_image1, points_image2,cv::RANSAC);//usar cv::RANSAC
}

void rva_draw_contour(cv::Mat image, std::vector<cv::Point2f> points, cv::Scalar color, int thickness){
	cv::line(image, points[0], points[1], color, thickness);//se puede hacer con un bucle for
	cv::line(image, points[1], points[2], color, thickness);
	cv::line(image, points[2], points[3], color, thickness);
	cv::line(image, points[3], points[0], color, thickness);
}

void rva_deform_image(const cv::Mat& im_input, cv::Mat & im_output, cv::Mat homography){
	cv::warpPerspective(im_input, im_output, homography, cv::Size(im_output.cols,im_output.rows));
}



// TASK 2
void rva_calculaKPsDesc(cv::Mat &img, std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors)
{
    auto Detector=cv::AKAZE::create(cv::AKAZE::DESCRIPTOR_MLDB,  0,  3, 1e-4f,8 );
    Detector ->detectAndCompute(img, cv::Mat(), keypoints, descriptors);
}

void rva_matchDesc(cv::Mat &descriptors1, cv::Mat &descriptors2, std::vector<cv::DMatch> &matches)
{
    auto matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
    matcher ->match(descriptors1, descriptors2, matches);

    //si se quieren aplicar filtros debe ser aqui
}

void rva_dibujaMatches(cv::Mat &img1, cv::Mat &img2, std::vector<cv::KeyPoint> &keypoints1, std::vector<cv::KeyPoint> &keypoints2, std::vector<cv::DMatch> &matches, cv::Mat &img_matches)
{
    cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
}


// TASK 3
void rva_localizaObj(const cv::Mat &img1, const cv::Mat &img2, const std::vector<cv::KeyPoint> &keypoints1, const std::vector<cv::KeyPoint> &keypoints2, const std::vector<cv::DMatch> &matches, cv::Mat &homography, std::vector<cv::Point2f> &pts_im2)
{

	//-- Para hacer la homografia necesitamos pasarle a la funcion los matches encontrados(los keypoint)
    std::vector<cv::Point2f> obj;
    std::vector<cv::Point2f> scene;
    for( size_t i = 0; i < matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints1[ matches[i].queryIdx ].pt );
        scene.push_back( keypoints2[ matches[i].trainIdx ].pt );
    }

	homography = rva_compute_homography(obj, scene);

	//Guardamos las coordenadas de las esquinas de la imagen patron
    std::vector<cv::Point2f> patron_corners(4);
    patron_corners[0] = cv::Point2f(0, 0);
    patron_corners[1] = cv::Point2f( (float)img1.cols, 0 );
    patron_corners[2] = cv::Point2f( (float)img1.cols, (float)img1.rows );
    patron_corners[3] = cv::Point2f( 0, (float)img1.rows );

	//
    perspectiveTransform(patron_corners, pts_im2, homography);
}