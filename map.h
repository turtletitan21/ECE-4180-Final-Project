// ============================================
// The header file for the Map class file.
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#ifndef MAP_H
#define MAP_H

#include "hash_table.h"

/**
 * A structure to represent the map. The implementation is private.
 */
struct Map;

// A function pointer type for drawing MapItems.
// All tiles are 11x11 blocks.
// u,v is the top left corner pixel of the block
typedef void (*DrawFunc)(int u, int v);

/**
 * The data for elements in the map. Each item in the map HashTable is a
 * MapItem.
 */
typedef struct {
    /**
     * Indicates the "type" of the MapItem: WALL, DOOR, PLANT, etc. This is
     * useful for determining how to interact with the object when updating the
     * game state.
     */
    int type;
    
    /**
     * A function pointer to the drawing function for this item. Used by draw_game.
     */
    DrawFunc draw;
    
    /**
     * If zero, this item should block character motion.
     */
    int walkable;
    
    /**
     * Arbitrary extra data for the MapItem. Could be useful for keeping up with
     * special information, like where a set of stairs should take the player.
     * 
     * Iterpretation of this can depend on the type of the MapItem. For example,
     * a WALL probably doesn't need to use this (it can be NULL), where an NPC
     * might use it to store game state (have I given the player the key yet?).
     */
    void* data;
} MapItem;

typedef struct {
    int tm;
    int tx, ty;
} StairsData;

// MapItem types
// Define more of these!
#define WALL        0
#define DOOR        1
#define PLANT       2
#define WATER       3
#define KEY         4
#define CHEST       5
#define VIPER_BODY  6
#define CLEAR       7
#define STAIRS      8
#define SONAR       9
#define PUZZLE      10
#define NPC         11
#define BOOST_UP    12
#define BOOST_DOWN  13

/**
 * Initializes the internal structures for all maps. This does not populate
 * the map with items, but allocates space for them, initializes the hash tables, 
 * and sets the width and height.
 */
void maps_init();

/**
 * Returns a pointer to the active map.
 */
Map* get_active_map();

/**
 * Sets the active map to map m, where m is the index of the map to activate.
 * Returns a pointer to the new active map.
 */
Map* set_active_map(int m);

/**
 * Returns the map m, regardless of whether it is the active map. This function
 * does not change the active map.
 */
Map* get_map(int m);

/**
 * Print the active map to the serial console.
 */
void print_map();

// Access
/**
 * Returns the width of the active map.
 */
int map_width();

/**
 * Returns the heigh of the active map.
 */
int map_height();

/**
 * Returns the total number of cells in the active map.
 */
int map_area();

/**
 * Returns the MapItem of the given location.
 */
MapItem* get_current(int x, int y);

/**
 * Returns the MapItem immediately above the given location.
 */
MapItem* get_north(int x, int y);

/**
 * Returns the MapItem immediately below the given location.
 */
MapItem* get_south(int x, int y);

/**
 * Returns the MapItem immediately to the right of the given location.
 */
MapItem* get_east(int x, int y);

/**
 * Returns the MapItem immediately to the left of  the given location.
 */
MapItem* get_west(int x, int y);

/**
 * Returns the MapItem at the given location.
 */
MapItem* get_here(int x, int y);

// Directions, for using the modification functions
#define HORIZONTAL  0
#define VERTICAL    1

/**
 * If there is a MapItem at (x,y), remove it from the map.
 */
void map_erase(int x, int y);

/**
 * Add WALL items in a line of length len beginning at (x,y).
 * If dir == HORIZONTAL, the line is in the direction of increasing x.
 * If dir == VERTICAL, the line is in the direction of increasing y.
 *
 * If there are already items in the map that collide with this line, they are
 * erased.
 */

void map_reset(); 

void add_wall(int x, int y, int dir, int len);

/**
 * Add a PLANT item at (x,y). If there is already a MapItem at (x,y), erase it
 * before adding the plant.
 */
void add_plant(int x, int y);


void add_chest(int x, int y);
void remove_chest(int x, int y);

void add_viper_body(int x, int y);
void add_viper_head(int x, int y);
void add_viper_tail(int x, int y);
void add_boost_down(int x, int y);
void add_boost_up(int x, int y);
void add_life(int x, int y);


#endif //MAP_H