////////////////////////////////////////////////////////////////////////////////
// quest.h
////////////////////////////////////////////////////////////////////////////////

#ifndef MUD98__DATA__QUEST_H
#define MUD98__DATA__QUEST_H

typedef struct quest_t Quest;
typedef struct quest_status_t QuestStatus;
typedef struct quest_target_t QuestTarget;
typedef struct quest_log_t QuestLog;

#include "merc.h"

#include "entities/area_data.h"

typedef enum quest_type_t {
    QUEST_VISIT_MOB,
} QuestType;

typedef struct quest_t {
    Quest* next;
    AreaData* area;
    VNUM vnum;
    QuestType type;
    int xp;
    LEVEL level;
    VNUM end;
    VNUM target;
    char* name;
    char* entry;
} Quest;

typedef enum quest_state_t {
    QSTAT_ACCEPTED,
    QSTAT_COMPLETE,
} QuestState;

typedef struct quest_status_t {
    QuestStatus* next;
    VNUM vnum;
    QuestState state;
} QuestStatus;

// For quick triggers and indicators
typedef struct quest_target_t {
    QuestTarget* next;
    VNUM quest_vnum;
    VNUM target_vnum;
    VNUM end_vnum;
    QuestType type;
} QuestTarget;

typedef struct quest_log_t {
    QuestTarget* target_objs;
    QuestTarget* target_mobs;
    QuestStatus* quests;
} QuestLog;

void load_quest(FILE* fp);
Quest* new_quest();
QuestLog* new_quest_log();
void free_quest(Quest* quest);
void free_quest_log(QuestLog* quest_log);
Quest* get_quest(VNUM vnum);
QuestTarget* get_quest_targ_mob(CharData* ch, VNUM target_vnum);
QuestTarget* get_quest_targ_obj(CharData* ch, VNUM target_vnum);
QuestStatus* get_quest_status(CharData* ch, VNUM vnum);
void finish_quest(CharData* ch, Quest* quest, QuestStatus* status);
void grant_quest(CharData* ch, Quest* quest);
void save_quests(FILE* fp, AreaData* pArea); 
bool can_quest(CharData* ch, VNUM vnum);
bool has_quest(CharData* ch, VNUM vnum);
bool can_finish_quest(CharData* ch, VNUM vnum);

extern const struct flag_type quest_type_table[];

#endif // !MUD98__DATA__QUEST_H