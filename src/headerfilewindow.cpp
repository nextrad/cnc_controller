//Class:        HeaderFileWindow
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       David Bissett
//Created:      April 2016
//Version       1.0 (June 2016)
//Edited by:    Shirley Coetzee
//Revision      2.0 (December 2016)
//Edited by:    Shirley Coetzee
//Revision      3.0 (December 2017)

//=============================================================================
// Includes
//=============================================================================
#include "headerfilewindow.h"
#include <QPushButton>
#include <QApplication>
#include <QDateTime>
#include <QStyleOption>


//=============================================================================
// Constructor
//=============================================================================
HeaderFileWindow::HeaderFileWindow(QWidget *parent) : QDialog(parent)
{
    //Set size of Window
    setMinimumSize(500,310);//setFixedSize(500,310);
    initGUI();
    showFirstMenu();
}



//=============================================================================
// initGUI()
//=============================================================================
void HeaderFileWindow::initGUI(void)
{
    //Title
    label = new QLabel(this);
    label->setGeometry(45, 10, 500, 50);
    label->setText("What would you like to Edit?");
    label->setFont(QFont("Ubuntu",24));
    label->show();

 

    //button for changing timing parameters in header file
    timingParametersButton = new QPushButton("Timing", this);
    timingParametersButton->setGeometry(100, 70, 140, 50);
    connect(timingParametersButton, SIGNAL (clicked(bool)), this, SLOT(timingParametersButtonClicked(void)));
    timingParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing Geometry parameters in header file
    geometryParametersButton = new QPushButton("Geometry\nParameters", this);
    geometryParametersButton->setGeometry(260, 70, 140, 50);  // 350
    connect(geometryParametersButton, SIGNAL (clicked(bool)), this, SLOT(geometryParametersButtonClicked(void)));
    geometryParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing target position in header file
    targetPositionSettingsButton = new QPushButton("Target\nPosition", this);
    targetPositionSettingsButton->setGeometry(100, 140, 140, 50);
    connect(targetPositionSettingsButton, SIGNAL (clicked(bool)), this, SLOT(targetPositionSettingsButtonClicked(void)));
    targetPositionSettingsButton->setFocusPolicy(Qt::NoFocus);

    //button for changing bearing parameters in header file
    bearingsButton = new QPushButton("Bearings", this);
    bearingsButton->setGeometry(260, 140, 140, 50);
    connect(bearingsButton, SIGNAL (clicked(bool)), this, SLOT(bearingsButtonClicked(void)));
    bearingsButton->setFocusPolicy(Qt::NoFocus);

    //button for changing weather parameters in header file
    weatherParametersButton = new QPushButton("Weather\nParameters", this);
    weatherParametersButton->setGeometry(100, 21, 140, 50);
    connect(weatherParametersButton, SIGNAL (clicked(bool)), this, SLOT(weatherParametersButtonClicked(void)));
    weatherParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing Pulse parameters in header file
    pulseParametersButton = new QPushButton("Pulse\nParameters", this);
    pulseParametersButton->setGeometry(260, 210, 140, 50);
    connect(pulseParametersButton, SIGNAL (clicked(bool)), this, SLOT(pulseParametersButtonClicked(void)));
    pulseParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing quicklook settings in header file
    quicklookSettingsButton = new QPushButton("Quicklook\nSettings", this);
    quicklookSettingsButton->setGeometry(100, 280, 140, 50);
    connect(quicklookSettingsButton, SIGNAL (clicked(bool)), this, SLOT(quicklookSettingsButtonClicked(void)));
    quicklookSettingsButton->setFocusPolicy(Qt::NoFocus);


    //cancel button to go to first menu
    cancelButton = new QPushButton("Cancel", this);
    cancelButton->setFont(QFont("Ubuntu",12));
    cancelButton->setGeometry(250, 420, 100, 30); //200, 420, 100, 30);
    connect(cancelButton, SIGNAL (clicked(bool)), this, SLOT(cancelButtonClicked(void)));
    cancelButton->setFocusPolicy(Qt::NoFocus);

    //ok button to accept value changes and write to header file
    okButton = new QPushButton("Ok", this);
    okButton->setFont(QFont("Ubuntu",12));
    okButton->setGeometry(120, 420, 100, 30); //20, 420, 100, 30);
    connect(okButton, SIGNAL (clicked(bool)), this, SLOT(okButtonClicked(void)));
    okButton->setFocusPolicy(Qt::NoFocus);
    okButton->hide();

    //labels and textboxes for header file variables
    text1 = new QLabel(this);
    text2 = new QLabel(this);
    text3 = new QLabel(this);
    text4 = new QLabel(this);
    text5 = new QLabel(this);
    text6 = new QLabel(this);
    text7 = new QLabel(this);
    text8= new QLabel(this);
    text9 = new QLabel(this);
    text10 = new QLabel(this);
    text11 = new QLabel(this);
    text12 = new QLabel(this);

    textbox1 = new QTextEdit(this);
    textbox1->hide();
    textbox2 = new QTextEdit(this);
    textbox2->hide();
    textbox3 = new QTextEdit(this);
    textbox3->hide();
    textbox4 = new QTextEdit(this);
    textbox4->hide();
    textbox5 = new QTextEdit(this);
    textbox5->hide();
    textbox6 = new QTextEdit(this);
    textbox6->hide();


       /*
    Rx1SwitchButton = new QPushButton(this);
    Rx1SwitchButton->hide();
    Rx1SwitchButton->setFocusPolicy(Qt::NoFocus);
    Rx2SwitchButton = new QPushButton(this);
    Rx2SwitchButton->hide();
    Rx2SwitchButton->setFocusPolicy(Qt::NoFocus);
    Rx3SwitchButton = new QPushButton(this);
    Rx3SwitchButton->hide();
    Rx3SwitchButton->setFocusPolicy(Qt::NoFocus);

    //Buttons to choose which pulse
    Pulse1Button = new QPushButton(this);
    Pulse1Button->hide();
    Pulse1Button->setFocusPolicy(Qt::NoFocus);
    Pulse2Button = new QPushButton(this);
    Pulse2Button->hide();
    Pulse2Button->setFocusPolicy(Qt::NoFocus);

    //mapping the buttons' clicked() signals so that they output integers that get mapped to the respective SLOT's input parameters
    //Here Rx'_'SwitchButton gets mapped to RxSwitchButtonClicked
    signalMapper = new QSignalMapper(this);
    connect(Rx1SwitchButton, SIGNAL (clicked(bool)), signalMapper, SLOT (map()));       //connecting the buttons to the map
    connect(Rx2SwitchButton, SIGNAL (clicked(bool)), signalMapper, SLOT (map()));
    connect(Rx3SwitchButton, SIGNAL (clicked(bool)), signalMapper, SLOT (map()));

    signalMapper->setMapping(Rx1SwitchButton, 1);                                       //mapping the buttons to their respective int value
    signalMapper->setMapping(Rx2SwitchButton, 2);
    signalMapper->setMapping(Rx3SwitchButton, 3);

    connect(signalMapper, SIGNAL (mapped(int)), this, SLOT(RxSwitchButtonClicked(int)));    //connecting the signal mapper to the slot that takes in an int

    //Button to change ADC settings
    adcButton = new QPushButton(this);
    adcButton->hide();
    adcButton->setFocusPolicy(Qt::NoFocus);
    connect(adcButton, SIGNAL (clicked(bool)), this, SLOT(adcButtonClicked(void)));

    //Here Pulse'_'Button gets mapped to PulseButtonClicked
    pulseSignalMapper = new QSignalMapper(this);
    connect(Pulse1Button, SIGNAL (clicked(bool)), pulseSignalMapper, SLOT (map()));
    connect(Pulse2Button, SIGNAL (clicked(bool)), pulseSignalMapper, SLOT (map()));
    pulseSignalMapper->setMapping(Pulse1Button, 1);
    pulseSignalMapper->setMapping(Pulse2Button, 2);
    connect(pulseSignalMapper, SIGNAL (mapped(int)), this, SLOT(pulseButtonClicked(int)));

    //Button to change export pulse parameters
    exportPulseParametersButton = new QPushButton(this);
    exportPulseParametersButton->hide();
    exportPulseParametersButton->setFocusPolicy(Qt::NoFocus);
    connect(exportPulseParametersButton, SIGNAL (clicked(bool)), this, SLOT(exportPulseParametersButtonClicked(void)));

    //Button to change export sample parameters
    exportSampleParametersButton = new QPushButton(this);
    exportSampleParametersButton->hide();
    exportSampleParametersButton->setFocusPolicy(Qt::NoFocus);
    connect(exportSampleParametersButton, SIGNAL (clicked(bool)), this, SLOT(exportSampleParametersButtonClicked(void)));
    */
}


