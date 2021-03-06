#include "timingdialog.h"
#include "ui_timingdialog.h"

//[Timing]
//; Time that experiment starts
//; Local time (SAST: UTC+2)
//YEAR    = 2017
//MONTH   = 12
//DAY     = 11
//HOUR    = 16
//MINUTE  = 20
//SECOND  = 00
//STARTTIMESECS = 60


TimingDialog::TimingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimingDialog)
{

    ui->setupUi(this);

    // Populate comboboxes

    QString qsvalue;
    stringstream ss;

    // year
    for (int i = 2018; i < 2031; i++)
    {
        ss << i;
        qsvalue = QString::fromStdString(ss.str());
        ui->yearcomboBox->addItem(qsvalue);
        ss.str("");             //clear stringstream
    }

    // (month or day) < 10
    for (int i = 1; i < 10; i++)
    {
        ss << "0" << i;
        qsvalue = QString::fromStdString(ss.str());
        ui->monthcomboBox->addItem(qsvalue);
        ui->daycomboBox->addItem(qsvalue);
        ss.str("");             //clear stringstream
    }

    // (month or day) between 10 and 12
    for (int i = 10; i < 13; i++)
    {
        ss << i;
        qsvalue = QString::fromStdString(ss.str());
        ui->monthcomboBox->addItem(qsvalue);
        ui->daycomboBox->addItem(qsvalue);
        ss.str("");             //clear stringstream
    }

    // (month or day) from 13 to 31
    for (int i = 13; i < 32; i++)
    {
        ss << i;
        qsvalue = QString::fromStdString(ss.str());
        ui->daycomboBox->addItem(qsvalue);
        ss.str("");             //clear stringstream
    }

    // (hour, minute or second) < 10
    for (int i = 0; i < 10; i++)
    {
        ss << "0" << i;
        qsvalue = QString::fromStdString(ss.str());
        ui->hourcomboBox->addItem(qsvalue);
        ui->minutecomboBox->addItem(qsvalue);
        ui->secondcomboBox->addItem(qsvalue);
        ss.str("");             //clear stringstream
    }

    // (hour, minute or second) < between 10 and 23
    for (int i = 10; i < 24; i++)
    {
        ss << i;
        qsvalue = QString::fromStdString(ss.str());
        ui->hourcomboBox->addItem(qsvalue);
        ui->minutecomboBox->addItem(qsvalue);
        ui->secondcomboBox->addItem(qsvalue);
        ss.str("");             //clear stringstream
    }

    // (hour, minute or second) < between 24 and 59
    for (int i = 24; i < 60; i++)
    {
        ss << i;
        qsvalue = QString::fromStdString(ss.str());
        ui->minutecomboBox->addItem(qsvalue);
        ui->secondcomboBox->addItem(qsvalue);
        ss.str("");             //clear stringstream
    }


    // Get current nowplussecs

    Datetime datetime;
    string str;

    int year, month, day, hour, minute, second, starttimesecs;

    // This time rolls over if add seconds
    string starttimesecsstr = headerarmfiles.readFromHeaderFile("Timing", "STARTTIMESECS").toStdString();
    starttimesecs = stoi(starttimesecsstr);
    string nowplussecs = datetime.getNowPlusSecs(starttimesecs);

    ss << nowplussecs.substr(0,4) << endl;
    str = ss.str();
    ss.str("");             //clear stringstream
    year = stoi(str);

    ss << nowplussecs.substr(5,2) << endl;
    str = ss.str();
    ss.str("");             //clear stringstream
    month = stoi(str);

    ss << nowplussecs.substr(8,2) << endl;
    str = ss.str();
    ss.str("");             //clear stringstream
    day = stoi(str);

    ss << nowplussecs.substr(11,2) << endl;
    str = ss.str();
    ss.str("");             //clear stringstream
    hour = stoi(str);

    ss << nowplussecs.substr(14,2) << endl;
    str = ss.str();
    ss.str("");             //clear stringstream
    minute = stoi(str);

    ss << nowplussecs.substr(17,2) << endl;
    str = ss.str();
    ss.str("");             //clear stringstream
    second = stoi(str);

    // Set combox boxes to current nowplussecs
    ui->yearcomboBox->setCurrentIndex(year - 2018);
    ui->monthcomboBox->setCurrentIndex(month - 1);
    ui->daycomboBox->setCurrentIndex(day - 1);
    ui->hourcomboBox->setCurrentIndex(hour);
    ui->minutecomboBox->setCurrentIndex(minute);
    ui->secondcomboBox->setCurrentIndex(second);
    ui->starttimeedit->setText(QString::fromStdString(starttimesecsstr));

}

TimingDialog::~TimingDialog()
{
    delete ui;
}


int TimingDialog::on_buttonBox_clicked()
{
    string year, month, day, hour, minute, second, starttime;
    stringstream ss;

    ss << ui->yearcomboBox->currentIndex() + 2018 << endl;
    year = ss.str();
    ss.str("");             //clear stringstream

    ss << setfill('0') << setw(2) << ui->monthcomboBox->currentIndex() + 1 << endl;
    month = ss.str();
    ss.str("");             //clear stringstream

    ss << setfill('0') << setw(2) << ui->daycomboBox->currentIndex() + 1 << endl;
    day = ss.str();
    ss.str("");             //clear stringstream

    ss << setfill('0') << setw(2) << ui->hourcomboBox->currentIndex() << endl;
    hour = ss.str();
    ss.str("");             //clear stringstream

    ss << setfill('0') << setw(2) << ui->minutecomboBox->currentIndex() << endl;
    minute = ss.str();
    ss.str("");             //clear stringstream

    ss << setfill('0') << setw(2) << ui->secondcomboBox->currentIndex() << endl;
    second = ss.str();
    ss.str("");             //clear stringstream

    ss << ui->starttimeedit->toPlainText().toStdString() << endl;
    starttime = ss.str();
    ss.str("");             //clear stringstream

    headerarmfiles.writeToHeaderFile("Timing", "YEAR", year);
    headerarmfiles.writeToHeaderFile("Timing", "MONTH", month);
    headerarmfiles.writeToHeaderFile("Timing", "DAY", day);
    headerarmfiles.writeToHeaderFile("Timing", "HOUR", hour);
    headerarmfiles.writeToHeaderFile("Timing", "MINUTE", minute);
    headerarmfiles.writeToHeaderFile("Timing", "SECOND", second);
    headerarmfiles.writeToHeaderFile("Timing", "STARTTIMESECS", starttime);

    return 0;
}


