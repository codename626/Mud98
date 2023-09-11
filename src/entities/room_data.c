////////////////////////////////////////////////////////////////////////////////
// room_data.h
// Utilities to handle navigable rooms
////////////////////////////////////////////////////////////////////////////////

#include "room_data.h"

#include "db.h"

#include "reset_data.h"

// MOVE THESE LATER!
void free_exit(ExitData* pExit);
void free_extra_descr(EXTRA_DESCR_DATA* pExtra);
//

int top_room;
VNUM top_vnum_room;
RoomData* room_index_free;
RoomData* room_index_hash[MAX_KEY_HASH];

void free_room_index(RoomData* pRoom)
{
    EXTRA_DESCR_DATA* pExtra;
    ResetData* pReset;
    int i;

    free_string(pRoom->name);
    free_string(pRoom->description);
    free_string(pRoom->owner);

    for (i = 0; i < MAX_DIR; i++)
        free_exit(pRoom->exit[i]);

    for (pExtra = pRoom->extra_descr; pExtra; pExtra = pExtra->next) {
        free_extra_descr(pExtra);
    }

    for (pReset = pRoom->reset_first; pReset; pReset = pReset->next) {
        free_reset_data(pReset);
    }

    pRoom->next = room_index_free;
    room_index_free = pRoom;
    return;
}

/*
 * Translates mob virtual number to its room index struct.
 * Hash table lookup.
 */
RoomData* get_room_data(VNUM vnum)
{
    RoomData* pRoomIndex;

    for (pRoomIndex = room_index_hash[vnum % MAX_KEY_HASH]; pRoomIndex != NULL;
        pRoomIndex = pRoomIndex->next) {
        if (pRoomIndex->vnum == vnum) return pRoomIndex;
    }

    if (fBootDb) {
        bug("Get_room_index: bad vnum %"PRVNUM".", vnum);
        exit(1);
    }

    return NULL;
}

RoomData* new_room_index()
{
    static	RoomData rZero;
    RoomData* pRoom;

    if (!room_index_free) {
        pRoom = alloc_perm(sizeof(*pRoom));
        top_room++;
    }
    else {
        pRoom = room_index_free;
        room_index_free = room_index_free->next;
    }

    *pRoom = rZero;

    pRoom->name = &str_empty[0];
    pRoom->description = &str_empty[0];
    pRoom->owner = &str_empty[0];
    pRoom->heal_rate = 100;
    pRoom->mana_rate = 100;

    return pRoom;
}
