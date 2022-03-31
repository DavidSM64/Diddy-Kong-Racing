# DKR Assets Specification (Rev. 2.0)

## Enums *(from include/enums.h)*

| Vehicle | |
| -------- | -------- |
| VEHICLE_CAR | 0 |
| VEHICLE_HOVERCRAFT | 1 |
| VEHICLE_PLANE | 2 |

| Language | |
| -------- | -------- |
| LANGUAGE_ENGLISH | 0 |
| LANGUAGE_GERMAN | 1 |
| LANGUAGE_FRENCH | 2 |
| LANGUAGE_JAPANESE | 3 |

| World | |
| -------- | -------- |
| WORLD_NONE | -1 |
| WORLD_CENTRAL_AREA | 0 |
| WORLD_DINO_DOMAIN | 1 |
| WORLD_SHERBET_ISLAND | 2 |
| WORLD_SNOWFLAKE_MOUNTAIN | 3 |
| WORLD_DRAGON_FOREST | 4 |
| WORLD_FUTURE_FUN_LAND | 5 |

| RaceType | |
| -------- | -------- |
| RACETYPE_DEFAULT | 0 |
| RACETYPE_HORSESHOE_GULCH | 3 |
| RACETYPE_HUBWORLD | 5 |
| RACETYPE_CUTSCENE_1 | 6 |
| RACETYPE_CUTSCENE_2 | 7 |
| RACETYPE_BOSS | 8 |
| RACETYPE_CHALLENGE_BATTLE | 64 |
| RACETYPE_CHALLENGE_BANANAS | 65 |
| RACETYPE_CHALLENGE_EGGS | 66 |

| HorizontalAlignmentFlags | |
| -------- | -------- |
| HORZ_ALIGN_LEFT | 0 |
| HORZ_ALIGN_RIGHT | 1 |
| HORZ_ALIGN_CENTER | 4 |

| VerticalAlignmentFlags | |
| -------- | -------- |
| VERT_ALIGN_TOP | 0 |
| VERT_ALIGN_BOTTOM | 2 |
| VERT_ALIGN_MIDDLE | 8 |

| AlignmentFlags | |
| -------- | -------- |
| ALIGN_TOP_LEFT | VERT_ALIGN_TOP \| HORZ_ALIGN_LEFT |
| ALIGN_TOP_CENTER | VERT_ALIGN_TOP \| HORZ_ALIGN_CENTER |
| ALIGN_TOP_RIGHT | VERT_ALIGN_TOP \| HORZ_ALIGN_RIGHT |
| ALIGN_MIDDLE_LEFT | VERT_ALIGN_MIDDLE \| HORZ_ALIGN_LEFT |
| ALIGN_MIDDLE_CENTER | VERT_ALIGN_MIDDLE \| HORZ_ALIGN_CENTER |
| ALIGN_MIDDLE_RIGHT | VERT_ALIGN_MIDDLE \| HORZ_ALIGN_RIGHT |
| ALIGN_BOTTOM_LEFT | VERT_ALIGN_BOTTOM \| HORZ_ALIGN_LEFT |
| ALIGN_BOTTOM_CENTER | VERT_ALIGN_BOTTOM \| HORZ_ALIGN_CENTER |
| ALIGN_BOTTOM_RIGHT | VERT_ALIGN_BOTTOM \| HORZ_ALIGN_RIGHT |

----

## Fonts

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| fonts | Object | Yes | Defines the filename for each font. The order of the fonts is set by the `asset_fonts.json` file in the root version directory. |
| type | String | Yes | Should always be "Fonts" |

```json 
{
  "fonts" : {
    "ASSET_FONTS_BIGFONT" : "game_fonts/BigFont.json",
    "ASSET_FONTS_FUNFONT" : "game_fonts/FunFont.json",
    "ASSET_FONTS_SMALLFONT" : "game_fonts/SmallFont.json",
    "ASSET_FONTS_SUBTITLEFONT" : "game_fonts/SubtitleFont.json"
  },
  "type" : "Fonts"
}
```

