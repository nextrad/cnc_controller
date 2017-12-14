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
//Edited by:    Shirley Coetzee
//Revision      5.0 (December 2017)


//=============================================================================
// Includes
//=============================================================================

#include "window.h"
#include <QPushButton>
#include <QApplication>
#include <QDateTime>
#include <QString>



//=============================================================================
// Constructor
//=============================================================================
Window::Window(QWidget *parent) : QWidget(parent)
{
    timMode = 0; //timer set to count down mode
    //Set size of window
    setFixedSize(600,590);

    initGUI();


    //connect to asterisk server and set up audio recording
    audioRecorder.connectToSocket();
    audioRecorder.loginAMI();
    audioRecorder.stopRecording();

    //Set up timers for start and end experiments and update countdown clock.
    //Note this is purely for display to monitor the time and does not directly affect the experiment
    stopUnixTime = time(NULL);
    starttimer = new QTimer(this);
    starttimer->setSingleShot(true);
    connect(starttimer, SIGNAL(timeout()), this, SLOT(startRecording()));

    endtimer = new QTimer(this);
    endtimer->setSingleShot(true);
    connect(endtimer, SIGNAL(timeout()), this, SLOT(stopRecording()));

    countDownTim = new QTimer(this);
    countDownTim->setInterval(1000);
    connect(countDownTim, SIGNAL(timeout()), this, SLOT(updateCountDownLCD()));
    countDownTim->start(1000);

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
//=============================================================================
//Method to close the CNC's server socket
void Window::closeServer()
{
    server.closeServer();
}


//=============================================================================
// initGUI()
//=============================================================================
//Method to initialise all the GUI features of the window
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
    countDownLabel->setGeometry(445, 500, 140, 20 ); //445, 410, 140, 20);
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
    updateHeaderFileButton = new QPushButton("Edit Header\nFile", this);
    updateHeaderFileButton->setGeometry(10, 130, 135, 50);
    connect(updateHeaderFileButton, SIGNAL (clicked(bool)), this, SLOT(updateHeaderFileButtonClicked(void)));

    //button for distributing header file to node controllers
    sendHeaderButton = new QPushButton("GO", this);
    sendHeaderButton->setGeometry( 250, 500, 135,50);                                    // 10, 190, 135, 50);
    sendHeaderButton->setStyleSheet("* { background-color: rgb(255,100,125) }");
    connect(sendHeaderButton, SIGNAL (clicked(bool)), this, SLOT(sendHeaderButtonClicked(void)));

    //button for showing video mosaic
    showVideoButton = new QPushButton("Start Video\nMosaic", this);
    showVideoButton->setGeometry(10, 250, 135, 50);
    connect(showVideoButton, SIGNAL (clicked(bool)), this, SLOT(showVideoButtonClicked(void)));
/*
    //button for starting the countdown timer display for the experiment
    startVideoRecordingCountDownButton = new QPushButton("Countdown to\nVideo Recording", this);
    startVideoRecordingCountDownButton->setGeometry(10, 310, 135, 50);
    connect(startVideoRecordingCountDownButton, SIGNAL (clicked(bool)), this, SLOT(startVideoRecordingCountDown(void)));

    //button for aborting recording and countdown
    abortVideoRecordingButton = new QPushButton("Abort\nVideo Recording", this);
    abortVideoRecordingButton->setGeometry(10, 310, 135, 50); //(10, 370, 135, 50);
    connect(abortVideoRecordingButton, SIGNAL (clicked(bool)), this, SLOT(abortVideoRecordingButtonClicked(void)));
*/
    //button for receiving node positions
    receiveNodeDetailsButton = new QPushButton("Receive Node\nDetails", this);
    receiveNodeDetailsButton->setGeometry(10, 430, 135, 50);
    connect(receiveNodeDetailsButton, SIGNAL (clicked(bool)), this, SLOT(receiveNodeDetailsButtonClicked(void)));
/*
    //close button
    closeButton = new QPushButton("Close", this);
    closeButton->setFont(QFont("Ubuntu",12));
    closeButton->setGeometry(400, 500, 135,50);
    connect(closeButton, SIGNAL (clicked(bool)), this, SLOT(closeButtonClicked(void)));
    closeButton->setFocusPolicy(Qt::NoFocus);
    */
}


