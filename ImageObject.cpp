//+-------------------------------------------------------------------------
//
//  InfoScreen
//  Copyright (C) 2024 Jakob Wallner
//
//  File:       ImageObject.cpp
//
//--------------------------------------------------------------------------

#include <iostream>

#include "ImageObject.hpp"

ImObjMode ImageObject::getmode(){
    return mode;
}
void ImageObject::setmode(ImObjMode m_mode){
    mode = m_mode;
}

string ImageObject::gettxtName(){
    return txtName;
}
void ImageObject::settxtName(string m_txtName){
    txtName = m_txtName;
}

string ImageObject::getimgName(){
    return imgName;
}
void ImageObject::setimgName(string m_imgName){
    imgName = m_imgName;
}

ImageObject::ImageObject(){}


ImageObject::ImageObject(ImObjMode m_mode, string m_name){
    mode = m_mode;
    switch (mode){
    case img:
        imgName = m_name;
        break;

    case txt:
        txtName = m_name;
        break;

    default:
        std::cout << "Wrong Mode -> imgtxt requires 2 name arguments!" << std::endl;
        break;
    }
}

ImageObject::ImageObject(ImObjMode m_mode, string m_txtname, string m_imgname){
    mode = m_mode;
    switch (mode){
    case imgtxt:
        txtName = m_txtname;
        imgName = m_imgname;
        break;
    
    default:
        std::cout << "Wrong Mode -> img/txt requires either 1 name argument!" << std::endl;
        break;
    }
}

ImageObject::~ImageObject(){}
