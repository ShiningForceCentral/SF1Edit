	TextOut(memdc,10,10,"Poison:",7);

	sprintf(out,"%d",Poison);
	if(focus==1&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,63,10,out,strlen(out));

	if(PoisonOffset==0x20244)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,20,26,13,13,bmpdc,0,0,SRCCOPY);
	TextOut(memdc,38,26,"Fixed Damage",12);
	if(PoisonOffset==0x20244)SelectObject(bmpdc,checkoff);
	else SelectObject(bmpdc,checkon);
	BitBlt(memdc,20,42,13,13,bmpdc,0,0,SRCCOPY);
	TextOut(memdc,38,42,"Percent Damage",14);
	if(PoisonOffset!=0x20244){
		TextOut(memdc,38,58,"Routine Offset:",15);
		sprintf(out,"%X",PoisonOffset);
		if(focus==2&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,148,58,out,strlen(out));
	}


	TextOut(memdc,310,10,"Fix Land Effect:",16);
	if(FixLE)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,414,12,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,310,30,"Automatic Item Passing:",23);
	if(ItemPassing)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,468,32,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc, 492, 30, "In Battle:", 10);
	if (ItemPassingBattle)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 558, 32, 13, 13, bmpdc, 0, 0, SRCCOPY);

	TextOut(memdc,310,50,"EXP Overflow:",13);
	if(EXPOverflow)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,404,52,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,310,70,"Add Armor Type:",15);
	if(AddArmor)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,417,72,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,310,90,"Smart Heal AI:",14);
	if(HealAI)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,417,92,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc, 310, 110, "Heal EXP Percent:", 17);
	sprintf(out, "%d", HPEXPPercent);
	if (focus == 13 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 437, 110, out, strlen(out));

	TextOut(memdc, 310, 130, "Heal EXP Min:", 13);
	sprintf(out, "%d", HPEXPMin);
	if (focus == 14 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 437, 130, out, strlen(out));



	TextOut(memdc, 310, 298, "Fix Muddle:", 11);
	if (FixMuddle)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 397, 300, 13, 13, bmpdc, 0, 0, SRCCOPY);
	TextOut(memdc, 420, 298, "(Evasion/Accuracy)", 18);



	TextOut(memdc,10,90,"Damage:",7);
	TextOut(memdc,20,106,"Base Percent:",13);
	sprintf(out,"%d",DamageBase);
	if(focus==3&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,115,106,out,strlen(out));
	
	TextOut(memdc,20,122,"Spread:",7);
	sprintf(out,"%d",DamageSpread-1);
	if(focus==4&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,115,122,out,strlen(out));

	TextOut(memdc,20,138,"Crit Mult:",10);
	sprintf(out,"%d",CritMult);
	if(focus==5&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,115,138,out,strlen(out));

	TextOut(memdc,10,170,"Three Digit Stats:",18);
	if(RemoveMarks)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,130,172,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,170,170,"Extend Status Screen:",22);
	TextOut(memdc,180,190, "(Adds Crit and Enemy Level)", 27);
	if(DisplayCrit)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,315,172,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,10,190,"Stat Cap to 127:",16);
	if(RemoveCaps)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,130,192,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,10,220,"Multiple Attacks:",17);
	TextOut(memdc,20,236,"Double Chance:",14);
	sprintf(out,"%d",DoubleChance);
	if(focus==6&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,124,236,out,strlen(out));

	TextOut(memdc, 170, 220, "Fix Class Double Setting:", 25);
	if (FixDoubles)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 338, 222, 13, 13, bmpdc, 0, 0, SRCCOPY);

	TextOut(memdc,20,252,"Triple+ Attacks:",16);
	if(MultiAttacks)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,130,254,13,13,bmpdc,0,0,SRCCOPY);

	if(MultiAttacks){
		TextOut(memdc,20,268,"Multi Falloff:",14);
		sprintf(out,"%d",MultiFalloff);
		if(focus==7&&cursor)sprintf(out,"%s|",out);
		TextOut(memdc,124,268,out,strlen(out));
	}

	TextOut(memdc,10,298,"Item Break Chance:        %",27);
	sprintf(out,"%d",BreakChance);
	if(focus==8&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,138,298,out,strlen(out));

	TextOut(memdc,10,328,"No Reviving:",12);
	if(DisallowRevive)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,102,330,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc,10,358,"Maximum Level:",14);
	TextOut(memdc,20,374,"Unpromoted:",11);
	sprintf(out,"%d",UnLevelLimit);
	if(focus==9&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,110,374,out,strlen(out));
	TextOut(memdc,20,390,"Promoted:",9);
	sprintf(out,"%d",LevelLimit);
	if(focus==10&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,110,390,out,strlen(out));

	TextOut(memdc,150,358,"Minimum Level:",14);
	TextOut(memdc,160,374,"To Promote:",11);
	TextOut(memdc,160,390,"Promoted:",9);

	sprintf(out,"%d",ProLevel);
	if(focus==11&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,250,374,out,strlen(out));

	sprintf(out,"%d",ProLevelAdd);
	if(focus==12&&cursor)sprintf(out,"%s|",out);
	TextOut(memdc,250,390,out,strlen(out));



	TextOut(memdc, 10, 410, "Promotion Stats Percentage:", 27);
	sprintf(out, "%d", PromotePercent);
	if (focus == 15 && cursor)sprintf(out, "%s|", out);
	TextOut(memdc, 210, 410, out, strlen(out));



	TextOut(memdc,10,430,"Jogurt Levels:",14);
	if(JogurtLevels)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,115,431,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc, 150, 430, "Show Crit Gains:", 16);
	if (ShowCrit)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 265, 431, 13, 13, bmpdc, 0, 0, SRCCOPY);

	TextOut(memdc,10,470,"Add MP Increase Effect:",23);
	if(ExtendStatItems)SelectObject(bmpdc,checkon);
	else SelectObject(bmpdc,checkoff);
	BitBlt(memdc,172,472,13,13,bmpdc,0,0,SRCCOPY);

	TextOut(memdc, 10, 490, "Add New Effects:", 16);
	if (AddMPEffect)SelectObject(bmpdc, checkon);
	else SelectObject(bmpdc, checkoff);
	BitBlt(memdc, 172, 492, 13, 13, bmpdc, 0, 0, SRCCOPY);