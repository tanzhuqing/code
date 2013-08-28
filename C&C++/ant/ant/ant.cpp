// ant.cpp : 定义控制台应用程序的入口点。
//




#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "dos.h"
#include "stdlib.h"
#include "dos.h"
#include "process.h"
#include "ctype.h"
#include "math.h"

void WorldInitial(void);
void BlockInitial(void);
void CreatBlock(void);
void SaveBlock(void);
void LoadBlock(void);
void HomeFoodInitial(void);
void AntInitial(void);
void WorldChange(void);
void AntMove(void);
void AntOneStep(void);
void DealKey(char key);
void ClearSmellDisp(void);
void DispSmell(int type);
int AntNextDir(int xxx,int yyy,int ddir);
int GetMaxSmell(int type,int xxx,int yyy,int ddir);
int IsTrace(int xxx,int yyy);
int MaxLocation(int num1,int num2,int num3);
int CanGo(int xxx,int yyy,int ddir);
int JudgeCanGo(int xxx,int yyy);
int TurnLeft(int ddir);
int TurnRight(int ddir);
int TurnBack(int ddir);

int MainTimer(void);
char WaitForKey(int secnum);
void DispPlayTime(void);
int TimeUse(void);
void HideCur(void);
void ResetCur(void);

/* ---------------  */
struct HomeStruct
{
    int xxx,yyy;
    int amount;
    int TargetFood;
}home;

struct FoodStruct
{
    int xxx,yyy;
    int amount; 
}food;

struct AntStruct
{
    int xxx,yyy;
    int dir;
    int speed;
    int SpeedTimer;
    int food;
    int SmellAmount[2];
    int tracex[TRACE_REMEMBER];
    int tracey[TRACE_REMEMBER];
    int TracePtr;
    int IQ;
}ant[MAX_ANT];
int AntNow;
int timer10ms;
struct time starttime,endtime;
int Smell[2][MAXX+1][MAXY+1];
int block[MAXX+1][MAXY+1];
int SmellGoneTimer;
int SmellDispFlag;
int CanFindFood;
int HardtoFindPath;

/* ----- Main -------- */
void main(void)
{
    char KeyPress;
    int tu;
    
    clrscr();
    HideCur();
    WorldInitial();
    do
    {
        timer10ms = MainTimer();
        if(timer10ms) AntMove();
        if(timer10ms) WorldChange();
        tu = TimeUse();
        if(tu>=60&&!CanFindFood)
        {
            gotoxy(1,MAXY+1);
            printf("Can not find food, maybe a block world.");
            WaitForKey(10);
            WorldInitial(); 
        }
        if(tu>=180&&home.amount<100&&!HardtoFindPath)
        {
            gotoxy(1,MAXY+1);
            printf("God! it is so difficult to find a path.");
            if(WaitForKey(10)==0x0d) WorldInitial();
            else
        	{
                HardtoFindPath = 1;
                gotoxy(1,MAXY+1);
                printf("                                       ");  	
        	}
        }
        if(home.amount>=home.TargetFood)
        {
            gettime(&endtime);
            KeyPress = WaitForKey(60);
            DispPlayTime();
            WaitForKey(10);
            WorldInitial();
        }
        else if(kbhit())
        {
            KeyPress = getch();
            DealKey(KeyPress);
        }
        else KeyPress = NULL;
    }
    while(KeyPress!=ESC);
    gettime(&endtime);
    DispPlayTime();
    WaitForKey(10);
    clrscr();
    ResetCur(); 
}

/* ------ general sub process ----------- */
int MainTimer(void)
/* output: how much 10ms have pass from last time call this process */
{
    static int oldhund,oldsec;
    struct  time t;
    int timeuse;

    gettime(&t);
    timeuse = 0;
    if(t.ti_hund!=oldhund)
    {
        if(t.ti_sec!=oldsec)
        {
            timeuse+=100;
            oldsec = t.ti_sec;
        }
        timeuse+=t.ti_hund-oldhund;
        oldhund = t.ti_hund;
    }
    else timeuse = 0;
    return (timeuse);
}

