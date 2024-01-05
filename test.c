#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_PIRATE_NAME_LENGTH 8
#define MAX_STRING_LENGTH 100
#define NUMBER_OF_PIRATES 4
#define NUMBER_OF_ISLANDS 2
#define RESTOCK_RATE 3
#define MAX_LOOT 80

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
    bool is_at_sea;
    Pirate crew[NUMBER_OF_PIRATES];
} Ship;

typedef struct {
    char name[MAX_STRING_LENGTH];
    char description[MAX_STRING_LENGTH];
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
} Island;

Difficulty difficulty;      // declaring

Attributes getBasePirateAttributes() {         // function
    Attributes baseAttributes;                  // declaring baseAttributes

    int thievery_base = 10 + rand() % 7; // 10 to 16        // assigns all baseAttributes to the pirates
    int charisma_base = 8 + rand() % 7; // 8 to 14
    int seamanship_base = 12 + rand() % 7; // 12 to 18
    int medicine_base = 6 + rand() % 7; // 6 to 12
    int instinct_base = 8 + rand() % 7; // 8 to 14
    int leadership_base = 10 + rand() % 7; // 10 to 16
    int carpentry_base = 9 + rand() % 7; // 9 to 15

    switch (difficulty) {                               // switch case based on diff, that divides base attributes
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
            baseAttributes.carpentry = carpentry_base / 2;
            break;

        case HARD:
            baseAttributes.thievery = thievery_base / 3;
            baseAttributes.charisma = charisma_base / 3;
            baseAttributes.seamanship = seamanship_base / 3;
            baseAttributes.medicine = medicine_base / 3;
            baseAttributes.instinct = instinct_base / 3;
            baseAttributes.leadership = leadership_base / 3;
            baseAttributes.carpentry = carpentry_base / 3;
            break;
    }

    return baseAttributes;      // returns the baseAttributes to the main
}

