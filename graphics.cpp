// ============================================
// The Graphics class file
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "graphics.h"

#include "globals.h"

#include "hardware.h"


void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define DIRT   BROWN
#define TEAL   0x008080
#define RED    0xFF0000
#define WHITE  0xFFFFFF
#define BLACK  0x000000 
#define GOLD   0xD4AF37
#define LBLUE  0xADD8E6
#define AQUA   0x66DDAA
#define ORANGE 0xFFA500
#define MAROON 0x8B0000
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'L') colors[i] = LBLUE;
        else if (img[i] == '1') colors[i] = GOLD;
        else if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == '2') colors[i] = BROWN;
        else if (img[i] == 'B') colors[i] = BLACK;
        else if (img[i] == 'T') colors[i] = TEAL;
        else if (img[i] == 'A') colors[i] = AQUA;
        else if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'M') colors[i] = MAROON;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'O') colors[i] = ORANGE;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_wall(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper
    char wall[122]="MMMMOMMMMMMMOOMOMMMMOMMMMMOMMMMOMMMMMMMMMMOMMMMMMOOMMOMMMMMMMMMMOMMMMOOMMMMMMMMMMMMMMMMMMMMMMMMOOMMMOOMMMMMMMMMMMMMMMMOOM";
    draw_img(u,v,wall);
}

void draw_plant(int u, int v)
{
    char plant[122]="BBBBLLLBBBBBBBLLLLLBBBBBLLLLLLLBBBBLLLLLLBBBBBBLLLLLBBBBBBLLLLLBBBBBBBLLLBBBBBBBBBLBBBBBBBBBB2BBBBBBBBBB2BBBBBBBBBB2BBBBB";
    draw_img(u,v,plant);
}

void draw_chest(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper
    
    /*
     ---OOOOO---
     --OOOOOOO--
     -OOOOOOGGO-
     OOOOOOGGGOO
     OOOOOOGOOOO
     OOOOOOOGGGO
     OOOOOOOOGGO
     OOOOOOOOOOO
     -OOOOOOOOO-
     --OOOOOOO--
     ---OOOOO---
    */
    char chest[122] = "---OOOOO-----OOOOOOO---OOOOOOGGO-OOOOOOGGGOOOOOOOOGOOOOOOOOOOOGGGOOOOOOOOOGGOOOOOOOOOOOO-OOOOOOOOO---OOOOOOO-----OOOOO---";
    draw_img(u, v, chest);
}

void draw_viper_body(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper
    char body[122] = "---GGGGG-----GGGGGGG---GGGGGGGGG-GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG-GGGGGGGGG---GGGGGGG-----GGGGG---";
    draw_img(u, v, body);
}

void draw_viper_head(int u, int v)
{
    // TODO: Implement
    //May need to design a viper head sprite
    //Tile still need to be designed on paper
    
    /*
     -----GGGGGG
     ----GGG--GG
     ---GGGG--GG
     --GGGGGGGGG
     -GGGGGGGGGG
     GGGGGGGGGGG
     -GGGGGGGGGG
     --GGGGGGGGG
     ---GGGG--GG
     ----GGG--GG
     -----GGGGGG
    */

    
    char head[122] = "-----GGGGGG----GGG--GG---GGGG--GG--GGGGGGGGG-GGGGGGGGGGGGGGGGGGGGG-GGGGGGGGGG--GGGGGGGGG---GGGG--GG----GGG--GG----GGGGGG";
    draw_img(u, v, head);
    //EAST
}

void draw_viper_head_south(int u, int v) 
{
    /*
     ----GGG----
     ---GGGGG---
     --GGGGGGG--
     -GGGGGGGGG-
     GGGGGGGGGGG
     GGGGGGGGGGG
     GGGGGGGGGGG
     G--GGGGG--G
     G--GGGGG--G
     GGGGGGGGGGG
     GGGGGGGGGGG
     
    */
    char head[122] = "----GGG-------GGGGG-----GGGGGGG---GGGGGGGGG-GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG--GGGGG--GG--GGGGG--GGGGGGGGGGGGGGGGGGGGGGG";
    draw_img(u, v, head);
}

void draw_viper_head_north(int u, int v) 
{
    /*
     GGGGGGGGGGG
     GGGGGGGGGGG
     G--GGGGG--G
     G--GGGGG--G
     GGGGGGGGGGG
     GGGGGGGGGGG
     GGGGGGGGGGG
     -GGGGGGGGG-
     --GGGGGGG--
     ---GGGGG---
     ----GGG----
    */
    char head[122] = "GGGGGGGGGGGGGGGGGGGGGGG--GGGGG--GG--GGGGG--GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG-GGGGGGGGG---GGGGGGG-----GGGGG-------GGG----";
    draw_img(u, v, head);
}

void draw_viper_head_west(int u, int v) 
{
    /*
     GGGGGGG----
     GG--GGGG---
     GG--GGGGG--
     GGGGGGGGGG-
     GGGGGGGGGGG
     GGGGGGGGGGG
     GGGGGGGGGGG
     GGGGGGGGGG-
     GG--GGGGG--
     GG--GGGG---
     GGGGGGG----
    */
    char head[122] = "GGGGGGG----GG--GGGG---GG--GGGGG--GGGGGGGGGG-GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG-GG--GGGGG--GG--GGGG---GGGGGGG----";
    draw_img(u, v, head);
}

