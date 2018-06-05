//Revision      2.0 (December 2016)
//Edited by:    Shirley Coetzee
//Revision      3.0 (January, February 2017)
//Edited by:    Shirley Coetzee
//Revision      4.0 (November 2017)
//Edited by:    Shirley Coetzee and Darryn Jordan
//Revision      5.0 (December 2017)
//Edited by:    Shirley Coetzee, Darryn Jordan, Brad Kahn and Simon Lewis
//Revision      6.0 (Jan/Feb 2018)
//Edited by:    Shirley Coetzee
//Revision      7.0 (Feb 2018)


//=============================================================================
// Includes
//=============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QApplication>
#include <QDateTime>
#include <QString>

#define DEBUG "goLater"

extern int EXPERIMENT_LENGTH; //in seconds


//=============================================================================
// Constructor
//=============================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    experiment_state = INACTIVE; //see enum for explanation

    resetHeaderFileTimes();

    ui->setupUi(this);

    ui->Countdown->display("00:00:00");

    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());

#ifdef DEBUG
    ui->goLaterButton->show();
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
#else
    ui->goLaterButton->hide();
#endif

    //connect to asterisk server and set up audio recording
    audioRecorder.connectToSocket();
    audioRecorder.loginAMI();
    audioRecorder.stopRecording();

    //start timer calls startRecording() once it reaches the start time (happens once)
    starttimer = new QTimer(this);
    starttimer->setSingleShot(true);
    connect(starttimer, SIGNAL(timeout()), this, SLOT(startRecording()));

    //end timer calls stopRecording() once it reaches the end time (happens once)
    endtimer = new QTimer(this);
    endtimer->setSingleShot(true);
    connect(endtimer, SIGNAL(timeout()), this, SLOT(stopRecording()));

    //the count down timer calls updateCountDownLCD() every second
    countdowntimer = new QTimer(this);
    countdowntimer->setInterval(1000);
    connect(countdowntimer, SIGNAL(timeout()), this, SLOT(updateCountDownLCD()));
    countdowntimer->start(1000);

}

//=============================================================================
// Destructor
//=============================================================================
MainWindow::~MainWindow()
{
    delete ui;
}


//=============================================================================
// editHeaderFileButton()
// Edits the Header File using several windows
//=============================================================================
void MainWindow::on_editHeaderFileButton_clicked()
{
    headerfilewindow = new HeaderFileWindow(this);
    headerfilewindow->show();

    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->countdownLabel->setText("");
}



//=============================================================================
// on_testConnectionButton_clicked()
// Tests the connections to CNC
//=============================================================================
void MainWindow::on_testConnectionButton_clicked()
{
    testSubNetwork("1");
    testSubNetwork("2");
    testSubNetwork("3");

    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    ui->countdownLabel->setText("");
}

