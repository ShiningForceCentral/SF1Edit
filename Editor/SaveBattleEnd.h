int WriteNode(FILE * fp, BEGraphNode * node, int script){

	if (node->visited && node->type->shape != 3) {
		long o = ftell(fp) + 2;
		long d = node->offset - o;

		if (d < 0) {
			d = d;
		}

		fprintf(fp, "%c", 0x60);
		fprintf(fp, "%c", 0x0);
		fprintf(fp, "%c", (d & 0xFF00) >> 8);
		fprintf(fp, "%c", (d & 0xFF));


		//MessageBox(hwnd, "Infinite Loop Detected. Remove the loop and save again. (Note that closing without correcting may result in data loss.)","Error",MB_OK);
		//return -10000;
		return -10001;
	}
	node->visited = true;

	int type = node->type-nodeTypesBE;

	int pat=-1;
	int t,a,v,k,u,l;

	int ret=0;

	if(type){
		if(node->type->shape==3)pat=NumBEPatterns-1;
		else for(int i=0;i<512;i++){
			if(BEPatternNodes[i]==type){
				pat=i;
				break;
			}
		}

		if(pat==-1)
			return 0;

		if(!strcmp(node->type->name,"Display Message From ID")){
			if(node->args[0]==0)pat++;
		}

		if(!strcmp(node->type->name,"Display Message")){
			if(node->args[0]==-1)pat++;
		}

		a=0;

		long o = ftell(fp);
		LLNode<BEGraphNode*>* cur2 = BEGraphs[script]->nodes.head;
		while (cur2) {

			if (cur2->data->branch == node->offset) {
				cur2->data->branch = -o;

			}
			if (cur2->data->branch2 == node->offset) {
				cur2->data->branch2 = -o;

			}

			cur2 = cur2->next;
		}

		node->offset = o;

		for(int i=0;i<BELength[pat];i++){
			t = BEPatterns[pat][i];
			if(t>=0){
				fprintf(fp,"%c",t);
			} else {
				ret = t;
				switch(t){
					case -21:
						v = node->args[a];
						//ret = -21;
						break;
					case -6:
						i++;
						v = BEPatterns[pat][i];
						break;
					case -12:
						i++;
						v = BEPatterns[pat][i];
						if(node->args[a])v = node->args[a];
						break;
					default:
						v = node->args[a];
						if(t==-12&&v==0x59)
							t=t;
						break;
				}

				k = -1*t;
				k=k%4;
				if(!k)k=4;

				u = 0x00FF << (8 * (k-1));

				for(int j=0;j<k;j++){
					l = (v&u) >> (8*(k-j-1));
					fprintf(fp,"%c", l);
					u = u / 0x0100;
				}

				a++;
			}
		}
	}
	return ret;
}

bool WriteBEGraphLine(FILE * fp, int script, BEGraphNode * start=0){

	if (!start)BEGraphs[script]->clearVisited();

	int t;
	long o,o2;

	BEGraphNode * cur;
	if(start)cur = start;
	else cur = BEGraphs[script]->nodes.tail->data;

	while(cur){

		t = WriteNode(fp,cur, script);

		if (t == -10000) {
			if (BEGraphs[script]->sel)BEGraphs[script]->sel->selected = false;
			cur->selected = true;
			cur->selout = false;
			BEGraphs[script]->sel = cur;
			BEGraphs[script]->vx = cur->x - BEGraphs[script]->w / 2;
			BEGraphs[script]->vy = cur->y - BEGraphs[script]->h / 2;
			return false;
		}

		if (t == -10001)return true;

		if(cur->out.size>1){
			if(t==-1){
				fseek(fp,-1,SEEK_CUR);
				fprintf(fp,"%c",0);
				o = ftell(fp);
			} else {
				o = ftell(fp) - 2;
			}
			if(o==0x1C432E)
				o=o;
			if (!WriteBEGraphLine(fp, script, cur->out.tail->data))return false;
			o2 = ftell(fp);

			//write jump offset?
			fseek(fp,o,SEEK_SET);
			fprintf(fp,"%c",((o2 - o)&0x00FF00)/0x100);
			fprintf(fp,"%c",((o2 - o)&0x00FF));
			fseek(fp,o2,SEEK_SET);

		}

		if(cur->out.size){
			cur=cur->out.head->data;
		}
		else cur = 0;
	}
	return true;
}

