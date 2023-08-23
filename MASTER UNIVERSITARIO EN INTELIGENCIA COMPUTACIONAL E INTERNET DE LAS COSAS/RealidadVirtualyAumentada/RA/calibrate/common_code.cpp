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
        drawChessboardCorners(img2,board_size, cv::Mat(corner_points), was_found);

        if(wname == NULL){
            cv::namedWindow("image");
            cv::imshow("image", img2);
        }else{
            cv::namedWindow(wname);
            cv::imshow(wname, img2);
        }
        cv::waitKey(0);
    }
    //
    return was_found;
}

float
fsiv_calibrate_camera(const std::vector<std::vector<cv::Point2f>>& _2d_points,
                      const std::vector<std::vector<cv::Point3f>>& _3d_points,
                      const cv::Size &camera_size,
                      cv::Mat& camera_matrix,
                      cv::Mat& dist_coeffs,
                      std::vector<cv::Mat>* rvecs,
                      std::vector<cv::Mat>* tvecs)
{
    CV_Assert(_3d_points.size()>=2 && _3d_points.size()==_2d_points.size());
    float error=0.0;
    //TODO
    std::vector<cv::Mat> mrvecs;
    std::vector<cv::Mat> mtvecs;
    if (rvecs == nullptr || tvecs == nullptr){
        error = calibrateCamera(_3d_points, _2d_points, camera_size, camera_matrix,dist_coeffs, mrvecs, mtvecs);
    }else{
        error = calibrateCamera(_3d_points, _2d_points, camera_size, camera_matrix,dist_coeffs, *rvecs, *tvecs);
    }

    //cv::CALIB_FIX_PRINCIPAL_POINT + cv::CALIB_FIX_ASPECT_RATIO + cv::CALIB_ZERO_TANGENT_DIST,
    //cv::TermCriteria(cv::TermCriteria::MAX_ITER|cv::TermCriteria::EPS, 30, 2.22e-16));

    if(rvecs != nullptr ){
        //bucle for donde se haga un copyTo a cada matriz
        rvecs->reserve(mrvecs.size());  
        for(int i = 0; i< mrvecs.size();i++){
            mrvecs[i].copyTo(rvecs[i]); 
        }
    }
    if(tvecs != nullptr ){
        tvecs->reserve(mtvecs.size());
        for(int i = 0; i< mtvecs.size();i++){
            mtvecs[i].copyTo(tvecs[i]);
        }
    }

    //
    CV_Assert(camera_matrix.rows==camera_matrix.cols &&
              camera_matrix.rows == 3 &&
              camera_matrix.type()==CV_64FC1);
    CV_Assert((dist_coeffs.rows*dist_coeffs.cols) == 5 &&
              dist_coeffs.type()==CV_64FC1);
    CV_Assert(rvecs==nullptr || rvecs->size()==_2d_points.size());
    CV_Assert(tvecs==nullptr || tvecs->size()==_2d_points.size());
    return error;
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

    //
}

void
fsiv_save_calibration_parameters(cv::FileStorage& fs,
                                const cv::Size & camera_size,
                                float error,
                                const cv::Mat& camera_matrix,
                                const cv::Mat& dist_coeffs,
                                 const cv::Mat& rvec,
                                 const cv::Mat& tvec)
{
    CV_Assert(fs.isOpened());
    CV_Assert(camera_matrix.type()==CV_64FC1 && camera_matrix.rows==3 && camera_matrix.cols==3);
    CV_Assert(dist_coeffs.type()==CV_64FC1 && dist_coeffs.rows==1 && dist_coeffs.cols==5);
    CV_Assert(rvec.type()==CV_64FC1 && rvec.rows==3 && rvec.cols==1);
    CV_Assert(tvec.type()==CV_64FC1 && tvec.rows==3 && tvec.cols==1);
    //TODO
    fs << "image-width" << camera_size.width ;
    fs << "image-height" << camera_size.height;
    fs << "error" << error;
    fs << "camera-matrix" << camera_matrix;
    fs << "distortion-coefficients" << dist_coeffs;
    fs << "rvec" << rvec;
    fs << "tvec" << tvec;

    //
    CV_Assert(fs.isOpened());
    return;
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
fsiv_undistort_image(const cv::Mat& input, cv::Mat& output,
                     const cv::Mat& camera_matrix,
                     const cv::Mat& dist_coeffs)
{
    //TODO
    //Hint: use cv::undistort.
    output = input.clone();
    undistort(input, output, camera_matrix, dist_coeffs);//corrigo distorsion radial
    //
}

void
fsiv_undistort_video_stream(cv::VideoCapture&input_stream,
                            cv::VideoWriter& output_stream,
                            const cv::Mat& camera_matrix,
                            const cv::Mat& dist_coeffs,
                            const int interp,
                            const char * input_wname,
                            const char * output_wname,
                            double fps)
{
    CV_Assert(input_stream.isOpened());
    CV_Assert(output_stream.isOpened());
    //TODO
    //Hint: to speed up, first compute the transformation maps
    //(one time only at the beginning using cv::initUndistortRectifyMap)
    // and then only remap (cv::remap) the input frame with the computed maps.
    //create source matrix

    cv::namedWindow("input_wname");
    cv::namedWindow("output_wname");

    cv::Mat frame, dest_image, map1, map2;

    input_stream >> frame;
    int key = 0;

      
    while (!frame.empty() && key !=27){
        cv::initUndistortRectifyMap(camera_matrix, dist_coeffs, cv::Mat(), camera_matrix, frame.size(), CV_32FC1, map1, map2);
        //create undistorted image
        cv::remap(frame, dest_image, map1, map2, cv::INTER_LINEAR);

        imshow("input_wname", frame);
        imshow("output_wname", dest_image);

        key = cv::waitKey(20) & 0xff;
        input_stream >> frame; 
    }

    //
    CV_Assert(input_stream.isOpened());
    CV_Assert(output_stream.isOpened());
}
