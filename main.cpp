#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <filesystem>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <thread>

#include "main.hpp"
#include "ImageObject.hpp"
#include "settings.h"

#define US 1000000

namespace fs = std::filesystem;
using namespace cv;
using std::vector, std::string, std::cout, std::thread;

int main(int argc, char** argv ){
    while(1){
        vector<string> datanames = getFiles(DATAPATH);
        vector<ImageObject> DpObjects;
        DpObjects = assignObject(datanames);

        for(auto i : DpObjects){
            displayImage(i);
            thread t1(waitKey, 0);
            t1.join();
        }
    }
    return 0;
}

vector<string> getFiles(string apath){
    vector<string> files;
    string path = apath;
    for (const auto & entry : fs::directory_iterator(path))
        files.push_back(entry.path());
    return files;
}

vector<ImageObject> assignObject(vector<string> names){
    vector<ImageObject> objects;
    string tmpname;
    bool flag = true;
    for(auto i : names){
        if(i.find(".txt") != string::npos){ // if ".txt" is found in string
            tmpname = i;
            tmpname.erase(tmpname.end() - 4, tmpname.end());
            for(auto j : names){
                if ((j.find(tmpname) != string::npos ) && (j.find(".txt") == string::npos)){ // if a file with the same name but different suffix is found
                    ImageObject it{imgtxt, i, j};
                    objects.push_back(it);
                    break;
                }
                if (((j.find(tmpname) != string::npos) && (j.find(".txt") != string::npos))){ // if no file with the same name is found
                    ImageObject jt{txt, i};
                    objects.push_back(jt);
                    break;
                }
            }
        }
        if(i.find(".txt") == string::npos){ // if ".txt" is not found in filename
            tmpname = i;
            tmpname.erase((tmpname.begin() + tmpname.find_last_of('.')), tmpname.end());
            string compn = tmpname + ".txt";

            for(auto j : names){
                if (j.compare(compn) == 0){
                    flag = false;
                    break;
                }
            }
            if(flag){
            ImageObject ji{img, i};
            objects.push_back(ji);
            }
        }
    }
    return objects;
}

Mat resizeToFull(Mat img){
    if(!img.data){
        cerr << "Error: Could not read the image." << endl;
    }
    double scaleX = static_cast<double>(SCREEN_WIDTH) / img.cols;
    double scaleY = static_cast<double>(SCREEN_HEIGHT) / img.rows;
    double scale = min(scaleX, scaleY);
    Mat resizedImage;
    resize(img, resizedImage, Size(), scale, scale);

    return resizedImage;
}

Mat centerOnBlack(Mat img){
    Mat blackBackground(SCREEN_HEIGHT, SCREEN_WIDTH, img.type(), Scalar(0, 0, 0)); // Create a black background image
    int xOffset = (SCREEN_WIDTH - img.cols) / 2; // Calculate the position to center the image
    int yOffset = (SCREEN_HEIGHT - img.rows) / 2;
    Mat roi = blackBackground(Rect(xOffset, yOffset, img.cols, img.rows)); // Copy the image onto the black background at the calculated position
    img.copyTo(roi);
    return blackBackground;
}

vector<string> readText(string txtpath){
    ifstream file(txtpath);
    if (!file.is_open()) {
        cerr << "Error: Could not open the text file." << endl;
    }
    string buf;
    vector<string> text;

    while(getline(file, buf)){
        text.push_back(buf);
    }
    file.close();
    return text;
}

Mat printTextOnImage(const vector<string> text, cv::Mat& image, int ystart){
    // Font settings
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 1.0;
    int thickness = 2;
    Scalar color(0,0,0);
    Point pos(20, ystart);

    for(auto i : text){
        putText(image, i, pos, fontFace, fontScale, color, thickness);
        pos.y += 30;
    } 
    return image;

    //TODO: deal with too long lines, and too many lines

}

void sleepForMilliseconds(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


Mat insertLogo(Mat img, Mat logo){
    int xOffset = (SCREEN_WIDTH - logo.cols); // Calculate the position to center the image
    int yOffset = (SCREEN_HEIGHT - logo.rows);
    Mat roi = img(Rect(xOffset, yOffset, logo.cols, logo.rows)); // Copy the image onto the black background at the calculated position
    logo.copyTo(roi);
    return img;
    
}


void displayImage(ImageObject obj){
    switch (obj.getmode()){
    case img:{
        Mat image;
        image = imread(obj.getimgName(), IMREAD_COLOR );
        if (!image.data){
            printf("No image data \n");
            return;
        }
        namedWindow("Image", WINDOW_AUTOSIZE);
        setWindowProperty("Image", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
        image = resizeToFull(image);
        if((image.cols != SCREEN_WIDTH) || (image.rows != SCREEN_HEIGHT))
            image = centerOnBlack(image);    
        imshow("Image", image);
        break;
    }
    case txt:{
        vector<string> text = readText(obj.gettxtName());


        Mat whiteBackground(SCREEN_HEIGHT, SCREEN_WIDTH, CV_8UC3, Scalar(255, 255, 255));

        Mat logo;
        logo = imread("logo.png", IMREAD_COLOR);
        if (!logo.data){
            printf("No image data \n");
            return;
        }
        whiteBackground = insertLogo(whiteBackground, logo);

        whiteBackground = printTextOnImage(text, whiteBackground, 20);

        namedWindow("Image", WINDOW_NORMAL);
        setWindowProperty("Image", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
        imshow("Image", whiteBackground);
        break;
    }
    case imgtxt:{
        vector<string> text = readText(obj.gettxtName());
        Mat image;
        image = imread(obj.getimgName(), IMREAD_COLOR );
        if (!image.data){
            printf("No image data \n");
            return;
        }
        namedWindow("Image", WINDOW_AUTOSIZE);
        setWindowProperty("Image", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
        image = resizeToFull(image);
        if((image.cols != SCREEN_WIDTH) || (image.rows != SCREEN_HEIGHT))
            image = centerOnBlack(image);    

        Mat txtbkrd(30 * (text.size() + 1), SCREEN_WIDTH, CV_8UC3, Scalar(255, 255, 255)); //TODO: Make image transparent
        Mat roi = image(Rect(0, (SCREEN_HEIGHT - (30 * (text.size() + 1))), SCREEN_WIDTH, (30 * (text.size() + 1)))); //?
        txtbkrd.copyTo(roi);
        image = printTextOnImage(text, image, (SCREEN_HEIGHT - (30 * text.size())));

        imshow("Image", image);


    }
    default:
        break;
    }
}
