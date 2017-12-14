//Class:        NetworkManager
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Author:       David Bissett
//Created:      May 2016
//Version       1.0 (June 2016)
//Edited by:    Shirley Coetzee
//Revision      2.0 (December 2016)
//Edited by:    Shirley Coetzee
//Revision      3.0 (December 2017)


//=============================================================================
// Includes
//=============================================================================
#include "networkmanager.h"


//=============================================================================
// Constructor
//=============================================================================
NetworkManager::NetworkManager()
{
    for(int i=0; i<3; i++)      //init with no error
    {
        error[i] = 0;
        nodeID[i] = -1;         //this stores the nodes number. Eg. if node 1 connects first then nodeID[0] is assigned 1
        gpsHt[i] = -1;
        gpsLat[i] = -361;
        gpsLon[i] = -361;
        clientIDs[i] = -1;          //Each index relates to the nodes numbers. The values stored at these indices relate to the order in which the nodes connected. It's the inverse of nodeID[]
        //received_message[i] = false;
    }

    endServer = false;
    noClients = 0;
    //the port to host the server on
    int portNumber = 8888;

    //Create socket
    //set socket to use AF_INET(IP), SOCK_STREAM(TCP) protocols)
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
        for(int i=0; i<3; i++)
        {
            error[i] = 1;
        }
        cout << " error 1: socket error\n";
    }
    cout << "Socket created" << endl;

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( portNumber ); //specify which port to use here NB

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        for(int i=0; i<3; i++)
        {
            error[i] = 2;
        }
        cout << " error 2: binding error\n";
        return;
    }
    printf("bind done on port %d \n", portNumber);
//--------------------------------------------------------------------------

    //Create a listener for connections using previously setup server socket with a maximum of 3 connections
    listen(socket_desc , 3);
    c = sizeof(struct sockaddr_in);

    cout << "Waiting for incoming connections..." << endl;

    clientThread = std::thread([this](){this->acceptClients();});
}


//=============================================================================
// closeServer()
//=============================================================================
void NetworkManager::closeServer()
{
    endServer = true;
    cout << "Closing clients...\n";
    while(noClients > 0)
    {
        removeClient(noClients - 1);
    }

    cout << "Closing server!" << endl;
    close(socket_desc);
    exit(0);
}


//=============================================================================
// Destructor
//=============================================================================
//method to properly close socket when NetworkManager object is destroyed
NetworkManager::~NetworkManager()
{
    endServer = true;
    clientThread.join();
    cout << "Closing clients...\n";
    while(noClients > 0)
    {
        close(client_sock[noClients - 1]);
        cout << "Client " << (noClients - 1) << " closed\n";
        getTSThread[noClients - 1].join();
        cout << "Thread " << (noClients - 1) << " joined\n";
        noClients--;
    }

    cout << "Closing server!" << endl;
    close(socket_desc);
}


