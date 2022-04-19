#include "stdio.h"
//#include <stdlib.h>
#include "windows.h"
#include <conio.h>
#include "time.h"

#define NROW 50
#define NCOLUMN 30
#define UP 72
#define DOWN 80
#define LEFT 75
//#define RU 1
//#define RD 2
//#define LU 3
//#define LD 4
#define RIGHT 77
#define COLOR_OF_FINISH 118
#define COLOR_OF_YOUR_SNAKE 3
#define COLOR_OF_COM_SNAKE 5
#define COLOR_EMPTY 1
#define SPEED_VOOM 60
#define BEGIN_OF_DOT 5

struct voom {
  int row,col;
} voom1[20],voom11[20];

void gotoxy(short X,short Y);
void set_direction(struct voom s[20],char dir);
//void set_direction2(struct voom p,int di);

int X,Y,i,RU=1,RD=2,LU=3,LD=4,dir2=4,voom_length=7,count=0;
char dir1='\n',dir11='\n',keypress;

int main(){
	int r,c;
	struct voom dot;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	dot.row=BEGIN_OF_DOT;
	dot.col=BEGIN_OF_DOT;
	for(i=0;i<=voom_length;i++)
		voom1[i].row=NROW-1;
	for(i=0;i<=voom_length;i++)
		voom11[i].row=1;
	for(i=0;i<=NCOLUMN;i++){
		gotoxy(i,0);
		SetConsoleTextAttribute(hConsole,6);
		printf(".");
		gotoxy(i,NROW);
		SetConsoleTextAttribute(hConsole,6);
		printf(".");
	}
	for(i=0;i<=NROW;i++){
		gotoxy(0,i);
		SetConsoleTextAttribute(hConsole,6);
		printf(".");
		gotoxy(NCOLUMN,i);
		SetConsoleTextAttribute(hConsole,6);
		printf(".");
	}
	do{
		gotoxy(30,6);
		SetConsoleTextAttribute(hConsole,COLOR_EMPTY);
		printf("                                  ");
		gotoxy(30,9);
		SetConsoleTextAttribute(hConsole,COLOR_EMPTY);
		printf("                                  ");
		do{
			if (kbhit()){
				keypress=(char)getch();
				if((keypress==RIGHT)||(keypress==LEFT))
		    		dir1 = keypress;
				else if((keypress=='a')||(keypress=='d'))
					dir11 = keypress;
			}if(dir1!='\n' || dir11!='\n'){
				if(count==3){
					for(i=0;i<=voom_length;i++){
						gotoxy(voom1[i].col,voom1[i].row);
						printf(" ");
						gotoxy(voom11[i].col,voom11[i].row);
						printf(" ");
				
					}
					for(i=0;i<=voom_length;i++)
						voom1[i].row=voom1[i].row-1;
					for(i=0;i<=voom_length;i++)
						voom11[i].row=voom11[i].row+1;
	    			for (i=0;i<=voom_length;i++){
	    				gotoxy(voom1[i].col,voom1[i].row);
						SetConsoleTextAttribute(hConsole,COLOR_OF_YOUR_SNAKE);
						printf("_");
					}
	    			for (i=0;i<=voom_length;i++){
	    				gotoxy(voom11[i].col,voom11[i].row);
						SetConsoleTextAttribute(hConsole,COLOR_OF_COM_SNAKE);
						printf("_");
					}
					count=0;
				}
				if(voom1[0].col==1 && dir1==LEFT){
					;
				}
				else if(voom1[voom_length].col==(NCOLUMN-1) && dir1==RIGHT){
					;
				}
				else{
					if(dir1==RIGHT){
    					gotoxy(voom1[0].col,voom1[0].row);
	    				printf(" ");
						for (i=1;i<=voom_length;i++)
	    					voom1[i-1]=voom1[i];
					}else{
	    				gotoxy(voom1[voom_length].col,voom1[voom_length].row);
	    				printf(" ");
						for (i=0;i<voom_length;i++)
	   						voom1[voom_length-i]=voom1[voom_length-i-1];
					}
					set_direction(voom1,dir1);
	    			for (i=0;i<=voom_length;i++){
	    				gotoxy(voom1[i].col,voom1[i].row);
						SetConsoleTextAttribute(hConsole,COLOR_OF_YOUR_SNAKE);
						printf("_");
					}
				}
				if(voom11[0].col==1 && dir11=='a'){
					;
				}
				else if(voom11[voom_length].col==(NCOLUMN-1) && dir11=='d'){
					;
				}
				else{
					if(dir11=='d'){
    					gotoxy(voom11[0].col,voom11[0].row);
	    				printf(" ");
						for (i=1;i<=voom_length;i++)
	    					voom11[i-1]=voom11[i];
					}else{
	    				gotoxy(voom11[voom_length].col,voom11[voom_length].row);
	    				printf(" ");
						for (i=0;i<voom_length;i++)
	   						voom11[voom_length-i]=voom11[voom_length-i-1];
					}
					set_direction(voom11,dir11);
	    			for (i=0;i<=voom_length;i++){
	    				gotoxy(voom11[i].col,voom11[i].row);
						SetConsoleTextAttribute(hConsole,COLOR_OF_COM_SNAKE);
						printf("_");
					}
				}
				//if(dir2==RU && dot.row-1==0 && dot.col+1==NCOLUMN)
					//dir2=LD;
				//else if(dir2==LU && dot.row-1==0 && dot.col-1==0)
					//dir2=RD;
				if(dot.row==voom1[0].row)
					keypress='h';
				else if(dot.row==voom11[0].row)
					keypress='h';
				//else if(dir2==RU && dot.row-1==0)
					//dir2=RD;
				else if(dir2==RU && dot.col+1==NCOLUMN)
					dir2=LU;
				else if(dir2==RD && dot.col+1==NCOLUMN)
					dir2=LD;
				//else if(dir2==LU && dot.row-1==0)
					//dir2=LD;
				else if(dir2==LU && dot.col-1==0)
					dir2=RU;
				else if(dir2==LD && dot.col-1==0)
					dir2=RD;

				for(i=0;i<=voom_length;i++){
					if(dot.row+1==voom1[0].row && (dot.col+1==voom1[i].col || dot.col-1==voom1[i].col)){//in khat ehtemalan dar || ,... moshkel
						count=count+1;
						if(dir2==RD){
							dir2=RU;
						}
						else if(dir2==LD){
							dir2=LU;
						}
					}
				}
				for(i=0;i<=voom_length;i++){
					if(dot.row-1==voom11[0].row && (dot.col+1==voom11[i].col || dot.col-1==voom11[i].col)){//in khat ehtemalan dar || ,... moshkel
						if(dir2==RU){
							dir2=RD;
						}
						else if(dir2==LU){
							dir2=LD;
						}
					}
				}
				gotoxy(dot.col,dot.row);
				printf(" ");
				//set_direction2(dot,dir2);
				r=dot.row;
				c=dot.col;
				if(dir2==RU){
					dot.row=r-1;
					dot.col=c+1;
				}
				else if(dir2==RD){
					dot.row=(r+1);
					dot.col=(c+1);
				}
				else if(dir2==LU){
					dot.row=(r-1);
					dot.col=(c-1);
				}
				else if(dir2==LD){
					dot.row=(r+1);
					dot.col=(c-1);
				}
				gotoxy(dot.col,dot.row);
				SetConsoleTextAttribute(hConsole,7);
				printf("o");
				if(dot.row==voom1[0].row)
					keypress='h';
				if(dot.row==voom11[0].row)
					keypress='h';
			}
			Sleep(SPEED_VOOM);
		} while (keypress!='h');
		gotoxy(30,6);
		SetConsoleTextAttribute(hConsole,COLOR_OF_FINISH);
		printf("G A M E   O V E R");
		gotoxy(30,9); printf("Resume Game (y/n)? ");
		do{
			keypress=getch();
		}while((keypress!='y')&&(keypress!='n'));
	}while (keypress=='y');
	return 0;
}

void gotoxy(short X,short Y){
	COORD coord;
	coord.X=X;
	coord.Y=Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void set_direction(struct voom s[20],char dir){
  switch(dir){
    case(RIGHT): s[voom_length].row=s[voom_length].row;
                     s[voom_length].col=s[voom_length].col+1;
                     break;
    case(LEFT) : s[0].row=s[0].row;
                     s[0].col=s[0].col-1;
					 break;
    case('d'): s[voom_length].row=s[voom_length].row;
                     s[voom_length].col=s[voom_length].col+1;
                     break;
    case('a') : s[0].row=s[0].row;
                     s[0].col=s[0].col-1;
  }
}

/*void set_direction2(struct voom p,int di){
	int r,c;
	r=p.row;
	c=p.col;
  switch(di){
    case(1): p.row=r-1;
				p.col=c+1;
				break;
	case(2): p.row=(r+1);
				p.col=(c+1);
				break;
	case(3): p.row=r-1;
				p.col=c-1;
				break;
	case(4): p.row=r+1;
				p.col=c-1;
				break;
  }
}*/

