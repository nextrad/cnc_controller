//Class:        AudioConnectionManager
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       Darryn Jordan
//Created:      November 2015
//Version       1.0 (April 2016)
//Edited by:    David Bissett
//Revision      2.0 (December 2016)
//Edited by:    Shirley Coetzee
//Revision      3.0 (May 2018)
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
    }
    catch (boost::system::system_error const& e) //exception was thrown, connection failed
    {
        cout << "Exiting: could not " << e.what();
        exit(0);
    }
}


void AudioConnectionManager::loginAMI(void)
{
    writeToSocket("Action: Login"); //Login
    writeToSocket("ActionID: 1");
    writeToSocket("Username: admin");
    writeToSocket("Secret: admin");
    writeToSocket("");

    writeToSocket("Action: Events"); //Turn Event Logging Off
    writeToSocket("ActionID: 2");
    writeToSocket("EventMask: off");
    writeToSocket("");
}


void AudioConnectionManager::beepAMI(void)
{
    stringstream ss_data;
    ss_data << "Data: " << TONES_PATH;

    writeToSocket("Action: Originate");
    writeToSocket("ActionID: 6");
    writeToSocket("Channel: LOCAL/101");
    writeToSocket("Application: Playback");
    writeToSocket(ss_data.str().c_str());
    writeToSocket("");
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
}


void AudioConnectionManager::startRecording(void)
{
    Datetime datetime;

    string record_command = "RecordFile: /var/spool/asterisk/" + datetime.getTimeAndDate("%d.%m.%Y_%I:%M:%S") + ".wav";  //the only location available for recording
    printf("\nSaving %s\n", record_command.c_str());

    writeToSocket("Action: ConfbridgeStartRecord");
    writeToSocket("ActionID: 3");
    writeToSocket("Conference: 100");
    writeToSocket(record_command);
    writeToSocket("");
    printf("\nWaiting for audio recording to begin...\n");
    printf("Recording audio ...\n");
    writeToSocket("");

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

    int status = system("sudo ../scripts/audio/relocate_audio_files.sh");
    if (-1 != status)
    {
        int ret = WEXITSTATUS(status);
        if(ret!=0)
        {
            cout << "Audio_files FAILED to relocate correctly" << endl;
        }
    }
}


void AudioConnectionManager::logoutAMI()
{
    writeToSocket("Action: Logoff");
    writeToSocket("ActionID: 5");
    writeToSocket("");
    exit(0);
}





