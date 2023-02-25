template <class T>
struct LLNode{
	T data;
	LLNode<T> * prev;
	LLNode<T> * next;
	LLNode(){
		prev = 0;
		next = 0;
	}
};

template <class T>
struct LinkedList{
	LLNode<T> * head;
	LLNode<T> * tail;
	int size;
	LinkedList(){
		head = 0;
		tail = 0;
		size = 0;
	}
	LinkedList(int l, ...){
		head = 0;
		tail = 0;
		size = 0;
		va_list vl;
		va_start( vl, l );
		for(int i=0;i<l;i++){
			append(va_arg( vl, T));
		}
		va_end( vl );
	}
	LinkedList(LinkedList&l){
		head = 0;
		tail = 0;
		size = 0;
		*this+=l;

	}
	~LinkedList(){
		clean();
	}
	LLNode<T> * add(T val){
		LLNode<T> * temp;
		temp = head;
		head = new LLNode<T>;
		head->next = temp;
		if(temp)temp->prev=head;
		else tail = head;
		head->data=val;
		size++;
		return head;
	}
	LLNode<T> * insert(T val,LLNode<T> * node){
		if(!node)return NULL;
		LLNode<T> * temp;
		temp = new LLNode<T>;
		temp->data=val;
		temp->next = node;
		temp->prev = node->prev;
		node->prev = temp;
		size++;
		if(node==head){
			head = temp;
			return temp;
		}
		if(temp->prev)temp->prev->next = temp;
		return temp;
	}
	LLNode<T> * append(T val){
		LLNode<T> * temp;
		temp = tail;
		tail = new LLNode<T>;
		tail->prev = temp;
		if(temp)temp->next=tail;
		else head = tail;
		tail->data=val;
		size++;
		return tail;
	}
	LLNode<T> * find(T val){
		LLNode<T> * temp = head;
		while(temp){
			if(temp->data==val)return temp;
			temp = temp->next;
		}
		return 0;
	}
	LLNode<T> * remove(LLNode<T> * node){
		if(!node)return 0;
		LLNode<T> * ret = 0;
		if(node==head)head=head->next;
		if(node==tail)tail=tail->prev;
		if(node->prev)node->prev->next=node->next;
		if(node->next){
			node->next->prev=node->prev;
			ret = node->next;
		}
		delete node;
		size--;
		return ret;
	}
	void remove(T val){
		remove(find(val));
	}
	void clean(){
		while(head){
			remove(head);
		}
	}

	LinkedList<T>& operator += (const LinkedList<T>& l){
		LLNode<T> * temp = l.head;
		while(temp){
			append(temp->data);
			temp = temp->next;
		}	
		return *this;
	}
	LinkedList<T>& operator -= (const LinkedList<T>& l){
		LLNode<T> * temp = l.head;
		while(temp){
			remove(find(temp->data));
			temp = temp->next;
		}	
		return *this;
	}

	LinkedList<T>& operator += (T val){
		add(val);
		return *this;
	}
	LinkedList<T>& operator -= (T val){
		remove(find(val));
		return *this;
	}

	LLNode<T> *  operator [](const int i){
		LLNode<T> * temp = head;
		for(int j=0;j<i;j++){
			if(temp)temp = temp->next;
		}
		if(temp)return temp;
		return NULL;
	}
};
