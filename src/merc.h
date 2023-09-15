/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

/***************************************************************************
 *  ROM 2.4 is copyright 1993-1998 Russ Taylor                             *
 *  ROM has been brought to you by the ROM consortium                      *
 *      Russ Taylor (rtaylor@hypercube.org)                                *
 *      Gabrielle Taylor (gtaylor@hypercube.org)                           *
 *      Brian Moore (zump@rom.org)                                         *
 *  By using this code, you have agreed to follow the terms of the         *
 *  ROM license, in the file Rom24/doc/rom.license                         *
 ***************************************************************************/

#pragma once
#ifndef MUD98__MERC_H
#define MUD98__MERC_H

#define MUD_NAME "Mud98"
#define MUD_VER "0.90"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _MSC_VER
#include <stddef.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Data files used by the server.
// 
// AREA_LIST contains a list of areas to boot.
// All files are read in completely at bootup.
// Most output files (bug, idea, typo, shutdown) are append-only.
// 
// The NULL_FILE is held open so that we have a stream handle in reserve, so
// players can go ahead and telnet to all the other descriptors. Then we close
// it whenever we need to open a file (e.g. a save file).
////////////////////////////////////////////////////////////////////////////////

extern char area_dir[];

#define DEFAULT_AREA_DIR "./"           // Default is legacy usage
#define PLAYER_DIR      "../player/"    // Player files
#define GOD_DIR         "../gods/"      // list of gods
#define TEMP_DIR        "../temp/"
#define DATA_DIR        "../data/"
#define PROG_DIR        DATA_DIR "progs/"
#define SOCIAL_FILE	    DATA_DIR "socials"
#define SKILL_FILE      DATA_DIR "skills"
#define COMMAND_FILE    DATA_DIR "commands"
#define RACES_FILE      DATA_DIR "races"
#define AREA_LIST       "area.lst"      // List of areas
#define BUG_FILE        "bugs.txt"      // For 'bug' and bug()
#define TYPO_FILE       "typos.txt"     // For 'typo'
#define NOTE_FILE       "notes.not"     // For 'notes'
#define IDEA_FILE       "ideas.not"
#define PENALTY_FILE    "penal.not"
#define NEWS_FILE       "news.not"
#define CHANGES_FILE    "chang.not"
#define SHUTDOWN_FILE   "shutdown.txt"  // For 'shutdown'
#define BAN_FILE        "ban.txt"
#define MUSIC_FILE      "music.txt"
#ifndef _MSC_VER
#define NULL_FILE       "/dev/null"     // To reserve one stream
#else
#define NULL_FILE       "nul"
#endif

#ifndef USE_RAW_SOCKETS
#define CERT_FILE       "../keys/rom-mud.pem"
#define PKEY_FILE       "../keys/rom-mud.key"
#endif

////////////////////////////////////////////////////////////////////////////////

#define args( list )                list

////////////////////////////////////////////////////////////////////////////////
// Custom Types
////////////////////////////////////////////////////////////////////////////////

// Used for flags and other bit fields
#define BIT(x) (1 << x)

// Expand when you run out of bits
#define FLAGS               uint32_t
#define FLAGS_MAX           BIT(31)

#define SHORT_FLAGS         uint16_t
#define SHORT_FLAGS_MAX     BIT(

#define LEVEL               int16_t

#define SKNUM               int16_t

// If you want to change the type for VNUM's, this is where you do it.
#define MAX_VNUM            INT32_MAX
#define VNUM                int32_t
#define PRVNUM              PRId32
#define STRTOVNUM(s)        (VNUM)strtol(s, NULL, 0)
#define VNUM_NONE           -1

////////////////////////////////////////////////////////////////////////////////

typedef struct char_data_t CharData;
typedef enum spell_target_t SpellTarget;

typedef void DoFunc(CharData* ch, char* argument);
typedef bool SpecFunc(CharData* ch);
typedef void SpellFunc(SKNUM sn, LEVEL level, CharData* ch, void* vo, SpellTarget target);
typedef int	LookupFunc(const char*);

#define DECLARE_DO_FUN( fun )       DoFunc fun
#define DECLARE_SPEC_FUN( fun )     SpecFunc fun
#define DECLARE_SPELL_FUN( fun )    SpellFunc fun
#define DECLARE_LOOKUP_FUN( fun )   LookupFunc fun

/* ea */
#define MSL MAX_STRING_LENGTH
#define MIL MAX_INPUT_LENGTH

