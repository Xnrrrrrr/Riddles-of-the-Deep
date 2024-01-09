#include <ncurses/curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>  // allows for strcmp (compares strings)
#include <math.h>

#include "islands.h"

#define MAX_PIRATE_NAME_LENGTH 8
#define MAX_STRING_LENGTH 100
#define NUMBER_OF_PIRATES 4
#define NUMBER_OF_ISLANDS 22
#define RESTOCK_RATE 3
#define MAX_LOOT 80

// exp macros
#define EXP_THRESHOLD 185
#define EXP_MULTIPLIER 1.104633  // Max level is 163; Was 1.107633 (max level = 158)

// ncurse macros
#define TEXT_BORDER_X 216
#define TEXT_BORDER_Y 25
#define ATTRIBUTE_BORDER_X 78
#define ATTRIBUTE_BORDER_Y 38
#define STATS_BORDER_X 78
#define STATS_BORDER_Y 39
#define VISUAL_BORDER_X 210
#define VISUAL_BORDER_Y 44
#define PADDING_Y 1
#define PADDING_X 2
#define NUM_BOXES_X 3
#define NUM_BOXES_Y 3

typedef struct {
    int thievery;
    int thievery_exp;

    int charisma;
    int charisma_exp;

    int seamanship;     // navigating storms/obstacles
    int seamanship_exp;

    int medicine;       // health recovery skill
    int medicine_exp;

    int instinct;       // survival instinct skill
    int instinct_exp;

    int leadership;     // how well a crew member leads others
    int leadership_exp;

    int carpentry;
    int carpentry_exp;
} Attributes;

typedef enum {
    EASY,
    NORMAL,
    HARD
} Difficulty;

typedef struct {
    char name[MAX_PIRATE_NAME_LENGTH];
    int health;
    int morale;
    Attributes attributes;
} Pirate;

typedef struct {
    int distance;
    int treasure;
    int food;
    int cannonballs;
    int rum;
    int health;
    bool is_at_sea;
    Pirate crew[NUMBER_OF_PIRATES];
} Ship;

Difficulty difficulty;      // declaring

// takes the base level as an arg
int calculateExp(int level) {
    double xp = EXP_THRESHOLD * pow(EXP_MULTIPLIER, level);
    return (int)xp;
}

// takes level as first arg and xp as second arg; Should be used whenever a pirate gains xp to check if they leveled an attribute
int calculateLevel(int base_level, int xp) {
    int level = fmax(base_level, floor(log(xp / (double)EXP_THRESHOLD) / log(EXP_MULTIPLIER)));
    return level;
}

