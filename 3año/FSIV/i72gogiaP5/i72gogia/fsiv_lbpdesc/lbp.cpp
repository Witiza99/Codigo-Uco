//! \file lbp.cpp
//! Utils for LBP

#include "lbp.h"
#include <vector>
#include <iostream>

using namespace std;

static const int uniform[256] =
{   
0,1,2,3,4,58,5,6,7,58,58,58,8,58,9,10,11,58,58,58,58,58,58,58,12,58,58,58,13,58,
14,15,16,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,17,58,58,58,58,58,58,58,18,
58,58,58,19,58,20,21,22,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,58,58,58,58,58,58,58,58,58,58,58,23,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,58,24,58,58,58,58,58,58,58,25,58,58,58,26,58,27,28,29,30,58,31,58,58,58,32,58,
58,58,58,58,58,58,33,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,34,58,58,58,58,
58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,35,36,37,58,38,58,58,58,39,58,58,58,58,58,58,58,40,58,58,58,58,58,58,58,58,58,
58,58,58,58,58,58,41,42,43,58,44,58,58,58,45,58,58,58,58,58,58,58,46,47,48,58,49,
58,58,58,50,51,52,58,53,54,55,56,57
};


void fsiv_lbp(const cv::Mat & imagem, cv::Mat & lbp)
{
    lbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);
	//TODO compute lbp codes.

	vector<int> auxiliar;
	auxiliar.resize(8);

	//primeros dos for para recorrer todos los elementos de la matriz
	for(int i=0;i < lbp.rows-1;i++){
		for(int j=0;j < lbp.cols-1; j++){
			auxiliar.clear();
			int max=imagem.at<uchar>(i,j);
			//doble for para ver los vecinos de mi anclaje
			for(int x=-1;x<2;x++){
				for(int y=-1;y<2;y++){
					if(!((x==0)&&(y==0))){
						if((x+i<0)||(x+i>lbp.rows-1)||(y+j<0)||(y+j>lbp.cols-1)){
							auxiliar.push_back(0);
						}else{
							if(imagem.at<uchar>(i+x,j+y)>=max){
								auxiliar.push_back(1);
							}else{
								auxiliar.push_back(0);
							}
						}
					}
				}
			}
			int resultado = 0;
			for(int w=0; w < auxiliar.size(); w++){
				if(auxiliar[w]==1){
					resultado=resultado+pow(2,w);
				}
			}
			lbp.at<uchar>(i,j)=resultado;
		}
	}
}

void fsiv_ulbp(const cv::Mat & imagem, cv::Mat & ulbp)
{
    ulbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);
	//TODO compute u-LBP codes.
}

void fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, bool normalize, int nbins)
{	    
	 lbp_hist == cv::Mat::zeros(1, nbins, CV_32FC1);
    //TODO compute lbp hist. \see cv::calcHist. Establish the number of bins
    float range[] = { 0, 256 };
    const float* ranges[] = {range};
	cv::calcHist( &lbp, 1, 0, cv::Mat(),lbp_hist, 1, &nbins, ranges);

    // Normalize?
    if (normalize)
    {
    	cv::normalize(lbp_hist, lbp_hist, 0, 1, cv::NORM_MINMAX);
    }
}

void fsiv_lbp_desc(const cv::Mat & image, cv::Mat & lbp_desc, const int *ncells, bool normalize, int nbins)
{
	//TODO compute lbp desc.
    if (normalize)
    {
		//TODO normaliza lbp_desc to mett cv::sum(lbp_desc)[0] == 1.0
		;
    }
}

void fsiv_lbp_disp(const cv::Mat & lbpmat, const std::string & winname)
{
	cv::namedWindow(winname);
	cv::imshow(winname, lbpmat);
	cv::waitKey(0) & 0xff;
}

float fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2)
{
	 float dist= 0.0;
	//TODO compute chi^2 distance. do not assume 256 bins allways!!
	 float suma= 0.0;
	 float var1, var2;

	 for(int j=0;j<h1.cols;j++){
	 	var1=pow(h1.at<float>(0,j)-h2.at<float>(0,j),2);
	 	var2=h1.at<float>(0,j)+h2.at<float>(0,j);
	 	if(var2==0){var2=1;}
	 	suma=suma+(var1/var2);
	 }
	 dist=suma*0.5;

    return dist;
}

