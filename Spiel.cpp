#include <iostream>
#include <windows.h>
#include <time.h>
#include "Spiel.hpp"
#include "Grafik.hpp"

using namespace std;

//Windows "winmm.lib" für Zufalszahlen initialisieren
#pragma comment (lib, "winmm.lib")

//Globale Variablen
char Blocks[7][4][4];	//5 = anz. Blöcke | 4 = Blockbreite | 4 = Blockhöhe
	
//Spielfeld erstellen
char Map[20][20];
	
//Block Objekt
struct Block
{
	char Shape[4][4];		//Array für Teile
	int rotation = 0;
	int PosX;
	int PosY;
	int LastX;
	int LastY;
	int LastRotation;
};



unsigned int Spiel(unsigned short Level, int Highscore)
{
	//Punkte Variable erzeugen
	int Punkte = 0;
	
	//Blöcke Initialisieren
	initBlocks();
	
	//Spielfeld definieren
	for(int y = 0; y < 20; y++)
	{
		for(int x = 0; x < 20; x++)
		{
			Map[x][y] = ' ';	//Spielfeld mit Leeren Zeichen füllen
		}
	}
	
	//Zufalls mit Zeit initialisieren
	srand(time(NULL));
		
	//Schleifen Variable "GameOver" (Zum bestimmen der Spielgültigkeit) erstellen
	bool GameOver = false;
	
	//Spiel Durchlaufen
	while(GameOver == false)
	{
		//Block Variablen erstellen
		Block B;
		B.LastRotation = 0;
		int newX = 0;
		int newY = 0;
		int newRotation = 0;
		
		//Block Shape setzen
		short Art = (rand()%7);
		for(int y = 0; y < 4; y++)
		{
			for(int x = 0; x < 4; x++)
			{
				B.Shape[x][y] = Blocks[Art][x][y];
			}
		}
		
		//Prüfen ob Block Plaziert werden kann
		if(TesteBlock(newX, newY, newRotation, B.Shape))
		{
			//Block Setzen
			SetzeBlock(newX, newY, newRotation, B.Shape);
			
			//BlockDaten Speichern
			B.LastRotation = newRotation;
			B.LastX = newX;
			B.LastY = newY;
			
			DrawGame(Map, Punkte, Highscore);
			
			//Variable für Schleifengültigkeit declarieren
			bool BlockMoving = true;
			
			//ZeitVariable setzen
			long LastTime = time(NULL);
			
			//Schleife für einzelnen Block
			while(BlockMoving == true)
			{	
				//Prüfen ob Taste gedrückt wurde
				if(GetKeyState(VK_LEFT) & 0x8000)
				{
					//neue Block Position um einen nach Links Verschieben
					newX -= 1;
					
					if(TesteBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape))
					{
						//Block Bewegen
						SetzeBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape);
						
						//BlockDaten Speichern
						B.LastRotation = newRotation;
						B.LastX = newX;
						B.LastY = newY;
						
						DrawGame(Map, Punkte, Highscore);
					}
					else
					{
						newX += 1;
					}
				}
				else if(GetKeyState(VK_RIGHT) & 0x8000)
				{
					//neue Block Position um einen nach Rechts Verschieben
					newX += 1;
					
					if(TesteBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape))
					{
						//Block Bewegen
						SetzeBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape);
						
						//BlockDaten Speichern
						B.LastRotation = newRotation;
						B.LastX = newX;
						B.LastY = newY;
						
						DrawGame(Map, Punkte, Highscore);
					}
					else
					{
						newX -= 1;
					}
				}
				else if(GetAsyncKeyState(VK_UP))
				{
					//neue Block Rotation setzen
					newRotation = ChangeRotation(newRotation);
					
					if(TesteBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape))
					{
						//Block Bewegen
						SetzeBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape);
						
						//BlockDaten Speichern
						B.LastRotation = newRotation;
						B.LastX = newX;
						B.LastY = newY;
						
						DrawGame(Map, Punkte, Highscore);
						
						Sleep(100);
					}
					else
					{
						newRotation = B.LastRotation;
					}
				}
				else if(GetKeyState(VK_DOWN) & 0x8000)
				{
					//neue Block Position um einen nach Rechts Verschieben
					newY += 1;
					
					if(TesteBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape))
					{
						//Block Bewegen
						SetzeBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape);
						
						//BlockDaten Speichern
						B.LastRotation = newRotation;
						B.LastX = newX;
						B.LastY = newY;
						
						DrawGame(Map, Punkte, Highscore);
					}
					else
					{
						newY -= 1;
					}
				}
				
				
				
				
				//Prüfen um genug Zeit für das Block-Fallen vergangen ist
				if(time(NULL) >= (LastTime + 1))
				{
					newY += 1;
					
					if(TesteBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape))
					{
						//Block Bewegen
						SetzeBlock(newX, newY, newRotation, B.LastX, B.LastY, B.LastRotation, B.Shape);
						
						//BlockDaten Speichern
						B.LastRotation = newRotation;
						B.LastX = newX;
						B.LastY = newY;
						
						LastTime = time(NULL);
						
						DrawGame(Map, Punkte, Highscore);
					}
					else
					{
						newY -= 1;
						BlockMoving = false;
					}
				}
				
				//Spiel Darstellen
				/*DrawGame(Map);*/
			}
			
			Punkte += GetTetris(Punkte, Highscore);
			Punkte += GetTriple(Punkte, Highscore);
			Punkte += GetDouble(Punkte, Highscore);
			Punkte += GetLine(Punkte, Highscore);
			
		}
		else
		{
			//Spielschleife Beenden
			GameOver = true;
		}

	}
	
	//Punkte anzeigen
		cout << "Deine Punkte: " << Punkte << endl;
		
		//Auf Spieler Warten
		system("pause");
	
	//Punkte zurückgeben
	return Punkte;
}

