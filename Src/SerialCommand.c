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
                            mdlTime time;

                            Model_GetValue(mddTime, (void*)&time );
                            time.min = pp.value;
                            Model_SetValue(mddTime, (void*)&time );
                            break;
                        }
                        case prtHOUR:
                        {
                            mdlTime time;

                            Model_GetValue(mddTime, (void*)&time );
                            time.hour = pp.value;
                            Model_SetValue(mddTime, (void*)&time );
                            break;
                        }
                        case prtDAY:
                        {
                            mdlDate date;

                            Model_GetValue(mddDate, (void*)&date );
                            date.day = pp.value;
                            Model_SetValue(mddDate, (void*)&date );
                        }
                        case prtMONTH:
                        {
                            mdlDate date;

                            Model_GetValue(mddDate, (void*)&date );
                            date.month = pp.value;
                            Model_SetValue(mddDate, (void*)&date );
                        }
                        case prtTEMP1MAX:
                        {
                            mdlTempLimits temp;

                            Model_GetValue(mddTempLimits1, (void*)&temp );
                            temp.tempMax = pp.value;
                            Model_SetValue(mddTempLimits1, (void*)&temp );
                            break;
                        }
                        case prtTEMP1MIN:
                        {
                            mdlTempLimits temp;

                            Model_GetValue(mddTempLimits1, (void*)&temp );
                            temp.tempMin = pp.value;
                            Model_SetValue(mddTempLimits1, (void*)&temp );
                            break;
                        }
                        case prtTEMP2MAX:
                        {
                            mdlTempLimits temp;

                            Model_GetValue(mddTempLimits2, (void*)&temp );
                            temp.tempMax = pp.value;
                            Model_SetValue(mddTempLimits2, (void*)&temp );
                            break;
                        }
                        case prtTEMP2MIN:
                        {
                            mdlTempLimits temp;

                            Model_GetValue(mddTempLimits2, (void*)&temp );
                            temp.tempMin = pp.value;
                            Model_SetValue(mddTempLimits2, (void*)&temp );
                            break;
                        }
                        case prtYEAR:
                        {
                            mdlDate date;

                            Model_GetValue(mddDate, (void*)&date );
                            date.year = pp.value;
                            Model_SetValue(mddDate, (void*)&date );
                        }

                    }
                }
            }
            workBuffer[0] = 0;
        }

    }

    return prcREPEAT;
}
