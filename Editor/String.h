struct String{
	char * data;
	String(){
		data=0;
	}
	String(int n){
		data=new char[n];
	}
	String(char * s){
		data = new char[strlen(s)+1];
		sprintf(data,s);
	}
	String(String & s){
		data = new char[s.length()+1];
		sprintf(data,s.data);
	}
	~String(){
		clean();
	}
	int length(){
		return strlen(data);
	}
	String& operator=(char * s){
		if(strlen(s)==0){
			if(data)data[0]=0;
			else data = new char[1];
			data[0]=0;
			return *this;
		}
		if(data)delete [] data;
		data = new char[strlen(s)+1];
		sprintf(data,s);
		return *this;
	}
	String& operator=(char s){
		if(data)delete [] data;
		data = new char[2];
		sprintf(data,"%c",s);
		return *this;
	}
	String& operator=(String& s){
		if (!data && !s.data)return *this;
		if(data&&s.data)
			if(s==*this)return *this;
		if(data)delete [] data;
		data = new char[s.length()+1];
		sprintf(data,s);
		return *this;
	}
	String& operator+=(char * s){
		char * temp;
		if(data){
			temp = new char[strlen(data)+strlen(s)+1];
			sprintf(temp,data);
			if(data==s){
				sprintf(temp,"%s%s",temp,temp);
				delete [] data;
				data = temp;
				return *this;
			}
			delete [] data;
		} else {
			temp = new char[strlen(s)+1];
		}
		data = temp;
		strcat(data,s);	
		return *this;
	}
	String& operator+=(char s){
		char * temp;
		if(data){
			temp = new char[strlen(data)+2];
			sprintf(temp,data);
			delete [] data;
		} else {
			temp = new char[2];
		}
		data = temp;
		char a[2];
		sprintf(a,"%c",s);
		strcat(data,a);	
		return *this;
	}
	bool operator>(char * c){
		return strcmp(data,c)>0;
	}
	bool operator<(char * c){
		return strcmp(data,c)<0;
	}
	bool operator==(char * c){
		return strcmp(data,c)==0;
	}
	bool operator>=(char * c){
		return strcmp(data,c)>=0;
	}
	bool operator<=(char * c){
		return strcmp(data,c)<=0;
	}
	bool operator!=(char * c){
		return strcmp(data,c)!=0;
	}
	operator char*(){
		return data;
	}
	String left(unsigned int len){
		String temp(len+1);
		strncpy(temp.data,data,len);
		temp.data[len]=0;
		return temp;
	}
	String right(unsigned int len){
		if(len>strlen(data))len=strlen(data);
		String temp(data+(strlen(data)-len));
		return temp;
	}
	String mid(unsigned int start, unsigned int len){
		if(start>strlen(data)-1)start=strlen(data)-1;
		if(len+start>strlen(data))len=strlen(data)-start;
		if(len<0)len=0;
		String temp(len+1);
		strncpy(temp.data,data+start,len);
		temp.data[len]=0;
		return temp;
	}
	char * reverse(){
		if(!data)return 0;
		int e=strlen(data)-1;
		char c;
		for(int s=0;s<e;s++,e--)
		{
			c=data[e];
			data[e]=data[s];
			data[s]=c;
		}
		return data;
	}
	char * find(char * str){
		return strstr(data,str);
	}
	String insert(char * str, int pos);
	String remove(unsigned int start, unsigned int len);
	String replace(char * str, char * replace);
	void clean(){
		if(data)delete [] data;
	}
};

String operator+(char* c,String& s){
	String ret(c);
	ret+=s;
	return ret;
}

String operator+(String& s,char* c){
	String ret(s);
	ret+=c;
	return ret;
}

String operator+(String& s,String& c){
	String ret(s);
	ret+=c;
	return ret;
}

String String::insert(char * str, int pos){
	if(pos<0)pos=0;
	if(pos>length())pos=length();
	*this=left(pos)+str+right(length()-pos);
	return *this;
};

String String::remove(unsigned int start, unsigned int len){
	if(start>strlen(data)-1)start=strlen(data)-1;
	if(len+start>strlen(data))len=strlen(data)-start;
	String temp = mid(start,len);
	*this=left(start)+right(length()-start-len);
	return temp;
};

String String::replace(char * str, char * replace){
	char * res = find(str);
	int pos;
	while(res){
		pos = res-data;
		remove(pos,strlen(str));
		insert(replace,pos);
		res = find(str);
	}
	return *this;
};