### Font

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| characters | Object (Dictionary) | Yes | Describes each character using a node object. |
| encoding | Object | Yes | Describes the encoding used for the tool. All 4 DKR fonts just use ASCII, but the builder tool can support custom encodings (though this is has not been tested yet) |
| fixed-width | Integer | Yes | If this value is not 0, then every character will use this value instead of their `char-width` value. |
| name | String | Yes | Name of the font. |
| special-character-width | Integer | Yes | Width for every ASCII character value smaller or equal to 0x20 (including space and excluding the tab character, which uses `tab-width`). |
| tab-width | Integer | Yes | Width of the tab character `\t` |
| textures | Array | Yes | An array of Texture IDs to use for this font. DKR has a maximum of 32 textures; future rare games extended this to 64. |
| unknown-text | String | Yes | Leftover debug text from development? |
| y-offset | Integer | Yes | Offsets the y position for each character in the font. (Might just be line height?) |

| `character` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- |
| char-width | Integer | Yes | Width of the character in pixels. (Excluding the space character, which uses `special-character-width`) |
| offset | Array (2 Integers) | Yes | Values added to the character's X,Y position  |
| tex-index | Integer | Yes | Index in the `textures` array to use for this character, or -1 if no texture is used. |
| tex-size | Array (2 Integers) | Yes | Width and height of the character's texture. |
| uv | Array (2 Integers) | Yes | X/Y position in the texture to use. |

| `encoding` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- |
| type | String | Yes | Should always be "ASCII" for the moment. Support for custom encodings might come in the future. |

```json 
{
  "characters" : {
    "A" : {
      "char-width" : 11,
      "offset" : [0, 0],
      "tex-index" : 0,
      "tex-size" : [11, 12],
      "uv" : [0, 0]
    },
    ... There are lots of charcters!
  },
  "encoding" : {
    "type" : "ASCII"
  },
  "fixed-width" : 0,
  "name" : "FunFont",
  "special-character-width" : 6,
  "tab-width" : 32,
  "textures" : ["ASSET_TEX2D_FUNFONT_0", "ASSET_TEX2D_FUNFONT_1", "ASSET_TEX2D_FUNFONT_2", "ASSET_TEX2D_FUNFONT_3", "ASSET_TEX2D_FUNFONT_4", "ASSET_TEX2D_FUNFONT_5"],
  "unknown-text" : "DIBANK \tdwise/seq_sample",
  "y-offset" : 16
}
```

## Game Text

Note: Only Textboxes are properly supported.

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| text-type | String | Yes | Either "Dialog" or "Textbox" |
| type | String | Yes | Should always be "GameText" |

### Dialog

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| raw | Array | Yes | Array of bytes that represents the data. Note: This is just temporary until the dialog text format is fully figured out. |

```json 
{
  "raw" : [1, 255, 255, 255, 255, 1, 4, 20, 89, 111, 117, 32, 104, 97, 118, 101, 32, 116, 97, 107, 101, 110, 32, 116, 104, 101, 32, 119, 114, 111, 110, 103, 32, 114, 111, 117, 116, 101, 46, 0, 12, 1, 255, 255, 255, 255, 1, 4, 30, 84, 82, 89, 32, 65, 71, 65, 73, 78, 33, 33, 0, 0, 0, 34],
  "text-type" : "Dialog",
  "type" : "GameText"
}
```

### Textbox

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| pages | Array | Yes | Contains arrays of commands that are used to create the textbox. |

| Command | Value Type | Comments |
| -------- | -------- | -------- |
| AddVerticalSpacing | Integer | Moves the current Y position down by this amount. |
| AllowUserInput | Boolean | Allows the user to skip the textbox if enabled. By default this is set to `true`, and seems to be disabled only for cutscenes. |
| SetAlignment | String | Should either be "center" or "left". |
| SetBorder | Object | Sets the size of the textbox based off distance from the sides of the screen, using the "top", "left", "bottom", "right" properties. Each property is an integer between 0 and 255. |
| SetColour | Object | Sets the RGBA color of the text, using the "red", "green", "blue", "alpha" properties. Each property is an integer between 0 and 255. |
| SetFont | String | Font ID to use for the following text. |
| SetLineHeight | Integer | Sets how much a new line will move the Y position down. |
| SetTimer | Integer | Sets how many seconds to display this textbox. |
| Text | String | Line of text to display. Automatically adds a newline at the end. |
| Unknown | Integer | Currently unknown value used in 6 textbox files. |