/*
 * Structure types.
 */
typedef struct kill_data KILL_DATA;
typedef struct time_info_data TIME_INFO_DATA;
typedef struct weather_data WEATHER_DATA;

/*
 * String and memory management parameters.
 */
#define MAX_KEY_HASH        1024
#define MAX_STRING_LENGTH   4608
#define MAX_INPUT_LENGTH    256
#define PAGELEN             22

/*
 * Game parameters.
 * Increase the max'es if you add more of something.
 * Adjust the pulse numbers to suit yourself.
 */
#define MAX_SOCIALS         256

#define MAX_IN_GROUP        15
#define MAX_ALIAS           5
#define MAX_THEMES          5
#define MAX_CLASS           4
#define MAX_PC_RACE         5
#define MAX_CLAN            3
#define MAX_LEVEL           (LEVEL)60
#define LEVEL_HERO          (MAX_LEVEL - 9)
#define LEVEL_IMMORTAL      (MAX_LEVEL - 8)

#define PULSE_PER_SECOND    4
#define PULSE_VIOLENCE      (3 * PULSE_PER_SECOND)
#define PULSE_MOBILE        (4 * PULSE_PER_SECOND)
#define PULSE_MUSIC         (6 * PULSE_PER_SECOND)
#define PULSE_TICK          (60 * PULSE_PER_SECOND)
#define PULSE_AREA          (120 * PULSE_PER_SECOND)

#define IMPLEMENTOR         MAX_LEVEL
#define CREATOR             (MAX_LEVEL - 1)
#define SUPREME             (MAX_LEVEL - 2)
#define DEITY               (MAX_LEVEL - 3)
#define GOD                 (MAX_LEVEL - 4)
#define IMMORTAL            (MAX_LEVEL - 5)
#define DEMI                (MAX_LEVEL - 6)
#define ANGEL               (MAX_LEVEL - 7)
#define AVATAR              (MAX_LEVEL - 8)
#define HERO                LEVEL_HERO

/*
 * Time and weather stuff.
 */
#define SUN_DARK      0
#define SUN_RISE      1
#define SUN_LIGHT     2
#define SUN_SET       3

#define SKY_CLOUDLESS 0
#define SKY_CLOUDY    1
#define SKY_RAINING   2
#define SKY_LIGHTNING 3

struct time_info_data {
    int hour;
    int day;
    int month;
    int year;
};

struct weather_data {
    int mmhg;
    int change;
    int sky;
    int sunlight;
};

/*
 * Attribute bonus structures.
 */
struct str_app_type {
    int16_t tohit;
    int16_t todam;
    int16_t carry;
    int16_t wield;
};

struct int_app_type {
    int16_t learn;
};

struct wis_app_type {
    int16_t practice;
};

struct dex_app_type {
    int16_t defensive;
};

struct con_app_type {
    int16_t hitp;
    int16_t shock;
};

/*
 * Per-class stuff.
 */
#define MAX_GUILD 2
#define MAX_STATS 5
#define STAT_STR  0
#define STAT_INT  1
#define STAT_WIS  2
#define STAT_DEX  3
#define STAT_CON  4

struct class_type {
    char* name; /* the full name of the class */
    char who_name[4]; /* Three-letter name for 'who'	*/
    int16_t attr_prime; /* Prime attribute		*/
    int16_t weapon; /* First weapon			*/
    int16_t guild[MAX_GUILD]; /* Vnum of guild rooms		*/
    int16_t skill_adept; /* Maximum skill level		*/
    int16_t thac0_00; /* Thac0 for level  0		*/
    int16_t thac0_32; /* Thac0 for level 32		*/
    int16_t hp_min; /* Min hp gained on leveling	*/
    int16_t hp_max; /* Max hp gained on leveling	*/
    bool fMana; /* Class gains mana on level	*/
    char* base_group; /* base skills gained		*/
    char* default_group; /* default skills gained	*/
};

struct wiznet_type {
    char* name;
    long flag;
    LEVEL level;
};

