//=================================================================
// The main program file.
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


// PROJECT INCLUDES
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "viper.h"
#include "mbed.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Important definitions


/////////////////////////////////////////////////////////////////////////////////////////

// GLOBAL VARS
Viper viper;

/////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION PROTOTYPES
void playSound(char* wav);
int get_action(GameInputs inputs);
int update_game(int action);
void draw_upper_status();
void draw_lower_status();
void draw_border();
void draw_game(int draw_option);
void init_main_map();

 
bool game_paused = false;
bool sticky_joystick = false;  
int max_length; 
int num_lives = 3; 
int game_mode;
bool reset = false;  

/////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION DEFINITIONS
/**
 * Program entry point! This is where it all begins.
 * This function is for all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */

int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    viper_init(&viper);
    max_length = VIPER_MAX_LENGTH; 
    
    // 0. Initialize the maps
    // TODO: implement maps_init() and init_main_map() function in map.cpp:
    maps_init();
    init_main_map();


    // Initialize game state
    set_active_map(0);
    viper.head_x = viper.head_y = 5;
    // viper.dir = NORTH; 
    
    draw_start_page(); 
    //draw_instructions();
    draw_gamemode(); 
    GameInputs select; 
    int difficulty;  
    while(!difficulty) {

        while(select.b1 && select.b2) {
            Timer t; 
            t.start();
            select = read_inputs();

            t.stop();
            int dt = t.read_ms();
            if (dt < 100) wait_ms(100 - dt);
        }

        difficulty = get_action(select); 
        if(difficulty == INVINCIBILITY_BUTTON) {
            uLCD.cls();
            uLCD.printf("EASY SELECTED");
            game_mode = 1; 
            max_length = 13; 
            wait_ms(1000);
            //uLCD.cls();
            draw_timer();
            draw_game(FULL_DRAW);
            break; 
        } else if (difficulty == MENU_BUTTON) {
            uLCD.cls();
            sticky_joystick = true; 
            uLCD.printf("HARD SELECTED");
            game_mode = 2; 
            max_length = 18; 
            wait_ms(1000);
            //uLCD.cls();
            draw_timer();
            draw_game(FULL_DRAW);
            break;
        }
    }
    // Initial drawing
    //draw_game(FULL_DRAW);
   
    // Main game loop
    int temp_speed = viper.speed;
    while(1) {
        // Timer to measure game update speed
        Timer t;
        t.start();

        // 1. Read inputs 
        //TODO: implement read_inputs() function in hardware.cpp:
        GameInputs inputs = read_inputs();
        
        // 2. Determine action (move, act, menu, etc.)
        //TODO: implement get_action() function:
        int action = get_action(inputs);
        if(action == MENU_BUTTON) {
            if (game_paused == true) {
                game_paused = false; 
                viper.speed = temp_speed;
                draw_game(1);
            } else { 
                viper.speed = 0; 
                //uLCD.filled_rectangle(3, 15, 126, 113, BLACK);
                game_paused = true; 
                draw_menu();
            }
        }
        
        // 3. Update game
        //TODO: implement update_game() function:
        
        
        int result; 
        result = update_game(action);
        

        uLCD.filled_rectangle(0, 0, 160, 7, BLACK);
        char str[1024];
        _snprintf(str,sizeof(str),"Pos:%d,%d Score:%d",viper.head_x,viper.head_y,viper.score);
        uLCD.text_string(str,0,0,FONT_7X8,RED);

        if (game_mode == 1) {
            uLCD.filled_rectangle(1, 15, 160, 7, BLACK);
            _snprintf(str,sizeof(str),"Lives:%d",num_lives);
            uLCD.text_string(str,1,15,FONT_7X8,RED);
        }
        
        // 3b. Check for game over based on result  
        // and if so, handle game over

        //TODO: implement this here or as a new function.
        
        //      3b1. if game is over, then
        //      3b2. draw and display tezt for game over sign
        
        if (result == GAME_WON) {
            gamewon();  
            return 1;  
        }

        if (result == GAME_OVER) {
            gameover();
            GameInputs select_restart; 
            int restart; 
            while (select_restart.b3) {
                Timer timer; 
                timer.start(); 
                select_restart = read_inputs(); 
                timer.stop(); 
                int dtimer = timer.read_ms(); 
                if (dtimer < 100) wait_ms(100 - dtimer); 
            }
            restart = get_action(select_restart); 
            if (restart == BUTTON_THREE) {
                map_reset();
                uLCD.cls();
                num_lives = 3; 
                viper.dir = EAST;
                uLCD.printf("Restarting...");
                
            }
            main();
            return 1;
        } 

        // 4. Draw screen -- provided.
        draw_game(result);
        
        // Compute update time
        t.stop();
        int dt = t.read_ms();

        // Display and wait
        // NOTE: Text is 8 pixels tall
        if (dt < 100) wait_ms(100 - dt);
    }
}

