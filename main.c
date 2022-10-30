#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "console.c"


#define NORM "\033[0m"
//Regular background
#define BLKB "\033[40m"
#define REDB "\033[41m"
#define GRNB "\033[42m"
#define YELB "\033[43m"
#define BLUB "\033[44m"
#define MAGB "\033[45m"
#define CYNB "\033[46m"
#define WHTB "\033[47m"


#define wl 'X'
#define ai ' '
#define wi 'W'
//#define pr '+'
char pr[20]="\033[45m+\033[0m";


int size = 10;

char mapO[10][10] =
{
	{wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl},
	{wl ,' ',' ',' ',wl ,' ',wl ,' ',wi ,wl},
	{wl ,' ',wl ,' ',wl ,' ',' ',' ',' ',wl},
	{wl ,' ',wl ,' ',wl ,' ',wl ,' ',' ',wl},
	{wl ,' ',wl ,' ',' ',' ',wl ,wl ,' ',wl},
	{wl ,' ',' ',wl ,' ',' ',wl ,' ',' ',wl},
	{wl ,wl ,' ',wl ,wl ,wl ,wl ,' ',wl ,wl},
	{wl ,' ',' ',wl ,' ',' ',' ',' ',' ',wl},
	{wl ,' ',' ',' ',' ',' ',' ',' ',' ',wl},
	{wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl},
};
char map[10][10] =
{
	{wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl},
	{wl ,' ',' ',' ',wl ,' ',wl ,' ',wi ,wl},
	{wl ,' ',wl ,' ',wl ,' ',' ',' ',' ',wl},
	{wl ,' ',wl ,' ',wl ,' ',wl ,' ',' ',wl},
	{wl ,' ',wl ,' ',' ',' ',wl ,wl ,' ',wl},
	{wl ,' ',' ',wl ,' ',' ',wl ,' ',' ',wl},
	{wl ,wl ,' ',wl ,wl ,wl ,wl ,' ',wl ,wl},
	{wl ,' ',' ',wl ,' ',' ',' ',' ',' ',wl},
	{wl ,' ',' ',' ',' ',' ',' ',' ',' ',wl},
	{wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl ,wl},
};


//il primo [] = percorso 
//il secondo [] = segmenti 
//il terzo [0] = x [1] = y
//path[?][0][0] = lunghezza del percorso
//path[?][0][1] = è un percorso vincente
int path[2000][20][2]={{{1,0},{1,8}}};
int paths = 1;

main(){
	system("color 0F");
	getch();
	printMap();

	createPaths();
	
	printMapO();
	printPath(getWinner());
	//disegnaPaths();
	//scriviPaths();
	getch();
 printf("\n\n");
}
void createPaths()
{
	int r=0;
	while (r==0)
	{
		r = createNewPath();
		printMap();
		Sleep(100);
	}
}
int getWinner()
{
	int maxSeg =0;
	int maxPath=0;
	int p;
	for (p=0;p<paths;p++)
	{
		int segNum = path[p][0][0];
		if (segNum>maxSeg && path[p][0][1])
		{
			maxSeg = segNum;
			maxPath = p;
		}
	}
	return maxPath;
}

