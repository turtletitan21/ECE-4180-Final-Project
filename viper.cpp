// ============================================
// The Viper class file
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "viper.h"


void viper_init (Viper * v)
{ 
  
    /*
    int head_x, head_y, head_px, head_py; // Location of the head of the viper
    int tail_x, tail_y, tail_px, tail_py;
    int length; // length of the viper
    Coordinate locations[VIPER_MAX_LENGTH]; // Viper body locations
    int score; //Current score of the viper
    int boost_up; //Current number of boost up in viper
    int boost_down; //current number of boost down in viper
    */
    
    
    // TODO: Implement
    //1. Set starting coordinates for your viper head and previous
    v->head_x = 5;
    v->head_y = 5;
    v->head_px = 5;
    v->head_py = 5;
    
    
    
    //2. Initialize all location for your maximum viper body (loop through the viper)
    for (int i = 0; i < VIPER_MAX_LENGTH; i++) {
        v->locations[i].x = -1;
        v->locations[i].y = -1;
    }

    //3. Set starting length of your viper
    v->length = 3;

    //4. Set starting coordinates for the rest of viper body from starting length
    for (int i = 0; i < v->length; i++) {
        v->locations[i].x = 5 - i;
        v->locations[i].y = 5;
    }

    //5. Initialize viper status
    v->tail_x = v->locations[v->length-1].x;
    v->tail_y = v->locations[v->length-1].y;
    v->tail_px = v->locations[v->length-1].x;
    v->tail_px = v->locations[v->length-1].y;
    v->score = 0;
    v->invincible = false;
    v->speed = 100;

}
