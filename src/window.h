//Author:       David Bissett
//Class:        Window
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      April 2016
//Last Edited:  June 2016

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QLCDNumber>
#include <QTextEdit>
#include <QString>
#include "connection_manager.h"
#include "audio_connection_manager.h"
#include "includes.h"
#include "parameters.h"
#include "datetime.h"
#include "headerfilewindow.h"
#include "header_arm_files.h"
#include "networkmanager.h"
#include <thread>

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

class QPushButton;
class Window : public QWidget
{
    Q_OBJECT
    public:
        explicit Window(QWidget *parent = 0);
        ~Window();
        //string convertFromUnixTime(time_t);
        bool testConnection(string unitname);
        char* stringToCharPntr(string str);
        bool testSubNetwork(QString NetID);

    private:
        int m_counter;
        QPushButton *testConnectionButton;
        QPushButton *startCountDownButton;
        QPushButton *abortVideoRecordingButton;
        QPushButton *updateHeaderFileButton;
        QPushButton *receiveNodeDetailsButton;
        QPushButton *sendHeaderButton;
        QPushButton *showVideoButton;
        QPushButton *runNextlookButton;
 //       QPushButton *closeButton;

        QLCDNumber *countDown;
        QTextEdit *statusBox;
        QLabel *countDownLabel;

        QTimer *starttimer;
        QTimer *endtimer;
        QTimer *countDownTim;
        string startTime, startTime2;
        string endTime;
        time_t stopUnixTime;
        time_t strtUnixTime;
        time_t currentUnixTime;
        int timMode;
        void initGUI(void);

        ConnectionManager connectionManager;
        AudioConnectionManager audioRecorder;
        HeaderFileWindow *headerfilewindow;
        HeaderArmFiles headerarmfiles;
        NetworkManager server;

    private slots:
        void connectionTestButtonClicked(void);
        void startCountDown(void);
        void updateCountDownLCD(void);
        void startRecording(void);
        void stopRecording(void);
        void abortVideoRecordingButtonClicked(void);
        void updateHeaderFileButtonClicked(void);
        void openMainMenu(void);
        void receiveNodeDetailsButtonClicked(void);
        int sendHeaderButtonClicked(void);
        void closeServer();
        void showVideoButtonClicked(void);
        void runNextlookButtonClicked(void);
       // void closeButtonClicked(void);

    signals:
    public slots:
};

#endif // WINDOW_H