//=============================================================================
// testSubNetwork()
// Tests the connections to CNC
//=============================================================================
void MainWindow::testSubNetwork(QString NetID)
{
    string temp, name;
    string address = "192.168.1.";
    address.append(NetID.toUtf8().constData());
    NetID = QString::number(NetID.toInt() - 1);    //This is because the node numbering actually starts from zero.

    //Test if Access Point bullet is connected
    name = "ap";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("2");
    if(!testConnection(temp))
    {
        ui->statusBox->setTextColor("red");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        ui->statusBox->setTextColor("green");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if STAtion bullet is connected
    name = "sta";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("3");
    if(!testConnection(temp))
    {
        ui->statusBox->setTextColor("red");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        ui->statusBox->setTextColor("green");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if PoE Switch is connected
    name = "switch";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("0");
    if(!testConnection(temp))
    {
        ui->statusBox->setTextColor("red");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        ui->statusBox->setTextColor("green");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if Node Laptop is connected
    name = "node";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("1");
    if(!testConnection(temp))
    {
        ui->statusBox->setTextColor("red");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        ui->statusBox->setTextColor("green");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if IP camera is connected
    name = "cam";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("4");
    if(!testConnection(temp))                   //Cameras have no ssh port and more security so it's easier to ping them
    {
        ui->statusBox->setTextColor("red");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        ui->statusBox->setTextColor("green");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if Cobalt is connected
    name = "cobalt";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("5");
    if(!testConnection(temp))
    {
        ui->statusBox->setTextColor("red");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        ui->statusBox->setTextColor("green");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if TCUs is connected
    name = "tcu";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("6");
    if(!testConnection(temp))
    {
        ui->statusBox->setTextColor("red");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        ui->statusBox->setTextColor("green");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    ui->statusBox->append("");
}

//=============================================================================
// testConnection()
// pings an address to see if it's connected to the network.
//=============================================================================
bool MainWindow::testConnection(string address)
{
    string command = "ping -c 1 ";  // where c = count
    command.append(address);

    int status = system(stringToCharPntr(command));
    if (-1 != status)
    {
        int ping_ret = WEXITSTATUS(status);

        if(ping_ret==0)
        {
            cout<<"Ping successful"<<endl; //Proceed
            return true;
        }
        else
        {
            cout<<"Ping not successful"<<endl; //Sleep and again check for ping
            return false;
        }
    }

    return false;
}

//=============================================================================
// stringToCharPntr()
// Takes in a string and converts it to char*
//=============================================================================
char* MainWindow::stringToCharPntr(string str)
{
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}

//=============================================================================
// receiveNodePositionsButtonClicked()
// method to receive the nodes' positions from the GPSDOs.
//=============================================================================
void MainWindow::on_receiveNodePositionsButton_clicked()
{
    ui->statusBox->append("");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Fetching GPS info files from GPSDOs");

    receiveNodePosition(0);
    receiveNodePosition(1);
    receiveNodePosition(2);

    ui->statusBox->append("");
    ui->statusBox->setTextColor("black");
    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    ui->countdownLabel->setText("");
}

//=============================================================================
// receiveNodePosition()
//=============================================================================
void MainWindow::receiveNodePosition(int node_num)
{
    stringstream ss;
    int status;
    int ret;
    string lat, lon, ht;

    try
    {
        ss << "ansible node" << node_num << " -m fetch -a \"src=~/Desktop/NextGPSDO/gps_info.ini dest=~/Documents/cnc_controller/" << "\"";
        cout << ss.str().c_str() << endl;

        status = system(stringToCharPntr(ss.str()));
        if (-1 != status)
        {
            ret = WEXITSTATUS(status);

            if (ret==0)
            {
                // Parse gpsinfo.ini file
                lat = headerarmfiles.readFromGPSInfoFile(node_num,"LATITUDE");
                lon = headerarmfiles.readFromGPSInfoFile(node_num,"LONGITUDE");
                ht = headerarmfiles.readFromGPSInfoFile(node_num,"ALTITUDE");

                if ((lat == "Fault") || (lon == "Fault") || (ht == "Fault"))
                {
                    // Display data on screen in red X per node
                    ui->statusBox->setTextColor("red");
                    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
                }
                else
                {
                    if (node_num == 0)
                    {
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LAT", lat);
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LON", lon);
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_HT", ht);
                    }
                    else if (node_num == 1)
                    {
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LAT", lat);
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LON", lon);
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_HT", ht);
                    }
                    else if (node_num == 2)
                    {
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LAT", lat);
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LON", lon);
                        headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_HT", ht);
                    }

                    // Display data on screen in green values per node
                    ui->statusBox->setTextColor("green");
                    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _    ") + "node" + QString::number(node_num) + "\n " \
                                + "lat=" + QString::fromStdString(lat) + ", \tlong=" + QString::fromStdString(lon) + ", \tht=" + QString::fromStdString(ht));
               }
            }
            else
            {
                // Display data on screen in red X per node
                ui->statusBox->setTextColor("red");
                ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
            }
        }
        ss.str("");             //clear stringstream
        ui->statusBox->append("");
    }
    catch(exception &e)
    {
        cout << "receiveNodePosition exception: " << e.what() << endl;
    }
}

//=============================================================================
// receiveBearingsButtonClicked()
// method to receive the bearings from the GPSDO.
//=============================================================================
void MainWindow::on_receiveBearingsButton_clicked()
{
    ui->statusBox->append("");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Fetching node bearings file from Mission Control");
    ui->statusBox->append("");

    receiveBearings(0);
    receiveBearings(1);
    receiveBearings(2);

    ui->statusBox->append("");
    ui->statusBox->setTextColor("black");
    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    ui->countdownLabel->setText("");
}

//=============================================================================
// receiveBearings()
//
//  tardat2cc.rtf
// (*171207*)
// DTG	061855Z 1217
// Target Lat/Lon 	{-34.1813,18.46}
// n1: Range	1.82952
// n1: Bearing 46.5192
//=============================================================================
void MainWindow::receiveBearings(int node_num)
{
    string lat, lon, dtg;
    string n0range, n0bearing, n1range, n1bearing, n2range, n2bearing;
    stringstream ss;
    int status;
    int ret;

    try
    {
        ss << "ansible node" << node_num << " -m fetch -a \"src=/home/nextrad/tardat2cc.rtf dest=~/Documents/cnc_controller/" << "\"";
        cout << ss.str().c_str() << endl;

        status = system(stringToCharPntr(ss.str()));
        if (-1 != status)
        {
            ret = WEXITSTATUS(status);

            if (ret==0)
            {
                // Parse tardat2cc.rtf file
                dtg = headerarmfiles.readFromBearingsFile(node_num, "DTG", 12);
                lat = headerarmfiles.readFromBearingsFile(node_num, "Lat", 8);
                lon = headerarmfiles.readFromBearingsFile(node_num, "Lon", 5);
                n0range = headerarmfiles.readFromBearingsFile(node_num, "n0: Range", 7);
                n0bearing = headerarmfiles.readFromBearingsFile(node_num, "n0: Bearing", 7);
                n1range = headerarmfiles.readFromBearingsFile(node_num, "n1: Range", 7);
                n1bearing = headerarmfiles.readFromBearingsFile(node_num, "n1: Bearing", 7);
                n2range = headerarmfiles.readFromBearingsFile(node_num, "n2: Range", 7);
                n2bearing = headerarmfiles.readFromBearingsFile(node_num, "n2: Bearing", 7);

                if ((lat == "Fault") || (lon == "Fault") || (dtg == "Fault"))
                {
                    // Display data on screen in red X per node
                    ui->statusBox->setTextColor("red");
                    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "\tnode" + QString::number(node_num));
                }
                else
                {
                    // Update Header file
                    headerarmfiles.writeToHeaderFile("Bearings", "DTG", dtg);
                    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_LAT", lat);
                    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_LON", lon);
                    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_HT", "0.00");

                    if (node_num == 0)
                    {
                        headerarmfiles.writeToHeaderFile("Bearings", "NODE0_RANGE", n0range);
                        headerarmfiles.writeToHeaderFile("Bearings", "NODE0_BEARING", n0bearing);
                    }
                    else if (node_num == 1)
                    {
                        headerarmfiles.writeToHeaderFile("Bearings", "NODE1_RANGE", n1range);
                        headerarmfiles.writeToHeaderFile("Bearings", "NODE1_BEARING", n1bearing);
                    }
                    else if (node_num == 2)
                    {
                        headerarmfiles.writeToHeaderFile("Bearings", "NODE2_RANGE", n2range);
                        headerarmfiles.writeToHeaderFile("Bearings", "NODE2_BEARING", n2bearing);
                    }

                    // Display data on screen in green values per node
                    ui->statusBox->setTextColor("green");
                    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _    ") + "node" + QString::number(node_num) + "\n" \
                                + "lat=" + QString::fromStdString(lat) + "\tlong=" + QString::fromStdString(lon) + "\n" \
                                + "DTG=" + QString::fromStdString(dtg));

                    switch(node_num)
                    {
                    case 0: ui->statusBox->append("n0 range=" + QString::fromStdString(n0range) + "\tn0 bearing=" + QString::fromStdString(n0bearing));
                            break;
                    case 1: ui->statusBox->append("n1 range=" + QString::fromStdString(n1range) + "\tn1 bearing=" + QString::fromStdString(n1bearing));
                            break;
                    case 2: ui->statusBox->append("n2 range=" + QString::fromStdString(n2range) + "\tn2 bearing=" + QString::fromStdString(n2bearing));
                            break;
                    }
                }
            }
            else
            {
                // Display data on screen in red X per node
                ui->statusBox->setTextColor("red");
                ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
            }
        }
        ss.str("");             //clear stringstream
        ui->statusBox->append("");
    }
    catch(exception &e)
    {
        cout << "receiveBearings exception: " << e.what() << endl;
    }
}

//=============================================================================
// showVideoButtonClicked()
// Method to show the video mosaic.
//=============================================================================
void MainWindow::on_showVideoButton_clicked()
{
    ui->statusBox->append("");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Opening mosaic view");
    int status = system("x-terminal-emulator -x -e \"cvlc --vlm-conf ../scripts/mosaic_view/mosaic.conf --mosaic-width=1280 --mosaic-height=720 --mosaic-keep-picture --mosaic-rows=2 --mosaic-cols=2 --mosaic-position=0 --mosaic-order=1,2,3,4\"");
    if (-1 != status)
    {
         int ret = WEXITSTATUS(status);

         if(ret!=0)
         {
            std::cout << "Failed to execute command properly" << endl;
         }
    }
    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    ui->countdownLabel->setText("");
}

//=============================================================================
// abortAudioRecordingButtonClicked()
// Method to abort the audio recording. Stops audio recording countdown timers and recording
//=============================================================================
void MainWindow::on_abortAudioRecordingButton_clicked()
{
    //in 'countdown to start' mode only the starttimer needs to be stopped
    if(experiment_state == WAITING)
    {
        starttimer->stop();
        endtimer->stop();
    }
    //in 'countdown to end' mode the starttimer must be stopped as well as the recording
    else if(experiment_state == ACTIVE)
    {
        stopRecording();
        endtimer->stop();
    }
    experiment_state = INACTIVE;
    ui->statusBox->setTextColor("black");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio recording aborted!");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    ui->countdownLabel->setText("Audio recording aborted!");
}

//=============================================================================
// runNextlookButtonClicked()
//=============================================================================
void MainWindow::on_runNextlookButton_clicked()
{
    ui->statusBox->append("");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Launching NeXtLook on Cobalts");

    int status = system("../scripts/nextlook/run_nextlook.sh");
    if (-1 != status)
    {
         int ret = WEXITSTATUS(status);

         if(ret!=0)
         {
            std::cout << "Failed to execute command properly" << endl;
         }
    }
    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    ui->countdownLabel->setText("");
}

//=============================================================================
// abortGoButtonClicked()
// aborts GoButton
//=============================================================================
void MainWindow::on_abortGoButton_clicked()
{
    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(RED).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(RED).c_str());
    ui->countdownLabel->setText("");
}

//=============================================================================
// goButtonClicked()
// sends out header file to all units then starts countdown to armtime
//=============================================================================
void MainWindow::on_goButton_clicked()
{

    // reset times
    resetHeaderFileTimes();

    // if countdown time valid
    if (checkCountdown())
    {
        ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());

        // sends out header file to all units
        if (sendFilesOverNetwork() == 0)
        {
            // initialise TCUs
            runTCUs();
        }
    }
    else
    {
        ui->goButton->setStyleSheet(setButtonColour(RED).c_str());
    }

    ui->statusBox->setTextColor("black");

}

//=============================================================================
// resetHeaderFileTimes()
// Resets Header File times to now plus STARTTIMESECS.
// The times rollover in date/time.
//=============================================================================
void MainWindow::resetHeaderFileTimes(void)
{
    Datetime datetime;
    std::string nowplussecs, day, month, year, hour, minute, second;

    // This time rolls over if add seconds
    nowplussecs = datetime.getNowPlusSecs(STARTTIMESECS);

    year = nowplussecs.substr(0,4);
    month = nowplussecs.substr(5,2);
    day = nowplussecs.substr(8,2);
    hour = nowplussecs.substr(11,2);
    minute = nowplussecs.substr(14,2);
    second = nowplussecs.substr(17,2);

    headerarmfiles.writeToHeaderFile("Timing", "YEAR", year);
    headerarmfiles.writeToHeaderFile("Timing", "MONTH", month);
    headerarmfiles.writeToHeaderFile("Timing", "DAY", day);
    headerarmfiles.writeToHeaderFile("Timing", "HOUR", hour);
    headerarmfiles.writeToHeaderFile("Timing", "MINUTE", minute);
    headerarmfiles.writeToHeaderFile("Timing", "SECOND", second);
}

//=============================================================================
// checkCountdown()
// This method parses the start and end times for the video recording,
// converts the times from dd-MM-yyyy hh:mm:ss to yyyy-MM-dd hh:mm:ss formats for timer and NTP
// If countdown time is valid, this method starts the countdown timer
//=============================================================================
bool MainWindow::checkCountdown(void)
{
    Datetime datetime;
    stringstream ss_unixtime;
    HeaderArmFiles headerarmfiles;

    // read armtime from Header File values
    QString year = headerarmfiles.readFromHeaderFile("Timing", "YEAR");
    QString month = headerarmfiles.readFromHeaderFile("Timing", "MONTH");
    QString day = headerarmfiles.readFromHeaderFile("Timing", "DAY");
    QString hour = headerarmfiles.readFromHeaderFile("Timing", "HOUR");
    QString minute = headerarmfiles.readFromHeaderFile("Timing", "MINUTE");
    QString second = headerarmfiles.readFromHeaderFile("Timing", "SECOND");

    cout << "checkCountdown1() = " << year.toStdString() << " " << month.toStdString() << " " << day.toStdString() << " " << hour.toStdString() << " " << minute.toStdString() << " " << second.toStdString() << endl;

    // calculate ENDTIMESECS from Header File values
    int num_pris = atoi(headerarmfiles.readFromHeaderFile("PulseParameters", "NUM_PRIS").toStdString().c_str());
    int pri = atoi(headerarmfiles.readFromHeaderFile("PulseParameters", "PRI").toStdString().c_str());    // microseconds
    EXPERIMENT_LENGTH = num_pris * pri * 1e-6;  // = 60000 * 1000/1000000 = 60

    //required format: YYYY-MM-DD HH:MM:SS
    ss_unixtime << year.toStdString() << "-" << setfill('0') << setw(2) << month.toStdString() << "-" << setfill('0') << setw(2) << day.toStdString() << " ";
    ss_unixtime << hour.toStdString() << ":" << setfill('0') << setw(2) << minute.toStdString() << ":" << setfill('0') << setw(2) << second.toStdString();

    cout << "checkCountdown2() = " << ss_unixtime.str() << endl;

    struct tm tm1;
    tm1 = datetime.convertToStructTm(ss_unixtime.str());

    // Check for validity
    int iyear, imonth, iday;

    iyear = tm1.tm_year + 1900;
    imonth = tm1.tm_mon + 1;
    iday = tm1.tm_mday;

    cout << "checkCountdown3() = " << iyear << " " << imonth << " " << iday << endl;

    if (((imonth == 2) && (iday > 28) && (remainder (iyear, 4) != 0)) ||
        ((imonth == 2) && (iday > 29) && (remainder (iyear, 4) == 0)) ||
        (((imonth == 4) || (imonth == 6) || (imonth == 11))  && (iday > 30)))
    {
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File date is invalid, please correct it.");
        return false;
    }

    strtUnixTime = datetime.convertToUnixTime(tm1);
    stopUnixTime = strtUnixTime + EXPERIMENT_LENGTH;
    currentUnixTime = time(NULL);

    //check if the start/end times are in the past
    if(strtUnixTime < currentUnixTime)
    {
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Please use a future start time");
        return false;
    }
    else if(stopUnixTime < strtUnixTime)
    {
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Please use a future stop time");
        return false;
    }
    else // return true
    {
        // start countdown to armtime
        starttimer->start((strtUnixTime - currentUnixTime)*1000);
        cout << "armtime = " << (strtUnixTime - currentUnixTime)*1000 << endl;
        ui->countdownLabel->setText("Countdown to armtime");
        experiment_state = WAITING;
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Countdown to armtime");

        return true;
    }
}

//=============================================================================
// setButtonColour(int colourno)
// sets button colour to light green = rgb(100,255,125),  light gray = rgb(211,211,211) or light red = rgb(255,100,125)
//=============================================================================
string MainWindow::setButtonColour(int colourno)
{
    string colourstr;
    if (colourno == GREEN)
    {
        colourstr = "* { background-color: rgb(100,255,125) }";  // light green
    }
    else if (colourno == GRAY)
    {
        colourstr = "* { background-color: rgb(211,211,211) }";  // light gray
    }
    else
    {
        colourstr = "* { background-color: rgb(255,100,125) }";  // light red
    }

    return colourstr;
}

//=============================================================================
// sendFilesOverNetwork()
//=============================================================================
int MainWindow::sendFilesOverNetwork(void)
{
    stringstream ss;
    int status;
    int ret = -1;

    try
    {
        //GPSDOs

        ss << "ansible nodes -m copy -a \"src=" << HEADER_PATH << " dest=/home/nextrad/Desktop/NextGPSDO/" << HEADER_FILE << "\"";
        status = system(stringToCharPntr(ss.str()));
        if (-1 != status)
        {
            ret = WEXITSTATUS(status);

            if (ret==0)
            {
                cout<< "Header file to GPSDOs all successful\n" <<endl;
                ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to all GPSDOs");
            }
            else
            {
                cout<< "Header file to GPSDOs not all successful\n" <<endl;
                ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to all GPSDOs");
            }
            ui->statusBox->append("");
        }
        ss.str("");

        // Nodes

        ss << "ansible nodes -m copy -a \"src=" << HEADER_PATH << " dest=" << HEADER_PATH << "\"";

        status = system(stringToCharPntr(ss.str()));
        if (-1 != status)
        {
             ret = WEXITSTATUS(status);

             if (ret==0)
             {
                 cout<< "Header file to nodes all successful\n" <<endl;
                 ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to all nodes");
              }
             else
             {
                 cout<< "Header file to nodes not all successful\n" <<endl;
                 ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to all nodes");
             }
             ui->statusBox->append("");
         }
         ss.str("");             //clear stringstream


         // Cobalts

         ss << "ansible cobalts -m copy -a \"src=" << HEADER_PATH << " dest=/smbtest/" << HEADER_FILE << "\"";

         status = system(stringToCharPntr(ss.str()));
         if (-1 != status)
         {
             ret = WEXITSTATUS(status);

             if (ret==0)
             {
                 cout<< "Header file to cobalts all successful\n" <<endl;
                 ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to all cobalts");
              }
             else
             {
                 cout<< "Header file to cobalts not all successful\n" <<endl;
                 ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to all cobalts");
             }
             ui->statusBox->append("");
         }
         ss.str("");             //clear stringstream


         ss << "ansible cobalts -m shell -a \"./run-cobalt.sh\"";

         status = system(stringToCharPntr(ss.str()));
         if (-1 != status)
         {
             ret = WEXITSTATUS(status);

             if (ret==0)
             {
                 cout<< "Primed all cobalts successfully\n" <<endl;
                 ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Primed all cobalts successfully");
              }
             else
             {
                 cout<< "Not all Cobalts were primed successfully\n" <<endl;
                 ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "All cobalts not primed successfully");
             }
             ui->statusBox->append("");
         }
         ss.str("");             //clear stringstream

        return ret;

    }
    catch(exception &e)
    {
        cout << "sendFilesOverNetwork() exception: " << e.what() << endl;
    }

    return -1;
}

//=============================================================================
// runTCUs()
//=============================================================================
void MainWindow::runTCUs(void)
{
    ui->statusBox->append("");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Initialising TCUs");

    runTCU(0);
    runTCU(1);
    runTCU(2);

    ui->statusBox->setTextColor("black");
}

//=============================================================================
// runTCU()
//=============================================================================
void MainWindow::runTCU(int tcu_num)
{
    stringstream ss;
    int ret;
    int status;

    ss << "../scripts/tcu/tcu_v2/tcu_project.py ";
    if (tcu_num == 0)
    {
        ss << TCU0;
    }
    else if (tcu_num == 1)
    {
        ss << TCU1;
    }
    else
    {
        ss << TCU2;
    }
    ss << " " << HEADER_PATH << " &" << endl;
    cout << ss.str() << endl;
    status = system(ss.str().c_str());

    if (-1 != status)
    {
        ret = WEXITSTATUS(status);

        if(ret==0)
        {
            cout << "TCU" << tcu_num << "init successful\n" <<endl;
            ui->statusBox->setTextColor("green");
            ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + "tcu" + QString::number(tcu_num));
        }
        else
        {
            cout << "TCU" << tcu_num << " init FAILED" <<endl;
            ui->statusBox->setTextColor("red");
            ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + "tcu" + QString::number(tcu_num) + "\n" \
                       + "return value=" + QString::number(ret));
        }
        ui->statusBox->append("");
    }
    ss.str("");             //clear stringstream
}

//=============================================================================
// goLaterButtonClicked()
// sends out header file to all units then starts countdown to armtime
//=============================================================================
void MainWindow::on_goLaterButton_clicked()
{
    // if countdown time valid, start display
    if (checkCountdown())
    {
        // sends out header file to all units
        if (sendFilesOverNetwork() == 0)
        {
            // initialise TCUs
            runTCUs();
        }
    }

    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());

}