void draw_viper_tail(int u, int v)
{
    // TODO: Implement
    //May need to design a viper tail sprite
    //Tile still need to be designed on paper
    
     /*
     GGGGGG-----
     GGGGGGG----
     -GGGGGGG---
     --GGGGGGG--
     ---GGGGGGG-
     ---GGGGGGGG
     ---GGGGGGG-
     --GGGGGGG--
     -GGGGGGG---
     GGGGGGG----
     GGGGGG-----
    
    */
    char tail[122] = "GGGGGG-----GGGGGGG-----GGGGGGG-----GGGGGGG-----GGGGGGG----GGGGGGGG---GGGGGGG---GGGGGGG---GGGGGGG---GGGGGGG----GGGGGG-----";
    draw_img(u, v, tail);
}

void draw_boost_up(int u, int v)
{
    // TODO: Implement
    //May need to design a viper tail sprite
    //Tile still need to be designed on paper
     /*
     ----YYY----
     ---YYYYY---
     --YYY-YYY--
     -YYY---YYY-
     YYY--Y--YYY
     YY--YYY--YY
     ---YYYYY---
     --YYY-YYY--
     -YYY---YYY-
     YYY-----YYY
     YY-------YY

    */
    char boostUp[122]="----YYY-------YYYYY-----YYY-YYY---YYY---YYY-YYY--Y--YYYYY--YYY--YY---YYYYY-----YYY-YYY---YYY---YYY-YYY-----YYYYY-------YY";
    draw_img(u, v, boostUp);
}

void draw_life(int u, int v)
{
    //drawn on paper
    char life[122]="BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBTTBTTBBBBBTTTTTTTBBBBTTTTTTTBBBBTTTTTTTBBBBBTTTTTBBBBBBTTTTTBBBBBBBTTTBBBBBBBBBTBBBBB";
    draw_img(u, v, life);
    
}

void draw_boost_down(int u, int v)
{
    // TODO: Implement
    //May need to design a viper tail sprite
    //Tile still need to be designed on paper
    char boostDown[122] = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBOBBBBBBBBOOOBBBBBBBOOOOOBBBBBBOOOOOBBBOBOOOOOOOOOOOOOOOOOO";
    draw_img(u, v, boostDown);
}

void gamewon() {
    uLCD.filled_rectangle(3, 15, 126, 113, BLACK);
    uLCD.text_string("YOU WON", 5, 3, FONT_12X16, RED);
    uLCD.text_string("DON'T HACK", 4, 5, FONT_12X16, RED);   
    uLCD.text_string("NEXT TIME", 4, 6, FONT_12X16, RED);
}

void gameover() {
    // Cover map
    uLCD.filled_rectangle(3, 15, 126, 113, BLACK);

    // Write message
    uLCD.text_string("GAME OVER", 5, 3, FONT_12X16, RED);
    uLCD.text_string("DAMN!", 7, 5, FONT_12X16, RED);
    uLCD.text_string("You're Terrible", 2, 7, FONT_12X16, RED);
    uLCD.text_string("RESTART (Button 3)", 1, 9, FONT_12X16, RED);

    
    

    
}
void draw_blue_wall(int u, int v)
{
    char wall[122]="LLLLLLLLLLLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLLLLLLLLLLL";
    draw_img(u,v,wall);
}

// void draw_border()
// {
//     uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
//     uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
//     uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
//     uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
// }

// void draw_timer() {
    
// }

void draw_start_page()
{
    // fill in borders
    //draw_border();

    // Cover map
    uLCD.filled_rectangle(3, 15, 126, 113, BLACK);

    // Write message
    uLCD.text_string("---------------", 1, 2, FONT_5X7, BLUE);
    uLCD.text_string("SNAKE GAME", 4, 4, FONT_12X16, BLUE);
    uLCD.text_string("by Raj Patel", 3, 5, FONT_5X7, BLUE);
    uLCD.text_string("---------------", 1, 7, FONT_5X7, BLUE);
    // wait_ms(5000);
    PwmOut speaker(p26);
    for (int i=0; i<2800; i=i+100) {
        speaker.period(1.0/float(i));
        speaker=0.25;
        wait_ms(100);
    }
    for (int i=0; i<300; i=i+100) {
        wait_ms(500);
    }
    speaker = 0.00;
    uLCD.cls();
}

void draw_menu() 
{
    uLCD.cls();
    uLCD.filled_rectangle(3, 15, 126, 113, BLACK);
    // Write message
    uLCD.text_string("GAME PAUSED", 4, 7, FONT_12X16, BLUE);
    // uLCD.text_string("by Raj Patel", 3, 5, FONT_5X7, BLUE);
    // uLCD.locate(4,4);
    // // uLCD.printf("GAME PAUSED");
    // uLCD.text_mode(OPAQUE);
    // uLCD.text_string("GAME PAUSED", 4, 4, FONT_5X7, RED);
}

void draw_gamemode() 
{
    uLCD.filled_rectangle(3, 15, 126, 113, BLACK);
    uLCD.text_string("SELECT DIFFICULTY", 1, 2, FONT_12X16, BLUE);
    uLCD.text_string("EASY (button 1)", 2, 5, FONT_12X16, BLUE);
    uLCD.text_string("HARD (button 2)", 2, 7, FONT_12X16, BLUE);
}

void draw_timer()
{
    uLCD.text_string("Game starts in:", 2, 8, FONT_5X7, BLUE);
    // uLCD.text_width(2); //1X size text
    // uLCD.text_height(2);
    // uLCD.set_font_size(4, 4);
    uLCD.color(RED);
    for (int i=10; i>=1; --i) {
        uLCD.locate(7,10);
        uLCD.printf("%2D",i);
        wait_ms(1000);
    }
    uLCD.cls();
}

void draw_instructions()
{
    uLCD.printf("Eat oranges to increase score.\n");
    uLCD.printf("EASY GAME MODE --> multiple lives and sticky Joystick OFF\n");
    uLCD.printf("HARD GAME MODE --> no extra lives and sticky Joystick ON\n");
    wait_ms(10000);
    uLCD.cls();

}



