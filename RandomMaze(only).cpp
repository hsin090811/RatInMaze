#include <iostream>
#include <time.h>
#include <stdlib.h>
#define STACK_SIZE   25
#define STACK_EMPTY  -1
#define STACK_FULL   -2
#include<conio.h>
#include<windows.h>
#include<ctime>
#define LENGTH 		1000
#define GOAL 		4
#define START 		2



using namespace std;

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput,scrn);
}

class Stack
{
    int data[STACK_SIZE];
    int top;
public:
    Stack();
    int Push(int);
    int Pop();
};
Stack::Stack():top(-1)
{
}
int Stack::Push(int x)
{
    if(top < (STACK_SIZE-1))
    {
        data[++top] = x;
        return 1;
    }
    else
    {
        return STACK_FULL;
    }
}
int Stack::Pop()
{
    if(top != -1){
        return data[top--];


    }
    else
    {
        return STACK_EMPTY;
    }
}


class MazePrint
{
	string road_figure;
	string wall_figure;
	string Start_figure;
	string Goal_figure;
	int x,y;
public:
	MazePrint();
	void CreateRoad(int a,int b);
	void CreateWall(int a,int b);
	void CreateStart(int a,int b);
	void CreateGoal(int a,int b);
};

MazePrint::MazePrint():road_figure("  "),wall_figure("¡½"),Start_figure("¡³"),Goal_figure("¡´"){
}

void MazePrint::CreateRoad(int a,int b){
	x=a;
	y=b;
	gotoxy(x,y);
	cout << road_figure ;
}

void MazePrint::CreateWall(int a,int b){
	x=a;
	y=b;
	gotoxy(x,y);
	cout << wall_figure ;
}

void MazePrint::CreateStart(int a,int b){
	x=a;
	y=b;
	gotoxy(x,y);
	cout << Start_figure ;
}

void MazePrint::CreateGoal(int a,int b){
	x=a;
	y=b;
	gotoxy(x,y);
	cout << Goal_figure ;
}

class Maze{
	int x,y,dir,Record,m,n;
	Stack Mazex;
	Stack Mazey;
	MazePrint MAZE;
protected:	
	int MazeArray[25][25];
public:
	Maze();
	void CreateMaze();
	void StartAndGoal();
	void Print();

};

Maze::Maze():dir(0),Record(0),m(1),n(1){
	for(int i=0; i<STACK_SIZE; i++){
		for(int j=0; j<STACK_SIZE; j++){
			if((i==0)||(j==0)||((i%2)==0)||((j%2)==0))MazeArray[i][j]=1;
			else {
				if((i%2==1)||(j%2==1))MazeArray[i][j]=0;
			}
		}
	}
	for(int i=0; i<STACK_SIZE; i++){
		for(int j=0; j<STACK_SIZE; j++){
			if(MazeArray[i][j]==1)MAZE.CreateWall(2*j,i);
			else MAZE.CreateRoad(2*j,i);
		}
		cout << endl ;
	}
	MAZE.CreateRoad(2*n,m);
	MazeArray[m][n]=START;
	Mazex.Push(n);
	Mazey.Push(m);
}

