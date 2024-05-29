#ifndef UART_H_
#define UART_H_

#define SUPPORT_NON_BLOCKING_UART

int UART_Open(char *pDeviceName);
void UART_Close(int UartHandle);
//bool UART_IsOpened(void);
bool UART_Write(int UartHandle, char *pData, int nDataSize);
bool UART_WriteString(int UartHandle, char *pString);
bool UART_Read(int UartHandle, char *pBuffer, int nBufferSize, int *prx_len);
bool UART_ReadWithTimeout(int UartHandle, alt_u8 *pBuffer, alt_u16 nBufferSize, alt_u16 *prx_len, alt_u32 timeout);
bool UART_NoneBlockingRead(int UartHandle, alt_u8 *pBuffer, int nBufferSize, int *prx_len);
//alt_u8 UART_ReceivedDataSize(int UartHandle);

//
bool UART_TestLoopback(void);

#endif /*UART_H_*/
