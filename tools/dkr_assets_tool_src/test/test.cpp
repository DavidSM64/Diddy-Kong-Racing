#include "test.h"

#include <string>
#include <vector>

#include "helpers/regexHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/fileHelper.h"

#include "helpers/c/cStructHelper.h"
#include "helpers/c/cContext.h"

#include "misc/globalSettings.h"

using namespace DkrAssetsTool;

void test_string_helper() {
    DebugHelper::DebugTimer timer;
    
    std::string testString = "Hello World!";
    
    StringHelper::make_uppercase(testString);
    DebugHelper::assert(testString == "HELLO WORLD!", "(String Helper) Uppercase Test: Failed");
    StringHelper::make_lowercase(testString);
    DebugHelper::assert(testString == "hello world!", "(String Helper) Lowercase Test: Failed");
    
    const std::string trimTestString = "  Foo    ";
    
    testString = trimTestString;
    StringHelper::rtrim(testString);
    DebugHelper::assert(testString == "  Foo", "(String Helper) Right Trim Test: Failed");
    testString = trimTestString;
    StringHelper::ltrim(testString);
    DebugHelper::assert(testString == "Foo    ", "(String Helper) Left Trim Test: Failed");
    testString = trimTestString;
    StringHelper::trim(testString);
    DebugHelper::assert(testString == "Foo", "(String Helper) Trim Test: Failed");
    
    const std::string splitStringInput = "  **x[2],*y  ,  z[3]  ";
    
    testString = splitStringInput;
    std::vector<std::string> testStringSplitted;
    
    StringHelper::split(testString, ',', testStringSplitted);
    
    DebugHelper::assert(testString == splitStringInput, "(String Helper) Split Test: input was modified.");
    DebugHelper::assert(testStringSplitted.size() == 3, "(String Helper) Split Test: size incorrect");
    DebugHelper::assert(testStringSplitted[0] == "  **x[2]", "(String Helper) Split Test: Failed (index 0)");
    DebugHelper::assert(testStringSplitted[1] == "*y  ", "(String Helper) Split Test: Failed (index 1)");
    DebugHelper::assert(testStringSplitted[2] == "  z[3]  ", "(String Helper) Split Test: Failed (index 2)");
    
    testStringSplitted.clear();
    
    StringHelper::split_and_trim(testString, ',', testStringSplitted);
    
    DebugHelper::assert(testString == splitStringInput, "(String Helper) Split & Trim Test: input was modified.");
    DebugHelper::assert(testStringSplitted.size() == 3, "(String Helper) Split & Trim Test: size incorrect");
    DebugHelper::assert(testStringSplitted[0] == "**x[2]", "(String Helper) Splitt & Trim Test: Failed (index 0)");
    DebugHelper::assert(testStringSplitted[1] == "*y", "(String Helper) Splitt & Trim Test: Failed (index 1)");
    DebugHelper::assert(testStringSplitted[2] == "z[3]", "(String Helper) Splitt & Trim Test: Failed (index 2)");
    
    DebugHelper::info(GREEN_TEXT, "String Helper passed all tests!", RESET_TEXT, " Took ", timer.elapsed());
}

void test_regex_engine_match(int testMajor, int testMinor, RegexMatchGroup &group, std::string expectedText, int expectedOffset) {
    std::string groupText = group.get_text();
    int groupOffset = group.get_offset();
    DebugHelper::assert(groupText == expectedText, 
        "(Regex Helper) ", testMajor, ",", testMinor, " Test Failed!\nText did not match!\n",
        "text     = \"", groupText, "\"\n",
        "expected = \"", expectedText, "\"");
    DebugHelper::assert(groupOffset == expectedOffset, 
        "(Regex Helper) ", testMajor, ",", testMinor, " Test Failed!\nOffset did not match!\n",
        "offset   = ", groupOffset, "\n",
        "expected = ", expectedOffset);
}