char WaitForKey(int secnum)
/* funtion: if have key in, exit immediately, else wait 'secnum' senconds then exit 
   input: secnum -- wait this senconds, must < 3600 (1 hour)
   output: key char, if no key in(exit when timeout), return NULL */
{
    int secin,secnow;
    int minin,minnow;
    int hourin,hournow;
    int secuse;
    struct  time t;

    gettime(&t);
    secin = t.ti_sec;
    minin = t.ti_min;
    hourin = t.ti_hour;
    
    do
    {
        if(kbhit()) return(getch());
        gettime(&t);
        secnow = t.ti_sec;
        minnow = t.ti_min;
        hournow = t.ti_hour;

        if(hournow!=hourin) minnow+=60;
        if(minnow>minin) secuse = (minnow-1-minin) + (secnow+60-secin);
        else secuse = secnow - secin;
        
        /* counting error check */
        if(secuse<0)
        {
            gotoxy(1,MAXY+1);
            printf("Time conuting error, any keyto exit...");
            getch();
            exit(3);
        }
    }
    while(secuse<=secnum);
    return (NULL);
}

void DispPlayTime(void)
{
    int ph,pm,ps;
    
    ph = endtime.ti_hour - starttime.ti_hour;
    pm = endtime.ti_min - starttime.ti_min;
    ps = endtime.ti_sec - starttime.ti_sec;
    
    if(ph<0) ph+=24;
    if(pm<0) { ph--; pm+=60; }
    if(ps<0) { pm--; ps+=60; }
    
    gotoxy(1,MAXY+1);
    printf("Time use: %d hour- %d min- %d sec ",ph,pm,ps);
}

int TimeUse(void)
{
    int ph,pm,ps;
    
    gettime(&endtime);
    ph = endtime.ti_hour - starttime.ti_hour;
    pm = endtime.ti_min - starttime.ti_min;
    ps = endtime.ti_sec - starttime.ti_sec;
    
    if(ph<0) ph+=24;
    if(pm<0) { ph--; pm+=60; }
    if(ps<0) { pm--; ps+=60; }
    
    return(ps+(60*(pm+60*ph)));
}


void HideCur(void)
{
    union REGS regs0;
    regs0.h.ah=1;
    regs0.h.ch=0x30;
    regs0.h.cl=0x31;
    int86(0x10,&regs0,&regs0);
}

void ResetCur(void)
{
    union REGS regs0;
    regs0.h.ah=1;
    regs0.h.ch=0x06;
    regs0.h.cl=0x07;
    int86(0x10,&regs0,&regs0);
}

/* ------------ main ANT programe ------------- */
void WorldInitial(void)
{
    int k,i,j;
    randomize();
    clrscr();
    HomeFoodInitial();
    for(AntNow=0;AntNow<MAX_ANT;AntNow++)
    {
        AntInitial();
    } /* of for AntNow */;
    
    BlockInitial();
    for(k=0;k<=1;k++)
    /* SMELL TYPE FOOD and HOME */
        for(i=0;i<=MAXX;i++)
            for(j=0;j<=MAXY;j++)
                Smell[k][i][j] = 0;
    SmellGoneTimer = 0;
    gettime(&starttime);
    SmellDispFlag = 0;
    CanFindFood = 0;
    HardtoFindPath = 0;
}

void BlockInitial(void)
{
    int i,j;
    int bn;
    
    for(i=0;i<=MAXX;i++)
        for(j=0;j<=MAXY;j++)
            block[i][j] = 0;
    
    bn = 1+ MAX_BLOCK/2 + random(MAX_BLOCK/2);
    for(i=0;i<=bn;i++) CreatBlock();
}

void CreatBlock(void)
{
    int x1,y1,x2,y2;
    int dx,dy;
    int i,j;
    
    x1 = random(MAXX)+1;
    y1 = random(MAXY)+1;
    
    dx = random(MAXX/10)+1;
    dy = random(MAXY/10)+1;
    
    x2 = x1+dx;
    y2 = y1+dy;
    
    if(x2>MAXX) x2 = MAXX;
    if(y2>MAXY) y2 = MAXY;
    
    if(food.xxx>=x1&&food.xxx<=x2&&food.yyy>=y1&&food.yyy<=y2) return;
    if(home.xxx>=x1&&home.xxx<=x2&&home.yyy>=y1&&home.yyy<=y2) return;
    
    for(i=x1;i<=x2;i++)
        for(j=y1;j<=y2;j++)
        {
            block[i][j] = 1;
            gotoxy(i,j);
            putch(BLOCK_CHAR);
        }
}

