//Class:        Window
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       David Bissett
//Created:      April 2016
//Version       1.0 (June 2016)
//Edited by:    Shirley Coetzee
//Revision      2.0 (December 2016)
//Edited by:    Shirley Coetzee
//Revision      3.0 (January, February 2017)
//Edited by:    Shirley Coetzee
//Revision      4.0 (November 2017)
//Edited by:    Shirley Coetzee and Darryn Jordan
//Revision      5.0 (December 2017)
//Edited by:    Shirley Coetzee, Darryn Jordan, Brad Kahn and Simon Lewis
//Revision      6.0 (Jan/Feb 2018)


//=============================================================================
// Includes
//=============================================================================

#include "window.h"
#include <QPushButton>
#include <QApplication>
#include <QDateTime>
#include <QString>

#define DEBUG "goLater"

extern int EXPERIMENT_LENGTH; //in seconds

//=============================================================================
// Constructor
//=============================================================================
Window::Window(QWidget *parent) : QWidget(parent)
{
    experiment_state = INACTIVE; //see enum for explanation
   // resetHeaderFileTimes();

    //Set size of window
    setFixedSize(600,590);

    initGUI();

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

    for(int i=0; i<3; i++)
    {
        server.resetError(i);       //This is to try get rid of a bug where server.error
    }

}


//=============================================================================
// Destructor
//=============================================================================
Window::~Window()
{
    closeServer();      //Close the CNC's server socket when the window closes
}


//=============================================================================
// Close Server()
// Method to close the CNC's server socket
//=============================================================================
void Window::closeServer()
{
    server.closeServer();
}


//=============================================================================
// initGUI()
// Method to initialise all the GUI features of the window
//=============================================================================
void Window::initGUI(void)
{
    //Title
    QLabel* label = new QLabel(this);
    label->setGeometry(30, 10, 100, 50);
    label->setText("CNC");
    label->setFont(QFont("Ubuntu",36));
    label->show();

    //text label above countdown LCD
    countDownLabel = new QLabel(this);
    countDownLabel->setGeometry(445, 500, 140, 20 );
    countDownLabel->setText("No countdown active");
    countDownLabel->setFont(QFont("Ubuntu",10));
    countDownLabel->show();

    //Status output text box for outputting any messages to user
    statusBox = new QTextEdit(this);
    statusBox->setGeometry(155, 70, 425, 420);
    statusBox->setTextColor("black");

    //countdown LCD number set to bottom right
    countDown = new QLCDNumber(8, this);
    countDown->setGeometry(445, 530, 140, 50);
    countDown->display("00:00:00");

    //button for testing network connections
    testConnectionButton = new QPushButton("Check Network\nConnection", this);
    testConnectionButton->setGeometry(10, 70, 135, 50);
    connect(testConnectionButton, SIGNAL (clicked(bool)), this, SLOT(connectionTestButtonClicked(void)));

    //button for editing header file
    editHeaderFileButton = new QPushButton("Edit Header\nFile", this);
    editHeaderFileButton->setGeometry(10, 130, 135, 50);
    connect(editHeaderFileButton, SIGNAL (clicked(bool)), this, SLOT(editHeaderFileButtonClicked(void)));

    //button for receiving node positions
    receiveNodePositionsButton = new QPushButton("Receive Node\nPositions", this);
    receiveNodePositionsButton->setGeometry(10, 190, 135, 50);
    connect(receiveNodePositionsButton, SIGNAL (clicked(bool)), this, SLOT(receiveNodePositionsButtonClicked(void)));

    //button for receiving bearings
    receiveBearingsButton = new QPushButton("Receive Bearings", this);
    receiveBearingsButton->setGeometry(10, 250, 135, 50);
    connect(receiveBearingsButton, SIGNAL (clicked(bool)), this, SLOT(receiveBearingsButtonClicked(void)));

    //button for showing video mosaic
    showVideoButton = new QPushButton("Start Video\nMosaic", this);
    showVideoButton->setGeometry(10, 310, 135, 50);
    connect(showVideoButton, SIGNAL (clicked(bool)), this, SLOT(showVideoButtonClicked(void)));

    //button for aborting recording and countdown
    abortAudioRecordingButton = new QPushButton("Abort\nAudio Recording", this);
    abortAudioRecordingButton->setGeometry(10, 370, 135, 50);
    connect(abortAudioRecordingButton, SIGNAL (clicked(bool)), this, SLOT(abortAudioRecordingButtonClicked(void)));

    //button for starting NeXtLook
    runNextlookButton = new QPushButton("Run\nNeXtLook", this);
    runNextlookButton->setGeometry(10, 430, 135, 50);
    connect(runNextlookButton, SIGNAL (clicked(bool)), this, SLOT(runNextlookButtonClicked(void)));

    //button for aborting goButton
    abortGoButton = new QPushButton("Abort GO", this);
    abortGoButton->setGeometry(10, 490, 135, 50);
    connect(abortGoButton, SIGNAL (clicked(bool)), this, SLOT(abortGoButtonClicked(void)));


    //button for distributing header file to node controllers
    goButton = new QPushButton("GO", this);
    goButton->setGeometry( 200, 500, 135, 50);
    goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    connect(goButton, SIGNAL (clicked(bool)), this, SLOT(goButtonClicked(void)));

#ifdef DEBUG
    //button for distributing header file to node controllers
    goLaterButton = new QPushButton("GO LATER", this);
    goLaterButton->setGeometry( 350, 510, 75, 35);
    goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    connect(goLaterButton, SIGNAL (clicked(bool)), this, SLOT(goLaterButtonClicked(void)));
#endif

}


