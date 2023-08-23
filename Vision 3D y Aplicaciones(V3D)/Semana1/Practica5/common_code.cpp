#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include "common_code.hpp"

#include <iostream>
std::vector<cv::Point3f>
fsiv_generate_3d_calibration_points(const cv::Size& board_size,
                                    float square_size)
{
    std::vector<cv::Point3f> ret_v;
    //TODO
    //Remenber: the first inner point has (1,1) in board coordinates.
    for( int i = 1; i < board_size.height+1; i++ )
        for( int j = 1; j < board_size.width+1; j++ )
            ret_v.push_back(cv::Point3f(float(j*square_size), float(i*square_size), 0)); 

    //
    CV_Assert(ret_v.size()==static_cast<size_t>(board_size.width*board_size.height));
    return ret_v;
}



bool
fsiv_find_chessboard_corners(const cv::Mat& img, const cv::Size &board_size,
                             std::vector<cv::Point2f>& corner_points,
                             const char * wname)
{
    CV_Assert(img.type()==CV_8UC3);
    bool was_found = false;
    //TODO
    cv::Mat imgGray;
    cv::Mat img2 = img.clone();
    cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    was_found = findChessboardCorners(imgGray,board_size,corner_points, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);
    
    if(was_found){
        cornerSubPix(imgGray, corner_points, cv::Size(5, 5), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 40, 0.001 ));
        /*drawChessboardCorners(img2,board_size, cv::Mat(corner_points), was_found);

        if(wname == NULL){
            cv::namedWindow("image");
            cv::imshow("image", img2);
        }else{
            cv::namedWindow(wname);
            cv::imshow(wname, img2);
        }
        cv::waitKey(0);*/
    }
    //
    return was_found;
}

void fsiv_compute_camera_pose(const std::vector<cv::Point3f> &_3dpoints,
                              const std::vector<cv::Point2f> &_2dpoints,
                              const cv::Mat& camera_matrix,
                              const cv::Mat& dist_coeffs,
                              cv::Mat& rvec,
                              cv::Mat& tvec)
{
    CV_Assert(_3dpoints.size()>=4 && _3dpoints.size()==_2dpoints.size());
    //TODO
    solvePnP(_3dpoints,_2dpoints,camera_matrix,dist_coeffs,rvec,tvec); 
    //
    CV_Assert(rvec.rows==3 && rvec.cols==1 && rvec.type()==CV_64FC1);
    CV_Assert(tvec.rows==3 && tvec.cols==1 && tvec.type()==CV_64FC1);
    return;
}

void
fsiv_draw_axes(cv::Mat& img,
               const cv::Mat& camera_matrix, const cv::Mat& dist_coeffs,
               const cv::Mat& rvec, const cv::Mat& tvec,
               const float size, const int line_width)
{
    //TODO
    std::vector<cv::Point2f> img_points;
    std::vector<cv::Point3f> ejes;
    ejes.push_back(cv::Point3f(0,0,0));
    ejes.push_back(cv::Point3f(size,0,0));
    ejes.push_back(cv::Point3f(0,size,0));
    ejes.push_back(cv::Point3f(0,0,-(size)));

    projectPoints(ejes, rvec, tvec, camera_matrix, dist_coeffs, img_points);

    //coordenadas
    cv::line(img, img_points[0], img_points[1], cv::Scalar(0,0,255), line_width);
    cv::line(img, img_points[0], img_points[2], cv::Scalar(0,255,0), line_width);
    cv::line(img, img_points[0], img_points[3], cv::Scalar(255,0,0), line_width);
    return;
    //
}

