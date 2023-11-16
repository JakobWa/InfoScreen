#ifndef DisplayImage_HPP
#define DisplayImage_HPP

#pragma once

#include <string>
#include <vector>
#include "ImageObject.hpp"

std::vector<std::string> getFiles(std::string apath);
std::vector<ImageObject> assignObject(std::vector<std::string> names);



#endif