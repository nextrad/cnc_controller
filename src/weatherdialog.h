#ifndef WEATHERDIALOG_H
#define WEATHERDIALOG_H

#include <QDialog>
#include "includes.h"
#include "datetime.h"
#include "header_arm_files.h"

namespace Ui {
class WeatherDialog;
}

class WeatherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WeatherDialog(QWidget *parent = 0);
    ~WeatherDialog();

private slots:
    void on_buttonBox_clicked();

private:
    Ui::WeatherDialog *ui;

    HeaderArmFiles headerarmfiles;
};

#endif // WEATHERDIALOG_H
