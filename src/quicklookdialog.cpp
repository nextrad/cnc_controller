#include "quicklookdialog.h"
#include "ui_quicklookdialog.h"

//=============================================================================
//quicklookSettingsButton()

//[Quicklook]

//; ADC_CHANNEL 0 = L, 1 = X, 2 = X
//ADC_CHANNEL = 0

//; MPA = 0, HPA = 1
//AMPLIFIER = 1

//DYNAMIC_RANGE = 50
//SPECTROGRAM_BIN = 1000
//DOPPLER_FFT = 256
//=============================================================================
QuicklookDialog::QuicklookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuicklookDialog)
{
    ui->setupUi(this);

    int adc_channel, amplifier;

    adc_channel = stoi(headerarmfiles.readFromHeaderFile("Quicklook", "ADC_CHANNEL").toStdString());
    cout << "adc_channel = " << adc_channel << endl;
    switch (adc_channel)
    {
    case 0:
        ui->adc_channel_0_radioButton->setChecked(true);
        break;
    case 1:
        ui->adc_channel_1_radioButton->setChecked(true);
        break;
    case 2:
        ui->adc_channel_2_radioButton->setChecked(true);
        break;
    }

    amplifier = stoi(headerarmfiles.readFromHeaderFile("Quicklook", "AMPLIFIER").toStdString());
    cout << "amplifier = " << amplifier << endl;
    switch (amplifier)
    {
    case 0:
        ui->amplifier_0_radioButton->setChecked(true);
        break;
    case 1:
        ui->amplifier_1_radioButton->setChecked(true);
        break;
    }

    ui->dynamic_range_Edit->setText(headerarmfiles.readFromHeaderFile("Quicklook", "DYNAMIC_RANGE"));
    ui->spectrogram_bin_Edit->setText(headerarmfiles.readFromHeaderFile("Quicklook", "SPECTROGRAM_BIN"));
    ui->doppler_fft_Edit->setText(headerarmfiles.readFromHeaderFile("Quicklook", "DOPPLER_FFT"));

}

QuicklookDialog::~QuicklookDialog()
{
    delete ui;
}

void QuicklookDialog::on_buttonBox_clicked()
{
    string adc_channel, amplifier, dynamic_range, spectrogram_bin, doppler_fft;

    if (ui->adc_channel_0_radioButton->isChecked())
    {
        adc_channel = "0";
    }
    else if (ui->adc_channel_1_radioButton->isChecked())
    {
        adc_channel = "1";
    }
    else if (ui->adc_channel_2_radioButton->isChecked())
    {
        adc_channel = "2";
    }

    if (ui->amplifier_0_radioButton->isChecked())
    {
        amplifier = "0";
    }
    else if (ui->amplifier_1_radioButton->isChecked())
    {
        amplifier = "1";
    }

    dynamic_range = ui->dynamic_range_Edit->toPlainText().toStdString();
    spectrogram_bin = ui->spectrogram_bin_Edit->toPlainText().toStdString();
    doppler_fft = ui->doppler_fft_Edit->toPlainText().toStdString();

    headerarmfiles.writeToHeaderFile("Quicklook", "ADC_CHANNEL", adc_channel);
    headerarmfiles.writeToHeaderFile("Quicklook", "AMPLIFIER", amplifier);
    headerarmfiles.writeToHeaderFile("Quicklook", "DYNAMIC_RANGE", dynamic_range);
    headerarmfiles.writeToHeaderFile("Quicklook", "SPECTROGRAM_BIN", spectrogram_bin);
    headerarmfiles.writeToHeaderFile("Quicklook", "DOPPLER_FFT", doppler_fft);
}