int createNewPath()
{
	int ret=0;
	int newPath[2000][20][2];
	int newPaths=0;
	int p;
	for (p=0; p<paths;p++)
	{
		int move=0;
		
		int segNum = path[p][0][0];
		int X=path[p][segNum][0];
		int Y=path[p][segNum][1];
		//check up
		if (!isWalled(X,Y-1))
		{

			if(isArrived(X,Y-1))
			{
				path[p][0][1] = 1;
				ret = 1;
			}
			//inserisco in newpath path
			int s;
			newPath[newPaths][0][0]=segNum+1;
			for (s=0;s<segNum;s++)
			{
				newPath[newPaths][s+1][0]=path[p][s+1][0];
				newPath[newPaths][s+1][1]=path[p][s+1][1];
			}
			//aggiungo un segmento al percorso
			newPath[newPaths][newPath[newPaths][0][0]][0] = X;   //al nuovo segmento metto la stessa x del segmento precente
			newPath[newPaths][newPath[newPaths][0][0]][1] = Y-1; //al nuovo segmento deincremento la vecchia y
			newPaths++;//riferisco di aver aggiunto un percorso
		}
		//checkDown
		if (!isWalled(X,Y+1))
		{

			if(isArrived(X,Y+1))
			{
				path[p][0][1] = 1;
				ret = 1;
			}
			int s;
			newPath[newPaths][0][0]=segNum+1;
			for (s=0;s<segNum;s++)
			{
				newPath[newPaths][s+1][0]=path[p][s+1][0];
				newPath[newPaths][s+1][1]=path[p][s+1][1];
			}
			//aggiungo un segmento al percorso
		
			newPath[newPaths][newPath[newPaths][0][0]][0] = X;   //al nuovo segmento metto la stessa x del segmento precente
			newPath[newPaths][newPath[newPaths][0][0]][1] = Y+1; //al nuovo segmento incremento la vecchia y
			newPaths++;//riferisco di aver aggiunto un percorso
		}
		//check right
		if (!isWalled(X+1,Y))
		{

			if(isArrived(X+1,Y))
			{
				path[p][0][1] = 1;
				ret = 1;
			}
			int s;
			newPath[newPaths][0][0]=segNum+1;
			for (s=0;s<segNum;s++)
			{
				newPath[newPaths][s+1][0]=path[p][s+1][0];
				newPath[newPaths][s+1][1]=path[p][s+1][1];
			}
			//aggiungo un segmento al percorso
			
			newPath[newPaths][newPath[newPaths][0][0]][0] = X+1;   //al nuovo segmento incremento la x del segmento precente
			newPath[newPaths][newPath[newPaths][0][0]][1] = Y; //al nuovo segmento lascio la vecchia y
			newPaths++;//riferisco di aver aggiunto un percorso
		}
		//check left
		if (!isWalled(X-1,Y))
		{
			
			if(isArrived(X-1,Y))
			{
				path[p][0][1] = 1;
				ret = 1;
			}
			int s;
			newPath[newPaths][0][0]=segNum+1;
			for (s=0;s<segNum;s++)
			{
				newPath[newPaths][s+1][0]=path[p][s+1][0];
				newPath[newPaths][s+1][1]=path[p][s+1][1];
			}
			//aggiungo un segmento al percorso
			
			newPath[newPaths][newPath[newPaths][0][0]][0] = X-1;   //al nuovo segmento deincremento la x del segmento precente
			newPath[newPaths][newPath[newPaths][0][0]][1] = Y; //al nuovo segmento lascio la vecchia y
			newPaths++;//riferisco di aver aggiunto un percorso
		}

	}

	//inserisco newPath in path;
	for (p=0;p<newPaths;p++)
	{
		int segNum = newPath[p][0][0];
		int s;
		path[p][0][0]=newPath[p][0][0];
		for (s=0;s<segNum;s++)
		{
			path[p][s+1][0]=newPath[p][s+1][0];
			path[p][s+1][1]=newPath[p][s+1][1];
			paths = newPaths;
		}
		map[path[p][segNum-1][1]][path[p][segNum-1][0]] = wl;//metto un muro dove sono gia passato
		//map[3][1] = wl;
	}
	return ret;
}

void printPath(int pathNum)
{
	int segNum = path[pathNum][0][0];
	int i;
	for (i=0;i<segNum;i++)
	{
		gotoxy(path[pathNum][i+1][0]*4,path[pathNum][i+1][1]*2);
		printf("%s",pr);
		Sleep(100);
	}
}
int isWalled(int X,int Y)
{
	if (map[Y][X] == wl)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int isArrived(int X,int Y)
{
	if (map[Y][X] == wi)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void scriviPaths()
{
	gotoxy(0,size*2+1);
	printf("percorsi %d\n",paths);
	int p;
	for(p=0;p<paths;p++)
	{
		printf("percorso %d\n",p);
		printf("numero segmenti= %d\n",path[p][0][0]);
		int s;
		for(s=0;s<path[p][0][0];s++)
		{
			printf("segmento %d: ",s);
			printf("x=%d ",path[p][s+1][0]);
			printf("y=%d\n",path[p][s+1][1]);
		}
	}
}
void disegnaPaths()
{
	int p;
	for(p=0;p<paths;p++)
	{
		//if (path[p][0][1])
		//{
			clrScr();
			printMapO();
			int s;
			for(s=0;s<path[p][0][0];s++)
			{
				int X = path[p][s+1][0];
				int Y = path[p][s+1][1];
				gotoxy(X*4,Y*2);
				printf("%s",pr);
				Sleep(10);
			}
		//}

	}
}
void printMap()
{
	int x;
	int y;
	for(x=0;x<size;x++)
	{
		for(y=0;y<size;y++)
		{
			gotoxy(x*4,y*2);
			printf("%c",map[y][x]);
		}
	}
}
void printMapO()
{
	int x;
	int y;
	for(x=0;x<size;x++)
	{
		for(y=0;y<size;y++)
		{
			gotoxy(x*4,y*2);
			printf("%c",mapO[y][x]);
		}
	}
}