//=============================================================================
// connectionTestButtonClicked()
// Tests the connections to CNC
//=============================================================================
void Window::connectionTestButtonClicked(void)
{
    testSubNetwork("1");
    testSubNetwork("2");
    testSubNetwork("3");

    statusBox->setTextColor("black");
}


//=============================================================================
// testSubNetwork()
//=============================================================================
//Tests the connections to CNC
void Window::testSubNetwork(QString NetID)
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
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if STAtion bullet is connected
    name = "sta";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("3");
    if(!testConnection(temp))
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if PoE Switch is connected
    name = "switch";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("0");
    if(!testConnection(temp))
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if Node Laptop is connected
    name = "node";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("1");
    if(!testConnection(temp))
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if IP camera is connected
    name = "cam";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("4");
    if(!testConnection(temp))                   //Cameras have no ssh port and more security so it's easier to ping them
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    //Test if Cobalt is connected
    name = "cobalt";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("5");
    if(!testConnection(temp))
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) );
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );
    }

    statusBox->append("");
}


//=============================================================================
// testConnection()
// pings an address to see if it's connected to the network.
//=============================================================================
bool Window::testConnection(string address)
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
char* Window::stringToCharPntr(string str)
{
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}


//=============================================================================
// startRecording()
// Method to start the countdown until the end of the experiment
// Note: This is purely for display and recording audio not actually controlling the experiment
//=============================================================================
void Window::startRecording(void)
{
    experiment_state = ACTIVE;
    audioRecorder.startRecording();
    endtimer->start((stopUnixTime - currentUnixTime)*1000);
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio recording started");
    countDownLabel->setText("Audio recording ends in ...");
}

//=============================================================================
// stopRecording()
// Method to stop the countdown timer signalling end of experiment
// Note: This is purely for display and recording audio not actually controlling the experiment
//=============================================================================
void Window::stopRecording(void)
{
    experiment_state = INACTIVE;
    audioRecorder.stopRecording();
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio stopped");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio saved to /var/spool/Asterisk/");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio relocated to /home/nextrad/Documents/Audio/output");
    countDownLabel->setText("Stopped recording");
}

