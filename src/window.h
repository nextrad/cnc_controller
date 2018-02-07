//Author:       David Bissett
//Class:        Window
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      April 2016
//Version       1.0 (June 2016)
//Edited by:    Shirley Coetzee and Darryn Jordan
//Revision      2.0 (December 2017)
//Edited by:    Shirley Coetzee, Darryn Jordan, Brad Kahn and Simon Lewis
//Revision      3.0 (Jan/Feb 2018)


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
        void testSubNetwork(QString NetID);
        int sendFilesOverNetwork(void);
        void resetHeaderFileTimes(void);
        bool checkCountdown(void);
        void runTCUs(void);
        void runTCU(int tcu_num);
        void receiveNodePosition(int node_num);
        void receiveBearings(int node_num);

    private:
        int m_counter;

        // INACTIVE is for prior to and after an experiment
        // WAITING is before start time
        // ACTIVE is during an experiment, between start and end time
        // INACTIVE -> WAITING -> ACTIVE -> INACTIVE
        enum timeState {INACTIVE=0, WAITING=1, ACTIVE=2};

        enum buttonColour {GREEN=0, GRAY=1, RED=2};

        QPushButton *testConnectionButton;
        QPushButton *startCountDownButton;
        QPushButton *abortAudioRecordingButton;
        QPushButton *editHeaderFileButton;
        QPushButton *receiveNodePositionsButton;
        QPushButton *receiveBearingsButton;

        QPushButton *goButton;
        QPushButton *goLaterButton;
        QPushButton *showVideoButton;
        QPushButton *runNextlookButton;
        QPushButton *abortGoButton;

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
        string setButtonColour(int colourno);

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
        void receiveNodePositionsButtonClicked(void);
        void receiveBearingsButtonClicked(void);
        void goButtonClicked(void);
        void goLaterButtonClicked(void);
        void closeServer();
        void showVideoButtonClicked(void);
        void runNextlookButtonClicked(void);
        void abortGoButtonClicked(void);

    signals:
    public slots:
};

#endif // WINDOW_H