void SaveBlock(void)
{
	FILE *fp_block;
	char FileNameBlock[20];
	int i,j;

	gotoxy(1,MAXY+1);
    printf("                                       "); 
	gotoxy(1,MAXY+1);
	printf("Save to file...",FileNameBlock);
	gets(FileNameBlock);
	if(FileNameBlock[0]==0) strcpy(FileNameBlock,"Ant.ant");
	else strcat(FileNameBlock,".ant");
	
	if ((fp_block = fopen(FileNameBlock, "wb")) == NULL)
	{	gotoxy(1,MAXY+1);
        printf("Creat file %s fail...",FileNameBlock);
		getch();
		exit(2);
	}
	gotoxy(1,MAXY+1);
    printf("                                                     "); 
    
	fputc(home.xxx,fp_block);
	fputc(home.yyy,fp_block);
	fputc(food.xxx,fp_block);
	fputc(food.yyy,fp_block);
	
	for(i=0;i<=MAXX;i++)
        for(j=0;j<=MAXY;j++)
            fputc(block[i][j],fp_block);
    
    fclose(fp_block);
}

void LoadBlock(void)
{
	FILE *fp_block;
	char FileNameBlock[20];
	int i,j,k;

	gotoxy(1,MAXY+1);
    printf("                                       "); 
	gotoxy(1,MAXY+1);
	printf("Load file...",FileNameBlock);
	gets(FileNameBlock);
	if(FileNameBlock[0]==0) strcpy(FileNameBlock,"Ant.ant");
	else strcat(FileNameBlock,".ant");
	
	if ((fp_block = fopen(FileNameBlock, "rb")) == NULL)
	{	gotoxy(1,MAXY+1);
        printf("Open file %s fail...",FileNameBlock);
		getch();
		exit(2);
	}
	
	clrscr();
	home.xxx = fgetc(fp_block);
	home.yyy = fgetc(fp_block);
	food.xxx = fgetc(fp_block);
	food.yyy = fgetc(fp_block);
	gotoxy(home.xxx,home.yyy); putch(HOME_CHAR);
    gotoxy(food.xxx,food.yyy); putch(FOOD_CHAR);
    food.amount = random(MAX_FOOD/3)+2*MAX_FOOD/3+1;
    /* food.amount = MAX_FOOD; */
    home.amount = 0;
    home.TargetFood = (food.amount<TARGET_FOOD)?food.amount:TARGET_FOOD;
	
	for(AntNow=0;AntNow<MAX_ANT;AntNow++)
    {
        AntInitial();
    } /* of for AntNow */;
    
	for(i=0;i<=MAXX;i++)
        for(j=0;j<=MAXY;j++)
        {
            block[i][j] = fgetc(fp_block);
            if(block[i][j])
            {
	            gotoxy(i,j);
	            putch(BLOCK_CHAR);
	        }
        }
    
    for(k=0;k<=1;k++)
    /* SMELL TYPE FOOD and HOME */
        for(i=0;i<=MAXX;i++)
            for(j=0;j<=MAXY;j++)
                Smell[k][i][j] = 0;
    SmellGoneTimer = 0;
    gettime(&starttime);
    SmellDispFlag = 0;
    CanFindFood = 0;
    HardtoFindPath = 0;
    
    fclose(fp_block);
}

void HomeFoodInitial(void)
{
    int randnum;
    int homeplace;
    /* 1 -- home at left-up, food at right-down
       2 -- home at left-down, food at right-up
       3 -- home at right-up, food at left-down
       4 -- home at right-down, food at left-up */

    randnum = random(100);
    if(randnum<25) homeplace = 1;
    else if (randnum>=25&&randnum<50) homeplace = 2;
    else if (randnum>=50&&randnum<75) homeplace = 3;
    else homeplace = 4;
    
    switch(homeplace)
    {
        case 1: home.xxx = random(MAXX/3)+1;
                home.yyy = random(MAXY/3)+1;
                food.xxx = random(MAXX/3)+2*MAXX/3+1;
                food.yyy = random(MAXY/3)+2*MAXY/3+1;
                break;
        case 2: home.xxx = random(MAXX/3)+1;
                home.yyy = random(MAXY/3)+2*MAXY/3+1;
                food.xxx = random(MAXX/3)+2*MAXX/3+1;
                food.yyy = random(MAXY/3)+1;
                break;
        case 3: home.xxx = random(MAXX/3)+2*MAXX/3+1;
                home.yyy = random(MAXY/3)+1;
                food.xxx = random(MAXX/3)+1;
                food.yyy = random(MAXY/3)+2*MAXY/3+1;
                break;
        case 4: home.xxx = random(MAXX/3)+2*MAXX/3+1;
                home.yyy = random(MAXY/3)+2*MAXY/3+1;
                food.xxx = random(MAXX/3)+1;
                food.yyy = random(MAXY/3)+1;
                break;
    }

    food.amount = random(MAX_FOOD/3)+2*MAX_FOOD/3+1;
    /* food.amount = MAX_FOOD; */
    home.amount = 0;
    home.TargetFood = (food.amount<TARGET_FOOD)?food.amount:TARGET_FOOD;

    /* data correctness check */
    if(home.xxx<=0||home.xxx>MAXX||home.yyy<=0||home.yyy>MAXY||
       food.xxx<=0||food.xxx>MAXX||food.yyy<=0||food.yyy>MAXY||
       food.amount<=0)
    {
        gotoxy(1,MAXY+1);
        printf("World initial fail, any key to exit...");
        getch();
        exit(2);    
    }
        
    gotoxy(home.xxx,home.yyy); putch(HOME_CHAR);
    gotoxy(food.xxx,food.yyy); putch(FOOD_CHAR);
}

