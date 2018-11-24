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
//Edited by:    Shirley Coetzee
//Revision      8.0 (Jul 2018)
//Edited by:    Shirley Coetzee
//Revision      9.0 (Sep 2018)


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
    ui->statusBox->append("");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Network Connections");
    ui->statusBox->append("");

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
    QString node_num_qstr = QString::number(NetID.toInt() - 1);    //This is because the node numbering actually starts from zero.

    //Test if Access Point bullet is connected
    name = "ap";
    name.append(node_num_qstr.toUtf8().constData());
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
    name.append(node_num_qstr.toUtf8().constData());
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
    name.append(node_num_qstr.toUtf8().constData());
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
    if(!testNodeConnection(NetID))
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
    name.append(node_num_qstr.toUtf8().constData());
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
    name.append(node_num_qstr.toUtf8().constData());
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
    name.append(node_num_qstr.toUtf8().constData());
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
// testNodeConnection()
// Tests the node connections to CNC
//=============================================================================
bool MainWindow::testNodeConnection(QString NetID)
{
    bool connected = false;
    string temp, name;
    string address = "192.168.1.";
    address.append(NetID.toUtf8().constData());
    QString node_num_qstr = QString::number(NetID.toInt() - 1);    //This is because the node numbering actually starts from zero.

    //Test if Node Laptop is connected
    name = "node";
    name.append(node_num_qstr.toUtf8().constData());
    temp = address;
    temp.append("1");
    if(testConnection(temp))
    {
        connected = true;
    }

    return connected;
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
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Node Positions");
    ui->statusBox->append("");

    receiveNodePosition(0);
    receiveNodePosition(1);
    receiveNodePosition(2);

    ui->statusBox->append("");
    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    ui->countdownLabel->setText("");
}

//=============================================================================
// receiveNodePosition()
//=============================================================================
bool MainWindow::receiveNodePosition(int node_num)
{
    stringstream ss;
    int status;
    int ret;
    string lat, lon, ht;
    bool connected = false;

    try
    {
        if (testNodeConnection(QString::number(node_num + 1)))
        {
            connected = true;

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
                        // Display data on screen in green values per node
                        ui->statusBox->setTextColor("green");
                        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _    ") + "node" + QString::number(node_num) + "\n " \
                                    + "lat=" + QString::fromStdString(lat) + ", \tlong=" + QString::fromStdString(lon) + ", \tht=" + QString::fromStdString(ht));

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
                    }
                }
                else
                {
                    // Display data on screen in red X per node
                    ui->statusBox->setTextColor("red");
                    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
                }
            }
            else
            {
                // Display data on screen in red X per node
                ui->statusBox->setTextColor("red");
                ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
            }
        }
        else
        {
            // Display data on screen in red X per node
            ui->statusBox->setTextColor("red");
            ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
        }

        ss.str("");             //clear stringstream
        ui->statusBox->append("");

    }
    catch(exception &e)
    {
        cout << "receiveNodePosition exception: " << e.what() << endl;
    }

    return connected;
}

