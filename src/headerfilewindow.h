//Author:       David Bissett
//Class:        HeaderFileWindow
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      April 2016
//Last Edited:  May 2016
//Edited by:    Shirley Coetzee
//Revision      3.0 (December 2017)
//Edited by:    Shirley Coetzee
//Revision      4.0 (February 2018)

#ifndef HEADERFILEWINDOW_H
#define HEADERFILEWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QTextEdit>
#include <QSignalMapper>
#include <QDateTime>
#include "connection_manager.h"
#include "audio_connection_manager.h"
#include "networkmanager.h"
#include "includes.h"
#include "parameters.h"
#include "datetime.h"
#include "header_arm_files.h"
#include "timingdialog.h"
#include "pulsedialog.h"
#include "targetdialog.h"
#include "bearingsdialog.h"
#include "weatherdialog.h"
#include "geometrydialog.h"
#include "quicklookdialog.h"


#include <QDialog>

namespace Ui {
class HeaderFileWindow;
}

class HeaderFileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HeaderFileWindow(QWidget *parent = 0);
    ~HeaderFileWindow();

private slots:
    void on_timingParametersButton_clicked();

    void on_geometryParametersButton_clicked();

    void on_targetPositionSettingsButton_clicked();

    void on_bearingsButtonClicked_clicked();

    void on_weatherParametersButton_clicked();

    void on_pulseParametersButton_clicked();

    void on_quicklookSettingsButton_clicked();

private:
    Ui::HeaderFileWindow *ui;

    time_t currentTime;
    NetworkManager server;
    HeaderArmFiles headerarmfiles;
    TimingDialog *timingdialog;
    PulseDialog *pulsedialog;
    TargetDialog *targetdialog;
    BearingsDialog *bearingsdialog;
    WeatherDialog *weatherdialog;
    GeometryDialog *geometrydialog;
    QuicklookDialog *quicklookdialog;

    short menu;

};

#endif // HEADERFILEWINDOW_H
