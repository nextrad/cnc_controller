#include "pulsedialog.h"
#include "ui_pulsedialog.h"

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
PulseDialog::PulseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PulseDialog)
{
    ui->setupUi(this);

    // Populate waveform comboBox
    ui->waveform_comboBox->addItem(" LFM   0.5us =  1");
    ui->waveform_comboBox->addItem(" LFM   1.0us =  2");
    ui->waveform_comboBox->addItem(" LFM   3.0us =  3");
    ui->waveform_comboBox->addItem(" LFM   5.0us =  4");
    ui->waveform_comboBox->addItem(" LFM  10.0us =  5");
    ui->waveform_comboBox->addItem(" LFM  15.0us =  6");
    ui->waveform_comboBox->addItem(" LFM  20.0us =  7");
    ui->waveform_comboBox->addItem("NLFM   0.5us =  8");
    ui->waveform_comboBox->addItem("NLFM   1.0us =  9");
    ui->waveform_comboBox->addItem("NLFM   3.0us = 10");
    ui->waveform_comboBox->addItem("NLFM   5.0us = 11");
    ui->waveform_comboBox->addItem("NLFM  10.0us = 12");
    ui->waveform_comboBox->addItem("NLFM  15.0us = 13");
    ui->waveform_comboBox->addItem("NLFM  20.0us = 14");

    // Set values from Header File

    string str = headerarmfiles.readFromHeaderFile("PulseParameters", "WAVEFORM_INDEX").toStdString();
    int waveform_index = stoi(str);
    ui->waveform_comboBox->setCurrentIndex(waveform_index - 1);

    ui->num_pris->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "NUM_PRIS"));
    ui->samples_per_pri->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "SAMPLES_PER_PRI"));
    ui->dac_delay->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "DAC_DELAY"));
    ui->adc_delay->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "ADC_DELAY"));

    ui->pol_order->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "POL_ORDER"));

    ui->pri->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "PRI"));
    ui->pre_pulse->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "PRE_PULSE"));
    ui->l_band_freq->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "L_BAND_WAVEFORM_FREQ"));
    ui->x_band_freq->setText(headerarmfiles.readFromHeaderFile("PulseParameters", "X_BAND_WAVEFORM_FREQ"));
}

PulseDialog::~PulseDialog()
{
    delete ui;
}

void PulseDialog::on_buttonBox_clicked()
{
    int ivalue;
    string svalue, svalue1;
    stringstream ss;

    ivalue = ui->waveform_comboBox->currentIndex() + 1;
    cout << ivalue << endl;
    ss << ivalue << endl;
    svalue = ss.str();
    headerarmfiles.writeToHeaderFile("PulseParameters", "WAVEFORM_INDEX", svalue);

    svalue = ui->num_pris->toPlainText().toStdString();
    headerarmfiles.writeToHeaderFile("PulseParameters", "NUM_PRIS", svalue);

    svalue = ui->samples_per_pri->toPlainText().toStdString();
    headerarmfiles.writeToHeaderFile("PulseParameters", "SAMPLES_PER_PRI", svalue);

    svalue = ui->dac_delay->toPlainText().toStdString();
    headerarmfiles.writeToHeaderFile("PulseParameters", "DAC_DELAY", svalue);

    svalue = ui->adc_delay->toPlainText().toStdString();
    headerarmfiles.writeToHeaderFile("PulseParameters", "ADC_DELAY", svalue);

    svalue = ui->pol_order->toPlainText().toStdString();
    int len = svalue.length() - 2;
    svalue1 = svalue.substr(0, len) + "\"";
    headerarmfiles.writeToHeaderFile("PulseParameters", "POL_ORDER", svalue1);

    svalue = ui->pri->toPlainText().toStdString();
    headerarmfiles.writeToHeaderFile("PulseParameters", "PRI", svalue);

    svalue = ui->pre_pulse->toPlainText().toStdString();
    headerarmfiles.writeToHeaderFile("PulseParameters", "PRE_PULSE", svalue);

    svalue = ui->l_band_freq->toPlainText().toStdString();
    headerarmfiles.writeToHeaderFile("PulseParameters", "L_BAND_WAVEFORM_FREQ", svalue);

    svalue = ui->x_band_freq->toPlainText().toStdString();
    headerarmfiles.writeToHeaderFile("PulseParameters", "X_BAND_WAVEFORM_FREQ", svalue);

}

void PulseDialog::on_radioButton0_clicked()
{
    if (ss.str() == "")
    {
        ss << "\"";
    }

    ss << "0, ";
    QString pol_order_qstr = QString::fromStdString(ss.str());
    ui->pol_order->setText(pol_order_qstr);
}

void PulseDialog::on_radioButton1_clicked()
{
    if (ss.str() == "")
    {
        ss << "\"";
    }

    ss << "1, ";
    QString pol_order_qstr = QString::fromStdString(ss.str());
    ui->pol_order->setText(pol_order_qstr);
}

void PulseDialog::on_radioButton2_clicked()
{
    if (ss.str() == "")
    {
        ss << "\"";
    }

    ss << "2, ";
    QString pol_order_qstr = QString::fromStdString(ss.str());
    ui->pol_order->setText(pol_order_qstr);
}

void PulseDialog::on_radioButton3_clicked()
{
    if (ss.str() == "")
    {
        ss << "\"";
    }

    ss << "3, ";
    QString pol_order_qstr = QString::fromStdString(ss.str());
    ui->pol_order->setText(pol_order_qstr);
}

void PulseDialog::on_radioButton4_clicked()
{
    if (ss.str() == "")
    {
        ss << "\"";
    }

    ss << "4, ";
    QString pol_order_qstr = QString::fromStdString(ss.str());
    ui->pol_order->setText(pol_order_qstr);
}

void PulseDialog::on_radioButton5_clicked()
{
    if (ss.str() == "")
    {
        ss << "\"";
    }

    ss << "5, ";
    QString pol_order_qstr = QString::fromStdString(ss.str());
    ui->pol_order->setText(pol_order_qstr);
}