//=============================================================================
// receiveData()
//=============================================================================
//Method to receive the position data from Nodes
void NetworkManager::receiveData(void)
{
    std::stringstream ss;
    /*
    cout << "receiving data" << endl;           //debugging
    fflush(stdout);
    cout << "receiving data now" << endl;           //debugging
    fflush(stdout);

    fd_set rfds;
    struct timeval tv;

    tv.tv_sec = 5;  //delay before recv() times out
    tv.tv_usec = 0;
    int rv;
*/
    if(noClients <= 0)
    {
        printf("There are %d clients",noClients);
        return;
    }
    else
    {
        for(int k=0;k<noClients;k++)
        {
/*
            FD_ZERO(&rfds); // clear the file descriptor set
            FD_SET(client_sock[k], &rfds); // add our file descriptor to the set
            sleep(0.05);
            //Set the timeout using select()
            //Not very sure how select() works but need it for timeout otherwise the program could hang forever or until data is received.
            rv = select(client_sock[k] + 1, &rfds, NULL, NULL, &tv);    //when using select the first parameter must be 1 more than the highest file descriptor.
            if(rv == 0)
            {
                error[k] = 4;
                printf("Connection timed out for client %d \n",k);
                continue;
            }
            if(rv > 0)
            {
                int64_t dataSize = 0;

                //Receive a message from client code waits here for a message
                //(this method returns a value if returned value is 0 client has disconnected)
                if(recv(client_sock[k] , &dataSize , sizeof(dataSize) , 0) == 0)
                {
                    cout << " Client Disconnected\n";
                    removeClient(k);
                    k--;            //decrement k to accommodate reshuffling of client file descriptors
                    continue;
                }

                if(dataSize == 4)      // If the next bytes of data are node's position
                {
                    double data [dataSize]; //Declare memory to store array of size dataSize

                    recv(client_sock[k] , &data , sizeof(data) , 0);
                    printf("Position received from client %d!\n", k);
                    nodeID[k] = data[0];
                    gpsLat[k] = data[1];
                    gpsLon[k] = data[2];
                    gpsHt[k] = data[3];

                    cout << "Sending ack..." << endl;
                    //send the size of the array so that the receiver knows what to expect
                    write(client_sock[k], &dataSize, sizeof(dataSize));
                    //next we send the actual array
                    write(client_sock[k], data, sizeof(data));
                    cout << "Ack sent." << endl;

                    //received_message[k] = true;
                }
            }*/

            int nodeID = getNodeID(k);
            //fflush(stdout);

            //    Fetch gps info file
            //    ansible nodes -m fetch -a "src=~/Desktop/NextGPSDO/gps_info.cfg dest=~/Desktop/AnsiNext/"
            ss << "ansible node" << (int) nodeID << " -m fetch -a \"src=/home/nextrad/Documents/NextGPSDO/gps_info.cfg dest=/home/node" << (int) nodeID << "/Documents/AnsiNext/\"";
            int status = system(stringToCharPntr(ss.str()));     // system(stringToCharPntr(ss.str()));
            if (-1 != status)
            {
                int hdr_ret = WEXITSTATUS(status);

                if(hdr_ret==0)
                {
                    cout<<"Fetch gps info file successful"<<endl;
                }
                else
                {
                    cout<<"Fetch gps info file not successful"<<endl;
                 }
            }

            // Parse gps data file

            //Open GPS File
            ifstream gpsFile ("/home/nextrad/Documents/NextGPSDO/gps_info.cfg");
            printf("GPS File opened\n");
            string temp;

            // ToDo 3/12/17

            while(!gpsFile.eof())
            {
                 getline(gpsFile,temp);
          /*      if(temp.substr(0,9) == "StartTime")     //looking for the "StartTime" in the header file
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
                }*/
            }
            gpsFile.close();

            // Save gps data

            // ToDo 3/12/17
//            nodeID[k] = data[0];
//            gpsLat[k] = data[1];
//            gpsLon[k] = data[2];
//            gpsHt[k] = data[3];
//            gpsStability[k] = data[4];
        }
    }

}


//=============================================================================
// getNoClients()
//=============================================================================
//Method to return the number of connected clients
int NetworkManager::getNoClients()
{
    return noClients;
}


//=============================================================================
// acceptClients
//=============================================================================
//This method is run as a separate thread and accepts new client and adds their file descriptors to client_sock[]
void NetworkManager::acceptClients(void)
{
    int temp = 0;
    int8_t dataSize = 1;
    int8_t data;

    noClients = 0;
    while(!endServer)
    {
        if(noClients < 3)
        {
            //accept connection from an incoming client
            //the code will wait on this line until a client connects...
            temp = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
            if((noClients != 0 && temp != client_sock[noClients - 1]) || noClients == 0)  //There was a problem of accepting a client twice so this checks if the new client has the same file descriptor
            {
                client_sock [noClients] = temp;
                cout << "Client connecting!..." << noClients << endl;

                //if there's a problem the accept function returns -1 so we check for that
                if (client_sock [noClients] < 0)
                {
                    perror("accept failed");
                    error[noClients] = 3;
                    cout << " error 3: accepting error\n";
                    return;//////////////////////////////////////Should have a better error handling
                }
                cout << "Connection accepted " << client_sock[noClients] << endl;

                //Check which node connected
                recv(client_sock[noClients], &dataSize, sizeof(dataSize), 0);
                recv(client_sock[noClients], &data, dataSize, 0);
                nodeID[noClients] = data;
                printf("Node %d Connected\n", nodeID[noClients]);
                clientIDs[nodeID[noClients]] = noClients;
                //Check if node has already been connected if so, then clean up old file descriptors etc.
                for(int i=0;i<noClients;i++)
                {
                    if(nodeID[i] == nodeID[noClients])
                    {
                        cout << "same client" << endl;
                        fflush(stdout);
                        removeClient(i);
                        cout << "Client reconnected" << endl;           //debugging
                    }
                }
                getTSThread[nodeID[noClients]] = std::thread([this](){this->checkTimeStamp(noClients);});        //make a thread that will send node current header file time stamp
                noClients++;
            }
            fflush(stdout);         //this line forces stdout to output so that you know what's happening in this thread
        }
    }
}


