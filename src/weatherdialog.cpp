#include "weatherdialog.h"
#include "ui_weatherdialog.h"

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
WeatherDialog::WeatherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeatherDialog)
{
    ui->setupUi(this);

    ui->douglas_sea_state_Edit->setText(headerarmfiles.readFromHeaderFile("Weather", "DOUGLAS_SEA_STATE"));
    ui->wind_speed_Edit->setText(headerarmfiles.readFromHeaderFile("Weather", "WIND_SPEED"));
    ui->wind_dir_Edit->setText(headerarmfiles.readFromHeaderFile("Weather", "WIND_DIR"));
    ui->wave_height_Edit->setText(headerarmfiles.readFromHeaderFile("Weather", "WAVE_HEIGHT"));
    ui->wave_dir_Edit->setText(headerarmfiles.readFromHeaderFile("Weather", "WAVE_DIR"));
    ui->wave_period_Edit->setText(headerarmfiles.readFromHeaderFile("Weather", "WAVE_PERIOD"));
    ui->air_temp_Edit->setText(headerarmfiles.readFromHeaderFile("Weather", "AIR_TEMPERATURE"));
    ui->air_pressure_Edit->setText(headerarmfiles.readFromHeaderFile("Weather", "AIR_PRESSURE"));
}

WeatherDialog::~WeatherDialog()
{
    delete ui;
}

void WeatherDialog::on_buttonBox_clicked()
{

    string douglas_sea_state, wind_speed, wind_dir, wave_height, wave_dir, wave_period, air_temp, air_pressure;

    douglas_sea_state = ui->douglas_sea_state_Edit->toPlainText().toStdString();
    wind_speed = ui->wind_speed_Edit->toPlainText().toStdString();
    wind_dir = ui->wind_dir_Edit->toPlainText().toStdString();
    wave_height = ui->wave_height_Edit->toPlainText().toStdString();
    wave_dir = ui->wave_dir_Edit->toPlainText().toStdString();
    wave_period = ui->wave_period_Edit->toPlainText().toStdString();
    air_temp = ui->air_temp_Edit->toPlainText().toStdString();
    air_pressure = ui->air_pressure_Edit->toPlainText().toStdString();

    headerarmfiles.writeToHeaderFile("Weather", "DOUGLAS_SEA_STATE", douglas_sea_state);
    headerarmfiles.writeToHeaderFile("Weather", "WIND_SPEED", wind_speed);
    headerarmfiles.writeToHeaderFile("Weather", "WIND_DIR", wind_dir);
    headerarmfiles.writeToHeaderFile("Weather", "WAVE_HEIGHT", wave_height);
    headerarmfiles.writeToHeaderFile("Weather", "WAVE_DIR", wave_dir);
    headerarmfiles.writeToHeaderFile("Weather", "WAVE_PERIOD", wave_period);
    headerarmfiles.writeToHeaderFile("Weather", "AIR_TEMPERATURE", air_temp);
    headerarmfiles.writeToHeaderFile("Weather", "AIR_PRESSURE", air_pressure);
}
