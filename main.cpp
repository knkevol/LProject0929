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
		Cur.X = (SHORT)Indata.X;
		Cur.Y = (SHORT)Indata.Y;
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
	if (KeyCode == 'w')
	{
		Characters[0].Y--;
	}
	else if (KeyCode == 's')
	{
		Characters[0].Y++;
	}
	else if (KeyCode == 'a')
	{
		Characters[0].X--;
	}
	else if (KeyCode == 'd')
	{
		Characters[0].X++;
	}
	else if (KeyCode == 'q')
	{
		bIsPlaying = false;
	}
	system("cls");
}

void MoveMonster()
{

}

void Tick()
{
	MovePlayer();
	MoveMonster();
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