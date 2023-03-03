#include <string.h>
#include <stdio.h>

typedef enum {
    Start_State,
    Idle_State,
    Stand_State,
    Sit_stand,
    Walk_State,
    Turn_State,
    End_State
} SystemState;


typedef enum {
    Transition_Event,
    Sit_ButtonPress_Event,
    Stand_ButtonPress_Event,
    Walk_ButtonPress_Event,
    Turn_ButtonPress_Event,
    End_ButtonPress_Event
} SystemEvent;