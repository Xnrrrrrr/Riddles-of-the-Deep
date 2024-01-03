#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Define constants for maximum string length
#define MAX_STRING_LENGTH 100

// define a structure for attributes
typedef struct {
    int thievery;       // thievery skill
    int charisma;       // charisma skill
    int seamanship;     // sailing related skill, navigating storms/obstacles
    int medicine;       // health recovery skill
    int instinct;       // survival instinct skill
    int leadership;     // leadership skill how well a crew member leads others
} Attributes;

// define an enum for diffuculty selection
typedef enum {
    EASY,
    NORMAL,
    HARD
} Difficulty;

// Define a structure for a pirate crew member
typedef struct {
    char name[MAX_STRING_LENGTH];
    int health;
    int morale;
    int experience;
    Attributes attributes;
} Pirate;


// Define a structure for the pirate ship
typedef struct {
    int distance;
    int treasure;
    int food;
    int cannonballs;
    int rum;
    int health;
    Pirate crew[4];
} Ship;

// Define a structure for an island
typedef struct {
    char name[MAX_STRING_LENGTH];
    char description[MAX_STRING_LENGTH];
    int treasureAvailable;
    int foodAvailable;
    int cannonballsAvailable;
    int rumAvailable;
} Island;

// Define a structure for weather conditions
typedef enum {
    CLEAR,
    STORM,
    CALM
} Weather;



// Function to initialize attributes based on difficulty
void initializePirateAttributes(Attributes *attributes, Difficulty difficulty) {
    switch (difficulty) {
        case EASY:
            attributes->thievery = 15;
            attributes->charisma = 20;
            attributes->seamanship = 25;
            attributes->medicine = 10;
            attributes->instinct = 20;
            attributes->leadership = 15;
            break;
        case NORMAL:
            attributes->thievery = 10;
            attributes->charisma = 15;
            attributes->seamanship = 20;
            attributes->medicine = 10;
            attributes->instinct = 15;
            attributes->leadership = 10;
            break;
        case HARD:
            attributes->thievery = 5;
            attributes->charisma = 10;
            attributes->seamanship = 15;
            attributes->medicine = 5;
            attributes->instinct = 10;
            attributes->leadership = 5;
            break;
    }
}

// Function to initialize pirate crew member
void initializePirate(Pirate *pirate, Difficulty difficulty) {
    // Implement pirate initialization logic here
    pirate->health = 100;
    pirate->morale = 100; // Start with full morale
    pirate->experience = 0;
    initializePirateAttributes(&pirate->attributes, difficulty);
}


// Function to initialize the pirate ship and crew
void initializeShip(Ship* ship, Difficulty difficulty) {
    ship->distance = 0;                     // tweak intiial resources here steven H
    ship->treasure = 0;
    ship->food = 30;
    ship->cannonballs = 10;
    ship->rum = 20;
    ship->health = 100;

    for (int i = 0; i < 4; i++) {
        snprintf(ship->crew[i].name, sizeof(ship->crew[i].name), "Pirate %d", i + 1);
        ship->crew[i].health = 100;
        ship->crew[i].morale = 100;
        ship->crew[i].experience = 0;
        initializePirate(&ship->crew[i], difficulty);
    }
}

// Function to clear the terminal screen

void clearScreen() {
    system("cls"); // For windows
    // system("clear"); // For linux/unix
}



// Function to initialize an island
void initializeIsland(Island* island, const char* name, const char* description, int treasure, int food, int cannonballs, int rum) {
    snprintf(island->name, sizeof(island->name), "%s", name);
    snprintf(island->description, sizeof(island->description), "%s", description);
    island->treasureAvailable = treasure;
    island->foodAvailable = food;
    island->cannonballsAvailable = cannonballs;
    island->rumAvailable = rum;
}

