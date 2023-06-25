#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

static char box[9]= {"         "};

static void splash(void);
static void strdly(char line[255]);

static void clrscr()
{
    system("@cls||clear");
}

static void reset_board()
{
    for(int i=0; i<9; i++)
    {
        box[i]=' ';
    }
}

static void print_board()
{
    printf("\t\t%c|%c|%c\n",box[0],box[1],box[2]);
    printf("\t\t_ _ _\n");
    printf("\t\t%c|%c|%c\n",box[3],box[4],box[5]);
    printf("\t\t_ _ _\n");
    printf("\t\t%c|%c|%c\n",box[6],box[7],box[8]);
}

static int check_winner(void)
{
    int winner=0;
    if(box[0]!=' '&&box[1]!=' '&&box[2]!=' ' )
    {
        if(box[0]==box[1]&&box[0]==box[2])
            winner=1;
    }
    if(box[3]!=' '&&box[4]!=' '&&box[5]!=' ' )
    {
        if(box[3]==box[4]&&box[3]==box[5])
            winner=1;
    }
    if(box[6]!=' '&&box[7]!=' '&&box[8]!=' ' )
    {
        if(box[6]==box[7]&&box[6]==box[8])
            winner=1;
    }
    if(box[0]!=' '&&box[3]!=' '&&box[6]!=' ' )
    {
        if(box[0]==box[3]&&box[0]==box[6])
            winner=1;
    }
    if(box[1]!=' '&&box[4]!=' '&&box[7]!=' ' )
    {
        if(box[1]==box[4]&&box[1]==box[7])
            winner=1;
    }
    if(box[2]!=' '&&box[5]!=' '&&box[8]!=' ' )
    {
        if(box[2]==box[5]&&box[2]==box[8])
            winner=1;
    }
    if(box[0]!=' '&&box[4]!=' '&&box[8]!=' ' )
    {
        if(box[0]==box[4]&&box[0]==box[8])
            winner=1;
    }
    if(box[2]!=' '&&box[4]!=' '&&box[6]!=' ' )
    {
        if(box[2]==box[4]&&box[2]==box[6])
            winner=1;
    }
    return winner;
}

static int check_empty_space(void)
{
    int full=0;
    int num=9;
    for(int i=0; i<9; i++)
    {
        if(box[i]!=' ')
            num--;
    }
    if(num==0)
        full=1;
    return full;
}

static void multiplayer(void)
{
    int move=0;
    do
    {
        print_board();

        int num;
start:
        printf("from box 1 to 9, where would you like to mark");
        scanf("%d",&num);
        num--;

        if(box[num]==' ')
        {
            if(move%2==0)
                box[num]='O';
            else
                box[num]='X';
        }
        else
        {
            printf("invalid move\n");
            goto start;
        }
        move++;
        clrscr();
        if(check_winner()==1)
        {
            print_board();
            printf("YOU WIN!\n");
            break;
        }
        if(check_empty_space()==1)
        {
            print_board();
            printf("IT'S A TIE!\n");
            break;
        }
    }
    while(check_empty_space()!=1);

}

static int bot_move(void)
{
    int num;
    srand(time(NULL));
start:
    num=rand()%9;
    if(box[num]==' ')
        box[num]='O';
    else
        goto start;
    if(check_winner()==1)
    {
        clrscr();
        print_board();
        printf("YOU LOSE!\n");
    }
}

static void player_move(void)
{
    int num;
start:
    printf("from box 1 to 9, where would you like to mark");
    scanf("%d",&num);
    num--;

    if(box[num]==' ')
        box[num]='X';
    else
    {
        printf("invalid move\n");
        goto start;
    }
    if(check_winner()==1)
    {
        clrscr();
        print_board();
        printf("YOU WIN!\n");

    }
}

