#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void initializePirate(Pirate* pirate) {
    // Other initialization code

    pirate->attributes.thievery = 4;   // Default value, adjust as needed
    pirate->attributes.charisma = 4;
    pirate->attributes.seamanship = 4;
    pirate->attributes.medicine = 4;
    pirate->attributes.instinct = 4;
    pirate->attributes.leadership = 4;
}


// Function to get attributes from the player
// Function to get attributes from the player for a given pirate
void getPlayerAttributes(Pirate* pirate, int pirateNumber) {
    printf("\nAllocate attribute points for Pirate %d:\n", pirateNumber);
    printf("Thievery (0-10): ");
    scanf("%d", &pirate->attributes.thievery);

    printf("Charisma (0-10): ");
    scanf("%d", &pirate->attributes.charisma);

    printf("Seamanship (0-10): ");
    scanf("%d", &pirate->attributes.seamanship);

    printf("Medicine (0-10): ");
    scanf("%d", &pirate->attributes.medicine);

    printf("Instinct (0-10): ");
    scanf("%d", &pirate->attributes.instinct);

    printf("Leadership (0-10): ");
    scanf("%d", &pirate->attributes.leadership);

    // Input validation
    while (pirate->attributes.thievery + pirate->attributes.charisma + pirate->attributes.seamanship +
           pirate->attributes.medicine + pirate->attributes.instinct + pirate->attributes.leadership > 13) {
        printf("Total points cannot exceed 13. Reallocate attribute points for Pirate %d:\n", pirateNumber);
        printf("Thievery (0-10): ");
        scanf("%d", &pirate->attributes.thievery);

        printf("Charisma (0-10): ");
        scanf("%d", &pirate->attributes.charisma);

        printf("Seamanship (0-10): ");
        scanf("%d", &pirate->attributes.seamanship);

        printf("Medicine (0-10): ");
        scanf("%d", &pirate->attributes.medicine);

        printf("Instinct (0-10): ");
        scanf("%d", &pirate->attributes.instinct);

        printf("Leadership (0-10): ");
        scanf("%d", &pirate->attributes.leadership);
    }
}



// Function to initialize the pirate ship and crew
void initializeShip(Ship* ship) {
    ship->distance = 0;                     // tweak intiial resources here steven H
    ship->treasure = 0;
    ship->food = 30;
    ship->cannonballs = 10;
    ship->rum = 20;

    for (int i = 0; i < 4; i++) {
        snprintf(ship->crew[i].name, sizeof(ship->crew[i].name), "Pirate %d", i + 1);
        ship->crew[i].health = 100;
        ship->crew[i].morale = 100;
        ship->crew[i].experience = 0;
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
    printf("    (                                                      (\n");
    printf("    (                   Distance: %d nautical miles        (\n", ship.distance);
    printf("    (                   Treasure: %d pieces                (\n", ship.treasure);
    printf("    (                   Food: %d units                     (\n", ship.food);
    printf("    (                   Cannonballs: %d                    (\n", ship.cannonballs);
    printf("    (                   Rum: %d barrels                    (\n", ship.rum);
    printf("    (                                                      (\n");
    printf("    (                   Crew Members:                     (\n");
    for (int i = 0; i < 4; i++) {
        printf("    (  %s - Health: %d, Morale: %d, Experience: %d  (\n", ship.crew[i].name, ship.crew[i].health, ship.crew[i].morale, ship.crew[i].experience);
    }
    printf("    (  Weather: ");
    switch (weather) {
        case CLEAR:
            printf("Clear                                       (\n");
            break;
        case STORM:
            printf("Stormy              (\n");
            break;
        case CALM:
            printf("Calm                (\n");
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


// Function to simulate the player's decision during the pirate journey
void makeDecision(Ship* ship, Island* currentIsland, int currentIslandIndex, Weather* weather) {
    printf("What will you do?\n");
    printf("1. Sail to the next island\n");
    printf("2. Rest the crew for a day\n");
    printf("3. Search for treasure on the island\n");
    printf("4. Trade with the locals\n");

    int choice;
    scanf("%d", &choice);
    getchar(); // Consume the newline character

    int randomDistance; //declares randomDistance before switchcase

    switch (choice) {
        case 1:
            randomDistance = rand() % 30 + 12;
            ship->distance += randomDistance;

            // Adjust food and rum consumption based on the random distance
            ship->food -= (randomDistance / 10);
            ship->rum -= (randomDistance / 15);             // same goes here bih its been increased doh

            // Display different dialogues based on the distance traveled
            if (randomDistance >= 12 && randomDistance <= 14) {
                printf("You set sail for the next island, and the sea is calm and peaceful.\n");
            } else if (randomDistance >= 15 && randomDistance <= 17) {
                printf("You encounter some rough waves, but your skilled crew navigates through them.\n");
            } else if (randomDistance >= 18 && randomDistance <= 20) {
                printf("Dark clouds gather in the sky, and the crew braces for an approaching storm.\n");
            } else {
                // Add more cases for different distances and events
                printf("Your journey continues...\n");
            }




            break;
        case 2:                                             // handles the rest for the day for the crew option 2
            for (int i = 0; i < 4; i++) {
                ship->crew[i].health += 10;
                if (ship->crew[i].health > 100) {
                    ship->crew[i].health = 100;
                }
            }
            ship->food -= 5;
            ship->rum -= 2;
            break;
        case 3:
            printf("You found %d pieces of treasure on %s!\n", currentIsland->treasureAvailable, currentIsland->name);      // needs more options for not finding treasure
            ship->treasure += currentIsland->treasureAvailable;
            currentIsland->treasureAvailable = 0;
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
            }
            break;


        default:
            printf("Invalid choice. Continue sailing to the next island.\n");
            ship->distance += 50;
            ship->food -= 10;
            ship->rum -= 5;
    }

    if (ship->food < 0) {
        ship->food = 0;
    }

    if (ship->rum < 0) {
        ship->rum = 0;
    }

    randomEvent(ship, &weather, currentIsland);






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
    srand((unsigned int)time(NULL));

    // intiliaze pirate ships and islands

    Ship pirateShip;
    initializeShip(&pirateShip);

    Island islands[3];
    initializeIsland(&islands[0], "Tortuga", "A notorious pirate haven", 0, 0, 0, 0);
    initializeIsland(&islands[1], "Isla de Muerta", "Rumored to have cursed treasure", 50, 20, 10, 15);
    initializeIsland(&islands[2], "Treasure Island", "The final destination for legendary riches", 100, 30, 20, 30);

    // print game intro

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

    getPlayerAttributes(&pirateShip.crew[0], 0);

    Pirate pirates[4];
    for (int i = 0; i < 4; i++) {
        snprintf(pirates[i].name, sizeof(pirates[i].name), "Pirate %d", i + 1);
        getPlayerAttributes(&pirates[i], i + 1);
        pirates[i].health = 100;
        pirates[i].morale = 100;
        pirates[i].experience = 0;
    }



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
