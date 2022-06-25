#include "mystery_gift.h"

#include "constants/moves.h"
#include "constants/items.h"
#include "string_util.h"
#include "pokemon.h"
#include "malloc.h"
#include "random.h"
#include "event_data.h"
#include "constants/flags.h"
#include "data.h"
#include "constants/region_map_sections.h"

const u8 gDeoxysGiftPassword[] = _("DEOXYS22");

const struct MysteryGiftMon gMysteryGift[] = {
    [MYSTERY_GIFT_1] = {
        .password = gDeoxysGiftPassword,
        .species = SPECIES_DEOXYS,
        .heldItem = ITEM_TWISTED_SPOON,
        .friendship = 70,
        .otName = _("PKMNSPC"),
        .otGender = 0,
        .level = 50,
        .hpIV = 31,
        .attackIV = 31,
        .defenseIV = 31,
        .speedIV= 31,
        .spAttackIV = 31,
        .spDefenseIV = 31,
        .abilityNum = 1,
        .moves = { MOVE_PSYCHIC, MOVE_REFLECT, MOVE_BRICK_BREAK, MOVE_SAFEGUARD },
        .shiny = 1,
        .flag = MYSTERY_GIFT_SPACE_DEOXYS,
    }
};

void giveMysteryGiftMon(struct MysteryGiftMon mgmon) {    
    u8 data;
    u16 ball = ITEM_CHERISH_BALL;
    bool32 isEventLegal = TRUE;
    u8 metLocation = METLOC_FATEFUL_ENCOUNTER;

    struct Pokemon *mon = AllocZeroed(sizeof(struct Pokemon));
    CreateMon(mon, mgmon.species, mgmon.level, 32, 0, 0, OT_ID_PRESET, 16980);
    data = mgmon.otGender;
    SetMonData(mon, MON_DATA_OT_GENDER, &data);
    data = mgmon.hpIV;
    SetMonData(mon, MON_DATA_HP_IV, &data);
    data = mgmon.attackIV;
    SetMonData(mon, MON_DATA_ATK_IV, &data);
    data = mgmon.defenseIV;
    SetMonData(mon, MON_DATA_DEF_IV, &data);
    data = mgmon.speedIV;
    SetMonData(mon, MON_DATA_SPEED_IV, &data);
    data = mgmon.spAttackIV;
    SetMonData(mon, MON_DATA_SPATK_IV, &data);
    data = mgmon.spDefenseIV;
    SetMonData(mon, MON_DATA_SPDEF_IV, &data);
    SetMonData(mon, MON_DATA_MOVE1, &mgmon.moves[0]);
    SetMonData(mon, MON_DATA_MOVE2, &mgmon.moves[1]);
    SetMonData(mon, MON_DATA_MOVE3, &mgmon.moves[2]);
    SetMonData(mon, MON_DATA_MOVE4, &mgmon.moves[3]);
    data = gBattleMoves[mgmon.moves[0]].pp;
    SetMonData(mon, MON_DATA_PP1, &data);
    data = gBattleMoves[mgmon.moves[1]].pp;
    SetMonData(mon, MON_DATA_PP2, &data);
    data = gBattleMoves[mgmon.moves[2]].pp;
    SetMonData(mon, MON_DATA_PP3, &data);
    data = gBattleMoves[mgmon.moves[3]].pp;
    SetMonData(mon, MON_DATA_PP4, &data);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &mgmon.friendship);
    SetMonData(mon, MON_DATA_HELD_ITEM, &mgmon.heldItem);
    SetMonData(mon, MON_DATA_OT_NAME, &mgmon.otName);
    SetMonData(mon, MON_DATA_POKEBALL, &ball);
    SetMonData(mon, MON_DATA_EVENT_LEGAL, &isEventLegal);
    SetMonData(mon, MON_DATA_MET_LOCATION, &metLocation);

    GiveMysteryGiftMon(mon);
}

u8 checkGift(const u8* password, u8* speciesName) {
    u8 i;
    for (i = MYSTERY_GIFT_1; i < MYSTERY_GIFT_END; i++) {
        if (StringCompare(gMysteryGift[i].password, password) == 0) {
            if (FlagGet(gMysteryGift[i].flag))
                return 2;

            if (gMysteryGift[i].shiny)
                FlagSet(FLAG_SHINY_MON);

            giveMysteryGiftMon(gMysteryGift[i]);
            FlagSet(gMysteryGift[i].flag);
            StringCopy(speciesName, gSpeciesNames[gMysteryGift[i].species]);
            return 0;
        }
    }

    return 1;
}