//=============================================================================
// sendToClients()
//=============================================================================
//This method sends the header file to the nodes
//This method no longer gets called. Instead scp is used to transfer the header file as it is simpler.
void NetworkManager::sendToClients(void) //char* hFile [], int8_t len [])
{/*
    if(noClients <= 0)
    {
        printf("There are %d clients",noClients);
        return;
    }
    fd_set rfds;
    struct timeval tv;

    tv.tv_sec = 20;  //delay before recv() times out
    tv.tv_usec = 0;
    int rv;

    std::vector<char> data;     //Used vectors because they behave like normal arrays but can change size easily
    std::vector<char> ack;
    int8_t dataSize = 1;
    bool is_equal;
    int n = 0;

    //Loop through all connected clients
    for(int k=0;k<noClients;k++)
    {
        //Loop through the H_FILE_LENGTH lines of the Header file. Should be set as a Macro in the future as header file will change.
        for(int j = 0; j < H_FILE_LENGTH && error[k]== 0; j++)
        {
            //Loop until there are no discrepancies between sent and echoed data
            is_equal = false;
            while(!is_equal && error[k] == 0)
            {
                //populate the vector with data
                dataSize = len[j];
                for(int i=0;i<len[j];i++)
                {
                    data.push_back( hFile[j][i]);
                }

                //Send size of line first then the actual text
                n = write(client_sock[k], &dataSize, sizeof(dataSize));
                if(n < 0)      //if client has disconnected         Note: write() returns -1 if the client has disconnected
                {
                    removeClient(k);
                    //received_message = false;
                    return;
                }
                n = write(client_sock[k], &data[0], len[j]);            //because we're using chars which have a size of one byte the size of the data is the same number as the length

                //check if client times out
                FD_ZERO(&rfds); // clear the file descriptor set
                FD_SET(client_sock[k], &rfds); // add our file descriptor to the set
                sleep(0.05);
                //Set the timeout using select()
                //Not very sure how select() works but need it for timeout otherwise the program could hang forever or until data is received.
                rv = select(client_sock[k] + 1, &rfds, NULL, NULL, &tv);    //when using select the first parameter must be 1 more than the highest file descriptor.
                if(rv == 0)
                {
                    error[k] = 4;
                    printf("Connection timed out for client %d \n",k);
                    break;
                }

                //Nodes will echo back the messages that they receive for error checking and to know that they're still connected
                n = recv(client_sock[k], &dataSize, sizeof(dataSize), 0);
                if( n == 0)   //if client has disconnected          Note recv() returns 0 if client has disconnected
                {
                    removeClient(k);
                    //received_message = false;
                    return;
                }
                else
                {
                    n = recv(client_sock[k], &ack[0], dataSize, 0);

                    //check that the echoed message is the same as the sent one
                    if ( data.size() < ack.size() )
                    {
                        is_equal = std::equal ( data.begin(), data.end(), ack.begin() );
                    }
                    else
                    {
                        is_equal = std::equal ( ack.begin(), ack.end(), data.begin() );
                    }
                }
                data.clear();       //clear the vector
            }
        }
        dataSize = (int8_t)2;

        //Send end of file code: "~~"
        write(client_sock[k], &dataSize, sizeof(dataSize));
        write(client_sock[k], "~~", 2);                     //I chose end of file code to be "~~" but it can be changed to anything as long as it's also changed on node side
        printf("Header File Sent to client %d\n", k);
        fflush(stdout);
    }
    //received_message = false;
    m.unlock();*/
}


