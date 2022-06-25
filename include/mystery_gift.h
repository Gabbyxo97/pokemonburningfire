#ifndef GUARD_MYSTERY_GIFT_H
#define GUARD_MYSTERY_GIFT_H

#include "global.h"

struct MysteryGiftMon
{
    const u8* password;
    const u16 species;
    const u16 heldItem;
    const u8 friendship;
    const u8 otName[11];
    const u8 level;
    const u32 otGender:1;
    const u32 hpIV:5;
    const u32 attackIV:5;
    const u32 defenseIV:5;
    const u32 speedIV:5;
    const u32 spAttackIV:5;
    const u32 spDefenseIV:5;
    const u32 abilityNum:1;
    const u16 moves[4];
    const u8 shiny:1;
    const u16 flag;
};

enum
{
    MYSTERY_GIFT_1,
    MYSTERY_GIFT_END
};

extern const u8 gDeoxysGiftPassword[];

u8 checkGift(const u8* password, u8* speciesName);

#endif // GUARD_MYSTERY_GIFT_H