void
fsiv_load_calibration_parameters(cv::FileStorage &fs,
                                 cv::Size &camera_size,
                                 float& error,
                                 cv::Mat& camera_matrix,
                                 cv::Mat& dist_coeffs,
                                 cv::Mat& rvec,
                                 cv::Mat& tvec)
{
    CV_Assert(fs.isOpened());
    //TODO
    int width, height;
    fs["image-width"] >> width;
    fs["image-height"] >> height;
    camera_size = cv::Size(width,height);
    fs["error"] >> error;
    fs["camera-matrix"] >> camera_matrix;
    fs["distortion-coefficients"] >> dist_coeffs;
    fs["rvec"] >> rvec;
    fs["tvec"] >> tvec;

    //
    CV_Assert(fs.isOpened());
    CV_Assert(camera_matrix.type()==CV_64FC1 && camera_matrix.rows==3 && camera_matrix.cols==3);
    CV_Assert(dist_coeffs.type()==CV_64FC1 && dist_coeffs.rows==1 && dist_coeffs.cols==5);
    CV_Assert(rvec.type()==CV_64FC1 && rvec.rows==3 && rvec.cols==1);
    CV_Assert(tvec.type()==CV_64FC1 && tvec.rows==3 && tvec.cols==1);
    return;
}

void
fsiv_draw_3d_model(cv::Mat &img, const cv::Mat& camera_matrix, const cv::Mat& dist_coeffs,
                   const cv::Mat& rvec, const cv::Mat& tvec,
                   const float size)
{
    //TODO
    std::vector<cv::Point2f> img_points;
    std::vector<cv::Point3f> ejes;
    ejes.push_back(cv::Point3f(0,0,0));
    ejes.push_back(cv::Point3f(size,0,0));
    ejes.push_back(cv::Point3f(0,size,0));
    ejes.push_back(cv::Point3f(size,size,0));
    ejes.push_back(cv::Point3f((size/2),(size/2),-(size)));

    projectPoints(ejes, rvec, tvec, camera_matrix, dist_coeffs, img_points);

    //coordenadas
    cv::line(img, img_points[0], img_points[1], cv::Scalar(255,128,0), 2);
    cv::line(img, img_points[0], img_points[2], cv::Scalar(255,128,0), 2);
    cv::line(img, img_points[1], img_points[3], cv::Scalar(255,128,0), 2);
    cv::line(img, img_points[2], img_points[3], cv::Scalar(255,128,0), 2);

    cv::line(img, img_points[0], img_points[4], cv::Scalar(255,128,0), 2);
    cv::line(img, img_points[1], img_points[4], cv::Scalar(255,128,0), 2);
    cv::line(img, img_points[2], img_points[4], cv::Scalar(255,128,0), 2);
    cv::line(img, img_points[3], img_points[4], cv::Scalar(255,128,0), 2);

    return;
}

void
fsiv_project_image(const cv::Mat& input, cv::Mat& output,
                   const cv::Size& board_size,
                   const std::vector<cv::Point2f>& _2dpoints)
{
    CV_Assert(!input.empty() && input.type()==CV_8UC3);
    CV_Assert(!output.empty() && output.type()==CV_8UC3);
    //CV_Assert(board_size.area()==_2dpoints.size());
    //TODO
    cv::Mat matriz_trans;
    cv::Mat aux;
    //puntos de la imagen a introducir
    std::vector<cv::Point2f> dst_p;
    dst_p.clear();
    dst_p.push_back(cv::Point2f(0, 0));
    dst_p.push_back(cv::Point2f(0, input.rows));
    dst_p.push_back(cv::Point2f(input.cols, input.rows));
    dst_p.push_back(cv::Point2f(input.cols, 0));

    matriz_trans=cv::getPerspectiveTransform(dst_p, _2dpoints);
    cv::warpPerspective(input, aux, matriz_trans, cv::Size(output.cols,output.rows));
    std::vector<cv::Point> img_points_int;
    for(int i = 0; i < _2dpoints.size(); i++){
        img_points_int.push_back(cv::Point((int)_2dpoints[i].x,(int)_2dpoints[i].y)); 
    }
    cv::fillConvexPoly(output,img_points_int,cv::Scalar(0,0,0));
    output=output|aux;
    return;
    //
}
