#include <opencv2/imgproc.hpp>
#include "common_code.hpp"
#include <iostream>

cv::Mat
fsiv_usm_enhance(cv::Mat  const& in, double g, int r,
                 int filter_type, cv::Mat *unsharp_mask)
{
    CV_Assert(!in.empty());
    CV_Assert(in.type()==CV_32FC1);
    CV_Assert(r>0);
    CV_Assert(filter_type>=0 && filter_type<=1);
    CV_Assert(g>=0.0);
    cv::Mat out = in.clone();
    //TODO
    //Hint: use your cv::blur or cv::GaussianBlur.
    //Remenber: filter size = 2*r +1.
    cv::Mat aux;
    if(filter_type==0){
        blur(in, aux, cv::Size(2*r +1,2*r +1));
    }else if(filter_type==1){
        GaussianBlur(in, aux, cv::Size(2*r +1, 2*r +1), 0);
    }else{
        std::cout<<"Mascara incorrecta"<<std::endl;
    }

    if(unsharp_mask != nullptr){
        aux.copyTo(*unsharp_mask);
    }

//    for(int i=0;i<in.rows;i++){//columnas
//        for(int j=0;j<in.cols;j++){//filas
//            out.at<float>(i,j) = (g+1)*in.at<float>(i,j)-g*aux->at<float>(i,j);
//        }
//    }
    out = (g+1)*in-g*aux;


    //
    CV_Assert(out.size()==in.size());
    CV_Assert(out.type()==in.type());
    return out;
}
