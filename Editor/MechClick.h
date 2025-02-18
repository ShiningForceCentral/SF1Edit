if (p.x >= 10 && p.x <= 100) {
    // Page navigation buttons
    if (p.y >= 10 && p.y <= 40) {
        currentPage = 1; // EXP Page
    }
    else if (p.y >= 50 && p.y <= 80) {
        currentPage = 2; // Fixes Page
    }
    else if (p.y >= 90 && p.y <= 120) {
        currentPage = 3; // Mechanics Page
    }
}

if (currentPage == 1) {
    // Page 1: EXP-Related Mechanics
    int centerOffset = 200;
    int yStart = 50;

    if (p.x >= centerOffset + 125 && p.x <= centerOffset + 145 && p.y >= yStart && p.y <= yStart + 20) {
        focus = 13; // Heal EXP Percent
    }
    if (p.x >= centerOffset + 105 && p.x <= centerOffset + 125 && p.y >= yStart + 30 && p.y <= yStart + 50) {
        focus = 14; // Heal EXP Min
    }
    if (p.x >= centerOffset + 90 && p.x <= centerOffset + 115 && p.y >= yStart + 60 && p.y <= yStart + 80) {
        focus = 16; // Detox EXP
    }
    if (p.x >= centerOffset + 190 && p.x <= centerOffset + 210 && p.y >= yStart + 90 && p.y <= yStart + 110) {
        focus = 15; // Promotion Stats Percentage
    }
    if (p.x >= centerOffset + 100 && p.x <= centerOffset + 165 && p.y >= yStart + 120 && p.y <= yStart + 133) {
        EXPOverflow = !EXPOverflow; // EXP Overflow
    }

    // Level Caps
    if (p.x >= centerOffset + 165 && p.x <= centerOffset + 185 && p.y >= yStart + 150 && p.y <= yStart + 170) {
        focus = 9; // Unpromoted Level Limit
    }
    if (p.x >= centerOffset + 150 && p.x <= centerOffset + 170 && p.y >= yStart + 180 && p.y <= yStart + 200) {
        focus = 10; // Promoted Level Limit
    }
    if (p.x >= centerOffset + 120 && p.x <= centerOffset + 140 && p.y >= yStart + 210 && p.y <= yStart + 230) {
        focus = 11; // Promotion Level
    }
    if (p.x >= centerOffset + 325 && p.x <= centerOffset + 345 && p.y >= yStart + 240 && p.y <= yStart + 260) {
        focus = 12; // the thing for promo exp
    }
    int tableX = 625; // far right x offset (adjust as needed)
    int tableY = 50;  // starting y position for the Kill EXP table

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 17; // EXP5Above
    }
    tableY += 30;

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 18; // EXPPlus4
    }
    tableY += 30;

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 19; // EXPPlus3
    }
    tableY += 30;

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 20; // EXPPlus2
    }
    tableY += 30;

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 21; // EXPPlus1
    }
    tableY += 30;

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 22; // SameLevel
    }
    tableY += 30;

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 23; // EXPMinus1
    }
    tableY += 30;

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 24; // EXPMinus2
    }
    tableY += 30;

    if (p.x >= tableX + 100 && p.x <= tableX + 120 && p.y >= tableY && p.y <= tableY + 20) {
        focus = 25; // EXP3Below
    }
}
else if (currentPage == 2) {
    // Page 2: Fixes
    int centerOffset = 200;
    int yStart = 50;

    if (p.x >= centerOffset + 80 && p.x <= centerOffset + 93 && p.y >= yStart + 2 && p.y <= yStart + 9) {
        FixMuddle = !FixMuddle; // Fix Muddle
    }
    if (p.x >= centerOffset + 105 && p.x <= centerOffset + 118 && p.y >= yStart + 30 && p.y <= yStart + 43) {
        FixLE = !FixLE; // Fix Land Effect
    }
    if (p.x >= centerOffset + 170 && p.x <= centerOffset + 183 && p.y >= yStart + 60 && p.y <= yStart + 73) {
        FixDoubles = !FixDoubles; // Fix Class Double Setting
    }
}
else if (currentPage == 3) {
    // Page 3: Mechanics
    int centerOffset = 200;
    int yStart = 50;

    // Poison
    if (p.x >= centerOffset + 50 && p.x <= centerOffset + 150 && p.y >= yStart && p.y <= yStart + 20) {
        focus = 1; // Poison
    }
    if (p.x >= centerOffset && p.x <= centerOffset + 13 && p.y >= yStart + 20 && p.y <= yStart + 33) {
        PoisonOffset = 0x20244; // Fixed Damage
    }
    if (p.x >= centerOffset && p.x <= centerOffset + 13 && p.y >= yStart + 40 && p.y <= yStart + 53 && PoisonOffset == 0x20244) {
        PoisonOffset = 0x180000; // Percent Damage
    }
    if (PoisonOffset != 0x20244 && p.x >= centerOffset + 240 && p.x <= centerOffset + 340 && p.y >= yStart + 40 && p.y <= yStart + 60) {
        focus = 2; // Routine Offset
    }

    // Wake Up Chance%
    if (p.x >= centerOffset + 310 && p.x <= centerOffset + 410 && p.y >= yStart + 90 && p.y <= yStart + 110) {
        focus = 18; // Wake Up Chance%
    }

    // Three Digit Stats
    if (p.x >= centerOffset + 150 && p.x <= centerOffset + 163 && p.y >= yStart + 90 && p.y <= yStart + 103) {
        RemoveMarks = !RemoveMarks; // Three Digit Stats
    }

    // Stat Cap to 127
    if (p.x >= centerOffset + 150 && p.x <= centerOffset + 163 && p.y >= yStart + 110 && p.y <= yStart + 123) {
        RemoveCaps = !RemoveCaps; // Stat Cap to 127
    }

    // Damage: Base Percent
    if (p.x >= centerOffset + 100 && p.x <= centerOffset + 200 && p.y >= yStart + 400 && p.y <= yStart + 420) {
        focus = 3; // Base Percent
    }

    // Damage: Spread
    if (p.x >= centerOffset + 100 && p.x <= centerOffset + 200 && p.y >= yStart + 420 && p.y <= yStart + 440) {
        focus = 4; // Spread
    }

    // Damage: Crit Multi
    if (p.x >= centerOffset + 100 && p.x <= centerOffset + 200 && p.y >= yStart + 440 && p.y <= yStart + 460) {
        focus = 5; // Crit Multi
    }

    // Double Chance
    if (p.x >= centerOffset + 150 && p.x <= centerOffset + 250 && p.y >= yStart + 160 && p.y <= yStart + 180) {
        focus = 6; // Double Chance
    }

    // Triple+ Attacks
    if (p.x >= centerOffset + 150 && p.x <= centerOffset + 163 && p.y >= yStart + 180 && p.y <= yStart + 193) {
        MultiAttacks = !MultiAttacks; // Triple+ Attacks
    }

    // Multi Falloff
    if (MultiAttacks && p.x >= centerOffset + 270 && p.x <= centerOffset + 370 && p.y >= yStart + 180 && p.y <= yStart + 200) {
        focus = 7; // Multi Falloff
    }

    // Item Break Chance
    if (p.x >= centerOffset + 130 && p.x <= centerOffset + 230 && p.y >= yStart + 210 && p.y <= yStart + 230) {
        focus = 8; // Item Break Chance
    }

    // No Reviving
    if (p.x >= centerOffset + 100 && p.x <= centerOffset + 113 && p.y >= yStart + 240 && p.y <= yStart + 253) {
        DisallowRevive = !DisallowRevive; // No Reviving
    }

    // Jogurt Levels
    if (p.x >= centerOffset + 100 && p.x <= centerOffset + 113 && p.y >= yStart + 270 && p.y <= yStart + 283) {
        JogurtLevels = !JogurtLevels; // Jogurt Levels
    }

    // Add MP Increase Effect
    if (p.x >= centerOffset + 160 && p.x <= centerOffset + 173 && p.y >= yStart + 302 && p.y <= yStart + 315) {
        ExtendStatItems = !ExtendStatItems; // Add MP Increase Effect
    }

    // Add New Effects
    if (p.x >= centerOffset + 150 && p.x <= centerOffset + 163 && p.y >= yStart + 330 && p.y <= yStart + 343) {
        AddMPEffect = !AddMPEffect; // Add New Effects
    }
}
