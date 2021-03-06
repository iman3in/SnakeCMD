#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <fstream>
using namespace std;

int width = 40; 
int height = 20; // tool o arz e zamin e bazi 
bool gameover; // neshan mide ke player bakhte ya na
bool wall; // do halat e mokhtalef e bazi 
int x, y, fx, fy, score; // mokhtasat sare mar va fruit va emtiaz e bazi 
int mx, my; //mokhtasat block  
int bfx , bfy ; //mokhtasat e big fruit
int bftime ; //timer big fruit 
int bfcount ; //timer e random e big fruit baraye zaher shodan 
int tailx[1000], taily[1000]; //mokhtasat e dom e mar
int ntail ; //tool dom e mar
bool restart; //baraye shoro e dobare e bazi 
int velocity = 50; //meghdar e sorat e mar
enum direction {stop = 0 , Left , Right , Up , Down , reset}; 
direction dr; // jahat e harekat
bool pwse = 0; // chek e pause
int scoree[10]; // emtiaz haro zakhire mikone

//reza dakheli
//ranke bazikona ro tooye ye file dakhele system save mikone
void outputscore()
{
	ofstream ranking("score.txt", ios::out);
	for (int i = 9; i >= 0; i--)
		ranking << scoree[i] << endl;
}

//reza dakheli
//rank haro load mikone
void inputscore()
{
	ifstream ranking("score.txt", ios::in);
	for (int i = 9; i >= 0; i--)
		ranking >> scoree[i];

}

//reza dakheli 
//score ha ro sefr mikone 
void resetscore()
{
	for (int i = 0; i < 10; i++)
		scoree[i] = 0;

	ofstream point;
	point.open("score.txt", ios::out);

	for (int i = 0; i < 10; i++)
	{
		point << scoree[i] << endl;
	}
	point.close();
}

//reza dakheli
//score jadid ro ba ghabli ha moghayese mikone va dar jadval gharar midahad
void Scoring()
{
	fstream point;
	point.open("score.txt", ios::in);
	if (!point.is_open())
	{
		resetscore();
	}
	inputscore();
	for (int i = 9; i >= 0; i--)
	{
		if (score > scoree[i])
		{
			for (int j = 0; j < i; j++)
			{
				scoree[j] = scoree[j + 1];
			}
			scoree[i] = score;
			break;
		}
	}
	outputscore();
	cout << endl;
	cout << "highscroes :" << endl;
	cout << " 1)" << scoree[9] << endl;
	cout << " 2)" << scoree[8] << endl;
	cout << " 3)" << scoree[7] << endl;
	cout << " 4)" << scoree[6] << endl;
	cout << " 5)" << scoree[5] << endl;
	cout << " 6)" << scoree[4] << endl;
	cout << " 7)" << scoree[3] << endl;
	cout << " 8)" << scoree[2] << endl;
	cout << " 9)" << scoree[1] << endl;
	cout << "10)" << scoree[0] << endl;
}

//iman soltani
//dar soorati ke bazi ro save karde bashi bazi e ghabli ro load mikone 
void load()
{
	ifstream save;
	save.open("save.txt", ios::in);

	save >> score;
	save >> width;
	save >> height;
	save >> wall;
	save >> x;
	save >> y;
	save >> fx;
	save >> fy;
	save >> mx;
	save >> my;
	save >> bfx;
	save >> bfy;
	save >> bftime;
	save >> bfcount;
	save >> ntail;
	for (int i = 0; i < ntail; i++)
	{
		save >> tailx[i];
		save >> taily[i];
	}
	save.close();
}

