# include "iGraphics.h"
# include "gl.h"
# include<stdio.h>
# include<stdlib.h>
# include<string.h>

typedef struct
{
    char name[80];
    int points;
} h_s;

h_s hscor[7];

int len = 0, mode = 0, in = 0;
char str[80], scr[10], i_scr[10];
int i_dx = 2, i_dy = 3, i_a = 25, i_platform_d = 50, i_platform_h = 5, i_ball_r = 4, i_ball_x = 200, i_ball_y = 99, i_platform_x = 175, i_platform_y = 90;
int ball_x = 200, ball_y = 99;
int dx = 2, dy = 3;
int mood = 0, level = 1, sound, r_level, g_s = 0, l_s, flag = 0, r_score = 0;
int cnt = 3;
int r_dx, r_dy;
int score = 0,score_finish=1;
int hori_x[624]= {8},vert_x[650]= {0},hori_y[624]= {330},vert_y[650]= {338},steel_x[624]= {8},steel_y[624]= {330};
int hbrickcount[624]= {0},vbrickcount[650]= {0},steelcount[624]= {0};
int platform_x = 175,  platform_y = 90, platform_d = 50, platform_h = 5, ball_r = 4, a = 25;
int i,j;

void name_write()
{
    FILE *fp;
    fp = fopen("score.txt","a");
    fprintf(fp,"%s %d\n",hscor[5].name,hscor[5].points);
    fclose(fp);
}
void name_read()
{
    FILE* fp1;
    fp1 = fopen("score.txt","r");
    int y, z;
    for(y = 0; y < 6; y++)
        fscanf(fp1,"%s %d",hscor[y].name,&hscor[y].points);
    fclose(fp1);
    FILE* fp2;
    fp2 = fopen("score.txt","w");
    for(y = 0; y < 6; y++)
    {
        for(z = y + 1; z < 6; z++)
        {
            if(hscor[y].points < hscor[z].points)
            {
                hscor[6] = hscor[y];
                hscor[y] = hscor[z];
                hscor[z] = hscor[6];
            }
        }
    }
    for(y = 0; y < 5; y++)
    {
        fprintf(fp2,"%s %d\n",hscor[y].name,hscor[y].points);
    }
    fclose(fp2);

    iShowBMP(0,0,"high_score.bmp");
    int kk = 0, ia;
    for(i = 0; i < 5; i++)
    {
        iSetColor(0,255,0);
        iText(70,572,"Name",GLUT_BITMAP_HELVETICA_18);
        iText(260,572,"Score",GLUT_BITMAP_HELVETICA_18);
        ia = hscor[i].points;
        itoa(ia,i_scr,10);
        iSetColor(255,255,255);
        iText(70,515+kk,hscor[i].name,GLUT_BITMAP_HELVETICA_18);
        iText(260,515+kk,i_scr,GLUT_BITMAP_HELVETICA_18);
        kk -= 65;
    }
}
int position,Save_Game=0;
int collision_counting_start_expand_1=0,collision_counting_start_fastball_1=0,collision_counting_start_slowball_1=0,collision_counting_start_shrink_1=0,collision_count_millisecond_expand_1=0,collision_count_millisecond_fastball_1=0,collision_count_millisecond_slowball_1=0,collision_count_millisecond_shrink_1=0;
int collision_counting_start_expand_2=0,collision_counting_start_fastball_2=0,collision_counting_start_slowball_2=0,collision_counting_start_shrink_2=0,collision_count_millisecond_expand_2=0,collision_count_millisecond_fastball_2=0,collision_count_millisecond_slowball_2=0,collision_count_millisecond_shrink_2=0;
int collision_counting_start_expand_3=0,collision_counting_start_fastball_3=0,collision_counting_start_slowball_3=0,collision_counting_start_shrink_3=0,collision_count_millisecond_expand_3=0,collision_count_millisecond_fastball_3=0,collision_count_millisecond_slowball_3=0,collision_count_millisecond_shrink_3=0;
int collision_counting_start_expand_4=0,collision_counting_start_fastball_4=0,collision_counting_start_slowball_4=0,collision_counting_start_shrink_4=0,collision_count_millisecond_expand_4=0,collision_count_millisecond_fastball_4=0,collision_count_millisecond_slowball_4=0,collision_count_millisecond_shrink_4=0;
int collision_counting_start_expand_5=0,collision_counting_start_fastball_5=0,collision_counting_start_slowball_5=0,collision_counting_start_shrink_5=0,collision_count_millisecond_expand_5=0,collision_count_millisecond_fastball_5=0,collision_count_millisecond_slowball_5=0,collision_count_millisecond_shrink_5=0;

int mood_danger_1=0,mood_danger_effect_1=1,mood_extra_life_effect_1=1,mood_expand_1=0,mood_extralife_1=0,mood_fastball_1=0,mood_shrink_paddle_1=0,mood_slow_ball_1=0;
int mood_danger_2=0,mood_danger_effect_2=1,mood_extra_life_effect_2=1,mood_expand_2=0,mood_extralife_2=0,mood_fastball_2=0,mood_shrink_paddle_2=0,mood_slow_ball_2=0;
int mood_danger_3=0,mood_danger_effect_3=1,mood_extra_life_effect_3=1,mood_expand_3=0,mood_extralife_3=0,mood_fastball_3=0,mood_shrink_paddle_3=0,mood_slow_ball_3=0;
int mood_danger_4=0,mood_danger_effect_4=1,mood_extra_life_effect_4=1,mood_expand_4=0,mood_extralife_4=0,mood_fastball_4=0,mood_shrink_paddle_4=0,mood_slow_ball_4=0;
int mood_danger_5=0,mood_danger_effect_5=1,mood_extra_life_effect_5=1,mood_expand_5=0,mood_extralife_5=0,mood_fastball_5=0,mood_shrink_paddle_5=0,mood_slow_ball_5=0;

///level detecting
void _score();
void platform();
void coordinate();
void f_score();
void alldeactive();
void life();
void allbrick();
void level1();
void collision();
void ballChange();
void draw_danger_icon();
void draw_expand_scatter();
void draw_fastball_icon();
void draw_slowball_icon();
void draw_shrink_icon();
void draw_extralife_icon();
///adding new final functions.These are level functions
void level1_icon_change();
void level2_icon_change();
void level3_icon_change();
void level4_icon_change();
void level5_icon_change();
void level1();
void level2();
void level3();
void level4();
void level5();
void all_mood_off()
{
    if(r_level==1)
    {
        mood_expand_1=0;
        mood_danger_1=0;
        mood_fastball_1=0;
        mood_slow_ball_1=0;
        mood_shrink_paddle_1=0;
        mood_extralife_1=0;
    }
    else  if(r_level==2)
    {
        mood_expand_2=0;
        mood_danger_2=0;
        mood_fastball_2=0;
        mood_slow_ball_2=0;
        mood_shrink_paddle_2=0;
        mood_extralife_2=0;
    }
    else  if(r_level==3)
    {
        mood_expand_3=0;
        mood_danger_3=0;
        mood_fastball_3=0;
        mood_slow_ball_3=0;
        mood_shrink_paddle_3=0;
        mood_extralife_3=0;
    }
    else if(r_level==4)
    {
        mood_expand_4=0;
        mood_danger_4=0;
        mood_fastball_4=0;
        mood_slow_ball_4=0;
        mood_shrink_paddle_4=0;
        mood_extralife_4=0;
    }
    else  if(r_level==5)
    {
        mood_expand_5=0;
        mood_danger_5=0;
        mood_fastball_5=0;
        mood_slow_ball_5=0;
        mood_shrink_paddle_5=0;
        mood_extralife_5=0;
    }
}
/// writing coordinates for special icon drop for each level
int expand_x_1,   expand_y_1,    danger_x_1,   danger_y_1,  fastball_x_1,    fastball_y_1;
int extra_life_x_1,  extra_life_y_1, shrink_paddle_x_1,  shrink_paddle_y_1;
int slow_ball_x_1,  slow_ball_y_1;

int expand_x_2,   expand_y_2,    danger_x_2,   danger_y_2,  fastball_x_2,fastball_y_2;
int extra_life_x_2,  extra_life_y_2, shrink_paddle_x_2,  shrink_paddle_y_2;
int slow_ball_x_2,  slow_ball_y_2;

int expand_x_3,   expand_y_3,   danger_x_3,   danger_y_3,  fastball_x_3,fastball_y_3;
int extra_life_x_3,  extra_life_y_3, shrink_paddle_x_3,  shrink_paddle_y_3;
int slow_ball_x_3,  slow_ball_y_3;

int expand_x_4,   expand_y_4,    danger_x_4,   danger_y_4,  fastball_x_4,fastball_y_4;
int extra_life_x_4,  extra_life_y_4, shrink_paddle_x_4,  shrink_paddle_y_4;
int slow_ball_x_4,  slow_ball_y_4;

int expand_x_5,   expand_y_5,    danger_x_5,   danger_y_5, fastball_x_5,fastball_y_5;
int extra_life_x_5,  extra_life_y_5, shrink_paddle_x_5,  shrink_paddle_y_5;
int slow_ball_x_5,  slow_ball_y_5;

///file operation for saving game
void save_game()
{
    FILE *fp;
    fp=fopen("Brick Breaker save.txt","w");
    fprintf(fp,"%d %d\n",ball_x,ball_y);
    fprintf(fp,"%d %d %d\n",platform_x, platform_y,  platform_d);
    fprintf(fp,"%d\n",score);
    fprintf(fp,"%d\n",cnt);
    fprintf(fp,"%d\n",r_level);
    for(int i=0; i<624; i++)
        fprintf(fp,"%d ",hbrickcount[i]);
    fprintf(fp,"\n");
    for(int i=0; i<624; i++)
        fprintf(fp,"%d ",steelcount[i]);
    fprintf(fp,"\n");
    for(int i=0; i<650; i++)
        fprintf(fp,"%d ",vbrickcount[i]);
    fprintf(fp,"\n");

    if(r_level==1)
    {
        fprintf(fp,"%d\n",mood_expand_1);
        fprintf(fp,"%d\n",collision_counting_start_expand_1);
        fprintf(fp,"%d\n",collision_count_millisecond_expand_1);
        fprintf(fp,"%d\n",expand_y_1);

        fprintf(fp,"%d\n",mood_shrink_paddle_1);
        fprintf(fp,"%d\n",collision_counting_start_shrink_1);
        fprintf(fp,"%d\n",collision_count_millisecond_shrink_1);
        fprintf(fp,"%d\n",shrink_paddle_y_1);

        fprintf(fp,"%d\n",mood_danger_1);
        fprintf(fp,"%d\n",mood_danger_effect_1);
        fprintf(fp,"%d\n",danger_y_1);

        fprintf(fp,"%d\n",mood_extralife_1);
        fprintf(fp,"%d\n",mood_extra_life_effect_1);
        fprintf(fp,"%d\n",extra_life_y_1);

        fprintf(fp,"%d\n",mood_fastball_1);
        fprintf(fp,"%d\n",collision_counting_start_fastball_1);
        fprintf(fp,"%d\n",collision_count_millisecond_fastball_1);
        fprintf(fp,"%d\n",fastball_y_1);

        fprintf(fp,"%d\n",mood_slow_ball_1);
        fprintf(fp,"%d\n",collision_counting_start_slowball_1);
        fprintf(fp,"%d\n",collision_count_millisecond_slowball_1);
        fprintf(fp,"%d\n",slow_ball_y_1);
    }
    if(r_level==2)
    {
        fprintf(fp,"%d\n",mood_expand_2);
        fprintf(fp,"%d\n",collision_counting_start_expand_2);
        fprintf(fp,"%d\n",collision_count_millisecond_expand_2);

        fprintf(fp,"%d\n",mood_shrink_paddle_2);
        fprintf(fp,"%d\n",collision_counting_start_shrink_2);
        fprintf(fp,"%d\n",collision_count_millisecond_shrink_2);

        fprintf(fp,"%d\n",mood_danger_2);
        fprintf(fp,"%d\n",mood_danger_effect_2);

        fprintf(fp,"%d\n",mood_extralife_2);
        fprintf(fp,"%d\n",mood_extra_life_effect_2);

        fprintf(fp,"%d\n",mood_fastball_2);
        fprintf(fp,"%d\n",collision_counting_start_fastball_2);
        fprintf(fp,"%d\n",collision_count_millisecond_fastball_2);

        fprintf(fp,"%d\n",mood_slow_ball_2);
        fprintf(fp,"%d\n",collision_counting_start_slowball_2);
        fprintf(fp,"%d\n",collision_count_millisecond_slowball_2);
    }
    if(r_level==3)
    {
        fprintf(fp,"%d\n",mood_expand_3);
        fprintf(fp,"%d\n",collision_counting_start_expand_3);
        fprintf(fp,"%d\n",collision_count_millisecond_expand_3);

        fprintf(fp,"%d\n",mood_shrink_paddle_3);
        fprintf(fp,"%d\n",collision_counting_start_shrink_3);
        fprintf(fp,"%d\n",collision_count_millisecond_shrink_3);

        fprintf(fp,"%d\n",mood_danger_3);
        fprintf(fp,"%d\n",mood_danger_effect_3);

        fprintf(fp,"%d\n",mood_extralife_3);
        fprintf(fp,"%d\n",mood_extra_life_effect_3);

        fprintf(fp,"%d\n",mood_fastball_3);
        fprintf(fp,"%d\n",collision_counting_start_fastball_3);
        fprintf(fp,"%d\n",collision_count_millisecond_fastball_3);

        fprintf(fp,"%d\n",mood_slow_ball_3);
        fprintf(fp,"%d\n",collision_counting_start_slowball_3);
        fprintf(fp,"%d\n",collision_count_millisecond_slowball_3);
    }
    if(r_level==4)
    {
        fprintf(fp,"%d\n",mood_expand_4);
        fprintf(fp,"%d\n",collision_counting_start_expand_4);
        fprintf(fp,"%d\n",collision_count_millisecond_expand_4);

        fprintf(fp,"%d\n",mood_shrink_paddle_4);
        fprintf(fp,"%d\n",collision_counting_start_shrink_4);
        fprintf(fp,"%d\n",collision_count_millisecond_shrink_4);

        fprintf(fp,"%d\n",mood_danger_4);
        fprintf(fp,"%d\n",mood_danger_effect_4);

        fprintf(fp,"%d\n",mood_extralife_4);
        fprintf(fp,"%d\n",mood_extra_life_effect_4);

        fprintf(fp,"%d\n",mood_fastball_4);
        fprintf(fp,"%d\n",collision_counting_start_fastball_4);
        fprintf(fp,"%d\n",collision_count_millisecond_fastball_4);

        fprintf(fp,"%d\n",mood_slow_ball_4);
        fprintf(fp,"%d\n",collision_counting_start_slowball_4);
        fprintf(fp,"%d\n",collision_count_millisecond_slowball_4);

    }
    if(r_level==5)
    {
        fprintf(fp,"%d\n",mood_expand_5);
        fprintf(fp,"%d\n",collision_counting_start_expand_5);
        fprintf(fp,"%d\n",collision_count_millisecond_expand_5);

        fprintf(fp,"%d\n",mood_shrink_paddle_5);
        fprintf(fp,"%d\n",collision_counting_start_shrink_5);
        fprintf(fp,"%d\n",collision_count_millisecond_shrink_5);

        fprintf(fp,"%d\n",mood_danger_5);
        fprintf(fp,"%d\n",mood_danger_effect_5);

        fprintf(fp,"%d\n",mood_extralife_5);
        fprintf(fp,"%d\n",mood_extra_life_effect_5);

        fprintf(fp,"%d\n",mood_fastball_5);
        fprintf(fp,"%d\n",collision_counting_start_fastball_5);
        fprintf(fp,"%d\n",collision_count_millisecond_fastball_5);

        fprintf(fp,"%d\n",mood_slow_ball_5);
        fprintf(fp,"%d\n",collision_counting_start_slowball_5);
        fprintf(fp,"%d\n",collision_count_millisecond_slowball_5);
    }
}

