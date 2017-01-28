/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include <string>

// Define path to store our resources (images, fonts, lvl data, audio,...)
#define RESOURCE_PATH "../../res/"
#define RESOURCE_XML_PATH "res\\"
#define RESOURCE_FILE(filename) (RESOURCE_PATH + (filename)).c_str()
#define RESOURCE_XML_FILE(filename) (RESOURCE_XML_PATH + (filename)).c_str()