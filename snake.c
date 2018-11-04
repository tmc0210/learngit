//头文件 

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include<string.h>
#include<malloc.h>

//函数声明 
void gotoxy(int x, int y);
void HideCursor(); 
void gamestart(); 
int gameover();
void move();
void movebody(int a,int b);
void printfmap();
void creatsnake();
void creatapple();
void creatpoison();
void eatapple();
void eatpoison();
int judge();
void clear();

//全局变量 
int direct=1;
int n;
int speed=100;
int score=0;

typedef struct Snake
{
 int x;
 int y;
 struct Snake *next;
}snake;

struct
{
	int x;
	int y;
}apple;

struct
{
	int x;
	int y;
}poison;

snake*head,*tail;

//gotoxy 
void gotoxy(int x,int y)
{
	COORD pos;
	HANDLE hOutput;
    pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//隐藏光标
void HideCursor()
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//主函数 
int main()
{
	
	HideCursor();
	mainlable:
	system("CLS");	
	n=4;
	direct=1;
	printfmap();
	creatsnake();
	creatapple();
	creatpoison();
	
	
	do
		move();
	while(judge()==1);
    if (gameover()==0)
	    {
	    	clear();
		    goto mainlable;
	    }
	return 0;
}

//打印地图 
void printfmap()
{
	system("CLS");
	int i,j;
   for(i=0;i<=62;i=i+2)
	{
		gotoxy(i,0);
	    printf("■") ;
		gotoxy(i,29);
	    printf("■") ;
	 } 
	 
	for(i=0;i<=29;i++)
	{
		gotoxy(0,i);
	    printf("■") ;
		gotoxy(62,i);
	    printf("■") ;
	}
}

//游戏开始 
void gamestart()
{
	
} 

//创建蛇 
void creatsnake()
{
	head=(snake*)malloc(sizeof(snake));
	head->x=28;
	head->y=15;
	tail=(snake*)malloc(sizeof(snake));
	snake*p1=(snake*)malloc(sizeof(snake));
	snake*p2=(snake*)malloc(sizeof(snake));
	snake*p3=(snake*)malloc(sizeof(snake));
	p1->x=28;
	p1->y=16;
	p2->x=28;
	p2->y=17;
	p3->x=28;
	p3->y=18;
	head->next=p1;
	p1->next=p2;
	p2->next=p3;
	p3->next=tail;
	tail->next=NULL;	
}

//生成苹果
void creatapple()
{
	srand((int)time(NULL));
	lable:
	apple.y=rand()%27+1;
	apple.x=rand()%58+2; 
	if (apple.x%2!=0)
	{
		apple.x=apple.x+1;
	}
	
	
	snake*p=head;
	while (1)
	{
		if(p->next==NULL)break;
		if(apple.x==p->x&&apple.y==p->y)
		{
			goto lable;
		}
		p=p->next;
	}
	gotoxy(apple.x,apple.y);
	printf("⊙");
	
}

//生成毒草
void creatpoison()
{
	srand((int)time(NULL));
	lable:
	poison.y=rand()%27+1;
	poison.x=rand()%58+2; 
	if (poison.x%2!=0)
	{
		poison.x=poison.x+1;
	}
	
	
	snake*p=head;
	while (1)
	{
		if(p->next==NULL)break;
		if((poison.x==p->x&&poison.y==p->y)||(poison.x==apple.x&&poison.y==apple.y))
		{
			goto lable;
		}
		p=p->next;
	}
	gotoxy(poison.x,poison.y);
	printf("○");
} 

//蛇的移动 1
void move()
{
	int ch; 
	int a=head->x,b=head->y;
	snake*p=head;
	while (1)
	{
		if(p->next==NULL)break;
		gotoxy(p->x,p->y);
		printf(" ");
		p=p->next;
	}
	if(kbhit())
	 {
	 	ch = getch();      
     } 
     switch(ch)
	  { 
      case 'W':   
      if(direct!=3) 
      direct=1;
      break;
      case 'A':   
      if(direct!=4) 
      direct=2;
      break;
      case 'S':   
      if(direct!=1) 
      direct=3;
      break;
      case 'D':   
      if(direct!=2) 
      direct=4;
      break;  
      case 'P':
      getch();
      break;
      }
    switch(direct)
    {
    	case 1:
    		head->y-=1;
			movebody(a,b);
			break;
    	case 2:
    		head->x-=2;
			movebody(a,b);
			break;
		case 3:
			head->y+=1;
			movebody(a,b);
			break;
		case 4:	
		    head->x+=2;
			movebody(a,b);
			break;
    		
	}
	p=head;
	while(1)
	{
		if (p->next==NULL)break;
		gotoxy(p->x, p->y);
		printf("■");
		p=p->next;
	}
	p=head;
	gotoxy(0, 28);	
	Sleep(100);
    eatapple();
    eatpoison();
    gotoxy(0,0);
	printf("■") ;
}

//蛇的移动 2
 void movebody(int a,int b)
{
	snake*p=head->next;
	int a1,b1,a2,b2;
	a1=p->x;
	b1=p->y;
	while(1)
	{
		if (p->next->next == NULL) break;
		a2=p->next->x;
		b2=p->next->y;
		p->next->x=a1;
		p->next->y=b1;
		a1=a2;
		b1=b2; 
		p=p->next;
	}
	p=head->next; 
	{
		p->x = a;
		p->y = b;
	}
	
 } 

//吃苹果 
void eatapple()
{
	if(head->x==apple.x&&head->y==apple.y)
	{
		creatapple();
		snake*add=(snake*)malloc(sizeof(snake));
		snake*p;
		p=head;
		while (1)
		{
			if(p->next->next==NULL)break;
			p=p->next;
		}
		p->next=add;
		add->next=tail;
		n=n+1;
	}	
}

//吃毒草 
void eatpoison()
{
	if(head->x==poison.x&&head->y==poison.y)
	{
		creatpoison();
		snake*p;
		p=head;
		while (1)
		{
			if(p->next->next->next==NULL)break;
			p=p->next;
		}
	    gotoxy(p->next->x,p->next->y);
	    printf(" ");
	    p->next=tail;
	    n=n-1;
	}
}

//死亡判定
int judge() 
{
	if(n<=2)
	{
		return 0;
	} 
	if(head->x==0||head->x==62||head->y==0||head->y==29)
	{
		return 0;
	}
	snake*p =head->next;
	while(1)
	{
		if(p->next== NULL)break;
		if(head->x==p->x&&head->y==p->y)
		{
			return 0;
		}
		p=p->next;
	}
	return 1; 

}

//GAMEOVER
int gameover()
{
	Sleep(200);
	char getkey;
	system("cls");
	gotoxy(48, 12);
	printf("GAME   OVER");
	gotoxy(43, 15);
	printf("DO YOU WANT TO TRY AGAIN?");
	gotoxy(43, 18);
	printf("Q:YES                E:NO");
        lable:
	    if(kbhit())
	 {
	 	getkey = getch();      
     } 
     switch(getkey)
	  { 
      case 'Q':
	  return 0;   
      break;
      case 'E':   
      return 1;
	  break;
	  default:
	  goto lable;
      }	
}

//clear
void clear()
{
	free(head);
	free(tail);
}

