
struct BasicDecompressor{
	
	FILE * fp;
	char barrel[17];
	long raw_barrel;
	long operand,repeat,offset,idx;
	char data[4096];
	char temp[17];
	char temp2[17];

	BasicDecompressor(FILE * file) : fp(file) {}

	char * GetData(long address){
		bool done=false;
		sprintf(data,"");

		fseek(fp,address,SEEK_SET);

		while(!done){
			raw_barrel = readword();
			itoa(raw_barrel,temp,2);
			strncpy(barrel,"0000000000000000",16-strlen(temp));
			barrel[16-strlen(temp)]=0;
			sprintf(barrel,"%s%s",barrel,temp);
			for(int i=0;i<strlen(barrel);i++){
				operand = readword();
				if(barrel[i]=='1'){
					if(!operand){
						done=true;
						break;
					}
					repeat = operand & 0x1F;
					offset = (operand - repeat) / 16;
					repeat = 33 - repeat;

					//commands?

					if(repeat%2){
						idx = offset*-2;
						if(idx==-4)
							sprintf(data,"%s%s",data,data+strlen(data)-4);
						else {
							strncpy(temp,data+strlen(data)-idx,4);
							temp[4]=0;
							sprintf(data,"%s%s",data,temp);
						}
						repeat--;
					}

					repeat/=2;

					for(int j=0;j<repeat;j++){
						idx = offset*-2;
						if(idx==-4)
							sprintf(data,"%s%s%s",data,data+strlen(data)-4,data+strlen(data)-4);
						else {
							if(idx==-8)
								sprintf(data,"%s%s",data,data+strlen(data)-8);
							else {
								strncpy(temp,data+strlen(data)-idx,8);
								temp[8]=0;
								sprintf(data,"%s%s",data,temp);
							}
						}
					}
				} else {
					sprintf(temp,"%X",operand);
					strncpy(temp2,"0000",4-strlen(temp));
					temp2[4-strlen(temp)]=0;
					sprintf(data,"%s%s%s",data,temp2,temp);
				}
			}
		}
		return data;
	}

	unsigned long readlong(){
		unsigned long t;
		fscanf(fp,"%c%c%c%c",&(temp[0]),&(temp[1]),&(temp[2]),&(temp[3]));
		t=temp[0];
		t*=256;
		t+=temp[1];
		t*=256;
		t+=temp[2];
		t*=256;
		t+=temp[3];
		return t;
	}

	unsigned long readword(){
		unsigned long t;
		fscanf(fp,"%c%c",&(temp[0]),&(temp[1]));
		t=temp[0];
		t*=256;
		t+=temp[1];
		t%=0x10000;
		return t;
	}

};


struct StackDecompressor{
	
	FILE * fp;
	char barrel[17];
	long raw_barrel;
	long operand,repeat,offset,idx,start,total;
	char data[4096];
	char temp[17];
	char temp2[256];
	char cmd_ctr;
	char t;
	String pixels,tile_barrel, pixel_barrel, command, stemp, stemp2;
	LinkedList<char> pixel_stack;
	LLNode<char> * node;

	StackDecompressor(FILE * file) : fp(file) {}