/**
 * Plays a .wav file
 */
void playSound(char* wav)
{
    // OPTIONAL: Implement
    
}



void eat_fx() 
{
    PwmOut speaker(p26);
    speaker.period(1.0/500.0); // 500hz period
    speaker =0.25; //25% duty cycle - mid range volume
    wait_ms(50);
    speaker=0.0; // turn off audio
}
/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 * Get Actions from User (pushbuttons, and nav_switch)
 * Based on push button and navigation switch inputs, determine which action
 * needs to be performed (may be no action).
 */
int get_action(GameInputs inputs)
{
    // TODO: Implement
    
    // 1. Check your action and menu button inputs and return the corresponding action value

    // 2. Check for your navigation switch inputs and return the corresponding action value
    
    // If no button is pressed, just return no action value
    if (!inputs.b1) {
      return INVINCIBILITY_BUTTON;  
    } else if (!inputs.b2) {
        return MENU_BUTTON;
    } else if (!inputs.b3) {
        return BUTTON_THREE;
    } else if (inputs.ns_left) {
        return GO_LEFT;    
    } else if (inputs.ns_right) {
        return GO_RIGHT;    
    } else if (inputs.ns_up) {
        return GO_UP;
    } else if (inputs.ns_down) {
        return GO_DOWN;    
    } else {
        return NO_ACTION;
    }
    
}

/**
 * This function is called by update game to check when the snake 
 * gets an object (in other words, when a snake eats an object). We 
 * update the snake and game conditions as needed based on the object type
 */
