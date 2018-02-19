#ifndef TARGETDIALOG_H
#define TARGETDIALOG_H

#include <QDialog>
#include "includes.h"
#include "datetime.h"
#include "header_arm_files.h"

namespace Ui {
class TargetDialog;
}

class TargetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TargetDialog(QWidget *parent = 0);
    ~TargetDialog();

private slots:
    void on_buttonBox_clicked();

private:
    Ui::TargetDialog *ui;

    HeaderArmFiles headerarmfiles;
};

#endif // TARGETDIALOG_H
