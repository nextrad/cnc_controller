#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

class DigitalClock : public QLCDNumber
{
    Q_OBJECT

public:
    DigitalClock(QWidget *parent = 0);

private slots:
    void showTime();
};

#endif // DIGITALCLOCK_H
