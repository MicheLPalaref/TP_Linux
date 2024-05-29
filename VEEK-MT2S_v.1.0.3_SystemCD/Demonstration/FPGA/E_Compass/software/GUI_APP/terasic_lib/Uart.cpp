#include "terasic_includes.h"
#include "Uart.h"
#include "sys/alt_dev.h"

#ifdef SUPPORT_NON_BLOCKING_UART

//static int pUart=0;


int UART_Open(char *pDeviceName){
    int UartHandle;
   // bool bNoneBlocking = FALSE;
//    UART_Close();
    
    UartHandle = open(pDeviceName, O_ACCMODE); // open file for reading and writing
//    pUart = open(UART_NAME, O_ACCMODE | ((bNoneBlocking)?O_NONBLOCK:0)); // open file for reading and writing
    if (UartHandle){
//        int i = fcntl(pJtagUart, F_SETFL, O_NONBLOCK);
//        printf("fcntl = %d\r\n", i);
  //      bSuccess = TRUE;
    }        
    return UartHandle;
}


void UART_Close(int UartHandle){
    if (UartHandle){
        close(UartHandle);
       // pUart = 0;
    }
}


bool UART_Write(int UartHandle, char *pData, int nDataSize){
    bool bSuccess = FALSE;
    if (UartHandle){
        if (write(UartHandle, pData, nDataSize) == nDataSize)
            bSuccess = TRUE;
    }            
    return bSuccess;        
        
}

bool UART_Read(int UartHandle, char *pBuffer, int nBufferSize, int *prx_len){
    int nResult;
    bool bSuccess = FALSE;
    if (UartHandle){
        nResult = read(UartHandle, pBuffer, nBufferSize);
        if (nResult >= 0){
            *prx_len = nResult;
            bSuccess = TRUE; 
            //if (*prx_len == nBufferSize)
            //    bSuccess = TRUE;
        }            
    }            
    return bSuccess;      
}

bool UART_ReadWithTimeout(int UartHandle, alt_u8 *pBuffer, alt_u16 nBufferSize, alt_u16 *prx_len, alt_u32 timeout){
    bool bSuccess = FALSE;
    if (UartHandle){
        int rx_total_cnt = 0, rx_cnt;
        alt_u32 time_start;
        bool bTimeout = FALSE;
        time_start = alt_nticks();
        while(!bSuccess && !bTimeout){
            UART_NoneBlockingRead(UartHandle, pBuffer+rx_total_cnt, nBufferSize-rx_total_cnt, &rx_cnt);
            //rx_cnt = read(pUart, pBuffer+rx_total_cnt, nBufferSize-rx_total_cnt);
            rx_total_cnt += rx_cnt;
            if (rx_total_cnt == nBufferSize)
                bSuccess = TRUE;
            else if ((alt_nticks() - time_start) > timeout)
                bTimeout = TRUE;    
            else
                usleep(1);                
        }
        *prx_len = rx_total_cnt;                
    }            
    return bSuccess;      
}

bool UART_NoneBlockingRead(int UartHandle, alt_u8 *pBuffer, int nBufferSize, int *prx_len){
    bool bSuccess;
    fcntl(UartHandle, F_SETFL, O_ACCMODE | O_NONBLOCK);
    bSuccess = UART_Read(UartHandle, (char *)pBuffer, nBufferSize, prx_len);
    fcntl(UartHandle, F_SETFL, O_ACCMODE);
    return bSuccess;
}




#else  //SUPPORT_NON_BLOCKING_UART


//static FILE *pUart=0;


int UART_Open(char *pDeviceName){
    int UartHandle;
    //bool bSuccess = FALSE;
    //UART_Close();
    UartHandle = fopen(pDeviceName, "r+"); // open file for reading and writing
    //if (UartHandle){
      //  bSuccess = TRUE;
    //}        
    return UartHandle;
}

void UART_Close(int UartHandle){
    if (UartHandle){
        fclose(UartHandle);
      //  pUart = NULL;
    }
}


bool UART_Write(int UartHandle, char *pData, int nDataSize){
    bool bSuccess = FALSE;
    if (UartHandle){
        if (fwrite(UartHandle, 1, nDataSize, pUart) == nDataSize)
            bSuccess = TRUE;
    }            
    return bSuccess;        
        
}

