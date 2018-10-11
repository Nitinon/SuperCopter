#include <stdio.h>
#include <conio.h>
#include<windows.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>
#define sizex 80
#define sizey 24
    HANDLE wHnd;    // Handle to write to the console.
    HANDLE rHnd;
    int menu[4];
    int score1,score2,score3,story_mode=0;
    int summ=0,c_enemy=0;
    double current_time[20];
    char name[6];
    //double current_time;
struct N_ranking{
    char name[20];
    int score;
}ranking[10];
struct enemy_stage{
    int turn,x,y,status,space,check;
}enemy_s1[20],enemy_s2[20],enemy_s3[20];
struct copter{
    int x,y,drop;
}copter;
struct boss{
	int x,y,status,bullet;
} boss;
struct bullet_st3{
    int x,y,status_b;
}bullet[10],enemy_bullet[10],boss_bullet[25];
struct object{
    int x,y,status;
}heal,posion,ammo;
void gotoxy(int x, int y){
    COORD c = { x, y };
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}
void copter_art(int x, int y,int rr){
	 setcolor(15,0);gotoxy(x-2,y); if(rr==1){setcolor(15,rand()%5+10); printf(" ");} setcolor(15,0);gotoxy(x+3,y-1); printf("%c%c%c",254,254,254);  printf(" "); gotoxy(x,y); setcolor(15,7); printf(" "); setcolor(15,0); gotoxy(x+2,y); setcolor(15,7); printf("   "); setcolor(15,1); printf("  ");
	 gotoxy(x,y+1); setcolor(15,7); printf("       "); setcolor(15,0);
}
void clear_here(int x,int y){
	gotoxy(x-1,y); setcolor(15,0); printf("           ");
	gotoxy(x,y+1); setcolor(15,0); printf("           ");
	gotoxy(x,y+2); setcolor(15,0); printf("           ");

}
void setcursor(int visible){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console,&lpCursor);
}
void setcolor(int fg,int bg){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg*16+fg);
}
void intro(){
    int i,j;
    int range=10;
    for(i=0;i<100;i++){
    for(j=0;j<=range*3;j+=range){
       if(i+(j/range)*5<90)
        copter_art(i+(j/range)*5+2,2+(j/range)*6,1);
    }
        Sleep(50);
    for(j=0;j<=range*3;j+=range){
       if(i+(j/range)*5<90)
        clear_here(i-1+(j/range)*5+2,1+(j/range)*6);
    }

}
system("cls");
    printf("\n\n\n");                                                                                  setcolor(10,0);
    gotoxy(16,4); printf("##########################################################################");Sleep(100);
    gotoxy(16,5);printf("#                                                                        #"); Sleep(100);
    gotoxy(16,6);printf("#       XXXXXXX   XX   XX   XXXXXXX    XXXXXXX    XXXXXXX                #");Sleep(100);
    gotoxy(16,7);printf("#       XXXX      XX   XX   XX    XX   XXX        XX    XX               #");Sleep(100);
    gotoxy(16,8);printf("#        XXX      XX   XX   XX    XX   XXXXXX     XX    XX               #");Sleep(100);
    gotoxy(16,9);printf("#          XXX    XX   XX   XXXXXXX    XXXXXX     XXXXXXX                #"); setcolor(14,0);Sleep(100);
    gotoxy(16,10);printf("#          XXXX   XXXXXXX   XX         XXX        XX   XX                #");Sleep(100);
    gotoxy(16,11);printf("#       XXXXXX    XXXXXXX   XX         XXXXXXX    XX    XX               #");Sleep(100);
    gotoxy(16,12);printf("#                                                                        #");Sleep(100);
    gotoxy(16,13);printf("#        XXXXXX    XXXXXX   XXXXXXX   XXXXXXXX   XXXXXXX    XXXXXXX      #");Sleep(100);
    gotoxy(16,14);printf("#       XXXXXXX   XX    XX  XX    XX  XXXXXXXX   XX         XX   XX      #");Sleep(100);
    gotoxy(16,15);printf("#       XXX      XX      XX XX    XX     XX      XXXXXX     XX    XX     #");setcolor(12,0); Sleep(100);
    gotoxy(16,16);printf("#       XXX      XX      XX XXXXXXX      XX      XXXXXX     XXXXXXX      #");Sleep(100);
    gotoxy(16,17);printf("#       XXXXXXX   XX    XX  XX           XX      XXX        XX   XX      #");Sleep(100);
    gotoxy(16,18);printf("#        XXXXXX    XXXXXX   XX           XX      XXXXXXX    XX    XX     #");Sleep(100);
    gotoxy(16,19);printf("#                                                                        #");Sleep(100);
    gotoxy(16,20);printf("##########################################################################");setcolor(15,0); Sleep(100);
    printf("\n                                        Press any Key to continues");
}
int sett() {
	int i,j;
	int FontSize=20;
    CONSOLE_FONT_INFOEX info = {0};


	// SET Font and Font size
	info.cbSize       = sizeof(info);
    info.dwFontSize.Y = 17; // leave X as zero
    info.FontWeight   = FW_NORMAL;
    wcscpy(info.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);

	// Remove Scrollbar
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO infox;
	GetConsoleScreenBufferInfo(handle, &infox);
	COORD new_size =
	{   infox.srWindow.Right - infox.srWindow.Left + 1,
		infox.srWindow.Bottom - infox.srWindow.Top + 1    };
	SetConsoleScreenBufferSize(handle, new_size);

}
double count_time(double current_time){
    double tt;
    tt=clock()-current_time;
    double time_taken = ((double)tt)/CLOCKS_PER_SEC;
    return time_taken+1;
}
char cursor(int x, int y){
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = {x,y}; DWORD num_read;
	if( !ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) )
		return '\0';
	else
		return buf[0];
}
void draw_ship(int x,int y){
    setcolor(14,0);
    gotoxy(x,y-1); printf("  \%c ",194);
	gotoxy(x,y); printf("|-<O");
    setcolor(15,0);
}
void draw_boss(int x,int y){
    gotoxy(x,y); setcolor(14,0); printf("%c%c%c%c%c",125,220,219,220,123);
    gotoxy(x,y+1); setcolor(6,0); printf("%c %c %c",177,176,177);
    gotoxy(x+1,y+1); setcolor(0,12); printf("%c",233);gotoxy(x+3,y+1);printf("%c",233);
    setcolor(6,0);gotoxy(x,y+2); printf("%c",223); gotoxy(x+4,y+2); printf("%c",223);
    setcolor(0,15); gotoxy(x+1,y+2); printf("%c%c%c",60,202,62);
    setcolor(14,4); gotoxy(x,y+3); printf("%c %c %c",157,157,157);
    setcolor(15,0); gotoxy(x,y+4); printf("%c%c%c%c%c",217,217,193,192,192);
}
void clear_boss(int x,int y){
	int i;
	setcolor(15,0);
	for(i=0;i<5;i++){ gotoxy(x,y+i); printf("     ");}
}
void draw_bullet(int x,int y){
    setcolor(11  ,0); gotoxy(x,y); printf(">");   setcolor(15,0);
}
void draw_bullet2(int x,int y){
    setcolor(14  ,0); gotoxy(x,y); printf("<");   setcolor(15,0);
}
void clear_ship(int x,int y){
     gotoxy(x+2,y-1); printf("  ");
	 gotoxy(x,y); printf("    ");
}
void clear_ship2(int x,int y){
	 gotoxy(x,y); printf("     ");
}
void draw_enemy(int x,int y){
    setcolor(11,0);gotoxy(x,y); printf("%c",rand()%3+176); setcolor(15,0);
}
void draw_shield(int x,int y){
        int i;
        for(i=0;i<4;i++){
        gotoxy(copter.x+7,copter.y-2+i);
        printf("%c",41);
        }
}
void clear_shield(int x,int y){
        int i;
        for(i=0;i<5;i++){
        gotoxy(x+7,y-2+i);
        printf(" ");
        }
}
void draw_heal(int x,int y,char ch){
    gotoxy(x,y);printf("______");
    gotoxy(x-1,y+1);printf("/_/__\\_\\");
    gotoxy(x+1,y+2);printf("\\  /");
    gotoxy(x+2,y+3);printf("\\/");
    gotoxy(x+3,y+4);printf("%c ",ch);
}
void clear_heal(int x,int y){
    gotoxy(x,y);printf("      ");
    gotoxy(x-1,y+1);printf("        ");
    gotoxy(x+1,y+2);printf("    ");
    gotoxy(x+2,y+3);printf("  ");
    gotoxy(x+3,y+4);printf("  ");
}
void clear_enemy(int x,int y){
    gotoxy(x,y);
    printf(" ");
}
int detect(int mode,int xt,int yt,int xo,int yo){
    if(mode==1){             //check copter
        if((yo==yt-1&&xo==xt+3)||(yo==yt&&(xo==xt-2||xo==xt-1||xo==xt||xo==xt+1||xo==xt+2||xo==xt+3))){
            return 1;
            }else return 0;
        }
        if(mode==2){            //check normal object
        if(yo==yt&&xo==xt){
            return 1;
            }else return 0;
        }
}
int detect_shield(int num){
        int i;
        for(i=0;i<4;i++){
        if(enemy_s1[num].status==1&&(copter.x+8==enemy_s1[num].x||copter.x+7==enemy_s1[num].x)&&copter.y-2+i==enemy_s1[num].y){
           return 1;
        }
       }
       return 0;
       }
