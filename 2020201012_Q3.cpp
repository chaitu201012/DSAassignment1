#include<iostream>
using namespace std;

template<typename T>
class Deque{

	T * circular_queue;
	int rear,begin, maxSize,queue_size;

public:

	Deque()
	{
		maxSize = 8;
		circular_queue = new T[maxSize];
		rear = 0;
		begin = 0;
        queue_size=0;
	}
    Deque(int n,T x){
        maxSize=n;
        circular_queue = new T[maxSize];
        for(int i=0;i<maxSize;i++){
            circular_queue[i]=x;
        }
        begin=0;
		rear=n-1;
        queue_size=n;
    }
	void push_back(T item)
	{

        if(rear>maxSize-1) resize(maxSize*4);
		circular_queue[rear] = item;
		rear++;

		if (begin > 0 && rear > maxSize)
		{
			rearrange();
		}
		else if (begin == 0 && rear > maxSize-1 )
		{
			resize(maxSize*4);
		}
        else if(rear==begin){
            rearrange();

        }
        queue_size++;
	}
    void push_front(T item){
        if((begin-1)==-1){
            if (rear==maxSize||rear==maxSize-1||rear>maxSize){
                resize(maxSize*4);
                begin=maxSize-1;
                circular_queue[begin]=item;
            }
            else if(rear<maxSize-1){
                 begin= maxSize-1;
                 circular_queue[begin]=item;
            }
        }
        else if(rear == maxSize && begin==0){
            resize(maxSize*4);
            begin=maxSize-1;
            circular_queue[begin]=item;
        }
        else if(begin-1==rear){
            rearrange();
            resize(maxSize*4);
            begin=maxSize-1;
            circular_queue[begin]=item;
        }
        else{
            begin--;
            circular_queue[begin]=item;
        }
        queue_size++;
    }

	void pop_front()
	{
		T temp = circular_queue[begin];
		begin++;
        queue_size--;
	//	return temp;
	}
    void pop_back()
	{

        rear--;
		T temp = circular_queue[rear];
        queue_size--;
	//	return temp;
	}

	void resize(int newSize)
	{
		int prevsize=maxSize;
		maxSize = newSize;
		T *temp2 = new T[maxSize];
        int tempindex=begin;
		int i=0;
	//	cout<<"queuesize= "<<queue_size<<endl;
        for(;i<queue_size;i++) {
        //    cout<<"circular_queue["<<tempindex<<"] "<<circular_queue[tempindex]<<endl;
            temp2[i]=circular_queue[tempindex];
			tempindex=(tempindex+1)%prevsize;

        }
		delete[] circular_queue;
		circular_queue = new T[maxSize];
	//	cout<<"maxSize =="<<maxSize<<endl;
        i=0;
		//cout<<"queuesize= "<<queue_size<<endl;
        for(;i<queue_size;i++ ){
		//	cout<<"temp["<<i<<"]"<<temp2[i]<<endl;
            circular_queue[i]=temp2[i];
        }
		//cout<<"queuesize= "<<queue_size<<endl;
		begin=0;
		rear=i;
		delete[] temp2;

	}

	void rearrange()
	{
        int prevsize=maxSize;
		T *temp = new T[maxSize];
		int tempindex = begin;
        int i=0;
		//cout<<"queuesize = "<<queue_size<<endl;
		//cout<<"maxSize= "<<maxSize<<endl;
        for(;i<queue_size;i++) {
            //cout<<"circular_queue["<<i<<"] "<<circular_queue[tempindex]<<endl;
            temp[i]=circular_queue[tempindex];
            tempindex=(tempindex+1)%maxSize;
        }

        i = 0;
		for ( ;i<queue_size; i++)
		{
            circular_queue[i] = temp[i];
		}
        begin=0;
        rear=i;

		delete[] temp;
	}
    void display(){
        rearrange();

        for(int i=0;i<queue_size;i++) {
            cout<<circular_queue[i]<<endl;
        }

    }
	T D(int n){
        rearrange();
		if(n<queue_size){
			return circular_queue[n];
		}
		else{
			cout<<"invaid index, no queue element at that index"<<endl;
			exit(1);
		}
    }

	bool isEmpty()
	{
		if(queue_size==0|| rear==0) return true;
		else return false;


	}

	int size()
	{
		return queue_size;
	}
	T front(){
		return circular_queue[begin];
	}
	T back(){
		return circular_queue[rear-1];
	}
	void clear(){
		begin=0;
		rear=0;
		queue_size=0;
	}

	void resize(int x,T d){
		if(x<maxSize) return;
		else{
			resize(x);
			//cout<<"maxx =="<<maxSize<<endl;
			//cout<<"queue_size"<<queue_size<<endl;
			for(int i=queue_size;i<x;i++){
				circular_queue[i]=d;
				//cout<<"i= "<<i<<circular_queue[i]<<endl;
			 }
			 queue_size=maxSize;
			}
	}
};

int main(){
	Deque<string> *dq=NULL ;
	int Qcount,n,c;
	cin>>Qcount;
	string str;
	while (Qcount>0){
		cin>>c;
		if(c==5){
			if(dq!=NULL) delete dq;
			dq= new Deque<string>();

		}
		else if(c==6){
		   cin>>n>>str;
		   if(dq!=NULL) delete dq;
 		   dq= new Deque<string>(n,str);
		   dq->display();

		}
		else if(c==1){
	 		cin>>str;
	        dq->push_front(str);
	        dq->display();

		}
		else if(c==2){
	 		//cout<<dq->pop_front()<<endl;
			dq->pop_front();
	        dq->display();

		}
		else if(c==3){
	  		cin>>str;
	        dq->push_back(str);
	        dq->display();

		}
		if(c==4){
	 		//cout<<dq->pop_back()<<endl;
			dq->pop_back();
	        dq->display();

		}
		else if(c==7){
	 		cout<<dq->front()<<endl;

		}
		else if(c==8){
	 		cout<<dq->back()<<endl;

		}
		else if(c==9){
	  		//cout<<dq->isEmpty();
			if(dq->isEmpty()) cout<<"true"<<endl;
			else cout<<"false"<<endl;

		}
		else if(c==10){
	  		cout<<dq->size()<<endl;

		}
		else if(c==11){
	 		cin>>n>>str;
	        dq->resize(n,str);
	        dq->display();

		}
		else if(c==12){
	 		dq->clear();
		}
		else if(c==13){
	 		cin>>n;
	        cout<<dq->D(n)<<endl;

		}
		else if(c==14){
	 		dq->display();

		}
		Qcount--;
	}
	delete dq;
	return 0;
}
