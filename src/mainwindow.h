#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
     void on_testConnectionButton_clicked();

     void on_editHeaderFileButton_clicked();

     void on_receiveNodePositionsButton_clicked();

     void on_receiveBearingsButton_clicked();

     void on_showVideoButton_clicked();

     void on_abortAudioRecordingButton_clicked();

     void on_runNextlookButton_clicked();

     void on_abortGoButton_clicked();

     void on_goButton_clicked();

     void on_goLaterButton_clicked();

private:
    Ui::MainWindow *ui;

    int m_counter;

    // INACTIVE is for prior to and after an experiment
    // WAITING is before start time
    // ACTIVE is during an experiment, between start and end time
    // INACTIVE -> WAITING -> ACTIVE -> INACTIVE
    enum timeState {INACTIVE=0, WAITING=1, ACTIVE=2};

    enum buttonColour {GREEN=0, GRAY=1, RED=2};

    QTimer *starttimer;
    QTimer *endtimer;
    QTimer *countdowntimer;
    string startTime;
    string endTime;
    time_t stopUnixTime;
    time_t strtUnixTime;
    time_t currentUnixTime;
    int experiment_state;

    ConnectionManager connectionManager;
    AudioConnectionManager audioRecorder;
    HeaderFileWindow *headerfilewindow;
    HeaderArmFiles headerarmfiles;
    NetworkManager server;

    void closeServer();

    void testSubNetwork(QString NetID);
    bool testConnection(string unitname);
    char* stringToCharPntr(string str);

    void receiveNodePosition(int node_num);

    void receiveBearings(int node_num);

    void resetHeaderFileTimes(void);
    string setButtonColour(int colourno);
    bool checkCountdown(void);
    int sendFilesOverNetwork(void);
    void runTCUs(void);
    void runTCU(int tcu_num);

    QString getCountDownTime(time_t timeLeft);
    void updateCountDownLCD(void);
    void startRecording(void);
    void stopRecording(void);


};

#endif // MAINWINDOW_H
