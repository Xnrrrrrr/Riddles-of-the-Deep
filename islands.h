#include <stdbool.h>

#ifndef ISLANDS_H
#define ISLANDS_H

#define MAX_STRING_LENGTH 100

typedef struct {
    char name[MAX_STRING_LENGTH];
    char description[MAX_STRING_LENGTH];
    int dubloon_available;
    int max_dubloon;
    int treasure_available;
    int max_treasure;
    int food_available;
    int max_food;
    int cannonballs_available;
    int max_cannonballs;
    int rum_available;
    int max_rum;
    bool is_island_hostile;
    bool is_looted;
    bool is_stronghold;
    bool has_shipwright;
    bool has_black_market;
} Island;

void initializeIslands(Island islands[], int numIslands);

#endif // ISLANDS_H