void initializeIslands(Island islands[], int numIslands) {          // function that TAKES island array and numIslands to
    // Non-hostile islands
    snprintf(islands[0].name, MAX_STRING_LENGTH, "Tortuga");
    snprintf(islands[0].description, MAX_STRING_LENGTH, "A lively pirate haven. Starting isle.");
    islands[0].treasure_available = 30;
    islands[0].max_treasure = 30;
    islands[0].food_available = 20;
    islands[0].max_food = 20;
    islands[0].cannonballs_available = 10;
    islands[0].max_cannonballs = 10;
    islands[0].rum_available = 15;
    islands[0].max_rum = 15;
    islands[0].is_island_hostile = false;
    islands[0].is_looted = false;

    snprintf(islands[1].name, MAX_STRING_LENGTH, "Crimson Cove");
    snprintf(islands[1].description, MAX_STRING_LENGTH, "Known for its vibrant red coral reefs");
    islands[1].treasure_available = 30;
    islands[1].max_treasure = 30;
    islands[1].food_available = 20;
    islands[1].max_food = 20;
    islands[1].cannonballs_available = 10;
    islands[1].max_cannonballs = 10;
    islands[1].rum_available = 15;
    islands[1].max_rum = 15;
    islands[1].is_island_hostile = false;
    islands[1].is_looted = false;

    snprintf(islands[3].name, MAX_STRING_LENGTH, "Emerald Isle");
    snprintf(islands[3].description, MAX_STRING_LENGTH, "Rumored to have mystical emerald artifacts");
    islands[3].treasure_available = 30;
    islands[3].max_treasure = 30;
    islands[3].food_available = 20;
    islands[3].max_food = 20;
    islands[3].cannonballs_available = 10;
    islands[3].max_cannonballs = 10;
    islands[3].rum_available = 15;
    islands[3].max_rum = 15;
    islands[3].is_island_hostile = false;
    islands[3].is_looted = false;

    snprintf(islands[4].name, MAX_STRING_LENGTH, "Gold Rush Atoll");
    snprintf(islands[4].description, MAX_STRING_LENGTH, "Once the sight of a legendary gold rush");
    islands[4].treasure_available = 30;
    islands[4].max_treasure = 30;
    islands[4].food_available = 20;
    islands[4].max_food = 20;
    islands[4].cannonballs_available = 10;
    islands[4].max_cannonballs = 10;
    islands[4].rum_available = 15;
    islands[4].max_rum = 15;
    islands[4].is_island_hostile = false;
    islands[4].is_looted = false;

    snprintf(islands[5].name, MAX_STRING_LENGTH, "Whispering Sands");
    snprintf(islands[5].description, MAX_STRING_LENGTH, "Desert Island with secrets carried by the wind");
    islands[5].treasure_available = 30;
    islands[5].max_treasure = 30;
    islands[5].food_available = 20;
    islands[5].max_food = 20;
    islands[5].cannonballs_available = 10;
    islands[5].max_cannonballs = 10;
    islands[5].rum_available = 15;
    islands[5].max_rum = 15;
    islands[5].is_island_hostile = false;
    islands[5].is_looted = false;

    snprintf(islands[6].name, MAX_STRING_LENGTH, "Admiral's Archipelago");
    snprintf(islands[6].description, MAX_STRING_LENGTH, "Enclave for Pirates of the highest status");
    islands[6].treasure_available = 30;
    islands[6].max_treasure = 30;
    islands[6].food_available = 20;
    islands[6].max_food = 20;
    islands[6].cannonballs_available = 10;
    islands[6].max_cannonballs = 10;
    islands[6].rum_available = 15;
    islands[6].max_rum = 15;
    islands[6].is_island_hostile = false;
    islands[6].is_looted = false;

    snprintf(islands[7].name, MAX_STRING_LENGTH, "Port Royal Haven");
    snprintf(islands[7].description, MAX_STRING_LENGTH, "Shrouded in mystery under the moonlight");
    islands[7].treasure_available = 30;
    islands[7].max_treasure = 30;
    islands[7].food_available = 20;
    islands[7].max_food = 20;
    islands[7].cannonballs_available = 10;
    islands[7].max_cannonballs = 10;
    islands[7].rum_available = 15;
    islands[7].max_rum = 15;
    islands[7].is_island_hostile = false;
    islands[7].is_looted = false;

    snprintf(islands[8].name, MAX_STRING_LENGTH, "Nassau Harbor");
    snprintf(islands[8].description, MAX_STRING_LENGTH, "Freedom port, pirate democracy, vibrant nightlife, notorious captains thrive");
    islands[8].treasure_available = 30;
    islands[8].max_treasure = 30;
    islands[8].food_available = 20;
    islands[8].max_food = 20;
    islands[8].cannonballs_available = 10;
    islands[8].max_cannonballs = 10;
    islands[8].rum_available = 15;
    islands[8].max_rum = 15;
    islands[8].is_island_hostile = false;
    islands[8].is_looted = false;

    snprintf(islands[9].name, MAX_STRING_LENGTH, "Buccaneers Refuge");
    snprintf(islands[9].description, MAX_STRING_LENGTH, "Sanctuary for outcasts, camaraderie, shared spoils, legendary pirate lore");
    islands[9].treasure_available = 30;
    islands[9].max_treasure = 30;
    islands[9].food_available = 20;
    islands[9].max_food = 20;
    islands[9].cannonballs_available = 10;
    islands[9].max_cannonballs = 10;
    islands[9].rum_available = 15;
    islands[9].max_rum = 15;
    islands[9].is_island_hostile = false;
    islands[9].is_looted = false;

    snprintf(islands[10].name, MAX_STRING_LENGTH, "Gold Coast Retreat");
    snprintf(islands[10].description, MAX_STRING_LENGTH, "Opulent haven, lavish lifestyles, treacherous alliances, high-stakes intrigues unfold.");
    islands[10].treasure_available = 30;
    islands[10].max_treasure = 30;
    islands[10].food_available = 20;
    islands[10].max_food = 20;
    islands[10].cannonballs_available = 10;
    islands[10].max_cannonballs = 10;
    islands[10].rum_available = 15;
    islands[10].max_rum = 15;
    islands[10].is_island_hostile = false;
    islands[10].is_looted = false;


    // Add more non-hostile islands as needed...

    // Hostile islands
    snprintf(islands[11].name, MAX_STRING_LENGTH, "Isla de Muerta");
    snprintf(islands[11].description, MAX_STRING_LENGTH, "A mysterious and dangerous island.");
    islands[11].treasure_available = 10;
    islands[11].max_treasure = 10;
    islands[11].food_available = 5;
    islands[11].max_food = 5;
    islands[11].cannonballs_available = 20;
    islands[11].max_cannonballs = 20;
    islands[11].rum_available = 5;
    islands[11].max_rum = 5;
    islands[11].is_island_hostile = true;
    islands[11].is_looted = false;

    snprintf(islands[12].name, MAX_STRING_LENGTH, "Skullcap Atoll");
    snprintf(islands[12].description, MAX_STRING_LENGTH, "Dreaded prison, pirate executions, haunted waters, cursed shores beckon danger");
    islands[12].treasure_available = 10;
    islands[12].max_treasure = 10;
    islands[12].food_available = 5;
    islands[12].max_food = 5;
    islands[12].cannonballs_available = 20;
    islands[12].max_cannonballs = 20;
    islands[12].rum_available = 5;
    islands[12].max_rum = 5;
    islands[12].is_island_hostile = true;
    islands[12].is_looted = false;

    snprintf(islands[13].name, MAX_STRING_LENGTH, "Dead Man's Reef");
    snprintf(islands[13].description, MAX_STRING_LENGTH, "A mysterious and dangerous island, Ship graveyard, treacherous currents, ghostly whispers, cursed maritime history.");
    islands[13].treasure_available = 10;
    islands[13].max_treasure = 10;
    islands[13].food_available = 5;
    islands[13].max_food = 5;
    islands[13].cannonballs_available = 20;
    islands[13].max_cannonballs = 20;
    islands[13].rum_available = 5;
    islands[13].max_rum = 5;
    islands[13].is_island_hostile = true;
    islands[13].is_looted = false;

    snprintf(islands[14].name, MAX_STRING_LENGTH, "Noose Point");
    snprintf(islands[14].description, MAX_STRING_LENGTH, "Infamous for executions, pirate justice, a grim place of finality");
    islands[14].treasure_available = 10;
    islands[14].max_treasure = 10;
    islands[14].food_available = 5;
    islands[14].max_food = 5;
    islands[14].cannonballs_available = 20;
    islands[14].max_cannonballs = 20;
    islands[14].rum_available = 5;
    islands[14].max_rum = 5;
    islands[14].is_island_hostile = true;
    islands[14].is_looted = false;

    snprintf(islands[15].name, MAX_STRING_LENGTH, "Red Tide Haven");
    snprintf(islands[15].description, MAX_STRING_LENGTH, "Blood-soaked shores, notorious battles, relentless pirates, danger on every wave");
    islands[15].treasure_available = 10;
    islands[15].max_treasure = 10;
    islands[15].food_available = 5;
    islands[15].max_food = 5;
    islands[15].cannonballs_available = 20;
    islands[15].max_cannonballs = 20;
    islands[15].rum_available = 5;
    islands[15].max_rum = 5;
    islands[15].is_island_hostile = true;
    islands[15].is_looted = false;

    snprintf(islands[16].name, MAX_STRING_LENGTH, "Calico's Cursed Island");
    snprintf(islands[16].description, MAX_STRING_LENGTH, "Infested by pirate outcasts, betrayal, buried grudges, an island of strife");
    islands[16].treasure_available = 10;
    islands[16].max_treasure = 10;
    islands[16].food_available = 5;
    islands[16].max_food = 5;
    islands[16].cannonballs_available = 20;
    islands[16].max_cannonballs = 20;
    islands[16].rum_available = 5;
    islands[16].max_rum = 5;
    islands[16].is_island_hostile = true;
    islands[16].is_looted = false;

    snprintf(islands[17].name, MAX_STRING_LENGTH, "Porto Desperation Isle");
    snprintf(islands[17].description, MAX_STRING_LENGTH, "Exile's refuge, banished pirates, desperate actions, a last resort");
    islands[17].treasure_available = 10;
    islands[17].max_treasure = 10;
    islands[17].food_available = 5;
    islands[17].max_food = 5;
    islands[17].cannonballs_available = 20;
    islands[17].max_cannonballs = 20;
    islands[17].rum_available = 5;
    islands[17].max_rum = 5;
    islands[17].is_island_hostile = true;
    islands[17].is_looted = false;

    snprintf(islands[18].name, MAX_STRING_LENGTH, "Tunis");
    snprintf(islands[18].description, MAX_STRING_LENGTH, "Desolate marsh isle, treacherous betrayal, festering vendettas, a realm gripped by strife");
    islands[18].treasure_available = 10;
    islands[18].max_treasure = 10;
    islands[18].food_available = 5;
    islands[18].max_food = 5;
    islands[18].cannonballs_available = 20;
    islands[18].max_cannonballs = 20;
    islands[18].rum_available = 5;
    islands[18].max_rum = 5;
    islands[18].is_island_hostile = true;
    islands[18].is_looted = false;

    snprintf(islands[19].name, MAX_STRING_LENGTH, "Barataria Bay");
    snprintf(islands[19].description, MAX_STRING_LENGTH, "Treacherous stronghold, pirate vendettas,");
    islands[19].treasure_available = 10;
    islands[19].max_treasure = 10;
    islands[19].food_available = 5;
    islands[19].max_food = 5;
    islands[19].cannonballs_available = 20;
    islands[19].max_cannonballs = 20;
    islands[19].rum_available = 5;
    islands[19].max_rum = 5;
    islands[19].is_island_hostile = true;
    islands[19].is_looted = false;

    snprintf(islands[20].name, MAX_STRING_LENGTH, "Blackbeard's Abyss Isle");
    snprintf(islands[20].description, MAX_STRING_LENGTH, "Shrouded cove, ominous legends, a feared and shadowed retreat");
    islands[20].treasure_available = 10;
    islands[20].max_treasure = 10;
    islands[20].food_available = 5;
    islands[20].max_food = 5;
    islands[20].cannonballs_available = 20;
    islands[20].max_cannonballs = 20;
    islands[20].rum_available = 5;
    islands[20].max_rum = 5;
    islands[20].is_island_hostile = true;
    islands[20].is_looted = false;

    snprintf(islands[21].name, MAX_STRING_LENGTH, "Corsair Bastion");
    snprintf(islands[21].description, MAX_STRING_LENGTH, "Pirate stronghold, ceaseless raids, enslaved shores, echoes of lawlessness");
    islands[21].treasure_available = 10;
    islands[21].max_treasure = 10;
    islands[21].food_available = 5;
    islands[21].max_food = 5;
    islands[21].cannonballs_available = 20;
    islands[21].max_cannonballs = 20;
    islands[21].rum_available = 5;
    islands[21].max_rum = 5;
    islands[21].is_island_hostile = true;
    islands[21].is_looted = false;


    // Add more hostile islands as needed...

    // Sapphire Shores
    // Serenity Bay
    // Tranquil Haven
    // Coral Cove
    // Paradise Isle
    // Harmony Atoll
    // Gentle Breeze Retreat
    // Azure Lagoon
    // Whispering Pines Peninsula
    // Crystal Waters Haven
    // Rainbow Reef
    // Starlight Sands
    // Silver Moon Harbor
}

