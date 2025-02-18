if (currentPage == 1) {
    Rectangle(memdc, 10, 10, 150, 40); // Highlight EXP button
}
else if (currentPage == 2) {
    Rectangle(memdc, 10, 50, 150, 80); // Highlight Fixes button
}
else if (currentPage == 3) {
    Rectangle(memdc, 10, 90, 150, 120); // Highlight Mechanics button
}

TextOut(memdc, 20, 15, "Levels & EXP", 13);
TextOut(memdc, 20, 55, "Various Fixes", 14);
TextOut(memdc, 20, 95, "Mechanics", 9);


if (currentPage == 1) {
    // Page 1: EXP-Related Mechanics
    int centerOffset = 200; // Center alignment
    int yStart = 50; // Starting Y position

    TextOut(memdc, centerOffset, yStart, "Heal EXP Percent:", 17);
    sprintf(out, "%d", HPEXPPercent);
    if (focus == 13 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 125, yStart, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 30, "Heal EXP Min:", 13);
    sprintf(out, "%d", HPEXPMin);
    if (focus == 14 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 105, yStart + 30, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 60, "Detox EXP:", 10);
    sprintf(out, "%d", DetoxEXP);
    if (focus == 16 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 90, yStart + 60, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 90, "Promotion Stats Percentage:", 27);
    sprintf(out, "%d", PromotePercent);
    if (focus == 15 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 190, yStart + 90, out, strlen(out));

    // EXP Overflow checkbox
    TextOut(memdc, centerOffset, yStart + 120, "EXP Overflow:", 13);
    if (EXPOverflow) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 100, yStart + 122, 13, 13, bmpdc, 0, 0, SRCCOPY);

    // Level Caps
    TextOut(memdc, centerOffset, yStart + 150, "Unpromoted Level Limit:", 24);
    sprintf(out, "%d", UnLevelLimit);
    if (focus == 9 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 165, yStart + 150, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 180, "Promoted Level Limit:", 24);
    sprintf(out, "%d", LevelLimit);
    if (focus == 10 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 150, yStart + 180, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 210, "Promotion Level:", 16);
    sprintf(out, "%d", ProLevel);
    if (focus == 11 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 120, yStart + 210, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 240, "Base Promoted Level (Used For Calculating EXP):", 48);
    sprintf(out, "%d", ProLevelAdd);
    if (focus == 12 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 325, yStart + 240, out, strlen(out));

    int tableX = 625; // far right x offset (adjust as needed)
    int tableY = 50;  // starting y position for the table

    // EXP5Above
    TextOut(memdc, tableX, tableY, "EXP5Above:", 10);
    sprintf(out, "%d", EXP5Above);
    if (focus == 17 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
    tableY += 30;

    // EXPPlus4
    TextOut(memdc, tableX, tableY, "EXPPlus4:", 9);
    sprintf(out, "%d", EXPPlus4);
    if (focus == 18 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
    tableY += 30;

    // EXPPlus3
    TextOut(memdc, tableX, tableY, "EXPPlus3:", 9);
    sprintf(out, "%d", EXPPlus3);
    if (focus == 19 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
    tableY += 30;

    // EXPPlus2
    TextOut(memdc, tableX, tableY, "EXPPlus2:", 9);
    sprintf(out, "%d", EXPPlus2);
    if (focus == 20 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
    tableY += 30;

    // EXPPlus1
    TextOut(memdc, tableX, tableY, "EXPPlus1:", 9);
    sprintf(out, "%d", EXPPlus1);
    if (focus == 21 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
    tableY += 30;

    // SameLevel
    TextOut(memdc, tableX, tableY, "SameLevel:", 10);
    sprintf(out, "%d", SameLevel);
    if (focus == 22 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
    tableY += 30;

    // EXPMinus1
    TextOut(memdc, tableX, tableY, "EXPMinus1:", 10);
    sprintf(out, "%d", EXPMinus1);
    if (focus == 23 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
    tableY += 30;

    // EXPMinus2
    TextOut(memdc, tableX, tableY, "EXPMinus2:", 10);
    sprintf(out, "%d", EXPMinus2);
    if (focus == 24 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
    tableY += 30;

    // EXP3Below
    TextOut(memdc, tableX, tableY, "EXP3Below:", 10);
    sprintf(out, "%d", EXP3Below);
    if (focus == 25 && cursor)sprintf(out, "%s|", out);
    TextOut(memdc, tableX + 100, tableY, out, strlen(out));
}
else if (currentPage == 2) {
    // Page 2: Fixes
    int centerOffset = 200; // Center alignment
    int yStart = 50; // Starting Y position

    TextOut(memdc, centerOffset, yStart, "Fix Muddle:", 11);
    if (FixMuddle) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 80, yStart +2, 13, 13, bmpdc, 0, 0, SRCCOPY);
    TextOut(memdc, centerOffset + 95, yStart, "(Evasion/Accuracy)", 18);

    TextOut(memdc, centerOffset, yStart + 30, "Fix Land Effect:", 16);
    if (FixLE) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 105, yStart + 32, 13, 13, bmpdc, 0, 0, SRCCOPY);

    // Fix Class Double Setting checkbox
    TextOut(memdc, centerOffset, yStart + 60, "Fix Class Double Setting:", 25);
    if (FixDoubles) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 170, yStart + 62, 13, 13, bmpdc, 0, 0, SRCCOPY);
}
else if (currentPage == 3) {
    // Page 3: Mechanics
    int centerOffset = 200; // Center alignment
    int yStart = 50; // Starting Y position

    // Poison
    TextOut(memdc, centerOffset, yStart, "Poison:", 7);
    sprintf(out, "%d", Poison);
    if (focus == 1 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 50, yStart, out, strlen(out));

    if (PoisonOffset == 0x20244) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset, yStart + 20, 13, 13, bmpdc, 0, 0, SRCCOPY);
    TextOut(memdc, centerOffset + 20, yStart + 20, "Fixed Damage", 12);

    if (PoisonOffset == 0x20244) SelectObject(bmpdc, checkoff);
    else SelectObject(bmpdc, checkon);
    BitBlt(memdc, centerOffset, yStart + 40, 13, 13, bmpdc, 0, 0, SRCCOPY);
    TextOut(memdc, centerOffset + 20, yStart + 40, "Percent Damage", 14);

    if (PoisonOffset != 0x20244) {
        TextOut(memdc, centerOffset + 140, yStart + 40, "Routine Offset:", 15);
        sprintf(out, "%X", PoisonOffset);
        if (focus == 2 && cursor) sprintf(out, "%s|", out);
        TextOut(memdc, centerOffset + 240, yStart + 40, out, strlen(out));
    }

    // Sleep Chance
    TextOut(memdc, centerOffset + 180, yStart + 90, "Wake Up Chance%:", 18);
    sprintf(out, "%d", SleepWakeChance);
    if (focus == 18 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 310, yStart + 90, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 380, "Damage:", 7);
    TextOut(memdc, centerOffset, yStart + 400, "Base Percent:", 13);
    sprintf(out, "%d", DamageBase);
    if (focus == 3 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 100, yStart + 400, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 420, "Spread:", 7);
    sprintf(out, "%d", DamageSpread - 1);
    if (focus == 4 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 100, yStart + 420, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 440, "Crit Mult:", 10);
    sprintf(out, "%d", CritMult);
    if (focus == 5 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 100, yStart + 440, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 90, "Three Digit Stats:", 18);
    if (RemoveMarks) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 150, yStart + 90, 13, 13, bmpdc, 0, 0, SRCCOPY);

    TextOut(memdc, centerOffset, yStart + 110, "Stat Cap to 127:", 16);
    if (RemoveCaps) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 150, yStart + 110, 13, 13, bmpdc, 0, 0, SRCCOPY);

    TextOut(memdc, centerOffset, yStart + 140, "Multiple Attacks:", 17);
    TextOut(memdc, centerOffset, yStart + 160, "Double Chance:", 14);
    sprintf(out, "%d", DoubleChance);
    if (focus == 6 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 150, yStart + 160, out, strlen(out));

     TextOut(memdc, centerOffset, yStart + 180, "Triple+ Attacks:", 16);
    if (MultiAttacks) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 150, yStart + 180, 13, 13, bmpdc, 0, 0, SRCCOPY);

    // Multi Falloff field (to the right of the checkbox)
    if (MultiAttacks) {
        TextOut(memdc, centerOffset + 170, yStart + 180, "Multi Falloff:", 14);
        sprintf(out, "%d", MultiFalloff);
        if (focus == 7 && cursor) sprintf(out, "%s|", out);
        TextOut(memdc, centerOffset + 270, yStart + 180, out, strlen(out));
    }

    TextOut(memdc, centerOffset, yStart + 210, "Item Break Chance:        %", 27);
    sprintf(out, "%d", BreakChance);
    if (focus == 8 && cursor) sprintf(out, "%s|", out);
    TextOut(memdc, centerOffset + 130, yStart + 210, out, strlen(out));

    TextOut(memdc, centerOffset, yStart + 240, "No Reviving:", 12);
    if (DisallowRevive) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 100, yStart + 240, 13, 13, bmpdc, 0, 0, SRCCOPY);

    TextOut(memdc, centerOffset, yStart + 270, "Jogurt Levels:", 14);
    if (JogurtLevels) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 100, yStart + 270, 13, 13, bmpdc, 0, 0, SRCCOPY);

    TextOut(memdc, centerOffset, yStart + 300, "Add MP Increase Effect:", 23);
    if (ExtendStatItems) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 160, yStart + 302, 13, 13, bmpdc, 0, 0, SRCCOPY);

    TextOut(memdc, centerOffset, yStart + 330, "Add New Effects:", 16);
    if (AddMPEffect) SelectObject(bmpdc, checkon);
    else SelectObject(bmpdc, checkoff);
    BitBlt(memdc, centerOffset + 150, yStart + 330, 13, 13, bmpdc, 0, 0, SRCCOPY);
}