void AntInitial(void)
/* initial ant[AntNow] */
{
    int randnum;
    int i;
    
    ant[AntNow].xxx = home.xxx;
    ant[AntNow].yyy = home.yyy;
    
    randnum = random(100);
    if(randnum<25) ant[AntNow].dir = UP;
    else if (randnum>=25&&randnum<50) ant[AntNow].dir = DOWN;
    else if (randnum>=50&&randnum<75) ant[AntNow].dir = LEFT;
    else ant[AntNow].dir = RIGHT;
    
    ant[AntNow].speed = 2*(random(INI_SPEED/2)+1);
    ant[AntNow].SpeedTimer = 0;
    ant[AntNow].food = 0;
    ant[AntNow].SmellAmount[SMELL_TYPE_FOOD] = 0;
    ant[AntNow].SmellAmount[SMELL_TYPE_HOME] = MAX_SMELL;
    ant[AntNow].IQ = 1;
    
    for(i=0;i<TRACE_REMEMBER;i++)
    {
        ant[AntNow].tracex[i] = 0;
        ant[AntNow].tracey[i] = 0;
    }
    ant[AntNow].TracePtr = 0;
    
    /* a sepecail ant */
    if(AntNow==0) ant[AntNow].speed = INI_SPEED;
}

void WorldChange(void)
{
    int k,i,j;
    int smelldisp;
    
    SmellGoneTimer+=timer10ms;
    if(SmellGoneTimer>=SMELL_GONE_SPEED)
    {
        SmellGoneTimer = 0;
        for(k=0;k<=1;k++)
        /* SMELL TYPE FOOD and HOME */
            for(i=1;i<=MAXX;i++)
                for(j=1;j<=MAXY;j++)
            		{
                        if(Smell[k][i][j])
                		{
                            smelldisp = 1+((10*Smell[k][i][j])/(MAX_SMELL*SMELL_DROP_RATE));
                            if(smelldisp>=30000||smelldisp<0) smelldisp = 30000;
                            if(SmellDispFlag)
                			{
                                gotoxy(i,j);
                                if((i==food.xxx&&j==food.yyy)||(i==home.xxx&&j==home.yyy))
                                    /* don't over write Food and Home */;
                        		else
                    			{
                                    if(smelldisp>9) putch('#');
                                    else putch(smelldisp+'0');
                    			}
                			}
                            Smell[k][i][j]-= 1+(Smell[k][i][j]*SMELL_GONE_RATE);
                            if(Smell[k][i][j]<0) Smell[k][i][j] = 0;
                            if(SmellDispFlag)
                			{
                                if(Smell[k][i][j]<=2)
                    			{
                                    gotoxy(i,j);
                                    putch(SPACE);
                    			}
                			}
                		}
                    } /* of one location */
    } /* of time to change the world */
} /* of world change */