int findNewIslandIndex(int current_island, int num_islands) {
    int new_island_index;
    do {
        new_island_index = rand() % num_islands;
    } while (new_island_index == current_island);
    return new_island_index;
}

int getTotalThievery(Ship myShip, int number_of_alive_pirates) {
    int total_crew_thievery = 0;
    for (int i = 0; i < number_of_alive_pirates; i++) {
        total_crew_thievery += myShip.crew[i].attributes.thievery;
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

float getRandomFloat(void) {
    return rand() / (float)RAND_MAX;
}

int main() {
    system("mode con: cols=300 lines=80");

    srand((unsigned int)time(NULL));

    char last_decision;

    do {
        int difficultyChoice;

        float loot_factor_forgiveness;

        char pirate_name[MAX_PIRATE_NAME_LENGTH];

        Island islands[NUMBER_OF_ISLANDS];
        initializeIslands(islands, NUMBER_OF_ISLANDS);

        // Randomly select a non-hostile starting island
        int current_island_index;
        do {
            current_island_index = rand() % NUMBER_OF_ISLANDS;
        } while (islands[current_island_index].is_island_hostile);

        // printf("You start on the island of %s.\n", islands[current_island_index].name);
        // printf("Description: %s\n", islands[current_island_index].description);
        // printf("Index: %d\n", current_island_index);

        Ship myShip;
        myShip.health = 100;
        myShip.distance = 0;
        myShip.is_at_sea = false;

        int number_of_alive_pirates = NUMBER_OF_PIRATES;

        int continue_from_while = 1;
        int port_choice;
        int distrance_traveled;

        int hostile_port_choice;

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
                    loot_factor_forgiveness = 0.4;
                    break;
                } else if (difficultyChoice == 2) {
                    difficulty = NORMAL;
                    myShip.cannonballs = 10;
                    myShip.treasure = 10;
                    myShip.food = 24;
                    myShip.rum = 20;
                    loot_factor_forgiveness = 0.2;
                    break;
                } else if (difficultyChoice == 3) {
                    difficulty = HARD;
                    myShip.cannonballs = 4;
                    myShip.treasure = 0;
                    myShip.food = 12;
                    myShip.rum = 10;
                    loot_factor_forgiveness = 0.1;
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

        // Inside the loop where you create pirates
        for (int i = 0; i < NUMBER_OF_PIRATES; i++) {
            Attributes baseAttributes = getBasePirateAttributes(difficulty);
            // Other attributes initialization...
            myShip.crew[i].attributes = baseAttributes;
            myShip.crew[i].health = 100;
            myShip.crew[i].morale = 100;
            myShip.crew[i].experience = 0;

            printf("Pirate %d Attributes:\n", i + 1);
            printf("Thievery: %d\n", myShip.crew[i].attributes.thievery);
            printf("Charisma: %d\n", myShip.crew[i].attributes.charisma);
            printf("Seamanship: %d\n", myShip.crew[i].attributes.seamanship);
            printf("Medicine: %d\n", myShip.crew[i].attributes.medicine);
            printf("Instinct: %d\n", myShip.crew[i].attributes.instinct);
            printf("Leadership: %d\n", myShip.crew[i].attributes.leadership);
            printf("Carpentry: %d\n", myShip.crew[i].attributes.carpentry);
            printf("Health: %d\n", myShip.crew[i].health);
            printf("Morale: %d\n", myShip.crew[i].morale);
            printf("Experience: %d\n", myShip.crew[i].experience);
            printf("\n");
        }

        // game loop
        while (myShip.health > 0 && number_of_alive_pirates > 0) {
            // 1 Update game state and perform game logic here --------------------------

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

                    // int total_crew_thievery = getTotalThievery(myShip, number_of_alive_pirates);
                    // int total_crew_charisma = getTotalCharisma(myShip, number_of_alive_pirates);
                    // int total_crew_seamanship = getTotalSeamanship(myShip, number_of_alive_pirates);
                    // int total_crew_medicine = getTotalMedicine(myShip, number_of_alive_pirates);
                    // int total_crew_instinct = getTotalInstinct(myShip, number_of_alive_pirates);
                    // int total_crew_leadership = getTotalLeadership(myShip, number_of_alive_pirates);
                    // int total_crew_carpentry = getTotalCarpentry(myShip, number_of_alive_pirates);

                    // printf("Total thievery across all living crew members: %d\n", total_crew_thievery);
                    // printf("Total charisma across all living crew members: %d\n", total_crew_charisma);
                    // printf("Total seamanship across all living crew members: %d\n", total_crew_seamanship);
                    // printf("Total medicine across all living crew members: %d\n", total_crew_medicine);
                    // printf("Total instinct across all living crew members: %d\n", total_crew_instinct);
                    // printf("Total leadership across all living crew members: %d\n", total_crew_leadership);
                    // printf("Total carpentry across all living crew members: %d\n", total_crew_carpentry);
                }
            }

            // Calculate pirate attributes
            int total_crew_thievery = getTotalThievery(myShip, number_of_alive_pirates);
            int total_crew_charisma = getTotalCharisma(myShip, number_of_alive_pirates);
            int total_crew_seamanship = getTotalSeamanship(myShip, number_of_alive_pirates);
            int total_crew_medicine = getTotalMedicine(myShip, number_of_alive_pirates);
            int total_crew_instinct = getTotalInstinct(myShip, number_of_alive_pirates);
            int total_crew_leadership = getTotalLeadership(myShip, number_of_alive_pirates);
            int total_crew_carpentry = getTotalCarpentry(myShip, number_of_alive_pirates);

            // 2. Print Current Game State --------------------------

            //printf("Ship Health: %d\n", myShip.health);

            // for (int i = 0; i < number_of_alive_pirates; i++) {
            //     printf("%s, hp: %d \n", myShip.crew[i].name, myShip.crew[i].health);
            // }

            // 3. Dialog and Chat Options ------------------------------
            if (!myShip.is_at_sea && !islands[current_island_index].is_island_hostile) {
                while (continue_from_while) {
                    printf("You're at the port of %s. What would you like to do? \n", islands[current_island_index].name);
                    printf("1. Explore the seas for treasure. \n"); // If food reaches 0, there will be a percent chance that each crew member will die
                    printf("2. Rest for the day. \n"); // Low chance for a crew member to go awol?
                    printf("3. Scour the island for riches. \n"); // Chance to lose or find new mates; 
                    printf("4. Hit the pub with your mates. \n"); // Raises moral but has a chance for one of your mates to get in a fight and injured. Maybe a chance to recruit a new mate for the price of some treasure. Consumes food, rum, and treasure?
                    printf("5. Trade with the locals. \n"); // chance to buy a treasure map

                    if (scanf(" %d", &port_choice) != 1) {
                        printf("Invalid input. Please enter an integer. \n");

                        while (getchar() != '\n');
                    } else {
                        switch (port_choice) {
                            case 1:
                                printf("You set sail in hopes to find some treasure. \n");
                                distrance_traveled = 8 + rand() % 63; // 8 to 70
                                myShip.distance += distrance_traveled;
                                if (myShip.distance >= 50 + rand() % 21) { // 50 to 70
                                    int new_island_index = findNewIslandIndex(current_island_index, NUMBER_OF_ISLANDS);

                                    current_island_index = new_island_index;

                                    printf("You arrived at an island! \n", islands[current_island_index].name);
                                    myShip.distance = 0;
                                    myShip.is_at_sea = false;
                                } else {
                                    printf("You traveled %d nautical miles. \n", distrance_traveled);
                                    myShip.is_at_sea = true;
                                }
                                continue_from_while = 0;
                                break;
                            case 2:
                                printf("Continue: \n");
                                continue_from_while = 0;
                                break;
                            case 3:
                                if (!islands[current_island_index].is_looted) {
                                    float loot_factor = getRandomFloat();  // Random factor between 0 and 1
                                    float max_loot = MAX_LOOT * (loot_factor + loot_factor_forgiveness);

                                    // type cast to convert from float to int (explict)
                                    int loot_amount = (int)(total_crew_thievery * loot_factor);
                                    loot_amount = (loot_amount > max_loot) ? max_loot : loot_amount;

                                    // Apply the loot to the island
                                    islands[current_island_index].treasure_available -= loot_amount;
                                    if (islands[current_island_index].treasure_available < 0) {
                                        islands[current_island_index].treasure_available = 0;
                                    }

                                    // Give loot to ship
                                    myShip.treasure += loot_amount;

                                    // Calculate if mates get injured in the process maybe 20% chance per mate?

                                    // mates gain xp based on loot_amount if they weren't injured

                                    printf("%d treasure gained. You now have %d treasure \n", loot_amount, myShip.treasure);
                                    sleep(1);

                                    // Mark the island as looted
                                    islands[current_island_index].is_looted = true;
                                    continue_from_while = 0;
                                } else {
                                    printf("%s has been looted recently. \n", islands[current_island_index].name);
                                    sleep(1);
                                }
                                break;
                            case 4:
                                printf(" \n");
                                break;
                            case 5:
                                printf(" \n");
                                break;
                            default:
                                printf("Enter an interger between 1 and 5. \n");
                                break;
                        }
                    }
                }
            }
            continue_from_while = 1;

            if (!myShip.is_at_sea && islands[current_island_index].is_island_hostile) {
                while (continue_from_while) {
                    printf("You're at the port of %s. You hear rumors that this island is not so friendly. What would you like to do next? \n", islands[current_island_index].name);
                    printf("1: Raid the island \n");
                    if (scanf(" %d", &hostile_port_choice) != 1) {
                        printf("Invalid input. Please enter an integer. \n");

                        while (getchar() != '\n');
                    } else {
                        switch (hostile_port_choice) {
                            case 1:
                                printf("1 \n");
                                break;
                            case 2:
                                printf("2 \n");
                                break;
                            case 3:
                                printf("3 \n");
                                break;
                            case 4:
                                printf("4 \n");
                                break;
                            case 5:
                                printf("5 \n");
                                break;
                            default:
                                printf("Enter an interger between 1 and 5. \n");
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
                    // printf("Resources on looted island: Treasure: %d, Food: %d, Cannonballs: %d, Rum: %d  \n", islands[i].treasure_available, islands[i].food_available, islands[i].cannonballs_available, islands[i].rum_available);
                }
            }


            //usleep(100000);  // Sleep for 0.1 seconds (100,000 microseconds)
        }

        if (myShip.health <= 0) {
            printf("Game over. Your ship was destroyed. \n");
        }

        if (number_of_alive_pirates == 0) {
            printf("Game over. All of your mates died. \n");
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