// Make sure RegexHelper::get_matches works.
void test_regex_engine_part1() {
    std::string testString = R"(
u8    pad[5]   ;   
s32    radius;
// Activation radius.
float        angleY;
u8 pad2   [5][4][2]   ;
u8 *********superPointer;
)";

    std::string testRegex = R"(([A-Za-z_][A-Za-z0-9_]*)\s*([*]+)?\s*([A-Za-z_][A-Za-z0-9_]*)\s*(\[.*\])?\s*;)";
    
    std::vector<RegexMatch> matches;
    RegexHelper::get_matches(testString, testRegex, matches);
    
    
    DebugHelper::assert(matches.size() == 5, 
        "(Regex Helper) Number of matches is not 5; got ", matches.size(), " matches instead!");
    
    test_regex_engine_match(0, 0, matches[0].get_group(1), "u8", 1);
    test_regex_engine_match(0, 1, matches[0].get_group(2), "", -1);
    test_regex_engine_match(0, 2, matches[0].get_group(3), "pad", 7);
    test_regex_engine_match(0, 3, matches[0].get_group(4), "[5]", 10);
    
    test_regex_engine_match(1, 0, matches[1].get_group(1), "s32", 4);
    test_regex_engine_match(1, 1, matches[1].get_group(2), "", -1);
    test_regex_engine_match(1, 2, matches[1].get_group(3), "radius", 11);
    test_regex_engine_match(1, 3, matches[1].get_group(4), "", -1);
    
    test_regex_engine_match(2, 0, matches[2].get_group(1), "float", 23);
    test_regex_engine_match(2, 1, matches[2].get_group(2), "", -1);
    test_regex_engine_match(2, 2, matches[2].get_group(3), "angleY", 36);
    test_regex_engine_match(2, 3, matches[2].get_group(4), "", -1);
    
    test_regex_engine_match(3, 0, matches[3].get_group(1), "u8", 1);
    test_regex_engine_match(3, 1, matches[3].get_group(2), "", -1);
    test_regex_engine_match(3, 2, matches[3].get_group(3), "pad2", 4);
    test_regex_engine_match(3, 3, matches[3].get_group(4), "[5][4][2]", 11);
    
    test_regex_engine_match(4, 0, matches[4].get_group(1), "u8", 1);
    test_regex_engine_match(4, 1, matches[4].get_group(2), "*********", 4);
    test_regex_engine_match(4, 2, matches[4].get_group(3), "superPointer", 13);
    test_regex_engine_match(4, 3, matches[4].get_group(4), "", -1);
}


// Make sure RegexHelper::get_first_match works.
void test_regex_engine_part2() {
    std::string testString = R"(/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80076BA0 */
)";

    std::string testRegex = R"([\/][*]+[ \t]*RAM_POS:[ \t]*((?:0x)[0-9a-fA-F]+|(?:[Aa][Uu][Tt][Oo]))[ \t]*(?:if[ \t]*([^*]*))?[*][\/])";
    
    RegexMatch *ramPosMatch = RegexHelper::get_first_match(testString, testRegex);

    DebugHelper::assert(ramPosMatch != nullptr, 
        "(Regex Helper) Could not find ramPos in test string!");
    
    test_regex_engine_match(5, 0, ramPosMatch->get_group(1), "0x80076BA0", 91);
}

// Returns true if a member was found.
bool part3_get_next_member(const std::string &inputStr, int &offset, std::string &outStr) {
    const std::string endCharRegex = R"([ \t]+((?:[^;]|[^{])*?([;{])))";
    
    //DebugHelper::info("offset = ", offset);
    
    RegexMatch *match = RegexHelper::get_first_match(inputStr, endCharRegex, offset);
    
    if(match == nullptr) {
        outStr = "<null>";
        return false;
    }
    
    outStr = match->get_group(1).get_text();
    offset += match->get_group(2).get_offset() + 1;
    
    delete match;
    
    return true;
}