void initBlocks()
{
	//Quadrat Erstellen
	Blocks[0][0][0] = ' ';
	Blocks[0][1][0] = ' ';
	Blocks[0][2][0] = ' ';
	Blocks[0][3][0] = ' ';
	Blocks[0][0][1] = ' ';
	Blocks[0][1][1] = '%';
	Blocks[0][2][1] = '%';
	Blocks[0][3][1] = ' ';
	Blocks[0][0][2] = ' ';
	Blocks[0][1][2] = '%';
	Blocks[0][2][2] = '%';
	Blocks[0][3][2] = ' ';
	Blocks[0][0][3] = ' ';
	Blocks[0][1][3] = ' ';
	Blocks[0][2][3] = ' ';
	Blocks[0][3][3] = ' ';
	
	//"L" 1 erstellen
	Blocks[1][0][0] = ' ';
	Blocks[1][1][0] = ' ';
	Blocks[1][2][0] = ' ';
	Blocks[1][3][0] = ' ';
	Blocks[1][0][1] = 'A';
	Blocks[1][1][1] = ' ';
	Blocks[1][2][1] = ' ';
	Blocks[1][3][1] = ' ';
	Blocks[1][0][2] = 'A';
	Blocks[1][1][2] = 'A';
	Blocks[1][2][2] = 'A';
	Blocks[1][3][2] = ' ';
	Blocks[1][0][3] = ' ';
	Blocks[1][1][3] = ' ';
	Blocks[1][2][3] = ' ';
	Blocks[1][3][3] = ' ';
	
	//"L" 2 erstellen
	Blocks[2][0][0] = ' ';
	Blocks[2][1][0] = ' ';
	Blocks[2][2][0] = ' ';
	Blocks[2][3][0] = ' ';
	Blocks[2][0][1] = ' ';
	Blocks[2][1][1] = ' ';
	Blocks[2][2][1] = ' ';
	Blocks[2][3][1] = 'H';
	Blocks[2][0][2] = ' ';
	Blocks[2][1][2] = 'H';
	Blocks[2][2][2] = 'H';
	Blocks[2][3][2] = 'H';
	Blocks[2][0][3] = ' ';
	Blocks[2][1][3] = ' ';
	Blocks[2][2][3] = ' ';
	Blocks[2][3][3] = ' ';
	
	//"Z" 1 erstellen
	Blocks[3][0][0] = ' ';
	Blocks[3][1][0] = ' ';
	Blocks[3][2][0] = ' ';
	Blocks[3][3][0] = ' ';
	Blocks[3][0][1] = ' ';
	Blocks[3][1][1] = 'O';
	Blocks[3][2][1] = 'O';
	Blocks[3][3][1] = ' ';
	Blocks[3][0][2] = 'O';
	Blocks[3][1][2] = 'O';
	Blocks[3][2][2] = ' ';
	Blocks[3][3][2] = ' ';
	Blocks[3][0][3] = ' ';
	Blocks[3][1][3] = ' ';
	Blocks[3][2][3] = ' ';
	Blocks[3][3][3] = ' ';
	
	//"Z" 2 erstellen
	Blocks[4][0][0] = ' ';
	Blocks[4][1][0] = ' ';
	Blocks[4][2][0] = ' ';
	Blocks[4][3][0] = ' ';
	Blocks[4][0][1] = ' ';
	Blocks[4][1][1] = 'M';
	Blocks[4][2][1] = 'M';
	Blocks[4][3][1] = ' ';
	Blocks[4][0][2] = ' ';
	Blocks[4][1][2] = ' ';
	Blocks[4][2][2] = 'M';
	Blocks[4][3][2] = 'M';
	Blocks[4][0][3] = ' ';
	Blocks[4][1][3] = ' ';
	Blocks[4][2][3] = ' ';
	Blocks[4][3][3] = ' ';
	
	//Langer Balken
	Blocks[5][0][0] = ' ';
	Blocks[5][1][0] = ' ';
	Blocks[5][2][0] = ' ';
	Blocks[5][3][0] = ' ';
	Blocks[5][0][1] = ' ';
	Blocks[5][1][1] = ' ';
	Blocks[5][2][1] = ' ';
	Blocks[5][3][1] = ' ';
	Blocks[5][0][2] = 'X';
	Blocks[5][1][2] = 'X';
	Blocks[5][2][2] = 'X';
	Blocks[5][3][2] = 'X';
	Blocks[5][0][3] = ' ';
	Blocks[5][1][3] = ' ';
	Blocks[5][2][3] = ' ';
	Blocks[5][3][3] = ' ';
	
	//Stufen Block erstellen
	Blocks[6][0][0] = ' ';
	Blocks[6][1][0] = ' ';
	Blocks[6][2][0] = ' ';
	Blocks[6][3][0] = ' ';
	Blocks[6][0][1] = ' ';
	Blocks[6][1][1] = 'Q';
	Blocks[6][2][1] = ' ';
	Blocks[6][3][1] = ' ';
	Blocks[6][0][2] = 'Q';
	Blocks[6][1][2] = 'Q';
	Blocks[6][2][2] = 'Q';
	Blocks[6][3][2] = ' ';
	Blocks[6][0][3] = ' ';
	Blocks[6][1][3] = ' ';
	Blocks[6][2][3] = ' ';
	Blocks[6][3][3] = ' ';
}