//=============================================================================
// showFirstMenu()
//=============================================================================
void HeaderFileWindow::showFirstMenu(void)
{
    clearMenu();
    menu = 0;
    cancelButton->setText("Ok");

    label->setGeometry(45, 10, 500, 50);
    label->setText("What would you like to Edit?");
    label->setFont(QFont("Ubuntu",24));

    quicklookSettingsButton->show();
    timingParametersButton->show();
 //   radarSettingsButton->show();
    bearingsButton->show();
    geometryParametersButton->show();
    targetPositionSettingsButton->show();
 //   polarisationButton->show();
    pulseParametersButton->show();
    weatherParametersButton->show();
}


//========================================================timingParametersButtonClicked=====================
// quicklookSettingsButtonClicked()
//[Quicklook]

//; ADC_CHANNEL 0 = L, 1 = X, 2 = X
//ADC_CHANNEL = 0

//; MPA = 0, HPA = 1
//AMPLIFIER = 1
//DYNAMIC_RANGE = 65
//SPECTROGRAM_BIN = 1000
//DOPPLER_FFT = 256
//=============================================================================
void HeaderFileWindow::quicklookSettingsButtonClicked(void)
{
    clearMenu();
    menu = 1;

    //set GUI buttons and textfields appropriately
    label->setText("Quicklook Settings");

    cancelButton->setText("Cancel");
    okButton->show();
/*
    text1->setGeometry(50, 100, 140, 40);
    text1->setText("ADC_CHANNEL");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(50, 200, 140, 40);
    text2->setText("AMPLIFIER");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("Quicklook", "ADC_CHANNEL");
    textbox1->setGeometry(250, 100, 140, 40);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("Quicklook", "AMPLIFIER");
    textbox2->setGeometry(250, 200, 140, 40);
    textbox2->setText(oldVal);
    textbox2->show();


    */

}