void SaveBE(){
	if(!strlen(file)){
		int ret=IDYES;
		OPENFILENAME openFileName;
		char path[256];
		path[0] = '\0';    
		memset( &openFileName, 0, sizeof(openFileName) );
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.hwndOwner = NULL;
		openFileName.hInstance = NULL;
		openFileName.lpstrFilter = "Genesis ROM(*.bin)\0*.bin\0";
		openFileName.lpstrCustomFilter = NULL;
		openFileName.nMaxCustFilter = 0;
		openFileName.nFilterIndex = 0;
		openFileName.lpstrFile =  path;
		openFileName.nMaxFile = 256;
		openFileName.lpstrFileTitle = NULL;
		openFileName.nMaxFileTitle = 0;
		openFileName.lpstrInitialDir = ".";
		openFileName.lpstrTitle = NULL;
		openFileName.Flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST;
		openFileName.nFileOffset = 0;
		openFileName.nFileExtension = 0;
		openFileName.lpstrDefExt = "bin";
		openFileName.lCustData = NULL;
		openFileName.lpfnHook = NULL;
		openFileName.lpTemplateName = NULL;

		if(GetOpenFileName(&openFileName)!=0){
			sprintf(file,path);
		}
	}

	int i,j;
	
	if(strlen(file)){


		FILE * fp = fopen(file,"rb+");

		if(0x1D8000>romsize){
			MessageBox(NULL,"Rom is too small, expand rom to save Battle End changes.","Error",MB_OK);
			fclose(fp);
			return;
		}
		
		//header code changes? **
		fseek(fp,0x12A4E6,SEEK_SET);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0xF9);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1D);
		fprintf(fp,"%c",0x89);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0x71);

		fseek(fp,0x1D8900,SEEK_SET);
		fprintf(fp,"%c",0x30);
		fprintf(fp,"%c",0x3B);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1E);
		fprintf(fp,"%c",0x4E);
		fprintf(fp,"%c",0xFB);
		fprintf(fp,"%c",0x00);
		fprintf(fp,"%c",0x1A);

		BEHeaderOffset = 0x1D8920;

		long o = BEHeaderOffset;
		long o2;

		//script code changes?

		o2 = 0x1D8960;
		
		for(i=0; i<NUM_BE; i++){
			BEGraphs[i]->fillEnds();

			fseek(fp,o,SEEK_SET);
			BEHeader[i] = o2 - BEHeaderOffset;
			fprintf(fp,"%c",(BEHeader[i]&0xFF00)/0x100);
			fprintf(fp,"%c",BEHeader[i]&0x00FF);
			o+=2;
			fseek(fp,o2,SEEK_SET);
			//write BE script

			if(!WriteBEGraphLine(fp,i)) {
				fclose(fp);
				return;
			}

			o2 = ftell(fp);
		}

		fclose(fp);
		MessageBox(NULL,"Battle Ends Saved","Note",MB_OK);
	}
}

void ExportBE(char*path){
	FILE * fp = fopen(path,"wb");



	fclose(fp);
	MessageBox(NULL,"BE Exported","Note",MB_OK);
}

void BEExport(){
	/*
	OPENFILENAME openFileName;
	char path[256];
	path[0] = '\0';  
	memset( &openFileName, 0, sizeof(openFileName) );
	openFileName.lStructSize = sizeof(openFileName);
	openFileName.hwndOwner = NULL;
	openFileName.hInstance = NULL;
	openFileName.lpstrFilter = "Shining Force Maps(*.sfma)\0*.sfma\0";
	openFileName.lpstrCustomFilter = NULL;
	openFileName.nMaxCustFilter = 0;
	openFileName.nFilterIndex = 0;
	openFileName.lpstrFile =  path;
	openFileName.nMaxFile = 256;
	openFileName.lpstrFileTitle = NULL;
	openFileName.nMaxFileTitle = 0;
	openFileName.lpstrInitialDir = ".";
	openFileName.lpstrTitle = NULL;
	openFileName.Flags = OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	openFileName.nFileOffset = 0;
	openFileName.nFileExtension = 0;
	openFileName.lpstrDefExt = "sfna";
	openFileName.lCustData = NULL;
	openFileName.lpfnHook = NULL;
	openFileName.lpTemplateName = NULL;

	if(GetSaveFileName(&openFileName)!=0){
		ExportMap(path);
	}*/
}