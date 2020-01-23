/*
The source code is from https://www.xanthium.in/Serial-Port-Programming-using-Win32-API

*/

#include <stdio.h>
#include <stdint.h>
#include <windows.h>

int main(void)
{
    HANDLE hComm;

    hComm = CreateFile("\\\\.\\COM30",               //Portname
                       GENERIC_READ | GENERIC_WRITE, //Read and Write
                       0,                            //NO Sharing
                       NULL,                         //No security
                       OPEN_EXISTING,                // Open Existing Port Only
                       0,                            //Non Overlapped IO
                       NULL);                        //NULL for COM devices

    if (hComm == INVALID_HANDLE_VALUE)
        printf("Error in opening serial port\r\n");
    else
        printf("opening serial port successful\r\n");

    CloseHandle(hComm); //Closing the Serial Port

    return 0;
}