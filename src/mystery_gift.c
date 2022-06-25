#include "mystery_gift.h"

#include "constants/moves.h"
#include "constants/items.h"
#include "mgba.h"
#include "string_util.h"

const u8 gDeoxysGiftPassword[] = _("A");

const struct MysteryGiftMon gMysteryGift[] = {
    [MYSTERY_GIFT_1] = {
        .password = gDeoxysGiftPassword,
        .species = SPECIES_DEOXYS,
        .heldItem = ITEM_TWISTED_SPOON,
        .friendship = 70,
        .otName = _("PKMNSPACE"),
        .otGender = 0,
        .level = 50,
        .hpIV = 31,
        .attackIV = 31,
        .defenseIV = 31,
        .speedIV= 31,
        .spAttackIV = 31,
        .spDefenseIV = 31,
        .abilityNum = 1,
        .moves[4] = { MOVE_PSYCHIC, MOVE_REFLECT, MOVE_BRICK_BREAK, MOVE_SAFEGUARD }   
    }
};

bool8 checkGift(const u8* password) {
    u8 i;
    for (i = MYSTERY_GIFT_1; i < MYSTERY_GIFT_END; i++) {
        if (StringCompare(gMysteryGift[i].password, password) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}