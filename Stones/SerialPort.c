/*
The source code is from https://www.xanthium.in/Serial-Port-Programming-using-Win32-API

*/

#include <stdio.h>
#include <stdint.h>
#include <windows.h>

/* This function convert interger to string using recursive
   using recursive is not necessary for this kind of operation but i found it interesting to do so
   To do - return string head address upon exit; ie finished converting.
         - Support negative value.   
   Note. Make sure the array got enough space to hold the converted string and initilize with NULL value.
      
*/
char *numToStr(int num, char *str)
{

    int rem = num % 10;
    int i = num / 10;
    if (i > 10)
    {
        str = numToStr(i, str);
        str++;
        *str = rem + '0';
        return str;
    }
    else
    {
        *str = i + '0';
        str++;
        *str = rem + '0';
        return str;
    }
}

int main(void)
{
    HANDLE hComm;
    int portNum = 123;
    char portName[10] = {"\\\\.\\COM"};
    char str[10] = {0};
    char *ptr;
    int i = 7;

    while (portNum != 0)
    {
        int rem = portNum % 10;
        portName[i++] = rem + '0';
        portNum = portNum / 10;
    }
    ptr = numToStr(123456789, str);
    hComm = CreateFile(portName,                     //Portname
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