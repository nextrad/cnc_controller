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
        bool newtime;

    private:
        void initGUI(void);
        NetworkManager server;

        QLabel *label;

        QPushButton *timingParametersButton;
        QPushButton *geometryParametersButton;
        QPushButton *targetPositionSettingsButton;
        QPushButton *bearingsButton;
        QPushButton *weatherParametersButton;
        QPushButton *pulseParametersButton;
        QPushButton *quicklookSettingsButton;

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
        QTextEdit *textbox7;
        QTextEdit *textbox8;
        QTextEdit *textbox9;
        QTextEdit *textbox10;
/*
        QPushButton *Rx1SwitchButton;
        QPushButton *Rx2SwitchButton;
        QPushButton *Rx3SwitchButton;
        QPushButton *adcButton;

        QSignalMapper *signalMapper;
        QSignalMapper *pulseSignalMapper;
*/
        time_t currentTime;
        HeaderArmFiles headerarmfiles;

        short menu;
        void clearMenu(void);
        void showFirstMenu(void);

    private slots:
        void timingParametersButtonClicked(void);
        void geometryParametersButtonClicked(void);
        void targetPositionSettingsButtonClicked(void);
        void bearingsButtonClicked(void);
        void weatherParametersButtonClicked(void);
        void pulseParametersButtonClicked(void);
        void quicklookSettingsButtonClicked(void);

        void cancelButtonClicked(void);
        void okButtonClicked(void);
      
    signals:
    public slots:
};

#endif // HEADERFILEWINDOW_H