bool TesteBlock (int X, int Y, int rotation, int LastX, int LastY, int LastRotation, char Shape[4][4])
{
	//Rotation ermitteln und Alten Block provisorisch entfernen
	switch(LastRotation)
	{
		case 0:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + x][LastY + y] = ' ';
						}
					}
				}	
			}break;
		case 90:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						
						{
							Map[LastX + (3 - y)][LastY + x] = ' ';
						}
					}
				}	
			}break;
		case 180:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + (3 - x)][LastY + (3 - y)] = ' ';
						}
					}
				}	
			}break;
		case 270:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + y][LastY + (3 - x)] = ' ';
						}
					}
				}	
			}break;
		default:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + x][LastY + y] = ' ';
						}
					}
				}	
			}
	}
	
	
	//Überprüfungs Variable erstellen
	bool GenugPlatz = true;
	
	//Überprüfen ob genug Platz für Verschoben Block vorhanden ist
	switch(rotation)
	{
		case 0:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+x) >= 0) && ((X+x) <= 20)) && (((Y+y) >= 0) && ((Y+y) <= 19)))
							{
								if(Map[X+x][Y+y] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}break;
		case 90:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+(3-y)) >= 0) && ((X+(3-y)) <= 20)) && (((Y+x) >= 0) && ((Y+x) <= 19)))
							{
								if(Map[X+(3-y)][Y+x] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}break;
		case 180:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+(3-x)) >= 0) && ((X+(3-x)) <= 20)) && (((Y+(3-y)) >= 0) && ((Y+(3-y)) <= 19)))
							{
								if(Map[X+(3-x)][Y+(3-y)] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}break;
		case 270:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+y) >= 0) && ((X+y) <= 20)) && (((Y+(3-x)) >= 0) && ((Y+(3-x)) <= 19)))
							{
								if(Map[X+y][Y+(3-x)] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}break;
		default:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+x) >= 0) && ((X+x) <= 20)) && (((Y+y) >= 0) && ((Y+y) <= 19)))
							{
								if(Map[X+x][Y+y] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}
	}
	
	//Entfernten Block wieder Setzen
	
	switch(LastRotation)
	{
		case 0:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX+x][LastY+y] = Shape[x][y];
						}
					}
				}	
			}break;
		case 90:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX+(3-y)][LastY+x] = Shape[x][y];
						}
					}
				}	
			}break;
		case 180:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX+(3-x)][LastY+(3-y)] = Shape[x][y];
						}
					}
				}	
			}break;
		case 270:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX+y][LastY+(3-x)] = Shape[x][y];
						}
					}
				}	
			}break;
		default:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX+x][LastY+y] = Shape[x][y];
						}
					}
				}	
			}
	}
	
	//Wert Zurückgeben
	return GenugPlatz;
}

