#include <iostream>
#include <opencv2/opencv.hpp>
#include "DisplayImage.hpp"
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;

#define DATAPATH "./data/"

std::vector<std::string> removeJustTxt(std::vector<std::string> files);

int main(int argc, char** argv ){
    /*if ( argc != 2 )
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

    waitKey(0);*/

    std::vector<std::string> datanames = getFiles();
    datanames = removeJustTxt(datanames);

    for(auto i : datanames) 
        std::cout << i << std::endl;
    
    return 0;
}

std::vector<std::string> getFiles(){
    std::vector<std::string> files;
    std::string path = DATAPATH;
    for (const auto & entry : fs::directory_iterator(path))
        files.push_back(entry.path());
    return files;
}

std::vector<std::string> removeJustTxt(std::vector<std::string> files){
    std::vector<std::string> newfiles;
    std::string tmpFN;
    for (auto i : files){
        if (i.find(".txt")== !std::string::npos){
            tmpFN = i;
            tmpFN.erase((i.size() - 5), std::string::npos);
            std::cout << std::endl << tmpFN << std::endl;
            tmpFN.append(".jpeg");
            for(auto j : files){
                if (!j.compare(tmpFN))
                {
                    goto RTEXIT;                                            //I know, shut up!
                }
            }
            break;
        }
        RTEXIT:
        newfiles.push_back(i);        
    }
    return newfiles;
}
