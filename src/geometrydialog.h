#ifndef GEOMETRYDIALOG_H
#define GEOMETRYDIALOG_H

#include <QDialog>
#include "includes.h"
#include "datetime.h"
#include "header_arm_files.h"

namespace Ui {
class GeometryDialog;
}

class GeometryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeometryDialog(QWidget *parent = 0);
    ~GeometryDialog();

private slots:
    void on_buttonBox_clicked();

private:
    Ui::GeometryDialog *ui;

    HeaderArmFiles headerarmfiles;
};

#endif // GEOMETRYDIALOG_H
