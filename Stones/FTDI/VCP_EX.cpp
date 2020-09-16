/*
 * This software is supplied on an as-is basis and no warranty as to their suitability for any particular purpose is either 
 * made or implied. Future Technology Devices International Ltd. will not accept any claim for damages howsoever arising as 
 * a result of use or failure of this software. Your statutory rights are not affected. This software or any variant of it 
 * is not intended for use in any medical appliance, device or system in which the failure of the product might reasonably be 
 * expected to result in personal injury. This document provides preliminary information that may be subject to change 
 * without notice.
 * 
 */

/*
 * The following code assumes a FT232R chip is connected to a PC with the RXD pin and the TXD pin shorted together.
 * The FTDI VCP driver must be installed on the PC.
 * The first part of the code determines the com port assigned to the device automatically, so the user does not have to
 * check in device manager.
 *
 * This com port number is then then opened with the standard W32 Serial COM API calls.
 * Data is then sent to the device which will loop back on the wire used to short RXD to TXD and the application reads the
 * data to prove it looped round.
 */


#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include "ftd2xx.h"

int main(int argc, char* argv[])
{
	FT_HANDLE fthandle;
	FT_STATUS res;
	LONG COMPORT;
	int numDevs;
	char COMx[9];
	char TxBuffer[6] = "#TST$";
	DWORD BytesWritten;
	int n;

	DCB dcb;
	HANDLE hCommPort;
	BOOL fSuccess;	


/***********************************************************************
//Find the com port that has been assigned to your device.
/***********************************************************************/
	res= FT_ListDevices(&numDevs,NULL,FT_LIST_NUMBER_ONLY);
		if (res == FT_OK) {
			// FT_ListDevices OK, number of devices connected is in numDevs
			printf("Number of devices %d\n",numDevs);
			}
			else {
			// FT_ListDevices failed
			}

	res = FT_Open(0, &fthandle);

	if(res != FT_OK){
		
		printf("opening failed! with error %d\n", res);
		
		return 1;
	}

	FT_Write(fthandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);


	
	res = FT_GetComPortNumber(fthandle,&COMPORT);

	if(res != FT_OK){
		
		printf("get com port failed %d\n", res);
		
		return 1;
	}

	if (COMPORT == -1){

		printf("no com port installed \n");
	}

	else{
		printf("com port number is %d\n", COMPORT);

	}


	FT_Close(fthandle);
	

/********************************************************/
// Open the com port assigned to your device
/********************************************************/		

		n = sprintf(COMx, "\\\\.\\COM%d",COMPORT);
		printf(COMx);
			hCommPort = CreateFile(
			COMx,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
            );

		if (hCommPort == INVALID_HANDLE_VALUE) 
		{
	
			printf("Help - failed to open\n");
			return(1);

		}	
			

		printf("Hello World!\n");
		
/********************************************************/
// Configure the UART interface parameters
/********************************************************/

		fSuccess = GetCommState(hCommPort, &dcb);


		if (!fSuccess) 

		{
			printf("GetCommStateFailed \n", GetLastError());
			return (2);

		}

		//set parameters.

		dcb.BaudRate = 19200;
		dcb.ByteSize = 8;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		
		fSuccess = SetCommState(hCommPort, &dcb);


		if (!fSuccess) 

		{
			printf("SetCommStateFailed \n", GetLastError());
			return (3);

		}


			printf("Port configured \n");


/********************************************************/
// Writing data to the USB to UART converter
/********************************************************/

	DWORD dwwritten = 0, dwErr;
	char data_out[12] = "#www$";
	DWORD w_data_len = 5;
			

fSuccess = WriteFile(hCommPort, &data_out, w_data_len, &dwwritten, NULL);
	
		
		if (!fSuccess) 

		{
			dwErr = GetLastError();
			printf("Write Failed \n", GetLastError());
			return (4);

		}

		
		printf("bytes written = %d\n", dwwritten);
			
/********************************************************/
//Reading data from the USB to UART converter
/********************************************************/
		
	char buf[256];
	DWORD dwRead;


	memset(buf,0,256);


	if (ReadFile(hCommPort, buf, w_data_len, &dwRead, NULL))

			{

				printf("data read = %s\n", buf);


			}

/********************************************************/
//Closing the device at the end of the program
/********************************************************/


    CloseHandle(hCommPort);

	getchar();
	return 0;
}