#include "targetdialog.h"
#include "ui_targetdialog.h"

//=============================================================================
// targetPositionSettingsButtonClicked()

//[TargetSettings]
//; lats and longs are in decimal degrees
//; height is in meters as WGS84 and above geoid

/*TGT_LOCATION_LAT = -34.1874
TGT_LOCATION_LON = 18.4280
TGT_LOCATION_HT = 0*/
//=============================================================================
TargetDialog::TargetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetDialog)
{
    ui->setupUi(this);

    ui->latEdit->setText(headerarmfiles.readFromHeaderFile("TargetSettings", "TGT_LOCATION_LAT"));
    ui->lonEdit->setText(headerarmfiles.readFromHeaderFile("TargetSettings", "TGT_LOCATION_LON"));
    ui->htEdit->setText(headerarmfiles.readFromHeaderFile("TargetSettings", "TGT_LOCATION_HT"));
}

TargetDialog::~TargetDialog()
{
    delete ui;
}

void TargetDialog::on_buttonBox_clicked()
{
    string lat, lon, ht;

    lat = ui->latEdit->toPlainText().toUtf8().constData();
    lon = ui->lonEdit->toPlainText().toUtf8().constData();
    ht = ui->htEdit->toPlainText().toUtf8().constData();

    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_LAT", lat);
    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_LON", lon);
    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_HT", ht);
}