bool TesteBlock (int X, int Y, int rotation, char Shape[4][4])
{
	//Überprüfungs Variable erstellen
	bool GenugPlatz = true;
	
	//Überprüfen ob genug Platz für Verschoben Block vorhanden ist
	switch(rotation)
	{
		case 0:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+x) >= 0) && ((X+x) <= 20)) && (((Y+y) >= 0) && ((Y+y) <= 19)))
							{
								if(Map[X+x][Y+y] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}break;
		case 90:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+(3-y)) >= 0) && ((X+(3-y)) <= 20)) && (((Y+x) >= 0) && ((Y+x) <= 19)))
							{
								if(Map[X+(3-y)][Y+x] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}break;
		case 180:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+(3-x)) >= 0) && ((X+(3-x)) <= 20)) && (((Y+(3-y)) >= 0) && ((Y+(3-y)) <= 19)))
							{
								if(Map[X+(3-x)][Y+(3-y)] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}break;
		case 270:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+y) >= 0) && ((X+y) <= 20)) && (((Y+(3-x)) >= 0) && ((Y+(3-x)) <= 19)))
							{
								if(Map[X+y][Y+(3-x)] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}break;
		default:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							if((((X+x) >= 0) && ((X+x) <= 20)) && (((Y+y) >= 0) && ((Y+y) <= 19)))
							{
								if(Map[X+x][Y+y] != ' ')
								{
									GenugPlatz = false;
								}
							}
							else
							{
								GenugPlatz = false;
							}
						}
					}
				}	
			}
	}
	
	
	//Wert Zurückgeben
	return GenugPlatz;
}

void SetzeBlock (int X, int Y, int rotation, char Shape[4][4])
{
	switch(rotation)
	{
		case 0:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+x][Y+y] = Shape[x][y];
						}
					}
				}	
			}break;
		case 90:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+(3-y)][Y+x] = Shape[x][y];
						}
					}
				}	
			}break;
		case 180:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+(3-x)][Y+(3-y)] = Shape[x][y];
						}
					}
				}	
			}break;
		case 270:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+y][Y+(3-x)] = Shape[x][y];
						}
					}
				}	
			}break;
		default:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+x][Y+y] = Shape[x][y];
						}
					}
				}	
			}
	}
}