Attributes getBasePirateAttributes() {      // function declaration       OOP
    Attributes baseAttributes;      // creates an object named baseAttributes based on the attributes "class" instantiation creating an occurence

    int thievery_base = 10 + rand() % 7; // 10 to 16        // assigns all baseAttributes to the pirates
    int charisma_base = 8 + rand() % 7; // 8 to 14
    int seamanship_base = 12 + rand() % 7; // 12 to 18
    int medicine_base = 6 + rand() % 7; // 6 to 12
    int instinct_base = 8 + rand() % 7; // 8 to 14
    int leadership_base = 10 + rand() % 7; // 10 to 16
    int carpentry_base = 9 + rand() % 7; // 9 to 15

    int thievery_exp, charisma_exp, seamanship_exp, medicine_exp, instinct_exp, leadership_exp, carpentry_exp;

    int normal_thievery = thievery_base / 2;
    int normal_charisma = charisma_base / 2;
    int normal_seamanship = seamanship_base / 2;
    int normal_medicine = medicine_base / 2;
    int normal_instinct = instinct_base / 2;
    int normal_leadership = leadership_base / 2;
    int normal_carpentry = carpentry_base / 2;

    int hard_thievery = thievery_base / 3;
    int hard_charisma = charisma_base / 3;
    int hard_seamanship = seamanship_base / 3;
    int hard_medicine = medicine_base / 3;
    int hard_instinct = instinct_base / 3;
    int hard_leadership = leadership_base / 3;
    int hard_carpentry = carpentry_base / 3;

    switch (difficulty) {                               // switch case based on diff, that divides base attributes
        case EASY:
            thievery_exp = calculateExp(thievery_base);
            charisma_exp = calculateExp(charisma_base);
            seamanship_exp = calculateExp(seamanship_base);
            medicine_exp = calculateExp(medicine_base);
            instinct_exp = calculateExp(instinct_base);
            leadership_exp = calculateExp(leadership_base);
            carpentry_exp = calculateExp(carpentry_base);

            baseAttributes.thievery = thievery_base;
            baseAttributes.thievery_exp = thievery_exp;

            baseAttributes.charisma = charisma_base;
            baseAttributes.charisma_exp = charisma_exp;

            baseAttributes.seamanship = seamanship_base;
            baseAttributes.seamanship_exp = seamanship_exp;

            baseAttributes.medicine = medicine_base;
            baseAttributes.medicine_exp = medicine_exp;

            baseAttributes.instinct = instinct_base;
            baseAttributes.instinct_exp = instinct_exp;

            baseAttributes.leadership = leadership_base;
            baseAttributes.leadership_exp = leadership_exp;

            baseAttributes.carpentry = carpentry_base;
            baseAttributes.carpentry_exp = carpentry_exp;
            break;

        case NORMAL:
            thievery_exp = calculateExp(normal_thievery);
            charisma_exp = calculateExp(normal_charisma);
            seamanship_exp = calculateExp(normal_seamanship);
            medicine_exp = calculateExp(normal_medicine);
            instinct_exp = calculateExp(normal_instinct);
            leadership_exp = calculateExp(normal_leadership);
            carpentry_exp = calculateExp(normal_carpentry);

            baseAttributes.thievery = normal_thievery;
            baseAttributes.thievery_exp = thievery_exp;

            baseAttributes.charisma = normal_charisma;
            baseAttributes.charisma_exp = charisma_exp;

            baseAttributes.seamanship = normal_seamanship;
            baseAttributes.seamanship_exp = seamanship_exp;

            baseAttributes.medicine = normal_medicine;
            baseAttributes.medicine_exp = medicine_exp;

            baseAttributes.instinct = normal_instinct;
            baseAttributes.instinct_exp = instinct_exp;

            baseAttributes.leadership = normal_leadership;
            baseAttributes.leadership_exp = leadership_exp;

            baseAttributes.carpentry = normal_carpentry;
            baseAttributes.carpentry_exp = carpentry_exp;
            break;

        case HARD:
            thievery_exp = calculateExp(hard_thievery);
            charisma_exp = calculateExp(hard_charisma);
            seamanship_exp = calculateExp(hard_seamanship);
            medicine_exp = calculateExp(hard_medicine);
            instinct_exp = calculateExp(hard_instinct);
            leadership_exp = calculateExp(hard_leadership);
            carpentry_exp = calculateExp(hard_carpentry);

            baseAttributes.thievery = hard_thievery;
            baseAttributes.thievery_exp = thievery_exp;

            baseAttributes.charisma = hard_charisma;
            baseAttributes.charisma_exp = charisma_exp;

            baseAttributes.seamanship = hard_seamanship;
            baseAttributes.seamanship_exp = seamanship_exp;

            baseAttributes.medicine = hard_medicine;
            baseAttributes.medicine_exp = medicine_exp;

            baseAttributes.instinct = hard_instinct;
            baseAttributes.instinct_exp = instinct_exp;

            baseAttributes.leadership = hard_leadership;
            baseAttributes.leadership_exp = leadership_exp;

            baseAttributes.carpentry = hard_carpentry;
            baseAttributes.carpentry_exp = carpentry_exp;
            break;
    }

    return baseAttributes;      // returns the baseAttributes to the main
}

int findNewIslandIndex(int current_island, int num_islands) {
    int new_island_index;
    do {                                                            // method so when you leave an island you wont end up there again
        new_island_index = rand() % num_islands;
    } while (new_island_index == current_island);
    return new_island_index;
}

int getTotalThievery(Ship myShip, int number_of_alive_pirates) {
    int total_crew_thievery = 0;                                    // sets total thievery so you can calculate how much resources you can get
    for (int i = 0; i < number_of_alive_pirates; i++) {             // initializes variable i of type int and sets its value to 0 , increments the value by 1 after each iteraiton
        total_crew_thievery += myShip.crew[i].attributes.thievery;  // method so when a member dies it decreases when a member dies or can increase when you get new members
    }
    return total_crew_thievery;
}

int getTotalCharisma(Ship myShip, int number_of_alive_pirates) {
    int total_crew_charisma = 0;
    for (int i = 0; i < number_of_alive_pirates; i++) {
        total_crew_charisma += myShip.crew[i].attributes.charisma;
    }
    return total_crew_charisma;
}

int getTotalSeamanship(Ship myShip, int number_of_alive_pirates) {
    int total_crew_seamanship = 0;
    for (int i = 0; i < number_of_alive_pirates; i++) {
        total_crew_seamanship += myShip.crew[i].attributes.seamanship;
    }
    return total_crew_seamanship;
}

int getTotalMedicine(Ship myShip, int number_of_alive_pirates) {
    int total_crew_medicine = 0;
    for (int i = 0; i < number_of_alive_pirates; i++) {
        total_crew_medicine += myShip.crew[i].attributes.medicine;
    }
    return total_crew_medicine;
}

int getTotalInstinct(Ship myShip, int number_of_alive_pirates) {
    int total_crew_instinct = 0;
    for (int i = 0; i < number_of_alive_pirates; i++) {
        total_crew_instinct += myShip.crew[i].attributes.instinct;
    }
    return total_crew_instinct;
}

