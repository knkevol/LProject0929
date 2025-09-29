#include <iostream>
#include <Windows.h>

using namespace std;

struct FCharacter
{
	int X;		//4byte
	int Y;		//4byte
	char Shape; //1byte
};
FCharacter Player;
FCharacter Monster;

FCharacter Characters[2];

void Render(FCharacter Indata)
{
	//for - ALL
	COORD Cur;
	Cur.X = Indata.X;
	Cur.Y = Indata.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	cout << Indata.Shape;
}

int main()
{
	//Load > 파일입출력으로 제작
	Player.X = 1;
	Player.Y = 1;
	Player.Shape = 'P';

	Monster.X = 10;
	Monster.Y = 10;
	Monster.Shape = 'M';

	Render(Player);
	Render(Monster);

	return 0;
}