	char * GetData(long address){
		bool done=false;
		sprintf(data,"");
		sprintf(barrel,"");
		pixels="";

		pixel_stack.clean();
		command = "FEDCBA9876543210";
		for(int l=0;l<command.length();l++){
			pixel_stack.add(command[l]);
		}

		fseek(fp,address,SEEK_SET);

		while(!done){
			cmd_ctr = 4;
			tile_barrel="";
			command="";
			while(cmd_ctr){
				if(!strlen(barrel)){
					raw_barrel = readword();
					itoa(raw_barrel,temp,2);
					strncpy(barrel,"0000000000000000",16-strlen(temp));
					barrel[16-strlen(temp)]=0;
					sprintf(barrel,"%s%s",barrel,temp);
				}
				while(strlen(barrel)){
					//for(int i=0;i<strlen(barrel);i++)
					command+=barrel[0];
					sprintf(barrel,"%s",barrel+1);
					if(command=="0") tile_barrel+="0";
					else if(command.left(2)=="10"&&command.length()==3){
						if(command[2]=='0')tile_barrel+="1";
						else tile_barrel+="2";
					} else if(command=="110"){
						tile_barrel+="4";
					} else if(command=="1110"){
						tile_barrel+="8";
					} else if(command.left(4)=="1111"&&command.length()==8){
						itoa(strtol(command.right(4),0,2),temp,16);
						tile_barrel+=temp;
					} else continue;

					cmd_ctr--;
					command="";
					if(!cmd_ctr)break;
				}
			}
			itoa(strtol(tile_barrel,0,16),temp2,2);
			sprintf(temp,"");
			strncpy(temp,"0000",4-strlen(temp2));
			temp[4-strlen(temp2)]=0;
			tile_barrel=temp;
			tile_barrel+=temp2;

			for(int j=0;j<strlen(tile_barrel);j++){
				cmd_ctr = 4;
				pixel_barrel="";
				if(tile_barrel[j]=='0'){
					while(cmd_ctr){
						if(!strlen(barrel)){
							raw_barrel = readword();
							itoa(raw_barrel,temp,2);
							strncpy(barrel,"0000000000000000",16-strlen(temp));
							barrel[16-strlen(temp)]=0;
							sprintf(barrel,"%s%s",barrel,temp);
						}
						while(strlen(barrel)){//for(int i=0;i<strlen(barrel);i++)
							command+=barrel[0];
							sprintf(barrel,"%s",barrel+1);
							if(command=="00"){

							} else if(command=="01"){
								node = pixel_stack[1];
								t = node->data;
								pixel_stack.remove(node);
								pixel_stack.add(t);
							} else if(command=="100"){
								node = pixel_stack[2];
								t = node->data;
								pixel_stack.remove(node);
								pixel_stack.add(t);
							} else if(command=="101"){
								node = pixel_stack[3];
								t = node->data;
								pixel_stack.remove(node);
								pixel_stack.add(t);
							} else if(command=="110"){
								node = pixel_stack[4];
								t = node->data;
								pixel_stack.remove(node);
								pixel_stack.add(t);
							} else if(command.left(3)=="111"&& (command.length()==10 || (command.length()%2==1 && command.find("0")) )){
								stemp = command.right(command.length()-3);
								stemp.reverse();
								int val=0;
								int tog=0;
								for(l=1;l<stemp.length();l++){
									stemp2=stemp[l];
									val+=atoi(stemp2)*(tog+1);
									tog^=1;
								}
								val+=5;
								stemp2=stemp[0];
								val+=atoi(stemp2);
								node = pixel_stack[val];
								t = node->data;
								pixel_stack.remove(node);
								pixel_stack.add(t);
							} else continue;
							pixel_barrel+=pixel_stack[0]->data;
							cmd_ctr--;
							command="";
							if(!cmd_ctr)break;
						}
					}
					pixels+=pixel_barrel;
				} else {
					cmd_ctr = 11;
					offset = 0;
					stemp = "";
					while(cmd_ctr){
						if(!strlen(barrel)){
							raw_barrel = readword();
							itoa(raw_barrel,temp,2);
							strncpy(barrel,"0000000000000000",16-strlen(temp));
							barrel[16-strlen(temp)]=0;
							sprintf(barrel,"%s%s",barrel,temp);
						}
						stemp+=barrel[0];
						sprintf(barrel,"%s",barrel+1);
						cmd_ctr--;
					}
					offset = strtol(stemp,0,2)*4;
					total=0;
					t='0';
					if(!offset){
						done = true;
						break;
					}
					start = pixels.length();
					while(t=='0'){
						if(!strlen(barrel)){
							raw_barrel = readword();
							itoa(raw_barrel,temp,2);
							strncpy(barrel,"0000000000000000",16-strlen(temp));
							barrel[16-strlen(temp)]=0;
							sprintf(barrel,"%s%s",barrel,temp);
						}

						pixels+=pixels.mid(pixels.length()-offset,4);
						total++;
						t=barrel[0];
						sprintf(barrel,"%s",barrel+1);
					}
					pixels+=pixels.mid(pixels.length()-offset,4);
				}
			}
		}
		FILE * tf = fopen("temp.bin","w+");
		fprintf(tf,pixels);
		fclose(tf);
		return data;
	}