int getTotalLeadership(Ship myShip, int number_of_alive_pirates) {
    int total_crew_leadership = 0;
    for (int i = 0; i < number_of_alive_pirates; i++) {
        total_crew_leadership += myShip.crew[i].attributes.leadership;
    }
    return total_crew_leadership;
}

int getTotalCarpentry(Ship myShip, int number_of_alive_pirates) {
    int total_crew_carpentry = 0;
    for (int i = 0; i < number_of_alive_pirates; i++) {
        total_crew_carpentry += myShip.crew[i].attributes.carpentry;
    }
    return total_crew_carpentry;
}

int calculateLoot(int total_crew_thievery, float loot_factor, float max_loot, int available_resources) {        // function that ensures LA doesnt exceed ML, also calculates it based on total crew thievery and loot factor
    // Type cast to convert from float to int (explicit)
    int loot_amount = (int)(total_crew_thievery * loot_factor);
    loot_amount = (loot_amount > max_loot) ? max_loot : loot_amount;            // conditional ternary operator, if LA > ML, ML is assigned to LA
    return (loot_amount > available_resources) ? available_resources : loot_amount;
}

float getRandomFloat(void) {                                            // function for RNG
    return rand() / (float)RAND_MAX;
}

void drawAttributeBoxes(WINDOW *attribute_area) {
    int board_height = ATTRIBUTE_BORDER_Y - 2 * PADDING_Y;
    int board_width = ATTRIBUTE_BORDER_X - 2 * PADDING_X;

    int cell_height = board_height / 3;
    int cell_width = board_width / 3;

    for (int i = 1; i < 3; i++) {
        // Draw horizontal lines
        mvwhline(attribute_area, PADDING_Y + i * cell_height - 1, PADDING_X, ACS_HLINE, board_width);
    }

    for (int i = 1; i < 3; i++) {
        // Draw vertical lines
        mvwvline(attribute_area, PADDING_Y, PADDING_X + i * cell_width, ACS_VLINE, board_height);
    }

    wrefresh(attribute_area);
}

// Accepts area type and a string such as "t" for text area, "a" for attribute area, "s" for stats area, and "v" for visual area
int clearAndRedraw(WINDOW *window, const char *identifier){ // "const char *" is used to represent string literals
    if (strcmp(identifier, "t") == 0) {
        wclear(window);
        box(window, 0, 0);
        mvwprintw(window, 0, 2, "Text Area");
        wrefresh(window);
    } else if (strcmp(identifier, "a") == 0) {
        wclear(window);
        box(window, 0, 0);
        drawAttributeBoxes(window);
        mvwprintw(window, 0, 2, "Attribute Area");
        wrefresh(window);
    } else if (strcmp(identifier, "s") == 0) {
        wclear(window);
        box(window, 0, 0);
        mvwprintw(window, 0, 2, "Stats Area");
        wrefresh(window);
    } else if (strcmp(identifier, "v") == 0) {
        wclear(window);
        box(window, 0, 0);
        mvwprintw(window, 0, 2, "Visual Area");
        wrefresh(window);
    } else {
        // Handle the case where identifier doesn't match any known value
        return -1;
    }
    return 0;
}

// Well... waits for user input
void waitForInput() {
    noecho();  // Turn off echoing
    getch();   // Wait for user input without displaying it
    echo();    // Turn echoing back on
}

// accepts attribute_area, myShip, and number_of_alive_pirates to calculate the position within the attribute area
void renderPirateAttributes(WINDOW *attribute_area, Ship myShip, int number_of_alive_pirates) {
    clearAndRedraw(attribute_area, "a");
    for (int i = 0; i < number_of_alive_pirates; i++) {
        int box_row = i / NUM_BOXES_X;   // Calculate row based on attribute layout
        int box_col = i % NUM_BOXES_Y;   // Calculate column based on attribute layout

        int cell_height = (ATTRIBUTE_BORDER_Y - 2 * PADDING_Y) / 3;  // Calculates height of each cell
        int cell_width = (ATTRIBUTE_BORDER_X - 2 * PADDING_X) / 3;  //Calculates width of each cell

        int start_y = PADDING_Y + box_row * cell_height + 1;  // Finds where to start text based on y-axis
        int start_x = PADDING_X + box_col * cell_width + 1;  // Finds where to start text based on x-axis

        mvwprintw(attribute_area, start_y, start_x + 2, "%s", myShip.crew[i].name);
        mvwprintw(attribute_area, start_y + 1, start_x + 2, "Thievery: %d", myShip.crew[i].attributes.thievery);
        mvwprintw(attribute_area, start_y + 2, start_x + 2, "Charisma: %d", myShip.crew[i].attributes.charisma);
        mvwprintw(attribute_area, start_y + 3, start_x + 2, "Seamanship: %d", myShip.crew[i].attributes.seamanship);
        mvwprintw(attribute_area, start_y + 4, start_x + 2, "Medicine: %d", myShip.crew[i].attributes.medicine);
        mvwprintw(attribute_area, start_y + 5, start_x + 2, "Instinct: %d", myShip.crew[i].attributes.instinct);
        mvwprintw(attribute_area, start_y + 6, start_x + 2, "Leadership: %d", myShip.crew[i].attributes.leadership);
        mvwprintw(attribute_area, start_y + 7, start_x + 2, "Carpentry: %d", myShip.crew[i].attributes.carpentry);
        mvwprintw(attribute_area, start_y + 8, start_x + 2, "Health: %d", myShip.crew[i].health);
        mvwprintw(attribute_area, start_y + 9, start_x + 2, "Morale: %d", myShip.crew[i].morale);
        wrefresh(attribute_area);
    }
}