void displayShipStatusVisual() {
    printf(" \n");
    printf("                                      .(  )`-._\n");
    printf("                                    .'  ||     `._\n");
    printf("                                  .'    ||        `.\n");
    printf("                               .'       ||          `._\n");
    printf("                             .'        _||_            `-.%c", '\n');
    printf("                          .'          |====|              `..%c", '\n');
    printf("                        .'             \\__/               (  )%c", '\n');
    printf("                      ( )               ||          _      ||%c", '\n');
    printf("                      /|\\               ||       .-` \\     ||%c", '\n');
    printf("                    .' | '              ||   _.-'    |     ||%c", '\n');
    printf("                   /   |\\ \\             || .'   `.__.'     ||   _.-..%c", '\n');
    printf("                 .'   /| `.            _.-'   _.-'       _.-.`-'`._`.`%c", '\n');
    printf("                \\  .' |  |        .-.`    `./      _.-`.    `._.-'%c", '\n');
    printf("                 |.   |  `.   _.-'   `.   .'     .'  `._.`---`%c", '\n');
    printf("                .'    |   |  :   `._..-'.'        `._..'  ||%c", '\n');
    printf("               /      |   \\  `-._.'    ||                 ||%c", '\n');
    printf("              |     .'|`.  |           ||_.--.-._         ||%c", '\n');
    printf("              '    /  |  \\ \\       __.--'\\    `. :        ||%c", '\n');
    printf("               \\  .'  |   \\|   ..-'   \\   `._-._.'        ||%c", '\n');
    printf("`.._            |/    |    `.  \\  \\    `._.-              ||%c", '\n');
    printf("    `-.._       /     |      \\  `-.'_.--'                 ||%c", '\n');
    printf("         `-.._.'      |      |        | |         _ _ _  _'_ _ _ _ _%c", '\n');
    printf("              `-.._   |      \\        | |        |_|_|_'|_|_|_|_|_|_|%c", '\n');
    printf("                  [`--^-..._.'        | |       /....../|  __   __  |%c", '\n');
    printf("                   \\`---.._|`--.._    | |      /....../ | |__| |__| |%c", '\n');
    printf("                    \\__  _ `-.._| `-._|_|_ _ _/_ _ _ /  | |__| |__| |%c", '\n');
    printf("                     \\   _o_   _`-._|_|_|_|_|_|_|_|_/   '-----------/%c", '\n');
    printf("                      \\_`.|.'  _  - .--.--.--.--.--.`--------------'%c", '\n');
    printf("      .```-._ ``-.._   \\__   _    _ '--'--'--'--'--'  - _ - _  __/%c", '\n');
    printf(" .`-.```-._ ``-..__``.- `.      _     -  _  _  _ -    _-   _  __/(.``-._%c", '\n');
    printf(" _.-` ``--..  ..    _.-` ``--..  .. .._ _. __ __ _ __ ..--.._ / .( _..```\n");
    printf("`.-._  `._  `- `-._  .`-.```-._ ``-..__``.-  -._--.__---._--..-._`...```\n");
    printf("   _.-` ``--..  ..  `.-._  `._  `- `-._ .-_. ._.- -._ --.._`` _.-``-.\n");


// add a way to generate four different pirate asci arts to the right of the ship
// generate


}