```json
{
  "pages" : [[{
        "command" : "SetBorder",
        "value" : {
          "bottom" : 200,
          "left" : 40,
          "right" : 205,
          "top" : 30
        }
      }, {
        "command" : "SetAlignment",
        "value" : "center"
      }, {
        "command" : "SetFont",
        "value" : "ASSET_FONTS_FUNFONT"
      }, {
        "command" : "SetTimer",
        "value" : 8
      }, {
        "command" : "Text",
        "value" : "TROPHY RACE"
      }, {
        "command" : "AddVerticalSpacing",
        "value" : 10
      }, {
        "command" : "Text",
        "value" : "TO ENTER THE TROPHY RACE,"
      }, {
        "command" : "Text",
        "value" : "YOU MUST COMPLETE"
      }, {
        "command" : "Text",
        "value" : "ALL THE TASKS"
      }, {
        "command" : "Text",
        "value" : "FROM THIS WORLD."
      }, {
        "command" : "AddVerticalSpacing",
        "value" : 15
      }, {
        "command" : "Text",
        "value" : "KEEP RACING!"
      }]],
  "text-type" : "Textbox",
  "type" : "GameText"
}
```

## Level Header

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| available-vehicles | Array | Yes | List of "Vehicle" enum Ids that tell the game which vehicles can be used in this track. |
| background-colour | Object | Yes | The clear color of the background. Only visible in some circumstances, mainly when a skydome is not used. |
| ceiling-height | Float | Yes | Maximum height for planes. |
| collectables | Integer | Yes | Bitfield representing the types of collectables found in the track (Bananas, Balloons, etc.). Note: This will probably be changed to an array of enum IDs in the future. |
| default-vehicle | String | Yes | The default vehicle to use for this track. Should be one of the options in the available-vehicles array. See the "Vehicle" enum for options. |
| fog | Object | Yes | Details the colour and distance of the fog used in the level. |
| fov | Integer | Yes | Sets camera's field of view. Can only be within the range (0, 90]. Usually set to 60 for most tracks. |
| instruments | Integer | Yes | Bitfield of which instruments are active when the level loads up. This is usually set to 65535 (0xFFFF) for most tracks. Note: This will probably be changed to an array of enum IDs in the future. |
| model | String | Yes | Level Model ID to use for this track. |
| music | Integer | Yes | Music track to use for this level. Note: This will probably be replaced with a string ID in the future. |
| number-laps | Integer | Yes | Number of laps to complete the race. Up to 6 laps should work; having more than that might cause glitches. |
| race-type | String | Yes | Type of race for this track. See "RaceType" enum for options. |
| skybox | Integer | Yes | Object index for the skydome being used for this level. Note: This will probably be replaced with a string ID in the future.|
| type | String | Yes | Should always be "LevelHeaders" |
| unknown-data | Object | Yes | Contains all the data we haven't figured out yet. These will be properly categorized in the future. |
| world | String | Yes | Which world this track appears in. See "World" enum for options. |

| `background-colour` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- |
| red | Integer | Yes | Red Channel value. 0-255 |
| green | Integer | Yes | Green Channel value. 0-255 |
| blue | Integer | Yes | Blue Channel value. 0-255 |

| `fog` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- |
| colour | Object | Yes | RGB values of the fog. |
| range | Object | Yes | Distance of the fog, min/max values usually fall within [900, 1000]. If both values are 0, then fog is disabled. |

| `fog` `colour` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- |
| red | Integer | Yes | Red Channel value. 0-255 |
| green | Integer | Yes | Green Channel value. 0-255 |
| blue | Integer | Yes | Blue Channel value. 0-255 |

