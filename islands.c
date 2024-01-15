#include "islands.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initializeIslands(Island islands[], int numIslands) {          // function that TAKES island array and numIslands to
    // Non-hostile islands
    snprintf(islands[0].name, MAX_STRING_LENGTH, "Tortuga");
    snprintf(islands[0].description, MAX_STRING_LENGTH, "A lively pirate haven. Starting isle.");
    islands[0].dubloon_available = 4 + rand() % 6; // 4 is lowest, 6 subtracted by 1 + add 4 together will be highest 4-9 CHECK
    islands[0].max_dubloon = islands[0].dubloon_available;
    islands[0].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[0].max_treasure = islands[0].treasure_available;
    islands[0].food_available = 3 + rand() % 5; // 3 to 7 CHECK
    islands[0].max_food = islands[0].food_available;
    islands[0].cannonballs_available = 3 + rand() % 5; // 3 to 7
    islands[0].max_cannonballs = islands[0].cannonballs_available;
    islands[0].rum_available = 4 + rand() % 3; // 4 to 6
    islands[0].max_rum = islands[0].rum_available;
    islands[0].is_island_hostile = false;
    islands[0].is_looted = false;
    islands[0].is_stronghold = false;

    snprintf(islands[1].name, MAX_STRING_LENGTH, "Crimson Cove");
    snprintf(islands[1].description, MAX_STRING_LENGTH, "Known for its vibrant red coral reefs");
    islands[1].dubloon_available = 3 + rand() % 7; // 3 - 9 CHECK
    islands[1].max_dubloon = islands[1].dubloon_available;
    islands[1].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[1].max_treasure = islands[1].treasure_available;
    islands[1].food_available = 4 + rand() % 6; // 4 to 9 CHECK
    islands[1].max_food = islands[1].food_available;
    islands[1].cannonballs_available = 3 + rand() % 7; // 3 to 9
    islands[1].max_cannonballs = islands[1].cannonballs_available;
    islands[1].rum_available = 4 + rand() % 6; // 4 to 9
    islands[1].max_rum = islands[1].rum_available;
    islands[1].is_island_hostile = false;
    islands[1].is_looted = false;
    islands[1].is_stronghold = false;

    snprintf(islands[2].name, MAX_STRING_LENGTH, "Sainte-Maria");
    snprintf(islands[2].description, MAX_STRING_LENGTH, "A place where pirates reside.");
    islands[2].dubloon_available = 4 + rand() % 4; // 4 to 7 CHECK
    islands[2].max_dubloon = islands[2].dubloon_available;
    islands[2].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[2].max_treasure = islands[2].treasure_available;
    islands[2].food_available = 2 + rand() % 3; // 2 to 4 CHECK
    islands[2].max_food = islands[2].food_available;
    islands[2].cannonballs_available = 3 + rand() % 5; // 3 to 7
    islands[2].max_cannonballs = islands[2].cannonballs_available;
    islands[2].rum_available = 4 + rand() % 3; // 4 to 6
    islands[2].max_rum = islands[2].rum_available;
    islands[2].is_island_hostile = false;
    islands[2].is_looted = false;
    islands[2].is_stronghold = false;

    snprintf(islands[3].name, MAX_STRING_LENGTH, "Emerald Isle");
    snprintf(islands[3].description, MAX_STRING_LENGTH, "Rumored to have mystical emerald artifacts");
    islands[3].dubloon_available = 2 + rand() % 11; // 2-12 because it has emeralds CHECK
    islands[3].max_dubloon = islands[3].dubloon_available;
    islands[3].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[3].max_treasure = islands[3].treasure_available;
    islands[3].food_available = 2 + rand() % 5; // 2 to 6; counter because it has more treasure CHECK
    islands[3].max_food = islands[3].food_available;
    islands[3].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[3].max_cannonballs = islands[3].cannonballs_available;
    islands[3].rum_available = 4 + rand() % 7; // 4 to 10
    islands[3].max_rum = islands[3].rum_available;
    islands[3].is_island_hostile = false;
    islands[3].is_looted = false;
    islands[3].is_stronghold = false;

    snprintf(islands[4].name, MAX_STRING_LENGTH, "Gold Rush Atoll");
    snprintf(islands[4].description, MAX_STRING_LENGTH, "Once the sight of a legendary gold rush");
    islands[4].dubloon_available = 5 + rand() % 4; // 5 to 8 CHECK
    islands[4].max_dubloon = islands[4].dubloon_available;
    islands[4].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[4].max_treasure = islands[4].treasure_available;
    islands[4].food_available = 4 + rand() % 9; // 4 to 11; CHECK
    islands[4].max_food = islands[4].food_available;
    islands[4].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[4].max_cannonballs = islands[4].cannonballs_available;
    islands[4].rum_available = 4 + rand() % 7; // 4 to 10
    islands[4].max_rum = islands[4].rum_available;
    islands[4].is_island_hostile = false;
    islands[4].is_looted = false;
    islands[4].is_stronghold = false;

    snprintf(islands[5].name, MAX_STRING_LENGTH, "Whispering Sands");
    snprintf(islands[5].description, MAX_STRING_LENGTH, "Desert Island with secrets carried by the wind");
    islands[5].dubloon_available = 4 + rand() % 3; // 4 to 6 CHECK
    islands[5].max_dubloon = islands[5].dubloon_available;
    islands[5].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[5].max_treasure = islands[5].treasure_available;
    islands[5].food_available = 3 + rand() % 4; // 3 to 6 CHECK
    islands[5].max_food = islands[5].food_available;
    islands[5].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[5].max_cannonballs = islands[5].cannonballs_available;
    islands[5].rum_available = 4 + rand() % 7; // 4 to 10
    islands[5].max_rum = islands[5].rum_available;
    islands[5].is_island_hostile = false;
    islands[5].is_looted = false;
    islands[5].is_stronghold = false;

    snprintf(islands[6].name, MAX_STRING_LENGTH, "Admiral's Archipelago");
    snprintf(islands[6].description, MAX_STRING_LENGTH, "Enclave for Pirates of the highest status");
    islands[6].dubloon_available = 5 + rand() % 6; // 5 to 10 CHECK
    islands[6].max_dubloon = islands[6].dubloon_available;
    islands[6].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[6].max_treasure = islands[6].treasure_available;
    islands[6].food_available = 2 + rand() % 7; // 2 to 8 CHECK
    islands[6].max_food = islands[6].food_available;
    islands[6].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[6].max_cannonballs = islands[6].cannonballs_available;
    islands[6].rum_available = 4 + rand() % 7; // 4 to 10
    islands[6].max_rum = islands[6].rum_available;
    islands[6].is_island_hostile = false;
    islands[6].is_looted = false;
    islands[6].is_stronghold = false;

    snprintf(islands[7].name, MAX_STRING_LENGTH, "Port Royal Haven");
    snprintf(islands[7].description, MAX_STRING_LENGTH, "Shrouded in mystery under the moonlight");
    islands[7].dubloon_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[7].max_dubloon = islands[7].dubloon_available;
    islands[7].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[7].max_treasure = islands[7].treasure_available;
    islands[7].food_available = 4 + rand() % 4; // 4 to 7 CHECK
    islands[7].max_food = islands[7].food_available;
    islands[7].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[7].max_cannonballs = islands[7].cannonballs_available;
    islands[7].rum_available = 4 + rand() % 7; // 4 to 10
    islands[7].max_rum = islands[7].rum_available;
    islands[7].is_island_hostile = false;
    islands[7].is_looted = false;
    islands[7].is_stronghold = false;

    snprintf(islands[8].name, MAX_STRING_LENGTH, "Nassau Harbor");
    snprintf(islands[8].description, MAX_STRING_LENGTH, "Freedom port, pirate democracy, vibrant nightlife, notorious captains thrive");
    islands[8].dubloon_available = 3 + rand() % 3; // 3 to 5 CHECK
    islands[8].max_dubloon = islands[8].dubloon_available;
    islands[8].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[8].max_treasure = islands[8].treasure_available;
    islands[8].food_available = 5 + rand() % 4; // 5 to 8 CHECK
    islands[8].max_food = islands[8].food_available;
    islands[8].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[8].max_cannonballs = islands[8].cannonballs_available;
    islands[8].rum_available = 4 + rand() % 7; // 4 to 10
    islands[8].max_rum = islands[8].rum_available;
    islands[8].is_island_hostile = false;
    islands[8].is_looted = false;
    islands[8].is_stronghold = false;

    snprintf(islands[9].name, MAX_STRING_LENGTH, "Buccaneers Refuge");
    snprintf(islands[9].description, MAX_STRING_LENGTH, "Sanctuary for outcasts, camaraderie, shared spoils, legendary pirate lore");
    islands[9].dubloon_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[9].max_dubloon = islands[9].dubloon_available;
    islands[9].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[9].max_treasure = islands[9].treasure_available;
    islands[9].food_available = 5 + rand() % 3; // 5 to 7 CHECK
    islands[9].max_food = islands[9].food_available;
    islands[9].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[9].max_cannonballs = islands[9].cannonballs_available;
    islands[9].rum_available = 4 + rand() % 7; // 4 to 10
    islands[9].max_rum = islands[9].rum_available;
    islands[9].is_island_hostile = false;
    islands[9].is_looted = false;
    islands[9].is_stronghold = false;

    snprintf(islands[10].name, MAX_STRING_LENGTH, "Gold Coast Retreat");
    snprintf(islands[10].description, MAX_STRING_LENGTH, "Opulent haven, lavish lifestyles, treacherous alliances, high-stakes intrigues unfold.");
    islands[10].dubloon_available = 2 + rand() % 3; // 2 to 4 CHECK
    islands[10].max_dubloon = islands[10].dubloon_available;
    islands[10].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[10].max_treasure = islands[10].treasure_available;
    islands[10].food_available = 2 + rand() % 7; // 2 to 8 CHECK
    islands[10].max_food = islands[10].food_available;
    islands[10].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[10].max_cannonballs = islands[10].cannonballs_available;
    islands[10].rum_available = 4 + rand() % 7; // 4 to 10
    islands[10].max_rum = islands[10].rum_available;
    islands[10].is_island_hostile = false;
    islands[10].is_looted = false;
    islands[10].is_stronghold = false;


    // Add more non-hostile islands as needed...

    // Hostile islands
    snprintf(islands[11].name, MAX_STRING_LENGTH, "Isla de Muerta");
    snprintf(islands[11].description, MAX_STRING_LENGTH, "A mysterious and dangerous island.");
    islands[11].dubloon_available = 2 + rand() % 5; // 2 to 6 CHECK
    islands[11].max_dubloon = islands[11].dubloon_available;
    islands[11].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[11].max_treasure = islands[11].treasure_available;
    islands[11].food_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[11].max_food = islands[11].food_available;
    islands[11].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[11].max_cannonballs = islands[11].cannonballs_available;
    islands[11].rum_available = 4 + rand() % 7; // 4 to 10
    islands[11].max_rum = islands[11].rum_available;
    islands[11].is_island_hostile = true;
    islands[11].is_looted = false;
    islands[11].is_stronghold = false;

    snprintf(islands[12].name, MAX_STRING_LENGTH, "Skullcap Atoll");
    snprintf(islands[12].description, MAX_STRING_LENGTH, "Dreaded prison, pirate executions, haunted waters, cursed shores beckon danger");
    islands[12].dubloon_available = 8 + rand() % 3; // 8 to 10 CHECK
    islands[12].max_dubloon = islands[12].dubloon_available;
    islands[12].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[12].max_treasure = islands[12].treasure_available;
    islands[12].food_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[12].max_food = islands[12].food_available;
    islands[12].cannonballs_available = 5 + rand() % 16; // 3 to 10
    islands[12].max_cannonballs = islands[12].cannonballs_available;
    islands[12].rum_available = 3 + rand() % 6; // 4 to 10
    islands[12].max_rum = islands[12].rum_available;
    islands[12].is_island_hostile = true;
    islands[12].is_looted = false;
    islands[12].is_stronghold = false;

    snprintf(islands[13].name, MAX_STRING_LENGTH, "Dead Man's Reef");
    snprintf(islands[13].description, MAX_STRING_LENGTH, "A mysterious and dangerous island, Ship graveyard, treacherous currents, ghostly whispers, cursed maritime history.");
    islands[13].dubloon_available = 2 + rand() % 9; // 2 to 10 CHECK
    islands[13].max_dubloon = islands[13].dubloon_available;
    islands[13].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[13].max_treasure = islands[13].treasure_available;
    islands[13].food_available = 2 + rand() % 5; // 2 to 6; CHECK
    islands[13].max_food = islands[13].food_available;
    islands[13].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[13].max_cannonballs = islands[13].cannonballs_available;
    islands[13].rum_available = 4 + rand() % 7; // 4 to 10
    islands[13].max_rum = islands[13].rum_available;
    islands[13].is_island_hostile = true;
    islands[13].is_looted = false;
    islands[13].is_stronghold = false;

    snprintf(islands[14].name, MAX_STRING_LENGTH, "Noose Point");
    snprintf(islands[14].description, MAX_STRING_LENGTH, "Infamous for executions, pirate justice, a grim place of finality");
    islands[14].dubloon_available = 2 + rand() % 7; // 2 to 8 CHECK
    islands[14].max_dubloon = islands[14].dubloon_available;
    islands[14].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[14].max_treasure = islands[14].treasure_available;
    islands[14].food_available = 3 + rand() % 3; // 3 to 5 CHECK
    islands[14].max_food = islands[14].food_available;
    islands[14].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[14].max_cannonballs = islands[14].cannonballs_available;
    islands[14].rum_available = 4 + rand() % 7; // 4 to 10
    islands[14].max_rum = islands[14].rum_available;
    islands[14].is_island_hostile = true;
    islands[14].is_looted = false;
    islands[14].is_stronghold = false;

    snprintf(islands[15].name, MAX_STRING_LENGTH, "Red Tide Haven");
    snprintf(islands[15].description, MAX_STRING_LENGTH, "Blood-soaked shores, notorious battles, relentless pirates, danger on every wave");
    islands[15].dubloon_available = 2 + rand() % 9; // 2 to 10 CHECK
    islands[15].max_dubloon = islands[15].dubloon_available;
    islands[15].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[15].max_treasure = islands[15].treasure_available;
    islands[15].food_available = 2 + rand() % 5; // 2 to 6; CHECK
    islands[15].max_food = islands[15].food_available;
    islands[15].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[15].max_cannonballs = islands[15].cannonballs_available;
    islands[15].rum_available = 4 + rand() % 7; // 4 to 10
    islands[15].max_rum = islands[15].rum_available;
    islands[15].is_island_hostile = true;
    islands[15].is_looted = false;
    islands[15].is_stronghold = false;

    snprintf(islands[16].name, MAX_STRING_LENGTH, "Calico's Cursed Island");
    snprintf(islands[16].description, MAX_STRING_LENGTH, "Infested by pirate outcasts, betrayal, buried grudges, an island of strife");
    islands[16].dubloon_available = 2 + rand() % 6; // 2 to 7 CHECK
    islands[16].max_dubloon = islands[16].dubloon_available;
    islands[16].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[16].max_treasure = islands[16].treasure_available;
    islands[16].food_available = 2 + rand() % 3; // 2 to 4 CHECK
    islands[16].max_food = islands[16].food_available;
    islands[16].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[16].max_cannonballs = islands[16].cannonballs_available;
    islands[16].rum_available = 4 + rand() % 7; // 4 to 10
    islands[16].max_rum = islands[16].rum_available;
    islands[16].is_island_hostile = true;
    islands[16].is_looted = false;
    islands[16].is_stronghold = false;

    snprintf(islands[17].name, MAX_STRING_LENGTH, "Porto Desperation Isle");
    snprintf(islands[17].description, MAX_STRING_LENGTH, "Exile's refuge, banished pirates, desperate actions, a last resort");
    islands[17].dubloon_available = 3 + rand() % 9; // 3- 11  CHECK
    islands[17].max_dubloon = islands[17].dubloon_available;
    islands[17].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[17].max_treasure = islands[17].treasure_available;
    islands[17].food_available = 2 + rand() % 4; // 2 to 5 CHECK
    islands[17].max_food = islands[17].food_available;
    islands[17].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[17].max_cannonballs = islands[17].cannonballs_available;
    islands[17].rum_available = 4 + rand() % 7; // 4 to 10
    islands[17].max_rum = islands[17].rum_available;
    islands[17].is_island_hostile = true;
    islands[17].is_looted = false;
    islands[17].is_stronghold = false;

    snprintf(islands[18].name, MAX_STRING_LENGTH, "Tunis");
    snprintf(islands[18].description, MAX_STRING_LENGTH, "Desolate marsh isle, treacherous betrayal, festering vendettas, a realm gripped by strife");
    islands[18].dubloon_available = 4 + rand() % 6; // 4 to 9    CHECK
    islands[18].max_dubloon = islands[18].dubloon_available;
    islands[18].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[18].max_treasure = islands[18].treasure_available;
    islands[18].food_available = 2 + rand() % 5; // 2 to 6; CHECK
    islands[18].max_food = islands[18].food_available;
    islands[18].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[18].max_cannonballs = islands[18].cannonballs_available;
    islands[18].rum_available = 4 + rand() % 7; // 4 to 10
    islands[18].max_rum = islands[18].rum_available;
    islands[18].is_island_hostile = true;
    islands[18].is_looted = false;
    islands[18].is_stronghold = false;

    snprintf(islands[19].name, MAX_STRING_LENGTH, "Barataria Bay");
    snprintf(islands[19].description, MAX_STRING_LENGTH, "Treacherous stronghold, pirate vendettas,");
    islands[19].dubloon_available = 2 + rand() % 7; // 2 to 8      CHECK
    islands[19].max_dubloon = islands[19].dubloon_available;
    islands[19].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[19].max_treasure = islands[19].treasure_available;
    islands[19].food_available = 2 + rand() % 7; // 2 to 8 CHECK
    islands[19].max_food = islands[19].food_available;
    islands[19].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[19].max_cannonballs = islands[19].cannonballs_available;
    islands[19].rum_available = 4 + rand() % 7; // 4 to 10
    islands[19].max_rum = islands[19].rum_available;
    islands[19].is_island_hostile = true;
    islands[19].is_looted = false;
    islands[19].is_stronghold = false;

    snprintf(islands[20].name, MAX_STRING_LENGTH, "Blackbeard's Abyss Isle");
    snprintf(islands[20].description, MAX_STRING_LENGTH, "Shrouded cove, ominous legends, a feared and shadowed retreat");
    islands[20].dubloon_available = 3 + rand() % 6; // 3 to 8          CHECK
    islands[20].max_dubloon = islands[20].dubloon_available;
    islands[20].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[20].max_treasure = islands[20].treasure_available;
    islands[20].food_available = 3 + rand() % 2; // 3 to 4 CHECK
    islands[20].max_food = islands[20].food_available;
    islands[20].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[20].max_cannonballs = islands[20].cannonballs_available;
    islands[20].rum_available = 4 + rand() % 7; // 4 to 10
    islands[20].max_rum = islands[20].rum_available;
    islands[20].is_island_hostile = true;
    islands[20].is_looted = false;
    islands[20].is_stronghold = false;

    snprintf(islands[21].name, MAX_STRING_LENGTH, "Corsair Bastion");
    snprintf(islands[21].description, MAX_STRING_LENGTH, "Pirate stronghold, ceaseless raids, enslaved shores, echoes of lawlessness");
    islands[21].dubloon_available = 4 + rand() % 7; // 4 to 10         CHECK
    islands[21].max_dubloon = islands[21].dubloon_available;
    islands[21].treasure_available = 2 + rand() % 2; // 2 to 3 CHECK
    islands[21].max_treasure = islands[21].treasure_available;
    islands[21].food_available = 3 + rand() % 8; // 3 to 10
    islands[21].max_food = islands[21].food_available;
    islands[21].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[21].max_cannonballs = islands[21].cannonballs_available;
    islands[21].rum_available = 4 + rand() % 7; // 4 to 10
    islands[21].max_rum = islands[21].rum_available;
    islands[21].is_island_hostile = true;
    islands[21].is_looted = false;
    islands[21].is_stronghold = false;

    //Strongholds

    snprintf(islands[22].name, MAX_STRING_LENGTH, "Steves Hole");
    snprintf(islands[22].description, MAX_STRING_LENGTH, "A deep damp murky hole");
    islands[22].dubloon_available = 4 + rand() % 7; // 4 to 10         CHECK
    islands[22].max_dubloon = islands[22].dubloon_available;
    islands[22].food_available = 3 + rand() % 8; // 3 to 10
    islands[22].max_food = islands[22].food_available;
    islands[22].cannonballs_available = 3 + rand() % 8; // 3 to 10
    islands[22].max_cannonballs = islands[22].cannonballs_available;
    islands[22].rum_available = 4 + rand() % 7; // 4 to 10
    islands[22].max_rum = islands[22].rum_available;
    islands[22].is_island_hostile = true;
    islands[22].is_looted = false;
    islands[22].is_stronghold = true;

}


// non-hostile -
// less chance and range of treasure,
// greater chance and range of food
// less chance and range of booze
// greater chance of cannonballs availabale

// add new variable and strongohlds boolean


// hostile -    i want shit u can only acquire on hostile islands, need a notes file also, save system, possibly designate certain hostile islands as strongholds which have greater chance of cannonballs
// greater chance and range of treasure,
// less chance and range of food
//