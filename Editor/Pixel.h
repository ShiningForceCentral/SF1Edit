struct PixelDecompressor{
	FILE * file;
	unsigned long Barrel;
	unsigned char Length;
	unsigned int Pos;
	unsigned int Pos2;
	unsigned int Count;

	char * Data;
	unsigned int width;
	unsigned int height;
	unsigned int size;
	char last;
	bool ret;

	PixelDecompressor(FILE * fp){
		file = fp;
		Data = new char[65536];
	}

	int GetData(unsigned int offset, char ** data, unsigned int w=0, unsigned int h=0){
		Length = 0;
		Pos = -1;
		Pos2 = 0;
		Barrel=0;

		fseek(file,offset,SEEK_SET);

		width = 0;
		height = 0;

		if(!w)fscanf(file,"%c",&width);
		else width=w;
		if(!h)fscanf(file,"%c",&height);
		else height=h;

		width*=8;
		height*=8;

		size = width*height;

		//*data = new char[size];
		//Data=*data;
		*data = Data;

		memset(Data,0xFF,size);

		bool bit;
		char c;
		bool restart;
		int shift;

		while(Pos<size||Pos==-1||Pos==4294967295){
			restart=false;
			Count = -1;
			shift=2;
			do{
				//bit = GetBit();

				if (!Length) {
					*(((char*)&Barrel) + 1) = fgetc(file);
					*(((char*)&Barrel)) = fgetc(file);
					//fscanf(file, "%c%c", ((char*)&Barrel) + 1, ((char*)&Barrel));
					Length = 16;
				}
				bit = (0x8000 & Barrel);
				Barrel = Barrel << 1;
				//Barrel &= 0xFFFF;// %= 0x10000;
				Length--;

				Count++;
			} while(!bit);

			shift=shift<<Count;
			Pos+=shift-2;

			Count++;

			if(Count){
				Pos+=GetBits(Count);
			}
			if(Pos>=size)
				return size;

			c = GetBits(4);
			c &= 0xF;

			Data[Pos]=c;
			last=c;
			if(GetBit()){
				Pos2=Pos;
				while(!restart){
					if(GetBit())CopyDownBitRight();
					else if(GetBit())CopyDownLeft(1);
					else if(GetBit()){
						if(GetBit())CopyDownRight(2);
						else CopyDownLeft(2);
					}
					else restart=true;
				}
			}
		}
		return size;
	}

	int GetRawData(unsigned int offset, char ** data){
		Pos = 0;

		fseek(file,offset,SEEK_SET);

		fscanf(file,"%c",&width);
		fscanf(file,"%c",&height);

		width*=8;
		height*=8;

		size = width*height;

		*data = new char[size];
		Data=*data;

		memset(Data,0xFF,size);

		while(Pos<size){
			Data[Pos]=GetBits(4);
			Pos++;
		}
		return size;
	}

	void CopyDownBitRight(){
		Pos2+=width;
		if(GetBit())Pos2++;
		if(Pos2<size)Data[Pos2]=last;
	}

	void CopyDownRight(int off){
		Pos2+=width;
		Pos2+=off;
		if(Pos2<size)Data[Pos2]=last;
	}

	void CopyDownLeft(int off){
		Pos2+=width;
		Pos2-=off;
		if(Pos2<size)Data[Pos2]=last;
	}

	inline bool GetBit(){
		if (!Length) {
			//Barrel = readword();
			*(((char*)&Barrel) + 1) = fgetc(file);
			*(((char*)&Barrel)) = fgetc(file);


			Length = 16;
		}
		ret = (0x8000&Barrel);
		Barrel = Barrel << 1;
		//Barrel &= 0xFFFF;// %= 0x10000;
		Length--;
		return ret;
	}

	inline int GetBits(int len){
		static int c;
		static char i;
		c = 0;

		if (Length >= len) {
			for (i = 0;i<len;i++) {
				c = c << 1;

				if (0x8000 & Barrel)c++;
				Barrel = Barrel << 1;
				//Barrel &= 0xFFFF;// %= 0x10000;
			}
			Length -= len;
			return c;
		}

		len -= Length;

		for(i=0;i<Length;i++){
			c=c<<1;

			if (0x8000 & Barrel)c++;
			Barrel = Barrel<<1;
			//Barrel &= 0xFFFF;// %= 0x10000;
		}

		*(((char*)&Barrel) + 1) = fgetc(file);
		*(((char*)&Barrel)) = fgetc(file);

		Length = 16-len;

		for (i = 0;i<len;i++) {
			c = c << 1;

			if (0x8000 & Barrel)c++;
			Barrel = Barrel << 1;
			//Barrel &= 0xFFFF;// %= 0x10000;
		}

		return c;
	}

	inline void CheckBarrel(){
		if(!Length){
			//Barrel = readword();
			fscanf(file, "%c%c", ((char*)&Barrel) + 1, ((char*)&Barrel));
			Length = 16;
		}
	}

	inline unsigned long readword(){
		static unsigned long t;
		fscanf(file,"%c%c",((char*)&t)+1,((char*)&t));
		return t;
	}
};