/*
//=============================================================================
// closeButtonClicked()
//=============================================================================
void HeaderFileWindow::closeButtonClicked(void)
{
    switch(menu)
    {
        default:
            emit finished(0);
        break;
    }
}

*/
//=============================================================================
// connectionTestButtonClicked()
//=============================================================================
//Tests the connections to CNC
void Window::connectionTestButtonClicked(void)
{
    bool connection_status = true;

//    string address = "192.168.1.";
//    string temp = address;
//    temp.append("1");

    //Test if CNCHub is connected

//    temp = "cnc"; //address;
//    if(!testConnection(temp))
// //   if(!connectionManager.isConnected())
//    {
//        statusBox->setTextColor("red");
//        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + QString::fromStdString(temp) ); //+ "CNCHub not connected");
//        connection_status = false;
//    }
//    else
//    {
//        statusBox->setTextColor("green");
//        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + QString::fromStdString(temp) ); //+ "CNCHub connected");

        statusBox->append("");
        if(!testSubNetwork("1"))             //Test SubNetwork for Node 0
        {
            connection_status = false;
        }

       //statusBox->append("");
        if(!testSubNetwork("2"))            //Test SubNetwork for Node 1
        {
            connection_status = false;
        }

        //statusBox->append("");
        if(!testSubNetwork("3"))            //Test SubNetwork for Node 2
        {
            connection_status = false;
        }
  // }
/*
    if(connection_status)
    {
        //if everything is connected change button colour to green
        testConnectionButton->setText("Connected");
        testConnectionButton->setStyleSheet("* { background-color: rgb(100,255,125) }");
    }
    else
    {
        //if anything is not connected change button colour to red
        testConnectionButton->setText("Connection Error");
        testConnectionButton->setStyleSheet("* { background-color: rgb(255,100,125) }");
    }
    */
}


//=============================================================================
// testSubNetwork()
//=============================================================================
//Tests the connections to CNC
bool Window::testSubNetwork(QString NetID)
{
//    //Trying to highlight individual lines in statusbox
//    QTextEdit::ExtraSelection highlight;
//    highlight.cursor = statusBox->textCursor();
//    highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
//    highlight.format.setBackground( Qt::green );
//    QList<QTextEdit::ExtraSelection> extras;

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
//    connectionManager.connectionTest(stringToCharPntr(temp));
//    if(!connectionManager.isConnected())
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
    //    connectionManager.connectionTest(stringToCharPntr(temp));
    //    if(!connectionManager.isConnected())
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
    //    connectionManager.connectionTest(stringToCharPntr(temp));
    //    if(!connectionManager.isConnected())
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
    //    connectionManager.connectionTest(stringToCharPntr(temp));
    //    if(!connectionManager.isConnected())
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
    //    connectionManager.connectionTest(stringToCharPntr(temp));
    //    if(!connectionManager.isConnected())
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
//=============================================================================
//pings an address to see if it's connected to the network.
bool Window::testConnection(string address)
{
    string command = "ping -c 1 ";  // c = count
    command.append(address);

//    string command = "ansible ";     // "ping -c 2 ";
//    command.append(unitname);
//    command.append(" -m ping "); //-vvvv");

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
//=============================================================================
//Takes in a string and converts it to char*
char* Window::stringToCharPntr(string str)
{
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}


//=============================================================================
// startCountDown()
//=============================================================================
//This method parses the start and end times for the video recording,
//converts the times from dd-MM-yyyy hh:mm:ss to yyyy-MM-dd hh:mm:ss formats for timer and NTP
//and starts the countdown timer
void Window::startCountDown(void)
{
    //Open Header File
    ifstream headerFile (CNC_HEADER_PATH);

    printf("Header File opened\n");
    string temp;

    /*
	// dd-MM-yyyy hh:mm:ss
    while(!headerFile.eof())
    {
        getline(headerFile,temp);
        if(temp.substr(0,9) == "StartTime")     //looking for the "StartTime" in the header file
        {
            if (temp.substr(9,3) == " = ")
            {
                startTime = temp.substr(12,19);
            }
            else if ((temp.substr(9,2) == " =") || (temp.substr(9,2) == "= "))
            {
                startTime = temp.substr(10,19);
            }
            else if (temp.substr(9,1) == "=")
            {
                startTime = temp.substr(11,19);
            }
             printf("startTime = %s\n", startTime.c_str());
        }
        else if(temp.substr(0,7) == "EndTime")  //looking for the "EndTime" in the header file
        {
            if (temp.substr(7,3) == " = ")
            {
                endTime = temp.substr(10,19);
            }
            else if ((temp.substr(7,2) == " =") || (temp.substr(7,2) == "= "))
            {
                endTime = temp.substr(9,19);
            }
            else if (temp.substr(7,1) == "=")
            {
                endTime = temp.substr(8,19);
            }
            printf("endTime = %s\n", endTime.c_str());
        }
    }
    headerFile.close();

    Datetime datetime;

    // Get Unix time (seconds since 01/01/1970)
    currentUnixTime = time(NULL);

    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    std::cout << buf << std::endl;


    strtUnixTime = datetime.convertToUnixTime(startTime)+2;  // 2016-10-19 15:22:00 +2  = 146883322
    stopUnixTime = datetime.convertToUnixTime(endTime)+4;    // The camera has a 2 second buffer which is why 2 seconds were added to start and 4 to end time

    cout << "\ncurrentUnixTime " << currentUnixTime << "\nstrtUnixTime " << strtUnixTime  << "\nstopUnixTime " << stopUnixTime << endl;

    // Checking if the start and end times are in the past or not
    if(strtUnixTime < currentUnixTime)
    {
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Please use a future start time");
    }
    else if(stopUnixTime < strtUnixTime)
    {
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Please use a future stop time");
    }
    else
    {
        starttimer->start((datetime.convertToUnixTime(startTime)+ 2 - currentUnixTime)*1000);
        starttimer->start();
        //camera buffer stores 2 seconds, thus start two seconds later and record for 2 seconds longer.
        countDownLabel->setText("Countdown to armtime");
        timMode = 1;
        statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Countdown to armtime");
        statusBox->append("");
    }

    fflush(stdout);*/
}



//=============================================================================
// startRecording()
//=============================================================================
//Method to start the countdown until the end of the experiment
//Note: This is purely for display and recording audio not actually controlling the experiment
void Window::startRecording(void)
{
    timMode = 2;
    endtimer->start(( stopUnixTime - currentUnixTime)*1000);
    audioRecorder.startRecording();
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio recording started");
    countDownLabel->setText("Recording audio");
}


//=============================================================================
// stopRecording()
//=============================================================================
//Method to stop the countdown timer signalling end of experiment
//Note: This is purely for display and recording audio not actually controlling the experiment
void Window::stopRecording(void)
{
    timMode = 0;
    audioRecorder.stopRecording();
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio stopped");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio saved to /var/spool/Asterisk/");
    statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + "Audio relocated to /home/nextrad/Documents/Audio/output");
    countDownLabel->setText("Stopped recording");
}