//=============================================================================
// removeClient
//=============================================================================
//this method disconnects the client and removes them from client_sock[]
void NetworkManager::removeClient(int clientID)
{
    try
    {
        getTSThread[nodeID[clientID]].join();
    }
    catch(exception& e) //the error that usually occurs says "Resource deadlock avoided". This is usually caused when trying to join the thread after it's already been joined.
    {
        cout << e.what() << endl;    //debugging
    }

    cout << "thread joined" << endl;           //debugging
    fflush(stdout);
    sleep(0.5);     //wait for all thread to be cleaned up after closing
    close(client_sock[clientID]);
    client_sock[clientID] = 0;
    noClients--;

    //make sure all arrays are shifted to cater for the removed client
    for(int i = clientID; i < 2; i++)
    {
        client_sock[i] = client_sock[i +1];
        nodeID[i] = nodeID[i +1];
        gpsLat[i] = gpsLat[i +1];
        gpsLon[i] = gpsLon[i +1];
        gpsHt[i] = gpsHt[i +1];
        //received_message[i] = received_message[i + 1];
    }
    nodeID[noClients + 1] = -1;

    for(int i=0;i<3; i++)
    {
        if(clientIDs[i] == clientID)
        {
            clientIDs[i] = -1;
        }
    }
    puts("client removed\n");
    fflush(stdout);         //flush stdout to make sure messages are ouputted
}


//=============================================================================
// checkError()
//=============================================================================
//This method is used to check which error was encountered when creating the server and connecting to the clients
int NetworkManager::checkError(int clientID)
{
    int temp = error[clientID];
    error [clientID]= 0;

    if(temp >= 0)
    {
        return temp;
    }
    else
    {
        return (int) 0;     //There was a weird error where occasionally 'error' was initialised as NULL when there were no errors so it returns zero in that case
    }
}


//=============================================================================
// setError()
//=============================================================================
//This method is used to check which error was encountered when creating the server and connecting to the clients
void NetworkManager::resetError(int clientID)
{
    error [clientID]= 0;
}