//=============================================================================
// viewMapButtonClicked()
// method to receive the bearings from the GPSDO.
//=============================================================================
void MainWindow::on_viewMapButton_clicked()
{
    ui->statusBox->append("");
    ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "View Map");
    ui->statusBox->append("");

    string lat, lon, ht;
    string namebig = "NODE";
    string namesmall = "node";
    string temp;

    bool connected = false;

    try
    {
        // save node positions to Google Earth file
        for( int node_num = 0; node_num < 3; node_num++ )
        {
            if (!receiveNodePosition(node_num))             // TODO - set to if(receiveNodePosition)
            {
                connected = true;

                string numbigstr = std::to_string(node_num);
                string numbigfull = namebig + numbigstr;

                temp = numbigfull + "_LOCATION_LAT";
                lat = headerarmfiles.readFromHeaderFile("GeometrySettings", temp).toStdString();

                temp = numbigfull + "_LOCATION_LON";
                lon = headerarmfiles.readFromHeaderFile("GeometrySettings", temp).toStdString();

                temp = numbigfull + "_LOCATION_HT";
                ht = headerarmfiles.readFromHeaderFile("GeometrySettings", temp).toStdString();

                string numsmallstr = std::to_string(node_num);
                string numsmallfull = namesmall + numsmallstr;

                headerarmfiles.writeToGoogleEarthFile(numsmallfull, "<longitude>", lon);
                headerarmfiles.writeToGoogleEarthFile(numsmallfull, "<latitude>", lat);
                headerarmfiles.writeToGoogleEarthFile(numsmallfull, "<altitude>", ht);
                headerarmfiles.writeToGoogleEarthFile(numsmallfull, "<coordinates>", lon + "," + lat + "," + ht);
            }
        }

//        if (connected)                  // TODO - set to connected
//        {
            // Define Google Earth selections
            QMessageBox::information(
                this,
                tr("Google Earth"),
                tr("Unselect \"Temporary Places\"\nSave to \"My Places.kml\"\nDiscard \"Temporary Places\""));


            // Launch Google Earth
            stringstream ss;
            int ret;
            int status;
            bool closed = false;

            // Remove any existing Google Earth programs
            ss << "pkill googleearth-bin";
            while (closed == false)
            {
                status = system(ss.str().c_str());
                if (-1 != status)
                {
                    ret = WEXITSTATUS(status);
                    if(ret==0)
                    {
                        cout << "Closed current Google Earth program\n" << endl;
                    }
                    else
                    {
                        closed = true;
                    }
                }
            }
            ss.str("");

            // Run Google Earth
            ss << "cd " << GOOGLE_EARTH_PATH " && ./google-earth-pro " << GOOGLE_EARTH_FULLFILE << " & exit";
            status = system(ss.str().c_str());
            if (-1 != status)
            {
                ret = WEXITSTATUS(status);
                if(ret==0)
                {
                    cout << "view map successful\n" << endl;
                }
                else
                {
                    cout << "view map FAILED" << endl;
                }
            }
            ss.str("");
      //  }

    }
    catch (exception &e)
    {
        cout << "on_viewMapButton_clicked() exception: " << e.what() << endl;
    }


    ui->statusBox->append("");
    ui->statusBox->setTextColor("black");
    ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    ui->countdownLabel->setText("");
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
    try
    {
        stringstream ss;
        int status;
        int ret = -1;

        ui->statusBox->append("");
        ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Aborting experiment!");

        ss << "ansible cobalts -m shell -a \"./killscript.sh\"";
        status = system(stringToCharPntr(ss.str()));
        if (-1 != status)
        {
            ret = WEXITSTATUS(status);

            if (ret==0)
            {
                cout<< "Aborted all cobalts successfully\n" <<endl;
                ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Aborted all cobalts successfully");
             }
            else
            {
                cout<< "Not all Cobalts were aborted successfully\n" <<endl;
                ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "All cobalts not aborted successfully");
            }
            ui->statusBox->append("");
        }
        ss.str("");             //clear stringstream

        cout<< "Aborting TCUs...\n" <<endl;
        killTCU(0);
        killTCU(1);
//        killTCU(2);                                                       // TODO - uncomment line and reset ansible hosts

        ui->statusBox->setTextColor("black");
        ui->goButton->setStyleSheet(setButtonColour(GREEN).c_str());
        ui->goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
        ui->countdownLabel->setText("");
    }
    catch(exception &e)
    {
        cout << "sendFilesOverNetwork() exception: " << e.what() << endl;
    }

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

        saveTarget();

        // sends out header file to ALL units
        if (sendFilesOverNetwork()== 0)
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
// calcExperimentLength()
//
// Calc ExperimentLength from the NUM_PRIS, and the summing of each specific block in PULSES
//=============================================================================
int MainWindow::calcExperimentLength(void)
{
    int num_pris = atoi(headerarmfiles.readFromHeaderFile("PulseParameters", "NUM_PRIS").toStdString().c_str());

    string pulses_str = headerarmfiles.readFromHeaderFile("PulseParameters", "PULSES").toStdString();
    // e.g. PULSES = "5.0,1000.0,0,1300.0|10.0,2000.0,1,1300.0|10.0,3000.0,2,1300.0|10.0,4000.0,3,1300.0";

    // ====================================================
    // Split into blocks separated by "|", put into pulses_arr

    std::string s = pulses_str;
    std::string delimiter = "|";

    // Get pulses_arr
    vector <string> pulses_arr;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        pulses_arr.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    pulses_arr.push_back(s);

    int num_pulses_in_block = pulses_arr.size();

    for (int i=0; i<num_pulses_in_block; i++)
        cout << pulses_arr[i] << "\n";

    cout << "num_pulses_in_block = " << num_pulses_in_block << std::endl  << std::endl;

    // =======================================================

    // Split into values separated by ",", put into block_arr

    std::string::size_type sz;   // alias of size_t
    int tblock = 0;
    int i_dec;

    for (int i=0; i<num_pulses_in_block; i++)
    {

        std::string s = pulses_arr[i];
        std::string delimiter = ",";

        // Get block
        vector <string> block_arr;

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            block_arr.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        block_arr.push_back(s);

        int num_values_in_block = block_arr.size();

        for (int i=0; i<num_values_in_block; i++)
            cout << block_arr[i] << "\n";

        cout << "num_values_in_block = " << num_values_in_block << endl;


        i_dec = std::stoi (block_arr[1],&sz);
        cout << "i_dec = " << i_dec << endl << endl;

        tblock += i_dec;
    }

    cout << "tblock = " << tblock << endl;

    // =======================================================

    int num_rpts = num_pris / num_pulses_in_block;

    cout << "num_pris =" << num_pris << "\nnum_rpts = " << num_rpts << endl;

    int texperiment = tblock * num_rpts * 1e-6;  //  secs
                                                // num_pris * pri * 1e-6;  // = 60000 * 1000/1000000 = 60

    cout << "texperiment = " << texperiment << " secs" << endl;

    return texperiment;
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

    cout << "checkCountdown1() = " << year.toStdString() << "-" << month.toStdString()<< "-" << day.toStdString();
    cout << " " << hour.toStdString() << ":" << minute.toStdString() << ":" << second.toStdString() << endl;

    // calculate EXPERIMENT_LENGTH from Header File values
    EXPERIMENT_LENGTH = calcExperimentLength();

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

    cout << "checkCountdown3() = " << iyear << "-" << imonth << "-" << iday << endl;

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

    if (testConnection(TCU0))
    {
        runTCU(0);
    }
    if (testConnection(TCU1))
    {
        runTCU(1);
    }
    if (testConnection(TCU2))
    {
       runTCU(2);
    }

    ui->statusBox->setTextColor("black");
}

