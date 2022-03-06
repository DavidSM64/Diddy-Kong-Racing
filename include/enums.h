#ifndef ENUMS_H
#define ENUMS_H

/* All enums that are exposed to assets should be placed in this file */

#ifdef DKR_ASSETS_TOOL
#define DEFINE_ENUM(NAME, ...) \
    out[#NAME] = new_enum(#__VA_ARGS__);
#else
#define DEFINE_ENUM(NAME, ...) \
    typedef enum NAME { \
        __VA_ARGS__ \
    } NAME;
#endif
   
#ifdef DKR_ASSETS_TOOL
// This is C++ code that belongs to dkr_assets_tool, not the game itself.
#include <map>
#include <regex>
inline std::map<std::string, int> new_enum(std::string values) {
    std::map<std::string, int> enumMap;
    // Regex only accepts positive/negative decimal/hexadecimal enum values.
    std::regex regex("([0-9A-Za-z_]+)\\s*(=\\s*([-]?(?:0x[0-9A-Fa-f]+|[0-9]+)))?");
    std::smatch sm;
    int nextValue = 0; // Enums default to starting at 0.
    while (regex_search(values, sm, regex)) {
        if(sm[3].length() > 0) // Assignment found in enum value, so replace nextValue.
            nextValue = std::stoi(sm[3], 0, 0);
        enumMap[sm[1]] = nextValue++;
        values = sm.suffix(); // Move to the next match
    }
    return enumMap;
}
inline std::map<std::string, std::map<std::string, int>> get_enums() {
std::map<std::string, std::map<std::string, int>> out;
#endif

/* -------------------------------------- Define all the enums here! -------------------------------------- */

// Note: All enums should only have a single literal value. This makes processing in the assets tool easier.
// This does mean you cannot use bitwise operations or other enum values. Sorry about that!

DEFINE_ENUM (
    Vehicle, 
        VEHICLE_CAR, 
        VEHICLE_HOVERCRAFT, 
        VEHICLE_PLANE,
)

DEFINE_ENUM (
    Language, 
        LANGUAGE_ENGLISH, 
        LANGUAGE_GERMAN, 
        LANGUAGE_FRENCH, 
        LANGUAGE_JAPANESE,
)

DEFINE_ENUM (
    World, 
        WORLD_NONE = -1, // This enum starts at -1 instead of 0.
        WORLD_CENTRAL_AREA, 
        WORLD_DINO_DOMAIN, 
        WORLD_SHERBET_ISLAND, 
        WORLD_SNOWFLAKE_MOUNTAIN, 
        WORLD_DRAGON_FOREST, 
        WORLD_FUTURE_FUN_LAND,
)

DEFINE_ENUM (
    RaceType, 
        RACETYPE_DEFAULT           =  0,
        RACETYPE_HORSESHOE_GULCH   =  3, 
        RACETYPE_HUBWORLD          =  5, 
        RACETYPE_CUTSCENE_1        =  6, // Not sure what the difference between these two are.
        RACETYPE_CUTSCENE_2        =  7, 
        RACETYPE_BOSS              =  8, 
        RACETYPE_CHALLENGE_BATTLE  = 64, 
        RACETYPE_CHALLENGE_BANANAS = 65, 
        RACETYPE_CHALLENGE_EGGS    = 66,
)

/* -------------------------------------------------------------------------------------------------------- */

#ifdef DKR_ASSETS_TOOL
return out;
}
#endif

#endif