//=============================================================================
// checkTimeStamp()
//=============================================================================
//This method is used to check which error was encountered when creating the server and connecting to the clients
void NetworkManager::checkTimeStamp(int nodeNum)
{
    nodeNum--;      //by the time this thread starts the value of noClients has already incremented. This still affects the nodeNum parameter somehow
    nodeNum = nodeID[nodeNum];
    cout << "Node ID " << nodeNum << endl;  //debugging
    bool file_read = false;

    fd_set rfds;
    struct timeval tv;

    tv.tv_sec = 5;  //delay before recv() times out
    tv.tv_usec = 0;
    int rv;
    string str;

   while(!endServer)
   {
        //m.lock();
        FD_ZERO(&rfds); /* clear the file descriptor set */
        FD_SET(client_sock[clientIDs[nodeNum]], &rfds); /* add our file descriptor to the set */
        sleep(0.05);
        //Set the timeout using select()
        //Not very sure how select() works but need it for timeout otherwise the program could hang forever or until data is received.
        rv = select(client_sock[clientIDs[nodeNum]] + 1, &rfds, NULL, NULL, &tv);    //when using select the first parameter must be 1 more than the highest file descriptor.
        if(rv == 0)
        {
            error[clientIDs[nodeNum]] = 4;
            //printf("Connection timed out for client %d \n",nodeNum);        //debugging
        }
        if(rv > 0)
        {
            int8_t dataSize = 0;

            //Receive a message from client code waits here for a message
            //(this method returns a value if returned value is 0 client has disconnected)
            if(recv(client_sock[clientIDs[nodeNum]] , &dataSize , sizeof(dataSize) , 0) == 0) //read into dataSize the first 16 bytes (sizeof(dataSize) = 16)
            {
                cout << " Client Disconnected\n";
                removeClient(clientIDs[nodeNum]);
            }

            if(dataSize == 6)
            {
                char data [dataSize]; //Declare memory to store array of size dataSize

                recv(client_sock[clientIDs[nodeNum]] , &data , sizeof(data) , 0); //read bytes equal to 16*data.length
                printf("Position received from client %s!\n", data);
                if(strcmp(data,"~~~~~~") == 0)
                {
                    cout << "message received" << endl;
                    fflush(stdout);

                    try
                    {
                        ifstream rfile (HEADER_FILE);
                        fflush(stdout);
                        string temp = "";
                        int pos = -1;

                        //find line with corresponding variable's name and find position of the variable's value on that line
                        while(!rfile.eof())
                        {
                            getline(rfile,temp);
                            if(temp.find("Time Stamp") != string::npos)
                            {
                                pos = -2;                                                   //pos = -2 is just to indicate that the section was found
                            }
                            if(pos == -2)
                            {
                                if(temp.find("TimeStamp") != string::npos)                      //if the variable's name is found
                                {
                                    pos = temp.find_first_of('=') + 2;                       //+2 because data starts after "= "
                                    break;
                                }
                            }
                        }
                        rfile.close();

                        //extract timestamp from file
                        str = temp.substr(pos, temp.find_last_of(';') - pos);
                        if(pos < 0)
                        {
                            str = "error: can't find variable";
                        }
                        cout << str << endl;
                        file_read = true;
                    }
                    catch(std::out_of_range&)
                    {
                        cout << "File busy" << endl;
                        //exception if file is being used somewhere else
                        //set file_read = false to make sure that it trys to read it again
                        file_read = false;
                    }
                }

                char* chr = stringToCharPntr(str);

                dataSize = 19;
                char timestamp[dataSize];
                for(int j=0;j<dataSize;j++)
                {
                    timestamp[j] = chr[j]; //populated one by one because strings were being corrupted for some reason
                }


                cout << timestamp << endl;
                write(client_sock[clientIDs[nodeNum]], &dataSize, sizeof(dataSize));
                //next we send the actual array
                write(client_sock[clientIDs[nodeNum]], &timestamp, dataSize);
                cout << "timestamp sent." << endl;
            }
            else if(dataSize == 4)      // If the next bytes of data are node's position
            {
                receiveData();
                /*
                int64_t sizeOfData = 4;
                double data [sizeOfData]; //Declare memory to store array of size dataSize

                recv(client_sock[nodeNum] , &data , sizeof(data) , 0);
                printf("Position received from client %d!\n", nodeNum);
                nodeID[nodeNum] = data[0];
                gpsLat[nodeNum] = data[1];
                gpsLon[nodeNum] = data[2];
                gpsHt[nodeNum] = data[3];

                cout << "Sending ack..." << endl;
                //send the size of the array so that the receiver knows what to expect
                write(client_sock[nodeNum], &sizeOfData, sizeof(sizeOfData));
                //next we send the actual array
                write(client_sock[nodeNum], data, sizeof(data));
                cout << "Ack sent." << endl;

                //received_message[k] = true;*/
            }
            cout << "received message" << endl;     //debugging
        }
        //m.unlock();
        //cout << "sleep" << endl;     //debugging
        //sleep(0.05);
    }
}


//=============================================================================
// stringToCharPntr()
//=============================================================================
//Takes in a string and converts it to char*
char* NetworkManager::stringToCharPntr(string str)
{
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}


//=============================================================================
// Get Methods
//=============================================================================
//This method returns the nodeID of the respective client
int NetworkManager::getNodeID(int clientID)
{
    return nodeID[clientID];
}

//This method returns the Latitude of the respective client
double NetworkManager::getGPSLat(int clientID)
{
    return gpsLat[clientID];
}

//This method returns the Longitude of the respective client
double NetworkManager::getGPSLon(int clientID)
{
    return gpsLon[clientID];
}

//This method returns the Altitude of the respective client
double NetworkManager::getGPSHt(int clientID)
{
    return gpsHt[clientID];
}

//This method returns the Stability of the respective client
double NetworkManager::getGPSStability(int clientID)
{
    return gpsStability[clientID];
}