bool UART_Read(int UartHandle, char *pBuffer, int nBufferSize, int *prx_len){
    bool bSuccess = FALSE;
    int nReadSize = 0;
    if (UartHandle){
        *prx_len = fread(pBuffer, 1, nBufferSize, UartHandle);
        if (*prx_len == nBufferSize)
            bSuccess = TRUE;
    }            
    return nReadSize;      
}

/*
alt_u8 UART_ReceivedDataSize(void){
    alt_u16 size = 0;
    alt_u16 status;
    status = IORD(UART_BASE, 4);
    if ((status & 0x80) == 0x80){
        size = IORD(UART_BASE, 0);
        size &= 0x7F;
    }        
    return size;
}*/

#endif //#ifdef SUPPORT_NON_BLOCKING_UART

bool UART_WriteString(int UartHandle, char *pString){
    return UART_Write(UartHandle, pString, strlen(pString));
}

//bool UART_IsOpened(void){
    //if (pUart)
      //  return TRUE;
    //return FALSE;        
//}

#if 0

bool UART_TestLoopback(void){
    bool bSuccess = FALSE;
    alt_u32 time_start;
 //   bool bOpened = FALSE;
    int UartHandle;
    
    time_start = alt_nticks();
 //   bOpened = UART_IsOpened();
        
    UartHandle = UART_Open(UART_NAME);
    if (UartHandle){
        alt_u8 szText[] = "UART Loopback\r\n";
#if 1
        alt_u8 szRead[32];
        int i;
        alt_u16 nReadSize;
        alt_u32 clean_time_start;
        
        // clear input buffer
        clean_time_start = alt_nticks();
        bool bCleanDone = FALSE;
        while(!bCleanDone){
            nReadSize = sizeof(szRead);
            bSuccess = UART_ReadWithTimeout(UartHandle, szRead, nReadSize, &nReadSize,alt_ticks_per_second()/10);
            if (nReadSize == 0)
                bCleanDone = TRUE;
            else if ((alt_nticks() - clean_time_start) > alt_ticks_per_second())  // timeout 1 second
                bCleanDone = TRUE;  // timeout                
        }            
        
        // loop backtest
        UART_WriteString(UartHandle, szText);
        usleep(50*1000);    // release CPU for UART process
        nReadSize = strlen(szText);
        //printf("[APP]UART try to read %d byte\r\n", nReadSize);
        bSuccess = UART_ReadWithTimeout(UartHandle, szRead, nReadSize, &nReadSize, alt_ticks_per_second()/10);
      //  APP_DEBUG(("[APP]UART_NoneBlockingRead %s (nReadSize=%d)\r\n", bSuccess?"success":"fail", nReadSize));
        //printf("[APP]UART_NoneBlockingRead %s (nReadSize=%d)\r\n", bSuccess?"success":"fail", nReadSize);
        szRead[nReadSize] = 0;
        //printf("read [%s]\r\n", szRead);
        for(i=0;bSuccess && i<nReadSize;i++){
            if (szRead[i] != szText[i]){
              //  APP_DEBUG(("[APP] UART Loopback compare fail at index %d\r\n", i));
                bSuccess = FALSE;
            }                
        }         
        //printf("uart test %s\r\n", bSuccess?"success":"ng");       
#else    
        // test non-block read
        UART_WriteString("Hello from UART\r\n");
        int nReadSize;
        printf("none blocking read...\r\n");
        if (UART_NoneBlockingRead(szText, sizeof(szText), &nReadSize)){
            printf("read ok\r\n");
            UART_Write(szText, sizeof(szText));
        }
        printf("none blocking read end, nReadSize=%d\r\n",nReadSize);
        
        //
        printf("blocking read...\r\n");
        if (UART_Read(szText, sizeof(szText), &nReadSize)){
            printf("read ok\r\n");
            UART_Write(szText, sizeof(szText));
        }
        printf("blocking read end, nReadSize=%d\r\n", nReadSize);
        bSuccess = TRUE;
#endif        
        
        UART_Close(UartHandle);
        //printf("[UART]test success\r\n");
    }else{
        //printf("[UART]test fail\r\n");
    }
    
  //  if (bOpened)  // restore status
    //    UART_Open(); 
    //APP_REPORT("[UART] %s (%ld second)\r\n", bSuccess?"success":"fail", (alt_nticks()-time_start)/alt_ticks_per_second());
   // report_result("UART", bSuccess, time_start);
    return bSuccess;
}


#endif
