//Author:       Darryn Jordan
//Edited By:    David Bissett
//File:         parameters.h
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      November 2015
//Last Edited:  June 2016

#ifndef PARAMETERS_H
#define PARAMETERS_H

enum WritePrivacy {PUBLIC, PRIVATE};

#define SOCKET_BUFFER_SIZE 	300
#define CNC_ADDRESS          "192.168.1.100"
#define SSH_PORT            22
#define TELNET_HOST 		"127.0.0.1"
#define TELNET_PORT 		4212
#define AUDIO_TELNET_PORT   5038
#define TELNET_PASSWORD		"vlc"

#define RTSP_HOST			"192.168.1.14"
#define RTSP_PORT			"88"

#define CAMERA_RESOLUTION 	480

#define IS_MOSAIC_MODE		true
#define H_FILE_LENGTH       112

#define HEADER_FILE         "NeXtRAD.ini"
#define CNC_HEADER_PATH     "/home/nextrad/Documents/cnc_controller/NeXtRAD.ini"
#define NODE_HEADER_PATH    "/home/nextrad/Documents/node_controller/NeXtRAD.ini"

#define ARMTIMECFG_FILE     "armtime.cfg"
#define ARMTIMECFG_PATH     "/home/nextrad/Documents/NextGPSDO/armtime.cfg"

#define STARTTIMESECS       20
#define ENDTIMESECS         30


#endif // PARAMETERS_H