void part3_check_member_and_offset(int testMajor, int testMinor, const std::string &memberStr, int nextOffset, 
    std::string expectedMemberStr, int expectedNextOffset) {
        DebugHelper::assert(memberStr == expectedMemberStr, 
        "(Regex Helper) ", testMajor, ",", testMinor, " Test Failed!\nText did not match!\n",
        "text     = \"", memberStr, "\"\n",
        "expected = \"", expectedMemberStr, "\"");
    DebugHelper::assert(nextOffset == expectedNextOffset, 
        "(Regex Helper) ", testMajor, ",", testMinor, " Test Failed!\nOffset did not match!\n",
        "next offset = ", nextOffset, "\n",
        "expected    = ", expectedNextOffset);
}

// Test multiple get_first_match
void test_regex_engine_part3() {
    std::string testString = R"(
            int a0;
            int b0;
            struct {
                int c0;
                int d0;
            };
            u8 pad2   [5][4][2];
            u8 *********superPointer;
    )";

    int curOffset = 0;
    std::string curMember;
    
    part3_get_next_member(testString, curOffset, curMember);
    part3_check_member_and_offset(6, 0, curMember, curOffset, "int a0;", 20);
    part3_get_next_member(testString, curOffset, curMember);
    part3_check_member_and_offset(6, 1, curMember, curOffset, "int b0;", 40);
    part3_get_next_member(testString, curOffset, curMember);
    part3_check_member_and_offset(6, 2, curMember, curOffset, "struct {", 61);
    curOffset = StringHelper::find_closing_brace(testString, curOffset - 1) + 2; // Skip over the inner struct. +2 for the closing brace and semicolon.
    part3_get_next_member(testString, curOffset, curMember);
    part3_check_member_and_offset(6, 3, curMember, curOffset, "u8 pad2   [5][4][2];", 157);
    
}

void test_regex_engine(RegexEngine engine) {
    if(!RegexHelper::set_engine(engine)) {
        DebugHelper::warn("Regex engine ", engine, " is not implemented!");
        return;
    }
    
    std::string regexEngineName = RegexHelper::get_current_engine_name();
    
    DebugHelper::info("Testing regex engine: \"", regexEngineName, "\"");
    
    DebugHelper::DebugTimer timer;
    
    test_regex_engine_part1();
    test_regex_engine_part2();
    test_regex_engine_part3();
    
    DebugHelper::info(GREEN_TEXT, "Regex engine ", regexEngineName, " passed all tests!", RESET_TEXT, " Took ", timer.elapsed());
}

void test_regex_helper() {
    test_regex_engine(RegexEngine::STL);
    test_regex_engine(RegexEngine::PCRE2);
}