	unsigned long readlong(){
		unsigned long t;
		fscanf(fp,"%c%c%c%c",&(temp[0]),&(temp[1]),&(temp[2]),&(temp[3]));
		t=temp[0];
		t*=256;
		t+=temp[1];
		t*=256;
		t+=temp[2];
		t*=256;
		t+=temp[3];
		return t;
	}

	unsigned long readword(){
		unsigned long t;
		fscanf(fp,"%c%c",&(temp[0]),&(temp[1]));
		t=temp[0];
		t*=256;
		t+=temp[1];
		t%=0x10000;
		return t;
	}

};


struct SpriteDecompressor{
	
	FILE * fp;
	long raw_barrel;
	char barrel[17];
	char temp[17];
	char raw[32768];
	char mem[32768];
	char width, height;
	int size;
	char counter;
	char length;
	long mult;

	int D1,D2,D4,D5,D6,D7;

	int A0,A1,A2,A3;

	SpriteDecompressor(FILE * file) : fp(file) {}

	char * GetData(long address){
		sprintf(barrel,"");
		memset(raw,0,4096);
		length=0;
		mult=2;
		D6 = 0x80;
		D7 = 0x0F;
		fseek(fp,address,SEEK_SET);
		width = readbyte();
		height = readbyte();
		size = width * height * 64;

		D2 = width * 8;
		A1 = 0;
		A2 = -1;
		route(0x262E);
		FILE * dump = fopen("Test.bin","w+");
		for(int i=0;i<size;i++){
			fprintf(dump,"%c",mem[i]);
		}
		fclose(dump);
		return mem;
	}

	void route(int func){
		while(func){
			switch(func){
				case 0x262E:
					func = x262E();
					break;
				case 0x26DC:
					func = x26DC();
					break;
				case 0x2736:
					func = x2736();
					break;
				case 0x2784:
					func = x2784();
					break;
				case 0x27CE:
					func = x27CE();
					break;
				case 0x281C:
					func = x281C();
					break;
				case 0x2878:
					func = x2878();
					break;
				case 0x28C6:
					func = x28C6();
					break;
				case 0x28D6:
					func = x28D6();
					break;
				case 0x28EC:
					func = branch2();
					break;
				case 0x2950:
					func = x2950();
					break;
			}
		}
	}

	int x262E(){
		mult=2;
		counter=0;
		while(!getBit()){
			counter++;
			if(counter==256)break;
		}
		mult=mult<<counter;
		A2+=mult-2;
		mult=0;
		while(counter>=0){
			mult=mult<<1;
			if(getBit())mult++;
			counter--;
		}
		A2+=mult;
		if(A2>=size)return 0x28C6;
		if(length>=4){
			length-=4;
			sprintf(temp,barrel);
			for(int i=strlen(barrel);i<16;i++){
				temp[i]='0';
			}
			temp[16]=0;
			raw_barrel = strtol(temp,0,2);
			raw_barrel = ROL(raw_barrel,4);
			itoa(raw_barrel,temp,2);
			strncpy(barrel,"0000000000000000",16-strlen(temp));
			barrel[16-strlen(temp)]=0;
			sprintf(barrel,"%s%s",barrel,temp);
			D1 = raw_barrel&0xFF;
			D1&=D7;
			D1|=D6;
		} else {
			raw_barrel=0;
			for(int i=0;i<4;i++){
				raw_barrel=raw_barrel<<1;
				if(getBit())raw_barrel++;
			}
			D1=raw_barrel;
			D1&=D7;
			D1|=D6;
		}
		raw[A2]=D1;
		if(!getBit())return 0x262E;
		A1=A2;
		return branch(4);
	}
	int x26DC(){
		if(getBit())return 0x27CE;
		A1+=D2-2;
		raw[A1]=D1&0xFF;
		return branch(4);
	}

	int x2736(){
		mult=A1;
		mult+=D2;
		if(getBit(false))mult++;
		A1=mult;
		raw[A1]=D1&0xFF;
		return branch(3);
	}

	int x2784(){
		A1+=D2-1;
		raw[A1]=D1&0xFF;
		return branch(3);
	}