void play_saved_game()
{
    FILE *playgame;
    playgame=fopen("Brick Breaker save.txt","r");
    fscanf(playgame,"%d%d",&ball_x,&ball_y);
    fscanf(playgame,"%d%d%d",&platform_x, &platform_y,  &platform_d);
    fscanf(playgame,"%d",&score);
    fscanf(playgame,"%d",&cnt);
    fscanf(playgame,"%d",&r_level);
    for(int i=0; i<624; i++)
        fscanf(playgame,"%d",&hbrickcount[i]);
    for(int i=0; i<624; i++)
         fscanf(playgame,"%d",&steelcount[i]);
    for(int i=0; i<650; i++)
        fscanf(playgame,"%d",&vbrickcount[i]);

    if(r_level==1)
    {
        fscanf(playgame,"%d",&mood_expand_1);
        fscanf(playgame,"%d",&collision_counting_start_expand_1);
        fscanf(playgame,"%d",&collision_count_millisecond_expand_1);
        fscanf(playgame,"%d",&expand_y_1);

        fscanf(playgame,"%d",&mood_shrink_paddle_1);
        fscanf(playgame,"%d",&collision_counting_start_shrink_1);
        fscanf(playgame,"%d",&collision_count_millisecond_shrink_1);
        fscanf(playgame,"%d",&shrink_paddle_y_1);

        fscanf(playgame,"%d",&mood_danger_1);
        fscanf(playgame,"%d",&mood_danger_effect_1);
        fscanf(playgame,"%d",&danger_y_1);

        fscanf(playgame,"%d",&mood_extralife_1);
        fscanf(playgame,"%d",&mood_extra_life_effect_1);
        fscanf(playgame,"%d",&extra_life_y_1);

        fscanf(playgame,"%d",&mood_fastball_1);
        fscanf(playgame,"%d",&collision_counting_start_fastball_1);
        fscanf(playgame,"%d",&collision_count_millisecond_fastball_1);
        fscanf(playgame,"%d",&fastball_y_1);

        fscanf(playgame,"%d",&mood_slow_ball_1);
        fscanf(playgame,"%d",&collision_counting_start_slowball_1);
        fscanf(playgame,"%d",&collision_count_millisecond_slowball_1);
        fscanf(playgame,"%d",&slow_ball_y_1);
    }
    if(r_level==2)
    {
        fscanf(playgame,"%d",&mood_expand_2);
        fscanf(playgame,"%d",&collision_counting_start_expand_2);
        fscanf(playgame,"%d",&collision_count_millisecond_expand_2);

        fscanf(playgame,"%d",&mood_shrink_paddle_2);
        fscanf(playgame,"%d",&collision_counting_start_shrink_2);
        fscanf(playgame,"%d",&collision_count_millisecond_shrink_2);

        fscanf(playgame,"%d",&mood_danger_2);
        fscanf(playgame,"%d",&mood_danger_effect_2);

        fscanf(playgame,"%d",&mood_extralife_2);
        fscanf(playgame,"%d",&mood_extra_life_effect_2);

        fscanf(playgame,"%d",&mood_fastball_2);
        fscanf(playgame,"%d",&collision_counting_start_fastball_2);
        fscanf(playgame,"%d",&collision_count_millisecond_fastball_2);

        fscanf(playgame,"%d",&mood_slow_ball_2);
        fscanf(playgame,"%d",&collision_counting_start_slowball_2);
        fscanf(playgame,"%d",&collision_count_millisecond_slowball_2);
    }
    if(r_level==3)
    {
        fscanf(playgame,"%d",&mood_expand_3);
        fscanf(playgame,"%d",&collision_counting_start_expand_3);
        fscanf(playgame,"%d",&collision_count_millisecond_expand_3);

        fscanf(playgame,"%d",&mood_shrink_paddle_3);
        fscanf(playgame,"%d",&collision_counting_start_shrink_3);
        fscanf(playgame,"%d",&collision_count_millisecond_shrink_3);

        fscanf(playgame,"%d",&mood_danger_3);
        fscanf(playgame,"%d",&mood_danger_effect_3);

        fscanf(playgame,"%d",&mood_extralife_3);
        fscanf(playgame,"%d",&mood_extra_life_effect_3);

        fscanf(playgame,"%d",&mood_fastball_3);
        fscanf(playgame,"%d",&collision_counting_start_fastball_3);
        fscanf(playgame,"%d",&collision_count_millisecond_fastball_3);

        fscanf(playgame,"%d",&mood_slow_ball_3);
        fscanf(playgame,"%d",&collision_counting_start_slowball_3);
        fscanf(playgame,"%d",&collision_count_millisecond_slowball_3);
    }
    if(r_level==4)
    {
        fscanf(playgame,"%d",&mood_expand_4);
        fscanf(playgame,"%d",&collision_counting_start_expand_4);
        fscanf(playgame,"%d",&collision_count_millisecond_expand_4);

        fscanf(playgame,"%d",&mood_shrink_paddle_4);
        fscanf(playgame,"%d",&collision_counting_start_shrink_4);
        fscanf(playgame,"%d",&collision_count_millisecond_shrink_4);

        fscanf(playgame,"%d",&mood_danger_4);
        fscanf(playgame,"%d",&mood_danger_effect_4);

        fscanf(playgame,"%d",&mood_extralife_4);
        fscanf(playgame,"%d",&mood_extra_life_effect_4);

        fscanf(playgame,"%d",&mood_fastball_4);
        fscanf(playgame,"%d",&collision_counting_start_fastball_4);
        fscanf(playgame,"%d",&collision_count_millisecond_fastball_4);

        fscanf(playgame,"%d",&mood_slow_ball_4);
        fscanf(playgame,"%d",&collision_counting_start_slowball_4);
        fscanf(playgame,"%d",&collision_count_millisecond_slowball_4);
    }
    if(r_level==5)
    {
        fscanf(playgame,"%d",&mood_expand_5);
        fscanf(playgame,"%d",&collision_counting_start_expand_5);
        fscanf(playgame,"%d",&collision_count_millisecond_expand_5);

        fscanf(playgame,"%d",&mood_shrink_paddle_5);
        fscanf(playgame,"%d",&collision_counting_start_shrink_5);
        fscanf(playgame,"%d",&collision_count_millisecond_shrink_5);

        fscanf(playgame,"%d",&mood_danger_5);
        fscanf(playgame,"%d",&mood_danger_effect_5);

        fscanf(playgame,"%d",&mood_extralife_5);
        fscanf(playgame,"%d",&mood_extra_life_effect_5);

        fscanf(playgame,"%d",&mood_fastball_5);
        fscanf(playgame,"%d",&collision_counting_start_fastball_5);
        fscanf(playgame,"%d",&collision_count_millisecond_fastball_5);

        fscanf(playgame,"%d",&mood_slow_ball_5);
        fscanf(playgame,"%d",&collision_counting_start_slowball_5);
        fscanf(playgame,"%d",&collision_count_millisecond_slowball_5);
    }
}
void _pause_game()
{
    iShowBMP(0,0,"Preview1.bmp");
    iSetColor(255,0,0);
    iText(100, 400, "Do U want to continue? ",GLUT_BITMAP_HELVETICA_18);
    iShowBMP(40,350,"resume.bmp");
    iShowBMP(210,350,"save&quit.bmp");
}
void reset()
{
    iPauseTimer(6);
    dx = i_dx, dy = i_dy, a = i_a;
    platform_d = i_platform_d, platform_h = i_platform_h, ball_r = i_ball_r;
    ball_x = i_ball_x, ball_y = i_ball_y,platform_x = i_platform_x, platform_y = i_platform_y;
    score = 0;
    cnt = 3;
    coordinate();
    alldeactive();
    level = r_level;
    mood = 1;
}
void initial();
void level_sel()
{
    iShowBMP(0,0,"Iso.bmp");
    iShowBMP(125,415,"level1.bmp");
    iShowBMP(125,375,"level2.bmp");
    iShowBMP(125,335,"level3.bmp");
    iShowBMP(125,295,"level4.bmp");
    iShowBMP(125,255,"level5.bmp");
}
void level_setup()
{
    if(level == 1)
    {
        if(Save_Game==0) level1();
        l_s = 1;
        level = 0;
    }
    else if(level == 2)
    {
        if(Save_Game==0) level2();
        l_s = 2;
        level = 0;
    }
    else if(level == 3)
    {
        if(Save_Game==0) level3();
        l_s = 3;
        level = 0;
    }
    else if(level == 4)
    {
        if(Save_Game==0) level4();
        l_s = 4;
        level = 0;
    }
    else if(level == 5)
    {
        if(Save_Game==0) level5();
        l_s = 5;
        level = 0;
    }
    r_level = l_s;
}
void sound_sel()
{
    iShowBMP(0,0,"Iso.bmp");
    iShowBMP(110,315,"on.bmp");
    iShowBMP(210,315,"off.bmp");
}
void check_level_end()
{
    int hc = 0, sc = 0, vc = 0;
    for(i = 0; i< 624; i++)
    {
        if(hbrickcount[i] == 0) hc++;
        if(steelcount[i] == 0) sc++;
    }
    for(i = 0; i < 650; i++)
        if(vbrickcount[i] == 0) vc++;

    //if(hc == 624 && sc == 624 && vc == 650) flag = 1;
    if(score >= 1000)
    {
        score_finish=0;
        flag = 1;
        iPauseTimer(6);
        all_mood_off();
    }
}
void new_level()
{
    iShowBMP(0,0,"Preview2.bmp");
    iSetColor(255,0,0);
    iText(125, 400, "Congratulations!!!",GLUT_BITMAP_HELVETICA_18);
    iSetColor(255,0,0);
    iText(125, 350, "Level Completed!!!",GLUT_BITMAP_HELVETICA_18);
    iShowBMP(40,300,"home.bmp");
    iShowBMP(210,300,"next.bmp");
}
void finale()
{
    iShowBMP(125,100,"exit.bmp");
    iShowBMP(30,150,"home.bmp");
    iShowBMP(210,150,"retry.bmp");
}
/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    iClear();
    if(mood == 0)
    {
        iShowBMP(0,0,"Brick breaker.bmp");
        initial();
    }
    if(mood == 1)
    {
        check_level_end();
        iShowBMP(0,0,"Preview3.bmp");
        if(g_s == 0)
        {
            if(Save_Game==0)
                iPauseTimer(6);
        }
        if(g_s == 1)
        {
            iResumeTimer(6);
            g_s = -1;
        }
        level_setup();
        allbrick();
        platform();
        life();
        if(flag == 1)
            mood = 8;
    }
    if(mood == 2)
    {
        level_sel();
        iShowBMP(125,150,"back.bmp");
    }
    if(mood == 3)
        sound_sel();
    if(mood == 5)
    {
        iShowBMP(0,0,"Preview2.bmp");
        f_score();
        iSetColor(150,150,150);
        iRectangle(100,175,200,50);
        if(mode == 1)
        {
            iSetColor(255, 255, 255);
            iText(110, 195, str, GLUT_BITMAP_HELVETICA_18);
        }
    }
    if(mood == 6)
    {
        name_read();
        finale();
    }
    if(mood == 7)
        _pause_game();
    if(mood == 8)
        new_level();
    if(mood == 9)
    {
        name_read();
        iShowBMP(125,150,"back.bmp");
    }
    draw_expand_scatter();
    draw_danger_icon();
    draw_fastball_icon();
    draw_slowball_icon();
    draw_shrink_icon();
    draw_extralife_icon();

    ///doing something new here to control resume and pause timer in expand icon
    if(r_level==1)
        iResumeTimer(1);
    else if(r_level==2)
        iResumeTimer(2);
    else if(r_level==3)
        iResumeTimer(3);
    else if(r_level==4)
        iResumeTimer(4);
    else if(r_level==5)
        iResumeTimer(5);
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    if(mx<position)
    {
        if(platform_x>=0)
        {
            platform_x-=(position-mx);
            if((ball_y==platform_y+platform_h+ball_r))
                ball_x-=(position-mx);
            position=mx;
        }
    }
    else if(mx>position)
    {
        if(platform_x+platform_d<=400)
        {
            platform_x+=(mx-position);
            if((ball_y==platform_y+platform_h+ball_r))
                ball_x+=(mx-position);
            position=mx;
        }
    }
}
/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        ///new game
        if((mx >= 125 && mx <= 275) && (my >= 435 && my <= 465 ) && mood == 0)
        {
            r_score = 0;
            score = 0;
            mood = 1;
            level = 1;
        }
        ///play saved game
        else if((mx >= 125 && mx <= 275) && (my >= 395 && my <= 425 ) && mood == 0)
        {
            Save_Game=1;
            play_saved_game();
            level=r_level;
            score_finish=1;
            mood=1;
            g_s=1;
        }
        ///level
        else if((mx >= 125 && mx <= 275) && (my >= 355 && my <= 385 ) && mood == 0)
        {
            mood = 2;
        }
        ///sound
        else if((mx >= 125 && mx <= 275) && (my >= 315 && my <= 345 )&& mood == 0)
        {
            mood = 3;
        }
        ///hall of fame
        else if((mx >= 125 && mx <= 275) && (my >= 275 && my <= 305 ) && mood == 0)
        {
            mood = 9;
        }
        ///exit
        else if((mx >= 125 && mx <= 275) && (my >= 235 && my <= 265 ) && mood == 0)
        {
            exit(0);
        }
        ///level5
        else if((mx >= 125 && mx <= 275) && (my >= 255 && my <= 285 ) && mood == 2)
        {
            level = 5;
            mood = 1;
        }
        ///level 4
        else if((mx >= 125 && mx <= 275) && (my >= 295 && my <= 325 ) && mood == 2)
        {
            level = 4;
            mood = 1;
        }
        ///level 3
        else if((mx >= 125 && mx <= 275) && (my >= 335 && my <= 365 ) && mood == 2)
        {
            level = 3;
            mood = 1;
        }
        ///level 2
        else if((mx >= 125 && mx <= 275) && (my >= 375 && my <= 405 ) && mood == 2)
        {
            level = 2;
            mood = 1;
        }
        ///level1
        else if((mx >= 125 && mx <= 275) && (my >= 415 && my <= 445 ) && mood == 2)
        {
            level = 1;
            mood = 1;
        }
        ///sound 0n
        else if((mx >= 110 && mx <= 190) && (my >= 315 && my <= 355 ) && mood == 3)
        {
            sound = 1;
            PlaySound("bricktheme.wav", NULL, SND_LOOP | SND_ASYNC);
            mood = 0;
        }
        ///sound off
        else if((mx >= 210 && mx <= 290) && (my >= 315 && my <= 355 ) && mood == 3)
        {
             PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
            sound = 0;
            mood = 0;
        }
        ///name enter
        else if((mx >= 100 && mx <= 300) && (my >= 175 && my <= 225) && mood == 5)
        {
            mode = 1;
        }
        ///home
        else if((mx >= 30 && mx <= 180) && (my >= 150 && my <= 180 ) && mood == 6)
        {
            reset();
            mood = 0;
            r_score = 0;
        }
        ///retry
        else if((mx >= 210 && mx <= 360) && (my >= 150 && my <= 180 ) && mood == 6)
        {
            reset();
            r_score = 0;
            mood = 1;
            if(level == 6)
                level = 5;
        }
        ///exit
        else if((mx >= 125 && mx <= 275) && (my >= 100 && my <= 130 ) && mood == 6)
        {
            exit(0);
        }
        ///resume
        else if((mx >= 40 && mx <= 190) && (my >= 350 && my <= 380 ) && mood == 7)
        {
            Save_Game=0;
            score_finish=1;
            mood = 1;
            iResumeTimer(6);
        }
        ///save & quit
        else if((mx >= 210 && mx <= 360) && (my >= 350 && my <= 380 ) && mood == 7)
        {

            save_game();
            printf("%d\n",r_level);
            Save_Game=1;
            all_mood_off();
            exit(0);
        }
        ///home
        else if((mx >= 40 && mx <= 190) && (my >= 300 && my <= 330 ) && mood == 8)
        {
            reset();
            flag = 0;
            mood = 0;
        }
        ///next
        else if((mx >= 210 && mx <= 360) && (my >= 300 && my <= 330 ) && mood == 8)
        {
            score_finish=1;
            Save_Game=0;
            flag = 0;
            r_score += score;
            r_level += 1;
            reset();
            score = 0;
            if(level == 6)
            {
                mood = 5;
            }
        }
        ///back to home
        else if((mx >= 125 && mx <= 275) && (my >= 150 && my <= 180 ) && (mood == 9 || mood == 2))
        {
            mood = 0;
        }
        position=mx;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}
