#ifndef TIMINGDIALOG_H
#define TIMINGDIALOG_H

#include <QDialog>
#include "includes.h"
#include "datetime.h"
#include "header_arm_files.h"
#include <math.h>

namespace Ui {
class TimingDialog;
}

class TimingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimingDialog(QWidget *parent = 0);
    ~TimingDialog();

private slots:
     int on_buttonBox_clicked();

private:
    Ui::TimingDialog *ui;

    HeaderArmFiles headerarmfiles;
};

#endif // TIMINGDIALOG_H
