//#include 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
#include "ftd2xx.h"
int main()
{
printf("Hello");
FT_HANDLE ftHandle;
FT_STATUS ftStatus;
ftStatus = FT_Open(0, &ftHandle);
ftStatus |= FT_SetUSBParameters(ftHandle, 4096, 4096); // Set USB transfer sizes
ftStatus |= FT_SetChars(ftHandle, false, 0, false, 0); // Disable event characters
ftStatus |= FT_SetTimeouts(ftHandle, 5000, 5000); // Set read/write timeouts to 5 sec
ftStatus |= FT_SetLatencyTimer(ftHandle, 16); // Latency timer at default 16ms
ftStatus |= FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x11, 0x13); // No flow control
ftStatus |= FT_SetBaudRate(ftHandle, 9600); // Baud rate = 9600
ftStatus |= FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1,
FT_PARITY_NONE);
if (ftStatus != FT_OK) printf("ftStatus not ok %d\n", ftStatus); //check for error
else
{
char data_out[12] = "Hello World";
DWORD w_data_len = 12;
DWORD data_written;
ftStatus = FT_Write(ftHandle, data_out, w_data_len, &data_written);
char data_in[12];
DWORD r_data_len = 12;
DWORD data_read;
ftStatus = FT_Read(ftHandle, data_in, r_data_len, &data_read);
if (ftStatus != FT_OK)
printf("ftStatus not ok %d\n", ftStatus);
else
printf("Data Read: %s\n", data_in);
}
ftStatus = FT_Close(ftHandle);
printf("Press Return To End Program");
getchar();
return 0;
}