//=======================================================================
// getCountDownTime()
//=======================================================================
//Calculates the hours minutes and seconds remaining for countdown
QString Window::getCountDownTime(time_t timeLeft)
{
    Datetime datetime;
    QString temp = datetime.getCountDownTime(timeLeft); //"%d.%m.%Y_%I:%M:%S");
    return temp;
}

//=============================================================================
// updateCountDownLCD()
// Updates the countdown LCD according.
//=============================================================================
void Window::updateCountDownLCD(void)
{
    currentUnixTime = time(NULL);
    if (experiment_state == INACTIVE)
    {
        countDown->display("00:00:00");
    }
    else if(experiment_state == WAITING)
    {
        countDown->display(getCountDownTime(strtUnixTime - currentUnixTime));
    }
    else if(experiment_state == ACTIVE)
    {
        countDown->display(getCountDownTime(stopUnixTime - currentUnixTime));
    }
}

//=============================================================================
// editHeaderFileButtonClicked()
// Opens a new menu to do with editing the header file
//=============================================================================
void Window::editHeaderFileButtonClicked(void)
{
    QIcon icon(ICON_PATH);
    headerfilewindow = new HeaderFileWindow();
    headerfilewindow->setWindowIcon(icon); //Set Icon for application
    headerfilewindow->show();

    //link the closing of the header file menu to opening the main window
    connect(headerfilewindow, SIGNAL (finished(int)), this, SLOT (openMainMenu(void)));
    this->hide();
}

//=============================================================================
// openMainMenu()
//=============================================================================
void Window::openMainMenu(void)
{
    this->show();
    headerfilewindow->hide();
    if (headerfilewindow->newtime == true)
    {
        goLaterButton->setStyleSheet(setButtonColour(GREEN).c_str());
    }
}

//=============================================================================
// receiveNodePositionsButtonClicked()
// method to receive the nodes' positions from the GPSDOs.
//=============================================================================
void Window::receiveNodePositionsButtonClicked(void)
{
    statusBox->append("");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Fetching GPS info files from GPSDOs");
    //statusBox->append("");

    receiveNodePosition(0);
    receiveNodePosition(1);
    receiveNodePosition(2);

    statusBox->append("");
    statusBox->setTextColor("black");
}

//=============================================================================
// receiveNodePosition()
//=============================================================================
void Window::receiveNodePosition(int node_num)
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
                    statusBox->setTextColor("red");
                    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
                }
                else
                {
                    // Update Header file
                    switch (node_num)
                    {
                        case 0: headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LAT", lat);
                                headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_LON", lon);
                                headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE0_LOCATION_HT", ht);
                                break;
                        case 1: headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LAT", lat);
                                headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_LON", lon);
                                headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE1_LOCATION_HT", ht);
                                break;
                        case 2: headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LAT", lat);
                                headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_LON", lon);
                                headerarmfiles.writeToHeaderFile("GeometrySettings", "NODE2_LOCATION_HT", ht);
                                break;
                    }

                    // Display data on screen in green values per node
                    statusBox->setTextColor("green");
                    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _    ") + "node" + QString::number(node_num) + "\n " \
                                + "lat=" + QString::fromStdString(lat) + ", \tlong=" + QString::fromStdString(lon) + ", \tht=" + QString::fromStdString(ht));
               }
            }
            else
            {
                // Display data on screen in red X per node
                statusBox->setTextColor("red");
                statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
            }
        }
        ss.str("");             //clear stringstream
        statusBox->append("");
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

void Window::receiveBearingsButtonClicked(void)
{
    statusBox->append("");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Fetching node bearings file from Mission Control");
    statusBox->append("");

    receiveBearings(0);
    receiveBearings(1);
    receiveBearings(2);

    statusBox->append("");
    statusBox->setTextColor("black");
}

//=============================================================================
// receiveBearings()