//=============================================================================
// RxSwitchButtonClicked()
//=============================================================================
/*
void HeaderFileWindow::RxSwitchButtonClicked(int switchID)
{
    stringstream ss;
    ss << switchID;
    string varName = ("Rx" + ss.str() + "Switch Parameters");

    //set GUI buttons and textfields appropriately
    clearMenu();
    menu = 6 + switchID;
    cancelButton->setText("Cancel");
    okButton->show();
    label->setText(QString::fromUtf8( varName.c_str()));

    varName = ("Rx" + ss.str() + "SwitchDelay");
    text1->setGeometry(15, 70, 180, 40);
    text1->setText(varName.c_str());
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    QString oldVal = headerarmfiles.readFromHeaderFile(varName, "quicklookration");
    textbox1->setGeometry(260, 73, 160, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    varName = ("Rx" + ss.str() + "SwitchPredelay");
    text2->setGeometry(15, 120, 180, 40);
    text2->setText(varName.c_str());
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    oldVal = headerarmfiles.readFromHeaderFile(varName, "quicklookration");
    textbox2->setGeometry(260, 123, 160, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    varName = ("Rx" + ss.str() + "Switchenable");
    text3->setGeometry(15, 170, 180, 40);
    text3->setText(varName.c_str());
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    oldVal = headerarmfiles.readFromHeaderFile(varName, "quicklookration");
    textbox3->setGeometry(260, 173, 160, 29);
    textbox3->setText(oldVal);
    textbox3->show();
}
*/

//=============================================================================
// adcButtonClicked()
//=============================================================================
/*
void HeaderFileWindow::adcButtonClicked(void)
{
    clearMenu();
    menu = 10;
    label->setText("ADC quicklookration Settings");

    //set GUI buttons and textfields appropriately
    okButton->show();

    //Labels for each of the radar settings
    text1->setGeometry(15, 70, 140, 40);
    text1->setText("AdcDcOffset");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(15, 120, 140, 40);
    text2->setText("AdcPreDelay");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(15, 170, 160, 40);
    text3->setText("AdcTriggerSource");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(250, 70, 140, 40);
    text4->setText("AdcTriggerLevel");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(15, 220, 200, 40);
    text5->setText("AdcPreTriggerSample");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    //Textboxes for each of the adc settings with their current values
    QString oldVal = headerarmfiles.readFromHeaderFile("AdcDcOffset", "quicklookration");
    textbox1->setGeometry(140, 73, 80, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("AdcPreDelay", "quicklookration");
    textbox2->setGeometry(140, 123, 80, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("AdcTriggerSource", "quicklookration");
    oldVal = oldVal.mid(1, oldVal.length() - 2);
    textbox3->setGeometry(260, 173, 80, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("AdcTriggerLevel", "quicklookration");
    textbox4->setGeometry(405, 73, 80, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("AdcPreTriggerSample", "quicklookration");
    textbox5->setGeometry(260, 223, 80, 29);
    textbox5->setText(oldVal);
    textbox5->show();

}
*/

//=============================================================================
// timingParametersButtonClicked()

//[Timing]
//; Time that experiment starts
//; Local time (SAST: UTC+2)
//YEAR    = 2017
//MONTH   = 12
//DAY     = 11
//HOUR    = 16
//MINUTE  = 20
//SECOND  = 00

//=============================================================================
void HeaderFileWindow::timingParametersButtonClicked(void)
{
    Datetime datetime;


    clearMenu();
    menu = 2;
    label->setText("Set Times && Parameters"); //Export Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();


    text1->setGeometry(15, 100, 140, 40);
    text1->setText("Year");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(15, 150, 140, 40);
    text2->setText("Month");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(15, 200, 140, 40);
    text3->setText("Day");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();


    text4->setGeometry(15, 250, 140, 40);
    text4->setText("Hour");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(15, 300, 140, 40);
    text5->setText("Minute");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(15, 350, 140, 40);
    text6->setText("Second");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();


    textbox1->setGeometry(150, 100, 200, 29);
    string now = datetime.getNowInYears();
    textbox1->setText(now.c_str());
    textbox1->show();

    textbox2->setGeometry(150, 150, 200, 29);
    now = datetime.getNowInMonths();
    textbox2->setText(now.c_str());
    textbox2->show();

    textbox3->setGeometry(150, 200, 200, 29);
    now = datetime.getNowInDays();
    textbox3->setText(now.c_str());
    textbox3->show();

    textbox4->setGeometry(150, 250, 200, 29);
    now = datetime.getNowInHours();
    textbox4->setText(now.c_str());
    textbox4->show();

    textbox5->setGeometry(150, 300, 200, 29);
    now = datetime.getNowInMinutes();
    textbox5->setText(now.c_str());
    textbox5->show();

    textbox6->setGeometry(150, 350, 200, 29);
    now = datetime.getNowSecsPlusSecs(STARTTIMESECS);
    textbox6->setText(now.c_str());
    textbox6->show();

/*
    exportPulseParametersButton->setGeometry(15, 200, 175, 40);
    exportPulseParametersButton->setText("Export Pulse\nParameters");
    exportPulseParametersButton->show();

    exportSampleParametersButton->setGeometry(260, 200, 175, 40);
    exportSampleParametersButton->setText("Export Sample\nParameters");
    exportSampleParametersButton->show();
    */
}


