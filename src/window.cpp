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


//=============================================================================
// Includes
//=============================================================================

#include "window.h"
#include <QPushButton>
#include <QApplication>
#include <QDateTime>
#include <QString>

extern int EXPERIMENT_LENGTH; //in seconds

//=============================================================================
// Constructor
//=============================================================================
Window::Window(QWidget *parent) : QWidget(parent)
{
    experiment_state = INACTIVE; //see enum for explanation

    //Set size of window
    setFixedSize(600,590);

    initGUI();

    // This saves the current times to the Header file
    // ToDo: In future, wait for Bill's target, bearing, weather first
    resetHeaderFileTimes();

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
    statusBox->setGeometry(155, 70, 425, 420); //320);

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

    //button for distributing header file to node controllers
    goButton = new QPushButton("GO", this);
    goButton->setGeometry( 250, 500, 135,50);
    goButton->setStyleSheet(setButtonColour(RED).c_str());
    connect(goButton, SIGNAL (clicked(bool)), this, SLOT(goButtonClicked(void)));

    //button for showing video mosaic
    showVideoButton = new QPushButton("Start Video\nMosaic", this);
    showVideoButton->setGeometry(10, 250, 135, 50);
    connect(showVideoButton, SIGNAL (clicked(bool)), this, SLOT(showVideoButtonClicked(void)));

    //button for aborting recording and countdown
    abortAudioRecordingButton = new QPushButton("Abort\nAudio Recording", this);
    abortAudioRecordingButton->setGeometry(10, 310, 135, 50); //(10, 370, 135, 50);
    connect(abortAudioRecordingButton, SIGNAL (clicked(bool)), this, SLOT(abortAudioRecordingButtonClicked(void)));

    //button for starting NeXtLook
    runNextlookButton = new QPushButton("Run\nNeXtLook", this);
    runNextlookButton->setGeometry(10, 370, 135, 50);
    connect(runNextlookButton, SIGNAL (clicked(bool)), this, SLOT(runNextlookButtonClicked(void)));

    //button for receiving node positions
    receiveNodeDetailsButton = new QPushButton("Receive Node\nDetails", this);
    receiveNodeDetailsButton->setGeometry(10, 430, 135, 50);
    connect(receiveNodeDetailsButton, SIGNAL (clicked(bool)), this, SLOT(receiveNodeDetailsButtonClicked(void)));

}


//=============================================================================
// connectionTestButtonClicked()
// Tests the connections to CNC
//=============================================================================
void Window::connectionTestButtonClicked(void)
{
    bool connection_status = true;

    statusBox->append("");
    if(!testSubNetwork("1"))             //Test SubNetwork for Node 0
    {
        connection_status = false;
    }

    if(!testSubNetwork("2"))            //Test SubNetwork for Node 1
    {
        connection_status = false;
    }

    if(!testSubNetwork("3"))            //Test SubNetwork for Node 2
    {
        connection_status = false;
    }
}


//=============================================================================
// testSubNetwork()
//=============================================================================
//Tests the connections to CNC
bool Window::testSubNetwork(QString NetID)
{
    bool connection_status = true;
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
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) ); //+ " not connected"); //"AP" + NetID + " not connected");
        connection_status = false;
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );  //+ " connected"); //"AP" + NetID + " connected");

    }

    //Test if STAtion bullet is connected
    name = "sta";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("3");
    if(!testConnection(temp))
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) ); //+ " not connected"); //"STA" + NetID + " not connected");
        connection_status = false;
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );  //+ " connected"); //"STA" + NetID + " connected");
    }

    //Test if PoE Switch is connected
    name = "switch";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("0");
    if(!testConnection(temp))
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) ); //+ " not connected"); //"Switch" + NetID + " not connected");
        connection_status = false;
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );  //+ " connected"); //"Switch" + NetID + " connected");
    }

    //Test if Node Laptop is connected
    name = "node";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("1");
    if(!testConnection(temp))
    {
        statusBox->append("");
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) ); //+ " not connected"); //"Node" + NetID + " not connected");
        connection_status = false;
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );  //+ " connected"); //"Node" + NetID + " connected");
    }

    //Test if IP camera is connected
    name = "cam";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("4");
    if(!testConnection(temp)) //isConnected())                  //Cameras have no ssh port and more security so it's easier to ping them
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) ); //+ " not connected"); //"Cam" + NetID + " not connected");
        connection_status = false;
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );  //+ " connected"); //"Cam" + NetID + " connected");
    }

    //Test if Cobalt is connected
    name = "cobalt";
    name.append(NetID.toUtf8().constData());
    temp = address;
    temp.append("5");
    if(!testConnection(temp))
    {
        statusBox->setTextColor("red");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(name) ); //+ " not connected"); //"Cobalt" + NetID + " not connected");
        connection_status = false;
    }
    else
    {
        statusBox->setTextColor("green");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(name) );  //+ " connected"); //"Cobalt" + NetID + " connected");
    }

    statusBox->append("");

    return connection_status;
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
// startCountdown()
// This method parses the start and end times for the video recording,
// converts the times from dd-MM-yyyy hh:mm:ss to yyyy-MM-dd hh:mm:ss formats for timer and NTP
// and starts the countdown timer
//=============================================================================
bool Window::startCountdown(void)
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
        goButton->setStyleSheet(setButtonColour(RED).c_str());
        return false;
    }
    else if(stopUnixTime < strtUnixTime)
    {
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Please use a future stop time");
        goButton->setStyleSheet(setButtonColour(RED).c_str());
        return false;
    }
    else // start countdown to armtime
    {
        starttimer->start((strtUnixTime - currentUnixTime)*1000);
        countDownLabel->setText("Countdown to armtime");
        experiment_state = WAITING;
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Countdown to armtime");
        goButton->setStyleSheet(setButtonColour(GREEN).c_str());
         return true;
    }
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
        goButton->setStyleSheet(setButtonColour(GREEN).c_str());
    }
}


