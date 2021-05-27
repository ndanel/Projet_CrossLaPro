#pragma hdrstop
#include "Unit2.h"
#include <string>
#pragma hdrstop
#pragma package(smart_init)
#include <iostream>
#include <stdio.h>
#include <sstream>




liaison::liaison(){
	this->buffer = new char[500];
}

bool liaison::ouvrirport(int portCOM){

	this->hcom = CreateFileA("COM"+portCOM,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING,NULL);

	if(hcom == INVALID_HANDLE_VALUE){
		return false;
	}

	GetCommState(this->hcom,&this->dcb);   //On configure les param�tres du port s�rie

	this->dcb.BaudRate = CBR_115200;    //9600 de baud rate
	this->dcb.ByteSize = 8;            //8 de Data size
	this->dcb.Parity = NOPARITY;
	this->dcb.StopBits = ONESTOPBIT;

	SetCommState(this->hcom,&this->dcb);


	COMMTIMEOUTS comm;
	comm.ReadIntervalTimeout = MAXDWORD;
	comm.ReadTotalTimeoutMultiplier=0;
	comm.ReadTotalTimeoutConstant=0;
	comm.WriteTotalTimeoutMultiplier=0;
	comm.WriteTotalTimeoutConstant=0;

	SetCommTimeouts(this->hcom,&comm);

	return true;
}

void liaison::ecrireport(char * buffer){
	char * buff[50];
	buff[0] = "0x02";
	buff[1] = "0";
	buff[2] = "1";
	buff[3] = "0x0D";
	unsigned long sendLenght;
	WriteFile(this->hcom,buff[0], 1,&sendLenght,NULL);
	WriteFile(this->hcom,buff[1], 1,&sendLenght,NULL);
	WriteFile(this->hcom,buff[2], 1,&sendLenght,NULL);
	WriteFile(this->hcom,buff[3], 1,&sendLenght,NULL);

}

void liaison::fermerport(){
	CloseHandle(this->hcom);
}

void liaison::recep(char *buffer){

	unsigned long sendLenght;
	ReadFile(this->hcom,buffer, 800,&sendLenght,NULL);
}







//---------------------------------------------------------------------------