	int x27CE(){
		A1+=D2+2;
		raw[A1]=D1&0xFF;
		return branch(4);
	}

	int x281C(){
		mult=A1;
		mult+=D2;
		if(getBit(false))mult++;
		A1=mult;
		raw[A1]=D1&0xFF;
		return branch(4);
	}

	int x2878(){
		A1+=D2-1;
		raw[A1]=D1&0xFF;
		return branch(4);
	}

	int x28C6(){
		A0=0;
		A1=0;
		A3=size;
		raw[A3]=0x80;
		raw[A3+1]=0x80;
		D6=0xF0;
		D1 = raw[A1++];
		D1 *= 0x100;
		D1 += raw[A1++];
		return 0x28D6;
	}

	int x28D6(){
		if(!D1&0x8000)return 0x292A;
		if(!D1&0x80)return 0x2906;
		D1=(D1&0xFFFFFF00)|(D1&D7);
		D4=D1&0xFF;
		D1&=0xFFFF;
		D1=D1>>4;
		D1=(D1&0xFFFFFF00)|(D4);
		if((D1&0xFF)==0)return 0x2950;
		D1 = (D1&0xFFFFFF00)|((D1<<4)&0xFF);
		D4|=(D1&0xFF);
		branch2();
	}

	int x2906(){
		D1=D1>>4;
		D4=D1&0xFF;
		D4=D4>>4;
		D4|=(D1&0xFF);
		raw[A0++]=D4;
		return branch2();
	}

	int x292A(){
		D4&=D6;
		D1=(D1&0xFFFFFF00)|(D1&D7);
		D4|=(D1&0xFF);
		raw[A0++]=D4;
		D4=(D4<<4)&0xFF;
		D4|=(D1&0xFF);
		return branch2();
	}

	int x2950(){
		A2=0;
		A3=0;
		A1=0;
		D2=D2>>1;
		D7=D2;
		D7=D7<<5;
		D4 = height<<2-1;
		D5 = width<<2-1;

		for(int l=0;l<=D5;l++){
			A0=A3;
			D6=D4;
			for(int k=0;k<=D6;k++){
				for(int j=0;j<4;j++){
					A2=A0+4*j;
					for(int i=0;i<8;i++){
						mem[A1++]=raw[A2];
						A2+=D2;
					}
				}
				A0+=D7;
			}
			A3+=16;
		}
		return 0;
	}

	int branch(int l){
		if(length>=l){
			length-=(l-1);
			if(getBit(false))return 0x2736;
			if(getBit(false))return 0x2784;
			if(getBit(false))return 0x26DC;
			return 0x262E;
		} else {
			length+=(4-l);
			if(getBit())return 0x281C;
			if(getBit())return 0x2878;
			if(getBit())return 0x26DC;
			return 0x262E;
		}
	}

	int branch2(){
		for(int i=0;i<4;i++){
			D1 = raw[A1++];
			D1 *= 0x100;
			D1 += raw[A1++];
			if((signed short)(D1))return 0x28D6;
			raw[A0++]=D4;
		}
		return 0x28EC;
	}

	bool getBit(bool adjLen=true){
		char c;
		if(!length){
			raw_barrel = readword();
			itoa(raw_barrel,temp,2);
			strncpy(barrel,"0000000000000000",16-strlen(temp));
			barrel[16-strlen(temp)]=0;
			sprintf(barrel,"%s%s",barrel,temp);
			length=16;
		}
		c=barrel[0];
		sprintf(barrel,"%s",barrel+1);
		if(adjLen)length--;
		return c=='1';
	}

	unsigned char readbyte(){
		unsigned char t;
		fscanf(fp,"%c",&t);
		return t;
	}

	unsigned long readword(){
		unsigned long t;
		fscanf(fp,"%c%c",&(temp[0]),&(temp[1]));
		t=temp[0];
		t*=256;
		t+=temp[1];
		t%=0x10000;
		return t;
	}

	unsigned long ROL(unsigned long n, unsigned long i){
	  return ((n << i) | (n >> (16 - i))) & 0xFFFF;
	}

	unsigned long ROR(unsigned long n, unsigned long i){
	  return ((n >> i) | (n << (16 - i))) & 0xFFFF;
	}

};