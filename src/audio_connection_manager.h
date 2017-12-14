//Author:       Darryn Jordan
//Edited By:    David Bissett
//Class:        AudioConnectionManager
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      November 2015
//Last Edited:  April 2016

#ifndef AUDIO_CONNECTION_MANAGER_H
#define AUDIO_CONNECTION_MANAGER_H

#include "includes.h"
#include "parameters.h"
#include "datetime.h"

class AudioConnectionManager
{
    private:
        char socketBuffer[SOCKET_BUFFER_SIZE];
        io_service service;
        ip::tcp::socket socket;
        ip::tcp::endpoint socketEndpoint;
        string password;
        string ipCameraAddress;
        string cameraOverlayConfig;

    public:
        AudioConnectionManager(void);
        void writeToSocket(string, WritePrivacy = PRIVATE);
        void readFromSocket(void);
        void clearSocketBuffer(void);
        void connectToSocket(void);
        void configureVideoStream(void);
        void startRecording(void);
        void stopRecording(void);
        void loginAMI(void);
        void logoutAMI(void);
        void beepAMI(void);
};


#endif // AUDIO_CONNECTION_MANAGER_H