void game_control(int direction){
    if(direction==1){
        if(copter.y>2&&summ>1){
            draw_ship(copter.x,--copter.y);
            clear_ship2(copter.x,copter.y+1);
        }
    }
    if(direction==2){
        draw_ship(--copter.x,copter.y);
        gotoxy(copter.x+4,copter.y);
        printf(" ");
        gotoxy(copter.x+4,copter.y-1);
        printf(" ");
    }
    if(direction==3){ //move forward
        draw_ship(++copter.x,--copter.y);
        gotoxy(copter.x-1,copter.y+1);
        printf("    ");
    }
    if(direction==5){ //move forward
        draw_ship(++copter.x,copter.y);
        gotoxy(copter.x-1,copter.y);
        printf(" ");
    }
    if(direction==0){
        if(copter.y<25){
        copter.drop++;
        if(copter.drop==3){
        clear_ship(copter.x,copter.y);
        draw_ship(copter.x,++copter.y);
        copter.drop=0;
        summ=0;
        }
        }
    }
}
int enemy_movement(int num){
int i,j;
for (i=0;i<5;i++){
    if(num==1){
        if(enemy_s3[i].x>0&&enemy_s3[i].status==1){
                if(enemy_s3[i].y==2){
                    enemy_s3[i].turn=0;
                    draw_enemy(enemy_s3[i].x-=8,enemy_s3[i].y);
                    clear_enemy(enemy_s3[i].x+8,enemy_s3[i].y);
                }
                if(enemy_s3[i].y==sizey-1){
                    enemy_s3[i].turn=1;
                    draw_enemy(enemy_s3[i].x-=8,enemy_s3[i].y);
                    clear_enemy(enemy_s3[i].x+8,enemy_s3[i].y);
                }
                if(enemy_s3[i].turn==1){
                    draw_enemy(enemy_s3[i].x,--enemy_s3[i].y);
                    clear_enemy(enemy_s3[i].x,enemy_s3[i].y+1);
                }
                if(enemy_s3[i].turn==0){
                    draw_enemy(enemy_s3[i].x,++enemy_s3[i].y);
                    clear_enemy(enemy_s3[i].x,enemy_s3[i].y-1);
                }
             }
        }
    if(num==2){
            if(enemy_s3[i].x>0&&enemy_s3[i].status==1){
                draw_enemy(--enemy_s3[i].x,enemy_s3[i].y);
                clear_enemy(enemy_s3[i].x+1,enemy_s3[i].y);
            }
            }
    if(num==3&&enemy_s3[i].status==1){ // turn 1 is up turn 2 is down
            if(enemy_s3[i].turn==1){
                draw_enemy(enemy_s3[i].x,++enemy_s3[i].y);
                clear_enemy(enemy_s3[i].x,enemy_s3[i].y-1);
            }
            if(enemy_s3[i].turn==0){
                draw_enemy(enemy_s3[i].x,--enemy_s3[i].y);
                clear_enemy(enemy_s3[i].x,enemy_s3[i].y+1);
            }
            if(enemy_s3[i].y>22){
                enemy_s3[i].turn=0;
            draw_enemy(enemy_s3[i].x-=5,enemy_s3[i].y);
            clear_enemy(enemy_s3[i].x+5,enemy_s3[i].y);
            }
            if(enemy_s3[i].y<=3){
                enemy_s3[i].turn=1;
            draw_enemy(enemy_s3[i].x-=5,enemy_s3[i].y);
            clear_enemy(enemy_s3[i].x+5,enemy_s3[i].y);

            }
            }
    if(enemy_s3[i].x==0){c_enemy++;}
        }
        return 0;
}
void boss_movement(int direction){
	if(direction==1&&boss.x-1!=20){ 				 //MoveLeft
		clear_boss(boss.x,boss.y);
		draw_boss(--boss.x,boss.y);
	}
	if(direction==2&&boss.x+5!=80){				//MoveRigth
		clear_boss(boss.x,boss.y);
		draw_boss(++boss.x,boss.y);
	}
	if(direction==3&&boss.y+1!=3){				//MoveUp
		clear_boss(boss.x,boss.y);
		draw_boss(boss.x,--boss.y);
	}
	if(direction==4&&boss.y+5!=24){				//MoveDown
		clear_boss(boss.x,boss.y);
		draw_boss(boss.x,++boss.y);
	}
}
int main_menu(){
    int ch,choice=1,x=35,y=3,i;
       Sleep(200);
        setcolor(10,0);
        for(i=0;i<=10;i++){gotoxy(x-7,y+4+i);printf("%c",186); }
        for(i=0;i<=10;i++){gotoxy(x+43,y+4+i);printf("%c",186); }//gotoxy(x+45,y+4); printf("%c",186);
        gotoxy(x-7,y+3);for(i=0;i<50;i++){ printf("%c",205);}
        gotoxy(x-7,y+15);for(i=0;i<50;i++){ printf("%c",205);}
        gotoxy(x-7,y+3); printf("%c",201); gotoxy(x-7,y+15); printf("%c",200);
        gotoxy(x+43,y+3); printf("%c",187); gotoxy(x+43,y+15); printf("%c",188);
        //This is Art
        copter_art(34,13,0);
        draw_boss(64,11);

    do{
    gotoxy(x,y-2);  printf(" __    _  __ _    __ _  _ ___ __ _");
    gotoxy(x,y-1);  printf("\(_ | ||_\)|_ |_)  /  / \\|_) | |_ |_)");
    gotoxy(x,y);    printf("__\)|_||  |__| \\  \\__\\_/|   | |__| \\");
    menu[0]=1;
    gotoxy(x+4 +7,y+5);  setcolor(13,0);printf(" START GAME  "); setcolor(15,0);
    gotoxy(x+4 +7,y+7);  setcolor(14,0);printf("HOW TO  PLAY "); setcolor(15,0);
    gotoxy(x+4 +7,y+9);  setcolor(11,0);printf("  RANKING    ");  setcolor(15,0);
    gotoxy(x+4 +7,y+11); setcolor(12,0); printf("   QUIT    ");setcolor(15,0);
    gotoxy(x ,y+17); printf("USE button W&S To Choose Enter To accept");
        gotoxy(83,22);printf(" DEV: Nitinon Penglao");  //show developer name
        gotoxy(83,23);printf(" Code: 59010734");
        gotoxy(83,24);printf(" CE 55 @KMITL");

    if(kbhit()){
     ch=getch();
     if(ch=='w')choice--;
     if(ch=='s') choice++;
    }
    if(choice>4) choice=1;
    if(choice<1) choice=4;
    clear_enemy(x+8,y+5); clear_enemy(x+8,y+7); clear_enemy(x+8,y+9); clear_enemy(x+8,y+11);
    if(choice==1) {gotoxy(x+8,y+5); printf(">");}
    if(choice==2) {gotoxy(x+8,y+7); printf(">");}
    if(choice==3) {gotoxy(x+8,y+9); printf(">");}
    if(choice==4) {gotoxy(x+8,y+11); printf(">");}
    }while(ch!='\r');
    system("cls");
    if(choice==1)choose_stage();
    if(choice==2)how_to();
    if(choice==3)show_ranking();
    if(choice==4) return 0;

}
int record(int score){

    int a,b,i,temp,j;
    FILE *fp;
    fp = fopen("ranking.txt", "r");
    for(i=0;i<5;i++)
    fscanf(fp,"%s %d",ranking[i].name,&ranking[i].score);

    for(i=0;i<5;i++){
        if(score>ranking[i].score){
            for(j=5;j>i;j--){
                strcpy(ranking[j].name,ranking[j-1].name);
                ranking[j].score=ranking[j-1].score;
            }
            break;
        }
    }
    temp=i;
    strcpy(ranking[temp].name,name);
    ranking[temp].score=score;
    fp = fopen("ranking.txt", "w");
    for(i=0;i<5;i++){
        fprintf(fp,"%s %d",ranking[i].name,ranking[i].score);
    }
    fclose(fp);
    return 0;


}
void choose_stage(){
     int ch,choice=1,x=35,y=3,i;
       Sleep(200);
        setcolor(10,0);
        for(i=0;i<=10;i++){gotoxy(x-7,y+4+i);printf("%c",186); }
        for(i=0;i<=10;i++){gotoxy(x+43,y+4+i);printf("%c",186); }//gotoxy(x+45,y+4); printf("%c",186);
        gotoxy(x-7,y+3);for(i=0;i<50;i++){ printf("%c",205);}
        gotoxy(x-7,y+15);for(i=0;i<50;i++){ printf("%c",205);}
        gotoxy(x-7,y+3); printf("%c",201); gotoxy(x-7,y+15); printf("%c",200);
        gotoxy(x+43,y+3); printf("%c",187); gotoxy(x+43,y+15); printf("%c",188);
        //This is Art
        copter_art(34,13,0);
        draw_boss(64,11);
    do{
	    gotoxy(x,y-2);  printf(" __    _  __ _    __ _  _ ___ __ _");
	    gotoxy(x,y-1);  printf("\(_ | ||_\)|_ |_)  /  / \\|_) | |_ |_)");
	    gotoxy(x,y);    printf("__\)|_||  |__| \\  \\__\\_/|   | |__| \\");
	    menu[0]=1;
	    gotoxy(x+8 +7,y+5); setcolor(14,0);printf("STORY"); setcolor(15,0);
	    gotoxy(x+8 +7,y+7); setcolor(13,0);printf("STAGE1");setcolor(15,0);
	    gotoxy(x+8 +7,y+9); setcolor(11,0);printf("STAGE2");setcolor(15,0);
	    gotoxy(x+8 +7,y+11);setcolor(7,0); printf("STAGE3");setcolor(15,0);
	    gotoxy(x+9 +7,y+13);setcolor(12,0); printf("BACK");setcolor(15,0);
	        gotoxy(83,22);printf(" DEV: Nitinon Penglao");  //show developer name
	        gotoxy(83,23);printf(" Code: 59010734");
	        gotoxy(83,24);printf(" CE 55 @KMITL");

    if(kbhit()){
     ch=getch();
     if(ch=='w')choice--;
     if(ch=='s') choice++;
    }
    if(choice>5) choice=1;
    if(choice<1) choice=5;
    clear_enemy(x+10,y+5); clear_enemy(x+10,y+7); clear_enemy(x+10,y+9); clear_enemy(x+10,y+11);clear_enemy(x+10,y+13);
    if(choice==1) {gotoxy(x +10,y+5); printf(">");}
    if(choice==2) {gotoxy(x +10,y+7); printf(">");}
    if(choice==3) {gotoxy(x +10,y+9); printf(">");}
    if(choice==4) {gotoxy(x +10,y+11); printf(">");}
    if(choice==5) {gotoxy(x +10,y+13); printf(">");}
    }while(ch!='\r');
    system("cls");
    if(choice==1){story_mode=1;stage1(); }
    if(choice==2)stage1();
    if(choice==3)stage2();
    if(choice==4)stage3();
    if(choice==5)main_menu();

}
char entername(){

    printf("enter name: ");
    scanf("%s",name);

    }
