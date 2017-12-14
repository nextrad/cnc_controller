//Class:        AudioConnectionManager
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       Darryn Jordan
//Created:      November 2015
//Version       1.0 (April 2016)
//Edited by:    David Bissett
//Revision      2.0 (December 2016)
//Edited by:    Shirley Coetzee

#include "audio_connection_manager.h"


AudioConnectionManager::AudioConnectionManager(void)  : socket(service)
{
    socketEndpoint.address(ip::address::from_string(TELNET_HOST));
    socketEndpoint.port(AUDIO_TELNET_PORT);
}


void AudioConnectionManager::clearSocketBuffer(void)
{
    for (int i = 0; i < SOCKET_BUFFER_SIZE; i++)
    {
        socketBuffer[i] = ' ';
    }
}


void AudioConnectionManager::connectToSocket(void)
{
    cout << "Attempting to establish connection to Asterisk server..." << endl;
    try
    {
        socket.connect(socketEndpoint); //attempt to connect to the endpoint, if no exception is thrown the connection is successful
        printf("Connection Active!\n\n");
        //readFromSocket();
    }
    catch (boost::system::system_error const& e) //exception was thrown, connection failed
    {
        cout << "Exiting: could not " << e.what();
        exit(0);
        //connectToSocket(); //restart connection
    }
}


void AudioConnectionManager::loginAMI(void)
{
    writeToSocket("Action: Login"); //Login
    writeToSocket("ActionID: 1");
    writeToSocket("Username: admin");
    writeToSocket("Secret: admin");
    writeToSocket("");
    //readFromSocket();
    writeToSocket("Action: Events"); //Turn Event Logging Off
    writeToSocket("ActionID: 2");
    writeToSocket("EventMask: off");
    writeToSocket("");
    //readFromSocket();
}


void AudioConnectionManager::beepAMI(void)
{
    writeToSocket("Action: Originate", PRIVATE); //start recording
    writeToSocket("ActionID: 6", PRIVATE);
    writeToSocket("Channel: LOCAL/101", PRIVATE);
    writeToSocket("Application: Playback", PRIVATE);
    writeToSocket("Data: /home/nextrad/tones/", PRIVATE);
    writeToSocket("", PRIVATE);
}


void AudioConnectionManager::writeToSocket(string message, WritePrivacy privacy)
{
    socket.write_some(buffer(message + (string)"\n")); //write to the socket

    if (privacy == PUBLIC)
    {
        if ( message != "")
        {
            cout << "~" << message << endl;   //echo to console
        }
        else
        {
            cout << endl;
        }
    }
}


void AudioConnectionManager::readFromSocket(void)
{
    clearSocketBuffer();
    socket.read_some(buffer(socketBuffer)); //read terminal response to the buffer array
    //cout << socketBuffer << endl;         	//echo to console
}


void AudioConnectionManager::startRecording(void)
{
    printf("Initializing audio recording...\n\n");

    Datetime datetime;

    string record_command = "RecordFile: /var/spool/asterisk/" + datetime.getTimeAndDate("%d.%m.%Y_%I:%M:%S") + ".wav";  //the only location available for recording
    printf("\nSaving %s\n", record_command.c_str());

    writeToSocket("Action: ConfbridgeStartRecord");
    writeToSocket("ActionID: 3");
    writeToSocket("Conference: 100");
    writeToSocket(record_command);
    writeToSocket("");

    printf("\nWaiting for audio recording to begin...\n\n");
    //waiting in a while loop would make the whole program hang and should rather be done with a QTimer
    //I thought it would be better to be able to start and stop the audio recording with a button
/*
    time_t oldTime;
    time_t currentTime = time(NULL);

    while (currentTime != startTime)
    {
        currentTime = time(NULL);

        if (currentTime == startTime)
        {
            cout << startTime - currentTime << "s to start\n";
            break;
        }

        if (currentTime != oldTime)
        {
            cout << startTime - currentTime << "s to start\n";
        }

        oldTime = currentTime;
    }
*/
    printf("\nRecording audio ...\n");
    writeToSocket("");
/*
    while (currentTime <= endTime)
    {
        currentTime = time(NULL);

        if (currentTime == endTime)
        {
            cout << "Time Elapsed: " << currentTime - startTime << "s" << endl;
            break;
        }

        if (currentTime != oldTime)
        {
            beepAMI();
            cout << "Time Elapsed: " << currentTime - startTime << "s" << endl;
        }
        oldTime = currentTime;
    }*/
}

void AudioConnectionManager::stopRecording(void)
{
    printf("Terminating audio recording...\n");

    writeToSocket("Action: ConfbridgeStopRecord"); //start recording
    writeToSocket("ActionID: 4");
    writeToSocket("Conference: 100");
    writeToSocket("");
    sleep(2);
    readFromSocket();

    system("sudo ../Audio/Asterisk/scripts/relocate_audio_files.sh");
}


void AudioConnectionManager::logoutAMI()
{
    writeToSocket("Action: Logoff");
    writeToSocket("ActionID: 5");
    writeToSocket("");
    //readFromSocket();
    exit(0);
}