void test_cstruct_helper_engine(RegexEngine engine) {
    if(!RegexHelper::set_engine(engine)) {
        DebugHelper::warn("Regex engine ", engine, " is not implemented!");
        return;
    }
    
    std::string regexEngineName = RegexHelper::get_current_engine_name();
    
    DebugHelper::DebugTimer timer;
    
    CContext ctx;
    
    std::string input;
    input = R"(
        struct {
            int a0;
            int b0;
            struct {
                int c0;
                int d0;
            };
        };
    )";
    
    CStruct test0(ctx, input);
    
    DebugHelper::assert(test0.is_trivial(), "Failed test 0.0 (struct was not trivial)");
    DebugHelper::assert(test0.get_byte_size() == 16, "Failed test 0.1 (struct was incorrect size, was ", test0.get_byte_size(), " when it should be 16)");
    DebugHelper::assert(test0.get_entry(0)->name == "a0", "Failed test 0.2 (Invalid name, was ", test0.get_entry(0)->name, " when it should be a0)");
    DebugHelper::assert(test0.get_entry(1)->name == "b0", "Failed test 0.3 (Invalid name, was ", test0.get_entry(1)->name, " when it should be b0)");
    DebugHelper::assert(test0.get_entry(2)->innerStruct->get_entry(0)->name == "c0", "Failed test 0.4 (Invalid name, was ", 
        test0.get_entry(2)->innerStruct->get_entry(0)->name, " when it should be c0)");
    DebugHelper::assert(test0.get_entry(2)->innerStruct->get_entry(1)->name == "d0", "Failed test 0.5 (Invalid name, was ", 
        test0.get_entry(2)->innerStruct->get_entry(1)->name, " when it should be d0)");
    DebugHelper::assert(test0.get_entry(0)->get_offset() == 0, "Failed test 0.6");
    DebugHelper::assert(test0.get_entry(1)->get_offset() == 4, "Failed test 0.7");
    DebugHelper::assert(test0.get_entry(2)->innerStruct->get_entry(0)->get_offset() == 8, "Failed test 0.8");
    
    // Clear structs that were created in the previous test.
    ctx.clear_structs();
    
    input = R"(
        // Size: 8 bytes. Shared across every entry.
        typedef struct LevelObjectEntryCommon {
            u8 objectID; // 9-bit object ID to load (uses size's MSB).
            u8 size; // 7-bit total entry length (MSB is used in object_id).
            s16 x, y, z; // Position in level
        } LevelObjectEntryCommon;
    )";
    CStruct entryCommon(ctx, input);
    
    input = R"(
        typedef struct LevelObjectEntry_Racer {
            /* 0x00 */ LevelObjectEntryCommon common;
            /* 0x08 */ s16 angleZ; Hint((Angle))
            /* 0x0A */ s16 angleX; Hint((   Angle))
            /* 0x0C */ s16 angleY; Hint((  Angle     ))
            /* 0x0E */ s16 playerIndex;
        } LevelObjectEntry_Racer;
    )";
    
    CStruct test1(ctx, input);
    DebugHelper::assert(!test1.is_trivial(), "Failed test 1.0 (struct was trivial)");
    DebugHelper::assert(test1.get_byte_size() == 16, "Failed test 1.1 (struct size incorrect, was ", test1.get_byte_size(), " when it should be 16)");
    DebugHelper::assert(test1.get_entry(1)->get_hint_type() == "Angle", "Failed test 1.2 (Invalid hint type, was \"", test1.get_entry(1)->get_hint_type(), 
        "\" when it should've been \"Angle\")");
    DebugHelper::assert(test1.get_entry(2)->get_hint_type() == "Angle", "Failed test 1.3 (Invalid hint type, was \"", test1.get_entry(2)->get_hint_type(), 
        "\" when it should've been \"Angle\")");
    DebugHelper::assert(test1.get_entry(3)->get_hint_type() == "Angle", "Failed test 1.4 (Invalid hint type, was \"", test1.get_entry(3)->get_hint_type(), 
        "\" when it should've been \"Angle\")");
    
    
    // Clear structs that were created in the previous test.
    ctx.clear_structs();
    
    input = R"(
        // Size: 8 bytes. Shared across every entry.
        typedef struct LevelObjectEntryCommon {
            u8 objectID; // 9-bit object ID to load (uses size's MSB).
            u8 size; // 7-bit total entry length (MSB is used in object_id).
            s16 x, y, z; // Position in level
        } LevelObjectEntryCommon;
    )";
    CStruct entryCommon2(ctx, input);
    
    input = R"(
        typedef struct LevelObjectEntry_Exit {
            LevelObjectEntryCommon common;
            u8 destinationMapId;
            u8 pad9;

            // Defines the location in overworld the player will spawn at.
            // Only used if the exit goes to overworld.
            //   0: Future Fun Land exit (also game start spawn)
            //   2: Dino Domain exit
            //   3: Snowflake Mountain exit
            //   4: Sherbet Island exit
            //   6: Dragon Forest exit
            //   7: Wizpig head exit
            s8 overworldSpawnIndex;

            u8 padB[5];
            u8 radius; // Activation radius.
            u8 angleY;
            u8 pad12[5];
            
            // Defines the location in a hub world the player will spawn at when exiting `destinationMapId`.
            // Only used if the exit goes to a race.
            //   0: Hub exit door
            //   1-4: One of the 4 race doors
            //   5: Boss door
            //   6: Minigame door
            //   7: Wizpig head
             u8 returnSpawnIndex;

            // -1: Doesn't warp to a boss race
            // 0: Warps to a boss 1 race
            // 1: Warps to a boss 2 race
            s8 bossFlag; Hint(  (  Enum : WarpFlag  )  )
            
            // Stuff added for testing purposes
            char *stringTest;
            int multiArrayTest[2][3][4][5];
            float floatTest;
            f32 floatTest2;
            int a, b, c;
            float *a2, * * b2, *** * c2 [ 1 ] [ 43] [ 55]   ;
            
            struct {
                int a;
                float b;
                struct {
                    int c;
                    int d;
                };
                struct {
                    int e;
                    int f;
                } innerStructTest;
                union {
                    struct LevelObjectEntry_Exit_SubStruct {
                        int g;
                        int h;
                    } innerStructinUnionInStruct;
                    u8 i;
                    s16 k;
                } unionInStruct;
            } structTest;
            struct {
                int aa;
                long long ab;
            };
            struct Foo {
                union Bar {
                    int a;
                    long b;
                }*bar[2];
            };
        } LevelObjectEntry_Exit;
    )";
    CStruct test2(ctx, input);
    
    DebugHelper::assert(!test2.is_trivial(), "Failed test 2.0 (struct was trivial)");
    
    DebugHelper::assert(test2.get_entry(9)->get_hint_value("Enum") == "WarpFlag", "Failed test 2.1 ()");
    // TODO: More tests needed!
    
    // Clear structs that were created in the previous test.
    ctx.clear_structs();
    
    DebugHelper::DebugTimer timer2;
    
    fs::path levelObjectEntriesFilepath = GlobalSettings::get_decomp_path("include_subpath", "/include") / "level_object_entries.h";
    CStructHelper::load_structs_from_file(ctx, levelObjectEntriesFilepath);
    
    DebugHelper::info(YELLOW_TEXT, "Took ", timer2.elapsed(), " to parse level_object_entries.h", RESET_TEXT);
    
    CStruct *levelObjectEntryCommon = ctx.get_struct("LevelObjectEntryCommon");
    CStruct *levelObjectEntryRacer = ctx.get_struct("LevelObjectEntry_Racer");
    CStruct *levelObjectEntryScenery = ctx.get_struct("LevelObjectEntry_Scenery");
    CStruct *levelObjectEntryExit = ctx.get_struct("LevelObjectEntry_Exit");
    CStruct *levelObjectEntryCheckpoint = ctx.get_struct("LevelObjectEntry_Checkpoint");
    
    // Make sure the sizes are correct.
    DebugHelper::assert(levelObjectEntryCommon->get_byte_size() == 8, "Failed test 3.0 (struct LevelObjectEntryCommon size is not 8)");
    DebugHelper::assert(levelObjectEntryRacer->get_byte_size() == 16, "Failed test 3.1 (struct LevelObjectEntry_Racer size is not 16)");
    DebugHelper::assert(levelObjectEntryScenery->get_byte_size() == 12, "Failed test 3.2 (struct LevelObjectEntry_Scenery size is not 12)");
    DebugHelper::assert(levelObjectEntryExit->get_byte_size() == 0x1A, "Failed test 3.3 (struct LevelObjectEntry_Exit size is not 0x1A)");
    DebugHelper::assert(levelObjectEntryCheckpoint->get_byte_size() == 0x1C, "Failed test 3.4 (struct LevelObjectEntry_Checkpoint size is not 0x1C)");
    // TODO: More tests needed!
    
    uint8_t entryCommonTestData[] = {
        0x0B, 
        0x08,
        0xFA, 0xCE,
        0xDE, 0xAD,
        0xBE, 0xEF
    };
    
    int16_t entryCommonTestData_x = levelObjectEntryCommon->get_entry(2)->get_integer_from_data(entryCommonTestData);
    int16_t entryCommonTestData_y = levelObjectEntryCommon->get_entry(3)->get_integer_from_data(entryCommonTestData);
    int16_t entryCommonTestData_z = levelObjectEntryCommon->get_entry(4)->get_integer_from_data(entryCommonTestData);
    
    DebugHelper::assert(entryCommonTestData_x == (int16_t)0xFACE, "Failed test 3.6 (Should be 0xFACE, but was ", DebugHelper::to_hex(entryCommonTestData_x), ")");
    DebugHelper::assert(entryCommonTestData_y == (int16_t)0xDEAD, "Failed test 3.7 (Should be 0xDEAD, but was ", DebugHelper::to_hex(entryCommonTestData_y), ")");
    DebugHelper::assert(entryCommonTestData_z == (int16_t)0xBEEF, "Failed test 3.8 (Should be 0xBEEF, but was ", DebugHelper::to_hex(entryCommonTestData_z), ")");
    
    DebugHelper::info(GREEN_TEXT, "C Struct Helper (using regex engine \"", regexEngineName, "\") passed all tests!", RESET_TEXT, " Took ", timer.elapsed());
}

