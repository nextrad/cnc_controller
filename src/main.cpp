
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       David Bissett
//Created:      April 2016
//Version       1.0 (June 2016)
//Edited by:    Shirley Coetzee
//Revision      2.0 (December 2016)

#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include "includes.h"
#include "parameters.h"


bool NTP_ON;
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
    MainWindow mainwindow;
    mainwindow.setWindowIcon(icon); //Set Icon for application
    mainwindow.show();
    return app.exec();
}

//Method to test if the NTP server is running correctly
void testNTP(void)
{
    NTP_ON = false;

    int status = system("sudo service ntp status > ../tmp/ntpStatus.txt");      //write the status of the NTP server to ntpStatus.txt
    if (-1 != status)
    {
        int ret = WEXITSTATUS(status);
        if(ret!=0)
        {
            cout << "NTP server FAILED to run correctly" << endl;
        }
    }

    //read status from file
    ifstream ntpStatus ("../tmp/ntpStatus.txt");
    printf("\nntpStatus.txt opened\n");
    string temp;
    getline(ntpStatus,temp);
    printf("%s\n", temp.c_str());

    if(temp.find("not running") != string::npos)            //if it finds the substring 'not running'
    {
        status = system("sudo service ntp start");
        if (-1 != status)
        {
            int ret = WEXITSTATUS(status);
            if(ret!=0)
            {
                cout << "NTP server FAILED to run correctly" << endl;
            }
        }

        printf("\n");
    }
    else
    {
        NTP_ON = true;
    }
    printf("\n");
    ntpStatus.close();
}

//Method to test if the DNS server is running correctly
void testDNS(void)
{
    int status = system("sudo service bind9 status > ../tmp/dnsStatus.txt");    //write the status of the DNS server to dnsStatus.txt
    if (-1 != status)
    {
        int ret = WEXITSTATUS(status);
        if(ret!=0)
        {
            cout << "DNS server FAILED to run correctly" << endl;
        }
    }

    //read status from file
    ifstream dnsStatus ("../tmp/dnsStatus.txt");
    printf("\ndnsStatus.txt opened\n");
    string temp;
    getline(dnsStatus,temp);
    printf("%s\n", temp.c_str());

    if(temp.find("not running") != string::npos)            //if it finds the substring 'not running'
    {
        status = system("sudo service bind9 start");
        if (-1 != status)
        {
            int ret = WEXITSTATUS(status);
            if(ret!=0)
            {
                cout << "DNS server FAILED to run correctly" << endl;
            }
        }
        printf("\n");
    }
    printf("\n");
    dnsStatus.close();
}

//Method to test if the Asterisk server is running correctly
void testAsterisk(void)
{
    int status = system("sudo service asterisk status > ../tmp/asteriskStatus.txt");    //write the status of the Asterisk server to asteriskStatus.txt
    if (-1 != status)
    {
        int ret = WEXITSTATUS(status);
        if(ret!=0)
        {
            cout << "Asterisk FAILED to run correctly" << endl;
        }
    }
    sleep(2);

    //read status from file
    ifstream audioStatus ("../tmp/asteriskStatus.txt");
    printf("\nasteriskStatus.txt opened\n");
    string temp;
    getline(audioStatus,temp);
    printf("%s\n", temp.c_str());

    if(temp.find("not running") != string::npos)                    //if it finds the substring 'not running'
    {
        status = system("sudo service asterisk start");
        if (-1 != status)
        {
            int ret = WEXITSTATUS(status);
            if(ret!=0)
            {
                cout << "Asterisk FAILED to run correctly" << endl;
            }
        }
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