//=============================================================================
// updateCountDownLCD()
//=============================================================================
// Updates the countdown LCD according.  timMode==0 - no active countdowns
//                                        timMode==1 - countdown until recording starts
//                                        timMode==2 - countdown until recording ends

void Window::updateCountDownLCD(void)
{
    Datetime datetime;

    currentUnixTime = time(NULL);
    if(timMode == 0)            //if no active countdowns
    {
        countDown->display("00:00:00");
    }
    else if(timMode == 1)       //if countdown until start
    {
        countDown->display(datetime.getCountDownTime(strtUnixTime - currentUnixTime));
    }
    else                        //if coundown until end
    {
        countDown->display(datetime.getCountDownTime(stopUnixTime - currentUnixTime));
    }

}



//=============================================================================
// updateHeaderFileButtonClicked()
//=============================================================================
//Opens a new menu to do with editing the header file
void Window::updateHeaderFileButtonClicked(void)
{
    QIcon icon("../media/icons/favicon2.ico");
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
}


//=============================================================================
// sendHeaderButtonClicked()
//=============================================================================
//sends out header file to all connected nodes
int Window::sendHeaderButtonClicked(void)
{

    // -------------------Send files over network  ---------------------------------------
    stringstream ss;
    int status;
    int hdr_ret;

    statusBox->append("");
    statusBox->append("");

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
    }
    ss.str("");             //clear stringstream
    statusBox->append("");


    // Nodes
//     ss << "ansible nodes -m copy -a \"src=/home/nextrad/Documents/node_controller/NeXtRAD_Header.txt dest=/home/nextrad/Documents/node_controller/NeXtRAD_Header.txt\"";
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
     }
     ss.str("");             //clear stringstream
     statusBox->append("");


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
     }
     ss.str("");             //clear stringstream
     statusBox->append("");


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
     }
     ss.str("");             //clear stringstream
     statusBox->append("");


     // TCUs
     // ToDo


     // start countdown
     startCountDown();

     return hdr_ret;
}


