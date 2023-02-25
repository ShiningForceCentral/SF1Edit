struct SBDecompressor{
	FILE * file;
	unsigned int Barrel;
	unsigned char Length;
	unsigned int Pos;
	unsigned char Count;
	unsigned int Width;
	unsigned char temp[2];
	unsigned int itemp;
	bool walk;

	bool * Data;

	SBDecompressor(FILE * fp){
		file = fp;
	}

	void GetData(unsigned int width,unsigned int size, bool * data, unsigned int bar=0, unsigned int len=0){
		Length = len;
		Count = 0;
		Pos = 0;
		Width=width;
		Data=data;
		Barrel=bar;
		walk = GetBit();
		//Data[Pos++]=walk;
		while(Pos<size){
			Count=1;
			while(!GetBit())Count++;
			RepeatLast();
			walk=!walk;
		}
	}

	bool GetBit(){
		CheckBarrel();
		bool ret = (0x8000&Barrel);
		Barrel*=2;
		Barrel%=0x10000;
		Length--;
		return ret;
	}

	void CheckBarrel(){
		if(!Length){
			Barrel = readword();
			Length = 16;
		}
	}

	void RepeatLast(){
		unsigned int d1,d2,d3;
		d1=0;
		d2=2;
		d3=0;
		Count--;
		if(GetBit())d1+=1;
		while(Count){
			d1=d1<<1;
			if(GetBit())d1+=1;
			d1=d1<<1;
			if(GetBit())d1+=1;
			d3+=d2;
			d2=d2<<2;
			Count--;
		}
		d1+=d3;
		d1++;
		for(int i=0;i<d1;i++){
			Data[Pos]=walk;
			Pos++;
		}
	}

	unsigned long readword(){
		unsigned long t;
		fscanf(file,"%c%c",&(temp[0]),&(temp[1]));
		t=temp[0];
		t*=256;
		t+=temp[1];
		return t;
	}
};

struct SBCompressor{
	FILE * file;
	unsigned int Barrel;
	unsigned char Length;
	unsigned int Pos;
	unsigned char Count;
	unsigned int Width;
	unsigned char temp[2];
	unsigned int itemp;
	unsigned int DataPos;
	unsigned int Repeat;
	bool walk;
	bool finish;

	bool * Data;

	SBCompressor(FILE * fp, bool fin=true){
		file = fp;
		finish = fin;
	}

	int PutData(unsigned int width,unsigned int size, bool * data, unsigned int bar=0, unsigned int len=0){
		Length = len;
		Count = 0;
		Pos = 0;
		DataPos = 0;
		Repeat = 0;
		Width=width;
		Data=data;
		Barrel=bar;

		walk = Data[Pos++];

		if(walk)
			PutBit(1);
		else
			PutBit(0);

		while(Pos<size){
			if(Data[Pos]==walk){
				Repeat++;
			} else {
				RepeatLast();
				walk=!walk;
			}
			Pos++;
		}
		if(Repeat)RepeatLast();
		if(Length&&finish){
			if(Length<9){
				Barrel=Barrel<<(16-Length);
				fprintf(file,"%c",(Barrel&0xFF00)/0x100);
				DataPos++;
			} else {
				Barrel=Barrel<<(16-Length);
				fprintf(file,"%c",(Barrel&0xFF00)/0x100);
				fprintf(file,"%c",Barrel%0x100);
				DataPos+=2;
			}
		}
		return DataPos;
	}

	void PutBit(char c){
		Barrel=Barrel<<1;
		if(c)Barrel++;
		Length++;
		if(Length==16){
			Length=0;
			fprintf(file,"%c",(Barrel&0xFF00)/0x100);
			fprintf(file,"%c",Barrel%0x100);
			Barrel=0;
			DataPos+=2;
		}
	}

	void RepeatLast(){
		int t=2;
		int t2=8;
		int t3=0;
		int t4=0;
		Repeat++;
		while(Repeat>t){
			t4=t;
			t+=t2;
			t2*=4;
			t3++;
		}
		for(int i=0;i<t3;i++){
			PutBit(0);
		}
		PutBit(1);
		Repeat-=t4+1;
		t2=1<<(t3*2);
		for(int i=0;i<=2*t3;i++){
			if(t2&Repeat)
				PutBit(1);
			else
				PutBit(0);
			t2=t2>>1;
		}

		Repeat=0;
	}
};