struct PixelCompressor{
	FILE * file;
	unsigned int Barrel;
	unsigned char Length;
	unsigned int Pos, Pos2;
	unsigned char Count;
	unsigned int Width;
	unsigned char temp[2];
	unsigned int itemp;
	unsigned int DataPos;
	unsigned int Repeat;

	unsigned char * Data;
	unsigned char Last;
	int found;
	unsigned int size;

	PixelCompressor(FILE * fp){
		file = fp;
	}

	int PutData(unsigned int width,unsigned int Size, unsigned char * data, bool putSize=true, char zero=0, char one=1){
		Length = 0;
		Count = 0;
		Pos = 0;
		Pos2 = 0;
		DataPos = 2;
		Repeat = 0;
		Width=width;
		Data=data;
		Barrel=0;
		size=Size;

		Data = new unsigned char[size];
		for(int i=0;i<size;i++){
			Data[i]=data[i];
			if(Data[i]==0)Data[i]=zero;
			else if(Data[i]==1)Data[i]=one;
		}

		if(putSize){
			fprintf(file,"%c",Width/8);
			fprintf(file,"%c",(size/Width)/8);
		}

		PutBit(1);
		PutBit(1);

		while(Pos<size){
			found=0;
			PutPixel(Data[Pos]);

			Pos2=Pos;

			int t;

			do{
				t=Search(found);
				if(t&&found==0)found=1;
				if(!t&&found==1)found=2;
			} while(found==1);

			if(found){
				PutBit(0);
				PutBit(0);
			}
			if(Data[Pos+1]==Last||Data[Pos+1]==0xFF){
				Pos2=Pos+1;
				if(Data[Pos2]==0xFF)Last=data[Pos2];
				Repeat=1;
				while((Data[Pos2]==Last||Data[Pos2]==0xFF)&&Pos2<size){
					if(Data[Pos2]==0xFF)Last=data[Pos2];
					Data[Pos2]=0xFF;
					Pos2++;
					Repeat++;
				}
				Pos=Pos2;
				PutBit(0);
				RepeatLast();
				found=0;
			} else {
				PutBit(0);
				PutBit(1);
				PutBit(1);
				Pos++;
				Pos2=Pos;
			}

		}
		if(Length){
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
		delete Data;
		return DataPos;
	}

	bool Search(int f){
		if(Pos2+Width-1<size){
			if(Data[Pos2+Width-1]==Last&&Data[Pos2+Width-2]!=Last){
				if(!f)PutBit(1);
				CopyDownLeft(1);
				return true;
			}
		}
		/*if(Pos2+Width<size){
			if(Data[Pos2+Width]==Last&&Data[Pos2+Width-1]!=Last){
				if(!f)PutBit(1);
				CopyDownBitRight(false);
				return true;
			}
		}*/
		/*if(Pos2+Width+1<size){
			if(Data[Pos2+Width+1]==Last&&Data[Pos2+Width]!=Last){
				if(!f)PutBit(1);
				CopyDownBitRight(true);
				return true;
			}
		}
		if(Pos2+Width-2<size){
			if(Data[Pos2+Width-2]==Last&&Data[Pos2+Width-3]!=Last){
				if(!f)PutBit(1);
				CopyDownLeft(2);
				return true;
			}
		}
		if(Pos2+Width+2<size){
			if(Data[Pos2+Width+2]==Last&&Data[Pos2+Width+1]!=Last){
				if(!f)PutBit(1);
				CopyDownRight(2);
				return true;
			}
		}
		*/
		return false;
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

	void PutPixel(char c){
		for(int i=0;i<4;i++){
			char b = c&8;
			b/=8;
			c=c<<1;
			PutBit(b);
		}
		Last = Data[Pos];
		Data[Pos]=0xFF;
		
	}

	void RepeatLast(){
		int t=2;
		int t2=2;
		int t3=0;
		int t4=0;
		while(Repeat>=t*2-2){
			t4=t;
			t+=t2;
			t2*=2;
			t3++;
		}
		int i;
		for(i=0;i<t3;i++){
			PutBit(0);
		}
		PutBit(1);
		Repeat-=t-2;
		t2=1<<(t3);
		for(i=0;i<=t3;i++){
			if(t2&Repeat)
				PutBit(1);
			else
				PutBit(0);
			t2=t2>>1;
		}

		Repeat=0;
	}

	void CopyDownBitRight(bool r){
		PutBit(1);
		Pos2+=Width;
		if(r){
			PutBit(1);
			Pos2++;
		} else PutBit(0);
		Data[Pos2]=0xFF;
	}

	void CopyDownRight(int off){
		if(off==1){
			PutBit(1);
			PutBit(1);
		}
		if(off==2){
			PutBit(0);
			PutBit(0);
			PutBit(1);
			PutBit(1);
		}
		Pos2+=Width;
		Pos2+=off;
		Data[Pos2]=0xFF;
	}

	void CopyDownLeft(int off){
		if(off==1){
			PutBit(0);
			PutBit(1);
		}
		if(off==2){
			PutBit(0);
			PutBit(0);
			PutBit(1);
			PutBit(0);
		}
		Pos2+=Width;
		Pos2-=off;
		Data[Pos2]=0xFF;
	}
};