void SetzeBlock (int X, int Y, int rotation, int LastX, int LastY, int LastRotation, char Shape[4][4])
{
	//Alten Block entfernen
	switch(LastRotation)
	{
		case 0:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + x][LastY + y] = ' ';
						}
					}
				}	
			}break;
		case 90:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + (3-y)][LastY + x] = ' ';
						}
					}
				}	
			}break;
		case 180:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + (3-x)][LastY + (3-y)] = ' ';
						}
					}
				}	
			}break;
		case 270:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + y][LastY + (3-x)] = ' ';
						}
					}
				}	
			}break;
		default:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[LastX + x][LastY + y] = ' ';
						}
					}
				}	
			}
	}
	
	//Block verschieben
	switch(rotation)
	{
		case 0:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+x][Y+y] = Shape[x][y];
						}
					}
				}	
			}break;
		case 90:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+(3-y)][Y+x] = Shape[x][y];
						}
					}
				}	
			}break;
		case 180:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+(3-x)][Y+(3-y)] = Shape[x][y];
						}
					}
				}	
			}break;
		case 270:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+y][Y+(3-x)] = Shape[x][y];
						}
					}
				}	
			}break;
		default:
			{
				for(int y = 0; y < 4; y++)
				{
					for(int x = 0; x < 4; x++)
					{
						if(Shape[x][y] != ' ')
						{
							Map[X+x][Y+y] = Shape[x][y];
						}
					}
				}	
			}
	}	
}

int ChangeRotation(int LastRotation)
{
	if(LastRotation == 0)
	{
		return 90;
	}
	else if(LastRotation == 90)
	{
		return 180;
	}
	else if(LastRotation == 180)
	{
		return 270;
	}
	else
	{
		return 0;
	}
}

int GetTetris(int P, int Highscore)
{
	//Temporäre Variable erstellen
	int Punkte = 0;
	
	//Prüf Variable erstellen
	bool Tetris = true;
	
	
	for(int Line = 0; Line < 17; Line++)
	{
		Tetris = true;
		
		for(int y = 0; y < 4; y++)
		{
			for(int x = 0; x < 20; x++)
			{
				if(Map[x][Line+y] == ' ')
				{
					Tetris = false;
				}
			}
		}
		
		if(Tetris == true)
		{
			//Tetris Anzeigen
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					Map[x][Line+y] = '=';
				}
			}
				
			DrawGame(Map, Punkte, Highscore);
				
			//1/4 Sekunden Warten
			Sleep(250);
				
			//Temporäres Spielfeld erstellen
			char TempMap[20][20];
			
			//Untere Hälfte durchlaufen
			for(int y = 19; y > Line+3; y--)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y] = Map[x][y];
				}
			}
			
			//Obere Hälfte durchlaufen
			for(int y = Line-1; y >= 0; y--)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y+4] = Map[x][y];
				}
			}
			
			//Oberen Leeren Teil mit ' ' füllen
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y] = ' ';
				}
			}
			
			//Map erneuern
			for(int y = 0; y < 20; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					Map[x][y] = TempMap[x][y];
				}
			}
			
			//SpielDartstellen
			DrawGame (Map, P, Highscore);
			
			//Schleife erneut beginnen
			Line = 0;
			
			//Punkte setzen
			Punkte += 10;
		}
	}
	
	return Punkte;
}

