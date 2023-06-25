#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <time.h>

#define height 20
#define width 80

//#define TESTING
#ifdef TESTING
#define BLANK '#'
#else
#define BLANK ' '
#endif // TESTING

static int tailx[200],taily[200];
static char field[height][width];
static int gameover,a,b,body=8,score;
static char current_time[40];
static char username[255],line[255];
static FILE*records;

void main_log();
static void clrscn();
static void splash_snake();
static void splash_menu();
static void get_time();
static void make_border();
static void mt_fld();
static void print_field();
static int find(char);
static void movement(char,char,int,int);
static void food();
static void body_movement();
static void make_record();
static void menu(void)
{
    splash_snake();
    main_log();
    int option;

    clrscn();
    splash_snake();
    splash_menu();
    printf("\nENTER HERE>");
    again:
    scanf("%d",&option);
    clrscn();
    switch(option)
    {
    case 1:
        break;
    case 2:
        clrscn();
    records = fopen("record.txt","r");
    while(!feof(records)){
        fgets(line,255,records);
        printf("%s\n",line);
    };
    fclose(records);
    splash_menu();
    goto again;
    break;
    case 3:
        printf("EXITED!");
        main();
        break;
    default:
        printf("INVALID INPUT.");
        goto again;
    }

}


void snake_main(void)
{
    //get_time();
    //printf("%s",current_time);
    //scanf("%d",&gameover);
    system("color 0A");
    int option;
    menu();
    srand(time(NULL));
    int x,y,data;
reset:
    clrscn();
    printf("\e[?25l");
    make_border();
    mt_fld();

    char move='a',tmp_move;
    while(gameover==0)
    {
        //Sleep(1000);
        fflush(stdin);
        data=find('<');
        x = data / 1000;
        y = data % 1000;

        if(kbhit()!=0)
        {
            tmp_move= tolower(getch());
            if(tmp_move=='w'||tmp_move=='a'||tmp_move=='s'||tmp_move=='d')
                if(fabs(tmp_move-move)>4)
                    move=tmp_move;
        }
        food();
        body_movement();
        movement(move,'<',x,y);
        print_field();

    }
    printf("\e[%d;%dHGAME OVER!\n",height+3,1);
    make_record();
    printf("PLAY AGAIN?\nY/N:");
    char choice;
    mid:
    scanf(" %c",&choice);
    if(tolower(choice)=='y')
        goto reset;
    else if(tolower(choice)!='n')
    {
        clrscn();
        splash_snake();
        printf("INVALID INPUT\nTRY AGAIN>");
        goto mid;
    }
}

static void make_record(void)
{
    printf("ENTER YOUR NAME>");
    gets(username);
    get_time();
    FILE * records = fopen("record.txt","a+");
    fprintf(records,"%s\t%d\t%s",username,score,current_time);
    fclose(records);
}

static void clrscn()
{
    system("cls");
}

static void make_border(void)
{
    for(int i=0; i<width+2; i++)
    {
        printf("\e[1;%df═",i);
        printf("\e[%d;%df═",height+2,i);
        if(i<=height+2)
        {
            printf("\e[%d;1f║",i);
            printf("\e[%d;%df║",i,width+2);
        }
    }
    printf("\e[%d,%dH╝",width+2,height+2);
    printf("\e[0;0H╔");
    printf("\e[%d;0H╚",height+2);
    printf("\e[0;%dH╗",width+2);
    printf("\e[%d;%dH SCORE = %d",1,width+3,score);
}

static void mt_fld(void)
{
    gameover=0;
    score=0;
    int xstart = height / 2;
    int ystart = width  / 2;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            field[i][j]=BLANK;
        }
    }
    field[xstart][ystart]='<';
    field[xstart][ystart + 1]='@';
    field[xstart][ystart + 2]='$';
    tailx[0] = xstart;
    taily[0] = ystart + 1;

start:
    a=rand()%height-2;
    b=rand()%width-2;
    if(field[a][b]!=BLANK)
        goto start;
    else
        field[a][b]='*';
}

static void print_field(void)
{
    int n=2;
    for(int i=0; i<height; i++)
    {
        printf("\e[%d;2H",n);//this makes the go through wall glitch
        n++;
        for(int j=0; j<width; j++)
        {
            printf("%c",field[i][j]);
        }
    }
}

static int find(char obj)
{
    for(int i=0; i<=height; i++)
        for(int j=0; j<=width; j++)
        {
            if(field[i][j]==obj)
                return i*1000+j;
        }
}

static void movement(char move,char obj,int x, int y)//x=height,y=width
{
    field[x][y]='#';

    switch(move)
    {
    case 'w':
    {
        x--;
        if(x<0)
            x=height-1;
        break;

    }
    case 's':
    {
        x++;
        if(x>height-1)
            x=0;
        break;
    }
    case 'a':
    {
        y--;
        if(y==0)
            y=width-1;
        break;
    }
    case 'd':
    {
        y++;
        if(y==width-1)
            y=0;
        break;
    }
    }

    if('$' == field[x][y] || '#' == field[x][y])
    {
        field[x][y]=obj;
        gameover = 1;
    }
    else field[x][y]=obj;
}

