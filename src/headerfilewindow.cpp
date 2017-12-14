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

    //button for changing calibration settings in header file
    calibSettingsButton = new QPushButton("Calibration\nSettings", this);
    calibSettingsButton->setGeometry(100, 70, 140, 50);
    connect(calibSettingsButton, SIGNAL (clicked(bool)), this, SLOT(calibSettingsButtonClicked(void)));
    calibSettingsButton->setFocusPolicy(Qt::NoFocus);

    //button for changing export parameters in header file
    exportParametersButton = new QPushButton("Time &&\nParameters", this);
    exportParametersButton->setGeometry(100, 140, 140, 50);
    connect(exportParametersButton, SIGNAL (clicked(bool)), this, SLOT(exportParametersButtonClicked(void)));
    exportParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing radar settings in header file
    radarSettingsButton = new QPushButton("Radar\nSettings", this);
    radarSettingsButton->setGeometry(100, 210, 140, 50);
    connect(radarSettingsButton, SIGNAL (clicked(bool)), this, SLOT(radarSettingsButtonClicked(void)));
    radarSettingsButton->setFocusPolicy(Qt::NoFocus);

    //button for changing bearing parameters in header file
    bearingsButton = new QPushButton("Bearings", this);
    bearingsButton->setGeometry(100, 280, 140, 50);
    connect(bearingsButton, SIGNAL (clicked(bool)), this, SLOT(bearingsButtonClicked(void)));
    bearingsButton->setFocusPolicy(Qt::NoFocus);

    //button for changing GPS parameters in header file
    gpsParametersButton = new QPushButton("GPS\nParameters", this);
    gpsParametersButton->setGeometry(100, 350, 140, 50);
    connect(gpsParametersButton, SIGNAL (clicked(bool)), this, SLOT(gpsParametersButtonClicked(void)));
    gpsParametersButton->setFocusPolicy(Qt::NoFocus);


    //button for changing target position in header file
    targetPositionSettingsButton = new QPushButton("Target\nPosition", this);
    targetPositionSettingsButton->setGeometry(260, 70, 140, 50);
    connect(targetPositionSettingsButton, SIGNAL (clicked(bool)), this, SLOT(targetPositionSettingsButtonClicked(void)));
    targetPositionSettingsButton->setFocusPolicy(Qt::NoFocus);

    //button for changing Polarisation parameters in header file
    polarisationButton = new QPushButton("Polarisation\nParameters", this);
    polarisationButton->setGeometry(260, 140, 140, 50);
    connect(polarisationButton, SIGNAL (clicked(bool)), this, SLOT(polarisationButtonClicked(void)));
    polarisationButton->setFocusPolicy(Qt::NoFocus);

    //button for changing Pulse parameters in header file
    pulseParametersButton = new QPushButton("Pulse\nParameters", this);
    pulseParametersButton->setGeometry(260, 210, 140, 50);
    connect(pulseParametersButton, SIGNAL (clicked(bool)), this, SLOT(pulseParametersButtonClicked(void)));
    pulseParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing Environmental parameters in header file
    environmentalParametersButton = new QPushButton("Environmental\nParameters", this);
    environmentalParametersButton->setGeometry(260, 280, 140, 50);
    connect(environmentalParametersButton, SIGNAL (clicked(bool)), this, SLOT(environmentalParametersButtonClicked(void)));
    environmentalParametersButton->setFocusPolicy(Qt::NoFocus);

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


    //Buttons to choose which calibration settings
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

    calibSettingsButton->show();
    exportParametersButton->show();
    radarSettingsButton->show();
    bearingsButton->show();
    gpsParametersButton->show();
    targetPositionSettingsButton->show();
    polarisationButton->show();
    pulseParametersButton->show();
    environmentalParametersButton->show();
}