static void single_player(void)
{

    char ans;
    int move=1;
    print_board();
question:
    printf("Would you like to make the first move?\n");
    printf("y/n:");
    scanf(" %c",&ans);
    do
    {
        clrscr();
        print_board();
        switch(ans)
        {
        case 'y':
        case 'Y':
        {
            if(move%2==1)
                player_move();
            else
                bot_move();
            break;
        }
        case 'n':
        case 'N':
        {
            if(move%2==0)
                player_move();
            else
                bot_move();
            break;
        }
        default:
        {
            printf("INVALID INPUT!\n");
            goto question;
        }
        }
        move++;
    }
    while(check_winner()!=1&&check_empty_space()!=1);

        if(check_empty_space()==1&&check_winner()!=1)
            printf("IT'S A TIE!\n");
}

void main_tic_tac_toe(void)
{
    char ans;
    system("color 0A");
menu:
    splash();
    int ques;
    printf("Which mode do you want to play: ");
    scanf(" %d",&ques);
    clrscr();
    switch(ques)
    {
    case 1:
    {
reset:
        reset_board();
        single_player();
        printf("Would you like to play again?\n");
        printf("y/n: ");
        scanf(" %c",&ans);
        if(ans=='y'||ans=='Y')
        {
            goto reset;
        }
        else
            goto menu;
    }
    case 2:
    {
preset:
        reset_board();
        multiplayer();
        printf("Would you like to play again?\n");
        printf("y/n: ");
        scanf(" %c",&ans);
        if(ans=='y'||ans=='Y')
        {
            goto preset;
        }
        else
            goto menu;
    }
    case 3:
        break;
    default:
        goto menu;
    }
}

static void strdly(char line[255])
{
    Sleep(45);
    printf("%s",line);
}

static void splash(void)
{

    strdly("                              _______________________________________________ \n");
    strdly("                             |  ___________________________________________  | \n");
    strdly("                             | |              #             @              | | \n");
    strdly("                             | |    #######   #     ###     @     +####    | | \n");
    strdly("                             | |    #######   #     ###     @   -#####     | | \n");
    strdly("                             | |    -:###     #     ###     @   :###.      | | \n");
    strdly("                             | |      ###     #     ###     @  .###        | | \n");
    strdly("                             | |      ###     #     ###     @  .###        | | \n");
    strdly("                             | |      ###     #     ###     @  .### .::    | | \n");
    strdly("                             | |      ###     #     ###     @   ######:    | | \n");
    strdly("                             | |      ***     #     ***     @    !###=     | | \n");
    strdly("                             | | ###########################@############# | | \n");
    strdly("                             | |     #######  #      ##;    @     +####    | | \n");
    strdly("                             | |     #######  #     ####;   @   -#####     | | \n");
    strdly("                             | |      :###    #    ######   @   :###.      | | \n");
    strdly("                             | |      :###    #   ###  ##;  @  .###        | | \n");
    strdly("                             | |      :###    #  :###  ###  @  .###        | | \n");
    strdly("                             | |      .###    #  #########; @  .### .::    | | \n");
    strdly("                             | |      :###    #  ########## @   ######:    | | \n");
    strdly("                             | |      :###    #  ###    ### @    !###=     | | \n");
    strdly("                             | | ###########################@############# | | \n");
    strdly("                             | |    #######   #     ####    @   #######    | | \n");
    strdly("                             | |    #######   #   #######   @   #######    | | \n");
    strdly("                             | |      ###     #  ###   ###  @   ###        | | \n");
    strdly("                             | |      ###     #  ###   ###  @   #####      | | \n");
    strdly("                             | |      ###     #  ###   ###  @   #####      | | \n");
    strdly("                             | |      ###     #  ###   ###  @   ###        | | \n");
    strdly("                             | |      ###     #   ##   ##   @   #######    | | \n");
    strdly("                             | |      ###     #    #####    @   #######    | | \n");
    strdly("                             | |___________________________________________| | \n");
    strdly("                             |_______________________________________________| \n");
    strdly(" \n");
    strdly("                                      _______________________________\n");
    strdly("                                     |  ___________________________  | \n");
    strdly("                                     | |    1. SINGLE PLAYER       | | \n");
    strdly("                                     | |    2. MULTIPLAYER         | | \n");
    strdly("                                     | |    3. EXIT                | | \n");
    strdly("                                     | |___________________________| | \n");
    strdly("                                     |_______________________________| \n");

}