//=============================================================================
// runTCU()TCU0
//=============================================================================
void MainWindow::runTCU(int tcu_num)
{
    stringstream ss;
    int ret;
    int status;

    ss << TCU_INIT_SCRIPT;
    if (tcu_num == 0)
    {
        ss << TCU0 << " -b " << TCU_BOF_ACTIVE;
    }
    else if (tcu_num == 1)
    {
        ss << TCU1 << " -b " << TCU_BOF_PASSIVE;
    }
    else
    {
        ss << TCU2 << " -b " << TCU_BOF_PASSIVE;
    }
    ss << " -i -f " << HEADER_PATH << " &" << endl;
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
// killTCU()
//=============================================================================
void MainWindow::killTCU(int tcu_num)
{
    stringstream ss;
    int ret;
    int status;

    ss << TCU_INIT_SCRIPT;
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
    ss << " -k &" << endl;
    cout << ss.str() << endl;
    status = system(ss.str().c_str());

    if (-1 != status)
    {
        ret = WEXITSTATUS(status);

        if(ret==0)
        {
            cout << "TCU" << tcu_num << "kill successful\n" <<endl;
            ui->statusBox->setTextColor("green");
            ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + "tcu" + QString::number(tcu_num));
        }
        else
        {
            cout << "TCU" << tcu_num << "kill FAILED" <<endl;
            ui->statusBox->setTextColor("red");
            ui->statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + "tcu" + QString::number(tcu_num) + "\n" \
                       + "return value=" + QString::number(ret));
        }
        ui->statusBox->append("");
    }
    ss.str("");             //clear stringstream
}

//=============================================================================
// on_saveTarget()
// sends out header file to all units then starts countdown to armtime
//=============================================================================
void MainWindow::saveTarget()
{
        cout << "Fetching target positions from Google Earth File" <<endl;
        // Read target positions from Google Earth
        string lont = headerarmfiles.readFromGoogleEarthFile("target", "<longitude>");
        string latt = headerarmfiles.readFromGoogleEarthFile("target", "<latitude>");
        string htt = headerarmfiles.readFromGoogleEarthFile("target", "<altitude>");

        // Save target positions to Header file
        headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_LAT", latt);
        headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_LON", lont);
        headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_HT", htt);
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
        saveTarget();

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
        if((strtUnixTime - currentUnixTime) >= 0)
        {
            ui->Countdown->display(getCountDownTime(strtUnixTime - currentUnixTime));
        }
    }
    else if (experiment_state == ACTIVE)
    {
        if((stopUnixTime - currentUnixTime) >= 0)
        {
            ui->Countdown->display(getCountDownTime(stopUnixTime - currentUnixTime));
        }
    }
}
