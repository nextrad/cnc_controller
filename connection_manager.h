//Author:       Darryn Jordan
//Edited By:    David Bissett
//Class:        ConnectionManager
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      November 2015
//Last Edited:  May 2016

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "includes.h"
#include "parameters.h"

class ConnectionManager
{
    private:
        char socketBuffer[SOCKET_BUFFER_SIZE];
        io_service service;
        ip::tcp::socket sockets;
        ip::tcp::endpoint remoteEndpoint;
        string password;
        bool connection;

    public:
        ConnectionManager(void);
        void connectionTest(char *addr);
        bool isConnected(void);
        string receiveGPSdata(void);
        char* stringToCharPntr(string str);
};

#endif // CONNECTIONMANAGER_H
