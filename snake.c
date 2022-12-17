#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define ESC 27

void menu(); void howPlay();
void generateMap(int b, int k, char map[b][k], char p, int y, int x, char tail, int ytail[], int xtail[], int nTails);
void displayMap(int b, int k, char map[b][k], int score);
void moveUp(int *y, int x, int ytail[], int xtail[], char *p, int nTails);
void moveDown(int *y, int x, int ytail[], int xtail[], char *p, int nTails);
void moveLeft(int y, int *x, int xtail[], int ytail[], char *p, int nTails);
void moveRight(int y, int *x, int xtail[], int ytail[], char *p, int nTails);
void followTails(int ytail[], int xtail[]);
void resetGame(int *nTails, int *y, int *x, int *score, char *player);
char food='o';
int xFood;
int yFood;

int main(int argc, char *argv[]) {
	srand(time(NULL));
	char pil;
	int baris=10, kolom=20;
	char map[baris][kolom];
	char player='^';
	char tail='*';
	int nTails=0;
	int ytail[10], xtail[10];
	int y=8,x=10;
	char move;
	int score=0;

	xFood= rand() % 18+1;
	yFood=rand() % 8+1;
	system("color 3");
	do{
		menu:
		system("cls");
		menu();
		printf("\n>>> "); pil=getch();
		switch (pil){
		case '1':
				do{
					system("cls");
					generateMap(baris, kolom, map,player,y,x,tail,ytail,xtail, nTails);
					displayMap(baris, kolom, map, score);	
						
					move = getch();
					switch(move){
						case 'w':
							moveUp(&y,x,ytail,xtail,&player, nTails);
						break;

						case 's':		
							moveDown(&y,x,ytail,xtail,&player, nTails);
						break;

						case 'a':
							moveLeft(y, &x, xtail, ytail,&player, nTails);	
						break;

						case 'd':
							moveRight(y, &x, xtail,ytail,&player, nTails);
						break;

						case 27:
							resetGame(&nTails, &y,&x,&score,&player);
							goto menu;
						break;
					}
					if(y==yFood && x==xFood){
						xFood= rand() % 18+1;
						yFood=rand() % 8+1;
						score++;
						nTails++;
					}
					if(map[y][x]=='*'){
							Sleep(80);
							goto exit;
						}else if(map[y][x]=='#'){
							Sleep(80);
							goto exit;
						}
					
				}while(score<10);
				if(score>=10){
					system("cls");
					printf("\n\n\tCongrats !!!");
					printf("\n\tYour score is: %d", score);
					getch();
				}else{
					exit:
						system("cls");
						printf("\n\n\tYOU DIED !");
						printf("\n\n\t[!] GAME OVER [!]\n");
						getch();
				}
			resetGame(&nTails, &y,&x,&score,&player);
			xFood= rand() % 18+1;
			yFood=rand() % 8+1;
		break;

		case '2':
			howPlay();
			getch();
		break;

		case 27:
			printf("\n\tThanks for playing! ^_^");
			printf("\n\tQuitting program...");
			printf("\n\n\t\tMade by Riksi Purnama");
		break;

		default:
			printf("\n\tMenu doesn't exist!");
			getch();
			break;
		}
	}while(pil!=27);
	getch();
	return 0;
}
void menu(){
	printf("\n\t\t--===[ WELCOME TO SNAKE ]===--\n");
	printf("\n\t[1] Let's Play!");
	printf("\n\t[2] How to Play?");
	printf("\n\t[ESC] Exit");
}

void howPlay(){
	system("cls");
	printf("\n\t\t--=== How To Play ===--\n");
	printf("\n\tW   : Move Up");
	printf("\n\tS   : Move Down");
	printf("\n\tA   : Move Left");
	printf("\n\tD   : Move Right");
	printf("\n\tESC : Exit");
}
void generateMap(int b, int k, char map[b][k], char p, int y, int x, char tail, int ytail[], int xtail[], int nTails){
	int i,j;
	for(i=0;i<b;i++){
		for(j=0;j<k;j++){
			if(i==0 || i==b-1){
				if(i==0 && j==0){
					map[i][j]=(201);
				}else if(i==0  && j==k-1){
					map[i][j]=(187);
				}else if(i==b-1 && j==0){
					map[i][j]=(200);
				}else if(i==b-1 && j==k-1){
					map[i][j]=(188);
				}else map[i][j]=(205);
			}else if(j==0 || j==k-1){
				map[i][j]=(186);
			}else if(i==4 && (j%4==0 || j==5 || j ==9 || j==11 || j==15)){
				map[i][j]='#';
			}else if(i==5 && (j%4==0 || j==5 || j ==9 || j==11 || j==15)){
				map[i][j]='#';
			}else map[i][j]=' ';
		}
	}
	map[y][x]=p;
	if(nTails!=0){
		for(i=0;i<=nTails;i++){
			map[ytail[i]][xtail[i]]=tail;
		}
	}
	map[yFood][xFood]=food;
}
void displayMap(int b, int k, char map[b][k], int score){
	int i,j;
	for(i=0;i<b;i++){
		for(j=0;j<k;j++){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
	
	printf("\nScore: %d", score);
	printf("\nPress ESC to Exit");
	if(score==10){
		printf("\n\nCongrats");
		getch();
	}
}

void moveUp(int *y, int x, int ytail[],int xtail[], char *p, int nTails){
	if(*y>1 && nTails==0){
		*p='^';	
		ytail[0]=*y;
		xtail[0]=x;
		*y=*y-1;
		followTails(ytail,xtail);
	}else if(*y>1 && (*y)-1!=ytail[0]){
		*p='^';	
		ytail[0]=*y;
		xtail[0]=x;
		*y=*y-1;
		followTails(ytail,xtail);
	}
}
void moveDown(int *y, int x, int ytail[],int xtail[], char *p,int nTails){
	if(*y<8 && nTails==0){
		*p='v';
		ytail[0]=*y;
		xtail[0]=x;
		*y=*y+1;
		followTails(ytail,xtail);
	}else if(*y<8 && (*y)+1!=ytail[0]){
		*p='v';
		ytail[0]=*y;
		xtail[0]=x;
		*y=*y+1;
		followTails(ytail,xtail);
	}
}
void moveLeft(int y, int *x, int xtail[], int ytail[], char *p,int nTails){
	if(*x>1 && nTails==0){
		*p='<';
		ytail[0]=y;
		xtail[0]=*x;
		*x=*x-1;
		followTails(ytail,xtail);
		
	}else if(*x>1 && *x-1!=xtail[0]){
		*p='<';
		ytail[0]=y;
		xtail[0]=*x;
		*x=*x-1;
		followTails(ytail,xtail);
	}
}
void moveRight(int y, int *x, int xtail[], int ytail[], char *p,int nTails){
	if(*x<18 && nTails==0){
		*p='>';
		ytail[0]=y;
		xtail[0]=*x;
		*x=*x+1;
		followTails(ytail,xtail);
	}else if(*x<18 && *x+1!=xtail[0]){
		*p='>';
		ytail[0]=y;
		xtail[0]=*x;
		*x=*x+1;
		followTails(ytail,xtail);
	}
}

void followTails(int ytail[], int xtail[]){
	int i;
	for(i=9;i>0;i--){
		ytail[i]=ytail[i-1];
		xtail[i]=xtail[i-1];
	}
}
void resetGame(int *nTails, int *y, int *x, int *score, char *player){
	*nTails=0;
	*y=8;
	*x=10;
	*score=0;
	*player='^';
}
