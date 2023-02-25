struct ULDecompressor{
	FILE * file;
	unsigned int Barrel;
	unsigned char Length;
	unsigned int Pos;
	unsigned char x,y,w,h;
	unsigned char tile;
	unsigned char flag;
	unsigned char temp[2];

	ULDecompressor(FILE * fp){
		file = fp;
	}

	void GetData(int mapnum,unsigned char width, unsigned int size, unsigned char * flags, unsigned char * flags2, unsigned char * event, unsigned char * group, char * data, unsigned int bar=0, unsigned int len=0){
		Length = len;
		Pos = 0;
		Barrel=bar;
		while(true){
			y = GetByte();
			if(y==0xFF)break;
			x = GetByte();
			h = GetByte();
			w = GetByte();
			Pos = x+y*width;

			flag = 0;
			if(GetBit())flag++;
			flag*=2;
			if(GetBit())flag++;

			for(y=0;y<=h;y++){
				for(x=0;x<=w;x++){
					tile = 0;
					if(GetBit())tile++;
					tile*=2;
					if(GetBit())tile++;
					tile*=2;
					if(GetBit())tile++;
					tile*=2;
					if(GetBit())tile++;
					flags[Pos+x+y*width]=flag;
					flags2[Pos+x+y*width]=tile;
				}
			}
		}
		while(true){
			y = GetByte();
			if(y==0xFF)break;
			x = GetByte();
			h = GetByte();
			w = GetByte();
			Pos = x+y*width;

			flag = 0;
			if(GetBit())flag++;
			flag*=2;
			if(GetBit())flag++;
			flag*=2;
			if(GetBit())flag++;

			for(y=0;y<=h;y++){
				for(x=0;x<=w;x++){
					tile = 0;
					if(GetBit())tile++;
					tile*=2;
					if(GetBit())tile++;
					tile*=2;
					if(GetBit())tile++;
					tile*=2;
					if(GetBit())tile++;
					tile*=2;
					if(GetBit())tile++;
					tile*=2;
					if(GetBit())tile++;
					group[Pos+x+y*width]=flag;
					data[Pos+x+y*width]=tile;
				}
			}
		}
		Pos = 0;
		if(Length>=8){
			fseek(file,-1,SEEK_CUR);
		}

		

		fscanf(file,"%c",&flag);
		Pos+=flag;
		while(Pos<size){
			if(flag!=0xFF){
				fscanf(file,"%c",&flag);
				event[Pos]=flag;
				Pos+=1;
			}
			fscanf(file,"%c",&flag);
			Pos+=flag;
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

	unsigned char GetByte(){
		unsigned char c=0;
		for(int i=0;i<8;i++){
			c*=2;
			if(GetBit())c++;
		}
		return c;
	}

	void CheckBarrel(){
		if(!Length){
			Barrel = readword();
			Length = 16;
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

struct ULCompressor{
	FILE * file;
	unsigned int Barrel;
	unsigned char Length;
	unsigned int Pos;
	unsigned int DataPos;
	unsigned char flag;
	unsigned char tile;
	unsigned int Width;
	unsigned char temp[2];
	bool finish;

	ULCompressor(FILE * fp, bool fin=true){
		file = fp;
		finish = fin;
	}

	int PutData(unsigned int width,unsigned int size, unsigned char * flags, unsigned char * flags2, unsigned char * event, unsigned char * group, char * data, unsigned int bar=0, unsigned int len=0){
		unsigned char x,y,w,h;
		Length = len;
		Pos = 0;
		DataPos=0;
		Barrel=bar;

		unsigned char ctemp[4096];
		unsigned char i;

		memcpy(ctemp,flags,4096);

		if(width)
		for(y=0;y<size/width;y++){
			for(x=0;x<width;x++){
				if(ctemp[x+y*width]){
					PutByte(y);
					PutByte(x);
					w=0;
					h=0;
					while(w<width&&ctemp[x+y*width+(w+1)]==ctemp[x+y*width]){
						w++;
					}
					while(y+h<size/width){
						for(i=0;i<=w;i++){
							if(ctemp[x+(y+h+1)*width+(i+1)]!=ctemp[x+y*width]){
								i=w*2;
								break;
							}
						}
						if(i==w*2)break;
						h++;
					}
					PutByte(h);
					PutByte(w);

					if(ctemp[x+y*width]&0x02)
						PutBit(1);
					else
						PutBit(0);

					if(ctemp[x+y*width]&0x01)
						PutBit(1);
					else
						PutBit(0);

					for(unsigned char j=0;j<=h;j++){
						for(unsigned char i=0;i<=w;i++){
							ctemp[x+(y+j)*width+(i)]=0;

							if(flags2[x+(y+j)*width+(i)]&0x08)
								PutBit(1);
							else
								PutBit(0);

							if(flags2[x+(y+j)*width+(i)]&0x04)
								PutBit(1);
							else
								PutBit(0);

							if(flags2[x+(y+j)*width+(i)]&0x02)
								PutBit(1);
							else
								PutBit(0);

							if(flags2[x+(y+j)*width+(i)]&0x01)
								PutBit(1);
							else
								PutBit(0);
						}
					}
				}
			}
		}

		PutByte(0xFF);

		memcpy(ctemp,group,4096);

		if(width)
		for(y=0;y<size/width;y++){
			for(x=0;x<width;x++){
				if(ctemp[x+y*width]){
					PutByte(y);
					PutByte(x);
					w=0;
					h=0;
					while(w<width&&ctemp[x+y*width+(w+1)]==ctemp[x+y*width]){
						w++;
					}
					while(y+h<size/width){
						for(i=0;i<=w;i++){
							if(ctemp[x+(y+h+1)*width+(i+1)]!=ctemp[x+y*width]){
								i=w*2;
								break;
							}
						}
						if(i==w*2)break;
						h++;
					}
					PutByte(h);
					PutByte(w);

					if(ctemp[x+y*width]&0x04)
						PutBit(1);
					else
						PutBit(0);

					if(ctemp[x+y*width]&0x02)
						PutBit(1);
					else
						PutBit(0);

					if(ctemp[x+y*width]&0x01)
						PutBit(1);
					else
						PutBit(0);

					for(unsigned char j=0;j<=h;j++){
						for(unsigned char i=0;i<=w;i++){
							ctemp[x+(y+j)*width+(i)]=0;

							if(data[x+(y+j)*width+(i)]&0x20)
								PutBit(1);
							else
								PutBit(0);

							if(data[x+(y+j)*width+(i)]&0x10)
								PutBit(1);
							else
								PutBit(0);

							if(data[x+(y+j)*width+(i)]&0x08)
								PutBit(1);
							else
								PutBit(0);

							if(data[x+(y+j)*width+(i)]&0x04)
								PutBit(1);
							else
								PutBit(0);

							if(data[x+(y+j)*width+(i)]&0x02)
								PutBit(1);
							else
								PutBit(0);

							if(data[x+(y+j)*width+(i)]&0x01)
								PutBit(1);
							else
								PutBit(0);
						}
					}
				}
			}
		}

		PutByte(0xFF);

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

		Length=0;

		for(Pos=0;Pos<size;Pos++){
			if(event[Pos]){
				fprintf(file,"%c",Length);
				fprintf(file,"%c",event[Pos]);
				DataPos+=2;
				Length=0;
			} else {
				Length++;
				if(Length==0xFF){
					Length=0;
					fprintf(file,"%c",0xFF);
					DataPos++;
				}
			}
		}
		if(Length)fprintf(file,"%c",Length);
		DataPos++;
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

	void PutByte(char c){
		for(int i=0;i<8;i++){
			if(c&0x80)PutBit(1);
			else PutBit(0);
			c=c<<1;
		}
	}
};
