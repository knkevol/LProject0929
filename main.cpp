#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

enum ERenderScreenBuffer
{
	FrontBuffer = 0,
	BackBuffer = 1
};

int CurrentBufferIndex = FrontBuffer;

HANDLE ScreenBuffers[2];

struct FCharacter
{
	int X;			//4byte
	int Y;			//4byte
	string Shape;	//1byte
};
FCharacter Player;
FCharacter Monster;

FCharacter Characters[2]; //Struct Array

int KeyCode = 0;

void Input()
{
	KeyCode = _getch();
}


void RenderCharacter(const FCharacter* InData)
{
		COORD Cur;
		Cur.X = (short)InData->X;
		Cur.Y = (short)InData->Y;

		SetConsoleCursorPosition(ScreenBuffers[CurrentBufferIndex], Cur);
		WriteConsole(ScreenBuffers[CurrentBufferIndex], InData->Shape.c_str(), 1, NULL, NULL);
		//cout << Indata->Shape; == WriteConsole
}

// == system("cls")
void Clear()
{
	COORD coordScreen = { 0, 0 };    // home for the cursor
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	//Screen Buffer Information
	GetConsoleScreenBufferInfo(ScreenBuffers[CurrentBufferIndex], &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(ScreenBuffers[CurrentBufferIndex],
		(TCHAR)' ',
		dwConSize,
		coordScreen,
		&cCharsWritten);
}

//Draw
void Presect() 
{
	SetConsoleActiveScreenBuffer(ScreenBuffers[CurrentBufferIndex]); //Draw Screen
	CurrentBufferIndex++;
	CurrentBufferIndex = CurrentBufferIndex % 2; // 0~1
}

void Render()
{
	Clear();

	for (int i = 0; i < 2; i++)
	{
		RenderCharacter(&Characters[i]);
	}

	Presect(); //Replace
}


void Init()
{
	//0
	ScreenBuffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, NULL);

	//1
	ScreenBuffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, NULL);


	srand((unsigned int)time(nullptr));

	//Load > File Inout
	Characters[0].X = 1;
	Characters[0].Y = 1;
	Characters[0].Shape = "P";

	Characters[1].X = 10;
	Characters[1].Y = 10;
	Characters[1].Shape = "M";
}

void MovePlayer()
{
	//Design Pattern
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