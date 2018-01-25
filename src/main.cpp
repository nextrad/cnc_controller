
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       David Bissett
//Created:      April 2016
//Version       1.0 (June 2016)
//Edited by:    Shirley Coetzee
//Revision      2.0 (December 2016)

#include <QApplication>
#include <QPushButton>
#include "window.h"
#include "includes.h"
#include "parameters.h"



int EXPERIMENT_LENGTH;

void testNTP(void);
void testDNS(void);
void testAsterisk(void);
void setParameters(void);

int main(int argc, char **argv)
{
    testDNS();
    testNTP();
    testAsterisk();
    setParameters();

    QApplication app (argc, argv);
    QIcon icon(ICON_PATH);
    Window window;
    window.setWindowIcon(icon); //Set Icon for application
    window.show();
    return app.exec();
}

//Method to test if the NTP server is running correctly
void testNTP(void)
{
    system("sudo service ntp status > ../tmp/ntpStatus.txt");      //write the status of the NTP server to ntpStatus.txt

    //read status from file
    ifstream ntpStatus ("../tmp/ntpStatus.txt");
    printf("\nntpStatus.txt opened\n");
    string temp;
    getline(ntpStatus,temp);
    printf("%s\n", temp.c_str());

    if(temp.find("not running") != string::npos)            //if it finds the substring 'not running'
    {
        system("sudo service ntp start");
        printf("\n");
    }
    printf("\n");
    ntpStatus.close();
}

//Method to test if the DNS server is running correctly
void testDNS(void)
{
    system("sudo service bind9 status > ../tmp/dnsStatus.txt");    //write the status of the DNS server to dnsStatus.txt

    //read status from file
    ifstream dnsStatus ("../tmp/dnsStatus.txt");
    printf("\ndnsStatus.txt opened\n");
    string temp;
    getline(dnsStatus,temp);
    printf("%s\n", temp.c_str());

    if(temp.find("not running") != string::npos)            //if it finds the substring 'not running'
    {
        system("sudo service bind9 start");
        printf("\n");
    }
    printf("\n");
    dnsStatus.close();
}

//Method to test if the Asterisk server is running correctly
void testAsterisk(void)
{
    system("sudo service asterisk status > ../tmp/asteriskStatus.txt");    //write the status of the Asterisk server to asteriskStatus.txt

    sleep(2);

    //read status from file
    ifstream audioStatus ("../tmp/asteriskStatus.txt");
    printf("\nasteriskStatus.txt opened\n");
    string temp;
    getline(audioStatus,temp);
    printf("%s\n", temp.c_str());

    if(temp.find("not running") != string::npos)                    //if it finds the substring 'not running'
    {
        system("sudo service asterisk start");
        printf("\n");
    }
    printf("\n");
    audioStatus.close();
}

void setParameters(void)
{
    bool gotDetailsOK = false;

    while (!gotDetailsOK)
    {
        EXPERIMENT_LENGTH = 60; //default value [seconds]
        gotDetailsOK = true;
     }
}
