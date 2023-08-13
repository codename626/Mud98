/***************************************************************************
 *  File: bit.c                                                            *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 *                                                                         *
 *  This code was written by Jason Dinkel and inspired by Russ Taylor,     *
 *  and has been used here for OLC - OLC would not be what it is without   *
 *  all the previous coders who released their source code.                *
 *                                                                         *
 ***************************************************************************/
/*
 The code below uses a table lookup system that is based on suggestions
 from Russ Taylor.  There are many routines in handler.c that would benefit
 with the use of tables.  You may consider simplifying your code base by
 implementing a system like below with such functions. -Jason Dinkel
 */

#include "merc.h"

#include "tables.h"
#include "lookup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

struct flag_stat_type {
    const struct flag_type *structure;
    bool stat;
};

/*****************************************************************************
 Name:		flag_stat_table
 Purpose:	This table catagorizes the tables following the lookup
 		functions below into stats and flags.  Flags can be toggled
 		but stats can only be assigned.  Update this table when a
 		new set of flags is installed.
 ****************************************************************************/
const struct flag_stat_type flag_stat_table[] =
{
/*  {	structure		    stat	}, */
    {	area_flags,		    false	},
    {   exit_flags,		    false	},
    {   door_resets,		true	},
    {   room_flags,		    false	},
    {   sector_flags,		true	},
    {   type_flags,		    true	},
    {   extra_flags,		false	},
    {   wear_flags,		    false	},
    {   act_flags,		    false	},
    {   affect_flags,		false	},
    {   apply_flags,		true	},
    {   wear_loc_flags,		true	},
    {   wear_loc_strings,	true	},
    {   container_flags,	false	},

/* ROM specific flags: */

    {   form_flags,         false   },
    {   part_flags,         false   },
    {   ac_type,            true    },
    {   off_flags,          false   },
    {   imm_flags,          false   },
    {   res_flags,          false   },
    {   vuln_flags,         false   },
    {   weapon_class,       true    },
    {   weapon_type2,       false   },
    {	furniture_flags,	false	},
    {   apply_types,		true	},
    {	target_table,		true	},
    {	dam_classes,		true	},
    {	log_flags,		    true	},
    {	show_flags,		    true	},
    {	stat_table,		    true	},
    {	mprog_flags,		false	},
    {   0,			        0	    }
};
    


/*****************************************************************************
 Name:		is_stat( table )
 Purpose:	Returns true if the table is a stat table and false if flag.
 Called by:	flag_value and flag_string.
 Note:		This function is local and used only in bit.c.
 ****************************************************************************/
bool is_stat(const struct flag_type* flag_table)
{
    int flag;

    for (flag = 0; flag_stat_table[flag].structure; flag++) {
        if (flag_stat_table[flag].structure == flag_table
            && flag_stat_table[flag].stat)
            return true;
    }
    return false;
}

/*****************************************************************************
 Name:		flag_value( table, flag )
 Purpose:	Returns the value of the flags entered.  Multi-flags accepted.
 Called by:	olc.c and olc_act.c.
 ****************************************************************************/
int flag_value(const struct flag_type* flag_table, char* argument)
{
    char word[MAX_INPUT_LENGTH];
    int  bit;
    int  marked = 0;
    bool found = false;

    if (is_stat(flag_table)) {
        one_argument(argument, word);

        return flag_lookup(word, flag_table);
    }

    /*
     * Accept multiple flags.
     */
    for (; ;) {
        argument = one_argument(argument, word);

        if (word[0] == '\0')
            break;

        if ((bit = flag_lookup(word, flag_table)) != NO_FLAG) {
            SET_BIT(marked, bit);
            found = true;
        }
    }

    if (found)
        return marked;
    else
        return NO_FLAG;
}

/*****************************************************************************
 Name:		flag_string( table, flags/stat )
 Purpose:	Returns string with name(s) of the flags or stat entered.
 Called by:	act_olc.c, olc.c, and olc_save.c.
 ****************************************************************************/
char* flag_string(const struct flag_type* flag_table, long bits)
{
    static char buf[10][MIL];
    int  flag;
    static int toggle;

    toggle = (++toggle) % 10;

    buf[toggle][0] = '\0';

    for (flag = 0; flag_table[flag].name != NULL; flag++) {
        if (!is_stat(flag_table) && IS_SET(bits, flag_table[flag].bit)) {
            strcat(buf[toggle], " ");
            strcat(buf[toggle], flag_table[flag].name);
        }
        else if (flag_table[flag].bit == bits) {
            strcat(buf[toggle], " ");
            strcat(buf[toggle], flag_table[flag].name);
            break;
        }
    }

    return (buf[toggle][0] != '\0') ? buf[toggle] + 1 : "none";
}