/*  tardat2cc.rtf
(*171207*)
DTG	061855Z 1217
Target Lat/Lon 	{-34.1813,18.46}
n1: Range	1.82952
n1: Bearing	46.5192
*/
//=============================================================================
void Window::receiveBearings(int node_num)
{
    string lat, lon, dtg, baseline_bisector;
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
                baseline_bisector = headerarmfiles.readFromBearingsFile(node_num, "BASELINE_BISECTOR", 5);
                n0range = headerarmfiles.readFromBearingsFile(node_num, "n0: Range", 7);
                n0bearing = headerarmfiles.readFromBearingsFile(node_num, "n0: Bearing", 7);
                n1range = headerarmfiles.readFromBearingsFile(node_num, "n1: Range", 7);
                n1bearing = headerarmfiles.readFromBearingsFile(node_num, "n1: Bearing", 7);
                n2range = headerarmfiles.readFromBearingsFile(node_num, "n2: Range", 7);
                n2bearing = headerarmfiles.readFromBearingsFile(node_num, "n2: Bearing", 7);

                if ((lat == "Fault") || (lon == "Fault") || (dtg == "Fault"))
                {
                    // Display data on screen in red X per node
                    statusBox->setTextColor("red");
                    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "\tnode" + QString::number(node_num));
                }
                else
                {
                    // Update Header file
                    headerarmfiles.writeToHeaderFile("Bearings", "DTG", dtg);
                    headerarmfiles.writeToHeaderFile("Bearings", "BASELINE_BISECTOR", baseline_bisector);
                    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_LAT", lat);
                    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_LON", lon);
                    headerarmfiles.writeToHeaderFile("TargetSettings", "TGT_LOCATION_HT", "0.00");

                    switch (node_num)
                    {
                        case 0: headerarmfiles.writeToHeaderFile("Bearings", "NODE0_RANGE", n0range);
                                headerarmfiles.writeToHeaderFile("Bearings", "NODE0_BEARING", n0bearing);
                                break;
                        case 1: headerarmfiles.writeToHeaderFile("Bearings", "NODE1_RANGE", n1range);
                                headerarmfiles.writeToHeaderFile("Bearings", "NODE1_BEARING", n1bearing);
                                break;
                        case 2: headerarmfiles.writeToHeaderFile("Bearings", "NODE2_RANGE", n2range);
                                headerarmfiles.writeToHeaderFile("Bearings", "NODE2_BEARING", n2bearing);
                                break;
                    }

                    // Display data on screen in green values per node
                    statusBox->setTextColor("green");
                    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _    ") + "node" + QString::number(node_num) + "\n" \
                                + "lat=" + QString::fromStdString(lat) + "\tlong=" + QString::fromStdString(lon) + "\n" \
                                + "DTG=" + QString::fromStdString(dtg) + "\tbaseline_bisector=" + QString::fromStdString(baseline_bisector));

                    switch(node_num)
                    {
                    case 0: statusBox->append("n0 range=" + QString::fromStdString(n0range) + "\tn0 bearing=" + QString::fromStdString(n0bearing));
                            break;
                    case 1: statusBox->append("n1 range=" + QString::fromStdString(n1range) + "\tn1 bearing=" + QString::fromStdString(n1bearing));
                            break;
                    case 2: statusBox->append("n2 range=" + QString::fromStdString(n2range) + "\tn2 bearing=" + QString::fromStdString(n2bearing));
                            break;
                    }
                }
            }
            else
            {
                // Display data on screen in red X per node
                statusBox->setTextColor("red");
                statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X    ") + "node" + QString::number(node_num));
            }
        }
        ss.str("");             //clear stringstream
        statusBox->append("");
    }
    catch(exception &e)
    {
        cout << "receiveBearings exception: " << e.what() << endl;
    }
}


//=============================================================================
// abortAudioRecordingButtonClicked()
// Method to abort the audio recording. Stops audio recording countdown timers and recording
//=============================================================================
void Window::abortAudioRecordingButtonClicked(void)
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
    countDownLabel->setText("Audio recording aborted!");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio recording aborted!");
}