//=============================================================================
// receiveNodeDetailsButtonClicked()
// method to receive the nodes' coordinates.
//=============================================================================
void Window::receiveNodeDetailsButtonClicked(void)
{
    stringstream ss;      //stringstreams for formatting the strings correctly for updating the header file
    //string temp;
    cout << "receiving position" << endl;         //debugging
    fflush(stdout);

    //check to see if there are any clients connected
    if(server.getNoClients() == 0)
    {
        cout << "no clients\n" << endl;
        fflush(stdout);
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "No Nodes Connected");
        return;
    }
    cout << "noClients checked\n" << endl;         //debugging
    fflush(stdout);

    int errorcode = server.checkError(0);
    //if there were no errors setting up the sockets then receive data from nodes
    if(errorcode == 0)
    {
        cout << "no error\n" << endl;         //debugging
        fflush(stdout);
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "CNC Server Ready");
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Waiting for incoming connections...");
        QApplication::processEvents();   //This forces QApplication to output to statusBox before next process
        server.receiveData();
    }
    else //Usually the error is caused by leaving sockets open. If this happens just recompile the cnc controller and the node controller
    {
        cout << "error\n" <<  errorcode << endl;         //debugging
        fflush(stdout);
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "error receiving GPS data"); //Not sure why but server.checkError is always != 0 the first time.
        return;
    }


    //loop through all connected clients to get their positions and write the positions to the header file
    for(int k = 0; k < server.getNoClients(); k++)
    {
        errorcode = server.checkError(0);

        int nodeID = server.getNodeID(k);
//      cout << "loop 1\n" << endl;         //debugging
        fflush(stdout);
        if(errorcode == 4)
        {
            cout << "node " << nodeID << " not ready\n" << endl;
            statusBox->setTextColor("red");
            ss << "node" << nodeID;
            statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + ss.str().c_str()); //+ QString::fromStdString(temp) );
            ss.str("");             //clear stringstream
            continue;
        }
        else
        {
            cout << "node " << nodeID << " gave details\n" << endl;
            statusBox->setTextColor("green");
            ss << "node" << nodeID;
            statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + ss.str().c_str()); //+ QString::fromStdString(temp) );
            ss.str("");             //clear stringstream
        }

        statusBox->append("");
    }
    fflush(stdout);
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
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Opening mosaic view.");
    system("x-terminal-emulator -x -e \"cvlc --vlm-conf ../scripts/mosaic_view/mosaic.conf --mosaic-width=1280 --mosaic-height=720 --mosaic-keep-picture --mosaic-rows=2 --mosaic-cols=2 --mosaic-position=0 --mosaic-order=1,2,3,4\"");
}

//=============================================================================
// runNextlookButtonClicked()
//=============================================================================
void Window::runNextlookButtonClicked(void)
{
    statusBox->append("");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Launching NeXtLook on Cobalts.");
    system("../scripts/nextlook/run_nextlook.sh");
}

