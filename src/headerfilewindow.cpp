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

// [PulseParameters]
// ; choose pulse width to use:
// ;   LFM              NLFM
// ;   0.5us   = 1      0.5us   = 8
// ;   1.0us   = 2      1.0us   = 9
// ;   3.0us   = 3      3.0us   = 10
// ;   5.0us   = 4      5.0us   = 11
// ;   10.0us  = 5      10.0us  = 12
// ;   15.0us  = 6      15.0us  = 13
// ;   20.0us  = 7      20.0us  = 14
// WAVEFORM_INDEX = 11
//
// ; NUM_PRIS = n x m (# unique pulses x # cycles)
// NUM_PRIS = 300000
// SAMPLES_PER_PRI = 2048
//
// ; DAC_DELAY MUST NOT BE LESS THAN 1. See Pentek Operating Manual 3.3.2, page 64. DAC_DELAY is the delay before transmit of the DAC. Actual delay is DAC_DELAY/180MSPS + 186*2/180MSPS (measured)
// DAC_DELAY = 1
//
// ; ADC_DELAY is the delay before recording on the ADCs. Actual delay is ADC_DELAY/180MSPS
// ;372
// ADC_DELAY = 372
//
// ; Pre-pulse time in microseconds, resolution of 0.01us
// PRE_PULSE = 30
//
// ; Pulse width of the PRI signal sent from the TCU to the REX in microseconds (e.g. '500' for 0.5ms)
// PRI_PULSE_WIDTH = 500
//
// ; Switch-off delay for the X-band amplifier switch in microseconds
// X_AMP_DELAY = 3.5
//
// ; Switch-off delay for the L-band amplifier switch in microseconds
// L_AMP_DELAY = 1.0
//
// ; Polarisation mode parameter decoding
// ; ------------------------------------
// ; Mode    Freq Band     TxPol   RxPol
// ; 0           L           V       V
// ; 1           L           V       H
// ; 2           L           H       V
// ; 3           L           H       H
// ; 4           X           V       H,V
// ; 5           X           H       H,V
//
// ; PULSE_x   =   [Pulse Width, PRI, Polarisation Mode, Waveform Frequency]
//
// ;       Pulse Width         = RF Pulse width in microseconds (e.g. '10.0'). This should correspond with WAVEFORM_INDEX for now, as only one pulse width is used in an experiment
// ;       PRI                 = Time between adjacent pulses in microseconds (e.g. '1000.0' for 1ms)
// ;       Polarisation Mode   = see "Polarisation mode parameter decoding" table (e.g. '2' for horizontal transmission, vertical reception)
// ;       Waveform Frequency  = Operating frequency of RF waveform in MHz (e.g. '1300' for L-band, '8500' for X-band)
//
// ; PULSES    =   [PULSE_0|PULSE_1|...|PULSE_n], n = number of unique pulses
// PULSES = "10.0,250.0,0,1300.0|10.0,250.0,1,1300.0|10.0,250.0,2,1300.0|10.0,250.0,3,1300.0"

//=============================================================================
void HeaderFileWindow::on_pulseParametersButton_clicked()
{
    try
    {
        // launch tcu_creator.py GUI to allow user to configure TCU parameters
        // this will output a PulseParams.ini file
        stringstream ss;
        int ret;
        int status;

        ss << "../scripts/tcu/tcu_v2/tcu_creator.py ";
        ss << " -f" << PULSE_PARAMS_PATH  << endl;
        cout << ss.str() << endl;
        status = system(ss.str().c_str());

        if (-1 != status)
        {
            ret = WEXITSTATUS(status);

            if(ret==0)
            {
                cout << "tcu_creator successful\n" << endl;
            }
            else
            {
                cout << "tcu_creator FAILED" << endl;
            }
        }
        ss.str("");

        // read PulseParams.ini
        string waveform_index_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "WAVEFORM_INDEX");
        string num_pris_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "NUM_PRIS");
        string dac_delay_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "DAC_DELAY");
        string adc_delay_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "ADC_DELAY");
        string pre_pulse_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "PRE_PULSE");
        string pri_pulse_width_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "PRI_PULSE_WIDTH");
        string x_amp_delay_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "X_AMP_DELAY");
        string l_amp_delay_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "L_AMP_DELAY");
        string pulses_str = headerarmfiles.readFromPulseParamsFile("PulseParameters", "PULSES");

        // update NeXtRAD.ini
        headerarmfiles.writeToHeaderFile("PulseParameters", "WAVEFORM_INDEX", waveform_index_str);
        headerarmfiles.writeToHeaderFile("PulseParameters", "NUM_PRIS", num_pris_str);
        headerarmfiles.writeToHeaderFile("PulseParameters", "DAC_DELAY", dac_delay_str);
        headerarmfiles.writeToHeaderFile("PulseParameters", "ADC_DELAY", adc_delay_str);
        headerarmfiles.writeToHeaderFile("PulseParameters", "PRE_PULSE", pre_pulse_str);
        headerarmfiles.writeToHeaderFile("PulseParameters", "PRI_PULSE_WIDTH", pri_pulse_width_str);
        headerarmfiles.writeToHeaderFile("PulseParameters", "X_AMP_DELAY", x_amp_delay_str);
        headerarmfiles.writeToHeaderFile("PulseParameters", "L_AMP_DELAY", l_amp_delay_str);
        headerarmfiles.writeToHeaderFile("PulseParameters", "PULSES", pulses_str);
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

//[Bearings]
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