//=============================================================================
// showVideoButtonClicked()
// Method to show the video mosaic.
//=============================================================================
void Window::showVideoButtonClicked(void)
{
    statusBox->append("");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Opening mosaic view");
    int status = system("x-terminal-emulator -x -e \"cvlc --vlm-conf ../scripts/mosaic_view/mosaic.conf --mosaic-width=1280 --mosaic-height=720 --mosaic-keep-picture --mosaic-rows=2 --mosaic-cols=2 --mosaic-position=0 --mosaic-order=1,2,3,4\"");
    if (-1 != status)
    {
         int ret = WEXITSTATUS(status);

         if(ret!=0)
         {
            std::cout << "Failed to execute command properly" << endl;
         }
    }
}

//=============================================================================
// runNextlookButtonClicked()
//=============================================================================
void Window::runNextlookButtonClicked(void)
{
    statusBox->append("");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Launching NeXtLook on Cobalts");

    int status = system("../scripts/nextlook/run_nextlook.sh");
    if (-1 != status)
    {
         int ret = WEXITSTATUS(status);

         if(ret!=0)
         {
            std::cout << "Failed to execute command properly" << endl;
         }
    }
}


//=============================================================================
// sendFilesOverNetwork()
//=============================================================================
int Window::sendFilesOverNetwork(void)
{
    stringstream ss;
    int status;
    int ret;

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
                cout<< "Header file to GPSDOs successful\n" <<endl;
                statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to all GPSDOs");
            }
            else
            {
                cout<< "Header file to GPSDOs NOT successful\n" <<endl;
                statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to all GPSDOs");
                return ret;
            }
            statusBox->append("");
        }
        ss.str("");             //clear stringstream


        // Nodes

        ss << "ansible nodes -m copy -a \"src=" << HEADER_PATH << " dest=" << HEADER_PATH << "\"";

        status = system(stringToCharPntr(ss.str()));
        if (-1 != status)
        {
             ret = WEXITSTATUS(status);

             if (ret==0)
             {
                 cout<< "Header file to nodes successful\n" <<endl;
                 statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to all nodes");
              }
             else
             {
                 cout<< "Header file to nodes not successful\n" <<endl;
                 statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to all nodes");
                 return ret;
             }
             statusBox->append("");
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
                 cout<< "Header file to cobalts successful\n" <<endl;
                 statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to all cobalts");
              }
             else
             {
                 cout<< "Header file to cobalts not successful\n" <<endl;
                 statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to all cobalts");
                 return ret;
             }
             statusBox->append("");
         }
         ss.str("");             //clear stringstream


         ss << "ansible cobalts -m shell -a \"./run-cobalt.sh\"";

         status = system(stringToCharPntr(ss.str()));
         if (-1 != status)
         {
             ret = WEXITSTATUS(status);

             if (ret==0)
             {
                 cout<< "Primed cobalts successfully\n" <<endl;
                 statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Primed all cobalts successfully");
              }
             else
             {
                 cout<< "Cobalts not primed successfully\n" <<endl;
                 statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "All cobalts not primed successfully");
                 return ret;
             }
             statusBox->append("");
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
// resetHeaderFileTimes()
// Resets Header File times to now plus STARTTIMESECS.
// The times rollover in date/time.
//=============================================================================
void Window::resetHeaderFileTimes(void)
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
bool Window::checkCountdown(void)
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

    // calculate ENDTIMESECS from Header File values
    int num_pris = atoi(headerarmfiles.readFromHeaderFile("PulseParameters", "NUM_PRIS").toStdString().c_str());
    int pri = atoi(headerarmfiles.readFromHeaderFile("PulseParameters", "PRI").toStdString().c_str());    // microseconds
    EXPERIMENT_LENGTH = num_pris * pri * 1e-6;  // = 60000 * 1000/1000000 = 60

    //required format: YYYY-MM-DD HH:MM:SS
    ss_unixtime << year.toStdString() << "-" << month.toStdString() << "-" << day.toStdString() << " ";
    ss_unixtime << hour.toStdString() << ":" << minute.toStdString() << ":" << second.toStdString();

    //change times to Unix time format
    strtUnixTime = datetime.convertToUnixTime(ss_unixtime.str());
    stopUnixTime = strtUnixTime + EXPERIMENT_LENGTH;
    currentUnixTime = time(NULL);

    //check if the start/end times are in the past
    if(strtUnixTime < currentUnixTime)
    {
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Please use a future start time");
        return false;
    }
    else if(stopUnixTime < strtUnixTime)
    {
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Please use a future stop time");
        return false;
    }
    else // return true
    {
        // start countdown to armtime
        starttimer->start((strtUnixTime - currentUnixTime)*1000);
        countDownLabel->setText("Countdown to armtime");
        experiment_state = WAITING;
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Countdown to armtime");
        return true;
    }
}