//=============================================================================
// exportPulseParametersButtonClicked()
//=============================================================================
/*
void HeaderFileWindow::exportPulseParametersButtonClicked(void)
{
    clearMenu();
    menu = 13;
    label->setText("Export Pulse Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();


    text1->setGeometry(25, 70, 140, 40);
    text1->setText("FirstPulse");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(25, 120, 140, 40);
    text2->setText("LastPulse");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(25, 170, 140, 40);
    text3->setText("PulseStep");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(250, 70, 140, 40);
    text4->setText("NumOfPulses");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    //cout << "first pulse" << endl;                              //debugging
    QString oldVal = headerarmfiles.readFromHeaderFile("FirstPulse", "Export");
    textbox1->setGeometry(140, 73, 40, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    //cout << "last pulse" << endl;                              //debugging
    oldVal = headerarmfiles.readFromHeaderFile("LastPulse", "Export");
    textbox2->setGeometry(140, 123, 40, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    //cout << "pulse step" << endl;                              //debugging
    oldVal = headerarmfiles.readFromHeaderFile("PulseStep", "Export");
    textbox3->setGeometry(140, 173, 40, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    //cout << "num of pulse" << endl;                              //debugging
    oldVal = headerarmfiles.readFromHeaderFile("NumOfPulses", "Export");
    textbox4->setGeometry(385, 73, 40, 29);
    textbox4->setText(oldVal);
    textbox4->show();
}
*/

//=============================================================================
// exportSampleParametersButtonClicked()
//=============================================================================
/*
void HeaderFileWindow::exportSampleParametersButtonClicked(void)
{
    clearMenu();
    menu = 14;
    label->setText("Export Sample Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();


    text1->setGeometry(25, 70, 140, 40);
    text1->setText("FirstSample");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(25, 120, 140, 40);
    text2->setText("LastSample");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(25, 170, 140, 40);
    text3->setText("SampleStep");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(25, 220, 220, 40);
    text4->setText("NumOfSamplesPerPulse");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("FirstSample", "Export");
    textbox1->setGeometry(140, 73, 60, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("LastSample", "Export");
    textbox2->setGeometry(140, 123, 60, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("SampleStep", "Export");
    textbox3->setGeometry(140, 173, 60, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("NumOfSamplesPerPulse", "Export");
    textbox4->setGeometry(250, 223, 60, 29);
    textbox4->setText(oldVal);
    textbox4->show();
}
*/

