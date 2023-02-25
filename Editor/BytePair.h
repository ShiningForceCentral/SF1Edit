struct BPDecompressor{
	FILE * file;
	unsigned int Barrel;
	unsigned char Length;
	unsigned int Pos;
	unsigned int Last;
	unsigned char Count;
	unsigned int Width;
	unsigned char temp[2];
	unsigned int itemp;
	bool skip;

	unsigned int * Data;

	BPDecompressor(FILE * fp){
		file = fp;
	}

	void GetData(unsigned int width,unsigned int size, unsigned int * data){
		Length = 0;
		Count = 0;
		Pos = 0;
		skip=false;
		Width=width;
		Data=data;
		Last=0;
		while(Pos<size){
			if(skip){
				Count=0;
				skip=false;
			} else
				while(!GetBit())Count++;
			if(Count)
				RepeatLast();
			else {
				if(GetBit())
					ConsecutiveData();
				else {
					if(GetBit())
						OffsetAbove();
					else RawData();
				}
			}
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

	void RawData(){
		unsigned char bits;
		if(Length>=10){
			itemp = Barrel&0xFFC0;
			Barrel=Barrel<<10;
			Barrel%=0x10000;
			itemp=itemp>>6;
			itemp&=0x3FF;
			Last = itemp;
			Data[Pos]=itemp;
			Pos++;
			Length-=10;
		} else {
			Barrel=Barrel>>(16-Length);
			itemp = Barrel;//Barrel&0x03FF;
			bits=10-Length;
			Length=0;
			CheckBarrel();
			for(int i=0;i<bits;i++){
				itemp*=2;
				if(GetBit())itemp++;
			}
			itemp&=0x3FF;
			Last = itemp;
			Data[Pos]=itemp;
			Pos++;
		}
	}

	void RepeatLast(){
		unsigned int d1,d2,d3;
		d1=0;
		d2=1;
		d3=0;
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
		for(int i=0;i<d1;i++){
			Data[Pos]=Last;
			Pos++;
		}
		skip=true;
	}

	void ConsecutiveData(){
		if(GetBit()){
			if(GetBit()){
				itemp=-1;
			} else {
				itemp=-2;
			}
		} else{
			if(GetBit()){
				itemp=2;
			} else {
				itemp=1;
			}
		}
		Last+=itemp;
		Data[Pos]=Last;
		Pos++;
	}

	void OffsetAbove(){
		bool neg;
		itemp=0;
		neg = GetBit();

		if(GetBit())itemp++;
		itemp*=2;
		if(GetBit())itemp++;
		itemp*=2;
		if(GetBit())itemp++;
		if(neg)itemp-=8;
		Last = Data[Pos-Width];
		Last+=itemp;
		Data[Pos]=Last;
		Pos++;
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

struct BPCompressor{
	FILE * file;
	unsigned int Barrel;
	unsigned char Length;
	unsigned int Pos;
	unsigned int Last;
	unsigned char Count;
	unsigned int Width;
	unsigned char temp[2];
	unsigned int itemp;
	unsigned int DataPos;
	unsigned int Repeat;
	bool skip;
	bool finish;

	unsigned int * Data;

	BPCompressor(FILE * fp, bool fin=true){
		file = fp;
		finish = fin;
	}

	int PutData(unsigned int width,unsigned int size, unsigned int * data, unsigned int bar=0, unsigned int len=0){
		Length = len;
		Count = 0;
		Pos = 0;
		DataPos = 0;
		Repeat = 0;
		skip=false;
		Width=width;
		Data=data;
		Barrel=bar;
		Last=0;

		while(Pos<size){
			if(Data[Pos]==Last){
				Repeat++;
			} else {
				if(Repeat)RepeatLast();
				else skip=false;

				if(abs(GetDiff(1))<3){
					ConsecutiveData();
				} else {
					if(GetDiff(Width)>-9&&GetDiff(Width)<8){
						OffsetAbove();
					} else {
						RawData();
					}
				}
			}
			Last=Data[Pos];
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
			if(Barrel%0x1000==0xC001)
				Barrel=0;
			Barrel=0;
			DataPos+=2;
		}
	}

	void PutByte(char c){
		for(int i=0;i<8;i++){
			if(c&0x80)PutBit(1);
			else PutBit(0);
			c=c<<1;
		}
	}

	/*void PutWord(int i){
		PutByte((i&0xFF00)/0x100);
		PutByte(i%0x100);
	}*/

	void RepeatLast(){
		int t=4;
		int t2=16;
		int t3=1;
		int t4=0;
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
		t2=1<<(t3*2-1);
		for(int i=0;i<2*t3;i++){
			if(t2&Repeat)
				PutBit(1);
			else
				PutBit(0);
			t2=t2>>1;
		}

		Repeat=0;
		skip=true;
	}

	void ConsecutiveData(){
		if(!skip)PutBit(1);
		PutBit(1);
		switch(GetDiff(1)){
			case 1:
				PutBit(0);
				PutBit(0);
				break;
			case 2:
				PutBit(0);
				PutBit(1);
				break;
			case -1:
				PutBit(1);
				PutBit(1);
				break;
			case -2:
				PutBit(1);
				PutBit(0);
				break;
		}
	}

	void OffsetAbove(){
		if(!skip)PutBit(1);
		PutBit(0);
		PutBit(1);
		switch(GetDiff(Width)){
			case 0:
				PutBit(0);
				PutBit(0);
				PutBit(0);
				PutBit(0);
				break;
			case 1:
				PutBit(0);
				PutBit(0);
				PutBit(0);
				PutBit(1);
				break;
			case 2:
				PutBit(0);
				PutBit(0);
				PutBit(1);
				PutBit(0);
				break;
			case 3:
				PutBit(0);
				PutBit(0);
				PutBit(1);
				PutBit(1);
				break;
			case 4:
				PutBit(0);
				PutBit(1);
				PutBit(0);
				PutBit(0);
				break;
			case 5:
				PutBit(0);
				PutBit(1);
				PutBit(0);
				PutBit(1);
				break;
			case 6:
				PutBit(0);
				PutBit(1);
				PutBit(1);
				PutBit(0);
				break;
			case 7:
				PutBit(0);
				PutBit(1);
				PutBit(1);
				PutBit(1);
				break;
			case -1:
				PutBit(1);
				PutBit(1);
				PutBit(1);
				PutBit(1);
				break;
			case -2:
				PutBit(1);
				PutBit(1);
				PutBit(1);
				PutBit(0);
				break;
			case -3:
				PutBit(1);
				PutBit(1);
				PutBit(0);
				PutBit(1);
				break;
			case -4:
				PutBit(1);
				PutBit(1);
				PutBit(0);
				PutBit(0);
				break;
			case -5:
				PutBit(1);
				PutBit(0);
				PutBit(1);
				PutBit(1);
				break;
			case -6:
				PutBit(1);
				PutBit(0);
				PutBit(1);
				PutBit(0);
				break;
			case -7:
				PutBit(1);
				PutBit(0);
				PutBit(0);
				PutBit(1);
				break;
			case -8:
				PutBit(1);
				PutBit(0);
				PutBit(0);
				PutBit(0);
				break;
		}
	}

	void RawData(){
		if(!skip)PutBit(1);
		PutBit(0);
		PutBit(0);
		int t2;
		t2=1<<9;
		for(int i=0;i<10;i++){
			if(t2&Data[Pos])PutBit(1);
			else PutBit(0);
			t2=t2>>1;
		}
	}

	int GetDiff(int offset){
		if(offset>Pos&&offset>1)return 65536;
		if(offset>Pos)return Data[Pos];
		return Data[Pos]-Data[Pos-offset];
	}
};