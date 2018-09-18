//Author:       Shirley Coetzee
//File:         header.h
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      December 2017

#ifndef HEADER_H
#define HEADER_H

#include <QDateTime>
#include "includes.h"
#include "parameters.h"
#include "SimpleIni.h"
#include <cctype>
#include <string>
#include <cstring>


class HeaderArmFiles
{
    public:
        HeaderArmFiles(void);
        void writeToHeaderFile(string section, string key, string value);
        QString readFromHeaderFile(string section, string var);
        QString readFromPulseParamsFile(string section, string var);
        string readFromGPSInfoFile(int nodeno, string var);
        string readFromBearingsFile(int nodeno, string var, int strsize);
        void writeToGoogleEarthFile(string section, string key, string var);
        string readFromGoogleEarthFile(string section, string key);

    private:

};


#endif // HEADER_H
