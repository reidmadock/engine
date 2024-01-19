/*
	To start off I am following along with Javidx9's "Code-It Yourself!" tutorial
	https://www.youtube.com/watch?v=xW8skO7MFYw&list=PLrOv9FMX8xJE8NgepZR1etrsU63fDDGxO&index=2

	Javidx9 himself is basing this version on the Wolfenstein 3D engine.

	I'd like to make my own adjustments as I learn more and adjust

	very introductory stuff here
*/
#include <iostream>
#include <Windows.h>

using namespace std;

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float fFOV = 3.14159 / 4.0;

float fDepth = 16.0f;

int main() {
	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	wstring map;
	map += L"################";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";


	// Game Loop
	while (1) {
		for (int i = 0; i < length; i++)
		{
			// For each col, calculate the projected ray angle into the world
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)i / (float)nScreenWidth) * fFOV;

			float fDistanceToWall = 0;
			bool bHitWall;

			float fEyeX = sinf(fRayAngle); 
			float fEyeY = cosf(fRayAngle);

			while (!bHitWall && fDistanceToWall < fDepth) {
				fDistanceToWall += 0.1f;

				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
					bHitWall = true;
					fDistanceToWall = fDepth;
				} else {
					// Ray is inbounds
					if (map[nTestY * nMapWidth + nTestX] == '#') {
						bHitWall = true;
					}
				}
			}

			// Calculate distance to floor/ceiling
			int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
			int nFloor = nScreenHeight - nCeiling;

			for (int y = 0; y < nScreenHeight; y++) {
				if (y < nCeiling) {
					screen[y * nScreenWidth + i] = ' '; // Blank space for the ceiling
				} else (y > nCeiling && y <= nFloor) {
					screen[y * nScreenWidth + i] = '#'; // Hash for the wall
				} else {
					screen[y * nScreenWidth + i] = ' '; // Blank for the floor
				}
			}
		}

		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

	}

	return 0;
}
