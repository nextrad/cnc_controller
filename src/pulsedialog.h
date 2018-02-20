#ifndef PULSEDIALOG_H
#define PULSEDIALOG_H

#include <QDialog>
#include "includes.h"
#include "datetime.h"
#include "header_arm_files.h"

namespace Ui {
class PulseDialog;
}

class PulseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PulseDialog(QWidget *parent = 0);
    ~PulseDialog();

private slots:
    void on_buttonBox_clicked();

    void on_radioButton0_clicked();

    void on_radioButton1_clicked();

    void on_radioButton2_clicked();

    void on_radioButton3_clicked();

    void on_radioButton4_clicked();

    void on_radioButton5_clicked();

private:
    Ui::PulseDialog *ui;

    HeaderArmFiles headerarmfiles;

    std::string pol_order_str;
};

#endif // PULSEDIALOG_H
