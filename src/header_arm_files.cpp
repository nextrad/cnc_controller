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
// readFromBearingsFile()
//=============================================================================
//method to return a variable's value from a Bearings file
string HeaderArmFiles::readFromBearingsFile(int nodeno, string var, int strsize)
{
    string path, data;

    switch (nodeno)
    {
        case 0: path = CNC_NODE0_BEARINGS_PATH;
                break;
        case 1: path = CNC_NODE1_BEARINGS_PATH;
                break;
        case 2: path = CNC_NODE2_BEARINGS_PATH;
                break;
    }

    //Read from header file
    std::ifstream check (path);
    if (check.good() != 1)
    {
        printf("Please check location of bearings file and try again.\n");
        return "Fault";
    }


    std::string line;
    while ( std::getline( check, line ) )
    {
        // find var
        std::size_t found = line.find(var);
        if (found!=std::string::npos)
        {
            //cout << line[found] << endl;

            // get rest of line
            std::string str = line.substr (found + var.length() + 1);
            //cout << "the rest of the string after " << var << " is " << str << endl;

            if (var == "Lon")
            {
                std::size_t found2 = str.find_first_of(",");
                if (found2!=std::string::npos)
                {
                    //cout << str.substr(found2 + 1) << endl;
                    // print out value
                    data = str.substr(found2 + 1, strsize);
                    //cout << data << endl;
                }
            }
            else
            {
                // find a minus or number
                std::size_t found2 = str.find_first_of("-1234567890");
                if (found2!=std::string::npos)
                {
                    //cout << str.substr(found2) << endl;
                    // print out value
                    data = str.substr(found2, strsize);
                    //cout << data << endl;
                }
            }
        }
    }

    return data;
}


//=============================================================================
// writeToGoogleEarthFile()
//=============================================================================
//method to return a variable's value from a Google Earth file
void HeaderArmFiles::writeToGoogleEarthFile(string section, string key, string var)
{
    //Read from Google Earth file
    std::ifstream original_file (GOOGLE_EARTH_FILE);
    if (original_file.good() != 1)
    {
        printf("Please check location of Google Earth file and try again.\n");
    }
    else
    {
        std::string original_substr, replacement ;
        std::string line;

        // get a temporary file name
        char tmp_file_name[ L_tmpnam ] ;
        std::tmpnam(tmp_file_name) ;
        std::ofstream temp_file(tmp_file_name) ;

        while ( std::getline( original_file, line) )
        {
            // find section
            std::size_t found = line.find(section);
            if (found!=std::string::npos)
            {
                temp_file << line << endl;

                // find key
                while ( std::getline( original_file, line) )
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
            std::ifstream temp_file(tmp_file_name) ;
            std::ofstream original_file(GOOGLE_EARTH_FILE) ;
            original_file << temp_file.rdbuf() ;
        }

        // delete the temporary file
        std::remove(tmp_file_name) ;
    }
}
