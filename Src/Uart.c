#include "Uart.h"

#define TX_BUFFER_SZ 128
#define RX_BUFFER_SZ 128

unsigned char txBuffer[TX_BUFFER_SZ];
unsigned char txHeadPtr;
unsigned char txTailPtr;

unsigned char rxBuffer[RX_BUFFER_SZ];
unsigned char rxHeadPtr;
unsigned char rxTailPtr;

ProcessReturn Uart_Process(void);

void Uart_Boot(void){
    txTailPtr = 0;
    txHeadPtr = 0;
    rxTailPtr = 0;
    rxHeadPtr = 0;

    LPC_IOCON->PIO1_7 = 1;
    LPC_IOCON->PIO1_6 = 1;

    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 12;

    LPC_SYSCON->UARTCLKDIV    |= 0x01;
	LPC_UART->LCR             |= (1<<7);
	LPC_UART->DLM              = 0x0;
	LPC_UART->DLL              = 0x1A;
	LPC_UART->FDR              = 0x00;
	LPC_UART->FCR             |= 0x01;
	LPC_UART->LCR             =  0x03;
	LPC_UART->TER             |= 0x80;

	static Process uart;
	uart.pR = Uart_Process;
	ProcMan_AddProcess(&uart);
}

ProcessReturn Uart_Process(void){

    if(LPC_UART->LSR & 0x40){
        if(txHeadPtr != txTailPtr){
            LPC_UART->THR = txBuffer[txTailPtr++];
            if(txTailPtr == TX_BUFFER_SZ)
                txTailPtr = 0;
        }
    }

    while (LPC_UART->LSR & 0x01){ // if has data
        rxBuffer[rxHeadPtr++] = LPC_UART->RBR;
        if(rxHeadPtr == RX_BUFFER_SZ)
            rxHeadPtr = 0;
    }

    return prcREPEAT;
}

bool Uart_DataAvailable(void){
    return rxHeadPtr != rxTailPtr;
}

unsigned int Uart_Read(unsigned char* data, unsigned int size){
    unsigned int i;

    for(i = 0 ; i < size && (rxHeadPtr != rxTailPtr) ; i++){ // copy data
        data[i] = rxBuffer[rxTailPtr++];
        if(rxTailPtr == RX_BUFFER_SZ){
            rxTailPtr = 0;
        }
    }

    return size < i ? size : i; // return the number of copied bytes
}

unsigned char Uart_ReadByte(void){
    unsigned char temp;

    Uart_Read(&temp, 1);

    return temp;
}


void Uart_Write(unsigned char* data, unsigned int size){
    unsigned int i;

    // copy to a internal buffer
    for(i = 0 ; i < size ; i++, txHeadPtr++){
        if(txHeadPtr == TX_BUFFER_SZ)
            txHeadPtr = 0;

        txBuffer[txHeadPtr] = data[i];
    }
}