//========================================================exportParametersButtonClicked=====================
// calibSettingsButtonClicked()
//=============================================================================
void HeaderFileWindow::calibSettingsButtonClicked(void)
{
    clearMenu();
    menu = 1;

    //set GUI buttons and textfields appropriately
    label->setText("Calibration Settings");

    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(15, 100, 140, 40);
    text1->setText("PriPredelay");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(260, 100, 140, 40);
    text2->setText("DdsPredelay");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("PriPredelay", "Calibration");
    textbox1->setGeometry(150, 105, 40, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("DdsPredelay", "Calibration");
    textbox2->setGeometry(445, 105, 40, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    Rx1SwitchButton->setGeometry(15, 150, 175, 40);
    Rx1SwitchButton->setText("Rx1 Switch");
    Rx1SwitchButton->show();

    Rx2SwitchButton->setGeometry(260, 150, 175, 40);
    Rx2SwitchButton->setText("Rx2 Switch");
    Rx2SwitchButton->show();

    Rx3SwitchButton->setGeometry(15, 200, 175, 40);
    Rx3SwitchButton->setText("Rx3 Switch");
    Rx3SwitchButton->show();

    adcButton->setGeometry(260, 200, 175, 40);
    adcButton->setText("ADC");
    adcButton->show();

}


//=============================================================================
// RxSwitchButtonClicked()
//=============================================================================
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

    QString oldVal = headerarmfiles.readFromHeaderFile(varName, "Calibration");
    textbox1->setGeometry(260, 73, 160, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    varName = ("Rx" + ss.str() + "SwitchPredelay");
    text2->setGeometry(15, 120, 180, 40);
    text2->setText(varName.c_str());
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    oldVal = headerarmfiles.readFromHeaderFile(varName, "Calibration");
    textbox2->setGeometry(260, 123, 160, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    varName = ("Rx" + ss.str() + "Switchenable");
    text3->setGeometry(15, 170, 180, 40);
    text3->setText(varName.c_str());
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    oldVal = headerarmfiles.readFromHeaderFile(varName, "Calibration");
    textbox3->setGeometry(260, 173, 160, 29);
    textbox3->setText(oldVal);
    textbox3->show();
}


//=============================================================================
// adcButtonClicked()
//=============================================================================
void HeaderFileWindow::adcButtonClicked(void)
{
    clearMenu();
    menu = 10;
    label->setText("ADC Calibration Settings");

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
    QString oldVal = headerarmfiles.readFromHeaderFile("AdcDcOffset", "Calibration");
    textbox1->setGeometry(140, 73, 80, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("AdcPreDelay", "Calibration");
    textbox2->setGeometry(140, 123, 80, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("AdcTriggerSource", "Calibration");
    oldVal = oldVal.mid(1, oldVal.length() - 2);
    textbox3->setGeometry(260, 173, 80, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("AdcTriggerLevel", "Calibration");
    textbox4->setGeometry(405, 73, 80, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("AdcPreTriggerSample", "Calibration");
    textbox5->setGeometry(260, 223, 80, 29);
    textbox5->setText(oldVal);
    textbox5->show();
}


//=============================================================================
// exportParametersButtonClicked()
//=============================================================================
void HeaderFileWindow::exportParametersButtonClicked(void)
{
    Datetime datetime;


    clearMenu();
    menu = 2;
    label->setText("Set Times && Parameters"); //Export Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();


    text1->setGeometry(15, 100, 140, 40);
    text1->setText("Start Time");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(15, 150, 140, 40);
    text2->setText("End Time");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    // Keep Header file dates in format of yyyy-MM-dd hh:mm:ss !!!

    //QString oldVal = headerarmfiles.readFromHeaderFile("StartTime", "Export");
    textbox1->setGeometry(150, 105, 200, 29);
    string now = datetime.nowPlusSecs(STARTTIMESECS);
    textbox1->setText(now.c_str());
    textbox1->show();

    //oldVal = headerarmfiles.readFromHeaderFile("EndTime", "Export");
    textbox2->setGeometry(150, 155, 200, 29);
    now = datetime.nowPlusSecs(ENDTIMESECS);
    textbox2->setText(now.c_str());
    textbox2->show();

    exportPulseParametersButton->setGeometry(15, 200, 175, 40);
    exportPulseParametersButton->setText("Export Pulse\nParameters");
    exportPulseParametersButton->show();

    exportSampleParametersButton->setGeometry(260, 200, 175, 40);
    exportSampleParametersButton->setText("Export Sample\nParameters");
    exportSampleParametersButton->show();
}


//=============================================================================
// exportPulseParametersButtonClicked()
//=============================================================================
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


//=============================================================================
// exportSampleParametersButtonClicked()
//=============================================================================
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
//=============================================================================
void HeaderFileWindow::bearingsButtonClicked(void)
{
    clearMenu();
    menu = 16;
    label->setText("Bearings");  // e.g. N 66° 0′ 0″ E  1245.01′

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(15, 70, 150, 40);
    text1->setText("Node 0 Bearing");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(15, 120, 150, 40);
    text2->setText("Node 1 Bearing");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(15, 170, 150, 40);
    text3->setText("Node 2 Bearing");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("Node 0 Bearing", "Bearings");
    textbox1->setGeometry(250, 73, 90, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("Node 1 Bearing", "Bearings");
    textbox2->setGeometry(250, 123, 90, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("Node 2 Bearing", "Bearings");
    textbox3->setGeometry(250, 173, 90, 29);
    textbox3->setText(oldVal);
    textbox3->show();

}


//=============================================================================
// gpsParametersButtonClicked()
//=============================================================================
void HeaderFileWindow::gpsParametersButtonClicked(void)
{
    clearMenu();
    menu = 17;
    label->setText("GPS Parameters");

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

//    text4->setGeometry(20, 220, 160, 50);
//    text4->setText("Stability");
//    text4->setFont(QFont("Ubuntu",14));
//    text4->show();


    QString temp;

    int NodeCnt = server.getNoClients();
    if (NodeCnt > 1)
    {
        temp = QString::number(server.getGPSLat(0));
        text5->setGeometry(200, 70, 160, 50);
        text5->setText(temp);
        text5->setFont(QFont("Ubuntu",14));
        text5->show();

        temp = QString::number(server.getGPSLon(0));
        text6->setGeometry(200, 120, 160, 50);
        text6->setText(temp);
        text6->setFont(QFont("Ubuntu",14));
        text6->show();

        temp = QString::number(server.getGPSHt(0));
        text7->setGeometry(200, 170, 160, 50);
        text7->setText(temp);
        text7->setFont(QFont("Ubuntu",14));
        text7->show();

    //    text8->setGeometry(200, 220, 160, 50);
    //    text8->setText("Node0Stability");
    //    text8->setFont(QFont("Ubuntu",14));
    //    text8->show();
    }

    if (NodeCnt > 2)
    {
        temp = QString::number(server.getGPSLat(1));
        text9->setGeometry(280, 70, 160, 50);
        text9->setText(temp);
        text9->setFont(QFont("Ubuntu",14));
        text9->show();

        temp = QString::number(server.getGPSLon(1));
        text10->setGeometry(280, 120, 160, 50);
        text10->setText(temp);
        text10->setFont(QFont("Ubuntu",14));
        text10->show();

        temp = QString::number(server.getGPSHt(1));
        text11->setGeometry(280, 170, 160, 50);
        text11->setText(temp);
        text11->setFont(QFont("Ubuntu",14));
        text11->show();

    //    text12->setGeometry(280, 230, 160, 50);
    //    text12->setText("Node2Stability");
    //    text12->setFont(QFont("Ubuntu",14));
    //    text12->show();
    }

    if (NodeCnt > 3)
    {

        temp = QString::number(server.getGPSLat(2));
        text13->setGeometry(360, 70, 160, 50);
        text13->setText(temp);
        text13->setFont(QFont("Ubuntu",14));
        text13->show();

        temp = QString::number(server.getGPSLon(2));
        text14->setGeometry(360, 120, 160, 50);
        text14->setText(temp);
        text14->setFont(QFont("Ubuntu",14));
        text14->show();

        temp = QString::number(server.getGPSHt(2));
        text15->setGeometry(360, 170, 160, 50);
        text15->setText(temp);
        text15->setFont(QFont("Ubuntu",14));
        text15->show();

    //    text16->setGeometry(360, 230, 160, 50);
    //    text16->setText("Node2Stability");
    //    text16->setFont(QFont("Ubuntu",14));
    //    text16->show();
    }

}

//=============================================================================
// targetPositionSettingsButtonClicked()
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
    text1->setText("TgtLocationLat");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(100, 120, 140, 40);
    text2->setText("TgtLocationLon");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(100, 170, 140, 40);
    text3->setText("TgtLocationHt");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("TgtLocationLat", "Target");
    textbox1->setGeometry(260, 73, 180, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("TgtLocationLon", "Target");
    textbox2->setGeometry(260, 123, 180, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("TgtLocationHt", "Target");
    textbox3->setGeometry(260, 173, 180, 29);
    textbox3->setText(oldVal);
    textbox3->show();
}


//=============================================================================
// polarisationButtonClicked()
//=============================================================================
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
}


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

    Pulse1Button->setGeometry(15, 150, 175, 40);
    Pulse1Button->setText("Pulse 1");
    Pulse1Button->show();

    Pulse2Button->setGeometry(260, 150, 175, 40);
    Pulse2Button->setText("Pulse 2");
    Pulse2Button->show();
}


//=============================================================================
// pulseButtonClicked()
//=============================================================================
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


//=============================================================================
// environmentalParametersButtonClicked()
//=============================================================================
void HeaderFileWindow::environmentalParametersButtonClicked(void)
{
    std::string now;

    clearMenu();
    menu = 18;
    label->setText("Environmental Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(15, 70, 200, 40);
    text1->setText("Humidity");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(15, 120, 200, 40);
    text2->setText("Air Temperature");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(15, 170, 200, 40);
    text3->setText("Barometric Pressure");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(15, 230, 200, 40);
    text4->setText("Time");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("Humidity", "Environment");
    textbox1->setGeometry(230, 70, 150, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("Air Temperature", "Environment");
    textbox2->setGeometry(230, 120, 150, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("Barometric Pressure", "Environment");
    textbox3->setGeometry(230, 170, 150, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    now = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8().constData();
    textbox4->setGeometry(230, 230, 150, 29);
    textbox4->setText(now.c_str());
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
    std::string temp;
    string varName = "";
    stringstream ss;
    switch(menu)
    {
        case 1://Calibration Settings
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PriPredelay", temp, "Calibration");

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("DdsPredelay", temp, "Calibration");

            showFirstMenu();
        break;

        case 2://Export Parameters
            temp = textbox1->toPlainText().toUtf8().constData();   //StartTime = 2017-12-04 16:46:17
            headerarmfiles.writeToHeaderFile("StartTime", temp, "Export");

            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToArmtimecfgFile(temp);

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("EndTime", temp, "Export");

            showFirstMenu();
        break;

        case 3://Radar Settings
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Power", temp, "Radar Settings");

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("F0", temp, "Radar Settings");

            temp = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PRF", temp, "Radar Settings");

            temp = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseLength", temp, "Radar Settings");

            temp = textbox5->toPlainText().toUtf8().constData();
            temp = "'" + temp + "'";
            headerarmfiles.writeToHeaderFile("Waveform", temp, "Radar Settings");

            showFirstMenu();
        break;

        case 4://Target Position
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TgtLocationLat", temp, "Target");

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TgtLocationLon", temp, "Target");

            temp = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TgtLocationHt", temp, "Target");

            showFirstMenu();
        break;

        case 5://Polarisation Parameters
            temp = textbox1->toPlainText().toUtf8().constData();
            temp = "'" + temp + "'";
            headerarmfiles.writeToHeaderFile("TxPol", temp, "Polarisation");

            temp = textbox2->toPlainText().toUtf8().constData();
            temp = "'" + temp + "'";
            headerarmfiles.writeToHeaderFile("Rx1Pol", temp, "Polarisation");

            temp = textbox3->toPlainText().toUtf8().constData();
            temp = "'" + temp + "'";
            headerarmfiles.writeToHeaderFile("Rx2Pol", temp, "Polarisation");

            temp = textbox4->toPlainText().toUtf8().constData();
            temp = "'" + temp + "'";
            headerarmfiles.writeToHeaderFile("Rx3Pol", temp, "Polarisation");

            showFirstMenu();
        break;

        case 6://Pulse Parameters
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("NumberOfPulses", temp, "Pulse Parameters");

            showFirstMenu();
        break;

        case 7: case 8: case 9://Calibration Settings RxSwitch
            ss << (menu - 6);
            varName = ("Rx" + ss.str() + "SwitchDelay");
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile(varName, temp, "Calibration");

            varName = ("Rx" + ss.str() + "SwitchPredelay");
            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile(varName, temp, "Calibration");

            varName = ("Rx" + ss.str() + "Switchenable");
            temp = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile(varName, temp, "Calibration");

            calibSettingsButtonClicked();
        break;

        case 10://Calibration Settings ADC
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("AdcDcOffset", temp, "Calibration");

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("AdcPreDelay", temp, "Calibration");

            temp = textbox3->toPlainText().toUtf8().constData();
            temp = "'" + temp + "'";
            headerarmfiles.writeToHeaderFile("AdcTriggerSource", temp, "Calibration");

            temp = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("AdcTriggerLevel", temp, "Calibration");

            temp = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("AdcPreTriggerSample", temp, "Calibration");

            showFirstMenu();
        break;

        case 11: case 12://Pulse 1 and 2 Parameters
            ss << (menu - 10);
            varName = ("Pulse " + ss.str());
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("MBoffset", temp, varName);

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("DIGoffset", temp, varName);

            temp = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PRIoffset", temp, varName);

            temp = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Frequency", temp, varName);

            temp = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TxPol", temp, varName);

            temp = textbox6->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("RxPol", temp, varName);

            showFirstMenu();
        break;

        case 13://Pulse Parameters
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("FirstPulse", temp, "Export");

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("LastPulse", temp, "Export");

            temp = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseStep", temp, "Export");

            temp = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("NumOfPulses", temp, "Export");

            showFirstMenu();
        break;

        case 14://Sample Parameters
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("FirstSample", temp, "Export");

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("LastSample", temp, "Export");

            temp = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("SampleStep", temp, "Export");

            temp = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("NumOfSamplesPerPulse", temp, "Export");

            showFirstMenu();
        break;

        case 16://Bearings Parameters
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node 0 Bearing", temp, "Bearings");

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node 1 Bearing", temp, "Bearings");

            temp = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node 2 Bearing", temp, "Bearings");

            showFirstMenu();
        break;

        case 17://gpsParameters Parameters

            temp = text1->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node0LocationLat", temp, "Geometry");

            temp = text2->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node0LocationLon", temp, "Geometry");

            temp = text3->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node0LocationHt", temp, "Geometry");

//            temp = text4->text().toUtf8().constData();
//            headerarmfiles.writeToHeaderFile("Node0Stability", temp, "Geometry");


            temp = text5->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node1LocationLat", temp, "Geometry");

            temp = text6->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node1LocationLon", temp, "Geometry");

            temp = text7->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node1LocationHt", temp, "Geometry");

//            temp = text8->text().toUtf8().constData();
//            headerarmfiles.writeToHeaderFile("Node1Stability", temp, "Geometry");


            temp = text9->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node2LocationLat", temp, "Geometry");

            temp = text10->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node2LocationLon", temp, "Geometry");

            temp = text11->text().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Node2LocationHt", temp, "Geometry");

//            temp = text12->text().toUtf8().constData();
//            headerarmfiles.writeToHeaderFile("Node2Stability", temp, "Geometry");

            // already gets saved
            showFirstMenu();
        break;

        case 18://environmental Parameters
            temp = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Humidity", temp, "Environment");

            temp = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Air Temperature", temp, "Environment");

            temp = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Barometric Pressure", temp, "Environment");

            temp = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Time", temp, "Environment");

            showFirstMenu();
        break;

    }
    //add a timestamp to the file
    temp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8().constData();
    headerarmfiles.writeToHeaderFile("TimeStamp", temp, "Time Stamp");



}


//=============================================================================
// clearMenu()
//=============================================================================
//Method to hide all buttons and textfields of the 'update header file' menus
void HeaderFileWindow::clearMenu(void)
{
    calibSettingsButton->hide();
    exportParametersButton->hide();
    radarSettingsButton->hide();
    bearingsButton->hide();
    gpsParametersButton->hide();
    targetPositionSettingsButton->hide();
    polarisationButton->hide();
    pulseParametersButton->hide();
    environmentalParametersButton->hide();

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

    Rx1SwitchButton->hide();
    Rx2SwitchButton->hide();
    Rx3SwitchButton->hide();

    okButton->hide();
    adcButton->hide();
    Pulse1Button->hide();
    Pulse2Button->hide();
    exportPulseParametersButton->hide();
    exportSampleParametersButton->hide();
}




