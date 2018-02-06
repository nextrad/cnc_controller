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
    newtime = false;

    //Set size of Window
    setMinimumSize(500,650);//setFixedSize(500,310);

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
    label->setText("Header File Settings");
    label->setFont(QFont("Ubuntu",24));
    label->show();

    //button for changing timing parameters in header file
    timingParametersButton = new QPushButton("Timing", this);
    timingParametersButton->setGeometry(100, 100, 140, 50);
    connect(timingParametersButton, SIGNAL (clicked(bool)), this, SLOT(timingParametersButtonClicked(void)));
    timingParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing Geometry parameters in header file
    geometryParametersButton = new QPushButton("Geometry\nParameters", this);
    geometryParametersButton->setGeometry(300, 100, 140, 50);  // 350
    connect(geometryParametersButton, SIGNAL (clicked(bool)), this, SLOT(geometryParametersButtonClicked(void)));
    geometryParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing target position in header file
    targetPositionSettingsButton = new QPushButton("Target\nPosition", this);
    targetPositionSettingsButton->setGeometry(100, 170, 140, 50);
    connect(targetPositionSettingsButton, SIGNAL (clicked(bool)), this, SLOT(targetPositionSettingsButtonClicked(void)));
    targetPositionSettingsButton->setFocusPolicy(Qt::NoFocus);

    //button for changing bearing parameters in header file
    bearingsButton = new QPushButton("Bearings", this);
    bearingsButton->setGeometry(300, 170, 140, 50);
    connect(bearingsButton, SIGNAL (clicked(bool)), this, SLOT(bearingsButtonClicked(void)));
    bearingsButton->setFocusPolicy(Qt::NoFocus);

    //button for changing weather parameters in header file
    weatherParametersButton = new QPushButton("Weather\nParameters", this);
    weatherParametersButton->setGeometry(100, 240, 140, 50);
    connect(weatherParametersButton, SIGNAL (clicked(bool)), this, SLOT(weatherParametersButtonClicked(void)));
    weatherParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing Pulse parameters in header file
    pulseParametersButton = new QPushButton("Pulse\nParameters", this);
    pulseParametersButton->setGeometry(300, 240, 140, 50);
    connect(pulseParametersButton, SIGNAL (clicked(bool)), this, SLOT(pulseParametersButtonClicked(void)));
    pulseParametersButton->setFocusPolicy(Qt::NoFocus);

    //button for changing quicklook settings in header file
    quicklookSettingsButton = new QPushButton("Quicklook\nSettings", this);
    quicklookSettingsButton->setGeometry(100, 310, 140, 50);
    connect(quicklookSettingsButton, SIGNAL (clicked(bool)), this, SLOT(quicklookSettingsButtonClicked(void)));
    quicklookSettingsButton->setFocusPolicy(Qt::NoFocus);


    //cancel button to go to first menu
    cancelButton = new QPushButton("Cancel", this);
    cancelButton->setFont(QFont("Ubuntu",12));
    cancelButton->setGeometry(250, 600, 100, 30); //200, 420, 100, 30);
    connect(cancelButton, SIGNAL (clicked(bool)), this, SLOT(cancelButtonClicked(void)));
    cancelButton->setFocusPolicy(Qt::NoFocus);

    //ok button to accept value changes and write to header file
    okButton = new QPushButton("Ok", this);
    okButton->setFont(QFont("Ubuntu",12));
    okButton->setGeometry(120, 600, 100, 30); //20, 420, 100, 30);
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
    text13 = new QLabel(this);
    text14 = new QLabel(this);
    text15 = new QLabel(this);

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
    textbox7 = new QTextEdit(this);
    textbox7->hide();
    textbox8 = new QTextEdit(this);
    textbox8->hide();
    textbox9 = new QTextEdit(this);
    textbox9->hide();
    textbox10 = new QTextEdit(this);
    textbox10->hide();


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

    quicklookSettingsButton->show();
    timingParametersButton->show();
    bearingsButton->show();
    geometryParametersButton->show();
    targetPositionSettingsButton->show();
    pulseParametersButton->show();
    weatherParametersButton->show();

}

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
    std::string nowplussecs, day, month, year, hour, minute, second;

    // This time rolls over if add seconds
    nowplussecs = datetime.getNowPlusSecs(STARTTIMESECS);

    year = nowplussecs.substr(0,4);
    month = nowplussecs.substr(5,2);
    day = nowplussecs.substr(8,2);
    hour = nowplussecs.substr(11,2);
    minute = nowplussecs.substr(14,2);
    second = nowplussecs.substr(17,2);


    clearMenu();
    menu = 1;
    label->setText("Set Times & Parameters"); //Export Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();


    text1->setGeometry(100, 70, 250, 50);
    text1->setText("Year");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(100, 120, 250, 50);
    text2->setText("Month");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(100, 170, 250, 50);
    text3->setText("Day");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(100, 220, 250, 50);
    text4->setText("Hour");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(100, 270, 250, 50);
    text5->setText("Minute");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(100, 320, 250, 50);
    text6->setText("Second");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();


    textbox1->setGeometry(300, 73, 180, 29);
    textbox1->setText(year.c_str());
    textbox1->show();

    textbox2->setGeometry(300, 123, 180, 29);
    textbox2->setText(month.c_str());
    textbox2->show();

    textbox3->setGeometry(300, 173, 180, 29);
    textbox3->setText(day.c_str());
    textbox3->show();

    textbox4->setGeometry(300, 223, 180, 29);
    textbox4->setText(hour.c_str());
    textbox4->show();

    textbox5->setGeometry(300, 273, 180, 29);
    textbox5->setText(minute.c_str());
    textbox5->show();

    textbox6->setGeometry(300, 323, 180, 29);
    textbox6->setText(second.c_str());
    textbox6->show();

    newtime = true;

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
    menu = 2;
    label->setText("Geometry Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(70, 70, 250, 50);
    text1->setText("Node 0 Latitude (dec deg)");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(70, 120, 250, 50);
    text2->setText("Node 0 Longitude (dec deg)");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(70, 170, 250, 50);
    text3->setText("Node 0 Height (m)");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();



    text4->setGeometry(70, 250, 250, 50);
    text4->setText("Node 1 Latitude (dec deg)");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(70, 300, 250, 50);
    text5->setText("Node 1 Longitude (dec deg)");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(70, 350, 250, 50);
    text6->setText("Node 1 Height (m)");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();



    text7->setGeometry(70, 430, 250, 50);
    text7->setText("Node 2 Latitude (dec deg)");
    text7->setFont(QFont("Ubuntu",14));
    text7->show();

    text8->setGeometry(70, 480, 250, 50);
    text8->setText("Node 2 Longitude (dec deg)");
    text8->setFont(QFont("Ubuntu",14));
    text8->show();

    text9->setGeometry(70, 530, 250, 50);
    text9->setText("Node 2 Height (m)");
    text9->setFont(QFont("Ubuntu",14));
    text9->show();





    QString oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE0_LOCATION_LAT");
    textbox1->setGeometry(350, 73, 180, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE0_LOCATION_LON");
    textbox2->setGeometry(350, 123, 180, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE0_LOCATION_HT");
    textbox3->setGeometry(350, 173, 180, 29);
    textbox3->setText(oldVal);
    textbox3->show();



    oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE1_LOCATION_LAT");
    textbox4->setGeometry(350, 253, 180, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE1_LOCATION_LON");
    textbox5->setGeometry(350, 303, 180, 29);
    textbox5->setText(oldVal);
    textbox5->show();

    oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE1_LOCATION_HT");
    textbox6->setGeometry(350, 353, 180, 29);
    textbox6->setText(oldVal);
    textbox6->show();



    oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE2_LOCATION_LAT");
    textbox7->setGeometry(350, 433, 180, 29);
    textbox7->setText(oldVal);
    textbox7->show();

    oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE2_LOCATION_LON");
    textbox8->setGeometry(350, 483, 180, 29);
    textbox8->setText(oldVal);
    textbox8->show();

    oldVal = headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE2_LOCATION_HT");
    textbox9->setGeometry(350, 533, 180, 29);
    textbox9->setText(oldVal);
    textbox9->show();

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
    menu = 3;
    label->setText("Target Position");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(70, 70, 250, 50);
    text1->setText("Target Latitude (dec deg)");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(70, 120, 250, 50);
    text2->setText("Target Longitude (dec deg)");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(70, 170, 250, 50);
    text3->setText("Target Height (m)");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("TargetSettings", "TGT_LOCATION_LAT");
    textbox1->setGeometry(350, 73, 180, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("TargetSettings", "TGT_LOCATION_LON");
    textbox2->setGeometry(350, 123, 180, 29);;
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("TargetSettings", "TGT_LOCATION_HT");
    textbox3->setGeometry(350, 173, 180, 29);
    textbox3->setText(oldVal);
    textbox3->show();
}


//=============================================================================
// bearingsButtonClicked()

//Bearings]
//; DTG is date-time (in date-time group format) of getting bearings. EXAMPLE: 091630Z JUL 11 = 1630 UTC on 9 July 2011
//; Baseline_Bisector and node ranges are in meters
//; Node bearings are in degrees relative to true north
/*DTG = "061855Z 1217"
BASELINE_BISECTOR = 2
NODE0_RANGE = 1.82952
NODE0_BEARING = 46.5192
NODE1_RANGE = 1.82952
NODE1_BEARING = 46.5192
NODE2_RANGE = 1.82952
NODE2_BEARING = 46.5192*/

//=============================================================================
void HeaderFileWindow::bearingsButtonClicked(void)
{
    clearMenu();
    menu = 4;
    label->setText("Bearings");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();


    text1->setGeometry(70, 70, 250, 50);
    text1->setText("Node 0 Range (m)");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(70, 120, 250, 50);
    text2->setText("Node 0 Bearing (dec deg)");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(70, 180, 250, 50);
    text3->setText("Node 1 Range (m)");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(70, 230, 250, 50);
    text4->setText("Node 1 Bearing (dec deg)");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(70, 290, 250, 50);
    text5->setText("Node 2 Range (m)");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(70, 340, 250, 50);
    text6->setText("Node 2 Bearing (dec deg)");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("Bearings", "NODE0_RANGE");
    textbox1->setGeometry(350, 73, 180, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("Bearings", "NODE0_BEARING");
    textbox2->setGeometry(350, 123, 180, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("Bearings", "NODE1_RANGE");
    textbox3->setGeometry(350, 183, 180, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("Bearings", "NODE1_BEARING");
    textbox4->setGeometry(350, 233, 180, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("Bearings", "NODE2_RANGE");
    textbox5->setGeometry(350, 293, 180, 29);
    textbox5->setText(oldVal);
    textbox5->show();

    oldVal = headerarmfiles.readFromHeaderFile("Bearings", "NODE2_BEARING");
    textbox6->setGeometry(350, 343, 180, 29);
    textbox6->setText(oldVal);
    textbox6->show();
}



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
    clearMenu();
    menu = 5;
    label->setText("Weather Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();

    text1->setGeometry(70, 70, 250, 50);
    text1->setText("Douglas Sea State (1-8)");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(70, 120, 250, 50);
    text2->setText("Wind Speed (knots)");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(70, 170, 250, 50);
    text3->setText("Wind Direction (deg)");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(70, 220, 250, 50);
    text4->setText("Wind Height (m)");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(70, 270, 250, 50);
    text5->setText("Wave Direction (deg)");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(70, 320, 250, 50);
    text6->setText("Wave Period (secs)");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();

    text7->setGeometry(70, 370, 250, 50);
    text7->setText("Air Temperature (deg C)");
    text7->setFont(QFont("Ubuntu",14));
    text7->show();

    text8->setGeometry(70, 420, 250, 50);
    text8->setText("Air Pressure (millibar)");
    text8->setFont(QFont("Ubuntu",14));
    text8->show();


    QString oldVal = headerarmfiles.readFromHeaderFile("Weather", "DOUGLAS_SEA_STATE");
    textbox1->setGeometry(350, 73, 180, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("Weather", "WIND_SPEED");
    textbox2->setGeometry(350, 123, 180, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("Weather", "WIND_DIR");
    textbox3->setGeometry(350, 173, 180, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("Weather", "WAVE_HEIGHT");
    textbox4->setGeometry(350, 223, 180, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("Weather", "WAVE_DIR");
    textbox5->setGeometry(350, 273, 180, 29);
    textbox5->setText(oldVal);
    textbox5->show();

    oldVal = headerarmfiles.readFromHeaderFile("Weather", "WAVE_PERIOD");
    textbox6->setGeometry(350, 323, 180, 29);
    textbox6->setText(oldVal);
    textbox6->show();

    oldVal = headerarmfiles.readFromHeaderFile("Weather", "AIR_TEMPERATURE");
    textbox7->setGeometry(350, 373, 180, 29);
    textbox7->setText(oldVal);
    textbox7->show();

    oldVal = headerarmfiles.readFromHeaderFile("Weather", "AIR_PRESSURE");
    textbox8->setGeometry(350, 423, 180, 29);
    textbox8->setText(oldVal);
    textbox8->show();
}



//=============================================================================
// pulseParametersButtonClicked()

//; choose pulse width to use:
//;   LFM              NLFM
//;   0.5us   = 1      0.5us   = 8
//;   1.0us   = 2      1.0us   = 9
//;   3.0us   = 3      3.0us   = 10
//;   5.0us   = 4      5.0us   = 11
//;   10.0us  = 5      10.0us  = 12
//;   15.0us  = 6      15.0us  = 13
//;   20.0us  = 7      20.0us  = 14
//WAVEFORM_INDEX = 5

//; NUM_PRIS = n x m (# unique pulses x # cycles)
//NUM_PRIS = 60000
//SAMPLES_PER_PRI = 4096

//; DAC_DELAY MUST NOT BE LESS THAN 1. See Pentek Operating Manual 3.3.2, page 64. DAC_DELAY is the delay before transmit of the DAC. Actual delay is DAC_DELAY/180MSPS + 186*2/180MSPS (measured)
//DAC_DELAY = 1

//; ADC_DELAY is the delay before recording on the ADCs. Actual delay is ADC_DELAY/180MSPS
//;372
//ADC_DELAY = 5400

//; polarisation mode parameter decoding
//; ------------------------------------
//; Mode    Freq Band     TxPol   RxPol
//; 0           L           V       V
//; 1           L           V       H
//; 2           L           H       V
//; 3           L           H       H
//; 4           X           V       H,V
//; 5           X           H       H,V

//; Order of pulse transmission in a cycle
//; Examples:
//;   "0,1,2,3,4,5" --> 6 pulses (n=6), above table from top to bottom
//;   "0"           --> 1 pulse  (n=1), just single L-band pulse, vertical tx pol, vertical rx pol
//;   "5,4"         --> 2 pulses (n=2), x-band, horizontal tx pol first, then vertical
//POL_ORDER = "0,1,2,3,4,5"

//; Pulse repetition interval in microseconds, resolution of 0.01us
//PRI = 1000

//; Pre-pulse time in microseconds, resolution of 0.01us
//PRE_PULSE = 30

//; waveform frequencies in MHz
//; NOTE: all L-band and X-band waveform frequencies for pulses within a cycle are fixed for now
//; Future work: create key(s) allowing for different L-band and X-band frequencies
//L_BAND_WAVEFORM_FREQ = 1300
//X_BAND_WAVEFORM_FREQ = 8500

//=============================================================================
void HeaderFileWindow::pulseParametersButtonClicked(void)
{
    clearMenu();
    menu = 6;
    label->setText("Pulse Parameters");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();


    //set GUI buttons and textfields appropriately
    text1->setGeometry(70, 70, 250, 50);
    text1->setText("Waveform Index (1-14)");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(70, 120, 250, 50);
    text2->setText("Number of PRIs");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(70, 170, 250, 50);
    text3->setText("Samples per PRI");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(70, 220, 250, 50);
    text4->setText("DAC Delay (no of 180MSPS)");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(70, 270, 250, 50);
    text5->setText("ADC Delay (no of 180MSPS)");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    text6->setGeometry(70, 320, 250, 50);
    text6->setText("Pol Order (e.g. \"0,1,2,3,4,5\")");
    text6->setFont(QFont("Ubuntu",14));
    text6->show();

    text7->setGeometry(70, 370, 250, 50);
    text7->setText("PRI (usecs)");
    text7->setFont(QFont("Ubuntu",14));
    text7->show();

    text8->setGeometry(70, 420, 250, 50);
    text8->setText("Pre Pulse (usecs)");
    text8->setFont(QFont("Ubuntu",14));
    text8->show();

    text9->setGeometry(70, 470, 250, 50);
    text9->setText("L Band Frequency (MHz)");
    text9->setFont(QFont("Ubuntu",14));
    text9->show();

    text10->setGeometry(70, 520, 250, 50);
    text10->setText("X Band Frequency (MHz)");
    text10->setFont(QFont("Ubuntu",14));
    text10->show();


    QString oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "WAVEFORM_INDEX");
    textbox1->setGeometry(350, 73, 180, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "NUM_PRIS");
    textbox2->setGeometry(350, 123, 180, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "SAMPLES_PER_PRI");
    textbox3->setGeometry(350, 173, 180, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "DAC_DELAY");
    textbox4->setGeometry(350, 223, 180, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "ADC_DELAY");
    textbox5->setGeometry(350, 273, 180, 29);
    textbox5->setText(oldVal);
    textbox5->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "POL_ORDER");
    textbox6->setGeometry(350, 323, 180, 29);
    textbox6->setText(oldVal);
    textbox6->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "PRI");
    textbox7->setGeometry(350, 373, 180, 29);
    textbox7->setText(oldVal);
    textbox7->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "PRE_PULSE");
    textbox8->setGeometry(350, 423, 180, 29);
    textbox8->setText(oldVal);
    textbox8->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "L_BAND_WAVEFORM_FREQ");
    textbox9->setGeometry(350, 473, 180, 29);
    textbox9->setText(oldVal);
    textbox9->show();

    oldVal = headerarmfiles.readFromHeaderFile("PulseParameters", "X_BAND_WAVEFORM_FREQ");
    textbox10->setGeometry(350, 523, 180, 29);
    textbox10->setText(oldVal);
    textbox10->show();
}

void HeaderFileWindow::quicklookSettingsButtonClicked(void)
{
    clearMenu();
    menu = 7;
    label->setText("Quicklook");

    //set GUI buttons and textfields appropriately
    cancelButton->setText("Cancel");
    okButton->show();


    //set GUI buttons and textfields appropriately
    text1->setGeometry(50, 70, 250, 50);
    text1->setText("ADC Chan'l (0=L,1=XV,2=XH)");
    text1->setFont(QFont("Ubuntu",14));
    text1->show();

    text2->setGeometry(50, 120, 250, 50);
    text2->setText("Amplifier (MPA=0,HPA=1)");
    text2->setFont(QFont("Ubuntu",14));
    text2->show();

    text3->setGeometry(50, 170, 250, 50);
    text3->setText("Dynamic Range");
    text3->setFont(QFont("Ubuntu",14));
    text3->show();

    text4->setGeometry(50, 220, 250, 50);
    text4->setText("Spectrogram Bin");
    text4->setFont(QFont("Ubuntu",14));
    text4->show();

    text5->setGeometry(50, 270, 250, 50);
    text5->setText("Doppler FFT");
    text5->setFont(QFont("Ubuntu",14));
    text5->show();

    QString oldVal = headerarmfiles.readFromHeaderFile("Quicklook", "ADC_CHANNEL");
    textbox1->setGeometry(350, 73, 180, 29);
    textbox1->setText(oldVal);
    textbox1->show();

    oldVal = headerarmfiles.readFromHeaderFile("Quicklook", "AMPLIFIER");
    textbox2->setGeometry(350, 123, 180, 29);
    textbox2->setText(oldVal);
    textbox2->show();

    oldVal = headerarmfiles.readFromHeaderFile("Quicklook", "DYNAMIC_RANGE");
    textbox3->setGeometry(350, 173, 180, 29);
    textbox3->setText(oldVal);
    textbox3->show();

    oldVal = headerarmfiles.readFromHeaderFile("Quicklook", "SPECTROGRAM_BIN");
    textbox4->setGeometry(350, 223, 180, 29);
    textbox4->setText(oldVal);
    textbox4->show();

    oldVal = headerarmfiles.readFromHeaderFile("Quicklook", "DOPPLER_FFT");
    textbox5->setGeometry(350, 273, 180, 29);
    textbox5->setText(oldVal);
    textbox5->show();

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

    std::string day, month, year, hour, minute, second, value;

    switch(menu)
    {
        case 1://Timing Parameters

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

            showFirstMenu();
        break;

        case 2://Geometry Settings

            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LAT", value);

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LON", value);

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_HT", value);


            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LAT", value);

            value = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LON", value);

            value = textbox6->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_HT", value);


            value = textbox7->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LAT", value);

            value = textbox8->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LON", value);

            value = textbox9->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_HT", value);


            showFirstMenu();
        break;

        case 3://Target Settings
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TargetSettings","TGT_LOCATION_LAT", value);

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TargetSettings","TGT_LOCATION_LON", value);

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("TargetSettings","TGT_LOCATION_HT", value);

            showFirstMenu();
        break;

        case 4://Bearings Parameters

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

        case 5://Weather Parameters

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

        case 6://Pulse Parameters
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "WAVEFORM_INDEX", value);

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "NUM_PRIS", value);

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "SAMPLES_PER_PRI", value);

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "DAC_DELAY", value);

            value = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "ADC_DELAY", value);

            value = textbox6->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "POL_ORDER", value);

            value = textbox7->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "PRI", value);

            value = textbox8->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "PRE_PULSE", value);

            value = textbox9->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "L_BAND_WAVEFORM_FREQ", value);

            value = textbox10->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("PulseParameters", "X_BAND_WAVEFORM_FREQ", value);

            showFirstMenu();
        break;

        case 7://Quicklook Settings ADC
            value = textbox1->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Quicklook", "ADC_CHANNEL", value);

            value = textbox2->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Quicklook", "AMPLIFIER", value);

            value = textbox3->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Quicklook", "DYNAMIC_RANGE", value);

            value = textbox4->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Quicklook", "SPECTROGRAM_BIN", value);

            value = textbox5->toPlainText().toUtf8().constData();
            headerarmfiles.writeToHeaderFile("Quicklook", "DOPPLER_FFT", value);

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
    bearingsButton->hide();
    geometryParametersButton->hide();
    targetPositionSettingsButton->hide();
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
    text13->hide();
    text14->hide();
    text15->hide();

    textbox1->hide();
    textbox2->hide();
    textbox3->hide();
    textbox4->hide();
    textbox5->hide();
    textbox6->hide();
    textbox7->hide();
    textbox8->hide();
    textbox9->hide();
    textbox10->hide();


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