void AntMove(void)
{
    int antx,anty;
    int smelltodrop,smellnow;
    
    for(AntNow=0;AntNow<MAX_ANT;AntNow++)
    {
        ant[AntNow].SpeedTimer+=timer10ms;
        if(ant[AntNow].SpeedTimer>=ant[AntNow].speed)
        {
            ant[AntNow].SpeedTimer = 0;
            gotoxy(ant[AntNow].xxx,ant[AntNow].yyy);
            putch(SPACE);
            AntOneStep();
            gotoxy(ant[AntNow].xxx,ant[AntNow].yyy);
            /* ant0 is a sepecail ant, use different color */
            if(AntNow==0) textcolor(0xd);
            if(ant[AntNow].food) putch(ANT_CHAR_FOOD);
            else putch(ANT_CHAR_EMPTY);
            if(AntNow==0) textcolor(0x7);
        	
            /* remember trace */
            ant[AntNow].tracex[ant[AntNow].TracePtr] = ant[AntNow].xxx;
            ant[AntNow].tracey[ant[AntNow].TracePtr] = ant[AntNow].yyy;
            if(++(ant[AntNow].TracePtr)>=TRACE_REMEMBER) ant[AntNow].TracePtr = 0;
        	
            /* drop smell */
            antx = ant[AntNow].xxx;
            anty = ant[AntNow].yyy;
        	
            if(ant[AntNow].food)
            /* have food, looking for home */
        	{
                if(ant[AntNow].SmellAmount[SMELL_TYPE_FOOD])
            	{
                    smellnow = Smell[SMELL_TYPE_FOOD][antx][anty];
                    smelltodrop = ant[AntNow].SmellAmount[SMELL_TYPE_FOOD]*SMELL_DROP_RATE;
                    if(smelltodrop>smellnow) Smell[SMELL_TYPE_FOOD][antx][anty] = smelltodrop;
                    /* else Smell[...] = smellnow */
                    ant[AntNow].SmellAmount[SMELL_TYPE_FOOD]-= smelltodrop;
                    if(ant[AntNow].SmellAmount[SMELL_TYPE_FOOD]<0) ant[AntNow].SmellAmount[SMELL_TYPE_FOOD] = 0;
                } /* of have smell to drop */
            } /* of have food */
            else
            /* no food, looking for food */
        	{
                if(ant[AntNow].SmellAmount[SMELL_TYPE_HOME])
            	{
                    smellnow = Smell[SMELL_TYPE_HOME][antx][anty];
                    smelltodrop = ant[AntNow].SmellAmount[SMELL_TYPE_HOME]*SMELL_DROP_RATE;
                    if(smelltodrop>smellnow) Smell[SMELL_TYPE_HOME][antx][anty] = smelltodrop;
                    /* else Smell[...] = smellnow */
                    ant[AntNow].SmellAmount[SMELL_TYPE_HOME]-= smelltodrop;
                    if(ant[AntNow].SmellAmount[SMELL_TYPE_HOME]<0) ant[AntNow].SmellAmount[SMELL_TYPE_HOME] = 0;
                } /* of have smell to drop */
        	}
        } /* of time to go */
        /* else not go */
    } /* of for AntNow */
    
    textcolor(FOOD_HOME_COLOR);
    gotoxy(home.xxx,home.yyy); putch(HOME_CHAR);
    gotoxy(food.xxx,food.yyy);
    if(food.amount>0) putch(FOOD_CHAR);
    else putch(FOOD_CHAR2);
    textcolor(7);

    gotoxy(1,MAXY+1);
    printf("Food %d, Home %d   ",food.amount,home.amount);
}

void AntOneStep(void)
{
    int ddir,tttx,ttty;
    int i;
    
    ddir = ant[AntNow].dir;
    tttx = ant[AntNow].xxx;
    ttty = ant[AntNow].yyy;
    
    ddir = AntNextDir(tttx,ttty,ddir);
    
    switch(ddir)
    {
        case UP:    ttty--;
                    break;	
        case DOWN:  ttty++;
                    break;	
        case LEFT:  tttx--;
                    break;	
        case RIGHT: tttx++;
                    break;	
        default:    break;
    } /* of switch dir */
    
    ant[AntNow].dir = ddir;
    ant[AntNow].xxx = tttx;
    ant[AntNow].yyy = ttty;
    
    if(ant[AntNow].food)
    /* this ant carry with food, search for home */
    {
        if(tttx==home.xxx&&ttty==home.yyy)
        {
            home.amount++;
            AntInitial();
        }
        if(tttx==food.xxx&&ttty==food.yyy)
            ant[AntNow].SmellAmount[SMELL_TYPE_FOOD] = MAX_SMELL;
    } /* of search for home */
    else
    /* this ant is empty, search for food */
    {
        if(tttx==food.xxx&&ttty==food.yyy)
        {
            if(food.amount>0)
        	{
                ant[AntNow].food = 1;
                food.amount--;
                ant[AntNow].SmellAmount[SMELL_TYPE_FOOD] = MAX_SMELL;
                ant[AntNow].SmellAmount[SMELL_TYPE_HOME] = 0;
                ant[AntNow].dir = TurnBack(ant[AntNow].dir);
                for(i=0;i<TRACE_REMEMBER;i++)
            	{
                    ant[AntNow].tracex[i] = 0;
                    ant[AntNow].tracey[i] = 0;
            	}
                ant[AntNow].TracePtr = 0;
                CanFindFood = 1;
            } /* of still have food */
        }
        if(tttx==home.xxx&&ttty==home.yyy)
            ant[AntNow].SmellAmount[SMELL_TYPE_HOME] = MAX_SMELL;
    }  /* of search for food */
}

