#pragma once
#include <opencv2/core.hpp>


/**
 * @brief Apply an unsharp mask enhance to the input image.
 * @arg[in] in is the input image.
 * @arg[in] g is the enhance's gain.
 * @arg[in] r is the window's radius.
 * @arg[in] filter_type specifies which filter to use. 0->Box, 1->Gaussian.
 * @arg[out] unsharp_mask if it is not nullptr, save the unsharp mask used.
 * @pre !in.empty() 
 * @pre g>=0.0
 * @pre r>0
 * @pre filter_type is {0, 1}
 * @post ret_v.rows==in.rows && ret_v.cols==in.cols
 * @post ret_v.type()==CV_32FC1
 */
cv::Mat fsiv_usm_enhance(cv::Mat  const& in, double g=1.0, int r=1,
                         int filter_type=0,
                         cv::Mat* unsharp_mask=nullptr);
