#include "common_code.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat fsiv_color_rescaling(const cv::Mat& in, const cv::Scalar& from, const cv::Scalar& to)
{
    CV_Assert(in.type()==CV_8UC3);
    cv::Mat out;
    //TODO
    //Cuidado con dividir por cero.
    //Evita los bucles.
    out = in.clone();
    
    if (from[0] != 0 && from[1] != 0 && from[2] != 0){//repasar esta parte

        double v1 = to[0]/from[0];
        double v2 = to[1]/from[1];
        double v3 = to[2]/from[2];
        multiply(in, cv::Scalar(v1,v2,v3), out);

    }else{
        std::cout<<"Division entre 0, no se puede continuar con el programa"<<std::endl;
        exit(0);
    }

    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    return out;
}

cv::Mat fsiv_wp_color_balance(cv::Mat const& in)
{
    CV_Assert(in.type()==CV_8UC3);
    cv::Mat out, tmp;
    //TODO
    //Sugerencia: utiliza el espacio de color GRAY para
    //saber la ilumimancia de un pixel.
//convertir imagne
    //ver punto mas brillante

    //llamar a la funcion que convierte la matriz
    cvtColor(in, tmp, cv::COLOR_BGR2GRAY);


    /*Código para indicar valor max y min de la imagen dada, para canal y de dos formas distintas*/
    double max;
    double min;
    cv::Point minID;
    cv::Point maxID;
    cv::minMaxLoc(tmp,&min,&max,&minID,&maxID);
    //std::cout<<"El valor máximo es: "<<maxID<<std::endl;

    double v1 = in.at<cv::Vec3b>(maxID.y, maxID.x)[0];
    double v2 = in.at<cv::Vec3b>(maxID.y, maxID.x)[1];
    double v3 = in.at<cv::Vec3b>(maxID.y, maxID.x)[2];


    cv::Scalar from(v1,v2,v3);
    cv::Scalar to(255,255,255);

    //llamar a la funcion que convierte la matriz
    //cvtColor(out, out, cv::COLOR_GRAY2BGR);

    out = fsiv_color_rescaling(in,from,to);

    

    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    return out;
}

cv::Mat fsiv_gw_color_balance(cv::Mat const& in)
{
    CV_Assert(in.type()==CV_8UC3);
    cv::Mat out,tmp;
    //TODO
//transformo a gris
    //aplico la media con su funcio
    //realizo la conversion

    //llamar a la funcion que convierte la matriz

    cv::Scalar to(128,128,128);

    out = fsiv_color_rescaling(in,cv::mean(in),to);

    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    return out;
}

cv::Mat fsiv_color_balance(cv::Mat const& in, float p)
{
    CV_Assert(in.type()==CV_8UC3);
    CV_Assert(0.0f<p && p<100.0f);
    cv::Mat out;
    //TODO
    //Sugerencia: utiliza el espacio de color GRAY para
    //saber la ilumimancia de un pixel.

    //llamo a los distintos metodos dependiendo de p
    


    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    return out;
}
