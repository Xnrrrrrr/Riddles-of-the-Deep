#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_PIRATE_NAME_LENGTH 8
#define MAX_STRING_LENGTH 100
#define NUMBER_OF_PIRATES 4

typedef struct {
    int thievery;
    int charisma;
    int seamanship;     // navigating storms/obstacles
    int medicine;       // health recovery skill
    int instinct;       // survival instinct skill
    int leadership;     // how well a crew member leads others
    int carpentry;
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
    int experience;
    Attributes attributes;
} Pirate;

typedef struct {
    int distance;
    int treasure;
    int food;
    int cannonballs;
    int rum;
    int health;
    Pirate crew[NUMBER_OF_PIRATES];
} Ship;

typedef struct {
    char name[MAX_STRING_LENGTH];
    char description[MAX_STRING_LENGTH];
    int treasureAvailable;
    int foodAvailable;
    int cannonballsAvailable;
    int rumAvailable;
} Island;

Difficulty difficulty;

Attributes getBasePirateAttributes(Difficulty difficulty) {
    Attributes baseAttributes;

    int thievery_base = rand() % 16 + 10;
    int charisma_base = rand() % 14 + 8;
    int seamanship_base = rand() % 18 + 12;
    int medicine_base = rand() % 12 + 6;
    int instinct_base = rand() % 14 + 8;
    int leadership_base = rand() % 16 + 10;
    int carpentry_base = rand() % 15 + 9;

    switch (difficulty) {
        case EASY:
            baseAttributes.thievery = thievery_base;
            baseAttributes.charisma = charisma_base;
            baseAttributes.seamanship = seamanship_base;
            baseAttributes.medicine = medicine_base;
            baseAttributes.instinct = instinct_base;
            baseAttributes.leadership = leadership_base;
            baseAttributes.carpentry = carpentry_base;
            break;

        case NORMAL:
            baseAttributes.thievery = thievery_base / 2;
            baseAttributes.charisma = charisma_base / 2;
            baseAttributes.seamanship = seamanship_base / 2;
            baseAttributes.medicine = medicine_base / 2;
            baseAttributes.instinct = instinct_base / 2;
            baseAttributes.leadership = leadership_base / 2;
            break;

        case HARD:
            baseAttributes.thievery = thievery_base / 3;
            baseAttributes.charisma = charisma_base / 3;
            baseAttributes.seamanship = seamanship_base / 3;
            baseAttributes.medicine = medicine_base / 3;
            baseAttributes.instinct = instinct_base / 3;
            baseAttributes.leadership = leadership_base / 3;
            break;
    }

    return baseAttributes;
}

int main() {
    char last_decision;
    do {
        int difficultyChoice;

        char pirate_name[MAX_PIRATE_NAME_LENGTH];

        Ship myShip;
        myShip.health = 100;
        myShip.distance = 0;

        int number_of_alive_pirates = NUMBER_OF_PIRATES;

        bool is_at_sea = false;

        int port_choice;

        bool has_treasure_map = false;

        while (1) {
            printf("Enter difficulty level: \n");
            printf("1: EASY \n");
            printf("2: NORMAL \n");
            printf("3: HARD \n");
            if (scanf(" %d", &difficultyChoice) != 1) {
                printf("Invalid input. Please enter an integer. \n");

                while (getchar() != '\n');
            } else {
                if (difficultyChoice == 1) {
                    difficulty = EASY;
                    myShip.cannonballs = 20;
                    myShip.treasure = 20;
                    myShip.food = 48;
                    myShip.rum = 30;
                    break;
                } else if (difficultyChoice == 2) {
                    difficulty = NORMAL;
                    myShip.cannonballs = 10;
                    myShip.treasure = 10;
                    myShip.food = 24;
                    myShip.rum = 20;
                    break;
                } else if (difficultyChoice == 3) {
                    difficulty = HARD;
                    myShip.cannonballs = 4;
                    myShip.treasure = 0;
                    myShip.food = 12;
                    myShip.rum = 10;
                    break;
                } else {
                    printf("Enter an interger between 1 and 3. \n\n");
                }
            }
        }

        for (int i = 0; i < NUMBER_OF_PIRATES; i++) {
            char pirate_name[MAX_PIRATE_NAME_LENGTH];

            while (1) {
                printf("Enter the name of your pirate #%d: (Must be %d characters or less)\n", i + 1, MAX_PIRATE_NAME_LENGTH);
                scanf(" %s", pirate_name);

                if (strlen(pirate_name) <= MAX_PIRATE_NAME_LENGTH) {
                    strcpy(myShip.crew[i].name, pirate_name);
                    break;
                } else {
                    printf("Try again. The pirate's name should be %d characters or less. \n\n", MAX_PIRATE_NAME_LENGTH);
                }
            }
        }

        Attributes baseAttributes = getBasePirateAttributes(difficulty);

        // Inside the loop where you create pirates
        for (int i = 0; i < NUMBER_OF_PIRATES; i++) {
            // Other attributes initialization...
            myShip.crew[i].attributes = baseAttributes;
            myShip.crew[i].health = 100;
            myShip.crew[i].morale = 100;
            myShip.crew[i].experience = 0;
        }

        // game loop
        while (myShip.health > 0 && number_of_alive_pirates > 0) {
            // 1 Update game state and perform game logic here

            // Decrease health of the ship over time
            // myShip.health--;

            // Decrease first pirates health of the ship over time
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
                }
            }

            // 2. Print Current Game State
            
            //printf("Ship Health: %d\n", myShip.health);

            for (int i = 0; i < number_of_alive_pirates; i++) {
                printf("%s, hp: %d \n", myShip.crew[i].name, myShip.crew[i].health);
            }

            // 3. Dialog and Chat Options
            if (!is_at_sea) {
                while (1) {
                    printf("You are at port (insert port name). What would you like to do? \n");
                    printf("1. Explore the seas for treasure. \n");
                    printf("2. Rest for the day. \n"); // Low chance for a crew member to go awol?
                    printf("3. Scour the island for riches. \n"); // Chance to lose or find new mates; 
                    printf("4. Hit the pub with your mates. \n"); // Raises moral but has a chance for one of your mates to get in a fight and injured. Maybe a chance to recruit a new mate for the price of some treasure. Consumes food, rum, and treasure?
                    printf("5. Trade with the locals. \n"); 

                    if (scanf(" %d", &port_choice) != 1) {
                        printf("Invalid input. Please enter an integer. \n");

                        while (getchar() != '\n');
                    } else {
                        switch (port_choice) {
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
                                printf("Enter an interger between 1 and 5. \n");
                                break;
                        }
                    }
                }
            }
            // 4. Other Game Logic

            // Add other game logic as needed

            // Introduce a delay to make the game playable
            // usleep(100000);  // Sleep for 0.1 seconds (100,000 microseconds)
        }

        if (myShip.health <= 0) {
            printf("Game over. Your ship was destroyed. \n");
        }

        if (number_of_alive_pirates == 0) {
            printf("Game over. All of your crew mates died. \n");
        }

        while (1) {
            printf("Restart? y/n: \n");
            scanf(" %c", &last_decision);

            if (last_decision == 'y') {
                break;
            } else if (last_decision == 'n') {
                return 0;
            } else {
                printf("Enter 'y' or 'n'. \n");
            }
        }
    } while (last_decision == 'y');
}