int main() {
    system("mode con: cols=300 lines=80");  // Set the initial console size; 300 columns (x) and 80 lines (y)
    srand((unsigned int)time(NULL));  // srand function is used to seed the random number generator. time makes it so the unique value is based on the current time in seconds from Jan 1st, 1970 (different value as time progresses when the app is executed)

    char last_decision;

    do {
        initscr();  // Starts curses mode

        refresh();  // Keeps the boxes from disappearing

        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);

        int text_area_y = yMax - TEXT_BORDER_Y - PADDING_Y;
        int right_area_x = xMax - ATTRIBUTE_BORDER_X - PADDING_X;
        int bottom_area_y = yMax - ATTRIBUTE_BORDER_Y - PADDING_Y;

        WINDOW *text_area = newwin(TEXT_BORDER_Y, TEXT_BORDER_X, text_area_y, PADDING_X);
        box(text_area, 0, 0);
        mvwprintw(text_area, 0, 2, "Text Area");
        wrefresh(text_area);

        WINDOW *attribute_area = newwin(ATTRIBUTE_BORDER_Y, ATTRIBUTE_BORDER_X, bottom_area_y, right_area_x);
        box(attribute_area, 0, 0);
        mvwprintw(attribute_area, 0, 2, "Attribute Area");
        drawAttributeBoxes(attribute_area);
        wrefresh(attribute_area);

        WINDOW *stats_area = newwin(STATS_BORDER_Y, STATS_BORDER_X, PADDING_Y, right_area_x);
        box(stats_area, 0, 0);
        mvwprintw(stats_area, 0, 2, "Stats Area");
        wrefresh(stats_area);

        WINDOW *visual_area = newwin(VISUAL_BORDER_Y, VISUAL_BORDER_X, (PADDING_Y * 8), ((PADDING_X * 3) - 1));
        box(visual_area, 0, 0);
        mvwprintw(visual_area, 0, 2, "Visual Area");
        wrefresh(visual_area);



        int difficulty_choice;
        float loot_factor_forgiveness;

        Island islands[NUMBER_OF_ISLANDS];
        initializeIslands(islands, NUMBER_OF_ISLANDS);

        int current_island_index;
        do {
            current_island_index = rand() % NUMBER_OF_ISLANDS; //
        } while (islands[current_island_index].is_island_hostile);  // Randomly selects a non-hostile starting island

        mvwprintw(text_area, 2, 2, "You start on the island of %s.", islands[current_island_index].name);
        mvwprintw(text_area, 3, 2, "Description: %s", islands[current_island_index].description);
        mvwprintw(text_area, 4, 2, "Press any key to continue:");
        wrefresh(text_area);

        waitForInput();

        Ship myShip;
        myShip.health = 100;
        myShip.distance = 0;
        myShip.is_at_sea = false;

        int number_of_alive_pirates = NUMBER_OF_PIRATES;        // needs a define of 9 pirates at top

        int continue_from_while = 1;        // breaks out of the while loop the right way
        int port_choice;                    // user input
        int distrance_traveled;             //

        int hostile_port_choice;

        // Commented so compiler can stop bitching, facts
        // bool has_treasure_map = false;

        while (1) {
            clearAndRedraw(text_area, "t");
            mvwprintw(text_area, 2, 2, "Enter a difficulty level: ");
            mvwprintw(text_area, 3, 2, "1: Easy");
            mvwprintw(text_area, 4, 2, "2: Normal");
            mvwprintw(text_area, 5, 2, "3: Hard");
            wrefresh(text_area);

            int ch = wgetch(text_area);     // ncruse only accepts strings, workaround for input

            if (ch != ERR) {                // ERR is built in
                difficulty_choice = ch - '0';  // Convert ASCII to integer

                if (difficulty_choice == 1) {
                    difficulty = EASY;
                    myShip.cannonballs = 20;
                    myShip.treasure = 20;
                    myShip.food = 48;
                    myShip.rum = 30;
                    loot_factor_forgiveness = 0.4;
                    break;
                } else if (difficulty_choice == 2) {
                    difficulty = NORMAL;
                    myShip.cannonballs = 10;
                    myShip.treasure = 10;
                    myShip.food = 24;
                    myShip.rum = 20;
                    loot_factor_forgiveness = 0.2;
                    break;
                } else if (difficulty_choice == 3) {
                    difficulty = HARD;
                    myShip.cannonballs = 4;
                    myShip.treasure = 0;
                    myShip.food = 12;
                    myShip.rum = 10;
                    loot_factor_forgiveness = 0.1;
                    break;
                } else {                        // input validation
                    mvwprintw(text_area, 24, 2, "Enter an interger between 1 and 3.");
                    wrefresh(text_area);
                }
            }   
        }

        clearAndRedraw(text_area, "t");     // clear and redraw for every note print

        for (int i = 0; i < NUMBER_OF_PIRATES; i++) {       // giving the pirates names 4+
            char pirate_name[MAX_PIRATE_NAME_LENGTH];

            while (1) {
                clearAndRedraw(text_area, "t");
                mvwprintw(text_area, 2, 2, "Enter the name of your pirate #%d (Must be %d characters or less): ", i + 1, MAX_PIRATE_NAME_LENGTH);
                wrefresh(text_area);

                wgetnstr(text_area, pirate_name, MAX_PIRATE_NAME_LENGTH);

                if (strlen(pirate_name) > 0 && strlen(pirate_name) <= MAX_PIRATE_NAME_LENGTH) {
                    strcpy(myShip.crew[i].name, pirate_name);
                    break;
                } else {
                    mvwprintw(text_area, 24, 2, "Try again. The pirate's name should be %d characters or less.", MAX_PIRATE_NAME_LENGTH);
                    wrefresh(text_area);
                }
            }
        }

        clearAndRedraw(text_area, "t");

        // Gives pirates there base shit 4x
        for (int i = 0; i < number_of_alive_pirates; i++) {
            Attributes baseAttributes = getBasePirateAttributes();
            myShip.crew[i].attributes = baseAttributes;
            myShip.crew[i].health = 100;
            myShip.crew[i].morale = 100;
        }

        renderPirateAttributes(attribute_area, myShip, number_of_alive_pirates);

        // while (1) {
        //     mvwprintw(text_area, 2, 2, "%s's Thievery EXP: %d", myShip.crew[0].name, myShip.crew[0].attributes.thievery_exp);
        //     mvwprintw(text_area, 3, 2, "%s's Thievery EXP: %d", myShip.crew[1].name, myShip.crew[1].attributes.thievery_exp);
        //     mvwprintw(text_area, 4, 2, "%s's Charisma EXP: %d", myShip.crew[0].name, myShip.crew[0].attributes.charisma_exp);
        //     mvwprintw(text_area, 5, 2, "%s's Charisma EXP: %d", myShip.crew[1].name, myShip.crew[1].attributes.charisma_exp);
        //     myShip.crew[0].attributes.thievery_exp += myShip.crew[0].attributes.thievery_exp * 0.05;
        //     int new_level = calculateLevel(myShip.crew[0].attributes.thievery, myShip.crew[0].attributes.thievery_exp);

        //     mvwprintw(text_area, 6, 2, "%s's Thievery level: %d", myShip.crew[0].name, new_level);
        //     wrefresh(text_area);

        //     myShip.crew[0].attributes.thievery = new_level;

        //     renderPirateAttributes(attribute_area, myShip, number_of_alive_pirates);

        //     waitForInput();
        // }

        // Game loop
        while (myShip.health > 0 && number_of_alive_pirates > 0) {
            // 1 Update game state and perform game logic here ----------

            // Decrease health of the ship over time
            // myShip.health--;

            // Decrease first pirate's health of the ship over time
            // myShip.crew[0].health--;


            // Check and remove pirates with 0 health
            for (int i = 0; i < number_of_alive_pirates; i++) {
                if (myShip.crew[i].health <= 0) {
                    // Shift remaining pirates to fill the gap
                    for (int j = i; j < number_of_alive_pirates - 1; j++) {
                        myShip.crew[j] = myShip.crew[j + 1];
                    }
                    number_of_alive_pirates--;

                    i--;
                    renderPirateAttributes(attribute_area, myShip, number_of_alive_pirates);
                }
            }

            // Calculate pirate attributes
            int total_crew_thievery = getTotalThievery(myShip, number_of_alive_pirates);
            // int total_crew_charisma = getTotalCharisma(myShip, number_of_alive_pirates);
            // int total_crew_seamanship = getTotalSeamanship(myShip, number_of_alive_pirates);
            // int total_crew_medicine = getTotalMedicine(myShip, number_of_alive_pirates);
            // int total_crew_instinct = getTotalInstinct(myShip, number_of_alive_pirates);
            // int total_crew_leadership = getTotalLeadership(myShip, number_of_alive_pirates);
            // int total_crew_carpentry = getTotalCarpentry(myShip, number_of_alive_pirates);

            // 2. Print Current Game State -----------------------

            //printf("Ship Health: %d", myShip.health);

            // for (int i = 0; i < number_of_alive_pirates; i++) {
            //     printf("%s, hp: %d", myShip.crew[i].name, myShip.crew[i].health);
            // }

            // 3. Dialog and Chat Options ------------------------------
            if (!myShip.is_at_sea && !islands[current_island_index].is_island_hostile && number_of_alive_pirates != 0) {
                while (continue_from_while) {
                    mvwprintw(text_area, 2, 2, "You're at the port of %s. What would you like to do?", islands[current_island_index].name);
                    mvwprintw(text_area, 3, 2, "1. Explore the seas for treasure."); // If food reaches 0, there will be a percent chance that each crew member will die
                    mvwprintw(text_area, 4, 2, "2. Rest for the day."); // Low chance for a crew member to go awol?
                    mvwprintw(text_area, 5, 2, "3. Scour the island for riches."); // Chance to lose or find new mates; 
                    mvwprintw(text_area, 6, 2, "4. Hit the pub with your mates."); // Raises moral but has a chance for one of your mates to get in a fight and injured. Maybe a chance to recruit a new mate for the price of some treasure. Consumes food, rum, and treasure?
                    mvwprintw(text_area, 7, 2, "5. Trade with the locals."); // chance to buy a treasure map
                    wrefresh(text_area);

                    int ch = wgetch(text_area);

                    if (ch != ERR) {
                        port_choice = ch - '0';  // Convert ASCII to integer
                        switch (port_choice) {
                            case 1:
                                clearAndRedraw(text_area, "t");
                                mvwprintw(text_area, 2, 2, "You set sail in hopes to find some treasure!");
                                wrefresh(text_area);

                                distrance_traveled = 8 + rand() % 63; // 8 to 70
                                myShip.distance += distrance_traveled;

                                if (myShip.distance >= 50 + rand() % 21) { // 50 to 70
                                    int new_island_index = findNewIslandIndex(current_island_index, NUMBER_OF_ISLANDS);

                                    current_island_index = new_island_index;

                                    mvwprintw(text_area, 3, 2, "You arrived at an island!");
                                    myShip.distance = 0;
                                    myShip.is_at_sea = false;
                                } else {
                                    mvwprintw(text_area, 3, 2, "You traveled %d nautical miles.", distrance_traveled);
                                    myShip.is_at_sea = true;
                                }
                                mvwprintw(text_area, 4, 2, "Press any key to continue...");
                                wrefresh(text_area);

                                waitForInput();

                                clearAndRedraw(text_area, "t");

                                continue_from_while = 0;
                                break;
                            case 2:
                                // continue_from_while = 0;
                                break;
                            case 3:
                                if (!islands[current_island_index].is_looted) {
                                    float treasure_loot_factor = getRandomFloat();  // Random factor between 0 and 1
                                    float treasure_max_loot = MAX_LOOT * (treasure_loot_factor + loot_factor_forgiveness);

                                    float food_loot_factor = getRandomFloat();  // Random factor between 0 and 1
                                    float food_max_loot = MAX_LOOT * food_loot_factor;

                                    float cannonball_loot_factor = getRandomFloat();  // Random factor between 0 and 1
                                    float cannonball_max_loot = MAX_LOOT * cannonball_loot_factor;

                                    float rum_loot_factor = getRandomFloat();  // Random factor between 0 and 1
                                    float rum_max_loot = MAX_LOOT * rum_loot_factor;

                                    // calculateLoot accepts total crew thievery as in interger, loot factor (float between 0 & 1), max loot (float), and available res at island (int). everything on island based on CII
                                    int treasure_loot_amount = calculateLoot(total_crew_thievery, treasure_loot_factor, treasure_max_loot, islands[current_island_index].treasure_available);
                                    int food_loot_amount = calculateLoot(total_crew_thievery, food_loot_factor, food_max_loot, islands[current_island_index].food_available);
                                    int cannonball_loot_amount = calculateLoot(total_crew_thievery, cannonball_loot_factor, cannonball_max_loot, islands[current_island_index].cannonballs_available);
                                    int rum_loot_amount = calculateLoot(total_crew_thievery, rum_loot_factor, rum_max_loot, islands[current_island_index].rum_available);

                                    // Apply the loot to the island
                                    islands[current_island_index].treasure_available -= treasure_loot_amount;       // decrementing (-=), simulates loot being taken from island, if prevents negative
                                    if (islands[current_island_index].treasure_available < 0) {
                                        islands[current_island_index].treasure_available = 0;
                                    }

                                    islands[current_island_index].food_available -= food_loot_amount;
                                    if (islands[current_island_index].food_available < 0) {
                                        islands[current_island_index].food_available = 0;
                                    }

                                    islands[current_island_index].cannonballs_available -= cannonball_loot_amount;
                                    if (islands[current_island_index].cannonballs_available < 0) {
                                        islands[current_island_index].cannonballs_available = 0;
                                    }
                                    
                                    islands[current_island_index].rum_available -= rum_loot_amount;
                                    if (islands[current_island_index].rum_available < 0) {
                                        islands[current_island_index].rum_available = 0;
                                    }

                                    // Give loot to ship
                                    myShip.treasure += treasure_loot_amount;
                                    myShip.food += food_loot_amount;
                                    myShip.cannonballs += cannonball_loot_amount;
                                    myShip.rum += rum_loot_amount;
                                    // Need to render this into the stats area (I assume that is where the ship health will be)

                                    clearAndRedraw(text_area, "t");

                                    // Calculate if mates get injured in the process of looting the island maybe 20% chance per mate?
                                    for (int i = 0; i < number_of_alive_pirates; i++) {     //
                                        float damage_chance = getRandomFloat(); // number between 0 and 1
                                        int damage_taken = 15 + rand() % 8; // 15 to 22

                                        if (damage_chance <= 0.2) {
                                            myShip.crew[i].health -= damage_taken;
                                            if (myShip.crew[i].health <= 0) {
                                                mvwprintw(text_area, i + 10, 2, "%s died while searching %s.", myShip.crew[i].name, islands[current_island_index].name);  // If two or more pirates die at the same time, one overwrites the other  
                                                // Shift remaining pirates to fill the gap
                                                for (int j = i; j < number_of_alive_pirates - 1; j++) {
                                                    myShip.crew[j] = myShip.crew[j + 1];
                                                }
                                                number_of_alive_pirates--;

                                                i--;

                                                // leaves for loop if no more pirates are alive (or if there is somehow negative pirates)
                                                if (number_of_alive_pirates <= 0) {
                                                    break;
                                                }
                                            } else {                    // add else if or switch case 0.1 etc random strings
                                                mvwprintw(text_area, i + 2, 2, "%s took %d damage. They now have %d health.", myShip.crew[i].name, damage_taken, myShip.crew[i].health);
                                            }
                                        } else {
                                            int check_for_level_up = myShip.crew[i].attributes.thievery;

                                            int exp_gain = treasure_loot_amount + rand() % 30;  // May need to adjust this

                                            myShip.crew[i].attributes.thievery_exp += exp_gain;

                                            int new_thievery_level = calculateLevel(myShip.crew[i].attributes.thievery, myShip.crew[i].attributes.thievery_exp);
                                            myShip.crew[i].attributes.thievery = new_thievery_level;

                                            if (myShip.crew[i].attributes.thievery > check_for_level_up) {
                                                int amount_of_levels_gained = myShip.crew[i].attributes.thievery - check_for_level_up;
                                                if (amount_of_levels_gained == 1) {
                                                    mvwprintw(text_area, i + 2, 2, "%s gained a level in thievery after receiving %d thievery xp. %s now has %d thievery xp.", myShip.crew[i].name, exp_gain, myShip.crew[i].name, myShip.crew[i].attributes.thievery_exp);
                                                } else {
                                                    mvwprintw(text_area, i + 2, 2, "%s gained %d levels in thievery after receiving %d thievery xp. %s now has %d thievery xp.", myShip.crew[i].name, amount_of_levels_gained, exp_gain, myShip.crew[i].name, myShip.crew[i].attributes.thievery_exp);
                                                }
                                            } else {
                                                mvwprintw(text_area, i + 2, 2, "%s gained %d thievery xp. %s now has %d thievery xp.", myShip.crew[i].name, exp_gain, myShip.crew[i].name, myShip.crew[i].attributes.thievery_exp);
                                            }
                                        }
                                        if (i == number_of_alive_pirates - 1) {
                                            renderPirateAttributes(attribute_area, myShip, number_of_alive_pirates);
                                            mvwprintw(text_area, i + 3, 2, "Press any key to continue..."); // Will have issues if a pirate dies
                                            wrefresh(text_area);
                                        }   
                                    }

                                    // leaves switch case in addition to the while loop to send the user to the restart screen
                                    if (number_of_alive_pirates == 0) {
                                        clearAndRedraw(text_area, "t");
                                        continue_from_while = 0;
                                        break;
                                    }
                                    
                                    // renderPirateAttributes(attribute_area, myShip, number_of_alive_pirates);
                                    // mvwprintw(text_area, number_of_alive_pirates + 2, 2, "Press any key to continue..."); // Will have issues if a pirate dies
                                    // wrefresh(text_area);

                                    waitForInput();
                                    
                                    clearAndRedraw(text_area, "t");

                                    mvwprintw(text_area, 2, 2, "%d treasure gained. You now have %d treasure", treasure_loot_amount, myShip.treasure);
                                    mvwprintw(text_area, 3, 2, "You gained %d food, %d cannonball(s), and %d rum. You now have %d food, %d cannonball(s), and %d rum.", food_loot_amount, cannonball_loot_amount, rum_loot_amount, myShip.food, myShip.cannonballs, myShip.rum);
                                    mvwprintw(text_area, 4, 2, "Press any key to continue...");
                                    wrefresh(text_area);

                                    waitForInput();
                                    // Mark the island as looted
                                    islands[current_island_index].is_looted = true;
                                    continue_from_while = 0;
                                } else {
                                    clearAndRedraw(text_area, "t");
                                    mvwprintw(text_area, 2, 2, "%s has been looted recently.", islands[current_island_index].name);
                                    mvwprintw(text_area, 3, 2, "Press any key to continue...");
                                    wrefresh(text_area);

                                    waitForInput();
                                }

                                clearAndRedraw(text_area, "t");

                                break;
                            case 4:
                                break;
                            case 5:
                                break;
                            default:
                                mvwprintw(text_area, 24, 2, "Enter an interger between 1 and 5.");
                                wrefresh(text_area);
                                break;
                        }
                    }
                }
            }
            continue_from_while = 1;

            if (myShip.is_at_sea && number_of_alive_pirates != 0) {
                float pirate_ship_encounter = getRandomFloat();
                if (pirate_ship_encounter <= 0.19) {

                }
            }

            if (!myShip.is_at_sea && islands[current_island_index].is_island_hostile && number_of_alive_pirates != 0) {
                while (continue_from_while) {
                    mvwprintw(text_area, 2, 2, "You're at the port of %s. You hear rumors that this island is not so friendly. What would you like to do next?", islands[current_island_index].name);
                    mvwprintw(text_area, 3, 2, "1: Raid the island.");
                    wrefresh(text_area);

                    int ch = wgetch(text_area);

                    if (ch != ERR) {
                        hostile_port_choice = ch - '0';  // Convert ASCII to integer
                        switch (hostile_port_choice) {
                            case 1:
                                
                                break;
                            case 2:
                                
                                break;
                            case 3:
                                
                                break;
                            case 4:
                               
                                break;
                            case 5:
                                
                                break;
                            default:
                                mvwprintw(text_area, 24, 2, "Enter an interger between 1 and 5.");
                                wrefresh(text_area);
                                break;
                        }
                    }
                }
            }
            continue_from_while = 1;

            // 4. Other Game Logic --------------------------

            // Restocking of islands after the fact just-in-case the user ends up on the same island again
            for (int i = 0; i < NUMBER_OF_ISLANDS; i++) {
                // Check if the island is looted and restock if it is
                if (islands[i].is_looted) {
                    // Increment resources based on your restocking logic
                    islands[i].treasure_available += RESTOCK_RATE;
                    islands[i].food_available += RESTOCK_RATE;
                    islands[i].cannonballs_available += RESTOCK_RATE;
                    islands[i].rum_available += RESTOCK_RATE;
                    
                    // Ensure resources don't exceed the unique maximum values
                    if (islands[i].treasure_available > islands[i].max_treasure) {
                        islands[i].treasure_available = islands[i].max_treasure;
                    }
                    if (islands[i].food_available > islands[i].max_food) {
                        islands[i].food_available = islands[i].max_food;
                    }
                    if (islands[i].cannonballs_available > islands[i].max_cannonballs) {
                        islands[i].cannonballs_available = islands[i].max_cannonballs;
                    }
                    if (islands[i].rum_available > islands[i].max_rum) {
                        islands[i].rum_available = islands[i].max_rum;
                    }

                    // Mark the island as not looted if it reaches the unique maximum in each resource
                    if (islands[i].treasure_available == islands[i].max_treasure &&
                        islands[i].food_available == islands[i].max_food &&
                        islands[i].cannonballs_available == islands[i].max_cannonballs &&
                        islands[i].rum_available == islands[i].max_rum) {
                        islands[i].is_looted = false;
                    }
                }
            }

            //usleep(100000);  // Sleep for 0.1 seconds (100,000 microseconds)
        }

        clearAndRedraw(text_area, "t");

        if (myShip.health <= 0) {
            int center_x = TEXT_BORDER_X / 2 - strlen("Game over. Your ship was destroyed.") / 2;
            int center_y = TEXT_BORDER_Y / 2;

            mvwprintw(text_area, center_y, center_x, "Game over. Your ship was destroyed.");
            wrefresh(text_area);
        }

        if (number_of_alive_pirates == 0) {
            int center_x = TEXT_BORDER_X / 2 - strlen("Game over. All of your mates died.") / 2;
            int center_y = TEXT_BORDER_Y / 2;

            mvwprintw(text_area, center_y, center_x, "Game over. All of your mates died.");
            wrefresh(text_area);
        }

        // End game loop
        while (1) {
            mvwprintw(text_area, 23, 2,"Restart? y/n:");
            wrefresh(text_area);
            
            last_decision = getch();

            if (last_decision == 'y') {
                clearAndRedraw(text_area, "t");
                renderPirateAttributes(attribute_area, myShip, number_of_alive_pirates);
                clearAndRedraw(stats_area, "s");
                clearAndRedraw(visual_area, "v");
                break;
            } else if (last_decision == 'n') {
                endwin(); // End curses mode
                return 0;
            } else {
                mvwprintw(text_area, 24, 2, "Enter 'y' or 'n'.");
                wrefresh(text_area);
                usleep(500000); // Sleep for a short time to display the message
            }
        }
    } while (last_decision == 'y');

    return 0;
}