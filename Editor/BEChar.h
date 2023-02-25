	c=wParam;

	if(menu==2){
		if(focus==32){
			val=c-'0';
			if(val>=0&&val<10){
				i=subselect[mode][8];
				if(i<1000){
					i*=10;
					i+=val;
					subselect[mode][8]=i;
				}
			}
			if(c==8){
				i=subselect[mode][8];
				i=i-i%10;
				i/=10;
				subselect[mode][8]=i;
			}
			subselect[mode][8]%=NUM_TEXT;
		}
	}

	if(focus==1){
		val=c-'0';
		if(val>=0&&val<10){
			i=subselect[mode][0];
			if(i<10){
				i*=10;
				i+=val;
				subselect[mode][0]=i;
			}
		}
		if(c==8){
			i=subselect[mode][0];
			i=i-i%10;
			i/=10;
			subselect[mode][0]=i;
		}
		subselect[mode][0]%=NUM_BE;

		BEGraphs[subselect[mode][0]]->w = BEGraphs[u]->w;
		BEGraphs[subselect[mode][0]]->h = BEGraphs[u]->h;
		BEGraphs[subselect[mode][0]]->vx=0;
		BEGraphs[subselect[mode][0]]->vy=0;
	}

	if(focus==2&&BEGraphs[subselect[mode][0]]->sel){
		i = subfocus;
		if(i<0)i=(i+1)*-1;
		val=c-'0';
		if(val>=0&&val<10){
			switch(BEGraphs[subselect[mode][0]]->sel->type->argtypes[i]){
				case ARG_DIR:
				case ARG_IGNORE:
				case ARG_SPECIAL:
				case ARG_BRANCH:
				case ARG_SBRANCH:
					return true;
				case ARG_VOICE:
				case ARG_BYTE:
				case ARG_WORD:
				case ARG_LONG:
				case ARG_MESSAGE:
				case ARG_BANKED:
					lo=BEGraphs[subselect[mode][0]]->sel->args[i];
					break;
				case ARG_ADDSUB:
					BEGraphs[subselect[mode][0]]->sel->args[i]&=0xF1;
					BEGraphs[subselect[mode][0]]->sel->args[i]|=(val*2)&0x0E;
					break;
				case ARG_YESNO:
					lo=BEGraphs[subselect[mode][0]]->sel->args[i];
					if(subfocus>=0)lo = (lo&0xFF00)/0x100;
					else lo = lo&0xFF;
					break;
			}

			lo*=10;
			lo+=val;

			switch(BEGraphs[subselect[mode][0]]->sel->type->argtypes[i]){
				case ARG_BYTE:
				case ARG_VOICE:
					BEGraphs[subselect[mode][0]]->sel->args[i]=lo&0x00FF;
					break;
				case ARG_WORD:
				case ARG_MESSAGE:
				case ARG_BANKED:
					BEGraphs[subselect[mode][0]]->sel->args[i]=lo&0x0000FFFF;
					break;
				case ARG_LONG:
					BEGraphs[subselect[mode][0]]->sel->args[i]=lo;
					break;
				case ARG_YESNO:
					if(subfocus>=0){
						lo = (lo*0x100)&0xFF00;
						BEGraphs[subselect[mode][0]]->sel->args[i]&=0xFF;
						BEGraphs[subselect[mode][0]]->sel->args[i]|=lo;
					} else {
						lo = lo&0xFF;
						BEGraphs[subselect[mode][0]]->sel->args[i]&=0xFF00;
						BEGraphs[subselect[mode][0]]->sel->args[i]|=lo;
					}
					break;
			}

		}
		if(c=='-'&&BEGraphs[subselect[mode][0]]->sel->type->argtypes[i]==ARG_ADDSUB){
			BEGraphs[subselect[mode][0]]->sel->args[i]^=0x01;
		}
		if(c==8){
			switch(BEGraphs[subselect[mode][0]]->sel->type->argtypes[i]){
				case ARG_DIR:
				case ARG_IGNORE:
				case ARG_SPECIAL:
				case ARG_BRANCH:
				case ARG_SBRANCH:
					return true;
				case ARG_ADDSUB:
					BEGraphs[subselect[mode][0]]->sel->args[i]&=0xF1;
					break;
				case ARG_VOICE:
				case ARG_BYTE:
					lo=BEGraphs[subselect[mode][0]]->sel->args[i]&0xFF;
					break;
				case ARG_WORD:
				case ARG_LONG:
				case ARG_MESSAGE:
				case ARG_BANKED:
					lo=BEGraphs[subselect[mode][0]]->sel->args[i];
					break;
				case ARG_YESNO:
					lo=BEGraphs[subselect[mode][0]]->sel->args[i];
					if(subfocus>=0)lo = (lo&0xFF00)/0x100;
					else lo = lo&0xFF;
					break;
			}
			lo=lo-lo%10;
			lo/=10;
			switch(BEGraphs[subselect[mode][0]]->sel->type->argtypes[i]){
				case ARG_VOICE:
				case ARG_BYTE:
				case ARG_WORD:
				case ARG_LONG:
				case ARG_MESSAGE:
				case ARG_BANKED:
					BEGraphs[subselect[mode][0]]->sel->args[i]=lo;
					break;
				case ARG_YESNO:
					if(subfocus>=0){
						lo = (lo*0x100)&0xFF00;
						BEGraphs[subselect[mode][0]]->sel->args[i]&=0xFF;
						BEGraphs[subselect[mode][0]]->sel->args[i]|=lo;
					} else {
						lo = lo&0xFF;
						BEGraphs[subselect[mode][0]]->sel->args[i]&=0xFF00;
						BEGraphs[subselect[mode][0]]->sel->args[i]|=lo;
					}
					break;
			}
		}
	}

	if(c=='z'){
		BEGraphs[subselect[mode][0]]->graphzoom*=2;
		if(BEGraphs[subselect[mode][0]]->graphzoom==16)BEGraphs[subselect[mode][0]]->graphzoom=1;
	}