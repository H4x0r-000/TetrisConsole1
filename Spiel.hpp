unsigned int Spiel(unsigned short Level, int Highscore);
void initBlocks();
int ChangeRotation(int LastRotation);
void SetzeBlock (int X, int Y, int rotation, char Shape[4][4]);
bool TesteBlock (int X, int Y, int rotation, char Shape[4][4]);
bool TesteBlock (int X, int Y, int rotation, int LastX, int LastY, int LastRotation, char Shape[4][4]);
void SetzeBlock (int X, int Y, int rotation, int LastX, int LastY, int LastRotation, char Shape[4][4]);
int GetTetris(int P, int Highscore);
int GetTriple(int P, int Highscore);
int GetDouble(int P, int Highscore);
int GetLine(int P, int Highscore);
