//Author:       Shirley Coetzee
//File:         header_arm_files.h
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      December 2017

#ifndef HEADERARMFILES_H
#define HEADERARMFILES_H

#include <QDateTime>
#include "includes.h"
#include "parameters.h"
#include "SimpleIni.h"

class HeaderArmFiles
{
    public:
        HeaderArmFiles(void);

        void setHeaderFileName(string newname);
        string getHeaderFileName();
        string getHeaderPathName();
        string getArmtimecfgFileName();
        string getArmtimecfgPathName();
        string getBearingsFileName();
        string getBearingsPathName();

        void writeToHeaderFile(string varName, string data, string section);
        QString readFromHeaderFile(string varName, string section);
        int renameHeaderFile(string newname);
        void writeToArmtimecfgFile(string data);
        QString readFromBearingsFile(string varName);

    private:
        string headerFileName;
        string headerPathName;
        string armtimecfgFileName;
        string armtimecfgPathName;
        string bearingsFileName;
        string bearingsPathName;


};


#endif // HEADERARMFILES_H
