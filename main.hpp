#ifndef MAIN_HPP
#define MAIN_HPP

#pragma once

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "ImageObject.hpp"

using cv::Mat;

/*This function iterates through a folder an returns a list of the files inside
*@param string with the name of the folder of the files
*@return vector of strings, where one string represents one file
*/
std::vector<std::string> getFiles(std::string apath);

/*This function takes a list of files and puts them into ImageObjects.
*It iterates through the list and groups files with the same name into one object,
*either containing just an image, just a textfile or both image and textfile.
*@param vector<string> list of files, in style of getFiles()
*@return vector of ImageObjects
*/
std::vector<ImageObject> assignObject(std::vector<std::string> names);

/*Resizes the given image to the Screensize provided in settings.h
*@param Mat image object
*@return Mat image object
*/
Mat resizeToFull(Mat img);

Mat centerOnBlack(Mat img);

Mat printTextOnImage(const std::string& text, cv::Mat& image, int ystart);

std::vector<std::string> readText(std::string txtpath);

Mat insertLogo(Mat img, Mat logo);

Mat bottomText(Mat img, std::vector<std::string> txt);

/*Takes an image and prints it to the screen
*@param ImageObject with image and/or textpath
*@retun nothing
*/
void displayImage(ImageObject obj);


#endif