/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(mood == 1 && key == 'p')
    {
        iPauseTimer(6);
        score_finish=0;
        all_mood_off();
        mood = 7;
    }
    if(mood == 1 && key == ' ')
    {
        g_s = 1;
    }
    if(mood == 5 && key == '\r')
    {
        mood = 6;
    }
    int o;
    if(mode == 1)
    {
        if(key == '\r')
        {
            mode = 0;
            strcpy(hscor[5].name,str);
            in = 1;
            if(in == 1)
            {
                name_write();
                in = 0;
            }
            for(o = 0; o < len; o++)
                str[o] = 0;
            len = 0;
            in = 1;
        }
        else
        {
            str[len] = key;
            len++;
        }
        hscor[5].points = score;
    }
}
/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_INSERT)
        mode = 1;
    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if(key == GLUT_KEY_LEFT)
    {
        if(platform_x < 50)
        {
           platform_x = 25;
           if(ball_y==(platform_y+platform_h+ball_r)) ball_x=platform_x+(platform_d/2);
        }
        platform_x -= a;
        if(ball_y==(platform_y+platform_h+ball_r)) ball_x-=a;

    }
    if(key == GLUT_KEY_RIGHT)
    {
        if(platform_x > 325)
        {
            platform_x = 325;
            if(ball_y==(platform_y+platform_h+ball_r)) ball_x=platform_x+(platform_d/2);
        }
            platform_x += a;
            if(ball_y==(platform_y+platform_h+ball_r)) ball_x+=a;
    }

}
void level2();
void level3();
void level4();
void level5();
void initial()
{
    iShowBMP(125,435,"new game.bmp");
    iShowBMP(125,395,"saved game.bmp");
    iShowBMP(125,355,"level.bmp");
    iShowBMP(125,315,"sound.bmp");
    iShowBMP(125,275,"halloffame.bmp");
    iShowBMP(125,235,"exit.bmp");
}
int main()
{
    PlaySound("bricktheme.wav", NULL, SND_LOOP | SND_ASYNC);
//    DWORD dwError = GetLastError();

    //place your own initialization codes here.

    coordinate();
    alldeactive();

    iSetTimer(1,collision);
    iSetTimer(1,level1_icon_change);
    iSetTimer(1,level2_icon_change);
    iSetTimer(1,level3_icon_change);
    iSetTimer(1,level4_icon_change);
    iSetTimer(1,level5_icon_change);
    iSetTimer(5, ballChange);
    iPauseTimer(1);
    iPauseTimer(2);
    iPauseTimer(3);
    iPauseTimer(4);
    iPauseTimer(5);
    iPauseTimer(6);

    iInitialize(400, 700, "BRICK_BREAKER");
    return 0;
}

void platform()
{
    iSetColor(255, 10, 10);
    iFilledCircle(ball_x, ball_y, ball_r);
    iSetColor(175,100,255);
    iFilledRectangle(platform_x, platform_y,  platform_d, platform_h);
}