| `fog` `range` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- |
| min | Integer | Yes | Starting point of fog. Usually set within the range [900, 999]. |
| max | Integer | Yes | Ending point of fog. Usually set at around 1000 (camera's far plane). |

```json
{
  "available-vehicles" : ["VEHICLE_CAR", "VEHICLE_HOVERCRAFT", "VEHICLE_PLANE"],
  "background-colour" : {
    "blue" : 24,
    "green" : 65,
    "red" : 120
  },
  "ceiling-height" : 400.000000,
  "collectables" : 73,
  "default-vehicle" : "VEHICLE_CAR",
  "fog" : {
    "colour" : {
      "blue" : 0,
      "green" : 0,
      "red" : 0
    },
    "range" : {
      "max" : 0,
      "min" : 0
    }
  },
  "fov" : 60,
  "instruments" : 65535,
  "model" : "ASSET_LEVEL_MODELS_5",
  "music" : 10,
  "number-laps" : 3,
  "race-type" : "RACETYPE_DEFAULT",
  "skybox" : 209,
  "type" : "LevelHeaders",
  "unknown-data" : {
    "unk1" : 0,
    "unk2" : 0,
    "unk3" : 1,
    "unk4" : [3, 4, 4, 4],
    "unk44" : [0, 0, 0, 0, 12, 0, 0],
    "unk4F" : [0, 0, 1],
    "unk53" : 180,
    "unk56" : [4, 16, 1, 0, 6, 0, 2, 0, 3, 0, 0, 120, 1, 0, 0, 153, 4, 0, 0, 62, 1, 1, 1, 1, 0, 5, 1, 1, 66, 224],
    "unk74" : [-1, -1, -1, -1, -1, -1, -1],
    "unkA0" : [1, 1, 0, 0],
    "unkA4" : -1,
    "unkA8" : 0,
    "unkAA" : 5,
    "unkB0" : [14, 16, 0, 18, 0, 0, 0, 1, 0, 66, 0, 5, 0, 0, 50, 130, 235, 255, 255, 255],
    "unkC" : [2, 2, 1, 4, 3, 2, 3, 1, 1, 1, 0, 2, 1, 3, 4, 2, 3, 0, 1, 1, 0, 1, 2, 1, 6, 4, 5, 4, 5, 7, 80, 50, 50, 50, 20, 20, 100, 0, 0, 0],
    "unkC4" : 1960,
    "weather" : {
      "unk90" : 0,
      "unk92" : 0,
      "unk94" : 0,
      "unk95" : 0,
      "unk96" : 0,
      "unk98" : 0,
      "unk9A" : 0
    }
  },
  "world" : "WORLD_DINO_DOMAIN"
}
```

## Level Name

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| languages     | Object (Dictionary) | Yes | Defines the name for each language. See the "Language" enum for keys. If a language is not defined, the output text for that language will be an empty string. Note: LANGUAGE_JAPANESE is not properly implemented in the us_1.0 version of DKR. |
| type | String | Yes | Should always be "LevelNames" |

```json
{
  "languages" : {
    "LANGUAGE_ENGLISH" : "Ancient Lake",
    "LANGUAGE_FRENCH" : "LAC ANCESTRAL",
    "LANGUAGE_GERMAN" : "Rumpelsee",
    "LANGUAGE_JAPANESE" : "Japanese"
  },
  "type" : "LevelNames"
}
```

## Menu Text

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| sections | Object (Dictionary) | Yes | Contains all the key/value pairs for the menu text. See `asset_menu_text.json` in the root version directory for the full list of ids. |
| type | String | Yes | Should always be "MenuText" |

```json 
{
  "sections" : {
    "ASSET_MENU_TEXT_ABANDONCHALLENGE" : "ABANDON CHALLENGE",
    "ASSET_MENU_TEXT_ADVENTURE" : "ADVENTURE",
    "ASSET_MENU_TEXT_ADVENTURE2" : "ADVENTURE",
    "ASSET_MENU_TEXT_ADVENTURETWO" : "ADVENTURE TWO",
    "ASSET_MENU_TEXT_ADVENTURETWO2" : "ADVENTURE TWO",
    "ASSET_MENU_TEXT_ADVTWOLOADERROR_0" : "SORRY, BUT YOU",
    "ASSET_MENU_TEXT_ADVTWOLOADERROR_1" : "CAN'T LOAD GAMES",
    "ASSET_MENU_TEXT_ADVTWOLOADERROR_2" : "FOR THE SECOND",
    "ASSET_MENU_TEXT_ADVTWOLOADERROR_3" : "ADVENTURE UNTIL",
    "ASSET_MENU_TEXT_ADVTWOLOADERROR_4" : "YOU HAVE COMPLETED",
    "ASSET_MENU_TEXT_ADVTWOLOADERROR_5" : "THE FIRST.",
    "ASSET_MENU_TEXT_ALLCODESDELETED" : "All cheats have been deleted",
    "ASSET_MENU_TEXT_AUDIOOPTIONS" : "AUDIO OPTIONS",
    "ASSET_MENU_TEXT_BADCODE" : "Sorry, the code was incorrect",
    "ASSET_MENU_TEXT_BADCONTPAK" : "BAD CONTROLLER PAK",
    "ASSET_MENU_TEXT_BESTLAP" : "BEST LAP",
    "ASSET_MENU_TEXT_BESTTIME" : "BEST TIME",
    "ASSET_MENU_TEXT_CANCEL" : "CANCEL",
    "ASSET_MENU_TEXT_CANCELDELETE" : "CANCEL",
    "ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_0" : "Cannot save",
    "ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_1" : "Ghost Data",
    "ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_0" : "CANNOT STORE ANY",
    "ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_1" : "MORE GHOSTS.",
    "ASSET_MENU_TEXT_CAR" : "CAR",
    "ASSET_MENU_TEXT_CARCHALLENGE" : "CAR CHALLENGE",
    "ASSET_MENU_TEXT_CAUTION" : "CAUTION",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_0" : "Please do not change Rumble",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_1" : "Pak or Controller Pak",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_10" : "please do so now. ",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_2" : "during gameplay.  Controller",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_3" : "Pak is required to save and",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_4" : "load ghost data in Time Trial",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_5" : "mode. If Controller Pak has",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_6" : "limited capacity, you will be",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_7" : "unable to save ghost data.",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_8" : "If you wish to change",
    "ASSET_MENU_TEXT_CAUTIONMESSAGE_9" : "Controller Pak or Rumble Pak,",
    "ASSET_MENU_TEXT_CHALLENGE" : "CHALLENGE",
    "ASSET_MENU_TEXT_CHALLENGES" : "CHALLENGES",
    "ASSET_MENU_TEXT_CHALLENGESELECT" : "CHALLENGE SELECT",
    "ASSET_MENU_TEXT_CHANGEVEHICLE" : "CHANGE VEHICLE",
    "ASSET_MENU_TEXT_CLEARALLCODES" : "CLEAR ALL CODES",
    "ASSET_MENU_TEXT_CLEARALLCODESCANCEL" : "CANCEL",
    "ASSET_MENU_TEXT_CLEARALLCODESCONFIRM" : "OK",
    "ASSET_MENU_TEXT_CLEARALLCODESTITLE" : "CLEAR ALL CODES?",
    "ASSET_MENU_TEXT_CODELIST" : "CODE LIST",
    "ASSET_MENU_TEXT_CONTINUE" : "CONTINUE",
    ... There are lots of ids!
  },
  "type" : "MenuText"
}
```

## Sprite

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| frame-tex-count | Array | Yes | An array of integers that describes how many textures are in each frame of a sprites animation. If the length of the array is just 1, then it is just a static non-animated sprite.  |
| start-texture | String | Yes | The starting texture ID. Sprite textures are sequential starting from this ID. |
| type | String | Yes | Should always be "Sprites". |
| unk4 | Integer | Yes | Unknown value |
| unk6 | Integer | Yes | Unknown value |

```json
{
  "frame-tex-count" : [1, 1, 1, 2],
  "start-texture" : "ASSET_TEX2D_54",
  "type" : "Sprites",
  "unk4" : 32,
  "unk6" : 34
}
```

## Texture Header

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| compressed | Boolean | Yes | Most textures are compressed, but a small amount are not. |
| flags | Object | Yes | Rendering options for this texture. |
| flipped-image | Boolean | Yes | Most of the 3D textures have their textures upside-down. To make things easier for the programmer, I flipped the .png images back to normal and added this option. |
| format | String | Yes | Texture format for the image. Should either be "RGBA32", "RGBA16", "IA16", "IA8", "IA4", "I8", or "I4". Note: "CI4" and "CI8" are not currently supported by the build tool. |
| frame-advance-delay | Integer | No | The speed at which animated textures change their images. Number of frames per texture = (256 / frame-advance-delay) * (60 / FPS) |
| frame-count | Integer | Yes | Number of frame images in this texture. Static textures will have this set to 1. |
| height | Integer | Yes | Height of the texture image. |
| img | String | Yes | Source path of the .png image. |
| palette-offset | Integer | No | Offset to CI palette. Note: CI4/CI8 textures are not supported yet, so this is currently unused. |
| sprite-x | Integer | No | X offset of the sprite image. |
| sprite-y | Integer | No | Y offset of the sprite image. |
| tex-type | Integer | Yes | Unknown 4-bit value. |
| type | String | Yes | Should always be "Textures". |
| width | Integer | Yes | Width of the texture image. |
| write-size | Boolean | Yes | Most textures write their byte size in the header, while some others just have 0. Not sure the reason for this. |

| `flags` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| flag-01 | Boolean | Yes | Unknown flag |
| flag-04 | Boolean | Yes | Unknown flag |
| flag-10 | Boolean | Yes | Unknown flag |
| interlaced | Boolean | Yes | Any non-power-of-two texture that is loaded from gDPLoadBlock (basically anything that is not on the HUD) needs to be interlaced. |
| wrap-s | String | Yes | Either "Wrap" or "Clamp" |
| wrap-t | String | Yes | Either "Wrap" or "Clamp" |


```json
{
  "compressed" : true,
  "flags" : {
    "flag-01" : false,
    "flag-04" : false,
    "flag-10" : false,
    "interlaced" : false,
    "wrap-s" : "Wrap",
    "wrap-t" : "Wrap"
  },
  "flipped-image" : false,
  "format" : "RGBA32",
  "frame-count" : 1,
  "height" : 28,
  "img" : "img/bigfont_a.png",
  "tex-type" : 0,
  "type" : "Textures",
  "width" : 24,
  "write-size" : true
}
```

## T.T. Ghost

| Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| header | Object | Yes | Contains information about this ghost. |
| nodes | Array | Yes | Array of node objects defining points of the ghost. The game will interpolate between them. Maximum of 360 nodes (3 minutes). |

| `header` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| level | String | Yes | Level Header ID for this ghost. |
| time | Integer | Yes | Divide this number by 60 to get seconds. |
| vehicle | String | Yes | Vehicle used for this ghost. See the "Vehicle" enum for options. |


| `node` Property Name | Type | Required | Comments |
| -------- | -------- | -------- | -------- | 
| rx | Integer | Yes | X rotation |
| ry | Integer | Yes | Y rotation |
| rz | Integer | Yes | Z rotation |
| x | Integer | Yes | X position |
| y | Integer | Yes | Y position |
| z | Integer | Yes | Z position |

```json
{
  "header" : {
    "level" : "ASSET_LEVEL_ANCIENTLAKE",
    "time" : 3677,
    "vehicle" : "VEHICLE_CAR"
  },
  "nodes" : [{
      "rx" : 0,
      "ry" : 0,
      "rz" : 0,
      "x" : -1741,
      "y" : 29,
      "z" : -6488
    },
    ... There are lots of nodes!
]
        
```

## Changelog

* **2.0** - Created spec

