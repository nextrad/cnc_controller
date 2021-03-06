//Author:       Darryn Jordan
//Edited By:    David Bissett
//File:         parameters.h
//For:          University of Cape Town, Dept. Elec. Eng., RRSG NeXtRAD
//Created:      November 2015
//Version       1.0 (June 2016)
//Edited by:    Shirley Coetzee and Darryn Jordan
//Revision      2.0 (December 2017)



#ifndef PARAMETERS_H
#define PARAMETERS_H

enum WritePrivacy {PUBLIC, PRIVATE};

#define SOCKET_BUFFER_SIZE          300
#define CNC_ADDRESS                 "192.168.1.100"
#define SSH_PORT                    22
#define TELNET_HOST                 "127.0.0.1"
#define TELNET_PORT                 4212
#define AUDIO_TELNET_PORT           5038
#define TELNET_PASSWORD             "vlc"

#define RTSP_HOST                   "192.168.1.14"
#define RTSP_PORT                   "88"

#define CAMERA_RESOLUTION           480

#define IS_MOSAIC_MODE              true
#define H_FILE_LENGTH               112

#define TCU_INIT_SCRIPT             "python3 /home/nextrad/Documents/tcu_software/controller_v2.py "

#define TCU0                        "192.168.1.16"
#define TCU1                        "192.168.1.26"
#define TCU2                        "192.168.1.36"

#define TCU_BOF_ACTIVE              "tcu_v2-1-3_active.bof"
#define TCU_BOF_PASSIVE             "tcu_v2-1-3_passive.bof"

#define HEADER_FILE                 "NeXtRAD.ini"
#define HEADER_PATH                 "/home/nextrad/Documents/nextrad_header/" HEADER_FILE

#define PULSE_PARAMS_FILE           "PulseParameters.ini"
#define PULSE_PARAMS_PATH           "/home/nextrad/Documents/tcu_software/" PULSE_PARAMS_FILE

#define GPS_INFO_FILE               "gps_info.ini"
#define CNC_NODE0_GPS_INFO_PATH     "/home/nextrad/Documents/cnc_controller/node0/home/nextrad/Desktop/NextGPSDO/gps_info.ini"
#define CNC_NODE1_GPS_INFO_PATH     "/home/nextrad/Documents/cnc_controller/node1/home/nextrad/Desktop/NextGPSDO/gps_info.ini"
#define CNC_NODE2_GPS_INFO_PATH     "/home/nextrad/Documents/cnc_controller/node2/home/nextrad/Desktop/NextGPSDO/gps_info.ini"
#define NODE_GPS_INFO_PATH          "/home/nextrad/Desktop/NextGPSDO/gps_info.ini"

#define BEARINGS_FILE               "tardat2cc.rtf"
#define CNC_NODE0_BEARINGS_PATH     "/home/nextrad/Documents/cnc_controller/node0/home/nextrad/Desktop/NextGPSDO/tardat2cc.rtf"
#define CNC_NODE1_BEARINGS_PATH     "/home/nextrad/Documents/cnc_controller/node1/home/nextrad/Desktop/NextGPSDO/tardat2cc.rtf"
#define CNC_NODE2_BEARINGS_PATH     "/home/nextrad/Documents/cnc_controller/node2/home/nextrad/Desktop/NextGPSDO/tardat2cc.rtf"
#define NODE_BEARINGS_PATH          "/home/nextrad/tardat2cc.rtf"

#define GOOGLE_EARTH_PATH           "/usr/bin"
#define GOOGLE_EARTH_FILE           "/home/nextrad/Documents/cnc_controller/src/My Places.kml"
#define GOOGLE_EARTH_FULLFILE       "/home/nextrad/Documents/cnc_controller/src/\"My Places.kml\""

#define ICON_PATH                   "../media/icons/favicon2.ico"
#define TONES_PATH                  "/var/lib/asterisk/sounds/custom/tone"
#define GOOGLE_EARTH_PATH           "/usr/bin"


#endif // PARAMETERS_H