void allbrick()
{
    ///horizontal
    for(i=0; i<624; i++)
    {
        if(hbrickcount[i]>0)
        {
            iSetColor(82, 99, 160);
            iFilledRectangle(hori_x[i],hori_y[i], 24, 8);
            iSetColor(255, 255, 255);
            iRectangle(hori_x[i],hori_y[i], 24, 8);
        }
        ///featured
        if(hbrickcount[i]==2)
        {
            iSetColor(rand()%255+100,0,rand()%255+100);
            iFilledRectangle(hori_x[i],hori_y[i],24,8);
            iSetColor(0,0,0);
            iRectangle(hori_x[i],hori_y[i],24,8);
        }
    }

    for(i=0; i<650; i++)
    {
        if(vbrickcount[i]>0)
        {
            iSetColor(82, 99, 160);
            iFilledRectangle(vert_x[i],vert_y[i], 8, 24);
            iSetColor(255, 255, 255);
            iRectangle(vert_x[i],vert_y[i], 8, 24);
        }
        ///featured
        if(vbrickcount[i]==2)
        {
            iSetColor(rand()%255+100,0,rand()%255+100);
            iFilledRectangle(vert_x[i],vert_y[i],8,24);
            iSetColor(0,0,0);
            iRectangle(vert_x[i],vert_y[i],8,24);
        }
    }

    for(i=0; i<624; i++)
    {
        if(steelcount[i]==3)
        {
            iSetColor(68,70,75);
            iFilledRectangle(steel_x[i],steel_y[i], 24, 8);
            iSetColor(255, 255, 255);
            iRectangle(steel_x[i],steel_y[i], 24, 8);
        }
        if(steelcount[i]==2)
        {
            iSetColor(159,156,183);
            iFilledRectangle(steel_x[i],steel_y[i], 24, 8);
            iSetColor(255, 255, 255);
            iRectangle(steel_x[i],steel_y[i], 24, 8);
        }
        if(steelcount[i]==1)
        {
            iSetColor(188,192,183);
            iFilledRectangle(steel_x[i],steel_y[i], 24, 8);
            iSetColor(255, 255, 255);
            iRectangle(steel_x[i],steel_y[i], 24, 8);
        }
    }
}
void level1()
{
    for(i=0; i<16; i++)
    {
        if( i==6 || i==7 || i==8 || i==9 )
            continue;
        hbrickcount[9*16+i]=1;
        hbrickcount[30*16+i]=1;
        ///featured
        if(i==1 || i==14)
        {
            hbrickcount[9*16+i]=2;
            hbrickcount[30*16+i]=2;
        }
    }

    for(i=0; i<8; i++)
    {
        hbrickcount[34*16+i+4]=1;
        hbrickcount[18*16+i+4]=1;
        /// feature
        if(i==3||i==4)
        {
            hbrickcount[34*16+i+4]=2;
            hbrickcount[18*16+i+4]=2;
        }
    }
    for(i=0; i<16 ; i++)
    {
        if( i>3 && i<12)
            continue;
        steelcount[i]=3;
        steelcount[38*16+i]=3;
    }
    for(i=1; i<9 ; i++)
    {
        steelcount[16*i+3]=3;
        steelcount[16*(i+30)+3]=3;
        steelcount[16*i+12]=3;
        steelcount[16*(i+30)+12]=3;
    }
    ///vertical middle

    for(i=0; i<5 ; i++)
    {
        if(i!=2)
        {
            vbrickcount[50*(6+i)+24]=1;
            vbrickcount[50*(6+i)+25]=1;
        }
        else
        {
            vbrickcount[50*(6+i)+24]=2;
            vbrickcount[50*(6+i)+25]=2;
        }
    }
    /// vertical sideways
    for(i=0; i<5 ; i++)
    {
        vbrickcount[50*(4+i)+4]=1;
        vbrickcount[50*(4+i)+44]=1;
        if(i==2)
        {
            vbrickcount[50*(4+i)+4]=2;
            vbrickcount[50*(4+i)+44]=2;
        }
    }
}
void level2()
{
    ///for horizontal
    for(i = 0; i < 16; i++)
    {
        if(i == 0 || i == 14)
        {
            for(j = 16; j <= 20 ; j++)
                hbrickcount[j * 16 + i] = 1;
        }
        if(i == 1 || i == 13)
        {
            for(j = 5; j <= 9 ; j++)
                hbrickcount[j * 16 + i] = 1;
            for(j = 15; j <= 20 ; j++)
                hbrickcount[j * 16 + i] = 1;
        }
        if(i == 2 || i == 12)
        {
            for(j = 14; j <= 21 ; j++)
                hbrickcount[j * 16 + i] = 1;

            hbrickcount[22 * 16 + 12] = 1 ;
            hbrickcount[25 * 16 + 2] = 1;
            hbrickcount[26 * 16 + 2] = 1;
            hbrickcount[27 * 16 + 2] = 1;
        }
        if( i == 3 || i == 11)
        {
            for(j = 0; j <= 4 ; j++)
                hbrickcount[j * 16 + i] = 1;
            for(j = 26; j <= 29 ; j++)
                hbrickcount[j * 16 + i] = 1;

            hbrickcount[11 * 16 + i] = 1;
            hbrickcount[14 * 16 + i] = 1;
            hbrickcount[15 * 16 + i] = 1;
            hbrickcount[20 * 16 + i] = 1;
            hbrickcount[21 * 16 + i] = 1;
            hbrickcount[24 * 16 + 11] = 1;
            hbrickcount[25 * 16 + 11] = 1;
        }
        if(i == 4 || i == 10)
        {
            hbrickcount[14 * 16 + i] = 1;
            hbrickcount[15 * 16 + i] = 1;
            hbrickcount[20 * 16 + i] = 1;
            hbrickcount[21 * 16 + i] = 1;
            hbrickcount[28 * 16 + i] = 1;
            hbrickcount[29 * 16 + i] = 1;

            for(j = 24; j <= 27; j++)
                hbrickcount[j * 16 + 10] = 1;
        }
        if(i == 5 || i == 9)
        {
            for(j = 2; j <= 11; j++)
                hbrickcount[j * 16 + i] = 1;
            hbrickcount[14 * 16 + i] = 1;
            hbrickcount[15 * 16 + i] = 1;
            hbrickcount[20 * 16 + i] = 1;
            hbrickcount[21 * 16 + i] = 1;
            hbrickcount[22 * 16 + 9] = 1;
            for(j = 24; j <=26; j++)
                hbrickcount[j * 16 + 5] = 1;
        }
        if(i == 6 || i == 8)
        {
            for(j = 14; j<=28; j++)
                hbrickcount[j * 16 + i] = 1;
            hbrickcount[1 * 16 + i] = 1;
            hbrickcount[5 * 16 + i] = 1;
            hbrickcount[8 * 16 + i] = 1;
            hbrickcount[9 * 16 + i] = 1;
        }
        if(i == 7)
        {
            for(j = 14; j<= 28; j++)
            {
                if(j == 22 || j == 23)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
            hbrickcount[0 * 16 + i] = 1;
            for(j  = 5; j <= 7 ; j++)
                hbrickcount[j * 16 + i] = 1;
        }
    }

    ///for steel
    for(i = 0; i < 16; i++)
    {
        if(i == 2 || i == 12)
        {
            steelcount[4 * 16 + i] =3;
            steelcount[5 * 16 + i] =3;
            steelcount[9 * 16 + i] =3;
            steelcount[10 * 16 + i] =3;

            for(j = 22; j<= 30; j++)
            {
                if(i == 2 && (j == 25||j == 26 || j== 27) || (i == 12 && j == 22))
                    continue;
                else
                    steelcount[j * 16 + i] =3;
            }
        }
        if(i == 3 || i == 11)
        {
            for(j = 16; j<=19; j++)
                steelcount[j * 16 + i] =3;
            steelcount[30 * 16 + i] =3;
            steelcount[31 * 16 + i] =3;

            for(j = 22; j<=25; j++)
            {
                if(i == 11 && ( j == 24 || j == 25))
                    continue;
                else
                    steelcount[j * 16 + i] =3;
            }
        }
        if(i == 4 || i == 10)
        {
            steelcount[16 * 16 + i] =3;
            steelcount[19 * 16 + i] =3;
            steelcount[22 * 16 + i] =3;
            steelcount[23 * 16 + i] =3;
            steelcount[30 * 16 + i] =3;
            steelcount[31 * 16 + i] =3;

            for(j = 24; j<= 27; j++)
                steelcount[j * 16 + 4] =3;
        }
        if( i == 5 || i == 9)
        {
            for(j = 16; j<=19; j++)
                steelcount[j * 16 + i] =3;
            for(j = 22; j<= 30 ; j++)
            {
                if((i == 5 && ( j == 24 || j == 25 || j == 26) )  || (i == 9 && j == 22))
                    continue;
                else
                    steelcount[j * 16 + i] =3;
            }

        }
        if( i == 6 || i == 8)
        {
            for(j = 2; j<= 4; j++)
                steelcount[j * 16 + i] =3;
        }
        if( i == 7)
        {
            for(j = 1; j <= 4; j++)
                steelcount[j * 16 + i] = 3;
            for(j = 8; j<= 10; j++)
                steelcount[j * 16 + i] =3;
        }
    }
    ///for special
    for(i = 0; i< 16; i++)
    {
        if(i == 0 || i ==14)
        {
            hbrickcount[8 * 16 + i] = 2;
        }
        if(i == 3 || i == 11)
        {
            hbrickcount[4 * 16 + i] = 2;
            hbrickcount[10 * 16 + i] = 2;
        }
        if( i == 4 || i == 10)
        {
            hbrickcount[17 * 16 + i] = 2;
            hbrickcount[18 * 16 + i] = 2;
            hbrickcount[32 * 16 + i] = 2;
            hbrickcount[33 * 16 + i] = 2;
        }
        if( i == 6 || i == 8)
        {
            hbrickcount[6 * 16 + i] = 2;
            hbrickcount[7 * 16 + i] = 2;
        }
        if(i == 7)
        {
            hbrickcount[22 * 16 + i] =2;
            hbrickcount[23 * 16 + i] =2;
        }
    }
}
void level5()
{
    ///for horizontal
    for(i = 0; i< 16; i++)
    {
        if(i == 0 || i == 15)
        {
            hbrickcount[8 * 16 + i] = 1;
            hbrickcount[9 * 16 + i] = 1;
            hbrickcount[30 * 16 + i] = 1;
            hbrickcount[31 * 16 + i] = 1;
        }
        if(i == 1 || i == 14)
        {
            hbrickcount[7 * 16 + i] = 1;
            hbrickcount[10 * 16 + i] = 1;
            hbrickcount[29 * 16 + i] = 1;
            hbrickcount[32 * 16 + i] = 1;
        }
        if(i == 2 || i == 13)
        {
            for(j = 6; j <= 11; j++)
            {
                if( j == 7 || j == 10)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
            for(j = 28; j <= 33; j++)
            {
                if(j == 29 || j == 32)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
        }
        if( i == 4 || i == 11)
        {
            for( j = 4; j <= 13; j++)
            {
                if(j == 6 || j == 7 || j == 10 || j == 11)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
            for(j = 26; j <= 35; j++)
            {
                if(j == 28 || j == 29 || j == 32 || j == 33)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
        }
        if(i == 5 || i == 10)
        {
            for(j = 3; j<= 14; j++)
            {
                if(j == 5 || j == 8 || j == 9 || j == 12)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
            for( j = 25; j<= 36; j++)
            {
                if( j == 27 || j == 30 || j == 31 || j == 34)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
        }
        if( i == 6 || i == 9)
        {
            for(j = 7; j<=10; j++)
                hbrickcount[j * 16 + i] = 1;
            for(j = 29; j <= 32; j++)
                hbrickcount[j * 16 + i] = 1;
        }
        if(i == 7 || i == 8)
        {
            for(j = 1; j <= 16; j++)
            {
                if(j == 4 || j == 8 || j ==9 || j == 13)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
            for(j = 23; j<= 38; j++)
            {
                if(j == 26 || j == 30 || j ==31 || j ==35)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
        }
    }
    ///for steel
    for(i = 0; i< 16; i++)
    {
        if(i == 0 || i == 15)
        {
            for(j = 1; j <= 3; j++)
                steelcount[j * 16 + i] = 3;
            for(j = 14; j <= 16; j++)
                steelcount[j * 16 + i] =3;
            for( j = 23; j<=25; j++)
                steelcount[j * 16 + i] =3;
            for(j = 36; j<=38; j++)
                steelcount[j * 16 + i] =3;
        }
        if(i == 1 || i == 14)
        {
            for(j = 1; j <= 3; j++)
            {
                if(j == 2)
                    continue;
                steelcount[j * 16 + i] = 3;
            }
            for(j = 14; j <= 16; j++)
            {
                if(j == 15)
                    continue;
                steelcount[j * 16 + i] =3;
            }
            for( j = 23; j<=25; j++)
            {
                if(j == 24)
                    continue;
                steelcount[j * 16 + i] =3;
            }
            for(j = 36; j<=38; j++)
            {
                if(j == 37)
                    continue;
                steelcount[j * 16 + i] =3;
            }
        }
        if( i == 2 || i == 13)
        {
            for(j = 1; j <= 3; j++)
                steelcount[j * 16 + i] = 3;
            for(j = 14; j <= 16; j++)
                steelcount[j * 16 + i] =3;
            for( j = 23; j<=25; j++)
                steelcount[j * 16 + i] =3;
            for(j = 36; j<=38; j++)
                steelcount[j * 16 + i] =3;
        }
        if(i == 3 || i == 12)
        {
            for(j =5; j<= 12; j++)
            {
                if(j == 6 || j == 8 || j == 9 || j == 11)
                    continue;
                else
                    steelcount[j * 16 + i] =3;
            }
            for(j = 27; j <= 34; j++)
            {
                if(j == 28 || j == 30 || j == 31 || j == 33)
                    continue;
                else
                    steelcount[j * 16 + i] =3;
            }
        }
        if(i == 5 || i == 10)
        {
            steelcount[8 * 16 + i] =3;
            steelcount[9 * 16 + i] =3;
            steelcount[30 * 16 + i] =3;
            steelcount[31 * 16 + i] =3;
        }
        if(i == 6 || i == 9)
        {
            steelcount[2 * 16 + i] =3;
            steelcount[5 * 16 + i] =3;
            steelcount[12 * 16 + i] =3;
            steelcount[15 * 16 + i] =3;
            steelcount[24 * 16 + i] =3;
            steelcount[27 * 16 + i] =3;
            steelcount[34 * 16 + i] =3;
            steelcount[37 * 16 + i] =3;
        }
    }
    ///for special
    for(i = 0; i< 16; i++)
    {
        if(i == 1 || i == 14)
        {
            hbrickcount[2 * 16 + i] = 2;
            hbrickcount[8 * 16 + i] = 2;
            hbrickcount[9 * 16 + i] = 2;
            hbrickcount[15 * 16 + i] = 2;
            hbrickcount[24 * 16 + i] = 2;
            hbrickcount[30 * 16 + i] = 2;
            hbrickcount[31 * 16 + i] = 2;
            hbrickcount[37 * 16 + i] = 2;
        }
        if(i == 7 || i == 8)
        {
            hbrickcount[8 * 16 + i] = 2;
            hbrickcount[9 * 16 + i] = 2;
            hbrickcount[30 * 16 + i] = 2;
            hbrickcount[31 * 16 + i] = 2;
        }
    }
}

void level3()
{
    ///for horizontal
    for(i  = 0; i < 16; i++)
    {
        if(i == 0 || i == 15)
        {
            for(j = 14 ; j <= 17; j++)
                hbrickcount[j * 16 + i] = 1;
            for(j = 24; j <= 27; j++)
                hbrickcount[j * 16 + i] = 1;
        }
        if(i == 1 || i == 2 || i == 3 || i == 4 ||i == 11 || i == 12 || i == 13 || i == 14)
        {
            for(j = 18; j <= 23; j++)
            {
                if( j == 19 || j == 22)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
        }
        if(i == 5 || i == 10)
        {
            for(j = 14; j <= 16; j++)
                hbrickcount[j * 16 + i] = 1;
            for(j = 25; j<= 27; j++)
                hbrickcount[j * 16 + i] = 1;
        }
        if(i == 6 || i == 9)
        {
            for(j = 13; j <= 28; j++)
            {
                if(j == 18 || j == 20 || j == 23)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
        }
        if(i == 7 || i == 8)
        {
            for(j = 13 ; j<= 28; j++)
            {
                if(j == 15 || j == 19 || j == 20 || j == 21 || j==23 || j == 26)
                    continue;
                else
                    hbrickcount[j * 16 + i] = 1;
            }
        }
    }

    ///for steel
    for(i = 0; i < 16 ; i++)
    {
        if (i == 0 || i == 15)
        {
            for(j = 19; j <= 22; j++)
                steelcount[j * 16 + i] =3;
        }
        if(i == 5 || i == 10)
        {
            for(j = 18; j <= 23 ; j++)
                steelcount[j * 16 + i] =3;
        }
        if(i == 6 || i == 9)
        {
            steelcount[18 * 16 + i] =3;
            steelcount[20 * 16 + i] =3;
            steelcount[23 * 16 + i] =3;
        }
        if(i == 7 || i == 8)
        {
            steelcount[19 * 16 + i] =3;
            steelcount[21 * 16 + i] =3;
            steelcount[23 * 16 + i] =3;
        }
    }
    ///for special
    for(i = 0; i<16; i++)
    {
        if(i == 0 || i == 15)
        {
            hbrickcount[13 * 16 + i] = 2;
            hbrickcount[28 * 16 + i] = 2;
        }
        if(i == 4 || i == 11)
        {
            hbrickcount[15 * 16 + i] = 2;
            hbrickcount[26 * 16 + i] = 2;
        }
        if(i == 7 || i == 8)
        {
            hbrickcount[15 * 16 + i] = 2;
            hbrickcount[20 * 16 + i] = 2;
            hbrickcount[26 * 16 + i] = 2;
        }
    }
}
void level4()
{

    for(i=3; i<12; i++)
    {
        if(i<6 || i>8)
            steelcount[18*16+i]=3;
        else
            hbrickcount[18*16+i]=1;
        hbrickcount[17*16+i]=1;
        hbrickcount[19*16+i]=1;
        if(i==7)
            continue;
        vbrickcount[50*(i-2)+21]=1;
        vbrickcount[50*(i-2)+25]=1;
    }
    hbrickcount[16*16+6]=2;
    hbrickcount[16*16+8]=2;
    for(i=5; i<30; i++)
    {
        if(i>19||i<17)
            steelcount[16*i+7]=3;
    }
    for(i=0; i<3; i++)
    {
        steelcount[i]=3;
        steelcount[15-i]=3;
        steelcount[i*16]=3;
        steelcount[i*16+15]=3;
    }
    for(i=0; i<4; i++)
    {
        hbrickcount[27*16+i]=1;
        hbrickcount[27*16+15-i]=1;
        vbrickcount[(9+i)*50+12]=1;
        vbrickcount[(9+i)*50+37]=1;
        vbrickcount[(9+i)*50+7]=2;
        vbrickcount[(9+i)*50+43]=2;// vertical mid position
        vbrickcount[(9+i)*50+1]=1;
        vbrickcount[(9+i)*50+48]=1;
    }
    hbrickcount[17]=1;
    hbrickcount[18]=2;
    hbrickcount[33]=2;
    hbrickcount[34]=1;
    hbrickcount[48]=1;
    hbrickcount[3]=1;
    hbrickcount[12]=1;
    hbrickcount[63]=1;
    hbrickcount[29]=2;
    hbrickcount[30]=1;
    hbrickcount[45]=1;
    hbrickcount[46]=2;
}

void alldeactive()
{
    for(i=0; i<624; i++)
    {
        hbrickcount[i]=0;
        steelcount[i]=0;
    }

    for(i=0; i<650; i++)
        vbrickcount[i]=0;
}

void ballChange()
{
    ball_x += dx;
    ball_y += dy;
    if(ball_x > 396 || ball_x < 4)
        dx = -dx;
    if(ball_y > 638 || ball_y < 4)
        dy = -dy;
    if(ball_y < 25)
    {
        cnt --;
        g_s = 0;
        ball_x = i_platform_x + (platform_d/2) ;
        ball_y = 99;
        platform_x = 175;
        platform_y = 90;
    }
    if(ball_x > platform_x - 4  &&  ball_x < platform_x + platform_d +4 && (ball_y >= platform_y + 8 && ball_y < platform_y + 12 ))
    {
        dy = -dy;
    }
    else if((ball_x == platform_x - 4 ) && (ball_y >= platform_y + 8 && ball_y < platform_y + 12))
    {
        if(dx > 0 && dy < 0)
        {
            dx = - dx;
            dy = - dy;
        }
        else if(dx < 0 && dy < 0)
        {
            dy = - dy;
        }
    }
    else if((ball_x == platform_x +platform_d +4) && (ball_y >= platform_y + 8 && ball_y < platform_y + 12))
    {
        if(dx < 0 && dy < 0)
        {
            dx = - dx;
            dy = - dy;
        }
        else if(dx > 0 && dy < 0)
        {
            dy = - dy;
        }
    }
}
void collision()
{
    for(i = 0; i < 624; i++)
    {
        if(hbrickcount[i] > 0)
        {
            if(ball_x >= hori_x[i] - 2 && ball_x <= hori_x[i] + 24 + 2 && (ball_y >= hori_y[i] - 4 && ball_y <= hori_y[i]) )
            {
                hbrickcount[i]--;
                dy = -dy;
                score += 5;
                break;
            }
            else if(ball_x >= hori_x[i] - 2 && ball_x <= hori_x[i] + 24 + 2 && (ball_y >= hori_y[i] + 8 && ball_y <= hori_y[i] + 8 + 4) )
            {
                hbrickcount[i]--;
                dy = -dy;
                score += 5;
                break;
            }
            else if(ball_x >= hori_x[i] - 4 && ball_x <= hori_x[i] && (ball_y >= hori_y[i] - 2 && ball_y <= hori_y[i] + 8 + 2) )
            {
                hbrickcount[i]--;
                dx = -dx;
                score += 5;
                break;
            }
            else if(ball_x >= hori_x[i] + 24 && ball_x <= hori_x[i] + 24 + 4 && (ball_y >= hori_y[i] - 2 && ball_y <= hori_y[i] + 8 + 2) )
            {
                hbrickcount[i]--;
                dx = -dx;
                score += 5;
                break;
            }
            if(r_level==1 && score_finish==1)
            {

                if(hbrickcount[296]==1 && mood_danger_effect_1==1 && Save_Game==0  )
                {
                    mood_danger_1=1;
                    mood_danger_effect_1=0;
                }

                if(hbrickcount[158]==1 && collision_counting_start_fastball_1==0 && Save_Game==0)
                {
                    mood_fastball_1=1;
                }
                if(hbrickcount[481]==1 && collision_counting_start_shrink_1==0 && Save_Game==0)
                {
                    mood_shrink_paddle_1=1;//
                }
                if(hbrickcount[494]==1 && mood_extra_life_effect_1==1 && Save_Game==0)
                {
                    mood_extralife_1=1;
                    mood_extra_life_effect_1=0;
                }
            }
            else if(r_level==2 && score_finish==1)
            {
                if(hbrickcount[359]==1 && mood_danger_effect_2==1 && Save_Game==0)
                {
                    mood_danger_2=1;
                    mood_danger_effect_2=0;
                }
                if(hbrickcount[75]==1 && collision_counting_start_fastball_2==0 && Save_Game==0)
                {
                    mood_fastball_2=1;
                }
                if(hbrickcount[104]==1 && collision_counting_start_shrink_2==0 && Save_Game==0)
                {
                    mood_shrink_paddle_2=1;//
                }
                if(hbrickcount[522]==1 && mood_extra_life_effect_2==1 && Save_Game==0)
                {
                    mood_extralife_2=1;
                    mood_extra_life_effect_2=0;//
                }
                if(hbrickcount[67]==1 && collision_counting_start_expand_2==0 && Save_Game==0)
                {
                    mood_expand_2=1;
                }
                if(hbrickcount[102]==1 && collision_counting_start_slowball_2==0 && Save_Game==0)
                {
                    mood_slow_ball_2=1;
                }
            }
            else if(r_level==3 && score_finish==1)
            {
                if(hbrickcount[248]==1 && mood_danger_effect_3==1 && Save_Game==0)
                {
                    mood_danger_3=1;
                    mood_danger_effect_3=0;
                }
                if(hbrickcount[251]==1 && collision_counting_start_fastball_3==0 && Save_Game==0)
                {
                    mood_fastball_3=1;
                }
                if(hbrickcount[244]==1 && collision_counting_start_shrink_3==0 && Save_Game==0)
                {
                    mood_shrink_paddle_3=1;
                }
                if(hbrickcount[327]==1 && mood_extra_life_effect_3==1 && Save_Game==0)
                {
                    mood_extralife_3=1;
                    mood_extra_life_effect_3=0;
                }
                if(hbrickcount[420]==1 && collision_counting_start_expand_3==0 && Save_Game==0)
                {
                    mood_expand_3=1;
                }
                if(hbrickcount[427]==1 && collision_counting_start_slowball_3==0 && Save_Game==0)
                {
                    mood_slow_ball_3=1;
                }
            }
            else if(r_level==4 && score_finish==1)
            {
                if(hbrickcount[262]==1 && mood_danger_effect_4==1 && Save_Game==0)
                {
                    mood_danger_4=1;
                    mood_danger_effect_4=0;
                }
                if(hbrickcount[33]==1 && collision_counting_start_fastball_4==0 && Save_Game==0)
                {
                    mood_fastball_4=1;
                }
                if(hbrickcount[18]==1 && collision_counting_start_shrink_4==0 && Save_Game==0)
                {
                    mood_shrink_paddle_4=1;//
                }
                if(hbrickcount[264]==1 && collision_counting_start_expand_4==0 && Save_Game==0)
                {
                    mood_expand_4=1;
                }
            }
            else if(r_level==5 && score_finish==1)
            {
                if(hbrickcount[136]==1 && mood_danger_effect_5==1 && Save_Game==0 && level==r_level)
                {
                    mood_danger_5=1;
                    mood_danger_effect_5=0;
                }
                if(hbrickcount[142]==1 && collision_counting_start_fastball_5==0 && Save_Game==0)
                {
                    mood_fastball_5=1;
                }
                if(hbrickcount[46]==1 && collision_counting_start_shrink_5==0 && Save_Game==0)
                {
                    mood_shrink_paddle_5=1;//
                }
                if(hbrickcount[487]==1 && mood_extra_life_effect_5==1 && Save_Game==0)
                {
                    mood_extralife_5=1;
                    mood_extra_life_effect_5=0;//
                }
                if(hbrickcount[254]==1 && collision_counting_start_expand_5==0 && Save_Game==0)
                {
                    mood_expand_5=1;
                }
                if(hbrickcount[385]==1 && collision_counting_start_slowball_5==0 && Save_Game==0)
                {
                    mood_slow_ball_5=1;
                }
            }
        }
    }
    for(i = 0; i < 624; i++)
    {
        if(steelcount[i] > 0)
        {
            if(ball_x >= steel_x[i] - 2 && ball_x <= steel_x[i] + 24 + 2 && (ball_y >= steel_y[i] - 2 && ball_y <= steel_y[i]) )
            {
                steelcount[i]--;
                dy = -dy;
                score += 5;
                break;
            }
            else if(ball_x >= steel_x[i] - 2 && ball_x <= steel_x[i] + 24 + 2 && (ball_y >= steel_y[i] + 8 && ball_y <= steel_y[i] + 8 + 4) )
            {
                steelcount[i]--;
                dy = -dy;
                score += 5;
                break;
            }
            else if(ball_x >= steel_x[i] - 4 && ball_x <= steel_x[i] && (ball_y >= steel_y[i] - 2 && ball_y <= steel_y[i] + 8 + 2) )
            {
                steelcount[i]--;
                dx = -dx;
                score += 5;
                break;
            }
            else if(ball_x >= steel_x[i] + 24 && ball_x <= steel_x[i] + 24 + 4 && (ball_y >= steel_y[i] - 2 && ball_y <= steel_y[i] + 8 + 2) )
            {
                steelcount[i]--;
                dx = -dx;
                score += 5;
                break;
            }

        }
    }
    for(i = 0; i < 650; i++)
    {
        if(vbrickcount[i] > 0)
        {
            if(ball_x >= vert_x[i] - 2 && ball_x <= vert_x[i] + 8+ 2 && (ball_y >= vert_y[i] - 4 && ball_y <= steel_y[i]) )
            {
                vbrickcount[i]--;
                dy = -dy;
                score += 5;
                break;
            }
            else if(ball_x >= vert_x[i] - 2 && ball_x <= vert_x[i] + 8 + 2 && (ball_y >= vert_y[i] + 24 && ball_y <= vert_y[i] + 24 +2) )
            {
                vbrickcount[i]--;
                dy = -dy;
                score += 5;
                break;
            }
            else if(ball_x >= vert_x[i] - 4 && ball_x <= vert_x[i] && (ball_y >= vert_y[i] - 2 && ball_y <= vert_y[i] + 24 +2) )
            {
                vbrickcount[i]--;
                dx = -dx;
                score += 5;
                break;
            }
            else if(ball_x >= vert_x[i] + 8 && ball_x <= vert_x[i] + 8 + 4 && (ball_y >= vert_y[i] - 2 && ball_y <= vert_y[i] + 24 + 2) )
            {
                vbrickcount[i]--;
                dx = -dx;
                score += 5;
                break;
            }
            if(r_level==1 && score_finish==1)
            {

                if(vbrickcount[304]==1 && collision_counting_start_expand_1==0 && Save_Game==0)
                {
                    mood_expand_1=1;
                }
                if(vbrickcount[424]==1 && collision_counting_start_slowball_1==0 && Save_Game==0)
                {
                    mood_slow_ball_1=1;
                }
            }

            else if(r_level==4 && score_finish==1)
            {
                if(vbrickcount[507]==1 && mood_extra_life_effect_4==1 && Save_Game==0)
                {
                    mood_extralife_4=1;
                    mood_extra_life_effect_4=0;

                }
                if(vbrickcount[543]==1 && collision_counting_start_slowball_4==0 && Save_Game==0)
                {
                    mood_slow_ball_4=1;
                }
            }
        }
    }
}

void coordinate()
{
    ///for horizontal
    for(i=0; i<16; i++)
    {
        if(i>0)
            hori_x[i]=hori_x[i-1]+24;

        for(j=1; j<39; j++)
            hori_x[16*j+i]=hori_x[i];
    }
    for(i=0; i<39; i++)
    {
        if(i>0)
            hori_y[16*i]=hori_y[16*i-1]+8;
        for(j=1; j<16; j++)
            hori_y[16*i+j]=hori_y[16*i];
    }
    ///for vertical
    for(i=0; i<50; i++)
    {
        if(i>0)
            vert_x[i]=vert_x[i-1]+8;
        for(j=1; j<13; j++)
            vert_x[50*j+i]=vert_x[i];
    }
    for(i=0; i<13; i++)
    {
        if(i>0)
            vert_y[50*i]=vert_y[50*i-1]+24;
        for(j=0; j<50; j++)
            vert_y[50*i+j]=vert_y[50*i];

    }
    ///for steel
    for(i=0; i<16; i++)
    {
        if(i>0)
            steel_x[i]=steel_x[i-1]+24;
        for(j=1; j<39; j++)
            steel_x[16*j+i]=steel_x[i];
    }
    for(i=0; i<39; i++)
    {
        if(i>0)
            steel_y[16*i]=steel_y[16*i-1]+8;
        for(j=1; j<16; j++)
            steel_y[16*i+j]=steel_y[16*i];
    }
}
void _score()
{
    itoa(score, scr, 10);

    iSetColor(255,255,255);
    iText(10, 675, "Score: ",GLUT_BITMAP_HELVETICA_18);
    iText(70, 675, scr,GLUT_BITMAP_HELVETICA_18);
}

void life()
{
    int ss = 0;
    iSetColor(255,255,255);
    iText(275,653,"Life: ",GLUT_BITMAP_HELVETICA_18);
    for(i = 0; i < 3; i++)
    {
        iSetColor(0,255,0);
        iFilledRectangle(325 + ss,650,15,15);
        ss += 20;
        _score();
    }
    if(cnt == 2)
    {
        ss = 0;
        iSetColor(255,0,0);
        iFilledRectangle(325 + ss,650,15,15);
    }
    if(cnt == 1)
    {
        ss = 0;
        for(i = 0; i < 2; i++)
        {
            iSetColor(255,0,0);
            iFilledRectangle(325 + ss,650,15,15);
            ss += 20;
        }
    }
    if(cnt == 0)
    {
        ss = 0;
        for(i = 0; i < 3; i++)
        {
            iSetColor(255,0,0);
            iFilledRectangle(325 + ss,650,15,15);
            ss += 20;
        }
        alldeactive();
        dx = 0;
        dy = 0;
        a = 0;
        all_mood_off();
        iShowBMP(0,0,"BACK.bmp");
        mood = 5;
        r_score += score;
    }
}

void f_score()
{
    score = r_score;
    itoa(score, scr, 10);
    int m,k = 100;
    char ch;
    iShowBMP2(100,425, "yourscore.bmp",0);
    for(m = 0; scr[m]; m++)
    {
        ch = scr[m];

        if(ch == '0')
            iShowBMP2(k, 350,"0.bmp", 0);
        if(ch == '1')
            iShowBMP2(k, 350,"1.bmp", 0);
        if(ch == '2')
            iShowBMP2(k, 350,"2.bmp", 0);
        if(ch == '3')
            iShowBMP2(k, 350,"3.bmp", 0);
        if(ch == '4')
            iShowBMP2(k, 350,"4.bmp", 0);
        if(ch == '5')
            iShowBMP2(k, 350,"5.bmp", 0);
        if(ch == '6')
            iShowBMP2(k, 350,"6.bmp", 0);
        if(ch == '7')
            iShowBMP2(k, 350,"7.bmp", 0);
        if(ch == '8')
            iShowBMP2(k, 350,"8.bmp", 0);
        if(ch == '9')
            iShowBMP2(k, 350,"9.bmp", 0);

        k += 55;
    }
    iSetColor(255,0,0);
    iText(100,250,"Enter Your Name: ",GLUT_BITMAP_HELVETICA_18);
}
void draw_expand_scatter()
{
    if(mood_expand_1)
        iShowBMP2(expand_x_1,expand_y_1,"expand.bmp",0);
    else if(mood_expand_2)
        iShowBMP2(expand_x_2,expand_y_2,"expand.bmp",0);
    else if(mood_expand_3)
        iShowBMP2(expand_x_3,expand_y_3,"expand.bmp",0);
    else if(mood_expand_4)
        iShowBMP2(expand_x_4,expand_y_4,"expand.bmp",0);
    else if(mood_expand_5)
        iShowBMP2(expand_x_5,expand_y_5,"expand.bmp",0);
}
void draw_danger_icon()
{
    if(mood_danger_1)
        iShowBMP2(danger_x_1,danger_y_1,"danger.bmp",0);
    else if(mood_danger_2)
        iShowBMP2(danger_x_2,danger_y_2,"danger.bmp",0);
    else if(mood_danger_3)
        iShowBMP2(danger_x_3,danger_y_3,"danger.bmp",0);
    else if(mood_danger_4)
        iShowBMP2(danger_x_4,danger_y_4,"danger.bmp",0);
    else if(mood_danger_5)
        iShowBMP2(danger_x_5,danger_y_5,"danger.bmp",0);
}
void draw_fastball_icon()
{
    if(mood_fastball_1)
        iShowBMP2(fastball_x_1,fastball_y_1,"fastball.bmp",0);
    else if(mood_fastball_2)
        iShowBMP2(fastball_x_2,fastball_y_2,"fastball.bmp",0);
    else if(mood_fastball_3)
        iShowBMP2(fastball_x_3,fastball_y_3,"fastball.bmp",0);
    else if(mood_fastball_4)
        iShowBMP2(fastball_x_4,fastball_y_4,"fastball.bmp",0);
    else if(mood_fastball_5)
        iShowBMP2(fastball_x_5,fastball_y_5,"fastball.bmp",0);

}
void draw_slowball_icon()
{
    if(mood_slow_ball_1)
        iShowBMP2(slow_ball_x_1,slow_ball_y_1,"slowball.bmp",0);
    else if(mood_slow_ball_2)
        iShowBMP2(slow_ball_x_2,slow_ball_y_2,"slowball.bmp",0);
    else if(mood_slow_ball_3)
        iShowBMP2(slow_ball_x_3,slow_ball_y_3,"slowball.bmp",0);
    else if(mood_slow_ball_4)
        iShowBMP2(slow_ball_x_4,slow_ball_y_4,"slowball.bmp",0);
    else if(mood_slow_ball_5)
        iShowBMP2(slow_ball_x_5,slow_ball_y_5,"slowball.bmp",0);
}
void draw_shrink_icon()
{
    if(mood_shrink_paddle_1)
        iShowBMP2(shrink_paddle_x_1,shrink_paddle_y_1,"shrink paddle.bmp",0);
    else if(mood_shrink_paddle_2)
        iShowBMP2(shrink_paddle_x_2,shrink_paddle_y_2,"shrink paddle.bmp",0);
    else if(mood_shrink_paddle_3)
        iShowBMP2(shrink_paddle_x_3,shrink_paddle_y_3,"shrink paddle.bmp",0);
    else if(mood_shrink_paddle_4)
        iShowBMP2(shrink_paddle_x_4,shrink_paddle_y_4,"shrink paddle.bmp",0);
    else if(mood_shrink_paddle_5)
        iShowBMP2(shrink_paddle_x_5,shrink_paddle_y_5,"shrink paddle.bmp",0);
}
void draw_extralife_icon()
{
    if(mood_extralife_1)
        iShowBMP2(extra_life_x_1,extra_life_y_1,"extralife.bmp",0);
    else if(mood_extralife_2)
        iShowBMP2(extra_life_x_2,extra_life_y_2,"extralife.bmp",0);
    else if(mood_extralife_3)
        iShowBMP2(extra_life_x_3,extra_life_y_3,"extralife.bmp",0);
    else if(mood_extralife_4)
        iShowBMP2(extra_life_x_4,extra_life_y_4,"extralife.bmp",0);
    else if(mood_extralife_5)
        iShowBMP2(extra_life_x_5,extra_life_y_5,"extralife.bmp",0);
}
void level1_icon_change()
{
    if(mood_expand_1==0 && collision_count_millisecond_expand_1<=1000)
    {
        if(collision_counting_start_expand_1)
        {
            collision_count_millisecond_expand_1++;
        }

        if(collision_count_millisecond_expand_1>1000)
        {
            platform_d=50;
        }
        expand_x_1=vert_x[304];
        expand_y_1=vert_y[304];
        }
    if(mood_shrink_paddle_1==0 && collision_count_millisecond_shrink_1<=1000)
    {
        if(collision_counting_start_shrink_1)
        {
            collision_count_millisecond_shrink_1++;
        }
        if(collision_count_millisecond_shrink_1>1000)
        {
            platform_d=50;
        }
        shrink_paddle_x_1=hori_x[481];
        shrink_paddle_y_1=hori_y[481];
    }
    if(mood_fastball_1==0 && collision_count_millisecond_fastball_1<=1000)
    {
        if(collision_counting_start_fastball_1)
        {
            collision_count_millisecond_fastball_1++;
        }
        if(collision_count_millisecond_fastball_1>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        fastball_x_1=hori_x[158];
        fastball_y_1=hori_y[158];
    }
    if(mood_slow_ball_1==0 && collision_count_millisecond_slowball_1<=1000)
    {
        if(collision_counting_start_slowball_1)
        {
            collision_count_millisecond_slowball_1++;
        }
        if(collision_count_millisecond_slowball_1>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        slow_ball_x_1=vert_x[424];
        slow_ball_y_1=vert_y[424];
    }
    if(mood_danger_1==0)
    {
        danger_x_1=hori_x[296];
        danger_y_1=hori_y[296];
    }
    if(mood_extralife_1==0)
    {
        extra_life_x_1=hori_x[494];
        extra_life_y_1=hori_y[494];
    }
    if(mood_expand_1==1)
    {
        expand_y_1--;
        if(expand_y_1<platform_y-10)
        {
            mood_expand_1=0;
        }
        else if(platform_y+5>=expand_y_1 && platform_y<=expand_y_1+40 && expand_x_1+50>=platform_x && expand_x_1<=platform_x+platform_d)
        {
            mood_expand_1=0;
            collision_counting_start_expand_1=1;
            platform_d=80;
        }
    }
    if(mood_shrink_paddle_1==1)
    {
        shrink_paddle_y_1--;
        if(shrink_paddle_y_1<platform_y-10)
        {
            mood_shrink_paddle_1=0;
        }
        else if(platform_y+5>=shrink_paddle_y_1 && platform_y<=shrink_paddle_y_1+31 && shrink_paddle_x_1+33>=platform_x && shrink_paddle_x_1<=platform_x+platform_d)
        {
            mood_shrink_paddle_1=0;
            collision_counting_start_shrink_1=1;
            platform_d=30;
        }
    }
    if(mood_danger_1==1)
    {
        danger_y_1--;
        if(danger_y_1<platform_y-10)
        {
            mood_danger_1=0;
        }
        else if(platform_y+5>=danger_y_1 && platform_y<=danger_y_1+30 && danger_x_1+33>=platform_x && danger_x_1<=platform_x+platform_d)
        {
            if(cnt==3) cnt=2;
            else if(cnt==2) cnt=1;
            else if(cnt==1) cnt=0;
            mood_danger_1=0;
        }
    }
    if(mood_extralife_1==1)
    {
        extra_life_y_1--;
        if(extra_life_y_1<platform_y-10)
        {
            mood_extralife_1=0;
        }
        else if(platform_y+5>=extra_life_y_1 && platform_y<=extra_life_y_1+30 && extra_life_x_1+35>=platform_x && extra_life_x_1<=platform_x+platform_d)
        {
            if(cnt==2) cnt=3;
            else if(cnt==1) cnt=2;
            else if(cnt==0) cnt=0;
            mood_extralife_1=0;
        }
    }
    if(mood_fastball_1==1)
    {
        fastball_y_1--;
        if(fastball_y_1<platform_y-10)
        {
            mood_fastball_1=0;
        }
        else if(platform_y+5>=fastball_y_1 && platform_y<=fastball_y_1+30 && fastball_x_1+32>=platform_x && fastball_x_1<=platform_x+platform_d)
        {
            mood_fastball_1=0;
            collision_counting_start_fastball_1=1;
            if(dx>0 && dy>0)
            {
                dx=3;
                dy=4;
            }
            else if(dx<0 && dy<0)
            {
                dx=-3;
                dy=-4;
            }
            else if(dx<0 && dy>0)
            {
                dx=-3;
                dy=4;
            }
            else if(dx>0 && dy<0)
            {
                dx=3;
                dy=-4;
            }
        }
    }
    if(mood_slow_ball_1==1)
    {
        slow_ball_y_1--;
        if(slow_ball_y_1<platform_y-10)
        {
            mood_slow_ball_1=0;
        }
        else if(platform_y+5>=slow_ball_y_1 && platform_y<=slow_ball_y_1+31 && slow_ball_x_1+34>=platform_x && slow_ball_x_1<=platform_x+platform_d)
        {
            mood_slow_ball_1=0;
            collision_counting_start_slowball_1=1;
            if(dx>0 && dy>0)
            {
                dx=1;
                dy=2;
            }
            else if(dx<0 && dy<0)
            {
                dx=-1;
                dy=-2;
            }
            else if(dx<0 && dy>0)
            {
                dx=-1;
                dy=2;
            }
            else if(dx>0 && dy<0)
            {
                dx=1;
                dy=-2;
            }
        }
    }
}
void level2_icon_change()
{
    if(mood_expand_2==0 && collision_count_millisecond_expand_2<=1000)
    {
        if(collision_counting_start_expand_2)
        {
            collision_count_millisecond_expand_2++;
        }
        if(collision_count_millisecond_expand_2>1000)
        {
            platform_d=50;
        }
        expand_x_2=hori_x[67];
        expand_y_2=hori_y[67];
    }
    if(mood_shrink_paddle_2==0 && collision_count_millisecond_shrink_2<=1000)
    {
        if(collision_counting_start_shrink_2)
        {
            collision_count_millisecond_shrink_2++;
        }
        if(collision_count_millisecond_shrink_2>1000)
        {
            platform_d=50;
        }
        shrink_paddle_x_2=hori_x[104];
        shrink_paddle_y_2=hori_y[104];
    }
    if(mood_fastball_2==0 && collision_count_millisecond_fastball_2<=1000)
    {
        if(collision_counting_start_fastball_2)
        {
            collision_count_millisecond_fastball_2++;
        }
        if(collision_count_millisecond_fastball_2>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        fastball_x_2=hori_x[75];
        fastball_y_2=hori_y[75];
    }
    if(mood_slow_ball_2==0 && collision_count_millisecond_slowball_2<=1000)
    {
        if(collision_counting_start_slowball_2)
        {
            collision_count_millisecond_slowball_2++;
        }
        if(collision_count_millisecond_slowball_2>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        slow_ball_x_2=hori_x[102];
        slow_ball_y_2=hori_y[102];
    }
    if(mood_danger_2==0)
    {
        danger_x_2=hori_x[359];
        danger_y_2=hori_y[359];
    }
    if(mood_extralife_2==0)
    {
        extra_life_x_2=hori_x[522];
        extra_life_y_2=hori_y[522];
    }
    if(mood_expand_2==1)
    {
        expand_y_2--;
        if(expand_y_2<platform_y-10)
        {
            mood_expand_2=0;
        }
        else if(platform_y+5>=expand_y_2 && platform_y<=expand_y_2+40 && expand_x_2+50>=platform_x && expand_x_2<=platform_x+platform_d)
        {
            mood_expand_2=0;
            collision_counting_start_expand_2=1;
            platform_d=80;
        }
    }
    if(mood_shrink_paddle_2==1)
    {
        shrink_paddle_y_2--;
        if(shrink_paddle_y_2<platform_y-10)
        {
            mood_shrink_paddle_2=0;
        }
        else if(platform_y+5>=shrink_paddle_y_2 && platform_y<=shrink_paddle_y_2+31 && shrink_paddle_x_2+33>=platform_x && shrink_paddle_x_2<=platform_x+platform_d)
        {
            mood_shrink_paddle_2=0;
            collision_counting_start_shrink_2=1;
            platform_d=30;
        }
    }
    if(mood_danger_2==1)
    {
        danger_y_2--;
        if(danger_y_2<platform_y-10)
        {
            mood_danger_2=0;
        }
        else if(platform_y+5>=danger_y_2 && platform_y<=danger_y_2+30 && danger_x_2+33>=platform_x && danger_x_2<=platform_x+platform_d)
        {
            if(cnt==3) cnt=2;
            else if(cnt==2) cnt=1;
            else if(cnt==1) cnt=0;
            mood_danger_2=0;
        }
    }
    if(mood_extralife_2==1)
    {
        extra_life_y_2--;
        if(extra_life_y_2<platform_y-10)
        {
            mood_extralife_2=0;
        }
        else if(platform_y+5>=extra_life_y_2 && platform_y<=extra_life_y_2+30 && extra_life_x_2+35>=platform_x && extra_life_x_2<=platform_x+platform_d)
        {
            if(cnt==2) cnt=3;
            else if(cnt==1) cnt=2;
            else if(cnt==0) cnt=0;
            mood_extralife_2=0;
        }
    }
    if(mood_fastball_2==1)
    {
        fastball_y_2--;
        if(fastball_y_2<platform_y-10)
        {
            mood_fastball_2=0;
        }
        else if(platform_y+5>=fastball_y_2 && platform_y<=fastball_y_2+30 && fastball_x_2+32>=platform_x && fastball_x_2<=platform_x+platform_d)
        {
            mood_fastball_2=0;
            collision_counting_start_fastball_2=1;
            if(dx>0 && dy>0)
            {
                dx=3;
                dy=4;
            }
            else if(dx<0 && dy<0)
            {
                dx=-3;
                dy=-4;
            }
            else if(dx<0 && dy>0)
            {
                dx=-3;
                dy=4;
            }
            else if(dx>0 && dy<0)
            {
                dx=3;
                dy=-4;
            }
        }
    }
    if(mood_slow_ball_2==1)
    {
        slow_ball_y_2--;
        if(slow_ball_y_2<platform_y-10)
        {
            mood_slow_ball_2=0;
        }
        else if(platform_y+5>=slow_ball_y_2 && platform_y<=slow_ball_y_2+31 && slow_ball_x_2+34>=platform_x && slow_ball_x_2<=platform_x+platform_d)
        {
            mood_slow_ball_2=0;
            collision_counting_start_slowball_2=1;
            if(dx>0 && dy>0)
            {
                dx=1;
                dy=2;
            }
            else if(dx<0 && dy<0)
            {
                dx=-1;
                dy=-2;
            }
            else if(dx<0 && dy>0)
            {
                dx=-1;
                dy=2;
            }
            else if(dx>0 && dy<0)
            {
                dx=1;
                dy=-2;
            }
        }
    }
}
void level3_icon_change()
{
    if(mood_expand_3==0 && collision_count_millisecond_expand_3<=1000)
    {
        if(collision_counting_start_expand_3)
        {
            collision_count_millisecond_expand_3++;
        }
        if(collision_count_millisecond_expand_3>1000)
        {
            platform_d=50;
        }
        expand_x_3=hori_x[420];
        expand_y_3=hori_y[420];/// i will change this value later..These logic will be useful when user will play previous level like level 1 after playing level 2
    }

    if(mood_shrink_paddle_3==0 && collision_count_millisecond_shrink_3<=1000)
    {
        if(collision_counting_start_shrink_3)
        {
            collision_count_millisecond_shrink_3++;
        }
        if(collision_count_millisecond_shrink_3>1000)
        {
            platform_d=50;
        }
        shrink_paddle_x_3=hori_x[244];
        shrink_paddle_y_3=hori_y[244];
    }
    if(mood_fastball_3==0 && collision_count_millisecond_fastball_3<=1000)
    {
        if(collision_counting_start_fastball_3)
        {
            collision_count_millisecond_fastball_3++;
        }
        if(collision_count_millisecond_fastball_3>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        fastball_x_3=hori_x[251];
        fastball_y_3=hori_y[251];
    }
    if(mood_slow_ball_3==0 && collision_count_millisecond_slowball_3<=1000)
    {
        if(collision_counting_start_slowball_3)
        {
            collision_count_millisecond_slowball_3++;
        }
        if(collision_count_millisecond_slowball_3>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        slow_ball_x_3=hori_x[427];
        slow_ball_y_3=hori_y[427];
    }
    if(mood_danger_3==0)
    {
        danger_x_3=hori_x[248];
        danger_y_3=hori_y[248];
    }
    if(mood_extralife_3==0)
    {
        extra_life_x_3=hori_x[327];
        extra_life_y_3=hori_y[327];
    }
    if(mood_expand_3==1)
    {
        expand_y_3--;
        if(expand_y_3<platform_y-10)
        {
            mood_expand_3=0;
        }
        else if(platform_y+5>=expand_y_3 && platform_y<=expand_y_3+40 && expand_x_3+50>=platform_x && expand_x_3<=platform_x+platform_d)
        {
            mood_expand_3=0;
            collision_counting_start_expand_3=1;
            platform_d=80;
        }
    }
    if(mood_shrink_paddle_3==1)
    {
        shrink_paddle_y_3--;
        if(shrink_paddle_y_3<platform_y-10)
        {
            mood_shrink_paddle_3=0;
        }
        else if(platform_y+5>=shrink_paddle_y_3 && platform_y<=shrink_paddle_y_3+31 && shrink_paddle_x_3+33>=platform_x && shrink_paddle_x_3<=platform_x+platform_d)
        {
            mood_shrink_paddle_3=0;
            collision_counting_start_shrink_3=1;
            platform_d=30;
        }
    }
    if(mood_danger_3==1)
    {
        danger_y_3--;
        if(danger_y_3<platform_y-10)
        {
            mood_danger_3=0;
        }
        else if(platform_y+5>=danger_y_3 && platform_y<=danger_y_3+30 && danger_x_3+33>=platform_x && danger_x_3<=platform_x+platform_d)
        {
            if(cnt==3) cnt=2;
            else if(cnt==2) cnt=1;
            else if(cnt==1) cnt=0;
            mood_danger_3=0;
        }
    }
    if(mood_extralife_3==1)
    {
        extra_life_y_3--;
        if(extra_life_y_3<platform_y-10)
        {
            mood_extralife_3=0;
        }
        else if(platform_y+5>=extra_life_y_3 && platform_y<=extra_life_y_3+30 && extra_life_x_3+35>=platform_x && extra_life_x_3<=platform_x+platform_d)
        {
            if(cnt==2) cnt=3;
            else if(cnt==1) cnt=2;
            else if(cnt==0) cnt=0;
            mood_extralife_3=0;
        }
    }
    if(mood_fastball_3==1)
    {
        fastball_y_3--;
        if(fastball_y_3<platform_y-10)
        {
            mood_fastball_3=0;
        }
        else if(platform_y+5>=fastball_y_3 && platform_y<=fastball_y_3+30 && fastball_x_3+32>=platform_x && fastball_x_3<=platform_x+platform_d)
        {
            mood_fastball_3=0;
            collision_counting_start_fastball_3=1;
            if(dx>0 && dy>0)
            {
                dx=3;
                dy=4;
            }
            else if(dx<0 && dy<0)
            {
                dx=-3;
                dy=-4;
            }
            else if(dx<0 && dy>0)
            {
                dx=-3;
                dy=4;
            }
            else if(dx>0 && dy<0)
            {
                dx=3;
                dy=-4;
            }
        }
    }
    if(mood_slow_ball_3==1)
    {
        slow_ball_y_3--;
        if(slow_ball_y_3<platform_y-10)
        {
            mood_slow_ball_3=0;
        }
        else if(platform_y+5>=slow_ball_y_3 && platform_y<=slow_ball_y_3+31 && slow_ball_x_3+34>=platform_x && slow_ball_x_3<=platform_x+platform_d)
        {
            mood_slow_ball_3=0;
            collision_counting_start_slowball_3=1;
            if(dx>0 && dy>0)
            {
                dx=1;
                dy=2;
            }
            else if(dx<0 && dy<0)
            {
                dx=-1;
                dy=-2;
            }
            else if(dx<0 && dy>0)
            {
                dx=-1;
                dy=2;
            }
            else if(dx>0 && dy<0)
            {
                dx=1;
                dy=-2;
            }
        }
    }
}
void level4_icon_change()
{
    if(mood_expand_4==0 && collision_count_millisecond_expand_4<=1000)
    {
        if(collision_counting_start_expand_4)
        {
            collision_count_millisecond_expand_4++;
        }
        if(collision_count_millisecond_expand_4>1000)
        {
            platform_d=50;
        }
        expand_x_4=hori_x[264];
        expand_y_4=hori_y[264];
    }
    if(mood_shrink_paddle_4==0 && collision_count_millisecond_shrink_4<=1000)
    {
        if(collision_counting_start_shrink_4)
        {
            collision_count_millisecond_shrink_4++;
        }
        if(collision_count_millisecond_shrink_4>1000)
        {
            platform_d=50;
        }
        shrink_paddle_x_4=hori_x[18];
        shrink_paddle_y_4=hori_y[18];
    }
    if(mood_fastball_4==0 && collision_count_millisecond_fastball_4<=1000)
    {
        if(collision_counting_start_fastball_4)
        {
            collision_count_millisecond_fastball_4++;
        }
        if(collision_count_millisecond_fastball_4>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        fastball_x_4=hori_x[33];
        fastball_y_4=hori_y[33];
    }
    if(mood_slow_ball_4==0 && collision_count_millisecond_slowball_4<=1000)
    {
        if(collision_counting_start_slowball_4)
        {
            collision_count_millisecond_slowball_4++;
        }
        if(collision_count_millisecond_slowball_4>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        slow_ball_x_4=vert_x[543];
        slow_ball_y_4=vert_y[543];
    }
    if(mood_danger_4==0)
    {
        danger_x_4=hori_x[262];
        danger_y_4=hori_y[262];
    }
    if(mood_extralife_4==0)
    {
        extra_life_x_4=vert_x[507];
        extra_life_y_4=vert_y[507];
    }
    if(mood_expand_4==1)
    {
        expand_y_4--;
        if(expand_y_4<platform_y-10)
        {
            mood_expand_4=0;
        }
        else if(platform_y+5>=expand_y_4 && platform_y<=expand_y_4+40 && expand_x_4+50>=platform_x && expand_x_4<=platform_x+platform_d)
        {
            mood_expand_4=0;
            collision_counting_start_expand_4=1;
            platform_d=80;
        }
    }
    if(mood_shrink_paddle_4==1)
    {
        shrink_paddle_y_4--;
        if(shrink_paddle_y_4<platform_y-10)
        {
            mood_shrink_paddle_4=0;
        }
        else if(platform_y+5>=shrink_paddle_y_4 && platform_y<=shrink_paddle_y_4+31 && shrink_paddle_x_4+33>=platform_x && shrink_paddle_x_4<=platform_x+platform_d)
        {
            mood_shrink_paddle_4=0;
            collision_counting_start_shrink_4=1;
            platform_d=30;
        }
    }
    if(mood_danger_4==1)
    {

        danger_y_4--;
        if(danger_y_4<platform_y-10)
        {
            mood_danger_4=0;
        }
        else if(platform_y+5>=danger_y_4 && platform_y<=danger_y_4+30 && danger_x_4+33>=platform_x && danger_x_4<=platform_x+platform_d)
        {
            if(cnt==3) cnt=2;
            else if(cnt==2) cnt=1;
            else if(cnt==1) cnt=0;
            mood_danger_4=0;
        }
    }
    if(mood_extralife_4==1)
    {
        extra_life_y_4--;
        if(extra_life_y_4<platform_y-10)
        {
            mood_extralife_4=0;
        }
        else if(platform_y+5>=extra_life_y_4 && platform_y<=extra_life_y_4+30 && extra_life_x_4+35>=platform_x && extra_life_x_4<=platform_x+platform_d)
        {
            if(cnt==2) cnt=3;
            else if(cnt==1) cnt=2;
            else if(cnt==0) cnt=0;
            mood_extralife_4=0;
        }
    }
    if(mood_fastball_4==1)
    {
        fastball_y_4--;
        if(fastball_y_4<platform_y-10)
        {
            mood_fastball_4=0;
        }
        else if(platform_y+5>=fastball_y_4 && platform_y<=fastball_y_4+30 && fastball_x_4+32>=platform_x && fastball_x_4<=platform_x+platform_d)
        {
            mood_fastball_4=0;
            collision_counting_start_fastball_4=1;
            if(dx>0 && dy>0)
            {
                dx=3;
                dy=4;
            }
            else if(dx<0 && dy<0)
            {
                dx=-3;
                dy=-4;
            }
            else if(dx<0 && dy>0)
            {
                dx=-3;
                dy=4;
            }
            else if(dx>0 && dy<0)
            {
                dx=3;
                dy=-4;
            }
        }
    }
    if(mood_slow_ball_4==1)
    {
        slow_ball_y_4--;
        if(slow_ball_y_4<platform_y-10)
        {
            mood_slow_ball_4=0;
        }
        else if(platform_y+5>=slow_ball_y_4 && platform_y<=slow_ball_y_4+31 && slow_ball_x_4+34>=platform_x && slow_ball_x_4<=platform_x+platform_d)
        {
            mood_slow_ball_4=0;
            collision_counting_start_slowball_4=1;
            if(dx>0 && dy>0)
            {
                dx=1;
                dy=2;
            }
            else if(dx<0 && dy<0)
            {
                dx=-1;
                dy=-2;
            }
            else if(dx<0 && dy>0)
            {
                dx=-1;
                dy=2;
            }
            else if(dx>0 && dy<0)
            {
                dx=1;
                dy=-2;
            }
        }
    }
}
void level5_icon_change()
{
    if(mood_expand_5==0 && collision_count_millisecond_expand_5<=1000)
    {
        if(collision_counting_start_expand_5)
        {
            collision_count_millisecond_expand_5++;
        }
        if(collision_count_millisecond_expand_5>1000)
        {
            platform_d=50;
        }
        expand_x_5=hori_x[254];
        expand_y_5=hori_y[254];
    }
    if(mood_shrink_paddle_5==0 && collision_count_millisecond_shrink_5<=1000)
    {
        if(collision_counting_start_shrink_5)
        {
            collision_count_millisecond_shrink_5++;
        }
        if(collision_count_millisecond_shrink_5>1000)
        {
            platform_d=50;
        }
        shrink_paddle_x_5=hori_x[46];
        shrink_paddle_y_5=hori_y[46];
    }
    if(mood_fastball_5==0 && collision_count_millisecond_fastball_5<=1000)
    {
        if(collision_counting_start_fastball_5)
        {
            collision_count_millisecond_fastball_5++;
        }
        if(collision_count_millisecond_fastball_5>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        fastball_x_5=hori_x[142];
        fastball_y_5=hori_y[142];
    }
    if(mood_slow_ball_5==0 && collision_count_millisecond_slowball_5<=1000)
    {
        if(collision_counting_start_slowball_5)
        {
            collision_count_millisecond_slowball_5++;
        }
        if(collision_count_millisecond_slowball_5>1000)
        {
            if(dx>0 && dy>0)
            {
                dx=2;
                dy=3;
            }
            else if(dx<0 && dy<0)
            {
                dx=-2;
                dy=-3;
            }
            else if(dx<0 && dy>0)
            {
                dx=-2;
                dy=3;
            }
            else if(dx>0 && dy<0)
            {
                dx=2;
                dy=-3;
            }
        }
        slow_ball_x_5=hori_x[385];
        slow_ball_y_5=hori_y[385];
    }
    if(mood_danger_5==0)
    {
        danger_x_5=hori_x[136];
        danger_y_5=hori_y[136];
    }
    if(mood_extralife_5==0)
    {
        extra_life_x_5=hori_x[487];
        extra_life_y_5=hori_y[487];
    }
    if(mood_expand_5==1)
    {
        expand_y_5--;
        if(expand_y_5<platform_y-10)
        {
            mood_expand_5=0;
        }
        else if(platform_y+5>=expand_y_5 && platform_y<=expand_y_5+40 && expand_x_5+50>=platform_x && expand_x_5<=platform_x+platform_d)
        {
            mood_expand_5=0;
            collision_counting_start_expand_5=1;
            platform_d=80;
        }
    }
    if(mood_shrink_paddle_5==1)
    {
        shrink_paddle_y_5--;
        if(shrink_paddle_y_5<platform_y-10)
        {
            mood_shrink_paddle_5=0;
        }
        else if(platform_y+5>=shrink_paddle_y_5 && platform_y<=shrink_paddle_y_5+31 && shrink_paddle_x_5+33>=platform_x && shrink_paddle_x_5<=platform_x+platform_d)
        {
            mood_shrink_paddle_5=0;
            collision_counting_start_shrink_5=1;
            platform_d=30;
        }
    }
    if(mood_danger_5==1)
    {
        danger_y_5--;
        if(danger_y_5<platform_y-10)
        {
            mood_danger_5=0;
        }
        else if(platform_y+5>=danger_y_5 && platform_y<=danger_y_5+30 && danger_x_5+33>=platform_x && danger_x_5<=platform_x+platform_d)
        {
            if(cnt==3) cnt=2;
            else if(cnt==2) cnt=1;
            else if(cnt==1) cnt=0;
            mood_danger_5=0;
        }
    }
    if(mood_extralife_5==1)
    {
        extra_life_y_5--;
        if(extra_life_y_5<platform_y-10)
        {
            mood_extralife_5=0;
        }
        else if(platform_y+5>=extra_life_y_5 && platform_y<=extra_life_y_5+30 && extra_life_x_5+35>=platform_x && extra_life_x_5<=platform_x+platform_d)
        {
            if(cnt==2) cnt=3;
            else if(cnt==1) cnt=2;
            else if(cnt==0) cnt=0;
            mood_extralife_5=0;
        }
    }
    if(mood_fastball_5==1)
    {
        fastball_y_5--;
        if(fastball_y_5<platform_y-10)
        {
            mood_fastball_5=0;
        }
        else if(platform_y+5>=fastball_y_5 && platform_y<=fastball_y_5+30 && fastball_x_5+32>=platform_x && fastball_x_5<=platform_x+platform_d)
        {
            mood_fastball_5=0;
            collision_counting_start_fastball_5=1;
            if(dx>0 && dy>0)
            {
                dx=3;
                dy=4;
            }
            else if(dx<0 && dy<0)
            {
                dx=-3;
                dy=-4;
            }
            else if(dx<0 && dy>0)
            {
                dx=-3;
                dy=4;
            }
            else if(dx>0 && dy<0)
            {
                dx=3;
                dy=-4;
            }
        }
    }
    if(mood_slow_ball_5==1)
    {
        slow_ball_y_5--;
        if(slow_ball_y_5<platform_y-10)
        {
            mood_slow_ball_5=0;
        }
        else if(platform_y+5>=slow_ball_y_5 && platform_y<=slow_ball_y_5+31 && slow_ball_x_5+34>=platform_x && slow_ball_x_5<=platform_x+platform_d)
        {
            mood_slow_ball_5=0;
            collision_counting_start_slowball_5=1;
            if(dx>0 && dy>0)
            {
                dx=1;
                dy=2;
            }
            else if(dx<0 && dy<0)
            {
                dx=-1;
                dy=-2;
            }
            else if(dx<0 && dy>0)
            {
                dx=-1;
                dy=2;
            }
            else if(dx>0 && dy<0)
            {
                dx=1;
                dy=-2;
            }
        }
    }
}