bool start()
{
	gameover = false;
	dr = stop;
	cout << "Welcome to Snake oooooO   *" << endl;
	cout << "HELP :" << endl;
	cout << "press W - A - S - D to move." << endl;
	cout << "press P to Pause and unpause.(and you can press O while game is pause to save game.)" << endl;
	cout << "press 1 to 5 numbers for set velocity." << endl;
	cout << "press R to reset." << endl;
	cout << "press M to resize the map.(its just avaible befor start the game)" << endl;
	cout << "press Z for start game in wall mode.(its just avaible befor start the game)" << endl;
	cout << "press X for start game in wall less mode.(its just avaible befor start the game)" << endl;
	cout << "press L to Load the last game you played." << endl;
	cout << "and press space bar for start new game ;)" << endl;
	char f = _getch();
	while (f != 32)
	{
		f = _getch();
		if (f == 'm')
		{
			cout << "Height : ";
			cin >> height;
			cout << "Width : ";
			cin >> width;
		}
		if (f == 'z')
		{
			wall = true;
			cout << "wall mode ON." << endl;
		}
		if (f == 'x')
		{
			wall = false;
			cout << "wall mode OFF." << endl;
		}
		if (f == 'l')
		{
			load();
			cout << "Game Loaded.";
			return 0;
		}
	}
	x = width / 2;
	y = height / 2;
	fx = rand() % width;
	fy = rand() % height;
	mx = rand() % width;
	my = rand() % height;
	score = 0;
	ntail = 0;
	bfcount = 0;
	bftime = 0;
	bfx = 10000;
	bfy = 10000;
	velocity = 50;
	return 0;
}

//iman soltani 
//zamin e bazi ra namayesh midahad
void show()
{
	system("cls");
	for (int i = 0; i < width+2; i++)
	{
		cout << "I";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "I";

			if (j == x && i == y)
				cout << "O";
			else if (j == fx && i == fy)
				cout << "*";
			else if (j == mx && i == my)
				cout << "#";
			else if (j == bfx && i == bfy)
				cout << "@";
			else
			{
				bool print = false;
				for (int k = 0; k < ntail ; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "I";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++)
	{
		cout << "I";
	}
	cout << endl;
	cout << "score : " << score << endl;
}

//iman soltani
//vorodi ha ro migire
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a' :
				if (dr != Right)
				dr = Left;
				break;
			case 'd' :
				if (dr != Left)
				dr = Right;
				break;
			case 'w' :
				if (dr != Down)
				dr = Up;
				break;
			case 's' :
				if (dr != Up)
				dr = Down;
				break;
			case 75:
				if (dr != Right)
					dr = Left;
				break;
			case 77:
				if (dr != Left)
					dr = Right;
				break;
			case 72:
				if (dr != Down)
					dr = Up;
				break;
			case 80:
				if (dr != Up)
					dr = Down;
				break;
			case 'r' :
				dr = reset;
				break;
			case 'p' :
				if (pwse == 0)
					pwse = 1;
				else if (pwse == 1)
					pwse = 0;
				break;
			case '1':
				velocity = 10;
				break;
			case '2':
				velocity = 50;
				break;
			case '3':
				velocity = 150;
				break;
			case '4':
				velocity = 300;
				break;
			case '5':
				velocity = 500;
				break;
		}
	}
}

//iman soltani
//mar ro ba tavajoh be vorodi ha harekat midahad
void move()
{
	if (dr != stop)
	{
		int prevx = tailx[0];
		int prevy = taily[0];
		int prev2x, prev2y;
		tailx[0] = x;
		taily[0] = y;
		for (int i = 1; i < ntail; i++)
		{
			prev2x = tailx[i];
			prev2y = taily[i];
			tailx[i] = prevx;
			taily[i] = prevy;
			prevx = prev2x;
			prevy = prev2y;
		}
	}
	switch (dr)
	{
	case Left :
		x--;
		break;
	case Right :
		x++;
		break;
	case Up :
		y--;
		break;
	case Down :
		y++;
		break;
	}
}

//reza dakheli 
//bakht e bazi ro chek mikone
void losechk()
{
	if (wall)
	{
		if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
			gameover = 1;
	}
	if (x < 0)
	{
		x = width - 1;
	}
	if (x > width - 1)
	{
		x = 0;
	}
	if (y < 0)
	{
		y = height - 1;
	}
	if (y > height - 1)
	{
		y = 0;
	}
	for (int i = 1; i < ntail; i++)
	{
		if (tailx[i] == x && taily[i] == y)
			gameover = 1;
	}
	if (ntail < 0)
		gameover = 1;
	if (score < 0)
		gameover = 1;
}

