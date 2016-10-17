#include "Protocol.h"

const char cmdUp[] = {SCMD_UP};
const char cmdDown[] = {SCMD_DOWN};
const char cmdLeft[] = {SCMD_LEFT};
const char cmdRight[] = {SCMD_RIGHT};
const char cmdSelect[] = {SCMD_SELECT};

const char cmdHour[] = {SCMD_HOUR};
const char cmdMinute[] = {SCMD_MINUTE};
const char cmdT1MAx[] = {SCMD_T1_MAX};
const char cmdT1Min[] = {SCMD_T1_MIN};
const char cmdT2Max[] = {SCMD_T2_MAX};
const char cmdT2Min[] = {SCMD_T2_MIN};
const char cmdDay[] = {SCMD_DAY};
const char cmdMonth[] = {SCMD_MONTH};
const char cmdYear[] = {SCMD_YEAR};


const char *cmds[] = {
    "00",

    cmdUp,
    cmdDown,
    cmdLeft,
    cmdRight,
    cmdSelect,

    cmdHour,
    cmdMinute,
    cmdT1MAx,
    cmdT1Min,
    cmdT2Max,
    cmdT2Min,
    cmdDay,
    cmdMonth,
    cmdYear
};

void Protocol_Parse(ProtocolPacket *pkt, unsigned char *sentence){

    if(sentence[0] == PROTOCOL_START_BYTE && sentence[PROTOCOL_LENGTH - 1] == PROTOCOL_END_BYTE){
        ParamType pTi;

        for(pTi = 0 ; pTi < prtEND ; pTi++){
            char *cPtr = cmds[pTi];

            if(sentence[1] == cPtr[0] && sentence[2] == cPtr[1]){
                pkt->prt = pTi;
                pkt->value = (sentence[3] - '0')*100 + (sentence[4] - '0')*10 + (sentence[5] - '0');
            }
        }
    }
    else pkt->prt = prtNULL;

}
