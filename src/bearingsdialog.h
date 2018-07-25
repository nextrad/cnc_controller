#ifndef BEARINGSDIALOG_H
#define BEARINGSDIALOG_H

#include <QDialog>
#include "includes.h"
#include "datetime.h"
#include "header_arm_files.h"


namespace Ui {
class BearingsDialog;
}

class BearingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BearingsDialog(QWidget *parent = 0);
    ~BearingsDialog();

private slots:
    void on_buttonBox_clicked();

private:
    Ui::BearingsDialog *ui;

    HeaderArmFiles headerarmfiles;
};

#endif // BEARINGSDIALOG_H