int c_continue(){
  int ch,choice=1,x=35,y=3,i;
        do{
    gotoxy(x,y-2);  printf(" __    _  __ _    __ _  _ ___ __ _");
    gotoxy(x,y-1);  printf("\(_ | ||_\)|_ |_)  /  / \\|_) | |_ |_)");
    gotoxy(x,y);    printf("__\)|_||  |__| \\  \\__\\_/|   | |__| \\");
    menu[0]=1;
    gotoxy(x+8 +7,y+5); printf("YES");
    gotoxy(x+8 +7,y+7); printf("NO");


    if(kbhit()){
     ch=getch();
     if(ch=='w')choice--;
     if(ch=='s') choice++;
    }
    if(choice>2) choice=1;
    if(choice<1) choice=2;
    clear_enemy(x+10,y+5); clear_enemy(x+10,y+7);
    if(choice==1) {gotoxy(x +10,y+5); printf(">");}
    if(choice==2) {gotoxy(x +10,y+7); printf(">");}

    }while(ch!='\r');
    system("cls");
    if(choice==1)return 1;
    if(choice==2) return 0;


}

int how_to(){
int x=25,y=0,i;
gotoxy(x,y);printf("  _  _  _____      __  _____ ___    ___ _      ___   __");
gotoxy(x,y+1);printf(" | || |\/ _ \\ \\    \/ \/ |_   _\/ _ \\  | _ \\ |    /_\\ \\ \/ \/");
gotoxy(x,y+2);printf(" | __ | \(_\) \\ \\\/\\\/ \/    | || \(_\) | |  _\/ |__ \/ _ \\ V \/ ");
gotoxy(x,y+3);printf(" |_||_|\\___\/ \\_\/\\_\/     |_| \\___\/  |_| |____\/_\/ \\_\\_| ");
    setcolor(12,0);gotoxy(x-4,y+5);for(i=0;i<65;i++)printf("%c",177);
    gotoxy(x-4,y+16);for(i=0;i<65;i++)printf("%c",177);
    for(i=0;i<11;i++){gotoxy(x-4,y+6+i); printf("%c",177);
                     gotoxy(x-4+64,y+6+i);printf("%c",177);
    }
    setcolor(15,0);

    gotoxy(x,y+6);printf("                      HOW TO PLAY                     ");
    gotoxy(x,y+7);printf("                                                      ");
    gotoxy(x,y+8);printf("    -  W =>  Take off your Helicopter          ");
    gotoxy(x,y+9);printf("    -  A =>  Move Left   ");
    gotoxy(x,y+10);printf("    -  D =>  Move  Right ");
    gotoxy(x,y+11);printf("    -  J =>  Shoot Bullet                             ");
	gotoxy(x,y+12);printf("    -  R =>  Reload                             ");
    gotoxy(x+15,y+18); printf("Press button enter to MainMenu");
    gotoxy(x,y+13);printf("    -  Itiem S=>  Shield                  ");
    gotoxy(x,y+14);printf("    -  Itiem H=>  Heal               ");
    gotoxy(x,y+15);printf("    -  Itiem A=>  Ammo              ");
	 gotoxy(83,22);printf(" DEV: Nitinon Penglao");  //show developer name
        gotoxy(83,23);printf(" Code: 59010734");
        gotoxy(83,24);printf(" CE 55 @KMITL");
    while(getch()!='\r'){}
    system("cls");
  main_menu();

    return 0;


}
int show_ranking(){
    int a,b,i,temp,score,j;
    int x=33,y=0;

gotoxy(x,y);printf("  ___    _   _  _ _  _____ _  _  ___ ");
gotoxy(x,y+1);printf(" | _ \\  \/_\\ | \\| | |\/ \/_ _| \\| |\/ __|");
gotoxy(x,y+2);printf(" |   \/ \/ _ \\| .` | ' < | || .` | \(_ |");
gotoxy(x,y+3);printf(" |_|_\\\/_\/ \\_\\_|\\_|_|\\_\\___|_|\\_|\\___|");



    FILE *fp;
     fp = fopen("ranking.txt", "r");
    for(i=0;i<5;i++)
        fscanf(fp,"%s %d",ranking[i].name,&ranking[i].score);

            fclose(fp);

    setcolor(13,0);gotoxy(x-4,y+5);for(i=0;i<47;i++)printf("%c",177);
    gotoxy(x-4,y+13);for(i=0;i<47;i++)printf("%c",177);
    for(i=0;i<7;i++){gotoxy(x-4,y+6+i); printf("%c",177);
                     gotoxy(x-4+46,y+6+i);printf("%c",177);
    }
    setcolor(15,0);
    for(i=0;i<5;i++){
        gotoxy(x+6,y+7+i); printf("%d\) %s",i+1,ranking[i].name);  gotoxy(x+6+20,y+7+i); printf("%d",ranking[i].score);
    }
    gotoxy(x+5,y+15); printf("Press button enter to MainMenu");
        gotoxy(83,22);printf(" DEV: Nitinon Penglao");  //show developer name
        gotoxy(83,23);printf(" Code: 59010734");
        gotoxy(83,24);printf(" CE 55 @KMITL");
  while(getch()!='\r'){}
  system("cls");
  main_menu();

    return 0;
}
void win(){
int x=30,y=8;
gotoxy(x,y);printf("__   _____  _   _  __      _____ _  _ ");
gotoxy(x,y+1);printf("\\ \\ \/ \/ _ \\| | | | \\ \\    \/ \/_ _| \\| |");
gotoxy(x,y+2);printf(" \\ V \/ \(_\) | |_| |  \\ \\\/\\\/ \/ | || .` |");
gotoxy(x,y+3);printf("  |_| \\___\/ \\___\/    \\_\/\\_\/ |___|_|\\_|");


gotoxy(35,15); printf("Press Button Enter to continues");
 while(getch()!='\r'){}
 system("cls");
}
void lose(){
int x=30,y=8;
gotoxy(x,y);printf("   ___   _   __  __ ___    _____   _____ ___ ");
gotoxy(x,y+1);printf("  \/ __| \/_\\ |  \\\/  | __|  \/ _ \\ \\ \/ \/ __| _ \\");
gotoxy(x,y+2);printf(" | \(_ |\/ _ \\| |\\\/| | _|  | \(_\) \\ V \/| _||   \/");
gotoxy(x,y+3);printf("  \\___\/_\/ \\_\\_|  |_|___|  \\___\/ \\_\/ |___|_|_\\");

 gotoxy(35,15); printf("Press Button Enter to continues");
   while(getch()!='\r'){}
   system("cls");
}
void ready(){
 int x=45,y=8;

 gotoxy(x,y);printf("  ______  ");
 gotoxy(x,y+1);printf(" / ___  \\ ");
 gotoxy(x,y+2);printf(" \\/   \\  \\");
 gotoxy(x,y+3);printf("   ___)  / ");
 gotoxy(x,y+4);printf("  \(___  \(  ");
 gotoxy(x,y+5);printf("      )  \\ ");
 gotoxy(x,y+6);printf("  \___\/   /");
 gotoxy(x,y+7);printf(" \\______\/ ");
//Sleep(1000);
Beep(270,1000);
system("cls");
 gotoxy(x,y);printf(" ______    ");
 gotoxy(x,y+1);printf("\/ ___  |   ");
 gotoxy(x,y+2);printf("\\\/  |  |   ");
 gotoxy(x,y+3);printf("   \/   |   ");
 gotoxy(x,y+4);printf("  \/   \/    ");
 gotoxy(x,y+5);printf(" \/   \/     ");
 gotoxy(x,y+6);printf("\(   \/__\/\\  ");
 gotoxy(x,y+7);printf("\\_______\/  ");
//Sleep(1000);
Beep(270,1000);
system("cls");
 gotoxy(x,y);printf(" __ ");
 gotoxy(x,y+1);printf("\/  \\  ");
 gotoxy(x,y+2);printf("\\\/ | ");
 gotoxy(x,y+3);printf(" | | ");
 gotoxy(x,y+4);printf(" | | ");
 gotoxy(x,y+5);printf(" | | ");
 gotoxy(x,y+6);printf("_| |_");
 gotoxy(x,y+7);printf("\\___\/");
//Sleep(1000);
Beep(270,1000);
system("cls");
x=35;
gotoxy(x,y);printf(" _____ _____  ___  ____ __   __");
gotoxy(x,y+1);printf("| ___ \\  ___|\/ _ \\|  _  \\ \\ \/ \/");
gotoxy(x,y+2);printf("| |_/ \/ |__ \/ \/_\\ \\ | | |\\ V \/ ");
gotoxy(x,y+3);printf("|    \/|  __||  _  | | | | \\ \/  ");
gotoxy(x,y+4);printf("| |\\ \\| |___| | | | |\/ \/  | |  ");
gotoxy(x,y+5);printf("\\_| \\_\\____\/\\_| |_\/___\/   \\_\/ ");
Sleep(1000);

system("cls");
gotoxy(x,y);printf(" _____ _____ ___  ______ _____ ");
gotoxy(x,y+1);printf("\/  ___|_   _\/ _ \\ | ___ \\_   _|");
gotoxy(x,y+2);printf("\\ `--.  | |\/ \/_\\ \\| |_\/ \/ | |");
 gotoxy(x,y+3);printf(" `--. \\ | ||  _  ||    \/  | |");
gotoxy(x,y+4);printf("\/\\__\/ \/ | || | | || |\\ \\  | |");
gotoxy(x,y+5);printf("\\____\/  \\_\/\\_| |_\/\\_| \\_| \\_\/");
//Sleep(2000);
Beep(400,1000);
system("cls");
}
int stage1(){
        char ch='.';
        int i,j,b; //loop border
        int life=3,score=0;
        int st_S=0,count=0,time_e[20]; //count every thing
        int x_coin,y_coin;
        int shield=0,time_less=0;
        srand( time( NULL ) ); //seed random
        entername();
        ready();
        draw_ship(copter.x=5,copter.y=10);
        setcolor(0,15);gotoxy(16,0);printf("STAGE 1 : *********** THE BEGINNING **********");setcolor(15,0);
        //generate border
        for(i=1;i<=24;i++){
            setcolor(9,9);
            gotoxy(0,i);
            printf("%c",254);
            gotoxy(81,i);
            printf("%c",254);
            setcolor(15,0);
        }
        setcolor(10,0); gotoxy(86,4); printf("%c%c",205,185); gotoxy(100,4); printf("%c%c",204,205);
        gotoxy(88,3);for(i=0;i<13;i++){ printf("%c",205);}
        gotoxy(88,5);for(i=0;i<13;i++){ printf("%c",205);}
        gotoxy(87,3); printf("%c",201); gotoxy(87,5); printf("%c",200); gotoxy(100,3); printf("%c",187); gotoxy(100,5); printf("%c",188);
        gotoxy(88,4); printf("SUPER COPTER");
        setcolor(15,0);
        gotoxy(87,7); printf("NAME: %s",name);
        gotoxy(86,8); //generate border status
        for(b=0;b<=15;b++) { setcolor(14,0); printf("%c",236); setcolor(15,0);}
        gotoxy(86,16);
        for(b=0;b<=15;b++) { setcolor(14,0); printf("%c",236); setcolor(15,0);}

        for(i=9;i<=15;i++){
            setcolor(14,0);
            gotoxy(86,i);
            printf("%c",236);
            gotoxy(101,i);
            printf("%c",236);
            setcolor(15,0);
        }
        gotoxy(83,22);printf(" DEV: Nitinon Penglao");  //show developer name
        gotoxy(83,23);printf(" Code: 59010734");
        gotoxy(83,24);printf(" CE 55 @KMITL");
        copter_art(90,19,0);
//************************set value ******************************************************
        //generate position enemy 1&3
        enemy_s1[0].x=80;
        enemy_s1[0].y=rand()%22+2;
        enemy_s1[0].status=0;
        //generate position enemy 4-15
        for(i=1;i<=15;i++){
        enemy_s1[i].x=enemy_s1[i-1].x+7;
        enemy_s1[i].y=rand()%22+2;
        enemy_s1[i].status=0;
        }
        current_time[0]=clock();        //start time
        current_time[3]=clock();
        (int)count_time(current_time[0]);
        gotoxy(9,0);
    do{
        gotoxy(0,1);
        for(i=0;i<=81;i++) {setcolor(9,0);printf("%c",254); setcolor(15,0);}
        gotoxy(0,24);
        for(i=0;i<=81;i++) {setcolor(9,0);printf("%c",254); setcolor(15,0);}
        gotoxy(90,10);
        printf("LIFE: %d",life);
        gotoxy(90,12);
        printf("SCORE: %d",score);
        gotoxy(90,14);
        printf("Time: %d",(int)count_time(current_time[3]));
        if(shield==1)clear_shield(copter.x,copter.y);
        if(kbhit()){ //copter control
        ch=getch();
        summ++;
    if(summ>3)summ=2;
    if(ch=='W'||ch=='w')game_control(1);
    if((ch=='D'||ch=='d'&&copter.x<72)&&summ>1) game_control(5);
    if((ch=='V'||ch=='v'))shield=1;    //test shield
    if((ch=='B'||ch=='b'))shield=0;
    if((ch=='A'||ch=='a'&&copter.x>1)&&summ>1) game_control(2);
    if(ch!='w'&&ch!='a'&&ch!='d'&&ch!='A'&&ch!='D')game_control(0);
        fflush(stdin);

    }else game_control(0);
        if(st_S==0){                    //random coin
            x_coin=rand()%55+10;
            y_coin=rand()%18+4;
        gotoxy(x_coin,y_coin);
        st_S++;
        }
        gotoxy(x_coin,y_coin);          //print coin until detect copter
        setcolor(10,0);printf("$");setcolor(15,0);

        if(detect(1,copter.x,copter.y,x_coin,y_coin)){ //detect coin and copter
            score++;
            clear_enemy(x_coin,y_coin);
            st_S=0;
        }
        if((int)count_time(current_time[1])==10){ //check shield time out
         current_time[0]=clock();
         shield=0;
        }
        if(shield==1){                                      //draw shield
            draw_shield(copter.x,copter.y);
        }
        if((int)count_time(current_time[0])%20==0&&heal.status==0){ //set status shield
        heal.x=rand()%50+20;
        heal.y=3;
        heal.status=1;
        shield=0;
        }
        if((int)count_time(current_time[3])%40==0&&posion.status==0){ //set status HEAL
        posion.x=rand()%50+20;
        posion.y=3;
        posion.status=1;
        }

        if(heal.status==1&&detect(1,copter.x,copter.y,heal.x+4,heal.y+4)){ //check shield detect copter
            current_time[1]=clock();
            shield=1;
            Beep(300,200);
            heal.status=0;
            clear_heal(heal.x,heal.y);
        }
        if(posion.status==1&&detect(1,copter.x,copter.y,posion.x+4,posion.y+4)){ //check POSION detect copter
            life++;
            Beep(300,200);
            posion.status=0;
            clear_heal(posion.x,posion.y);
        }

        if(posion.status==1&&count%10==0){                   //HEAL movement
            draw_heal(posion.x,++posion.y,'H');
            gotoxy(posion.x,posion.y-1);
            printf("      ");
            gotoxy(posion.x-1,posion.y);
            printf(" ");
            gotoxy(posion.x+6,posion.y);
            printf(" ");
            }
        if(shield!=1&&heal.status==1&&count%10==0){          //shield movement
            draw_heal(heal.x,++heal.y,'S');
            gotoxy(heal.x,heal.y-1);
            printf("      ");
            gotoxy(heal.x-1,heal.y);
            printf(" ");
            gotoxy(heal.x+6,heal.y);
            printf(" ");
            }
        if(heal.y+4>=23){ heal.status=0; clear_heal(heal.x,heal.y); heal.y=100;  } //clear shield when drop on wall
        if(posion.y+4>=23){ posion.status=0; clear_heal(posion.x,posion.y); posion.y=100;  } //clear HEAL when drop on wall
      for(i=0;i<15;i++){  //enemy movement
        enemy_s1[i].x--;
        if(detect_shield(i)&&shield==1){                     //detect shield
                enemy_s1[i].status=0;
                clear_enemy(enemy_s1[i].x+1,enemy_s1[i].y);
                Beep(1000,500);
       }
        if(enemy_s1[i].x==79) enemy_s1[i].status=1;         //check until
        if(enemy_s1[i].status==1) {                         //draw enemy
        draw_enemy(enemy_s1[i].x,enemy_s1[i].y);
        clear_enemy(enemy_s1[i].x+1,enemy_s1[i].y);
        }
        if(enemy_s1[i].x<=1){                               //clear enemy when touch wall
           clear_enemy(enemy_s1[i].x,enemy_s1[i].y);
           enemy_s1[i].x=95;
           enemy_s1[i].y=rand()%22+2;
           enemy_s1[i].status=0;
        }
        if(detect(1,copter.x,copter.y,enemy_s1[i].x,enemy_s1[i].y)&&enemy_s1[i].status==1){ //detect copter and enemy
           life--;
           Beep(300,200);
           clear_enemy(enemy_s1[i].x,enemy_s1[i].y);
           enemy_s1[i].x=95;
           enemy_s1[i].y=rand()%22+2;
           enemy_s1[i].status=0;
        }
    }
        if(copter.y==24||copter.y==2){  //when copter hit border

                Beep(1000,300);
                life--;
                if(shield==1){
                clear_shield(copter.x,copter.y);
				clear_ship(copter.x,copter.y);
			}else{
			    clear_ship(copter.x,copter.y);
            }
                draw_ship(copter.x=5,copter.y=10);
                gotoxy(0,1);
                    for(i=0;i<=81;i++) {setcolor(9,0);printf("%c",254); setcolor(15,0);}
                gotoxy(0,24);
                    for(i=0;i<=81;i++) {setcolor(9,0);printf("%c",254); setcolor(15,0);}
                Sleep(200);

			}
        count++;
		if(count>10000) count=1;
        Sleep(50);
}while (ch!='x'&&score<20&&life>0);
        if((int)count_time(current_time[3])>100)
            time_less=(int)count_time(current_time[3])-100;
            Beep(1000,1000);
            system("cls");
            score1=score-(time_less/10)+(life*10);
        if(story_mode==1){
            gotoxy(36,6); printf("Do you want continues to Stage2 ?");
        if(c_continue()==1)stage2();
            else main_menu();
        }else{
        if(life==0||ch=='x')lose();
            else win();
            main_menu();
        }
        if(life<=0)main_menu();
        return 0;
}
int stage2(){
        char ch='.';
        int eX=40,count_e=0,count_e2=1;
        int i,j,b;
        int life=1;
        int score=0;
        int st_S=0,check_del_space=0;
        int space=9;
        int enemy_count=1,del_space=0;
         summ=0;
         srand( time( NULL ) );
        if(story_mode!=1) entername();
        ready();
        setcursor(0);
        draw_ship(copter.x=5,copter.y=10);
        gotoxy(20,0); setcolor(0,15); printf("STAGE 2 : *********** BONUS TIME **********");setcolor(15,0);
        //generate border
        for(i=1;i<=24;i++){
            setcolor(5,5);
            gotoxy(0,i);
            printf("%c",254);
            gotoxy(81,i);
            printf("%c",254);
            setcolor(15,0);
        }
        setcolor(10,0); gotoxy(86,4); printf("%c%c",205,185); gotoxy(100,4); printf("%c%c",204,205);
        gotoxy(88,3);for(i=0;i<13;i++){ printf("%c",205);}
        gotoxy(88,5);for(i=0;i<13;i++){ printf("%c",205);}
        gotoxy(87,3); printf("%c",201); gotoxy(87,5); printf("%c",200); gotoxy(100,3); printf("%c",187); gotoxy(100,5); printf("%c",188);
        gotoxy(88,4); printf("SUPER COPTER");
        setcolor(15,0);
        gotoxy(87,7); printf("NAME: %s",name);
        gotoxy(86,8); 		//generate border status
        for(b=0;b<=15;b++) { setcolor(14,0); printf("%c",236); setcolor(15,0);}
        gotoxy(86,16);
        for(b=0;b<=15;b++) { setcolor(14,0); printf("%c",236); setcolor(15,0);}

        for(i=9;i<=15;i++){
            setcolor(14,0);
            gotoxy(86,i);
            printf("%c",236);
            gotoxy(101,i);
            printf("%c",236);
            setcolor(15,0);
        }
        gotoxy(83,22);printf(" DEV: Nitinon Penglao");  //show developer name
        gotoxy(83,23);printf(" Code: 59010734");
        gotoxy(83,24);printf(" CE 55 @KMITL");
        copter_art(90,19,0);
        //************************set value****************************************
        enemy_s2[0].status=0;
        enemy_s2[0].check=1;
        enemy_s2[0].space=9;
        draw_enemy(enemy_s2[0].x=80,enemy_s2[0].y=rand()%10+5);
        for(i=1;i<5;i++){
            enemy_s2[i].x=enemy_s2[i-1].x+16;
            enemy_s2[i].y=rand()%10+5;
            enemy_s2[i].status=0;
            enemy_s2[i].space=9;
            enemy_s2[i].check=1;
        }
   do{
        //generate border
       gotoxy(0,1);
        for(i=0;i<=81;i++) {setcolor(5,0);printf("%c",254); setcolor(15,0);}
        gotoxy(0,24);
        for(i=0;i<=81;i++) {setcolor(5,0);printf("%c",254); setcolor(15,0);}
	    //set header stage2
        gotoxy(90,11);
        printf("LIFE: %d",life);
        gotoxy(90,13);
        printf("SCORE: %d",score);
        //-------------------pole Movement
        for(j=0;j<5;j++){
            enemy_s2[j].x--;
            if(check_del_space!=0&&check_del_space%5==0){ //increase space when score%5=0
                    check_del_space%=5;
                    del_space++;
            }
        	if(enemy_s2[j].x==79){ enemy_s2[j].space-=del_space; enemy_s2[j].status=1; enemy_s2[j].check=1;}  //visible pole
        	if(enemy_s2[j].x<=0){       				//check when hit left border
              enemy_s2[j].status=0;
              enemy_s2[j].x=80;
              for(i=2;i<24;i++) clear_enemy(1,i);
            }
    		if(enemy_s2[j].status==1){
            for(i=2;i<=enemy_s2[j].y;i++){ //upper space
                draw_enemy(enemy_s2[j].x,i);  //draw and clear pole
                clear_enemy(enemy_s2[j].x+1,i);
            }
            for(i=enemy_s2[j].y+enemy_s2[j].space;i<24;i++){ //lower space
                draw_enemy(enemy_s2[j].x,i);  //draw and clear pole
                clear_enemy(enemy_s2[j].x+1,i);
            }
        }
	       if(((copter.x==enemy_s2[j].x||copter.x+1==enemy_s2[j].x||copter.x+2==enemy_s2[j].x||copter.x+3==enemy_s2[j].x)&&(copter.y<=enemy_s2[j].y||copter.y>=enemy_s2[j].y+enemy_s2[j].space))&&enemy_s2[j].check==1){
	        enemy_s2[j].check=0;  //detect copter and pole life --
	        life--;
	        Beep(200,400);
	        }
	        if(enemy_s2[j].check==1&&(copter.x==enemy_s2[j].x||copter.x+1==enemy_s2[j].x)){      //check pole score++
	                enemy_s2[j].check=0;
	                score++;
	                check_del_space++;
	            }
        }
 //-------------------control--------------------------------
        if(kbhit()){
                ch=getch();
                summ++;
            if(summ>2)summ=2;
            if(ch=='W'||ch=='w')game_control(1);
            if((ch=='D'||ch=='d'&&copter.x<72)&&summ>1) game_control(3);
            if((ch=='A'||ch=='a')&&summ>1&&copter.x>1) game_control(2);
            if(ch!='w'&&ch!='a'&&ch!='d'&&ch!='A'&&ch!='D')game_control(0);
                fflush(stdin);
            }else game_control(0);
        count_e++;
        Sleep(50);

}while (ch!='x'&&score<25&&life>0&&copter.y!=24&&copter.y!=2);

        Beep(1000,1000);
        system("cls");

        score2=score*10;

        if(story_mode==1){
         gotoxy(36,6); printf("Do you want continues to Stage3 ?");
         if(c_continue()==1)stage3();
        else main_menu();
        }else{
        if(score>=20)win();
            else if(score<20)  lose();
            main_menu();
        }

        return 0;
}
int stage3(){
        char ch='.';
        int i,j,k,b;
        int life=5,score=0,life_boss=20;
        int st_S=0,count=1;
        int drop=0,turn=1,standby=0,formation=3;
        int magazine=8,B_ullet=5,status_boss=0,b_direction,generate_enemy=0;
         summ=0;
         srand( time( NULL ) );
        if(story_mode!=1) entername();
         ready();
         setcursor(0);
        b_direction=3; //boss direction
        gotoxy(20,0); setcolor(0,15); printf("STAGE3 : *********** LAST STAGE **********");setcolor(15,0);
        //generate border
        gotoxy(0,1);
        for(i=0;i<=81;i++) {setcolor(2,0);printf("%c",254); setcolor(15,0);}
        gotoxy(0,24);
        for(i=0;i<=81;i++) {setcolor(2,0);printf("%c",254); setcolor(15,0);}

        for(i=1;i<=24;i++){
            setcolor(2,2);
            gotoxy(0,i);
            printf("%c",254);
            gotoxy(81,i);
            printf("%c",254);
            setcolor(15,0);
        }
        setcolor(10,0); gotoxy(86,4); printf("%c%c",205,185); gotoxy(100,4); printf("%c%c",204,205);
        gotoxy(88,3);for(i=0;i<13;i++){ printf("%c",205);}
        gotoxy(88,5);for(i=0;i<13;i++){ printf("%c",205);}
        gotoxy(87,3); printf("%c",201); gotoxy(87,5); printf("%c",200); gotoxy(100,3); printf("%c",187); gotoxy(100,5); printf("%c",188);
        gotoxy(88,4); printf("SUPER COPTER");
        setcolor(15,0);
        gotoxy(87,7); printf("NAME: %s",name);
        gotoxy(86,8); //generate border status
        for(b=0;b<=15;b++) { setcolor(14,0); printf("%c",236); setcolor(15,0);}
        gotoxy(86,16);
        for(b=0;b<=15;b++) { setcolor(14,0); printf("%c",236); setcolor(15,0);}

        for(i=9;i<=15;i++){
            setcolor(14,0);
            gotoxy(86,i);
            printf("%c",236);
            gotoxy(101,i);
            printf("%c",236);
            setcolor(15,0);
        }
        gotoxy(83,22);printf(" DEV: Nitinon Penglao");  //show developer name
        gotoxy(83,23);printf(" Code: 59010734");
        gotoxy(83,24);printf(" CE 55 @KMITL");
        copter_art(90,19,0);

        draw_ship(copter.x=5,copter.y=10);
        gotoxy(0,1);
        for(i=0;i<5;i++) enemy_bullet[i].status_b=1;

        int yyy=0;
        current_time[3]=clock();
    do{
        gotoxy(88,10);
        printf("BULLET: %d/%d",B_ullet,magazine);
        gotoxy(88,12);
        printf("SCORE: %d",score);
        gotoxy(88,14);
        printf("LIFE: %d",life);
        if(c_enemy!=0&&c_enemy%5==0&&status_boss!=1){

            c_enemy=0;
            formation=rand()%3+1;
        if(formation==1){
            enemy_s3[0].x=79;
            enemy_s3[0].y=2;
            enemy_s3[0].turn=1;
            enemy_s3[0].status=1;
            draw_enemy(enemy_s3[0].x,enemy_s3[0].y);
        for(i=1;i<5;i++){
            enemy_s3[i].x=79;
            enemy_s3[i].y=enemy_s3[i-1].y+5;
            enemy_s3[i].turn=1;
            enemy_s3[i].status=1;
            draw_enemy(enemy_s3[i].x,enemy_s3[i].y);
            }
        }
        if(formation==2){
            enemy_s3[0].x=79;
            enemy_s3[0].y=rand()%3+3;
            enemy_s3[0].turn=1;
            enemy_s3[0].status=1;
            draw_enemy(enemy_s3[0].x,enemy_s3[0].y);
        for(i=1;i<5;i++){
            enemy_s3[i].x=79;
            enemy_s3[i].y=enemy_s3[i-1].y+(rand()%3+3);
            enemy_s3[i].turn=1;
            enemy_s3[i].status=1;
            draw_enemy(enemy_s3[i].x,enemy_s3[i].y);
           }
        }
        if(formation==3){                                           //set enemy formation 3
            enemy_s3[0].turn=1;
            enemy_s3[0].status=1;
            draw_enemy(enemy_s3[0].x=70,enemy_s3[0].y=2);
        for(i=1;i<3;i++){
            enemy_s3[i].x=enemy_s3[i-1].x+5;
            enemy_s3[i].y=enemy_s3[i-1].y+5;
            enemy_s3[i].turn=1;
            enemy_s3[i].status=1;
            draw_enemy(enemy_s3[i].x,enemy_s3[i].y);
           }
           enemy_s3[2].turn=rand()%2;
        for(i=3;i<5;i++){
            enemy_s3[i].x=enemy_s3[i-1].x-5;
            enemy_s3[i].y=enemy_s3[i-1].y+5;
            enemy_s3[i].turn=0;
            enemy_s3[i].status=1;
            draw_enemy(enemy_s3[i].x,enemy_s3[i].y);
           }
         }
        }

        if((int)count_time(current_time[3])%10==0&&ammo.status==0){ //set status AMMO
        ammo.x=rand()%70+3;
        ammo.y=3;
        ammo.status=1;
        }
        if((int)count_time(current_time[3])%40==0&&posion.status==0){ //set status HEAL
        posion.x=rand()%70+3;
        posion.y=3;
        posion.status=1;
        }
        if(ammo.status==1&&detect(1,copter.x,copter.y,ammo.x+4,ammo.y+4)){ //check Ammo detect copter
            if(magazine<9)magazine++;
            Beep(300,200);
            ammo.status=0;
            clear_heal(ammo.x,ammo.y);
        }
        if(posion.status==1&&detect(1,copter.x,copter.y,posion.x+4,posion.y+4)){ //check POSION detect copter
            life++;
            Beep(300,200);
            posion.status=0;
            clear_heal(posion.x,posion.y);
        }
        if(posion.status==1&&detect(1,copter.x,copter.y,posion.x+4,posion.y+4)){ //check POSION detect copter
            life++;
            Beep(300,200);
            posion.status=0;
            clear_heal(posion.x,posion.y);
        }
          if(posion.status==1&&count%10==0){                   //HEAL movement
            draw_heal(posion.x,++posion.y,'H');
            gotoxy(posion.x,posion.y-1);
            printf("      ");
            gotoxy(posion.x-1,posion.y);
            printf(" ");
            gotoxy(posion.x+6,posion.y);
            printf(" ");
            }
        if(ammo.status==1&&count%10==0){  				                 //Ammo movement
            draw_heal(ammo.x,++ammo.y,'A');
            gotoxy(ammo.x,ammo.y-1);
            printf("      ");
            gotoxy(ammo.x-1,ammo.y);
            printf(" ");
            gotoxy(ammo.x+6,ammo.y);
            printf(" ");
            }
        if(posion.y+5==24&&posion.status==1) { posion.status=0; clear_heal(posion.x,posion.y);}
        if(ammo.y+5==24&&ammo.status==1) { ammo.status=0; clear_heal(ammo.x,ammo.y);}
//-------------------control--------------------------------
         if(kbhit()){
        ch=getch();
        summ++;

    if(summ>2)summ=2;
    if(ch=='W'||ch=='w')game_control(1);
    if((ch=='D'||ch=='d'&&copter.x<72)&&summ>1) game_control(5);
    if((ch=='A'||ch=='a'&&copter.x>1)&&summ>1) game_control(2);
    if(ch=='j'&&standby!=5&&B_ullet!=0){
        for(j=0;j<5;j++){
            if(bullet[j].status_b==0)break;
        }
            bullet[j].x=copter.x+5;
            bullet[j].y=copter.y;
            bullet[j].status_b=1;
            draw_bullet(bullet[j].x,bullet[j].y);
            standby++;
            B_ullet--;
            }
    if(ch=='r'&&B_ullet==0&&magazine!=0){ magazine--; B_ullet=5; }
    if(ch!='w'&&ch!='a'&&ch!='d'&&ch!='j')game_control(0);
            fflush(stdin);
        }else game_control(0);
////////////////////////////////////////////////////////////////////////////////
    for (i=0;i<5;i++){
                if(enemy_s3[i].status==1&&detect(1,copter.x,copter.y,enemy_s3[i].x,enemy_s3[i].y)==1){ //detect copter and enemy
                    life--;
                    c_enemy++;
                    clear_enemy(enemy_s3[i].x,enemy_s3[i].y);
                    if(c_enemy==5){generate_enemy++;}
                    enemy_s3[i].status=0;
                    Beep(300,1000);
                }
            }

    for(j=0;j<5;j++){
            if(bullet[j].status_b==1){
                draw_bullet(++bullet[j].x,bullet[j].y);
                clear_enemy(bullet[j].x-1,bullet[j].y);

                for (i=0;i<5;i++){      //detect bullet enemy and bullet copter
                        if(enemy_bullet[i].status_b==0&&detect(2,bullet[j].x,bullet[j].y,enemy_bullet[i].x,enemy_bullet[i].y)){
                           enemy_bullet[i].status_b=1;
                        }
                }
            }
            if(bullet[j].x==80){       //out of border
                clear_enemy(bullet[j].x,bullet[j].y);
                bullet[j].status_b=0;
                bullet[j].x=0;
                standby--;
            }
    		for (i=0;i<5;i++){			//detect bullet and enemy
             	if(enemy_s3[i].status==1&&bullet[j].x==enemy_s3[i].x && bullet[j].y==enemy_s3[i].y) {
                	enemy_s3[i].status=0;
               	    clear_enemy(enemy_s3[i].x,enemy_s3[i].y);
               	    c_enemy++;
               	    if(c_enemy==5){generate_enemy++;}
                    score++;
            		}
           		}
           if((bullet[j].x>boss.x&&bullet[j].x<boss.x+5)&&(bullet[j].y>=boss.y&&bullet[j].y<boss.y+5)) {
		   		life_boss--;


                for(i=60;i>life_boss+20;i-=2) {gotoxy(i,3); printf("  ");}

		   		clear_enemy(bullet[j].x,bullet[j].y);
                bullet[j].status_b=0;
		   		bullet[j].x=0;
		   		standby--;
		   }
         }
            if(status_boss==0&&generate_enemy>=4) {
			draw_boss(boss.x=rand()%20+50,boss.y=rand()%15+5);
			status_boss=1;
				for(k=0;k<20;k++) boss_bullet[k].status_b=0;
			}

			// enemy movement
            if(count%5==0&&status_boss==0){
                int nnn;
                nnn=rand()%5; //random shoot bullet enemy
                if(enemy_bullet[nnn].status_b==1&&enemy_s3[nnn].status==1){ //draw enemy bullet
                draw_bullet2(enemy_bullet[nnn].x=enemy_s3[nnn].x-2,enemy_bullet[nnn].y=enemy_s3[nnn].y);
                enemy_bullet[nnn].status_b=0;
            }
            //formation of enemy_movement
                if(formation!=2)enemy_movement(formation);
                if(formation==2&&count%20==0)
                enemy_movement(formation);
           //  count%=5;
            }
            //detect helicopter
            for (i=0;i<5;i++){
                if(enemy_bullet[i].status_b==0&&detect(1,copter.x,copter.y,enemy_bullet[i].x,enemy_bullet[i].y)==1){
                   life--;
                   clear_enemy(enemy_bullet[i].x,enemy_bullet[i].y);

                   enemy_bullet[i].status_b=1;
                   Beep(300,1000);
                   clear_enemy(enemy_bullet[i].x+1,enemy_bullet[i].y);
            }
            //detect bullet out line
                if(enemy_bullet[i].x<=1){
                   clear_enemy(enemy_bullet[i].x,enemy_bullet[i].y);
                   enemy_bullet[i].status_b=1;
                   }
                if( enemy_bullet[i].status_b==0){ //bullet enemy movement
                   draw_bullet2(--enemy_bullet[i].x,enemy_bullet[i].y);
                   clear_enemy(enemy_bullet[i].x+1,enemy_bullet[i].y);
                   }
            }
			// The Boss is coming
            if(status_boss==1){
                gotoxy(10,3);
                printf("LIFE BOSS: ");
                gotoxy(20,3);
                for(i=0;i<life_boss;i++) { setcolor(13,0); printf("%c ",177); setcolor(15,0); }
            }


			if(status_boss==1&&count%5 ==0) {
                    if(boss.x>=74) b_direction=1;
                    if(boss.x<=21) b_direction=2;
                    if(boss.y<=4) b_direction=4;
                    if(boss.y>=19) b_direction=3;
                    boss_movement(b_direction);
            }
			if(count%20==0) { b_direction=rand()%4+1;}

			if(status_boss==1&&count%10==0){
				for(k=0;k<20;k++) {
				if(count%20==0&&boss_bullet[k].status_b==0){
					boss_bullet[k].status_b=1;
					draw_bullet2(boss_bullet[k].x=boss.x-3,boss_bullet[k].y=boss.y+rand()%5);
					k=20;
				}
				}
			}
			for(k=0;k<20;k++) {
				if(boss_bullet[k].status_b==1){
					draw_bullet2(--boss_bullet[k].x,boss_bullet[k].y);
					clear_enemy(boss_bullet[k].x+1,boss_bullet[k].y);
				}
				for(i=0;i<5;i++)
                    if(bullet[i].status_b==1&&(boss_bullet[k].x==bullet[i].x&&boss_bullet[k].y==bullet[i].y||boss_bullet[k].x==bullet[i].x+1&&boss_bullet[k].y==bullet[i].y)){
                    clear_enemy(boss_bullet[k].x,boss_bullet[k].y);
                    clear_enemy(bullet[i].x,bullet[i].y);
                        boss_bullet[k].status_b=0;
                        bullet[i].status_b=0;
                        standby--;
                    }
				if(boss_bullet[k].x==1) {
                    boss_bullet[k].status_b=0;
                    clear_enemy(boss_bullet[k].x,boss_bullet[k].y);
				}
                if(detect(1,copter.x,copter.y,boss_bullet[k].x,boss_bullet[k].y)&&boss_bullet[k].status_b==1)
                {
                    boss_bullet[k].status_b=0;
                    Beep(200,300);
                    life--;
                    clear_enemy(boss_bullet[k].x,boss_bullet[k].y);
                }
			}
            if((copter.x+4>boss.x&&copter.x+4<boss.x+5)&&(copter.y>boss.y&&copter.y<boss.y+5)){
                Beep(1000,300);
                life--;
                clear_ship(copter.x,copter.y);
                draw_ship(copter.x=5,copter.y=10);

            }
			if(copter.y==24||copter.y==2){ //if copter hit with border
                Beep(1000,300);
                life--;
                clear_ship(copter.x,copter.y);
                draw_ship(copter.x=5,copter.y=10);
                gotoxy(0,1);
                    for(i=0;i<=81;i++) {setcolor(2,0);printf("%c",254); setcolor(15,0);}
                gotoxy(0,24);
                    for(i=0;i<=81;i++) {setcolor(2,0);printf("%c",254); setcolor(15,0);}
                Sleep(200);

			}
			count++;

        Sleep(50);
}while (ch!='x'&&life>0&&life_boss>0);
    system("cls");
    if(life==0)lose(); //if die life=0
    else win(); //if win

    if(life!=0)score3=score+20+(life*10); //calculate score

    if(story_mode==1){record(score1+score2+score3); //sum score
        if(life_boss<=0&&ch!='x')win();
        else lose();
        main_menu();
    }
    else{ //do you want to continue
            if(c_continue()==1)stage3();
            else main_menu();
        }
}
int main(){
    int i,j;
    sett();
    setcursor(0);
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    intro();
    getch();
    system("cls");
    main_menu();
    system("cls");
    return 0;
}


