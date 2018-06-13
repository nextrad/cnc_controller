//Class:        HeaderFileWindow
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       David Bissett
//Created:      April 2016
//Version       1.0 (June 2016)
//Edited by:    Shirley Coetzee
//Revision      2.0 (December 2016)
//Edited by:    Shirley Coetzee
//Revision      3.0 (December 2017)
//Edited by:    Shirley Coetzee
//Revision      4.0 (February 2018)

//=============================================================================
// Includes
//=============================================================================
#include <QPushButton>
#include <QApplication>
#include <QDateTime>
#include <QStyleOption>
#include "headerfilewindow.h"
#include "ui_headerfilewindow.h"


//=============================================================================
// Constructor
//=============================================================================
HeaderFileWindow::HeaderFileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HeaderFileWindow)
{
    ui->setupUi(this);
}


//=============================================================================
// Destructor
//=============================================================================
HeaderFileWindow::~HeaderFileWindow()
{
    delete ui;
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
void HeaderFileWindow::on_timingParametersButton_clicked()
{
    try
    {
        timingdialog = new TimingDialog(this);
        timingdialog->show();

    }
    catch (exception &e)
    {
        cout << "on_timingParametersButton_clicked() exception: " << e.what() << endl;
    }
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
void HeaderFileWindow::on_pulseParametersButton_clicked()
{
    try
    {
        cout << "BRAD NEEDS TO IMPLEMENT THIS!: " << endl;

        // Brad Kahn - replace this code below with a system call (see examples in mainwindow.cpp) to call your code !!!

        // call brads python gui to edit pulse params
        // this generates a temp pulseparams.ini

        // cpp needs to read this pulseparams.ini and update NeXtRAD.ini
         //   readFromPulseParamsFile('param1')

        // string num_pris_str = headerarmfiles.readFromHeaderFile("PulseParameters", "NUM_PRIS");
        // string other_stuffs_str = headerarmfiles.readFromHeaderFile("PulseParameters", "OTHER_STUFFS");

        // headerarmfiles.writeToHeaderFile("PulseParameters", "NUM_PRIS", num_pris_str);
        // headerarmfiles.writeToHeaderFile("PulseParameters", "NUM_PRIS", other_stuffs_str);


//        old code before June 2018.
//        pulsedialog = new PulseDialog(this);
//        pulsedialog->show();
    }
    catch (exception &e)
    {
        cout << "on_pulseParametersButton_clicked() exception: " << e.what() << endl;
    }
}


//=============================================================================
// targetPositionSettingsButtonClicked()

//[TargetSettings]
//; lats and longs are in decimal degrees
//; height is in meters as WGS84 and above geoid

//TGT_LOCATION_LAT = -34.1874
//TGT_LOCATION_LON = 18.4280
//TGT_LOCATION_HT = 0
//=============================================================================
void HeaderFileWindow::on_targetPositionSettingsButton_clicked()
{
    try
    {
        targetdialog = new TargetDialog(this);
        targetdialog->show();
    }
    catch (exception &e)
    {
        cout << "on_targetPositionSettingsButton_clicked() exception: " << e.what() << endl;
    }
}


//=============================================================================
// bearingsButtonClicked()

//Bearings]
//; DTG is date-time (in date-time group format) of getting bearings. EXAMPLE: 091630Z JUL 11 = 1630 UTC on 9 July 2011
//; Baseline_Bisector and node ranges are in meters
//; Node bearings are in degrees relative to true north
//DTG = "061855Z 1217"
//NODE0_RANGE = 1.82952
//NODE0_BEARING = 46.5192
//NODE1_RANGE = 1.82952
//NODE1_BEARING = 46.5192
//NODE2_RANGE = 1.82952
//NODE2_BEARING = 46.5192

//=============================================================================
void HeaderFileWindow::on_bearingsButtonClicked_clicked()
{
    try
    {
        bearingsdialog = new BearingsDialog(this);
        bearingsdialog->show();
    }
    catch (exception &e)
    {
        cout << "on_bearingsButtonClicked_clicked() exception: " << e.what() << endl;
    }
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
void HeaderFileWindow::on_weatherParametersButton_clicked()
{
    try
    {
        weatherdialog = new WeatherDialog(this);
        weatherdialog->show();
    }
    catch (exception &e)
    {
        cout << "on_weatherParametersButton_clicked() exception: " << e.what() << endl;
    }
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
void HeaderFileWindow::on_geometryParametersButton_clicked()
{
    try
    {
        geometrydialog = new GeometryDialog(this);
        geometrydialog->show();
    }
    catch (exception &e)
    {
        cout << "on_geometryParametersButton_clicked() exception: " << e.what() << endl;
    }
}


//=============================================================================
//quicklookSettingsButton()

//[Quicklook]
//ADC_CHANNEL 0 = L, 1 = X, 2 = X
//AMPLIFIER = (MPA = 0, HPA = 1)
//DYNAMIC_RANGE = 50
//SPECTROGRAM_BIN = 1000
//DOPPLER_FFT = 256
//=============================================================================
void HeaderFileWindow::on_quicklookSettingsButton_clicked()
{
    try
    {
        quicklookdialog = new QuicklookDialog(this);
        quicklookdialog->show();
    }
    catch (exception &e)
    {
        cout << "on_quicklookSettingsButton_clicked() exception: " << e.what() << endl;
    }
}