void DealKey(char key)
{
    int i;
    switch(key)
    {
        case 'p':   gettime(&endtime);
                    DispPlayTime();
                    getch();
                    gotoxy(1,MAXY+1);
                    for(i=1;i<=MAXX-1;i++) putch(SPACE);
                    break;
        case 't':   if(SmellDispFlag)
            		{
                        SmellDispFlag=0;
                        ClearSmellDisp();
            		}
                    else SmellDispFlag = 1;
                    break;
        case '1':   DispSmell(SMELL_TYPE_FOOD);
                    getch();
                    ClearSmellDisp();
                    break;
        case '2':   DispSmell(SMELL_TYPE_HOME);
                    getch();
                    ClearSmellDisp();
                    break;
        case '3':   DispSmell(2);
                    getch();
                    ClearSmellDisp();
                    break;
        case 's':   SaveBlock();
        			break;
        case 'l':   LoadBlock();
        			break;
        default:    gotoxy(1,MAXY+1);
                    for(i=1;i<=MAXX-1;i++) putch(SPACE);
    } /* of switch */
}

void ClearSmellDisp(void)
{
    int k,i,j;
    
    for(k=0;k<=1;k++)
    /* SMELL TYPE FOOD and HOME */
        for(i=1;i<=MAXX;i++)
            for(j=1;j<=MAXY;j++)
            	{
                    if(Smell[k][i][j])
            		{
                        gotoxy(i,j);
                        putch(SPACE);
            		}
                } /* of one location */
}

void DispSmell(int type)
/* input: 0 -- Only display food smell
          1 -- Only display home smell
          2 -- Display both food and home smell
*/
{
    int k,i,j;
    int fromk,tok;
    int smelldisp;
    
    switch(type)
    {
        case 0: fromk = 0;
                tok = 0;
                break;
        case 1: fromk = 1;
                tok = 1;
                break;
        case 2: fromk = 0;
                tok = 1;
                break;
        default:fromk = 0;
                tok = 1;
                break;	
    }
    SmellGoneTimer = 0;
    for(k=fromk;k<=tok;k++)
    /* SMELL TYPE FOOD and HOME */
        for(i=1;i<=MAXX;i++)
            for(j=1;j<=MAXY;j++)
            	{
                    if(Smell[k][i][j])
            		{
                        smelldisp = 1+((10*Smell[k][i][j])/(MAX_SMELL*SMELL_DROP_RATE));
                        if(smelldisp>=30000||smelldisp<0) smelldisp = 30000;
                        gotoxy(i,j);
                        if(i!=food.xxx||j!=food.yyy)
                		{
                            if((i==food.xxx&&j==food.yyy)||(i==home.xxx&&j==home.yyy))
                                /* don't over write Food and Home */;
                    		else
                			{
                                if(smelldisp>9) putch('#');
                                else putch(smelldisp+'0');
                			}
                		}
            		}
                } /* of one location */ 
}

