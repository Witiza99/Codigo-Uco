// This program creates a sample homograpy matrix and apply it to an image
// (c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

#include "rva.h"

using namespace std;

// This is a global variable to store the 4 points
std::vector<cv::Point2f> points;

// This function is mouse callback to collect the 4 points
void mouse_callback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {

        // Gather the im_input from userdata
        cv::Mat im_input = *(cv::Mat*)userdata;

        // Control if there are less than 4 points
        if (points.size() >= 4) {
            return;
        }

        // Add the point to the vector
        points.push_back(cv::Point2f(x, y));
        std::cout << "Point " << points.size() << ": " << x << ", " << y << std::endl;

        // Draw a circle at the current point
        // *** COMPLETAR ***
        cv::circle(im_input, points.back(), 5, cv::Scalar(0, 255, 0), 2);

        // Display the input image
        cv::imshow("Input Image", im_input);
    }
}

int main(int argc, char** argv)
{
    // Read the input image path from the command line using Opencv 
    cv::CommandLineParser parser(argc, argv, "{@input | ../data/opencv3_scene.png | input image}");
    cout<<parser.get<cv::String>("@input")<<endl;;
    cv::Mat im_input = cv::imread(parser.get<cv::String>("@input"), cv::IMREAD_COLOR);
    if (im_input.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // Resize the input image if is greater than 1024x768, keep the aspect ratio
    if (im_input.cols > 1024 || im_input.rows > 768) {
        float scale = std::min(1024.0f / im_input.cols, 768.0f / im_input.rows);
        cv::resize(im_input, im_input, cv::Size(), scale, scale);
    }

    // Open a window to display the input image
    cv::namedWindow("Input Image", cv::WINDOW_AUTOSIZE);

    // Set the mouse callback to collect the 4 points, pass the im_input to the callback
    cv::setMouseCallback("Input Image", mouse_callback, &im_input);
    
    // Display the input image
    cv::imshow("Input Image", im_input);

    // Wait until the user presses the ESC key
    while (cv::waitKey(0) != 27) {
        if (points.size() >= 4) {
            break;
        }
    }
    
    // Draw the contour on the input image
    rva_draw_contour(im_input, points, cv::Scalar(0, 255, 0), 2);

    // Display the input image
    cv::imshow("Input Image", im_input);

    // Wait until the user presses any key
    cv::waitKey(0);

    // Create the output image with size 480x640
    cv::Mat im_output(640, 480, CV_8UC3);

    // Compute the homography to warp the image
    std::vector<cv::Point2f> points_dst = std::vector<cv::Point2f>{
        cv::Point2f(0, 0),
        cv::Point2f(im_output.cols - 1, 0),
        cv::Point2f(im_output.cols - 1, im_output.rows - 1),
        cv::Point2f(0, im_output.rows - 1)
    };
    cv::Mat homography = rva_compute_homography(points, points_dst);
    
    // Deform the image
    rva_deform_image(im_input, im_output, homography);

    // Display the output image
    cv::imshow("Output Image", im_output);

    // Wait until the user presses any key
    cv::waitKey(0);

    // Save the output image to disk
    // *** COMPLETAR ***
    imwrite("Salida.png", im_output);

    return 0;
}