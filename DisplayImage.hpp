#ifndef DisplayImage_HPP
#define DisplayImage_HPP

#pragma once

#include <string>
#include <vector>
#include "ImageObject.hpp"

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

#endif