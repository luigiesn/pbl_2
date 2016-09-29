#include "SerialCommand.h"

#define TEMP_BUFFER PROTOCOL_LENGTH

ProcessReturn SerialCmd_Process(void);

void SerialCmd_Boot(void){

    static Process serialCmd;
    serialCmd.pR = SerialCmd_Process;
    ProcMan_AddProcess(&serialCmd);

}

ProcessReturn SerialCmd_Process(void){
    unsigned char tempChar;
    static unsigned char workBuffer[TEMP_BUFFER];
    static unsigned int iWorkBuffer;

    static ProtocolPacket pp;

    if (!Uart_DataAvailable())
        return prcREPEAT;

    if(workBuffer[0] != PROTOCOL_START_BYTE){
        workBuffer[0] = Uart_ReadByte();
    }else{
        iWorkBuffer++;
        workBuffer[iWorkBuffer] = Uart_ReadByte();

        if(iWorkBuffer == TEMP_BUFFER - 1){
            iWorkBuffer = 0;

            if(workBuffer[TEMP_BUFFER-1] == PROTOCOL_END_BYTE){
                Protocol_Parse(&pp, workBuffer);
                Uart_Write(workBuffer, TEMP_BUFFER);

                if(&pp != NULL){

                    switch(pp.prt){
                        case prtMIN:
                        {
                            mdlTime *time = (mdlTime*)(Model_GetVar(mddTime));
                            time->min = pp.value;
                            break;
                        }
                        case prtHOUR:
                        {
                            mdlTime *time = (mdlTime*)(Model_GetVar(mddTime));
                            time->hour = pp.value;
                            break;
                        }
                        case prtDAY:
                        {
                            mdlDate *date = (mdlDate*)(Model_GetVar(mddDate));
                            date->day = pp.value;
                            break;
                        }
                        case prtMONTH:
                        {
                            mdlDate *date = (mdlDate*)(Model_GetVar(mddDate));
                            date->month = pp.value;
                            break;
                        }
                        case prtTEMP1MAX:
                        {
                            mdlTempLimits *temp = (mdlTempLimits*)(Model_GetVar(mddTempLimits1));
                            temp->tempMax = pp.value;
                            break;
                        }
                        case prtTEMP1MIN:
                        {
                            mdlTempLimits *temp = (mdlTempLimits*)(Model_GetVar(mddTempLimits1));
                            temp->tempMin = pp.value;
                            break;
                        }
                        case prtTEMP2MAX:
                        {
                            mdlTempLimits *temp = (mdlTempLimits*)(Model_GetVar(mddTempLimits2));
                            temp->tempMax = pp.value;
                            break;
                        }
                        case prtTEMP2MIN:
                        {
                            mdlTempLimits *temp = (mdlTempLimits*)(Model_GetVar(mddTempLimits2));
                            temp->tempMin = pp.value;
                            break;
                        }
                        case prtYEAR:
                        {
                            mdlDate *date = (mdlDate*)(Model_GetVar(mddDate));
                            date->year = pp.value;
                            break;
                        }

                    }
                }
            }
            workBuffer[0] = 0;
        }

    }

    return prcREPEAT;
}
