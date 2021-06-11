//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <stdio.h>
#include <string>
#include <iostream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	RS232 = new liaison();
	int portCOM;
	char * temp[50];
	if(Edit1->Text == "1"){
		portCOM = 1;
	} else if(Edit1->Text == "2"){
		portCOM = 2;
	} else if(Edit1->Text == "3"){
		portCOM = 3;
	} else if(Edit1->Text == "4"){
		portCOM = 4;
	} else if(Edit1->Text == "5"){
		portCOM = 5;
	} else if(Edit1->Text == "6"){
		portCOM = 6;
	} else if(Edit1->Text == "7"){
		portCOM = 7;
	} else if(Edit1->Text == "8"){
		portCOM = 8;
	} else if(Edit1->Text == "9"){
		portCOM = 9;
	} else if(Edit1->Text == "10"){
		portCOM = 10;
	} else if(Edit1->Text == "11"){
		portCOM = 11;
	} else if(Edit1->Text == "12"){
		portCOM = 12;
	} else if(Edit1->Text == "13"){
		portCOM = 13;
	} else if(Edit1->Text == "14"){
		portCOM = 14;
	} else if(Edit1->Text == "15"){
		portCOM = 15;
	} else{
		portCOM = 999;
	}
	if(portCOM >= 1 && portCOM <= 15){
		bool reussiteOuvrirPort = RS232->ouvrirport(portCOM);
		if(reussiteOuvrirPort == false){
			Label2->Caption = "Ouverture �chou�e";
		}else{
			Label2->Caption = "Ouverture r�ussie";
			Label1->Visible = false;
			Edit1->Visible = false;
			Button1->Visible = false;
			Button2->Visible = true;
		}
	} else{
		Label2->Caption = "Num�ro de port incorrect";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int longueurBuffer = 4, longueurBufferRecep = 10;
	char buffer[4], bufferRecep[10], bufferRecepFinal[30];
	char heure[9] = "lol", date[10];
	bool debutTrame = false, finTrame = false;

	buffer[0] = 0x02;
	buffer[1] = 0x33;
	buffer[2] = 0x39;
	buffer[3] = 0x0D;

	RS232->ecrireport(buffer,longueurBuffer);

	Sleep(1000);

	int nb = 0, timeout = 0;
	do{
		RS232->recep(bufferRecep,longueurBufferRecep);
		for(int i = 0; i < longueurBufferRecep; i++){
			if(bufferRecep[i] == 0x02 && finTrame == false && debutTrame == false){
				debutTrame = true;
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-1] == 0x02 && bufferRecep[i] != 0x30){
				debutTrame = false;
				nb -= 1;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-1] == 0x02 && bufferRecep[i] == 0x30){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] == 0x02 && bufferRecepFinal[nb-1] == 0x30 && bufferRecep[i] != 0x31){
				debutTrame = false;
				nb -= 2;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] == 0x02 && bufferRecepFinal[nb-1] == 0x30 && bufferRecep[i] == 0x31){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] != 0x02 && bufferRecepFinal[nb-1] != 0x30 && bufferRecepFinal[nb-1] != 0x02 && bufferRecep[i] != 0x0D){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && bufferRecep[i] == 0x0D){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
				finTrame = true;
			}else if(debutTrame == true && finTrame == false){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}
		}
		timeout++;
	}while(finTrame == false && timeout < 20);
	if(timeout >= 20){
		Label2->Caption = "Erreur de connexion";
	} else {
		Button2->Visible = false;
		Button3->Visible = true;
		if(this->acquisitionStarted == false){
			Button4->Visible = true;
		} else if(this->acquisitionStarted == true){
			Label7->Visible = true;
			Label8->Visible = true;
			Label9->Visible = true;
			Label10->Visible = true;
			Label11->Visible = true;
			Label12->Visible = true;
			Label13->Visible = true;
			Label14->Visible = true;
			Label15->Visible = true;
			Label16->Visible = true;
			Button5->Visible = true;
		}
		Label2->Visible = false;
		Label3->Visible = true;
		Label4->Visible = true;
		Label5->Visible = true;
		Label6->Visible = true;
		snprintf(date,10,"%c%c%c%c%c%c%c%c%c%c",bufferRecepFinal[22],bufferRecepFinal[23],bufferRecepFinal[21],bufferRecepFinal[19],bufferRecepFinal[20],bufferRecepFinal[24],bufferRecepFinal[25],bufferRecepFinal[26],bufferRecepFinal[27],bufferRecepFinal[28]);
		snprintf(heure,8,"%c%c%c%c%c%c%c%c",bufferRecepFinal[10],bufferRecepFinal[11],bufferRecepFinal[12],bufferRecepFinal[13],bufferRecepFinal[14],bufferRecepFinal[15],bufferRecepFinal[16],bufferRecepFinal[17]);

		std::string dateS = date;
		Label6->Caption = dateS.c_str();
		std::string heureS = heure;
		Label4->Caption = heureS.c_str();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	int longueurBuffer = 4, longueurBufferRecep = 10;
	char buffer[4], bufferRecep[10], bufferRecepFinal[30];
	char heure[9] = "lol", date[10];
	bool debutTrame = false, finTrame = false;

	buffer[0] = 0x02;
	buffer[1] = 0x33;
	buffer[2] = 0x39;
	buffer[3] = 0x0D;

	RS232->ecrireport(buffer,longueurBuffer);

	Sleep(1000);

	int nb = 0, timeout = 0;
	do{
		RS232->recep(bufferRecep,longueurBufferRecep);
		for(int i = 0; i < longueurBufferRecep; i++){
			if(bufferRecep[i] == 0x02 && finTrame == false && debutTrame == false){
				debutTrame = true;
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-1] == 0x02 && bufferRecep[i] != 0x30){
				debutTrame = false;
				nb -= 1;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-1] == 0x02 && bufferRecep[i] == 0x30){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] == 0x02 && bufferRecepFinal[nb-1] == 0x30 && bufferRecep[i] != 0x31){
				debutTrame = false;
				nb -= 2;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] == 0x02 && bufferRecepFinal[nb-1] == 0x30 && bufferRecep[i] == 0x31){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] != 0x02 && bufferRecepFinal[nb-1] != 0x30 && bufferRecepFinal[nb-1] != 0x02 && bufferRecep[i] != 0x0D){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && bufferRecep[i] == 0x0D){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
				finTrame = true;
			}else if(debutTrame == true && finTrame == false){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}
		}
		timeout++;
	}while(finTrame == false && timeout < 20);
	if(timeout >= 20){
		Button3->Visible = false;
		Button2->Visible = true;
		Button4->Visible = false;
		Button5->Visible = false;
		Label2->Visible = true;
		Label3->Visible = false;
		Label4->Visible = false;
		Label5->Visible = false;
		Label6->Visible = false;
		Label7->Visible = false;
		Label8->Visible = false;
		Label9->Visible = false;
		Label10->Visible = false;
		Label11->Visible = false;
		Label12->Visible = false;
		Label13->Visible = false;
		Label14->Visible = false;
		Label15->Visible = false;
		Label16->Visible = false;
		Label2->Caption = "Erreur de connexion";
	} else {
		snprintf(date,10,"%c%c%c%c%c%c%c%c%c%c",bufferRecepFinal[22],bufferRecepFinal[23],bufferRecepFinal[21],bufferRecepFinal[19],bufferRecepFinal[20],bufferRecepFinal[24],bufferRecepFinal[25],bufferRecepFinal[26],bufferRecepFinal[27],bufferRecepFinal[28]);
		snprintf(heure,8,"%c%c%c%c%c%c%c%c",bufferRecepFinal[10],bufferRecepFinal[11],bufferRecepFinal[12],bufferRecepFinal[13],bufferRecepFinal[14],bufferRecepFinal[15],bufferRecepFinal[16],bufferRecepFinal[17]);

		std::string dateS = date;
		Label6->Caption = dateS.c_str();
		std::string heureS = heure;
		Label4->Caption = heureS.c_str();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int longueurBuffer = 4;
	char buffer[4];

	//Definition de la trame � envoyer
	buffer[0] = 0x02;
	buffer[1] = 0x30;
	buffer[2] = 0x30;
	buffer[3] = 0x0D;

	//Envoi de la trame
	RS232->ecrireport(buffer,longueurBuffer);

	this->acquisitionStarted = true;
	Button4->Visible = false;
	Button5->Visible = true;
	Label7->Visible = true;
	Label8->Visible = true;
	Label9->Visible = true;
	Label10->Visible = true;
	Label11->Visible = true;
	Label12->Visible = true;
	Label13->Visible = true;
	Label14->Visible = true;
	Label15->Visible = true;
	Label16->Visible = true;

	th = new ThreadDetectionDossard(true);
	th->Priority = tpNormal;
	th->Resume();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	th->Terminate();
	delete th; // lib�ration m�moire

	int longueurBuffer = 4;
	char buffer[4];

	//Definition de la trame � envoyer
	buffer[0] = 0x02;
	buffer[1] = 0x30;
	buffer[2] = 0x31;
	buffer[3] = 0x0D;

	//Envoi de la trame
	RS232->ecrireport(buffer,longueurBuffer);

	this->acquisitionStarted = false;
	Button4->Visible = true;
	Button5->Visible = false;
	Label7->Visible = false;
	Label8->Visible = false;
	Label9->Visible = false;
	Label10->Visible = false;
	Label11->Visible = false;
	Label12->Visible = false;
	Label13->Visible = false;
	Label14->Visible = false;
	Label15->Visible = false;
	Label16->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Label13Click(TObject *Sender)
{
	/*int nb = 0, longueurBufferRecep = 23, n = 0, timeout = 0;
	char bufferRecep[23], bufferRecepFinal[46], nombreDetection[2], idDossard[7], heureDetection[12];
	bool debutTrame, finTrame;
	debutTrame = false;
	finTrame = false;
	while(finTrame == false && timeout < 3){
		Sleep(1000);
		RS232->recep(bufferRecep,longueurBufferRecep);
		for(int i = 0; i < longueurBufferRecep; i++){
			if(bufferRecep[i] == 0x02 && finTrame == false && debutTrame == false){
				debutTrame = true;
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-1] == 0x02 && bufferRecep[i] != 0x30){
				debutTrame = false;
				nb -= 1;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-1] == 0x02 && bufferRecep[i] == 0x30){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] == 0x02 && bufferRecepFinal[nb-1] == 0x30 && bufferRecep[i] != 0x30){
				debutTrame = false;
				nb -= 2;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] == 0x02 && bufferRecepFinal[nb-1] == 0x30 && bufferRecep[i] == 0x30){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && finTrame == false && bufferRecepFinal[nb-2] != 0x02 && bufferRecepFinal[nb-1] != 0x30 && bufferRecepFinal[nb-1] != 0x02 && bufferRecep[i] != 0x0D){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
			}else if(debutTrame == true && bufferRecep[i] == 0x0D){
				bufferRecepFinal[nb] = bufferRecep[i];
				nb++;
				finTrame = true;
			}else if(debutTrame == true && finTrame == false){
				if(bufferRecep[i] == 0x31 && bufferRecep[i-1] == 0x32 && nb == 13){
					bufferRecepFinal[nb] = bufferRecep[i];
					nb++;
				} else if(nb == 13 && bufferRecep[i] != 0x31 && bufferRecep[i-1] != 0x32){
					nb -= 13;
				} else {
					bufferRecepFinal[nb] = bufferRecep[i];
					nb++;
				}
			}
		}
		timeout++;
	}
	if(finTrame == true){
		snprintf(nombreDetection,2,"%c%c",bufferRecepFinal[8],bufferRecepFinal[9]);
		snprintf(idDossard,6,"%c%c%c%c%c%c",bufferRecepFinal[27],bufferRecepFinal[28],bufferRecepFinal[29],bufferRecepFinal[30],bufferRecepFinal[31],bufferRecepFinal[32]);
		snprintf(heureDetection,11,"%c%c%c%c%c%c%c%c%c%c%c",bufferRecepFinal[34],bufferRecepFinal[35],bufferRecepFinal[36],bufferRecepFinal[37],bufferRecepFinal[38],bufferRecepFinal[39],bufferRecepFinal[40],bufferRecepFinal[41],bufferRecepFinal[42],bufferRecepFinal[43],bufferRecepFinal[44]);

		std::string nbDetectionS(nombreDetection);
		Label12->Caption = nbDetectionS.c_str();
		std::string idDossardS(idDossard);
		Label8->Caption = idDossardS.c_str();
		std::string heureDetectionS(heureDetection);
		Label10->Caption = heureDetectionS.c_str();
	}      */

}
//---------------------------------------------------------------------------

