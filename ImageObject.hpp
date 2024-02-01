//+-------------------------------------------------------------------------
//
//  InfoScreen
//  Copyright (C) 2024 Jakob Wallner
//
//  File:       ImageObject.hpp
//
//--------------------------------------------------------------------------

#ifndef IMAGEOBJECT_HPP
#define IMAGEOBJECT_HPP

#include <string>

#pragma once

using namespace std;

enum ImObjMode{img, txt, imgtxt};

class ImageObject
{
public:
    ImObjMode getmode();
    void setmode(ImObjMode m_mode);
    string gettxtName();
    void settxtName(string m_txtName);
    string getimgName();
    void setimgName(string m_imgName);

    ImageObject();
    ImageObject(ImObjMode m_mode, string m_name);
    ImageObject(ImObjMode m_mode, string m_txtname, string m_imgname);
    ~ImageObject();


private:
    ImObjMode mode;
    string txtName;
    string imgName;
};

#endif