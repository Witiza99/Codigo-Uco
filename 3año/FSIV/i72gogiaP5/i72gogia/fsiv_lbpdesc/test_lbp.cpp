//! \file test_lbp.cpp
//! \author FSIV-UCO

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "lbp.h"

using namespace std;

const cv::String keys =
    "{help h usage ? |      | print this message.}"
//    "{u uniform      |      | use uLBP.}"
//    "{c colunms      |0     | Build descriptor using a grid with c colums.}"
//    "{r rows         |0     | Build descriptor using a grid with r rows.}"
    "{@image1        |<none>| path to input image.}"
    "{@image2        |      | path to second image, for comparison.}"
    ;

int main(int argc, char * argv[])
{
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Test LBP implementation.");
	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}
	cv::String img_name = parser.get<cv::String>(0);
	cv::String img_name2 = parser.get<cv::String>(1);

	if (!parser.check()){
		parser.printErrors();
		return 0;
	}

	// TODO Load the image1
	cv::Mat image1 = cv::imread(img_name, cv::IMREAD_COLOR);
	if (image1.empty())
	{
		std::cerr << "Error: no he podido abrir el fichero '" << img_name << "'." << std::endl;
		return EXIT_FAILURE;
	}


	// TODO Load the image2 (if it is set).
	cv::Mat image2;
	if(!img_name2.empty()){
		image2 = cv::imread(img_name2, cv::IMREAD_COLOR);
		if (image2.empty())
		{
			std::cerr << "Error: no he podido abrir el fichero '" << img_name2 << "'." << std::endl;
			return EXIT_FAILURE;
		}
	}else{
		// TODO if image2 is not set, image2 = mirror(image1) (x axe). see cv::flip()
		cv::flip(image1, image2, 1);
	}

	//  TODO Compute LBP matrixs
	cv::Mat lbp1;
	cv::Mat lbp2;
	cv::Mat aux1;
	cv::Mat aux2;
	cvtColor(image1, aux1, cv::COLOR_BGR2GRAY);
	cvtColor(image2, aux2, cv::COLOR_BGR2GRAY);

	fsiv_lbp(aux1, lbp1);
	fsiv_lbp(aux2, lbp2);

	// TODO Display LBP images
	fsiv_lbp_disp(lbp1, "imagen1");
	fsiv_lbp_disp(lbp2, "imagen2");

	// TODO Compute the LBP histograms.
	cv::Mat lbp_h1, lbp_h2;
	fsiv_lbp_hist(lbp1, lbp_h1);
	fsiv_lbp_hist(lbp2, lbp_h2);

	// TODO Compute the Chi^2 distance between the input image1 and image2, if it is set,
	/// or else between image1 and its mirror.
	float dist = fsiv_chisquared_dist(lbp_h1, lbp_h2);

	std::cerr << "Distance between image1, image2 = " << dist << std::endl;   
	std::cout << "End! " <<std::endl;

	return 0;
}
