#include <iostream>
#include <opencv2/opencv.hpp>
#include "DisplayImage.hpp"
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;

#define DATAPATH "./data/"

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cout << "usage: DisplayImage.out <tetst.jpeg>\n";
        return -1;
    }
    Mat image;
    image = imread( argv[1], IMREAD_COLOR );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    std::string path = DATAPATH;
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;

    waitKey(0);
    return 0;
}

std::vector<std::string> verify(){






}