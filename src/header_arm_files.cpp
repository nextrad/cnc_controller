//Class:        Datetime
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Version       1.0 (December 2017)
//Created by:   Shirley Coetzee
//Revision      2.0 (July 2018)
//Edited by:    Shirley Coetzee and Brad Kahn
//Revision      3.0 (September 2018)
//Edited by:    Shirley Coetzee




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
    std::ifstream check (HEADER_PATH);
    if (!check.good())
    {
        printf("Please check location of header file and try again.\n");
        exit(EXIT_FAILURE);
    }

    CSimpleIniA ini;

    ini.LoadFile(HEADER_PATH);

    ini.SetValue(section.c_str(),key.c_str(),value.c_str());

    ini.SaveFile(HEADER_PATH);

    check.close();
}


//=============================================================================
// readFromHeaderFile()
//=============================================================================
//method to return a variable's value from the NeXtRAD header file
QString HeaderArmFiles::readFromHeaderFile(string section, string var)
{
    //Read from header file
    std::ifstream check (HEADER_PATH);
    if (!check.good())
    {
        printf("Please check location of header file and try again.\n");
        exit(EXIT_FAILURE);
    }

    CSimpleIniA ini;

    ini.LoadFile(HEADER_PATH);

    std::string value = (ini.GetValue(section.c_str(), var.c_str()));

    check.close();

    return  QString::fromUtf8(value.c_str());
}


//=============================================================================
// readFromPulseParamsFile()
//=============================================================================
//method to return a variable's value from the PulseParams.ini file
QString HeaderArmFiles::readFromPulseParamsFile(string section, string var)
{

    std::ifstream check (PULSE_PARAMS_PATH);
    if (!check.good())
    {
        printf("Please check location of PulseParams.ini file and try again.\n");
        exit(EXIT_FAILURE);
    }

    CSimpleIniA ini;

    ini.LoadFile(PULSE_PARAMS_PATH);

    std::string value = (ini.GetValue(section.c_str(), var.c_str()));

    check.close();

    return  QString::fromUtf8(value.c_str());
}


//=============================================================================
// readFromGPSInfoFile()
//=============================================================================
//method to return a variable's value from a GPSInfo file
string HeaderArmFiles::readFromGPSInfoFile(int nodeno, string var)
{
    string path;

    switch (nodeno)
    {
        case 0: path = CNC_NODE0_GPS_INFO_PATH;
                break;
        case 1: path = CNC_NODE1_GPS_INFO_PATH;
                break;
        case 2: path = CNC_NODE2_GPS_INFO_PATH;
                break;
    }

    //Read from header file
    std::ifstream check (path);
    if (check.good() != 1)
    {
        printf("Please check location of gps info file and try again.\n");
        return "Fault";
    }

    CSimpleIniA ini;

    ini.LoadFile(path.c_str());

    std::string value = (ini.GetValue("", var.c_str()));

    check.close();

    return value;
}


//=============================================================================
// writeToGoogleEarthFile()
//=============================================================================
//method to place a variable's value into a Google Earth file
void HeaderArmFiles::writeToGoogleEarthFile(string section, string key, string var)
{
    // Open Google Earth file
    std::ifstream file (GOOGLE_EARTH_FILE);
    if (file.good() != 1)
    {
        printf("Please check location of Google Earth file and try again.\n");
    }
    else
    {
        std::string original_substr, replacement ;
        std::string line;

        // get a temporary file name
        char tempFileName[20]; // name only valid till next invocation of tempFileOpen
        std::ofstream temp_file;
        strcpy(tempFileName, "/tmp/XXXXXX");
        if (mkstemp(tempFileName) != -1)
        {

            temp_file.open(tempFileName);

            while ( std::getline( file, line) )
            {
                // find section
                std::size_t found = line.find(section);
                if (found!=std::string::npos)
                {
                    temp_file << line << endl;

                    // find key
                    while ( std::getline( file, line) )
                    {
                        found = line.find(key);
                        if (found!=std::string::npos)
                        {
                            original_substr = line;

                            std::string key1 = key.substr(1,key.length()-2);
                            replacement = key + var + "</" + key1 + ">";

                            line.replace( found, original_substr.size(), replacement ) ;
                            found += replacement.size() ;

                            temp_file << line << endl;

                            break;
                        }
                        else
                        {
                            temp_file << line << endl;
                        }
                    }
                }
                else
                {
                    temp_file << line << endl;
                }
            }

            // overwrite the original file with the temporary file
            {
                std::ifstream temp_file(tempFileName) ;
                std::ofstream file(GOOGLE_EARTH_FILE) ;
                file << temp_file.rdbuf() ;
            }

            // delete the temporary file
            std::remove(tempFileName) ;
        }
    }
}


//=============================================================================
// readFromGoogleEarthFile()
//=============================================================================
//method to return a variable's value from a Google Earth file
string HeaderArmFiles::readFromGoogleEarthFile(string section, string key)
{   
    string data = "";

    // Open Google Earth file
    std::ifstream file (GOOGLE_EARTH_FILE);
    if (file.good() != 1)
    {
        printf("Please check location of Google Earth file and try again.\n");
    }
    else
    {
        std::string line;

        while ( std::getline( file, line) )
        {
            // find section
            std::size_t found = line.find(section);
            if (found!=std::string::npos)
            {
                // find key
                while ( std::getline( file, line) )
                {
                    found = line.find(key);
                    if (found!=std::string::npos)
                    {
                        // get data
                        found = line.find('>');
                        if (found!=std::string::npos)
                        {
                            string str = line.substr(found + 1);
                            found = str.find(".");
                            if (found!=std::string::npos)
                            {
                                data = line; //str.substr(found);
                            }
                            else
                            {
                                found = str.find("<");
                                data = str.substr(0, found);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    return data;
}