void test_cstruct_helper() {
    test_cstruct_helper_engine(RegexEngine::STL);
    test_cstruct_helper_engine(RegexEngine::PCRE2);
}

void test_cenum_helper_engine(RegexEngine engine) {
    if(!RegexHelper::set_engine(engine)) {
        DebugHelper::warn("Regex engine ", engine, " is not implemented!");
        return;
    }
    
    std::string regexEngineName = RegexHelper::get_current_engine_name();
    
    DebugHelper::DebugTimer timer;
    
    CContext ctx;
    std::string input;
    
    input = R"(
        typedef enum Test {
            FOO_BAR,
            FOO_BAR_2,
            FOO_BAR_4 = 123
        } Test;
    )";
    CEnum testEnum(ctx, input);
    
    input = R"(
        typedef enum Test2 {
            AA = -1,
            AB = 2,
            AC,
            AD = 512,
            AE = FOO_BAR_4 | AD
        } Test2;
    )";
    CEnum test0(ctx, input);
    
    DebugHelper::assert(ctx.get_int_value_of_symbol("AA") == -1, "Failed test 0.1 (AA has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("AB") == 2, "Failed test 0.2 (AB has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("AC") == 3, "Failed test 0.3 (AC has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("AD") == 512, "Failed test 0.4 (AD has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("AE") == (512 | 123), "Failed test 0.5 (AE has the incorrect value)");
    
    ctx.clear_enums();
    
    // Test enums.h
    fs::path enumsFilepath = GlobalSettings::get_decomp_path("include_subpath", "/include") / "enums.h";
    CEnumsHelper::load_enums_from_file(ctx, enumsFilepath);
    
    // Check a single member from each enum.
    DebugHelper::assert(ctx.get_int_value_of_symbol("VEHICLE_PLANE") == 2, "Failed test 1.1 (VEHICLE_PLANE has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("CAMERA_FINISH_CHALLENGE") == 5, "Failed test 1.2 (CAMERA_FINISH_CHALLENGE has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("LANGUAGE_GERMAN") == 1, "Failed test 1.3 (LANGUAGE_GERMAN has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("WORLD_FUTURE_FUN_LAND") == 5, "Failed test 1.4 (WORLD_FUTURE_FUN_LAND has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("RACETYPE_CHALLENGE_BANANAS") == 65, "Failed test 1.5 (RACETYPE_CHALLENGE_BANANAS has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("HORZ_ALIGN_CENTER") == 4, "Failed test 1.6 (HORZ_ALIGN_CENTER has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("VERT_ALIGN_BOTTOM") == 2, "Failed test 1.7 (VERT_ALIGN_BOTTOM has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("ALIGN_BOTTOM_CENTER") == 6, "Failed test 1.8 (ALIGN_BOTTOM_CENTER has the incorrect value)");
    DebugHelper::assert(ctx.get_int_value_of_symbol("SURFACE_ZIP_PAD") == 3, "Failed test 1.9 (SURFACE_ZIP_PAD has the incorrect value)");
    
    DebugHelper::info(GREEN_TEXT, "C Enum Helper (using regex engine \"", regexEngineName, "\") passed all tests!", RESET_TEXT, " Took ", timer.elapsed());
}

void test_cenum_helper() {
    test_cenum_helper_engine(RegexEngine::STL);
    test_cenum_helper_engine(RegexEngine::PCRE2);
}

void Test::test_all() {
    DebugHelper::info("Testing helpers!");
    test_regex_helper();
    test_cstruct_helper();
    test_cenum_helper();
}
