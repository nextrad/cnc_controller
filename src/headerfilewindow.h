//Author:       David Bissett
//Class:        HeaderFileWindow
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      April 2016
//Last Edited:  May 2016
//Edited by:    Shirley Coetzee
//Revision      3.0 (December 2017)

#ifndef HEADERFILEWINDOW_H
#define HEADERFILEWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QTextEdit>
#include <QSignalMapper>
#include <QDateTime>
#include <stdio.h>
#include "connection_manager.h"
#include "audio_connection_manager.h"
#include "networkmanager.h"
#include "includes.h"
#include "parameters.h"
#include "datetime.h"
#include "header_arm_files.h"

class HeaderFileWindow : public QDialog
{
    Q_OBJECT
    public:
        HeaderFileWindow(QWidget *parent = 0);

    private:
        void initGUI(void);
        NetworkManager server;

        QLabel *label;

        QPushButton *calibSettingsButton;
        QPushButton *exportParametersButton;
        QPushButton *radarSettingsButton;
        QPushButton *targetPositionSettingsButton;
        QPushButton *polarisationButton;
        QPushButton *pulseParametersButton;
        QPushButton *Pulse1Button;
        QPushButton *Pulse2Button;
        QPushButton *exportPulseParametersButton;
        QPushButton *exportSampleParametersButton;
        QPushButton *environmentalParametersButton;
        QPushButton *bearingsButton;
        QPushButton *gpsParametersButton;

        QPushButton *cancelButton;
        QPushButton *okButton;

        QLabel *text1;
        QLabel *text2;
        QLabel *text3;
        QLabel *text4;
        QLabel *text5;
        QLabel *text6;
        QLabel *text7;
        QLabel *text8;
        QLabel *text9;
        QLabel *text10;
        QLabel *text11;
        QLabel *text12;
        QLabel *text13;
        QLabel *text14;
        QLabel *text15;
        QLabel *text16;

        QTextEdit *textbox1;
        QTextEdit *textbox2;
        QTextEdit *textbox3;
        QTextEdit *textbox4;
        QTextEdit *textbox5;
        QTextEdit *textbox6;

        QPushButton *Rx1SwitchButton;
        QPushButton *Rx2SwitchButton;
        QPushButton *Rx3SwitchButton;
        QPushButton *adcButton;

        QSignalMapper *signalMapper;
        QSignalMapper *pulseSignalMapper;

        time_t currentTime;
        HeaderArmFiles headerarmfiles;


        short menu;
        void clearMenu(void);
        void showFirstMenu(void);

    private slots:
        void calibSettingsButtonClicked(void);
        void exportParametersButtonClicked(void);
        void radarSettingsButtonClicked(void);
        void targetPositionSettingsButtonClicked(void);
        void polarisationButtonClicked(void);
        void pulseParametersButtonClicked(void);
        void cancelButtonClicked(void);
        void okButtonClicked(void);
        void RxSwitchButtonClicked(int switchID);
        void adcButtonClicked(void);
        void pulseButtonClicked(int pulseID);
        void exportPulseParametersButtonClicked(void);
        void exportSampleParametersButtonClicked(void);
        void environmentalParametersButtonClicked(void);
        void bearingsButtonClicked(void);
        void gpsParametersButtonClicked(void);

    signals:
    public slots:
};

#endif // HEADERFILEWINDOW_H