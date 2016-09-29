#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "defs.h"

#define PROTOCOL_LENGTH 8

#define PROTOCOL_START_BYTE '$'
#define PROTOCOL_END_BYTE '\0'

/* protocol format
 *
 * $LLNNN\n\0
 *
 * $ - opening char
 * LL - two char command id
 * NNN - three number command value
 * \n\0 - closing char
 *
 */

// directional access
#define SCMD_UP      "UP"
#define SCMD_DOWN    "DW"
#define SCMD_LEFT    "LT"
#define SCMD_RIGHT   "RT"
#define SCMD_SELECT  "CR"

// direct access
#define SCMD_HOUR    "HR"
#define SCMD_MINUTE  "MN"
#define SCMD_T1_MAX  "T1"
#define SCMD_T1_MIN  "t1"
#define SCMD_T2_MAX  "T2"
#define SCMD_T2_MIN  "t2"
#define SCMD_DAY     "DY"
#define SCMD_MONTH   "MT"
#define SCMD_YEAR    "YR"

typedef enum{
     prtNULL,

     prtUP,     //UP
     prtDOWN,   //DW
     prtLEFT,   //LT
     prtRIGHT,  //RT
     prtSELECT, //CR

     prtHOUR,       //HR
     prtMIN,        //MN
     prtTEMP1MAX,   //T1
     prtTEMP1MIN,   //t1
     prtTEMP2MAX,   //t2
     prtTEMP2MIN,   //
     prtDAY,
     prtMONTH,
     prtYEAR,

     prtEND
}ParamType;

typedef struct{
    ParamType prt;
    unsigned int value;
}ProtocolPacket;

void Protocol_Parse(ProtocolPacket *pkt, unsigned char *sentence);

#endif