static void food(void)
{
    if(field[a][b]=='<')
    {
        score+=10;
        body+=2;
        printf("\e[%d;%dH \e[KSCORE = %d",1,width+2,score);
start:
        a=rand()%height-3;
        b=rand()%width-2+1;
        if(field[a][b]!=BLANK)
            goto start;
        else
        {
            field[a][b]='*';
        }
    }
}

static void body_movement(void)
{
    int x,y,data;
    data=find('$');
    x = data / 1000;
    y = data % 1000;
    field[x][y]=' ';
    field[tailx[0]][taily[0]]='$';

    for(int i=0; i<body; i++)
    {
        tailx[i]=tailx[i+1];
        taily[i]=taily[i+1];
    }
    data=find('<');
    x=data/1000;
    y=data-x*1000;
    tailx[body]=x;
    taily[body]=y;
}

static void get_time(void)
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strcpy( current_time, asctime (timeinfo) );
}

static void splash_snake(void)
{
    strdly("                                           =:                     \n");
    strdly("                                           .#+                    \n");
    strdly("                                           .-+-                   \n");
    strdly("                              :-::.::::    :--#                   \n");
    strdly("                           :*#+#+*###*+#**--=---                  \n");
    strdly("                        .=#+=+%#+::::=++++#*@-:*                  \n");
    strdly("                    =+#%#*+++#@*#%    01*++++*#%:=                  \n");
    strdly("                   ++++*++++++@#++#+#%@%++@++%+:                  \n");
    strdly("                  +=++++#@#++++++*+++*++++++#%%@-                 \n");
    strdly("          .......-=+++@*+@@@@%#*#%####***#*+*++*%......           \n");
    strdly("          .#=+==+%-+++%++%++@@@@@@@#+==+=-'''-'''*===#.           \n");
    strdly("      ....--.....#++++**#%++**@@@@+*#%#+=*  =*-  :.. --....       \n");
    strdly("     :%%#-..:####++++#*+*%@#+++%@#*======%.**@@.*####: .-#%%:      \n");
    strdly("     .*. .-###@@@=++**++%%%%@++=%@@+#=+@@@%=@@@@@@@###-. .*.      \n");
    strdly("      :+ *#%@@@%@++**+++%%%%%%++=#@@+%==*===+%%%%%@@@%#* +:       \n");
    strdly("      .#.:#@@%%%%+*++*##%@%%%@%*+-*@@+%==#===#%%%%%%@@#:.#.       \n");
    strdly("       :* *%@%%%%++*++++*@@@%%%@%*++@@*@+%+==%%%%%%%@%* *:        \n");
    strdly("       .# .#@@%%@%++#+++*@%%%@%%%@%*+@#*==*+#%%%%%%@@#: #.        \n");
    strdly("        :* *%@%%%@%+#++++*@@%%%%%%%@%+#+#==#%%%%%%%@%* *.         \n");
    strdly("        .# :#@@%%@@%*%++++%%%@%%%%%%%@%+++#==#%%%%@@#: #.         \n");
    strdly("         .# *%@%%%@@@#*+*+#@%%%@%%@%%%%%%#@%+=*%%%@%#:#:                  \n");
    strdly("          :%%'''''''@%@*+%%@%%%%%%%@%@%%@%%%%%=.'''''''';           \n");
    strdly("          -=  =@@%@  --+%#=- @%@-@%@+--=%+  @%#.   ......          \n");
    strdly("          -*    -@@@@=   #@+ %@+ *%@@  +%  %%%@.  '@@@@@.          \n");
    strdly("          :%       @% :  #%# @@.  @%@  *@ @%%%%.  '':@@@.         \n");
    strdly("          =%%#=     @ @:  @# @##  %%@  +  #%@@#.    :@@@.         \n");
    strdly("          ==%*%#    @ @@  -#      =@@  +=  @@%*.  '@@@@@.         \n");
    strdly("          +-=  *@   % @@#  * %@@*  @@  *@  =%**.  '''''''.         \n");
    strdly("          +-:=     @@ %@@+ * :@@@  +@  *@*  #@*..........         \n");
    strdly("         .=@=*@@@% #@#####@@@@@@@@@@@@@@@###@%#########+.         \n");
    strdly("          ... .... .:##. -*#@@@%%%@@@##- .##:.                    \n");
    strdly("                     .-**: =*#@@@@@#*= :**:.                      \n");
    strdly("                       .-**: -*#%#*- :**-.                        \n");
    strdly("                         .-+#: -*- :#+-.                          \n");
    strdly("                           .-+%: :%+-.                            \n");
    strdly("                             .-+@+-.                              \n");
    strdly("                               .:.                                \n");
}

static void splash_menu(void)
{
    strdly("            ________________________________________ \n");
    strdly("           |  ____________________________________  | \n");
    strdly("           | |     WHAT WOULD YOU LIKE TO DO?     | | \n");
    strdly("           | |     1. PLAY GAME                   | | \n");
    strdly("           | |     2. CHECK PREVIOUS RECORDS      | | \n");
    strdly("           | |     3. EXIT                        | | \n");
    strdly("           | |____________________________________| | \n");
    strdly("           |________________________________________|\n");

}