//=============================================================================
// sendFilesOverNetwork()
//=============================================================================
int Window::sendFilesOverNetwork(void)
{
    stringstream ss;
    int status;
    int hdr_ret;

 //   statusBox->append("");

    //GPSDOs
    //Update nodes armtime
    //ansible nodes -m copy -a "src=~/Desktop/AnsiNext/armtime.cfg dest=~/Desktop/NextGPSDO/armtime.cfg"
    ss << "ansible nodes -m copy -a \"src=" << ARMTIMECFG_PATH << " dest=/home/nextrad/Desktop/NextGPSDO/" << ARMTIMECFG_FILE << "\"";
    status = system(stringToCharPntr(ss.str()));     // system(stringToCharPntr(ss.str()));
    if (-1 != status)
    {
        hdr_ret = WEXITSTATUS(status);

        if(hdr_ret==0)
        {
            cout<< "Header file to GPSDOs successful\n" <<endl;
            statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to GPSDOs");
        }
        else
        {
            cout<< "Header file to GPSDOs NOT successful\n" <<endl;
            statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to GPSDOs");
            return hdr_ret;
        }
        statusBox->append("");
    }
    ss.str("");             //clear stringstream


    // Nodes
    // ss << "ansible nodes -m copy -a \"src=/home/nextrad/Documents/node_controller/NeXtRAD_Header.txt dest=/home/nextrad/Documents/node_controller/NeXtRAD_Header.txt\"";
    ss << "ansible nodes -m copy -a \"src=" << CNC_HEADER_PATH << " dest=" << NODE_HEADER_PATH << "\"";

    status = system(stringToCharPntr(ss.str()));     // system(stringToCharPntr(ss.str()));
    if (-1 != status)
    {
         hdr_ret = WEXITSTATUS(status);

         if(hdr_ret==0)
         {
             cout<< "Header file to nodes successful\n" <<endl;
             statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to nodes");
          }
         else
         {
             cout<< "Header file to nodes not successful\n" <<endl;
             statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to nodes");
             return hdr_ret;
         }
         statusBox->append("");
     }
     ss.str("");             //clear stringstream


     // Cobalts
     //ss << "ansible cobalts -m copy -a \"src=/home/nextrad/Documents/node_controller/NeXtRAD_Header.txt dest=/smbtest/NeXtRAD_Header.txt\"";
     ss << "ansible cobalts -m copy -a \"src=" << CNC_HEADER_PATH << " dest=/smbtest/" << HEADER_FILE << "\"";

     status = system(stringToCharPntr(ss.str()));     // system(stringToCharPntr(ss.str()));
     if (-1 != status)
     {
         hdr_ret = WEXITSTATUS(status);

         if(hdr_ret==0)
         {
             cout<< "Header file to cobalts successful\n" <<endl;
             statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File sent to cobalts");
          }
         else
         {
             cout<< "Header file to cobalts not successful\n" <<endl;
             statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Header File not sent to cobalts");
             return hdr_ret;
         }
         statusBox->append("");
     }
     ss.str("");             //clear stringstream


     ss << "ansible cobalts -m shell -a \"./run-cobalt.sh\"";

     status = system(stringToCharPntr(ss.str()));     // system(stringToCharPntr(ss.str()));
     if (-1 != status)
     {
         hdr_ret = WEXITSTATUS(status);

         if(hdr_ret==0)
         {
             cout<< "Primed cobalts successfully\n" <<endl;
             statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Run cobalts successful");
          }
         else
         {
             cout<< "Cobalts not primed successfully\n" <<endl;
             statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Run cobalts not successful");
             return hdr_ret;
         }
         statusBox->append("");
     }
     ss.str("");             //clear stringstream


     // TCUs
     // ToDo

}

//=============================================================================
// setArmTime()
//=============================================================================
void Window::resetHeaderFileTimes(void)
{
    Datetime datetime;
    std::string day, month, year, hour, minute, second;
    stringstream ss_armtime;

    year = datetime.getNowInYears();
    headerarmfiles.writeToHeaderFile("Timing", "YEAR", year);

    month = datetime.getNowInMonths();
    headerarmfiles.writeToHeaderFile("Timing", "MONTH", month);

    day = datetime.getNowInDays();
    headerarmfiles.writeToHeaderFile("Timing", "DAY", day);

    hour = datetime.getNowInHours();
    headerarmfiles.writeToHeaderFile("Timing", "HOUR", hour);

    minute = datetime.getNowInMinutes();
    headerarmfiles.writeToHeaderFile("Timing", "MINUTE", minute);

    second = datetime.getNowSecsPlusSecs(STARTTIMESECS);
    headerarmfiles.writeToHeaderFile("Timing", "SECOND", second);

    ss_armtime << "Date=" << day << "/" << month << "/" << year << "\n";
    ss_armtime << "Arm_Time=" << hour << ":" << minute << ":" << second;
    headerarmfiles.writeToArmtimecfgFile(ss_armtime.str());

    goButton->setStyleSheet(setButtonColour(GREEN).c_str());
}

//=============================================================================
// goButtonClicked()
// sends out header file to all units then starts countdown to armtime
//=============================================================================
int Window::goButtonClicked(void)
{
    int hdr_ret = 0;

    // start countdown
    if (startCountdown())
    {
        // sends out header file to all units
        hdr_ret = sendFilesOverNetwork();
    }
    return hdr_ret;
}

//=============================================================================
// setButtonColour(int colourno)
// sets button colour to light green = rgb(100,255,125),  light yellow = rgb(255,255,125) or light red = rgb(255,100,125)
//=============================================================================
string Window::setButtonColour(int colourno)
{
    string colourstr;
    if (colourno == GREEN)
    {
        colourstr = "* { background-color: rgb(100,255,125) }";  // light green
    }
    else if (colourno == AMBER)
    {
        colourstr = "* { background-color: rgb(255,255,125) }";  // light yellow
    }
    else
    {
        colourstr = "* { background-color: rgb(255,100,125) }";  // light red
    }
    return colourstr;
}
