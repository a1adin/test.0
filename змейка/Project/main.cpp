#include <iostream>  //����������� ����������
#include <time.h> //��������� �����
#include <stdio.h> //��� printf
#include <windows.h> // ��� HANDLE, �������, �����
#include <conio.h>  //��� kbhit

using namespace std;



HANDLE hConsole;
//HANDLE hStdout, hStdin;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
} 
//����
enum ConsoleColor
{
    	Black         = 0,
		Blue          = 1,
		Green         = 2,
		Cyan          = 3,
		Red           = 4,
		Magenta       = 5,
		Brown         = 6,
		LightGray     = 7,
		DarkGray      = 8,
		LightBlue     = 9,
		LightGreen    = 10,
		LightCyan     = 11,
		LightRed      = 12,
		LightMagenta  = 13,
		Yellow        = 14,
		White         = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


class Zmeja  // ��������� ������ 
{
	public:COORD *t; //�����
	public:int PCount; //���������� �����
};
enum uprawlenie{LEFT,UP,RIGHT,DOWN}; //����������� ������
class Game //�����-��������: ������, �����, ������������ �� X � Y, ��������, �����������
{
	public:Zmeja gaduka; //������
	public:COORD jabloko; //������
	public:int dx,dy; //������������
	public:int pause; //��������
	public:int nap; //�����������
	
};


void PlusJabloko(Game &g) //������� ��������� �����
{
	int i,x,y;
	int n = g.gaduka.PCount;
	do
	{
		x = rand() % 56+3; //
		y = rand() % 19+3; //��������� ������
		for(i = 0; i < n; i++)
		{
			if(x == g.gaduka.t[i].X && y == g.gaduka.t[i].Y) // �������� ���� ������ �� ������� �� ����
				break;
		}
	}
	while(i < n);
	g.jabloko.X = x; //
	g.jabloko.Y = y; //���������� ������� ������
	SetConsoleCursorPosition(hConsole, g.jabloko); //��������� ������ � ��� �������
	SetConsoleTextAttribute(hConsole,0x0c); //���� ������  
	printf("%c", 4); //������ ������ ����� ����� ��������
	
}


void skorostGame(Game &g) // ������� ������ ������ �� ��������� � ��������
{
	system("cls");
	g.gaduka.PCount = 3; //������� ����� � ������
	g.gaduka.t = new COORD [3];//������� �����
	for(int i = 0; i < 3; i++)
	{
		g.gaduka.t[i].X = 20 + i;
		g.gaduka.t[i].Y = 20;
		
	}
	g.dx = 1;
	g.dy = 0;
	g.pause = 100;//�������� ������������ ����
	PlusJabloko(g);//������ ������
}
void Level()
{
	GotoXY(10,10);cout <<"Vy nikogda ne vyigraete"<<endl; //�������: �� ������� �� ���������
	GotoXY(10,11);cout <<"esli ne budete bditelny!"<<endl; //�������: ���� �� ������ ���������!
}
void ZmejaStart()
{
	GotoXY(10,15);cout <<"Soberi 50 yablok, togda posmotrim ;)"<<endl; //�������: ������ 50 �����, ����� ��������� ;)
}
void STENA_2() //��� ����������, ������������ �� �����
{
	SetColor(LightBlue , Black);GotoXY(20,0);cout << "Snake game by Danilenko Alexander" <<endl;  //�������: ���� ������ ��������� ����������
	GotoXY(64,2);cout <<  "Dannue:" << endl ; //������
	GotoXY(64,3);cout <<  "Yablok:0" << endl ; //�����
	GotoXY(64,4); cout <<  "Dlina:3"<< endl; //�����
	GotoXY(64,5); cout <<  "Speed:0" << endl; //��������
	GotoXY(64,7); cout << "Uprawlenie:" <<  endl; //����������
    GotoXY(64,8); cout << "Esc:Wuxod" <<  endl; //�����
	GotoXY(64,9); cout << "P:Pause" <<  endl; //�����
	GotoXY(64,10); cout <<"S:Start" <<  endl; //�����
	GotoXY(64,11); cout <<"L:Level" <<  endl; //�������
	GotoXY(64,13);printf("%c",24);cout <<":Wwerx"<<endl; //�����
	GotoXY(64,14);printf("%c",25);cout<<":Wniz"<<endl;   //����
	GotoXY(64,15);printf("%c",27);cout<<":Wlewo"<<endl;  //�����
	GotoXY(64,16);printf("%c",26);cout<<":Wprawo"<<endl; //������
				{SetColor(LightMagenta , Black);
				
                GotoXY(2,2); //������ ������� �������������� �����-������
				int m = 0;
				for(m = 0; m < 60; m++)
				{
					printf("*");
				}
				}
				
				{
					GotoXY(2,24); //������ ������ �������������� �����-������
					int m = 0;
					for(m = 0; m < 60;m++)
					{
						printf("*");
					}
				}
				{	//������ ����� ������������ �����-������
					GotoXY(2,3); cout << "*"<<endl;
					GotoXY(2,4); cout << "*"<<endl;
					GotoXY(2,5); cout << "*"<<endl;
					GotoXY(2,6); cout << "*"<<endl;
					GotoXY(2,7); cout << "*"<<endl;
					GotoXY(2,8); cout << "*"<<endl;
					GotoXY(2,9); cout << "*"<<endl;
					GotoXY(2,10); cout << "*"<<endl;
					GotoXY(2,11); cout << "*"<<endl;
					GotoXY(2,12); cout << "*"<<endl;
					GotoXY(2,13); cout << "*"<<endl;
					GotoXY(2,14); cout << "*"<<endl;
					GotoXY(2,15); cout << "*"<<endl;
					GotoXY(2,16); cout << "*"<<endl;
					GotoXY(2,17); cout << "*"<<endl;
					GotoXY(2,18); cout << "*"<<endl;
					GotoXY(2,19); cout << "*"<<endl;
					GotoXY(2,20); cout << "*"<<endl;
					GotoXY(2,21); cout << "*"<<endl;
					GotoXY(2,22); cout << "*"<<endl;
					GotoXY(2,23); cout << "*"<<endl;
				}
				{   //������ ������ ������������ �����-������
					GotoXY(61,3); cout << "*"<<endl;
					GotoXY(61,4); cout << "*"<<endl;
					GotoXY(61,5); cout << "*"<<endl;
					GotoXY(61,6); cout << "*"<<endl;
					GotoXY(61,7); cout << "*"<<endl;
					GotoXY(61,8); cout << "*"<<endl;
					GotoXY(61,9); cout << "*"<<endl;
					GotoXY(61,10); cout << "*"<<endl;
					GotoXY(61,11); cout << "*"<<endl;
					GotoXY(61,12); cout << "*"<<endl;
					GotoXY(61,13); cout << "*"<<endl;
					GotoXY(61,14); cout << "*"<<endl;
					GotoXY(61,15); cout << "*"<<endl;
					GotoXY(61,16); cout << "*"<<endl;
					GotoXY(61,17); cout << "*"<<endl;
					GotoXY(61,18); cout << "*"<<endl;
					GotoXY(61,19); cout << "*"<<endl;
					GotoXY(61,20); cout << "*"<<endl;
					GotoXY(61,21); cout << "*"<<endl;
					GotoXY(61,22); cout << "*"<<endl;
					GotoXY(61,23); cout << "*"<<endl;
				}
}


//������� ������� ������� � ������
enum {KONEC, STENA,  PLUS, MOVE};
int Move(Game &g)
{
	int & n = g.gaduka.PCount;
	COORD head = g.gaduka.t[n - 1]; //������
	COORD tail = g.gaduka.t[0]; //�����
	COORD next;
	next.X = head.X + g.dx;
	next.Y = head.Y + g.dy; //�������� ��������� ����� �� �����������
	
    if(next.X < 3 || next.Y < 3 || next.X > 60 || next.Y > 23)//�� �������� �� � �����?
		return STENA;
		
	if(n > 4)
	{
		for(int i = 0; i < n; i++)
			if(next.X == g.gaduka.t[i].X && next.Y == g.gaduka.t[i].Y) //�� ������� �� �� ����?
				return KONEC;
	}
	
	if(next.X == g.jabloko.X && next.Y == g.jabloko.Y)
	{
		COORD*temp = new COORD[ ++n ]; //����� ����� ������� �� 1
		for(int i = 0; i < n; i++)
			temp[i] = g.gaduka.t[i]; //������������
		temp[n - 1] = next; //��������� ����
		delete [] g.gaduka.t;
		g.gaduka.t = temp;
		
		SetConsoleCursorPosition(hConsole,head);
		SetConsoleTextAttribute(hConsole, 0x0a); //����������� ������ ������� ���� 
		printf("*");
		SetConsoleCursorPosition(hConsole,next);
		SetConsoleTextAttribute(hConsole,0x0a);
		printf("%c",1);
		PlusJabloko(g);
		return PLUS;
	}
	
	for(int i = 0; i < n - 1; i++)
		g.gaduka.t[i] = g.gaduka.t[i + 1];
	g.gaduka.t[n - 1] = next;
	SetConsoleCursorPosition(hConsole,tail);//����������� �������
	printf(" ");
	
	SetConsoleCursorPosition(hConsole,head);
	SetConsoleTextAttribute(hConsole, 0x0a);//������ ����� ���� � ������� ����
	printf("*");
	SetConsoleCursorPosition(hConsole,next);
	SetConsoleTextAttribute(hConsole,0x0f); //������ ������ � ����� ���� (������ ����) 
	printf("%c",1);
	
	return MOVE;
}

int intro()
{
        GotoXY(3,10); //�������
	printf("���筠� ������. ��ࠢ����� ���� - ��५�窠��. Esc - ��室 �� ����.");
    GotoXY(15,11);
    printf("�᫨ ᮡ���� 50 ��, � ��� ���� ���ਧ ;)");
    GotoXY(18,15);
    printf("��� �த������� �몭�� �� ������ :D");
	getch();
}

int main()
{

    
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ���������� �������
	intro();
    int key = 0, count = 0;
	bool Pause=false;
	Game g;
	skorostGame(g);
	STENA_2();
	srand(time(0));
	bool pause = false;
	while(key != 27)
	{
		while(!kbhit()) //���� ���� ������
		{
			if(Pause==true)
			{
				Sleep(1); 
				continue;
			}
			
			switch (Move(g))//��������
			{
				
			case PLUS:
				++count;
				g.pause-=1;
				SetColor(LightBlue , Black);
				GotoXY(64,2);cout <<  "Danue:" << endl ;
				GotoXY(64,3); cout << "Jablok:" <<count << endl;
				GotoXY(64,4); cout << "Dlina:" <<g.gaduka.PCount << endl;
				GotoXY(64,5); cout << "Speed:" <<g.pause<< endl;
				GotoXY(64,7); cout << "Uprawlenie:" <<  endl;
				GotoXY(64,8); cout << "Esc:Wuxod" <<  endl;
				GotoXY(64,9); cout << "P:Pause" <<  endl;
				GotoXY(64,10); cout <<"S:Start" <<  endl;
				GotoXY(64,11); cout <<"L:Level" <<  endl;
				GotoXY(64,13);printf("%c",24);cout <<":Wwerx"<<endl;
				GotoXY(64,14);printf("%c",25);cout<<":Wniz"<<endl;
				GotoXY(64,15);printf("%c",27);cout<<":Wlewo"<<endl;
				GotoXY(64,16);printf("%c",26);cout<<":Wprawo"<<endl;
				if (count == 50) 
				{
                    SetColor(White , Black);
                    GotoXY(24,1); cout << "Vy vyigrali! Pozdravlyayu! Vy ne chelovek! xD" << endl; //�� ��������
					getch();
					return(0);
				}
				break;
				
			case STENA:
				
			case KONEC:
				GotoXY(23,1); printf("�� �ந�ࠫ�! ��-�-�!!!\n\n\t\t\t"); //�� ���������, �� �� ��
				getch();
				break;
			}
			
			Sleep(g.pause); //��������
		}
	key = getch();
		
    	if(key=='P'||key=='p')
			Pause=!Pause;
			else if(key=='S'||key=='s')
			ZmejaStart();
		else if(key=='L'||key=='l')
			Level();
		else if(key==0||key==224)
		{
			key=getch();
			
			if(key == 72 && g.nap != DOWN)
			{
				g.nap = UP;
				g.dx = 0;
				g.dy = -1;
			}
			else if(key == 80 && g.nap != UP)
			{
				g.nap = DOWN;
				g.dx = 0;
				g.dy = 1;
			}
			else if(key == 75 && g.nap != RIGHT)
			{
				g.nap = LEFT;
				g.dx = -1;
				g.dy = 0;
			}
			else if(key == 77 && g.nap != LEFT)
			{
				g.nap = RIGHT;
				g.dx = 1;
				g.dy = 0;
			}
		}
	}
}