int GetTriple(int P, int Highscore)
{
	//Temporäre Variable erstellen
	int Punkte = 0;
	
	//Prüf Variable erstellen
	bool Triple = true;
	
	
	for(int Line = 0; Line < 18; Line++)
	{
		Triple = true;
		
		for(int y = 0; y < 3; y++)
		{
			for(int x = 0; x < 20; x++)
			{
				if(Map[x][Line+y] == ' ')
				{
					Triple = false;
				}
			}
		}
		
		if(Triple == true)
		{
			//Triple Anzeigen
			for(int y = 0; y < 3; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					Map[x][Line+y] = '=';
				}
			}
			
			DrawGame(Map, P, Highscore);
			
			//1/4 Sekunden Warten
			Sleep(250);
				
			//Temporäres Spielfeld erstellen
			char TempMap[20][20];
			
			//Untere Hälfte durchlaufen
			for(int y = 19; y > Line+2; y--)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y] = Map[x][y];
				}
			}
			
			//Obere Hälfte durchlaufen
			for(int y = Line-1; y >= 0; y--)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y+3] = Map[x][y];
				}
			}
			
			//Oberen Leeren Teil mit ' ' füllen
			for(int y = 0; y < 3; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y] = ' ';
				}
			}
			
			//Map erneuern
			for(int y = 0; y < 20; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					Map[x][y] = TempMap[x][y];
				}
			}
			
			//SpielDartstellen
			DrawGame (Map, P, Highscore);
			
			//Schleife erneut beginnen
			Line = 0;
			
			//Punkte setzen
			Punkte += 7;
		}
	}
	
	return Punkte;
}

int GetDouble(int P, int Highscore)
{
	//Temporäre Variable erstellen
	int Punkte = 0;
	
	//Prüf Variable erstellen
	bool Double = true;
	
	
	for(int Line = 0; Line < 19; Line++)
	{
		Double = true;
		
		for(int y = 0; y < 2; y++)
		{
			for(int x = 0; x < 20; x++)
			{
				if(Map[x][Line+y] == ' ')
				{
					Double = false;
				}
			}
		}
		
		if(Double == true)
		{
			//Double Anzeigen
			for(int y = 0; y < 2; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					Map[x][Line+y] = '=';
				}
			}
			
			DrawGame(Map, P, Highscore);
			
			//1/4 Sekunden Warten
			Sleep(250);
				
			//Temporäres Spielfeld erstellen
			char TempMap[20][20];
			
			//Untere Hälfte durchlaufen
			for(int y = 19; y > Line+1; y--)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y] = Map[x][y];
				}
			}
			
			//Obere Hälfte durchlaufen
			for(int y = Line-1; y >= 0; y--)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y+2] = Map[x][y];
				}
			}
			
			//Oberen Leeren Teil mit ' ' füllen
			for(int y = 0; y < 2; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y] = ' ';
				}
			}
			
			//Map erneuern
			for(int y = 0; y < 20; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					Map[x][y] = TempMap[x][y];
				}
			}
			
			//SpielDartstellen
			DrawGame (Map, P, Highscore);
			
			//Schleife erneut beginnen
			Line = 0;
			
			//Punkte setzen
			Punkte += 3;
		}
	}
	
	return Punkte;
}

int GetLine(int P, int Highscore)
{
	//Temporäre Variable erstellen
	int Punkte = 0;
	
	//Prüf Variable erstellen
	bool L = true;
	
	
	for(int Line = 0; Line < 20; Line++)
	{
		
		L = true;
		
		for(int x = 0; x < 20; x++)
		{
			if(Map[x][Line] == ' ')
			{
				L = false;
			}
		}
		
		if(L == true)
		{
			//Line Anzeigen
			for(int x = 0; x < 20; x++)
			{
				Map[x][Line] = '=';
			}
			
			DrawGame(Map, P, Highscore);
			
			//1/4 Sekunden Warten
			Sleep(250);
				
			//Temporäres Spielfeld erstellen
			char TempMap[20][20];
			
			//Untere Hälfte durchlaufen
			for(int y = 19; y > Line; y--)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y] = Map[x][y];
				}
			}
			
			//Obere Hälfte durchlaufen
			for(int y = Line-1; y >= 0; y--)
			{
				for(int x = 0; x < 20; x++)
				{
					TempMap[x][y+1] = Map[x][y];
				}
			}
			
			//Oberen Leeren Teil mit ' ' füllen
			for(int x = 0; x < 20; x++)
			{
				TempMap[x][0] = ' ';
			}
			
			//Map erneuern
			for(int y = 0; y < 20; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					Map[x][y] = TempMap[x][y];
				}
			}
			
			//SpielDartstellen
			DrawGame (Map, P, Highscore);
			
			//Schleife erneut beginnen
			Line = 0;
			
			//Punkte setzen
			Punkte += 1;
		}
	}
	
	return Punkte;
}
