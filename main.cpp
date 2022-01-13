/*
	Name: Tetris Console Beta1.0
	Copyright: Ricci rassau
	Author: Ricci Rassau
	Date: 20.04.19 19:58
	Description: Ein Simples Consolen Tetris
*/
#include <iostream>
#include <stdlib.h>

//Dateien
#include "Spiel.hpp"

using namespace std;

//Globale Variablen
unsigned int Highscore = 0;
unsigned short Level = 1;

//Prototypen
void Menue();


int main()
{
	Menue();
	
	return 0;
}

void Menue()
{
	//Variablen
	char Auswahl;
	
	//Schleife bis Benutzerbeenden ausführen
	do
	{
		system("cls");		//Bildschirm löschen
		
		//Menü ausgeben
		cout << "Tetris Console Beta1.0" << endl;
		cout << "--------------------------------------" << endl;
		cout << "(S)piel Starten" << endl;
		cout << "(L)evel weahlen" << endl;
		cout << "(H)ighscore ausgeben" << endl;
		cout << "(B)eenden" << endl << endl;
		
		
		//Eingabe abfragen
		cin >> Auswahl;
		
		//Eingabe testen
		if(Auswahl == 'S' || Auswahl == 's')
		{
			Spiel(Level, Highscore);
		}
		else if(Auswahl == 'L' || Auswahl == 'l')
		{
			//Temporäre Variabele
			unsigned short lvl_temp;
			
			
			//Wiederholen bis zur gültigen eingabe
			do
			{
				//Level auswahl anzeigen
				cout << endl << "Aktuelles Level: " << Level << endl;
				cout << "Welches Level willst Du spielen? (1 - 10)" << endl;
				cout << "Level: ";
				
				//Level abfragen
				cin >> lvl_temp;
				
				//Levelbereich checken
				if(lvl_temp < 1 || lvl_temp > 10)
				{
					cout << "Ungueltiges Level!" << endl;
				}
				
			} while (lvl_temp < 1 || lvl_temp > 10);
			
			//Level Speichern
			Level = lvl_temp;
		}
		else if(Auswahl == 'H' || Auswahl == 'h')
		{
			//Highscore ausgeben
			cout << endl << endl << "Der Highscore ist: " << Highscore << endl;
			
			//Warten auf Benutzer-weiter
			system("pause");
		}
		else if(Auswahl == 'B' || Auswahl == 'b')
		{
			//Bildschirm löschen
			system("cls");
			
			//kleine Beendigungs ausgabe
			cout << "Danke fuers Spielen!" << endl;
			
			//Auf Benutzer warten
			system("pause");
		}
		else
		{
			//Fehlertext ausgeben
			cout << "Ungueltige Eingabe!" << endl;
			
			//Auf Benuter warten
			system("pause");
		}
		
	} while(Auswahl != 'B' && Auswahl != 'b');
}