//=============================================================================
// receiveNodeDetailsButtonClicked()
//=============================================================================
//method to receive the nodes' coordinates.
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
            //fflush(stdout);
            //ss << "Client " << (int) k << " wasn't ready to send position";
            //statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + ss.str().c_str());
            statusBox->setTextColor("red");
            ss << "node" << nodeID;
            statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      X     ") + ss.str().c_str()); //+ QString::fromStdString(temp) );
            ss.str("");             //clear stringstream
            continue;
        }
        else
        {
            cout << "node " << nodeID << " gave details\n" << endl;
            //cout << "client ready. position received\n" << endl;         //debugging
            //fflush(stdout);
            //ss << "Node " << server.getNodeID(k) << " position received";
            //statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm   ") + ss.str().c_str());
            statusBox->setTextColor("green");
            ss << "node" << nodeID;
            statusBox->append(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm      _     ") + ss.str().c_str()); //+ QString::fromStdString(temp) );
            ss.str("");             //clear stringstream
        }

        statusBox->append("");


        //For node 0 both Tx and Rx1's positions must be updated
//        int nodeID = server.getNodeID(k);
//        fflush(stdout);

        /*
        if(nodeID == 0) // Set Tx and Rx locations
        {

//            if(errorcode == 4)
//            {
//                server.resetError(k);
//                return;
//            }

            ss.str("");             //clear stringstream
            ss << server.getGPSLat(k);
            fflush(stdout);
            headerarmfiles->writeToHeaderFile("TxLocationLat", ss.str(), "Geometry");
            headerarmfiles->writeToHeaderFile("Rx1LocationLat", ss.str(), "Geometry");

            ss.str("");             //clear stringstream
            ss << server.getGPSLon(k);
            fflush(stdout);
            headerarmfiles->writeToHeaderFile("TxLocationLon", ss.str(), "Geometry");
            headerarmfiles->writeToHeaderFile("Rx1LocationLon", ss.str(), "Geometry");

            ss.str("");             //clear stringstream
            ss << server.getGPSHt(k);
            fflush(stdout);
            headerarmfiles->writeToHeaderFile("TxLocationHt", ss.str(), "Geometry");
            headerarmfiles->writeToHeaderFile("Rx1LocationHt", ss.str(), "Geometry");

            ss.str("");             //clear stringstream
            ss << server.getGPSStability(k);
            fflush(stdout);
            headerarmfiles->writeToHeaderFile("TxLocationStability", ss.str(), "Geometry");
            headerarmfiles->writeToHeaderFile("Rx1LocationStability", ss.str(), "Geometry");

        }
        else // Set only Rx locations
        {
            ss.str("");             //clear stringstream
            varName.str("");

//            if(server.checkError(k) == 4)
//            {
//                server.resetError(k);
//                return;
//            }


            ss << server.getGPSLat(k);
            fflush(stdout);
            varName << "Rx" << (nodeID+1) << "LocationLat";
            headerarmfiles->writeToHeaderFile(varName.str(), ss.str(), "Geometry");
            fflush(stdout);

            ss.str("");             //clear stringstream
            varName.str("");
            varName << "Rx" << (nodeID+1) << "LocationLon";
            ss << server.getGPSLon(k);
            fflush(stdout);
            headerarmfiles->writeToHeaderFile(varName.str(), ss.str(), "Geometry");

            ss.str("");             //clear stringstream
            varName.str("");
            ss << server.getGPSHt(k);
            fflush(stdout);
            varName << "Rx" << (nodeID+1) << "LocationHt";
            headerarmfiles->writeToHeaderFile(varName.str(), ss.str(), "Geometry");

            ss.str("");             //clear stringstream
            varName.str("");
            ss << server.getGPSStability(k);
            fflush(stdout);
            varName << "Rx" << (nodeID+1) << "LocationStability";
            headerarmfiles->writeToHeaderFile(varName.str(), ss.str(), "Geometry");

        }
    */

 // Shirley moved this to sendHeaderClicked()
 //       // add a cnc timestamp to the header file
 //      temp = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss").toUtf8().constData();
 //       headerarmfiles->writeToHeaderFile("TimeStamp", temp, "Time Stamp");
    }
    fflush(stdout);
}


//=============================================================================
// abortVideoRecordingButtonClicked()
//=============================================================================
//Method to abort the video recording. Stops video recording countdown timers and recording
void Window::abortVideoRecordingButtonClicked(void)
{
    //stop all timers
    if(timMode == 1)
    {
        starttimer->stop();
    }
    else if(timMode == 2)
    {
        stopRecording();
        endtimer->stop();
    }

    //set timer mode to 'no active countdowns'
    timMode = 0;
    countDownLabel->setText("Video rec aborted!");
}

//=============================================================================
// showVideoButtonClicked()
//=============================================================================
//Method to show the video mosaic.
void Window::showVideoButtonClicked(void)
{
    system("x-terminal-emulator -x -e \"cvlc --vlm-conf ../scripts/mosaic_view/mosaic.conf --mosaic-width=1280 --mosaic-height=720 --mosaic-keep-picture --mosaic-rows=2 --mosaic-cols=2 --mosaic-position=0 --mosaic-order=1,2,3,4\"");
}
