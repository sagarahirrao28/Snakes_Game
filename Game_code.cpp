#include <conio.h> 
#include <iostream> 
#include <windows.h>
using namespace std;

// height and width of the boundary 
const int width = 80; 
const int height = 20; 

int x, y; // head coordinates of snake (x-axis, y-axis)

int fruitCordX, fruitCordY;// food coordinates 
 
int playerScore; // variable to store the score
 
int snakeTailX[100], snakeTailY[100]; // Array to store the coordinates of snake tail (x-axis, y-axis)
 
int snakeTailLen; // variable to store the length of the sanke's tail
 
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // for storing snake's moving direction

snakesDirection sDir; // snakesDirection variable 
 
bool isGameOver; // boolean variable for checking game is over or not

// Initializing the game
void GameInit() 
{ 
	isGameOver = false; 
	sDir = STOP; 
	x = width / 2; 
	y = height / 2; 
	fruitCordX = rand() % width; 
	fruitCordY = rand() % height; 
	playerScore = 0; 
}

// Function for creating the game board & rendering 
void GameRender(string playerName) 
{ 
	system("cls"); // Clear the console 
 
	for (int i = 0; i < width + 2; i++) // Creating top walls with '-'
		cout << "-"; 
	cout << endl; 

	for (int i = 0; i < height; i++) 
    { 
		for (int j = 0; j <= width; j++) 
        {  
			if (j == 0 || j == width) // Creating side walls with '|'
				cout << "|";  
			if (i == y && j == x) // Creating snake's head with 'O'
				cout << "O";  
			else if (i == fruitCordY && j == fruitCordX) // Creating the sanke's food with '#'
				cout << "#"; 
			else // Creating snake's tail with '*'  
            { 
				bool prTail = false; 
				for (int k = 0; k < snakeTailLen; k++) 
                { 
					if (snakeTailX[k] == j && snakeTailY[k] == i) 
                    { 
						cout << "*"; 
						prTail = true; 
					} 
				} 
				if (!prTail) 
					cout << " "; 
			} 
		} 
		cout << endl; 
	} 

	for (int i = 0; i < width + 2; i++) // Creating bottom walls with '-' 
		cout << "-"; 
	cout << endl; 

	cout << playerName << "'s Score: " << playerScore // Display player's score 
		<< endl; 
}

// Function for updating the game state 
void UpdateGame() 
{ 
	int prevX = snakeTailX[0]; 
	int prevY = snakeTailY[0]; 
	int prev2X, prev2Y; 
	snakeTailX[0] = x; 
	snakeTailY[0] = y; 

	for (int i = 1; i < snakeTailLen; i++) 
    { 
		prev2X = snakeTailX[i]; 
		prev2Y = snakeTailY[i]; 
		snakeTailX[i] = prevX; 
		snakeTailY[i] = prevY; 
		prevX = prev2X; 
		prevY = prev2Y; 
	} 

	switch (sDir) 
    { 
	case LEFT: 
		x--; 
		break; 
	case RIGHT: 
		x++; 
		break; 
	case UP: 
		y--; 
		break; 
	case DOWN: 
		y++; 
		break; 
	} 

	if (x >= width || x < 0 || y >= height || y < 0) // Checks for snake's collision with the wall (|) 
		isGameOver = true; 
 
	for (int i = 0; i < snakeTailLen; i++) // Checks for collision with the tail (*) 
    { 
		if (snakeTailX[i] == x && snakeTailY[i] == y) 
			isGameOver = true; 
	} 
 
	if (x == fruitCordX && y == fruitCordY) // Checks for snake's collision with the food (#)
    { 
		playerScore += 10; 
		fruitCordX = rand() % width; 
		fruitCordY = rand() % height; 
		snakeTailLen++; 
	} 
}

// Function to set the game difficulty level 
int SetDifficulty() 
{ 
	int dfc, choice; 
	cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard"
            "\nNOTE: if not chosen or pressed any other key, the difficulty will be automatically set to medium\nChoose difficulty level: "; 
	cin >> choice; 
	switch (choice) 
    { 
	case '1': 
		dfc = 50; 
		break; 
	case '2': 
		dfc = 100; 
		break; 
	case '3': 
		dfc = 150; 
		break; 
	default: 
		dfc = 100; 
	} 
	return dfc; 
}

// Function to handle user UserInput 
void UserInput() 
{ 
	if (_kbhit()) // Checks if a key is pressed or not 
    { 
		switch (_getch()) // Getting the pressed key
        { 
		case 'a': 
			sDir = LEFT; 
			break; 
		case 'd': 
			sDir = RIGHT; 
			break; 
		case 'w': 
			sDir = UP; 
			break; 
		case 's': 
			sDir = DOWN; 
			break; 
		case 'x': 
			isGameOver = true; 
			break; 
		} 
	} 
}

// Game looping function 
int main() 
{ 
	string playerName; 
	cout << "enter your name: "; 
	cin >> playerName; 
	int dfc = SetDifficulty(); 

	GameInit(); 
	while (!isGameOver) { 
		GameRender(playerName); 
		UserInput(); 
		UpdateGame(); 
		// creating a delay according to the chosen difficulty 
		Sleep(dfc); 
	} 

	return 0;
}
