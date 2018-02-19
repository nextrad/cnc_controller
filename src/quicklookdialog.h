#ifndef QUICKLOOKDIALOG_H
#define QUICKLOOKDIALOG_H

#include <QDialog>
#include "includes.h"
#include "datetime.h"
#include "header_arm_files.h"

namespace Ui {
class QuicklookDialog;
}

class QuicklookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuicklookDialog(QWidget *parent = 0);
    ~QuicklookDialog();

private slots:
    void on_buttonBox_clicked();


private:
    Ui::QuicklookDialog *ui;

    HeaderArmFiles headerarmfiles;
};

#endif // QUICKLOOKDIALOG_H