int AntNextDir(int xxx,int yyy,int ddir)
{
    int randnum;
    int testdir;
    int CanGoState;
    int cangof,cangol,cangor;
    int msf,msl,msr,maxms;
    int type;
    
    CanGoState = CanGo(xxx,yyy,ddir);
    if(CanGoState==0||CanGoState==2||CanGoState==3||CanGoState==6) cangof = 1;
    else cangof = 0;
    if(CanGoState==0||CanGoState==1||CanGoState==3||CanGoState==5) cangol = 1;
    else cangol = 0;
    if(CanGoState==0||CanGoState==1||CanGoState==2||CanGoState==4) cangor = 1;
    else cangor = 0;
    
    if(ant[AntNow].food) type = SMELL_TYPE_HOME;
    else type = SMELL_TYPE_FOOD;
    
    msf = GetMaxSmell(type,xxx,yyy,ddir);
    msl = GetMaxSmell(type,xxx,yyy,TurnLeft(ddir));
    msr= GetMaxSmell(type,xxx,yyy,TurnRight(ddir));
    maxms = MaxLocation(msf,msl,msr);
    /* maxms - 1 - msf is MAX
               2 - msl is MAX
               3 - msr is MAX 
               0 - all 3 number is 0 */
    
    testdir = NULL;
    switch(maxms)
    {
        case 0: /* all is 0, keep testdir = NULL, random select dir */
                break;
        case 1: if(cangof)
                    testdir = ddir;
                else
                    if(msl>msr) if(cangol) testdir = TurnLeft(ddir);
                    else if(cangor) testdir = TurnRight(ddir);
                break;
        case 2: if(cangol)
                    testdir = TurnLeft(ddir);
                else
                    if(msf>msr) if(cangof) testdir = ddir;
                    else if(cangor) testdir = TurnRight(ddir);
                break;
        case 3: if(cangor)
                    testdir = TurnRight(ddir);
                else
                    if(msf>msl) if(cangof) testdir =ddir;
                    else if(cangol) testdir = TurnLeft(ddir);
                break;
        default:break;
    } /* of maxms */
    
    randnum = random(1000);
    if(randnum<SMELL_DROP_RATE*1000||testdir==NULL)
    /* 1. if testdir = NULL, means can not find the max smell or the dir to max smell can not go
       then random select dir
       2. if ant error, don't follow the smell, random select dir
    */
    {
        randnum = random(100);
        switch(CanGoState)
        {
            case 0: if(randnum<90) testdir = ddir;
                    else if (randnum>=90&&randnum<95) testdir = TurnLeft(ddir);
                    else testdir = TurnRight(ddir);
                    break;
            case 1: if(randnum<50) testdir = TurnLeft(ddir);
                    else testdir = TurnRight(ddir);
                    break;
            case 2: if(randnum<90) testdir = ddir;
                    else testdir = TurnRight(ddir);
                    break;
            case 3: if(randnum<90) testdir = ddir;
                    else testdir = TurnLeft(ddir);
                    break;
            case 4: testdir = TurnRight(ddir);
                    break;
            case 5: testdir = TurnLeft(ddir);
                    break;
            case 6: testdir = ddir;
                    break;
            case 7: testdir = TurnBack(ddir);
                    break;
            default:testdir = TurnBack(ddir);
        } /* of can go state */ 
    }
    return(testdir);
}

int GetMaxSmell(int type,int xxx,int yyy,int ddir)
{
    int i,j;
    int ms; /* MAX smell */
    
    ms = 0;
    switch(ddir)
    {
        case UP:    for(i=xxx-ANT_EYESHOT;i<=xxx+ANT_EYESHOT;i++)
                        for(j=yyy-ANT_EYESHOT;j<yyy;j++)
                		{
                            if(!JudgeCanGo(i,j)) continue;
                            if((i==food.xxx&&j==food.yyy&&type==SMELL_TYPE_FOOD)||
                               (i==home.xxx&&j==home.yyy&&type==SMELL_TYPE_HOME))
                			{
                                ms = MAX_SMELL;
                            	break;
                			}
                            if(IsTrace(i,j)) continue;
                            if(Smell[type][i][j]>ms) ms = Smell[type][i][j];
                		}
                    break;	
        case DOWN:  for(i=xxx-ANT_EYESHOT;i<=xxx+ANT_EYESHOT;i++)
                        for(j=yyy+1;j<=yyy+ANT_EYESHOT;j++)
                		{
                            if(!JudgeCanGo(i,j)) continue;
                            if((i==food.xxx&&j==food.yyy&&type==SMELL_TYPE_FOOD)||
                               (i==home.xxx&&j==home.yyy&&type==SMELL_TYPE_HOME))
                			{
                                ms = MAX_SMELL;
                            	break;
                			}
                            if(IsTrace(i,j)) continue;
                            if(Smell[type][i][j]>ms) ms = Smell[type][i][j];
                		}
                    break;	
        case LEFT:  for(i=xxx-ANT_EYESHOT;i<xxx;i++)
                        for(j=yyy-ANT_EYESHOT;j<=yyy+ANT_EYESHOT;j++)
                		{
                            if(!JudgeCanGo(i,j)) continue;
                            if((i==food.xxx&&j==food.yyy&&type==SMELL_TYPE_FOOD)||
                               (i==home.xxx&&j==home.yyy&&type==SMELL_TYPE_HOME))
                			{
                                ms = MAX_SMELL;
                            	break;
                			}
                            if(IsTrace(i,j)) continue;
                            if(Smell[type][i][j]>ms) ms = Smell[type][i][j];
                		}
                    break;	
        case RIGHT: for(i=xxx+1;i<=xxx+ANT_EYESHOT;i++)
                        for(j=yyy-ANT_EYESHOT;j<=yyy+ANT_EYESHOT;j++)
                		{
                            if(!JudgeCanGo(i,j)) continue;
                            if((i==food.xxx&&j==food.yyy&&type==SMELL_TYPE_FOOD)||
                               (i==home.xxx&&j==home.yyy&&type==SMELL_TYPE_HOME))
                			{
                                ms = MAX_SMELL;
                            	break;
                			}
                            if(IsTrace(i,j)) continue;
                            if(Smell[type][i][j]>ms) ms = Smell[type][i][j];
                		}
                    break;	
        default:    break;
    }
    return(ms);
}

