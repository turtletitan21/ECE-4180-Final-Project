// ============================================
// The header file for Hardware class file.
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#ifndef HARDWARE_H
#define HARDWARE_H

/**
 * Structure that represents all the inputs to the game.
 * If additional hardware is added, new elements should be added to this struct.
 */
struct GameInputs {
    int b1, b2, b3;             // Button presses
    bool ns_up, ns_down;        // NavSwitch readings
    bool ns_left, ns_right;     // ...
    bool ns_center;             // ...
};

/**
 * Initialize all the hardware.
 */
int hardware_init();
GameInputs read_inputs();

#endif // HARDWARE_H