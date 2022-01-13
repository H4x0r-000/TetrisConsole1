#include <iostream>
#include <stdlib.h>
#include "Grafik.hpp"

using namespace std;


void DrawGame(char Map[20][20], int Punkte, int Highscore)
{
	//Bildschirm löschen
	system("cls");
	
	cout << "Punkte: " << Punkte << endl;
	cout << "Highscore: " << Highscore << endl;
	
	//Spielfeld Darstellen
	cout << "######################" << endl;
	
	for(int y = 0; y < 20; y++)
	{
		cout << "#";
		
		for(int x = 0; x < 20; x++)
		{
			cout << Map[x][y];
		}
		cout << "#" << endl;
	}
	
	cout << "######################" << endl;
}