//iman soltnai 
//yek fruit dar zamin e bazi be vojod miare ke va agar bokhorish tool e mar ziad mishe va emtiaz mide
void fruit()
{
	if (x == fx && y == fy)
	{
		ntail++;
		score += 10;
		fx = rand() % width;
		fy = rand() % height;
	}
}

//reza dakheli 
//yek mane dar bazi be vojod miare ke dar asar barkhord ba oon emtiaz o tool mar kam mishe 
void block()
{
	if (mx == x && my == y)
	{
		mx = rand() % width;
		my = rand() % height;
		ntail--;
		score -= 20;
	}
}

//iman soltani
//bazi ra reset mikone
void resetcheck()
{
	if (dr == reset)
	{
		system("cls");
		start();
	}
}

//iman soltnai 
//fruit e emtiazi dar time random be vojod miare ke emtiazesh bishtare
void bigfruit()
{
	if (dr != stop)
		bfcount += (rand() % 3);
	if (bfcount % 3 == 0 && bfcount > 200)
	{
		bfx = rand() % width;
		bfy = rand() % height;
		bfcount = 0;
	}
	if (x == bfx && y == bfy)
	{
		ntail++;
		score += 100;
		bfx = 10000;
		bfy = 10000;
		bftime = 0;
		bfcount = 0;
	}
	if (bfx < width - 1 && bfx > 0 && bfy < height - 1 && bfy > 0)
	{
		bftime++;
		bfcount = 0;
	}

	if (bftime > 200)
	{
		bftime = 0;
		bfcount = 0;
		bfx = 10000;
		bfy = 10000;
	}
}

//iman soltani
//etela'at e bazi ro save mikone dar file
void save()
{
	ofstream save;
	save.open("save.txt", ios::out);

	save << score << " ";
	save << width << " ";
	save << height << " ";
	save << wall << " ";
	save << x << " ";
	save << y << " ";
	save << fx << " ";
	save << fy << " ";
	save << mx << " ";
	save << my << " ";
	save << bfx << " ";
	save << bfy << " ";
	save << bftime << " ";
	save << bfcount << " ";
	save << ntail << " ";
	for (int i = 0; i < ntail; i++)
	{
		save << tailx[i] << " ";
		save << taily[i] << " ";
	}
	save.close();
}

//iman soltani
//bazi ro motevaghef mikonad
void pause()
{
	if (pwse == 1)
		cout << "press O to save the game.\nand press P for resume game.";

	while (pwse == 1)
	{
		char f = _getch();
		if (f == 'p')
			pwse = 0;
		if (f == 'o')
			save();
	}
}

//reza dakheli 
//vaghti bazi tamoom she in tabe ejra mishe ke emtiaz ha va yek menu namayesh mide
bool game_over()
{
	system("cls");
	cout << "GAME OVER !" << endl << endl;
	Scoring();
	cout << endl << "press R for reset scores." << endl;
	cout << "press SpaceBar for play a new game." << endl;
	cout << "press ESC for Exit.";
	int kb;
	do
	{
		kb = _getch();
		if (kb == 'r')
		{
			system("cls");
			resetscore();
			Scoring();
			cout << endl << "press R for reset scores." << endl;
			cout << "press SpaceBar for play a new game." << endl;
			cout << "press ESC for Exit.";
		}
		else if (kb == 32)
		{
			system("cls");
			return 1 ;
		}
		else if (kb == 27)
		{
			return 0;
		}
	} while (1);
}

int main()
{
	do
	{
		start();
		while (!gameover)
		{
			Sleep(velocity);
			show();
			input();
			move();
			losechk();
			fruit();
			block();
			bigfruit();
			resetcheck();
			pause();
		}
		restart = 0;
		restart = game_over();
	}
	while (restart);
}