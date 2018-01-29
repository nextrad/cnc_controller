//Author:       David Bissett
//Class:        NetworkManager
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      May 2016
//Last Edited:  June 2016

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QWidget>
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <stdint.h> //int16_t
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sstream>
#include <thread>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "parameters.h"
#include <fstream>
#include <mutex>
//Can't import includes.h because boost library causes method overloading

using namespace std;

class NetworkManager
{
    private:
        int socket_desc , client_sock[3], c ;
        struct sockaddr_in server , client[];
        int portNumber;
        int error[3];
        double gpsLat[3], gpsLon[3], gpsHt[3];
        int nodeID[3],clientIDs[3];
        std::thread clientThread, getTSThread[3];
        int noClients;
        bool endServer;
        void acceptClients(void);
        void removeClient(int clientID);
        void checkTimeStamp(int nodeNum);
        char* stringToCharPntr(string str);
        bool finished;
        //bool received_message[3];
        std::mutex m;

    public:
        NetworkManager();
        ~NetworkManager();
        void receiveData(void);
        int checkError(int clientID);
        void resetError(int clientID);
        int getNodeID(int clientID);
        double getGPSLat(int clientID);
        double getGPSLon(int clientID);
        double getGPSHt(int clientID);
        int getNoClients();

    public slots:
        void closeServer();
};

#endif // NETWORKMANAGER_H
