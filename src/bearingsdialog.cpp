#include "bearingsdialog.h"
#include "ui_bearingsdialog.h"

//[Bearings]

//; DTG is date-time (in date-time group format) of getting bearings. EXAMPLE: 091630Z JUL 11 = 1630 UTC on 9 July 2011
//; Node bearings are in degrees relative to true north
//DTG = "061855Z 1217"
//N0_RANGE = 1.82952
//N0_BEARING = 46.5192
//N1_RANGE = 1.82952
//N1_BEARING = 46.5192
//N2_RANGE = 1.82952
//N2_BEARING = 46.5192


BearingsDialog::BearingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BearingsDialog)
{
    ui->setupUi(this);

    ui->dtg_Edit->setText(headerarmfiles.readFromHeaderFile("Bearings", "DTG"));

    ui->node0_range_Edit->setText(headerarmfiles.readFromHeaderFile("Bearings", "NODE0_RANGE"));
    ui->node0_bearing_Edit->setText(headerarmfiles.readFromHeaderFile("Bearings", "NODE0_BEARING"));

    ui->node1_range_Edit->setText(headerarmfiles.readFromHeaderFile("Bearings", "NODE1_RANGE"));
    ui->node1_bearing_Edit->setText(headerarmfiles.readFromHeaderFile("Bearings", "NODE1_BEARING"));

    ui->node2_range_Edit->setText(headerarmfiles.readFromHeaderFile("Bearings", "NODE2_RANGE"));
    ui->node2_bearing_Edit->setText(headerarmfiles.readFromHeaderFile("Bearings", "NODE2_BEARING"));

}

BearingsDialog::~BearingsDialog()
{
    delete ui;
}

void BearingsDialog::on_buttonBox_clicked()
{

    string dtg, node0_range, node0_bearing, node1_range, node1_bearing, node2_range, node2_bearing;

    dtg = ui->dtg_Edit->toPlainText().toStdString();

    node0_range = ui->node0_range_Edit->toPlainText().toStdString();
    node0_bearing = ui->node0_bearing_Edit->toPlainText().toStdString();

    node1_range = ui->node1_range_Edit->toPlainText().toStdString();
    node1_bearing = ui->node1_bearing_Edit->toPlainText().toStdString();

    node2_range = ui->node2_range_Edit->toPlainText().toStdString();
    node2_bearing = ui->node2_bearing_Edit->toPlainText().toStdString();

    headerarmfiles.writeToHeaderFile("Bearings", "DTG", dtg);

    headerarmfiles.writeToHeaderFile("Bearings", "NODE0_RANGE", node0_range);
    headerarmfiles.writeToHeaderFile("Bearings", "NODE0_BEARING", node0_bearing);

    headerarmfiles.writeToHeaderFile("Bearings", "NODE1_RANGE", node1_range);
    headerarmfiles.writeToHeaderFile("Bearings", "NODE1_BEARING", node1_bearing);

    headerarmfiles.writeToHeaderFile("Bearings", "NODE2_RANGE", node2_range);
    headerarmfiles.writeToHeaderFile("Bearings", "NODE2_BEARING", node2_bearing);

}
