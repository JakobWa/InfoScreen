#include <iostream>
#include <opencv2/opencv.hpp>
#include "DisplayImage.hpp"
#include "ImageObject.hpp"
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;

#define DATAPATH "./data/"


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

    std::vector<std::string> datanames = getFiles(DATAPATH);

    
        


    
    return 0;
}

std::vector<std::string> getFiles(std::string apath){
    std::vector<std::string> files;
    std::string path = apath;
    for (const auto & entry : fs::directory_iterator(path))
        files.push_back(entry.path());
    return files;
}

std::vector<ImageObject> assignObject(std::vector<std::string> names){
    std::vector<ImageObject> objects;
    std::string tmpname;
    for(auto i : names){
        if(i.find(".txt")){
            tmpname = i;
            tmpname.erase(tmpname.end() - 4, tmpname.end());
            for(auto j : names){
                if (j.find(tmpname) && !j.find(".txt")){
                    ImageObject it{imgtxt, i, j};
                    objects.push_back(it);
                    delete &it;
                }
                if (!(j.find(tmpname) && !j.find(".txt"))){
                    ImageObject jt{txt, i};
                    objects.push_back(jt);
                    delete &jt;
                }
            }
        }
        if(!i.find(".txt")){
            
        }

    }
}