struct race_type {
    char* name; /* call name of the race */
    char* who_name;
    char* skills[5];		/* bonus skills for the race */
    bool pc_race; /* can be chosen by pcs */
    FLAGS act_flags; /* act bits for the race */
    FLAGS aff; /* aff bits for the race */
    FLAGS off; /* off bits for the race */
    FLAGS imm; /* imm bits for the race */
    FLAGS res; /* res bits for the race */
    FLAGS vuln; /* vuln bits for the race */
    FLAGS form; /* default form flag for the race */
    FLAGS parts; /* default parts for the race */
    int16_t race_id;
    int16_t points;			/* cost in points of the race */
    int16_t class_mult[MAX_CLASS];	/* exp multiplier for class, * 100 */
    int16_t stats[MAX_STATS];	/* starting stats */
    int16_t max_stats[MAX_STATS];	/* maximum stats */
    int16_t size;			/* aff bits for the race */
};

/*
 * A kill structure (indexed by level).
 */
struct kill_data {
    int16_t number;
    int16_t killed;
};

/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (Start of section ... start here)                     *
 *                                                                         *
 ***************************************************************************/

/* AC types */
#define AC_PIERCE               0
#define AC_BASH                 1
#define AC_SLASH                2
#define AC_EXOTIC               3

/* dice */
#define DICE_NUMBER             0
#define DICE_TYPE               1
#define DICE_BONUS              2

/* gate flags */
#define GATE_NORMAL_EXIT        BIT(0)
#define GATE_NOCURSE            BIT(1)
#define GATE_GOWITH             BIT(2)
#define GATE_BUGGY              BIT(3)
#define GATE_RANDOM             BIT(4)

/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (End of this section ... stop here)                   *
 *                                                                         *
 ***************************************************************************/

/*
 * Utility macros.
 */
#define IS_VALID(data)       ((data) != NULL && (data)->valid)
#define VALIDATE(data)       ((data)->valid = true)
#define INVALIDATE(data)     ((data)->valid = false)
#define UMIN(a, b)           ((a) < (b) ? (a) : (b))
#define UMAX(a, b)           ((a) > (b) ? (a) : (b))
#define URANGE(a, b, c)      ((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
#define LOWER(c)             ((c) >= 'A' && (c) <= 'Z' ? (c) + 'a' - 'A' : (c))
#define UPPER(c)             ((c) >= 'a' && (c) <= 'z' ? (c) + 'A' - 'a' : (c))
#define IS_SET(flag, bit)    ((flag) & (bit))
#define SET_BIT(var, bit)    ((var) |= (bit))
#define REMOVE_BIT(var, bit) ((var) &= ~(bit))
#define TOGGLE_BIT(var, bit) ((var) ^= (bit))
#define IS_NULLSTR(str)		 ((str) == NULL || (str)[0] == '\0')
#define CHECKNULLSTR(str)    ((str) == NULL ? "" : (str))
#define CH(d)		         ((d)->original ? (d)->original : (d)->character)
#define BETWEEN(min,num,max) (((min) < (num)) && ((num) < (max)))
#define BETWEEN_I(x,y,z)     (((x) <= (y)) && ((y) <= (z)))
#define CHECK_POS(a, b, c)   \
    { \
        (a) = (b); \
        if ((a) < 0) \
            bug( "CHECK_POS : " c " == %d < 0", a ); \
    }
#define ARRAY_COPY(array1, array2, len) \
    { \
        int _xxx_; \
        for (_xxx_ = 0; _xxx_ < len; _xxx_++) \
            array1[_xxx_] = array2[_xxx_]; \
    }

/*
 * Structure for a social in the socials table.
 */
struct social_type {
    char* name;
    char* char_no_arg;
    char* others_no_arg;
    char* char_found;
    char* others_found;
    char* vict_found;
    char* char_not_found;
    char* char_auto;
    char* others_auto;
};

/*
 * Global constants.
 */
extern const struct str_app_type str_app[26];
extern const struct int_app_type int_app[26];
extern const struct wis_app_type wis_app[26];
extern const struct dex_app_type dex_app[26];
extern const struct con_app_type con_app[26];

extern const struct class_type class_table[MAX_CLASS];
extern const struct wiznet_type wiznet_table[];
extern       struct race_type* race_table;
extern       struct social_type* social_table;
extern char* const title_table[MAX_CLASS][MAX_LEVEL + 1][2];

/*****************************************************************************
 *                                    OLC                                    *
 *****************************************************************************/

#define NO_FLAG         -99 // Must not be used in flags or stats.

////////////////////////////////////////////////////////////////////////////////
// Global Vars
////////////////////////////////////////////////////////////////////////////////

// main.c
extern time_t current_time;
extern FILE* fpReserve;
extern bool MOBtrigger;

// db.c
extern char str_empty[1];
extern bool fBootDb;

#endif // !MUD98__MERC_H
