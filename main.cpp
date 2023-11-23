#include <iostream>
#include <opencv2/opencv.hpp>
#include "main.hpp"
#include "ImageObject.hpp"
#include <filesystem>
#include "settings.h"
#include <chrono>
#include <fstream>

namespace fs = filesystem;
using namespace cv;
using namespace std;

int main(int argc, char** argv ){
    /*if ( argc != 2 )
    {
        cout << "usage: DisplayImage.out <tetst.jpeg>\n";
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

    string path = DATAPATH;
    for (const auto & entry : fs::directory_iterator(path))
        cout << entry.path() << endl;

    waitKey(0);*/
    while(1){
        vector<string> datanames = getFiles(DATAPATH);
        vector<ImageObject> DpObjects;
        DpObjects = assignObject(datanames);

        for(auto i : DpObjects){
            displayImage(i);
            if(waitKey(0) == 'x')
                return 0;
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
                if (((j.find(tmpname) != string::npos) && (j.find(".txt") == string::npos))){ // if no file with the same name is found
                    ImageObject jt{txt, i};
                    objects.push_back(jt);
                    break;
                }
            }
        }
        if(i.find(".txt") == string::npos){ // if ".txt" is not found in filename
            tmpname = i;
            tmpname.erase((tmpname.begin() + tmpname.find_last_of('.')), tmpname.end());
            for(auto j : names){
                if (!((j.find(tmpname) != string::npos ) && (j.find(".txt") != string::npos))){
                    ImageObject ji{img, i};
                    objects.push_back(ji);
                    break;
                }
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

string readText(string txtpath){
    ifstream file(txtpath);
    if (!file.is_open()) {
        cerr << "Error: Could not open the text file." << endl;
    }
    string text;
    getline(file, text);
    file.close();
    return text;
}

void displayImage(ImageObject obj){
    switch (obj.getmode()){
    case img:{
        Mat image;
        image = imread(obj.getimgName(), IMREAD_COLOR );
        if (!image.data){
            printf("No image data \n");
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
        string text = readText(obj.gettxtName());

        Mat whiteBackground(SCREEN_HEIGHT, SCREEN_WIDTH, CV_8UC3, Scalar(255, 255, 255));
        int fontFace = FONT_HERSHEY_SIMPLEX;
        double fontScale = 2.0;
        int thickness = 2;
        int baseline = 0;
        Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);

        Point textPosition((SCREEN_WIDTH - textSize.width) / 2, (SCREEN_HEIGHT + textSize.height) / 2);

        putText(whiteBackground, text, textPosition, fontFace, fontScale, Scalar(0, 0, 0), thickness);

        namedWindow("Text on White Background", WINDOW_NORMAL);
        setWindowProperty("Text on White Background", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
        imshow("Text on White Background", whiteBackground);
        break;
    }
    default:
        break;
    }
    return;
}