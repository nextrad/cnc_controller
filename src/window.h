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
        QString getCountDownTime(time_t timeLeft);
        bool testConnection(string unitname);
        char* stringToCharPntr(string str);
        bool testSubNetwork(QString NetID);
        int sendFilesOverNetwork(void);
        void resetHeaderFileTimes(void);
        bool startCountDown(void);

    private:
        int m_counter;

        //inactive is for prior to and after an experiment
        //waiting is before start time
        //active is during an experiment, between start and end time
        // INACTIVE -> WAITING -> ACTIVE -> INACTIVE
        enum timeState {INACTIVE=0, WAITING=1, ACTIVE=2};

        QPushButton *testConnectionButton;
        QPushButton *startCountDownButton;
        QPushButton *abortAudioRecordingButton;
        QPushButton *editHeaderFileButton;
        QPushButton *receiveNodeDetailsButton;
        QPushButton *goButton;
        QPushButton *showVideoButton;
        QPushButton *runNextlookButton;

        QLCDNumber *countDown;
        QTextEdit *statusBox;
        QLabel *countDownLabel;

        QTimer *starttimer;
        QTimer *endtimer;
        QTimer *countdowntimer;
        string startTime;
        string endTime;
        time_t stopUnixTime;
        time_t strtUnixTime;
        time_t currentUnixTime;
        int experiment_state;

        void initGUI(void);

        ConnectionManager connectionManager;
        AudioConnectionManager audioRecorder;
        HeaderFileWindow *headerfilewindow;
        HeaderArmFiles headerarmfiles;
        NetworkManager server;

    private slots:
        void connectionTestButtonClicked(void);  
        void updateCountDownLCD(void);
        void startRecording(void);
        void stopRecording(void);
        void abortAudioRecordingButtonClicked(void);
        void editHeaderFileButtonClicked(void);
        void openMainMenu(void);
        void receiveNodeDetailsButtonClicked(void);
        int goButtonClicked(void);
        void closeServer();
        void showVideoButtonClicked(void);
        void runNextlookButtonClicked(void);

    signals:
    public slots:
};

#endif // WINDOW_H