void Maze::CreateMaze(){
	while(1){
		while(1){
			if(dir==0)dir = (rand()%4)+1;
			if((dir==1)&&(MazeArray[m-2][n]==0)&&((m-2)!=-1)){
				m = m-2 ;
				MAZE.CreateRoad(2*n,m+1);
				MazeArray[m+1][n]=2;
				MazeArray[m][n]=2;
				Mazex.Push(n);
				Mazey.Push(m);
				dir=0;
			}
			else if((dir==2)&&(MazeArray[m][n+2]==0)&&((n+2)!=25)){
				n = n+2 ;
				MAZE.CreateRoad(2*(n-1),m);
				MazeArray[m][n-1]=2;
				MazeArray[m][n]=2;
				Mazex.Push(n);
				Mazey.Push(m);
				dir=0;
			}
			else if((dir==3)&&(MazeArray[m+2][n]==0)&&((m+2)!=25)){
				m = m+2 ;
				MAZE.CreateRoad(2*n,m-1);
				MazeArray[m-1][n]=2;
				MazeArray[m][n]=2;
				Mazex.Push(n);
				Mazey.Push(m);
				dir=0;
			}
			else if((dir==4)&&(MazeArray[m][n-2]==0)&&((n-2)!=-1)){
				n = n-2;
				MAZE.CreateRoad(2*(n+1),m);
				MazeArray[m][n+1]=2;
				MazeArray[m][n]=2;
				Mazex.Push(n);
				Mazey.Push(m);
				dir=0;
			}
			else{
				dir=0;
				Record++;		
			}
			if(Record==100) break;
		}
		if(Record==100){
			if(((m = Mazey.Pop())!=STACK_EMPTY)&&((n = Mazex.Pop())!=STACK_EMPTY)){
			}else{
				int BR=0;
				for(int i=0; i<STACK_SIZE; i++){
					for(int j=0; j<STACK_SIZE; j++){
						if((i%2==1)||(j%2==1)){
							if((MazeArray[i][j]==0)&&((((MazeArray[i+2][j]==2)&&(MazeArray[i-2][j]==2))||((MazeArray[i][j+2]==2)&&(MazeArray[i][j-2]==2)))||
													(((MazeArray[i+2][j]==2)&&(MazeArray[i][j-2]==2))||((MazeArray[i][j+2]==2)&&(MazeArray[i-2][j]==2)))||
													(((MazeArray[i+2][j]==2)&&(MazeArray[i][j+2]==2))||((MazeArray[i-2][j]==2)&&(MazeArray[i][j-2]==2))))){
								if((i%2==1)||(j%2==1)){
									n=j;
									m=i;
									MazeArray[m][n]=2;
									while(1){
										dir = rand()%4+1;
										if((dir==1)&&(m-1!=0)&&(MazeArray[m-2][n]==2)){
											MAZE.CreateRoad(2*n,m-1);
											MazeArray[m-1][n]=2;
											break;
										}
										else if((dir==2)&&(n+1!=24)&&(MazeArray[m][n+2]==2)){
											MAZE.CreateRoad(2*(n+1),m);
											MazeArray[m][n+1]=2;
											break;
										}
										else if((dir==2)&&(n-1!=0)&&(MazeArray[m][n-2]==2)){
											MAZE.CreateRoad(2*(n-1),m);
											MazeArray[m][n-1]=2;
											break;
										}
										else if((dir==2)&&(m+1!=24)&&(MazeArray[m+2][n]==2)){
											MAZE.CreateRoad(2*n,m+1);
											MazeArray[m+1][n]=2;
											break;
										}
									}	
									Mazex.Push(n);
									Mazey.Push(m);
									MazeArray[m][n]=2;
									BR++;
									break;
								}
							}
						}		
					}
					if(BR==1) break;
				}
			}
			Record=0;
		}
		int B=0;
		for(int i=0; i<STACK_SIZE; i++){
			for(int j=0; j<STACK_SIZE; j++){
				if(MazeArray[i][j]!=0)B++;
			}
		}
		if(B==625)break;
	}
}

void Maze::StartAndGoal(){
	MazeArray[1][1]=START;
	MAZE.CreateStart(2,1);
	MazeArray[23][23]=GOAL;
	MAZE.CreateGoal(46,23);
}

void Maze::Print(){
	gotoxy(0,27);
	for(int i=0; i<STACK_SIZE; i++){
		for(int j=0; j<STACK_SIZE; j++){
			cout<<MazeArray[i][j]<<" ";
		}
		cout << endl ;
	}
}

int main()
{
    
	srand(time(NULL));
	Maze maze;
    maze.CreateMaze();
    maze.StartAndGoal();
    maze.Print();
   	gotoxy(51,27);
    system("pause");
    return 0;
}

