#include "geometrydialog.h"
#include "ui_geometrydialog.h"

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
GeometryDialog::GeometryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeometryDialog)
{
    ui->setupUi(this);

    ui->n0_lat_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE0_LOCATION_LAT"));
    ui->n0_lon_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE0_LOCATION_LON"));
    ui->n0_ht_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE0_LOCATION_HT"));

    ui->n1_lat_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE1_LOCATION_LAT"));
    ui->n1_lon_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE1_LOCATION_LON"));
    ui->n1_ht_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE1_LOCATION_HT"));

    ui->n2_lat_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE2_LOCATION_LAT"));
    ui->n2_lon_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE2_LOCATION_LON"));
    ui->n2_ht_Edit->setText(headerarmfiles.readFromHeaderFile("GeometrySettings", "NODE2_LOCATION_HT"));
}

GeometryDialog::~GeometryDialog()
{
    delete ui;
}

void GeometryDialog::on_buttonBox_clicked()
{

    string n0_lat, n0_lon, n0_ht, n1_lat, n1_lon, n1_ht, n2_lat, n2_lon, n2_ht;

    n0_lat = ui->n0_lat_Edit->toPlainText().toStdString();
    n0_lon = ui->n0_lon_Edit->toPlainText().toStdString();
    n0_ht = ui->n0_ht_Edit->toPlainText().toStdString();

    n1_lat = ui->n1_lat_Edit->toPlainText().toStdString();
    n1_lon = ui->n1_lon_Edit->toPlainText().toStdString();
    n1_ht = ui->n1_ht_Edit->toPlainText().toStdString();

    n2_lat = ui->n2_lat_Edit->toPlainText().toStdString();
    n2_lon = ui->n2_lon_Edit->toPlainText().toStdString();
    n2_ht = ui->n2_ht_Edit->toPlainText().toStdString();

    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LAT", n0_lat);
    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LON", n0_lon);
    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_HT", n0_ht);

    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LAT", n1_lat);
    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LON", n1_lon);
    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_HT", n1_ht);

    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LAT", n2_lat);
    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LON", n2_lon);
    headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_HT", n2_ht);

}

