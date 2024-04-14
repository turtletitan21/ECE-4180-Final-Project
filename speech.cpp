// // ============================================
// // The Speech class file
// //
// // Copyright 2022 Georgia Tech. All rights reserved.
// // The materials provided by the instructor in this course are for
// // the use of the students currently enrolled in the course.
// // Copyrighted course materials may not be further disseminated.
// // This file must NOT be made publicly available anywhere.
// //==================================================================

// #include "speech.h"

// #include "globals.h"
// #include "hardware.h"


// /**
//  * Draw the speech bubble background.
//  */
// static void draw_speech_bubble();

// /**
//  * Erase the speech bubble.
//  */
// static void erase_speech_bubble();

// /**
//  * Draw a single line of the speech bubble.
//  * @param line The text to display
//  * @param which If TOP, the first line; if BOTTOM, the second line.
//  */
// #define TOP     0
// #define BOTTOM  1
// static void draw_speech_line(const char *line, int which);

// #define YELLOW 0xFFFF00
// void draw_speech_bubble()
// {
//     // TODO: Implement
    
//     //***
//     // HINT: for this function and below: Check out the ULCD demo in the docs to see what
//     // uLCD methods you can use to draw graphics 
    
//     //Link: https://os.mbed.com/users/4180_1/notebook/ulcd-144-g2-128-by-128-color-lcd/
//     //***
//     uLCD.filled_rectangle(0,100,127,127, WHITE);
// }   

// void erase_speech_bubble()
// {
//     // TODO: Implement
//     uLCD.filled_rectangle(0,100,127,127, BLACK);
// }

// void draw_speech_line(const char *line, int which)
// {
//     // TODO: Implement
//     uLCD.text_string((char*) line, 1, 12 + which, FONT_5X7, GREEN);
// }

// void speech_bubble_wait()
// {
//     // TODO: Implement
//     GameInputs in;

//     Timer c; c.start();

//     // Get inputs and display a flashing button
//     // while waiting for action button to be pressed
//     do {
//         Timer t; t.start();

//         int dc = c.read_ms();
//         if (dc > 1000) {
//             uLCD.filled_circle(120, 114, 3, DGREY);
//             c.reset();
//         }
//         else if (dc > 500)
//             uLCD.filled_circle(120, 114, 3, LGREY);

//         in = read_inputs();

//         t.stop();
//         int dt = t.read_ms();
//         if (dt < 100) wait_ms(100 - dt);
//     }while(in.b1);
// }

// void speech(const char *line1, const char *line2)
// {
//     // TODO: Implement
//     draw_speech_bubble();
//     draw_speech_line(line1, TOP);
//     draw_speech_line(line2, BOTTOM);
//     speech_bubble_wait();
//     erase_speech_bubble();
// }

// void long_speech(const char *lines[], int n)
// {
//     // TODO: Implement
//      int i;
//     int length = (n % 2) ? n-1 : n;
//     for(i = 0; i < length; i++)
//         speech(lines[i++], lines[i]);
//     if(length == n-1) speech(lines[n-1], "");
// }