//=============================================================================
// startRecording()
// Method to start the countdown until the end of the experiment
// Note: This is purely for display and recording audio not actually controlling the experiment
//=============================================================================
void MainWindow::startRecording(void)
{
    experiment_state = ACTIVE;
    audioRecorder.startRecording();
    endtimer->start((stopUnixTime - currentUnixTime)*1000);
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio recording started");
    ui->countdownLabel->setText("Audio recording ends in ...");
}

//=============================================================================
// stopRecording()
// Method to stop the countdown timer signalling end of experiment
// Note: This is purely for display and recording audio not actually controlling the experiment
//=============================================================================
void MainWindow::stopRecording(void)
{
    experiment_state = INACTIVE;
    audioRecorder.stopRecording();
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio stopped");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio saved to /var/spool/Asterisk/");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio relocated to /home/nextrad/Documents/Audio/output");
    ui->countdownLabel->setText("Audio recording stopped");
}

//=======================================================================
// getCountDownTime()
//=======================================================================
//Calculates the hours minutes and seconds remaining for countdown
QString MainWindow::getCountDownTime(time_t timeLeft)
{
    Datetime datetime;
    QString temp = datetime.getCountDownTime(timeLeft); //"%d.%m.%Y_%I:%M:%S");
    return temp;
}

//=============================================================================
// updateCountDownLCD()
// Updates the countdown LCD according.
//=============================================================================
void MainWindow::updateCountDownLCD(void)
{
    currentUnixTime = time(NULL);
    if (experiment_state == INACTIVE)
    {
        ui->Countdown->display("00:00:00");
    }
    else if (experiment_state == WAITING)
    {
        ui->Countdown->display(getCountDownTime(strtUnixTime - currentUnixTime));
//        cout << "WAITING " << strtUnixTime - currentUnixTime << endl;
    }
    else if (experiment_state == ACTIVE)
    {
        ui->Countdown->display(getCountDownTime(stopUnixTime - currentUnixTime));
//        cout << "ACTIVE " << stopUnixTime - currentUnixTime << endl;
    }
}
