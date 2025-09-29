#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

struct FCharacter
{
	int X;		//4byte
	int Y;		//4byte
	char Shape; //1byte
};
FCharacter Player;
FCharacter Monster;

FCharacter Characters[2]; //구조체 배열

void RenderCharacter(FCharacter Indata)
{
		COORD Cur;
		Cur.X = (short)Indata.X;
		Cur.Y = (short)Indata.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
		cout << Indata.Shape;
}

void Render()
{
	for (int i = 0; i < 2; i++)
	{
		RenderCharacter(Characters[i]);
	}
}

void Init()
{
	srand((unsigned int)time(nullptr));

	//Load > 파일입출력으로 제작
	Characters[0].X = 1;
	Characters[0].Y = 1;
	Characters[0].Shape = 'P';

	Characters[1].X = 10;
	Characters[1].Y = 10;
	Characters[1].Shape = 'M';
}
int KeyCode = 0;
void Input()
{
	KeyCode = _getch();
}

void MovePlayer()
{
	bool bIsPlaying = true;
	//디자인 패턴
	switch (KeyCode)
	{
	case 'w': //Up
		Characters[0].Y--;
		break;
	case 's': //Down
		Characters[0].Y++;
		break;
	case 'a': //Left
		Characters[0].X--;
		break;
	case 'd': //Right
		Characters[0].X++;
		break;
	default: //Error
		break;
	}
}

void MoveMonster()
{ //No Input
	int Direction = rand() % 4;

	switch (Direction)
	{
	case 0: //Up
		Characters[1].Y--;
		break;
	case 1: //Down
		Characters[1].Y++;
		break;
	case 2: //Left
		Characters[1].X--;
		break;
	case 3: //Right
		Characters[1].X++;
		break;
	default: //Error
		break;
	}
}

void Tick()
{
	MovePlayer();
	MoveMonster();
	system("cls");
}

int main()
{
	Init(); //UE5 == BeginPlay

	while (true)
	{
		Input();
		Tick();
		Render();
	}
	
	return 0;
}