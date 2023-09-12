////////////////////////////////////////////////////////////////////////////////
// char_data.h
// Character data
////////////////////////////////////////////////////////////////////////////////

typedef struct char_data_t CharData;

#pragma once
#ifndef MUD98__ENTITIES__CHAR_DATA_H
#define MUD98__ENTITIES__CHAR_DATA_H

#include "merc.h"

#include "interp.h"
#include "note.h"

#include "area_data.h"
#include "mob_memory.h"
#include "mob_prototype.h"
#include "object_data.h"
#include "player_data.h"
#include "room_data.h"

#include <stdbool.h>

typedef struct char_data_t {
    CharData* next;
    CharData* next_in_room;
    CharData* master;
    CharData* leader;
    CharData* fighting;
    CharData* reply;
    CharData* pet;
    CharData* mprog_target;
    MobMemory* memory;
    SpecFunc* spec_fun;
    MobPrototype* pIndexData;
    DESCRIPTOR_DATA* desc;
    AffectData* affected;
    NoteData* pnote;
    ObjectData* carrying;
    ObjectData* on;
    RoomData* in_room;
    RoomData* was_in_room;
    AreaData* zone;
    PlayerData* pcdata;
    GEN_DATA* gen_data;
    char* name;
    char* material;
    char* short_descr;
    char* long_descr;
    char* description;
    char* prompt;
    char* prefix;
    time_t logon;
    time_t played;
    int id;
    int version;
    int lines; /* for the pager */
    int exp;
    int act;
    int comm;
    int wiznet;
    int imm_flags;
    int res_flags;
    int vuln_flags;
    int affected_by;
    int form;
    int parts;
    int off_flags;
    int wait;
    int16_t damage[3];
    int16_t dam_type;
    int16_t start_pos;
    int16_t default_pos;
    int16_t mprog_delay;
    int16_t group;
    int16_t clan;
    int16_t sex;
    int16_t ch_class;
    int16_t race;
    int16_t level;
    int16_t trust;
    int16_t size;
    int16_t position;
    int16_t practice;
    int16_t train;
    int16_t carry_weight;
    int16_t carry_number;
    int16_t saving_throw;
    int16_t alignment;
    int16_t hitroll;
    int16_t damroll;
    int16_t armor[4];
    int16_t wimpy;
    int16_t perm_stat[MAX_STATS];
    int16_t mod_stat[MAX_STATS];
    int16_t invis_level;
    int16_t incog_level;
    int16_t timer;
    int16_t daze;
    int16_t hit;
    int16_t max_hit;
    int16_t mana;
    int16_t max_mana;
    int16_t move;
    int16_t max_move;
    int16_t gold;
    int16_t silver;
    bool valid;
} CharData;

#define IS_NPC(ch)            (IS_SET((ch)->act, ACT_IS_NPC))
#define IS_IMMORTAL(ch)       (get_trust(ch) >= LEVEL_IMMORTAL)
#define IS_HERO(ch)           (get_trust(ch) >= LEVEL_HERO)
#define IS_TRUSTED(ch, level) (get_trust((ch)) >= (level))
#define IS_AFFECTED(ch, sn)   (IS_SET((ch)->affected_by, (sn)))

#define GET_AGE(ch)                                                            \
    ((int)(17 + ((ch)->played + current_time - (ch)->logon) / 72000))

#define IS_GOOD(ch)    (ch->alignment >= 350)
#define IS_EVIL(ch)    (ch->alignment <= -350)
#define IS_NEUTRAL(ch) (!IS_GOOD(ch) && !IS_EVIL(ch))

#define IS_AWAKE(ch)   (ch->position > POS_SLEEPING)
#define GET_AC(ch, type)                                                       \
    ((ch)->armor[type]                                                         \
     + (IS_AWAKE(ch) ? dex_app[get_curr_stat(ch, STAT_DEX)].defensive : 0))
#define GET_HITROLL(ch)                                                        \
    ((ch)->hitroll + str_app[get_curr_stat(ch, STAT_STR)].tohit)
#define GET_DAMROLL(ch)                                                        \
    ((ch)->damroll + str_app[get_curr_stat(ch, STAT_STR)].todam)

#define IS_OUTSIDE(ch)         (!IS_SET((ch)->in_room->room_flags, ROOM_INDOORS))

#define WAIT_STATE(ch, npulse) ((ch)->wait = UMAX((ch)->wait, (npulse)))
#define DAZE_STATE(ch, npulse) ((ch)->daze = UMAX((ch)->daze, (npulse)))
#define get_carry_weight(ch)                                                   \
    ((ch)->carry_weight + (ch)->silver / 10 + (ch)->gold * 2 / 5)

#define HAS_TRIGGER(ch, trig) (IS_SET((ch)->pIndexData->mprog_flags, (trig)))
#define IS_SWITCHED(ch) (ch->desc && ch->desc->original)
#define IS_BUILDER(ch, Area) (!IS_NPC(ch) && !IS_SWITCHED(ch) && \
                (ch->pcdata->security >= Area->security \
                || strstr(Area->builders, ch->name) \
                || strstr(Area->builders, "All")))
#define PERS(ch, looker)                                                       \
    (can_see(looker, (ch)) ? (IS_NPC(ch) ? (ch)->short_descr : (ch)->name)     \
                           : "someone")

void free_char_data(CharData* ch);
CharData* new_char_data();

extern CharData* char_list;
extern CharData* char_free;

extern int mobile_count;

#endif // !MUD98__ENTITIES__CHAR_DATA_H