//=============================================================================
// radarSettingsButtonClicked()
//=============================================================================
void HeaderFileWindow::radarSettingsButtonClicked(void)
{
    clearMenu();
    menu = 3;
    label->setText("Radar Settings");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    //Labels for each of the radar settings
    text1->setGeometry(25, 70, 140, 40);
    text1->setText("Power");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(25, 120, 140, 40);
    text2->setText("F0");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(25, 170, 140, 40);
    text3->setText("PRF");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(250, 70, 140, 40);
    text4->setText("PulseLength");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(250, 120, 140, 40);
    text5->setText("Waveform");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    //Textboxes for each of the radar settings with their current values
    QString oldVal = headerarmfiles.readFromHeaderFile("Power", "Radar Settings");
    textbox1->setGeometry(100, 73, 90, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("F0", "Radar Settings");
    textbox2->setGeometry(100, 123, 90, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("PRF", "Radar Settings");
    textbox3->setGeometry(100, 173, 90, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseLength", "Radar Settings");
    textbox4->setGeometry(385, 73, 90, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("Waveform", "Radar Settings");
    oldVal = oldVal.mid(1, oldVal.length() - 2);    //substring without inverted commas
    textbox5->setGeometry(385, 123, 90, 29);
    textbox5->setText(oldVal);
    textbox5->show();
}

//=============================================================================
// bearingsButtonClicked()

//Bearings]
//; DTG is date-time (in date-time group format) of getting bearings. EXAMPLE: 091630Z JUL 11 = 1630 UTC on 9 July 2011
//; Baseline_Bisector and node ranges are in meters
//; Node bearings are in degrees relative to true north
//DTG = "061855Z 1217"
//Baseline_Bisector = 2
//n0_Range = 1.82952
//n0_Bearing = 46.5192
//n1_Range = 1.82952
//n1_Bearing = 46.5192
//n2_Range = 1.82952
//n2_Bearing = 46.5192

//=============================================================================
void HeaderFileWindow::bearingsButtonClicked(void)
{
    clearMenu();
    menu = 16;
    label->setText("Bearings");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(15, 70, 150, 40);
    text1->setText("Node 0 Range");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(15, 140, 150, 40);
    text2->setText("Node 0 Bearing");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(15, 210, 150, 40);
    text3->setText("Node 1 Range");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(15, 280, 150, 40);
    text4->setText("Node 1 Bearing");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(15, 350, 150, 40);
    text5->setText("Node 2 Range");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(15, 420, 150, 40);
    text6->setText("Node 2 Bearing");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();

    QString oldVal = headerarmfiles.readFromBearingsFile("n0: Range");
    textbox1->setGeometry(250, 70, 90, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromBearingsFile("n0: Bearing");
    textbox2->setGeometry(250, 140, 90, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromBearingsFile("n1: Range");
    textbox3->setGeometry(250, 210, 90, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromBearingsFile("n1: Bearing");
    textbox4->setGeometry(250, 280, 90, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromBearingsFile("n2: Range");
    textbox5->setGeometry(250, 350, 90, 29);
    textbox5->setText(oldVal);
    textbox5->show();

    oldVal = headerarmfiles.readFromBearingsFile("n2: Bearing");
    textbox6->setGeometry(250, 420, 90, 29);
    textbox6->setText(oldVal);
    textbox6->show();
}


//=============================================================================
// geometryParametersButtonClicked()

//[GeometrySettings]
//; heights are WGS84 and above geoid
//; lats and longs are in decimal degrees
//Node0LocationLat   = -34.1891
//Node0LocationLon   = 18.3665
//Node0LocationHt    = 52.76
//Node1LocationLat   = -3.1891
//Node1LocationLon   = 18.3665
//Node1LocationHt    = 52.76
//Node2LocationLat   = -34.1891
//Node2LocationLon   = 18.3665
//Node2LocationHt   = 52.76

//=============================================================================
void HeaderFileWindow::geometryParametersButtonClicked(void)
{
    clearMenu();
    menu = 17;
    label->setText("geometry Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(20, 70, 160, 50);
    text1->setText("Latitude");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(20, 120, 160, 50);
    text2->setText("Longitude");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(20, 170, 160, 50);
    text3->setText("Height");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();


    QString temp;

    int NodeCnt = server.getNoClients();
    if (NodeCnt > 1)
    {
        temp = QString::number(server.getGPSLat(0));
        text4->setGeometry(200, 70, 160, 50);
        text4->setText(temp);
        text4->setFont(QFont("Ubuntu",14));
        text4->show();

        temp = QString::number(server.getGPSLon(0));
        text5->setGeometry(200, 120, 160, 50);
        text5->setText(temp);
        text5->setFont(QFont("Ubuntu",14));
        text5->show();

        temp = QString::number(server.getGPSHt(0));
        text6->setGeometry(200, 170, 160, 50);
        text6->setText(temp);
        text6->setFont(QFont("Ubuntu",14));
        text6->show();

    }

    if (NodeCnt > 2)
    {
        temp = QString::number(server.getGPSLat(1));
        text7->setGeometry(280, 70, 160, 50);
        text7->setText(temp);
        text7->setFont(QFont("Ubuntu",14));
        text7->show();

        temp = QString::number(server.getGPSLon(1));
        text8->setGeometry(280, 120, 160, 50);
        text8->setText(temp);
        text8->setFont(QFont("Ubuntu",14));
        text8->show();

        temp = QString::number(server.getGPSHt(1));
        text9->setGeometry(280, 170, 160, 50);
        text9->setText(temp);
        text9->setFont(QFont("Ubuntu",14));
        text9->show();

    }

    if (NodeCnt > 3)
    {

        temp = QString::number(server.getGPSLat(2));
        text10->setGeometry(360, 70, 160, 50);
        text10->setText(temp);
        text10->setFont(QFont("Ubuntu",14));
        text10->show();

        temp = QString::number(server.getGPSLon(2));
        text11->setGeometry(360, 120, 160, 50);
        text11->setText(temp);
        text11->setFont(QFont("Ubuntu",14));
        text11->show();

        temp = QString::number(server.getGPSHt(2));
        text12->setGeometry(360, 170, 160, 50);
        text12->setText(temp);
        text12->setFont(QFont("Ubuntu",14));
        text12->show();

    }

}

//=============================================================================
// targetPositionSettingsButtonClicked()

//[TargetSettings]
//; lats and longs are in decimal degrees
//; height is in meters as WGS84 and above geoid

/*TGT_LOCATION_LAT = -34.1874
TGT_LOCATION_LON = 18.4280
TGT_LOCATION_HT = 0*/
//=============================================================================
void HeaderFileWindow::targetPositionSettingsButtonClicked(void)
{
    clearMenu();
    menu = 4;
    label->setText("Target Position");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(100, 70, 140, 40);
    text1->setText("TGT_LOCATION_LAT");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(100, 120, 140, 40);
    text2->setText("TGT_LOCATION_LON");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(100, 170, 140, 40);
    text3->setText("TGT_LOCATION_HT");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    QString oldVal = headerarmfiles.readFromBearingsFile("Target Lat/Lon");
    textbox1->setGeometry(260, 73, 180, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromBearingsFile("Target Lat/Lon");
    textbox2->setGeometry(260, 123, 180, 29);
    textbox2->setText(oldVal);
    textbox2->show();


    textbox3->setGeometry(260, 173, 180, 29);
    textbox3->setText("0.0235");   // user can enter new value if necessary
    textbox3->show();
}


//=============================================================================
// polarisationButtonClicked()
//=============================================================================
/*
void HeaderFileWindow::polarisationButtonClicked(void)
{
    clearMenu();
    menu = 5;
    label->setText("Polarisation Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    //Labels for each of the polarisation parameters
    text1->setGeometry(100, 70, 140, 40);
    text1->setText("TxPol");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(100, 120, 140, 40);
    text2->setText("Rx1Pol");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(100, 170, 140, 40);
    text3->setText("Rx2Pol");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(100, 220, 140, 40);
    text4->setText("Rx3Pol");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    //Textboxes for each of the polarisation parameters with their current values
    QString oldVal = headerarmfiles.readFromHeaderFile("TxPol", "Polarisation");          //Get current value of TxPol from header file
    oldVal = oldVal.mid(1, oldVal.length() - 2);    //substring without inverted commas
    textbox1->setGeometry(260, 73, 160, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("Rx1Pol", "Polarisation");          //Get current value of Rx1Pol from header file
    oldVal = oldVal.mid(1, oldVal.length() - 2);    //substring without inverted commas
    textbox2->setGeometry(260, 123, 160, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("Rx2Pol", "Polarisation");          //Get current value of Rx1Pol from header file
    oldVal = oldVal.mid(1, oldVal.length() - 2);    //substring without inverted commas
    textbox3->setGeometry(260, 173, 160, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("Rx3Pol", "Polarisation");          //Get current value of Rx1Pol from header file
    oldVal = oldVal.mid(1, oldVal.length() - 2);    //substring without inverted commas
    textbox4->setGeometry(260, 223, 160, 29);
    textbox4->setText(oldVal);
    textbox4->show();
}*/


//=============================================================================
// pulseParametersButtonClicked()
//=============================================================================
void HeaderFileWindow::pulseParametersButtonClicked(void)
{
    clearMenu();
    menu = 6;
    label->setText("Pulse Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(100, 70, 150, 40);
    text1->setText("NumberOfPulses");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("NumberOfPulses", "Pulse");
    textbox1->setGeometry(260, 73, 90, 29);
    textbox1->setText(oldVal);
    textbox1->show();
/*
    Pulse1Button->setGeometry(15, 150, 175, 40);
    Pulse1Button->setText("Pulse 1");
    Pulse1Button->show();

    Pulse2Button->setGeometry(260, 150, 175, 40);
    Pulse2Button->setText("Pulse 2");
    Pulse2Button->show();
    */
}


//=============================================================================
// pulseButtonClicked()
//=============================================================================
/*
void HeaderFileWindow::pulseButtonClicked(int pulseID)
{
    stringstream ss;
    ss << pulseID;
    string varName = ("Pulse " + ss.str() + " Parameters");

    clearMenu();
    menu = 10 + pulseID;
    cancelButton->setText("Cancel");
    okButton->show();
    label->setText(QString::fromUtf8( varName.c_str()));

    //set GUI buttons and textfields appropriately
    text1->setGeometry(15, 70, 90, 40);
    text1->setText("MBoffset");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(15, 120, 90, 40);
    text2->setText("DIGoffset");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(15, 170, 90, 40);
    text3->setText("PRIoffset");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(260, 70, 90, 40);
    text4->setText("Frequency");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(260, 120, 90, 40);
    text5->setText("TxPol");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(260, 170, 90, 40);
    text6->setText("RxPol");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();

    varName = ("Pulse " + ss.str());
    QString oldVal = headerarmfiles.readFromHeaderFile("MBoffset", varName);
    textbox1->setGeometry(150, 73, 90, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("DIGoffset", varName);
    textbox2->setGeometry(150, 123, 90, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("PRIoffset", varName);
    textbox3->setGeometry(150, 173, 90, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("Frequency", varName);
    textbox4->setGeometry(400, 73, 90, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("TxPol", varName);
    textbox5->setGeometry(400, 123, 90, 29);
    textbox5->setText(oldVal);
    textbox5->show();

    oldVal = headerarmfiles.readFromHeaderFile("RxPol", varName);
    textbox6->setGeometry(400, 173, 90, 29);
    textbox6->setText(oldVal);
    textbox6->show();
}

*/
//=============================================================================
// weatherParametersButtonClicked()

//[Weather]
//DOUGLAS_SEA_STATE = 5     ; (1 - 8)
//WIND_SPEED        = 10000 ; (knots)
//WIND_DIR          = 123   ; (degrees) where it's coming from (bearing)
//WAVE_HEIGHT       = 6     ; (meters)
//WAVE_DIR          = 123   ; (degrees) where it's coming from (bearing)
//WAVE_PERIOD       = 7.0   ; (seconds)
//AIR_TEMPERATURE   = 17    ; (degrees Celsius)
//AIR_PRESSURE      = 10.7  ; (millibar)

//=============================================================================
void HeaderFileWindow::weatherParametersButtonClicked(void)
{
    std::string now;

    clearMenu();
    menu = 18;
    label->setText("Weather Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();



    text1->setGeometry(15, 70, 200, 40);
    text1->setText("Douglas Sea State");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(15, 120, 200, 40);
    text2->setText("Wind Speed");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(15, 170, 200, 40);
    text3->setText("Wind Direction");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(15, 230, 200, 40);
    text4->setText("Wind Height");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(15, 280, 200, 40);
    text5->setText("Wave Direction");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(15, 330, 200, 40);
    text6->setText("Wave Period");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();

    text7->setGeometry(15, 380, 200, 40);
    text7->setText("Air Temperature");
    text7->setFont(QFont("Ubuntu",14));
    text7->show();

    text8->setGeometry(15, 430, 200, 40);
    text8->setText("Air Pressure");
    text8->setFont(QFont("Ubuntu",14));
    text8->show();


    QString oldVal = headerarmfiles.readFromHeaderFile("DOUGLAS_SEA_STATE", "Weather");
    textbox1->setGeometry(230, 70, 150, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("WIND_SPEED", "Weather");
    textbox2->setGeometry(230, 120, 150, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("WIND_DIR", "Weather");
    textbox3->setGeometry(230, 170, 150, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("WAVE_HEIGHT", "Weather");
    textbox4->setGeometry(230, 230, 150, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("WAVE_DIR", "Weather");
    textbox1->setGeometry(230, 280, 150, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("WAVE_PERIOD", "Weather");
    textbox2->setGeometry(230, 330, 150, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("AIR_TEMPERATURE", "Weather");
    textbox3->setGeometry(230, 380, 150, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("AIR_PRESSURE", "Weather");
    textbox4->setGeometry(230, 430, 150, 29);
    textbox4->setText(oldVal);
    textbox4->show();
}


//=============================================================================
// cancelButtonClicked()
//=============================================================================
void HeaderFileWindow::cancelButtonClicked(void)
{
    switch(menu)
    {
        case 0:                         // switch from headerfile to main menu
            emit finished(0);           // emit SIGNAL "finished(int)" which gets picked up by parent Window()
        break;

        default:                        // switch from subheaderfile to headerfile
            showFirstMenu();            // Default is to show first menu.
        break;
    }
}


//=============================================================================
// okButtonClicked()
//=============================================================================
//This method reduces the number of buttons needed and combines the ok button of all headerfiles
void HeaderFileWindow::okButtonClicked(void)
{

    std::string day, month, year, hour, minute, second, value, var;
    stringstream ss_armtime;

    switch(menu)
    { /*
        case 1://quicklookration Settings
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PriPredelay", value, "quicklookration");

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("DdsPredelay", value, "quicklookration");

            showFirstMenu();
        break;*/

        case 2://Timing Parameters

            year = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Timing", "YEAR", year);

            month = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Timing", "MONTH", month);

            day = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Timing", "DAY", day);

            hour = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Timing", "HOUR", hour);

            minute = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Timing", "MINUTE", minute);

            second = textbox6->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Timing", "SECOND", second);

            ss_armtime << "Date=" << day << "/" << month << "/" << year << "\n";
            ss_armtime << "Arm_Time=" << hour << ":" << minute << ":" << second;
            headerarmfiles.writeToArmtimecfgFile(ss_armtime.str());

            showFirstMenu();
        break;

        /*case 3:
         //Radar Settings
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Power", value, "Radar Settings");

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("F0", value, "Radar Settings");

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PRF", value, "Radar Settings");

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseLength", value, "Radar Settings");

            value = textbox5->toPlainText().toUtf8().constData();
            value = "'" + value + "'";
            headerarmfiles.writeToHeaderFile("Waveform", value, "Radar Settings");

            showFirstMenu();
        break;
*/
        case 4://Target Position
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TGT_LOCATION_LAT", value, "Target");

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TGT_LOCATION_LON", value, "Target");

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TGT_LOCATION_HT", value, "Target");

            showFirstMenu();
        break;
/*
        case 5://Polarisation Parameters
            value = textbox1->toPlainText().toUtf8().constData();
            value = "'" + value + "'";
            headerarmfiles.writeToHeaderFile("TxPol", value, "Polarisation");

            value = textbox2->toPlainText().toUtf8().constData();
            value = "'" + value + "'";
            headerarmfiles.writeToHeaderFile("Rx1Pol", value, "Polarisation");

            value = textbox3->toPlainText().toUtf8().constData();
            value = "'" + value + "'";
            headerarmfiles.writeToHeaderFile("Rx2Pol", value, "Polarisation");

            value = textbox4->toPlainText().toUtf8().constData();
            value = "'" + value + "'";
            headerarmfiles.writeToHeaderFile("Rx3Pol", value, "Polarisation");

            showFirstMenu();
        break;

        case 6://Pulse Parameters
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("NumberOfPulses", value, "Pulse Parameters");

            showFirstMenu();
        break;

        case 7: case 8: case 9://quicklookration Settings RxSwitch
            ss << (menu - 6);
            varName = ("Rx" + ss.str() + "SwitchDelay");
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile(varName, value, "quicklookration");

            varName = ("Rx" + ss.str() + "SwitchPredelay");
            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile(varName, value, "quicklookration");

            varName = ("Rx" + ss.str() + "Switchenable");
            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile(varName, value, "quicklookration");

            quicklookSettingsButtonClicked();
        break;

        case 10://quicklookration Settings ADC
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("AdcDcOffset", value, "quicklookration");

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("AdcPreDelay", value, "quicklookration");

            value = textbox3->toPlainText().toUtf8().constData();
            value = "'" + value + "'";
            headerarmfiles.writeToHeaderFile("AdcTriggerSource", value, "quicklookration");

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("AdcTriggerLevel", value, "quicklookration");

            value = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("AdcPreTriggerSample", value, "quicklookration");

            showFirstMenu();
        break;

        case 11: case 12://Pulse 1 and 2 Parameters
            ss << (menu - 10);
            varName = ("Pulse " + ss.str());
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("MBoffset", value, varName);

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("DIGoffset", value, varName);

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PRIoffset", value, varName);

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Frequency", value, varName);

            value = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TxPol", value, varName);

            value = textbox6->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("RxPol", value, varName);

            showFirstMenu();
        break;

        case 13://Pulse Parameters
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("FirstPulse", value, "Export");

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("LastPulse", value, "Export");

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseStep", value, "Export");

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("NumOfPulses", value, "Export");

            showFirstMenu();
        break;

        case 14://Sample Parameters
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("FirstSample", value, "Export");

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("LastSample", value, "Export");

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("SampleStep", value, "Export");

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("NumOfSamplesPerPulse", value, "Export");

            showFirstMenu();
        break;*/

        case 16://Bearings Parameters

            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Bearings", "NODE0_RANGE", value);

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Bearings", "NODE0_BEARING", value);

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Bearings", "NODE1_RANGE", value);

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Bearings", "NODE1_BEARING", value);

            value = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Bearings", "NODE2_RANGE", value);

            value = textbox6->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Bearings", "NODE2_BEARING", value);

            showFirstMenu();
        break;

        case 17://geometryParameters Parameters

            value = text4->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LAT", value);

            value = text5->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LON", value);

            value = text6->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_HT", value);

            value = text7->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LAT", value);

            value = text8->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LON", value);

            value = text9->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_HT", value);

            value = text10->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LAT", value);

            value = text11->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LON", value);

            value = text12->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_HT", value);

            // already gets saved
            showFirstMenu();
        break;

        case 18://weather Parameters

            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Weather", "DOUGLAS_SEA_STATE", value);

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Weather", "WIND_SPEED", value);

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Weather", "WIND_DIR", value);

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Weather", "WAVE_HEIGHT", value);

            value = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Weather", "WAVE_DIR", value);

            value = textbox6->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Weather", "WAVE_PERIOD", value);

            value = textbox7->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Weather", "AIR_TEMPERATURE", value);

            value = textbox8->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Weather", "AIR_PRESSURE", value);

            showFirstMenu();
        break;

    }
}


//=============================================================================
// clearMenu()
//=============================================================================
//Method to hide all buttons and textfields of the 'update header file' menus
void HeaderFileWindow::clearMenu(void)
{
    quicklookSettingsButton->hide();
    timingParametersButton->hide();
//    radarSettingsButton->hide();
    bearingsButton->hide();
    geometryParametersButton->hide();
    targetPositionSettingsButton->hide();
 //   polarisationButton->hide();
    pulseParametersButton->hide();
    weatherParametersButton->hide();

    text1->hide();
    text2->hide();
    text3->hide();
    text4->hide();
    text5->hide();
    text6->hide();
    text7->hide();
    text8->hide();
    text9->hide();
    text10->hide();
    text11->hide();
    text12->hide();

    textbox1->hide();
    textbox2->hide();
    textbox3->hide();
    textbox4->hide();
    textbox5->hide();
    textbox6->hide();
/*
    Rx1SwitchButton->hide();
    Rx2SwitchButton->hide();
    Rx3SwitchButton->hide();
*/
    okButton->hide();
//    adcButton->hide();
//    Pulse1Button->hide();
//    Pulse2Button->hide();
//    exportPulseParametersButton->hide();
//    exportSampleParametersButton->hide();
}