//=============================================================================
// runTCUs()
//=============================================================================
void Window::runTCUs(void)
{
    statusBox->append("");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Initialising TCUs");

    runTCU(0);
    runTCU(1);
    runTCU(2);

    statusBox->setTextColor("black");
}

//=============================================================================
// runTCU()
//=============================================================================
void Window::runTCU(int tcu_num)
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
    ss << " " << HEADER_PATH << endl;
    cout << ss.str() << endl;
    status = system(ss.str().c_str());

    if (-1 != status)
    {
        ret = WEXITSTATUS(status);

        if(ret==0)
        {
            cout<< "TCU" << tcu_num << "init successful\n" <<endl;
            statusBox->setTextColor("green");
            statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + "TCU" + QString::number(tcu_num));
        }
        else
        {
            cout<< "TCU" << tcu_num << " init FAILED" <<endl;
            statusBox->setTextColor("red");
            statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + "TCU" + QString::number(tcu_num) + "\n" \
                       + "return value=" + QString::number(ret));
        }
        statusBox->append("");
    }
    ss.str("");             //clear stringstream
}


//=============================================================================
// abortGoButtonClicked()
// aborts GoButton
//=============================================================================
void Window::abortGoButtonClicked(void)
{
    goButton->setStyleSheet(setButtonColour(RED).c_str());
    goLaterButton->setStyleSheet(setButtonColour(RED).c_str());
}

//=============================================================================
// goButtonClicked()
// sends out header file to all units then starts countdown to armtime
//=============================================================================
void Window::goButtonClicked(void)
{

    // reset times
    resetHeaderFileTimes();

    // if countdown time valid
    if (checkCountdown())
    {
        goButton->setStyleSheet(setButtonColour(GREEN).c_str());

        // sends out header file to all units
        if (sendFilesOverNetwork() == 0)
        {
            // initialise TCUs
            runTCUs();
        }
    }
    else
    {
        goButton->setStyleSheet(setButtonColour(RED).c_str());
    }

    headerfilewindow->newtime = false;
    goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());

}

//=============================================================================
// goLaterButtonClicked()
// sends out header file to all units then starts countdown to armtime
//=============================================================================
void Window::goLaterButtonClicked(void)
{

    if (headerfilewindow->newtime == true)
    {
        // if countdown time valid, start display
        if (checkCountdown())
        {
            goLaterButton->setStyleSheet(setButtonColour(GREEN).c_str());

            // sends out header file to all units
            if (sendFilesOverNetwork() == 0)
            {
                // initialise TCUs
                runTCUs();
            }
        }
        else
        {
            goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
        }

        headerfilewindow->newtime = false;
        goLaterButton->setStyleSheet(setButtonColour(GRAY).c_str());
    }

}

//=============================================================================
// setButtonColour(int colourno)
// sets button colour to light green = rgb(100,255,125),  light gray = rgb(211,211,211) or light red = rgb(255,100,125)
//=============================================================================
string Window::setButtonColour(int colourno)
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