// Function to display the status of the pirate ship
void displayShipStatus(Ship ship, Weather weather) {
    displayShipStatusVisual();
    printf("    _______________________________________________________\n");
    printf("    /\\                                                      \\\n");
    printf("(O)===)><><><><><><><><><><><><><><><><><><><><><><><><><><><)==(O)\n");
    printf("    \\/''''''''''''''''''''''''''''''''''''''''''''''''''''''/\n");
    printf("    (                                                      (\n");
    printf("     )                                                      )\n");
    printf("    (                                                      (\n");
    printf("     )                                                      )\n");
    printf("    (                   Pirate Ship                        (\n");
    printf("     )                                                      )\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("     )                                                      )\n");
    printf("    (                                                      (\n");
    printf("     )                                                      )\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("    (                                                      (\n");
    printf("    (                   Ship Health: %d                   (\n", ship.health);
    printf("    (                   Distance: %d nautical miles         (\n", ship.distance);
    printf("    (                   Treasure: %d pieces                 (\n", ship.treasure);
    printf("    (                   Food: %d units                     (\n", ship.food);
    printf("    (                   Cannonballs: %d                    (\n", ship.cannonballs);
    printf("    (                   Rum: %d barrels                    (\n", ship.rum);
    printf("    (                                                      (\n");
    printf("    (                   Crew Members:                      (\n");
    for (int i = 0; i < 4; i++) {
        printf("    (  %s - Health: %d, Morale: %d, Experience: %d  (\n", ship.crew[i].name, ship.crew[i].health, ship.crew[i].morale, ship.crew[i].experience);
    }
    printf("    (  Weather: ");
    switch (weather) {
        case CLEAR:
            printf("Clear                                      (\n");
            break;
        case STORM:
            printf("Stormy                                     (\n");
            break;
        case CALM:
            printf("Calm                                       (\n");
            break;
    }
    printf("    (                                                      (\n");
    printf("    \\/______________________________________________________/\n");
    printf("\n");
}



// Function to simulate a random event during the pirate journey
void randomEvent(Ship* ship, Weather* weather, Island* currentIsland) {
    int event = rand() % 5; // 0 to 4

    switch (event) {
        case 0:
            printf("You encountered a friendly trading ship and gained extra treasure!\n");
            ship->treasure += 20;
            break;
        case 1:
            printf("You discovered a hidden cove with valuable treasures!\n");
            ship->treasure += 30;
            break;
        case 2:
            printf("Oh no! A rival pirate ship attacked you!\n");
            for (int i = 0; i < 4; i++) {
                int damage = rand() % 20 + 10; // Random damage between 10 and 30
                ship->crew[i].health -= damage;
            }
            break;
        case 3:
            printf("The weather changed to a storm! Your ship's crew morale decreased.\n");
            for (int i = 0; i < 4; i++) {
                ship->crew[i].morale -= 20;
                if (ship->crew[i].morale < 0) {
                    ship->crew[i].morale = 0;
                }
            }
            *weather = STORM;
            break;
        case 4:
            printf("You found a peaceful island, %s. Your crew's morale increased!\n", currentIsland->name);
            for (int i = 0; i < 4; i++) {
                ship->crew[i].morale += 20;
                if (ship->crew[i].morale > 100) {
                    ship->crew[i].morale = 100;
                }
            }
            break;
        case 5:
            printf("A giant sea monster surfaces near your ship. Your crew is shaking in their boots!");
            for (int i = 0; i < 4; i++) {
                ship->crew[i].morale -= 35;
                if (ship->crew[i].morale > 100) {
                    ship->crew[i].morale = 100;
                }
            }
            break;
        case 6:
            printf("The water is choppy and waves are beginning to surround the ship ");
            for (int i = 0; i < 4; i++) {           // iterates through each members of the crew
                ship->crew[i].morale -= 10;         // increases or decreases the morale of each crew member by 20
                if (ship->crew[i].morale > 100) {   // after in or de of the morale, checks if it exceeds 0 or 100
                    ship->crew[i].morale = 100;     // ensures morale doesnt go to 0
                }
            }
            break;

    }

    // penalties for resource shortages     ADD CANNONBALL SHORTAGE
    if (ship->food == 0) {
        printf("Your crew is hungry! Morale decreased.\n");
        for (int i = 0; i < 4; i++) {
            ship->crew[1].morale -= 10;
            if (ship->crew[i].morale < 0) {
                ship->crew[i].morale = 0;
            }
        }
    }

    if (ship->rum == 0) {
        printf("Your crew is thirsty! Morale decreased.\n");
        for (int i = 0; i < 4; i++) {
            ship->crew[1].morale -= 10;
            if (ship->crew[i].morale < 0) {
                ship->crew[i].morale = 0;
            }
        }
    }
}

// Function to decrease morale
void decreaseMorale(Ship* ship, int amount) {
    ship->crew->morale -= amount;
    if (ship->crew->morale < 0) {
        ship->crew->morale = 0;
    }
}

// Function to increase morale
void increaseMorale(Ship* ship, int amount) {
    ship->crew->morale += amount;
    if (ship->crew->morale > 100) {
        ship->crew->morale = 100;
    }
}

// Function to decrease health
void decreaseHealth(Ship* ship, int amount) {
    ship->crew->health -= amount;
    if (ship->crew->health < 0) {
        ship->crew->health = 0;
    }
}

// Function to increase health
void increaseHealth(Ship* ship, int amount) {
    ship->crew->health += amount;
    if (ship->crew->health > 100) {
        ship->crew->health = 100;
    }
}

// Function to decrease treasure
void decreaseTreasure(Ship* ship, int amount) {
    ship->treasure -= amount;
    if (ship->treasure < 0) {
        ship->treasure = 0;
    }
}

// Function to consume food
void consumeFood(Ship* ship, int amount) {
    ship->food -= amount;
    if (ship->food < 0) {
        ship->food = 0;
    }
}

// Function to decrease crew experience
void decreaseCrewExperience(Ship* ship, int amount) {
    for (int i = 0; i < 4; ++i) {
        ship->crew[i].experience -= amount;
        if (ship->crew[i].experience < 0) {
            ship->crew[i].experience = 0;
        }
    }
}

// Function to simulate the player's decision during the pirate journey
void makeDecision(Ship* ship, Island* currentIsland, int currentIslandIndex, Weather* weather) {
    int continue_from_choice = 1;
    int choice = 0;
    int randomDistance;

    while (continue_from_choice) {
        printf("What will you do?\n");
        printf("1. Sail to the next island\n");
        printf("2. Rest the crew for a day\n");
        printf("3. Search for treasure on the island\n");
        printf("4. Trade with the locals\n");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter an integer. \n");

            while (getchar() != '\n');
        } else {
            switch (choice) {
                case 1:
                    randomDistance = rand() % 32 + 12;
                    ship->distance += randomDistance;

                    if (randomDistance >= 12 && randomDistance <= 14) {
                        // Calm weather has a positive effect on morale and health but is less likely
                        if (rand() % 16 == 0) {
                            printf("You set sail for the next island, and the sea is calm and peaceful.\n");
                            increaseMorale((Ship *) &ship, 10); // Increase morale by 10 points
                            increaseHealth((Ship *) &ship, 15); // Increase health by 15 points
                        } else {
                            printf("Your journey continues...\n");
                            // Continue without positive effects
                        }
                    } else if (randomDistance >= 15 && randomDistance <= 17) {
                        printf("You encounter some rough waves, but your skilled crew navigates through them.\n");
                        // Rough waves decrease morale, health, and treasure, and increase food consumption
                        decreaseMorale(ship, 15);  // Decrease morale by 15 points
                        decreaseHealth(ship, 20);  // Decrease health by 20 points
                        decreaseTreasure(ship, 5); // Decrease treasure by 5 pieces
                        consumeFood(ship, 8);      // Increase food consumption by 8 units
                    } else if (randomDistance >= 18 && randomDistance <= 20) {
                        printf("Dark clouds gather in the sky, and the crew braces for an approaching storm.\n");
                        // Stormy weather decreases health, morale, and treasure, and increases food consumption
                        decreaseHealth(ship, 30); // Decrease health by 30 points
                        decreaseMorale(ship, 25); // Decrease morale by 25 points
                        decreaseTreasure(ship, 10); // Decrease treasure by 10 pieces
                        consumeFood(ship, 12);    // Increase food consumption by 12 units
                        decreaseCrewExperience(ship, 5); // Decrease crew experience by 5 points
                    } else if (randomDistance >= 21 && randomDistance <= 23) {
                        printf("Thick fog envelops the ship, making it difficult to spot potential treasures.\n");
                        // Foggy weather decreases visibility, affecting treasure discovery chances
                        decreaseTreasure(ship, 10); // Decrease treasure by 10 pieces
                    } else if (randomDistance >= 24 && randomDistance <= 26) {
                        printf("The crew faces extreme heat, leading to fatigue and decreased morale.\n");
                        // Hot weather decreases morale and crew experience
                        decreaseMorale(ship, 25); // Decrease morale by 25 points
                        decreaseCrewExperience(ship, 8); // Decrease crew experience by 8 points
                    } else if (randomDistance >= 27 && randomDistance <= 29) {
                        printf("A sudden cold front chills the crew, leading to health issues.\n");
                        // Cold weather decreases health and increases food consumption
                        decreaseHealth(ship, 20); // Decrease health by 20 points
                        consumeFood(ship, 10);    // Increase food consumption by 10 units
                    } else if (randomDistance >= 30 && randomDistance <= 32) {
                        printf("A violent thunderstorm disrupts the ship's course and causes chaos.\n");
                        // Thunderstorm decreases health, morale, and crew experience
                        decreaseHealth(ship, 35); // Decrease health by 35 points
                        decreaseMorale(ship, 30); // Decrease morale by 30 points
                        decreaseCrewExperience(ship, 15); // Decrease crew experience by 15 points
                    }
                    continue_from_choice = 0;
                    break;
                case 2:
                    for (int i = 0; i < 4; i++) {
                        ship->crew[i].health += 20;
                        if (ship->crew[i].health > 100) {
                            ship->crew[i].health = 100;
                        }
                    }
                    ship->food -= 5;
                    ship->rum -= 2;
                    continue_from_choice = 0;
                    break;
                case 3:
                    printf("You found %d pieces of treasure on %s!\n", currentIsland->treasureAvailable, currentIsland->name);      // needs more options for not finding treasure
                    ship->treasure += currentIsland->treasureAvailable;
                    currentIsland->treasureAvailable = 0;
                    continue_from_choice = 0;
                    break;
                case 4:
                    printf("Trading with the locals on %s...\n", currentIsland->name);

                    // Simulate a conversation with locals
                    printf("Locals: Ahoy there, pirate! What brings ye to our humble island?\n");
                    printf("1. Ask about the local rumors.\n");
                    printf("2. Inquire about the available goods for trade.\n");
                    printf("3. Attempt to negotiate the prices.\n");
                    printf("4. Leave without making a trade.\n");

                    int conversationChoice;
                    scanf("%d", &conversationChoice);

                    switch (conversationChoice) {
                        case 1:
                            printf("Locals: Rumor has it there be a hidden treasure chest on the nearby isle. Beware of the curses!\n");
                            break;
                        case 2:
                            printf("Locals: We've got some fine goods for trade. Take a look:\n");
                            printf("   a. Food and rum (Cost: 10 treasure)\n");
                            printf("   b. Cannonballs and rum (Cost: 15 treasure)\n");

                            char tradeOption;
                            if (scanf(" %c", &tradeOption) != 1) {
                                // Invalid input, handle accordingly
                                printf("Invalid choice. No trade was made.\n");
                                break;
                            }

                            switch (tradeOption) {
                                case 'a':
                                    if (ship->treasure >= 10) {
                                        printf("Locals: A wise choice! Here's some food and rum for ye.\n");
                                        ship->food += 30;
                                        ship->rum += 20;
                                        ship->treasure -= 10;
                                    } else {
                                        printf("Locals: Ye don't have enough treasure for this trade!\n");
                                    }
                                    break;
                                case 'b':
                                    if (ship->treasure >= 15) {
                                        printf("Locals: Ready for battle, eh? Here's some cannonballs and rum for ye.\n");
                                        ship->cannonballs += 20;
                                        ship->rum += 30;
                                        ship->treasure -= 15;
                                    } else {
                                        printf("Locals: Ye don't have enough treasure for this trade!\n");
                                    }
                                    break;
                                default:
                                    // Invalid input, handle accordingly
                                    printf("Invalid choice. No trade was made.\n");
                            }
                            break;

                        case 3:
                            printf("Locals: A shrewd negotiator, are ye? Let's see what we can arrange.\n");

                            // Implement your negotiation logic here
                            printf("1. Offer a lower price for the goods.\n");
                            printf("2. Compliment the locals to get a better deal.\n");
                            printf("3. Threaten to find another trader if the price isn't reduced.\n");

                            int negotiationChoice;
                            scanf("%d", &negotiationChoice);

                            switch (negotiationChoice) {
                                case 1:
                                    printf("Locals: Aye, we can lower the price a bit for ye.\n");
                                    // Implement logic to adjust trade based on the user's choice
                                    break;
                                case 2:
                                    printf("Locals: Flattery will get ye everywhere! Enjoy a special discount.\n");
                                    // Implement logic to adjust trade based on the user's choice
                                    break;
                                case 3:
                                    printf("Locals: No need for threats, pirate. We'll make a fair deal.\n");
                                    // Implement logic to adjust trade based on the user's choice
                                    break;
                                default:
                                    printf("Locals: Ye be speakin' gibberish! No trade was made.\n");
                                }
                                break;
                        case 4:
                            printf("Locals: Farewell, pirate. May the winds be at yer back.\n");
                            break;
                        default:
                            printf("Locals: Ye be speakin' gibberish! No trade was made.\n");
                            break;
                        }
                continue_from_choice = 0;
                break;
                default:
                    printf("Enter an interger between 1 and 4. \n");
                    break;
            }
        }
    }

    if (ship->food < 0) {
        ship->food = 0;
    }

    if (ship->rum < 0) {
        ship->rum = 0;
    }

    randomEvent(ship, weather, currentIsland);






}

// Function to check if the game is over
int isGameOver(Ship ship) {
    for (int i = 0; i < 4; i++) {
        if (ship.crew[i].health <= 0 || ship.crew[i].morale <= 0) {
            return 1; // Game over if any crew member's health or morale reaches zero
        }
    }

    if (ship.distance >= 200) {
        return 1; // Game over if the ship reaches 200 nautical miles
    }

    return 0; // Game continues
}

int main() {
    srand((unsigned int)time(NULL));        // creating random seed each time program is ran

    printf("   ______________________________\n");
    printf(" / \\                             \\\n");
    printf("|   |                            |\n");
    printf(" \\_ |                            |\n");
    printf("    | Welcome to Riddles         |\n");
    printf("    |      of the deep!          |\n");
    printf("    |                            |\n");
    printf("    |                            |\n");
    printf("    |                            |\n");
    printf("    |   Your goal is to reach    |\n");
    printf("    |    Treasure Island and     |\n");
    printf("    |     accumulate as much     |\n");
    printf("    |      treasure as possible  |\n");
    printf("    |                            |\n");
    printf("    |                            |\n");
    printf("    |   _________________________|___\n");
    printf("    |  /                            /\n");
    printf("    \\_/____________________________/ \n");

    Difficulty difficulty;
    int difficultyChoice;
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
                break;
            } else if (difficultyChoice == 2) {
                difficulty = NORMAL;
                break;
            } else if (difficultyChoice == 3) {
                difficulty = HARD;
                break;
            } else {
                printf("Enter an interger between 1 and 3. \n\n");
            }
        }
    }

    Pirate pirates[4];

    // intiliaze pirate ships and islands

    Ship pirateShip;
    initializeShip(&pirateShip, difficulty);

    Island islands[13];
    initializeIsland(&islands[0], "Tortuga", "A notorious pirate haven", 0, 0, 0, 0);
    initializeIsland(&islands[1], "Isla de Muerta", "Rumored to have cursed treasure", 50, 20, 10, 15);
    initializeIsland(&islands[2], "Treasure Island", "The final destination for legendary riches", 100, 30, 20, 30);
    initializeIsland(&islands[3], "Blackbeard's Retreat", "Hideout of the infamous Blackbeard", 80, 40, 15, 20);
    initializeIsland(&islands[4], "Crimson Cove", "Known for its vibrant red coral reefs", 60, 25, 12, 18);
    initializeIsland(&islands[5], "Emerald Isle", "Rumored to have mystical emerald artifacts", 90, 35, 25, 22);
    initializeIsland(&islands[6], "Gold Rush Atoll", "Once the site of a legendary gold rush", 120, 50, 30, 35);
    initializeIsland(&islands[7], "Siren's Call", "Beware the enchanting songs of the sirens", 70, 30, 18, 20);
    initializeIsland(&islands[8], "Moonlit Bay", "Shrouded in mystery under the moonlight", 110, 45, 28, 30);
    initializeIsland(&islands[9], "Thunder Isle", "Frequently struck by thunderstorms", 85, 38, 20, 25);
    initializeIsland(&islands[10], "Jade Harbor", "Home to a hidden harbor of valuable jade", 95, 42, 22, 28);
    initializeIsland(&islands[11], "Whispering Sands", "Desert island with secrets carried by the wind", 75, 35, 15, 20);
    initializeIsland(&islands[12], "Mystic Key Atoll", "Guardian of an ancient pirate treasure", 130, 55, 35, 40);



    // init weather and island index

    Weather weather = CLEAR;
    int currentIslandIndex = 0;

    // game loop

    while (!isGameOver(pirateShip)) {
        // display current status
        displayShipStatus(pirateShip, weather);
        // get players decision
        makeDecision(&pirateShip, &islands[currentIslandIndex], currentIslandIndex, &weather);



        if (isGameOver(pirateShip)) {
            printf("Game Over! Your pirate adventure was unsuccessful.\n");
        }

        // Change weather conditions randomly
        if (rand() % 4 == 0) {
            weather = rand() % 3; // 0 to 2
        }

        // Move to the next island if the distance is reached
        if (pirateShip.distance >= 50 && currentIslandIndex < 2) {
            currentIslandIndex++;
            printf("You've reached %s!\n", islands[currentIslandIndex].name);
        }
    }

    printf("Game Over! Your pirate adventure has ended.\n");
    printf("Final Status:\n");
    displayShipStatus(pirateShip, weather);

    return 0;
}