int get_object(){
    
    //TODO: Implement
    
    // 1. Get item at current head location
    MapItem *item = get_here(viper.head_x, viper.head_y);
    
    // 2. Initialize a return value variable to denote the item type we got
    int output;
    
    // 3. Check if item is valid and is a chest
    //    3a. if so, increment the score, extend the length of the viper
    //    3b. Remove the chest
    //    3c. set the return value variable to GOT_LENGTH
    if (item != NULL && item->type == CHEST) {
            
                viper.score = viper.score + 1;
                map_erase(viper.head_x, viper.head_y);
                viper.length = viper.length + 1;
                eat_fx();
                output = GOT_LENGTH;    
    }
    
    // 4. Else, check if the item is valid a boost-up/boost-down
    //    4a. if so, set the ability for the viper based on the type of item
    //          for the right amount fo time
    //    4b. Remove the boost-up/down item
    //    4c. Set the return value variable to GOT_OBJ
    //    Hint: You have to do this check for all your boost-ups/downs. Might be 
    //          easier to use Switch statements.
    else if (item != NULL && (item->type == BOOST_DOWN || item->type == BOOST_UP || item-> type == LIFE)) {
        if (item -> type == BOOST_UP) {
            for(int i = viper.head_x; i < viper.head_x + 5; i+=3) {
                for (int j = viper.head_y; j < viper.head_y + 5; j+=3) {
                    MapItem* this_coord = get_here(i, j);
                    if (this_coord) {
                        draw_nothing(i,j);
                    } else {
                        add_chest(i,j);
                    }
                }
            }
            // add_chest(viper.head_x - 1, viper.head_y - 5); 
            // add_chest(viper.head_x - 5, viper.head_y - 5);
            // add_chest(viper.head_x + 5, viper.head_y + 5);
            // add_chest(viper.head_x + 5, viper.head_y + 1);
            // add_chest(viper.head_x - 5, viper.head_y + 1);
            // add_chest(viper.head_x - 1, viper.head_y + 5);
            output = BOOST_UP;
        } 
        else if (item -> type == BOOST_DOWN) {
            add_wall(viper.head_x + 2, viper.head_y, VERTICAL, 5);
            add_wall(viper.head_x, viper.head_y + 2, HORIZONTAL, 5);
            output = BOOST_DOWN;
            num_lives--; 
        } else if (item->type == LIFE) {
            num_lives++;
            output = LIFE;
        }
    }  
    
    // 5. Check if the return value variable is GOT_LENGTH
    //    5a. If so, then increase the snake length and update its locations as needed
    //        Hint: Refer to Step 6 below; the main difference is that you need 
    //        to lengthen the snake (what should we change the snake tail position to?)
    if (output == GOT_LENGTH) {
        map_erase(viper.locations[viper.length-2].x, viper.locations[viper.length-2].y);
        
        for(int i = viper.length - 1; i > 0; i--) {
            viper.locations[i] = viper.locations[i-1];    
        }
        viper.locations[0].x = viper.head_x;
        viper.locations[0].y = viper.head_y;
        add_viper_head(viper.locations[0].x, viper.locations[0].y);
        add_viper_body(viper.locations[1].x, viper.locations[1].y);
        add_viper_body(viper.locations[viper.length-2].x, viper.locations[viper.length-2].y);
        add_viper_tail(viper.locations[viper.length-1].x, viper.locations[viper.length-1].y);
        
        viper.tail_py = viper.tail_y;
        viper.tail_y = viper.locations[viper.length-1].y;
        viper.tail_px = viper.tail_x;
        viper.tail_x = viper.locations[viper.length-1].x;

    } 
    
    // 6. For any other object, do the following default steps
    //    6a. initialize two variables to to denote the original location for the x and y tail of the viper
    //    6b. For each location of the viper body, move them forward by one location
    //    6c. Update the initial viper location to the viper head x and y location
    //    6d. call a function to add a viper head given the head x and y location
    //    6e. call a function to add a viper body to the location after the head
    //    6f. call a function to add a viper tail to the location of the last viper locations
    //    6g. call a function to map erase the original location for the x and y tail
    //    6h. return the return value variable
    else {
        map_erase(viper.locations[viper.length-1].x, viper.locations[viper.length-1].y);
        for(int i = viper.length - 1; i > 0; i--) {
            viper.locations[i] = viper.locations[i-1];    
        }
        viper.locations[0].x = viper.head_x;
        viper.locations[0].y = viper.head_y;
        add_viper_head(viper.locations[0].x, viper.locations[0].y);
        add_viper_body(viper.locations[1].x, viper.locations[1].y);
        add_viper_tail(viper.locations[viper.length-1].x, viper.locations[viper.length-1].y);
        viper.tail_px = viper.tail_x;
        viper.tail_x = viper.locations[viper.length-1].x;
        viper.tail_py = viper.tail_y;
        viper.tail_y = viper.locations[viper.length-1].y;
        
    }
    
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the viper position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the viper has not moved.
 */
 
 
int update_game(int action)
{
    // TODO: Implement
    
    // 1. Check the viper speed and update viper speed status
    
    // 2. Update the previous viper head position to the current position
    
    // 3. Check if action is to go up

        //3a. Get item north of the current viper head
        
        
        //3b. Update the current viper head position upwards
        
        
        //3c. Check if the item exist and item is walkable
       
        
         //3d. Check if the viper gets an object (eats) by calling another function
       
    int moving = 0;
    // TODO: Implement
    if (viper.speed && sticky_joystick) {
        moving = 1;
        wait_ms(100 - viper.speed);
    }
    
    viper.head_px = viper.head_x;
    viper.head_py = viper.head_y;

    if (action == GO_UP) {
        viper.dir = NORTH;
    } else if (action == GO_DOWN) {
        viper.dir = SOUTH;
    } else if (action == GO_RIGHT) {
        viper.dir = EAST;
    } else if (action == GO_LEFT) {
        viper.dir = WEST;
    }

    if (moving) {
        if (viper.dir == NORTH && game_paused == false) {
            MapItem *curritem = get_north(viper.head_x, viper.head_y);
            viper.head_py = viper.head_y;
            viper.head_y = viper.head_y - 1;
            
            if (curritem != NULL && curritem->walkable == false) {
                if (viper.invincible == true) {
                    viper.head_y = viper.head_y + 1;
                    return NO_RESULT;   
                }
                return GAME_OVER;    
            } 

            get_object();
            
            if (viper.length >= max_length) {
                return GAME_WON;    
            }
            return MOVED_NORTH;
            
        } else if (viper.dir == SOUTH && game_paused == false) {
            MapItem *curritem = get_south(viper.head_x, viper.head_y);
            viper.head_py = viper.head_y;
            viper.head_y = viper.head_y + 1;
            if (curritem != NULL && curritem->walkable == false) {
                if (viper.invincible == true) {
                    viper.head_y = viper.head_y - 1;
                    return NO_RESULT;   
                }
                return GAME_OVER;    
            } 
            get_object();
            
            if (viper.length >= max_length) {
                return GAME_WON;    
            }
            
            return MOVED_SOUTH;
            
        } else if (viper.dir == EAST && game_paused == false) {
            MapItem *curritem = get_east(viper.head_x, viper.head_y);
            viper.head_px = viper.head_x;
            viper.head_x = viper.head_x + 1;
            
            if (curritem != NULL && curritem->walkable == false) {
                if (viper.invincible == true) {
                    viper.head_x = viper.head_x - 1;
                    return NO_RESULT;   
                }
                return GAME_OVER;
            } 
            get_object();
            
            if (viper.length >= max_length) {
                return GAME_WON;    
            }
            
            return MOVED;
            
        } else if (viper.dir == WEST && game_paused == false) {
            MapItem *curritem = get_west(viper.head_x, viper.head_y);
            viper.head_px = viper.head_x;
            viper.head_x = viper.head_x - 1;
            if (curritem != NULL && curritem->walkable == false) {
                if (viper.invincible == true) {
                    viper.head_x = viper.head_x + 1;
                    return NO_RESULT;   
                }
                return GAME_OVER;
            } 
            get_object();
            
            if (viper.length >= max_length) {
                return GAME_WON;    
            }
            return MOVED_WEST;

        } else if (action == INVINCIBILITY_BUTTON) {
            if (viper.invincible == true) {
                viper.invincible = false;    
            } else {
                viper.invincible = true;    
            }
            
            return NO_RESULT;
        } // else if (action == MENU_BUTTON) {
        //     if (game_paused == true) {
        //         game_paused = false; 
        //         draw_game(1);
        //     } else {
        //         viper.speed = 0; 
        //         //uLCD.filled_rectangle(3, 15, 126, 113, BLACK);
        //         game_paused = true; 
        //         draw_menu();
        //     }
        //     return NO_RESULT;

        // } 
        else {
            return NO_RESULT; 
        }
    } else {
        if (action == GO_UP && game_paused == false) {
            MapItem *curritem = get_north(viper.head_x, viper.head_y);
            viper.head_py = viper.head_y;
            viper.head_y = viper.head_y - 1;

            
            if (curritem != NULL && curritem->walkable == false) {
                if (viper.invincible == true) {
                    viper.head_y = viper.head_y + 1;
                    return NO_RESULT;   
                } else if (num_lives > 0) {
                    viper.head_y = viper.head_y + 1;
                    num_lives--;
                    return NO_RESULT;  
                } else {
                    return GAME_OVER;    
                }
            } 

            get_object();
            
            if (viper.length >= max_length) {
                return GAME_WON;    
            }
            return MOVED_NORTH;
            
        } else if (action == GO_DOWN && game_paused == false) {
            MapItem *curritem = get_south(viper.head_x, viper.head_y);
            viper.head_py = viper.head_y;
            viper.head_y = viper.head_y + 1;
            if (curritem != NULL && curritem->walkable == false) {
                if (viper.invincible == true) {
                    viper.head_y = viper.head_y - 1;
                    return NO_RESULT;   
                }
                else if (num_lives > 0) {
                    viper.head_y = viper.head_y - 1;
                    num_lives--;
                    return NO_RESULT;  
                } else {
                    return GAME_OVER;    
                }    
            } 
            get_object();
            
            if (viper.length >= max_length) {
                return GAME_WON;    
            }
            
            return MOVED_SOUTH;
            
        } else if (action == GO_RIGHT && game_paused == false) {
            MapItem *curritem = get_east(viper.head_x, viper.head_y);
            viper.head_px = viper.head_x;
            viper.head_x = viper.head_x + 1;
            
            if (curritem != NULL && curritem->walkable == false) {
                if (viper.invincible == true) {
                    viper.head_x = viper.head_x - 1;
                    return NO_RESULT;   
                } else if (num_lives > 0) {
                    viper.head_x = viper.head_x - 1;
                    num_lives--;
                    return NO_RESULT;  
                } else {
                    return GAME_OVER;    
                }
                
            } 
            get_object();
            
            if (viper.length >= max_length) {
                return GAME_WON;    
            }
            
            return MOVED;
            
        } else if (action == GO_LEFT && game_paused == false) {
            MapItem *curritem = get_west(viper.head_x, viper.head_y);
            viper.head_px = viper.head_x;
            viper.head_x = viper.head_x - 1;
            if (curritem != NULL && curritem->walkable == false) {
                if (viper.invincible == true) {
                    viper.head_x = viper.head_x + 1;
                    return NO_RESULT;   
                } else if (num_lives > 0) {
                    viper.head_x = viper.head_x + 1;
                    num_lives--;
                    return NO_RESULT;  
                } else {
                    return GAME_OVER;    
                }
                
            } 
            get_object();
            
            if (viper.length >= max_length) {
                return GAME_WON;    
            }
            return MOVED_WEST;

        } else if (action == INVINCIBILITY_BUTTON) {
            if (viper.invincible == true) {
                viper.invincible = false;    
            } else {
                viper.invincible = true;    
            }
            
            return NO_RESULT;
        } // else if (action == MENU_BUTTON) {
        //     if (game_paused == true) {
        //         game_paused = false; 
        //         draw_game(1);
        //     } else {
        //         viper.speed = 0; 
        //         //uLCD.filled_rectangle(3, 15, 126, 113, BLACK);
        //         game_paused = true; 
        //         draw_menu();
        //     }
        //     return NO_RESULT;

        // } 
        else {
            return NO_RESULT; 
        }
    }
}




/**
 * Draw the upper status bar.
 */
void draw_upper_status()
{
    uLCD.line(0, 9, 127, 9, GREEN);
}

/**
 * Draw the lower status bar.
 */
void draw_lower_status()
{
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(  0,   9, 127,  14, WHITE);   // Top
    uLCD.filled_rectangle(  0,  13,   2, 114, WHITE);   // Left
    uLCD.filled_rectangle(  0, 114, 127, 117, WHITE);   // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE);   // Right
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status
 * bars. Unless init is nonzero, this function will optimize drawing by only
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int draw_option)
{
    // Draw game border first
    if(draw_option == FULL_DRAW) 
    {
        draw_border();
        int u = 58;
        int v = 56;
        draw_viper_head(u, v);
        draw_viper_body(u-11, v);
        draw_viper_tail(u-22, v);
        return;
    } else {
        draw_border();
    }

    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) { // Iterate over columns of tiles
        for (int j = -4; j <= 4; j++) { // Iterate over one column of tiles
            // Here, we have a given (i,j)

            // Compute the current map (x,y) of this tile
            int x = i + viper.head_x;
            int y = j + viper.head_y;

            // Compute the previous map (px, py) of this tile
            int px = i + viper.head_px;
            int py = j + viper.head_py;

            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;

            // Figure out what to draw
            DrawFunc draw = NULL;
            if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) { // Current (i,j) in the map
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (draw_option || curr_item != prev_item) { // Only draw if they're different
                    if (curr_item) { // There's something here! Draw it
                        draw = curr_item->draw;
                        if (draw == draw_viper_head) {
                            if (draw_option == MOVED_SOUTH) {
                                draw = draw_viper_head_south; 
                            } else if (draw_option == MOVED_NORTH) {
                                draw = draw_viper_head_north; 
                            } else if (draw_option == MOVED_WEST) {
                                draw = draw_viper_head_west; 
                            }
                        }
                    } else { // There used to be something, but now there isn't
                        draw = draw_nothing;
                    }
                } else if (curr_item && curr_item->type == CLEAR) {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            } else if (draw_option) { // If doing a full draw, but we're out of bounds, draw the walls.
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars
    draw_upper_status();
    draw_lower_status();
}

/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    // for(int i = map_width() + 3; i < map_area(); i += 39) {
    //     add_chest(i % map_width(), i / map_width());
    // }

    // for (int i = 0; i < 50; i++) 
    // {
    //     int w = rand() % (map_width() - 1); 
    //     int h = rand() % (map_height() - 1);
    //     MapItem* curr_coord = get_here(w, h); 
    //     if (curr_coord) {
    //         draw_nothing(w, h);
    //     } else {
    //         add_chest(w, h); 
    //     }
    // } 

    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    /* Print 5 random numbers from 0 to 49 */
    for(int i = 0 ; i < map_width(); i++ ) {
        int w = rand() % 51;
        int h = rand() % 51; 
        MapItem* curr_coord = get_here(w, h);
        if (curr_coord) {
            draw_nothing(w, h);
        } else {
            add_chest(w, h); 
        }
    }

    //10 random boost ups
    for(int i = 0 ; i < 10; i++ ) {
        int w = rand() % 51;
        int h = rand() % 51; 
        MapItem* curr_coord = get_here(w, h);
        if (curr_coord) {
            draw_nothing(w, h);
        } else {
            add_boost_up(w, h); 
        }
    }

    //10 random boost downs
    for(int i = 0 ; i < 10; i++ ) {
        int w = rand() % 51;
        int h = rand() % 51; 
        MapItem* curr_coord = get_here(w, h);
        if (curr_coord) {
            draw_nothing(w, h);
        } else {
            add_boost_down(w, h); 
        }
    }

    //10 random life ups
    for(int i = 0 ; i < 10; i++ ) {
        int w = rand() % 51;
        int h = rand() % 51; 
        MapItem* curr_coord = get_here(w, h);
        if (curr_coord) {
            draw_nothing(w, h);
        } else {
            add_life(w, h); 
        }
    }

    //Insert boost up
    //add_boost_up(6,6);
    //add_boost_up(4,4);
    
    //insert boost down
    //add_boost_down(10,10);
    // add_boost_down(9,9);
    
    
    pc.printf("plants\r\n");

    pc.printf("Adding walls!\r\n");
    add_wall(            0,              0, HORIZONTAL, map_width());
    add_wall(            0, map_height()-1, HORIZONTAL, map_width());
    add_wall(            0,              0,   VERTICAL, map_height());
    add_wall(map_width()-1,              0,   VERTICAL, map_height());
    pc.printf("Walls done!\r\n");
    
    add_viper_head(viper.locations[0].x, viper.locations[0].y);
    add_viper_body(viper.locations[1].x, viper.locations[1].y);
    add_viper_tail(viper.locations[2].x, viper.locations[2].y);
    
    pc.printf("Add extra chamber\r\n");
    add_wall(30,  0,   VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39,  0,   VERTICAL, 10);
    pc.printf("Added!\r\n");
    
    print_map();
}
    


