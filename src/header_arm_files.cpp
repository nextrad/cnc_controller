//Class:        Datetime
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       Shirley Coetzee
//Created:      December 2017
//Version       1.0 (December 2017)


#include "includes.h"
#include "parameters.h"
#include "header_arm_files.h"


HeaderArmFiles::HeaderArmFiles(void)
{


}

//=============================================================================
// writeToHeaderFile()
//=============================================================================
//method to set a variable's value in the NeXtRAD header file
void HeaderArmFiles::writeToHeaderFile(string section, string key, string value)
{
    std::ifstream check (CNC_HEADER_PATH);
    if (!check.good())
    {
        printf("Please check location of header file and try again.\n");
        exit(EXIT_FAILURE);
    }

    CSimpleIniA ini;

    ini.LoadFile(CNC_HEADER_PATH);

    ini.SetValue(section.c_str(),key.c_str(),value.c_str());

    ini.SaveFile(CNC_HEADER_PATH);

    check.close();
}


//=============================================================================
// readFromHeaderFile()
//=============================================================================
//method to return a variable's value from the NeXtRAD header file
QString HeaderArmFiles::readFromHeaderFile(string section, string var)
{
    //Read from header file
    std::ifstream check (CNC_HEADER_PATH);
    if (!check.good())
    {
        printf("Please check location of header file and try again.\n");
        exit(EXIT_FAILURE);
    }

    CSimpleIniA ini;

    ini.LoadFile(CNC_HEADER_PATH);

    std::string value = (ini.GetValue(section.c_str(), var.c_str()));

    check.close();

    return  QString::fromUtf8(value.c_str());
}


//=============================================================================
// writeToArmtimecfgFile()
//=============================================================================
//method to set up the NextGPSDO armtime.cfg file
void HeaderArmFiles::writeToArmtimecfgFile(string data)
{
    //overwrite file with new value
    ofstream wfile (ARMTIMECFG_PATH);
    wfile << data;
    wfile.close();

    fflush(stdout);
}


//=============================================================================
// readFromBearingsFile()
//=============================================================================
//method to return a variable's value from the NeXtRAD bearings file
QString HeaderArmFiles::readFromBearingsFile(string varName)
{
    //Read from bearings file
    ifstream rfile (BEARINGS_PATH);
    string temp = "";
    int pos = -1;

    //find line with corresponding variable's name and find position of the variable's value on that line
    while(!rfile.eof())
    {
        getline(rfile,temp);
        /*
        if(temp.find(section) != string::npos)
        {
            pos = -2;                                                   //pos = -2 is just to indicate that the section was found
        }
        if(pos == -2)
        {*/
            if(temp.find(varName) != string::npos)                      //if the variable's name is found
            {
                pos = temp.find_first_of('=') + 2;                       //+2 because data starts after "= "
                break;
            }
        //}
    }
    rfile.close();

    if(pos < 0)
    {
        string str = "error: can't find variable";
        return "Error";
    }
    //cout << "substring" << endl;                              //debugging

    //convert from std::string to QString
    string str = temp.substr(pos, temp.find_last_of(';') - pos);
    //cout << "substring end" << endl;                              //debugging


    return   QString::fromUtf8( str.c_str());
}