int IsTrace(int xxx,int yyy)
{
    int i;
    
    for(i=0;i<TRACE_REMEMBER;i++)
        if(ant[AntNow].tracex[i]==xxx&&ant[AntNow].tracey[i]==yyy) return(1);
    return(0);  
}

int MaxLocation(int num1,int num2,int num3)
{
    int maxnum;
    
    if(num1==0&&num2==0&&num3==0) return(0);
    
    maxnum = num1;
    if(num2>maxnum) maxnum = num2;
    if(num3>maxnum) maxnum = num3;
    
    if(maxnum==num1) return(1);
    if(maxnum==num2) return(2);
    if(maxnum==num3) return(3); 
}

int CanGo(int xxx,int yyy,int ddir)
/* input: xxx,yyy - location of ant
          ddir - now dir
   output: 0 - forward and left and right can go
           1 - forward can not go
           2 - left can not go
           3 - right can not go
           4 - forward and left can not go
           5 - forward and right can not go
           6 - left and right can not go
           7 - forward and left and right all can not go
*/
{
    int tx,ty,tdir;
    int okf,okl,okr;
    
    /* forward can go ? */
    tdir = ddir;
    tx = xxx;
    ty = yyy;
    switch(tdir)
    {
        case UP:    ty--;
                    break;	
        case DOWN:  ty++;
                    break;	
        case LEFT:  tx--;
                    break;	
        case RIGHT: tx++;
                    break;	
        default:    break;
    } /* of switch dir */
    if(JudgeCanGo(tx,ty)) okf = 1;
    else okf = 0;
    
    /* turn left can go ? */
    tdir = TurnLeft(ddir);
    tx = xxx;
    ty = yyy;
    switch(tdir)
    {
        case UP:    ty--;
                    break;	
        case DOWN:  ty++;
                    break;	
        case LEFT:  tx--;
                    break;	
        case RIGHT: tx++;
                    break;	
        default:    break;
    } /* of switch dir */
    if(JudgeCanGo(tx,ty)) okl = 1;
    else okl = 0;
    
    /* turn right can go ? */
    tdir = TurnRight(ddir);
    tx = xxx;
    ty = yyy;
    switch(tdir)
    {
        case UP:    ty--;
                    break;	
        case DOWN:  ty++;
                    break;	
        case LEFT:  tx--;
                    break;	
        case RIGHT: tx++;
                    break;	
        default:    break;
    } /* of switch dir */
    if(JudgeCanGo(tx,ty)) okr = 1;
    else okr = 0;
    
    if(okf&&okl&&okr) return(0);
    if(!okf&&okl&&okr) return(1);
    if(okf&&!okl&&okr) return(2);
    if(okf&&okl&&!okr) return(3);
    if(!okf&&!okl&&okr) return(4);
    if(!okf&&okl&&!okr) return(5);
    if(okf&&!okl&&!okr) return(6);
    if(!okf&&!okl&&!okr) return(7);
    return(7);
}

int JudgeCanGo(int xxx,int yyy)
/* input: location to judeg
   output: 0 -- can not go
           1 -- can go
*/
{
    int i,j;
    
    if(xxx<=0||xxx>MAXX) return(0);
    if(yyy<=0||yyy>MAXY) return(0);
    if(block[xxx][yyy]) return(0);
    return(1);
}

int TurnLeft(int ddir)
{
    switch(ddir)
    {
        case UP:    return(LEFT);
        case DOWN:  return(RIGHT);
        case LEFT:  return(DOWN);
        case RIGHT: return(UP);
        default:    break;
    } /* of switch dir */
}

int TurnRight(int ddir)
{
    switch(ddir)
    {
        case UP:    return(RIGHT);
        case DOWN:  return(LEFT);
        case LEFT:  return(UP);
        case RIGHT: return(DOWN);
        default:    break;
    } /* of switch dir */
}

int TurnBack(int ddir)
{
    switch(ddir)
    {
        case UP:    return(DOWN);
        case DOWN:  return(UP);
        case LEFT:  return(RIGHT);
        case RIGHT: return(LEFT);
        default:    break;
    } /* of switch dir */
}
