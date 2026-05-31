#include<iostream>
using namespace std;

class HashMap
{
private:
   int size;
   string* table;
   int curEle;
   

public:
    HashMap(int s) 
	{
		    size=s;
        	table= new string[size];
        	for(int i=0;i<size;i++)
        	{
        		table[i]="00";
			}
            curEle=0;
    }
    bool isEmpty()
    {
    	if(curEle==0)
    	{
    		return 1;
		}
		else
		{
			return 0;
		}
	}
	bool isfull()
	{
		if(curEle==size)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	double loadfactor()
	{
		double v=this->curEle / this->size;
		return v;
	}
	int hashFunction(string s)
	{
		int sum = 0;
        for (int i=0;i<s.size();i++) 
		{
			char c=s[i];
			sum+=i;
		}
        return sum % size;
	}
    bool Insert(string v)
    {
    	int j;
        int index = hashFunction(v);
        if(table[index]=="00")
		{
		table[index]=v;
		}
		else
		{
		   for(int i=0;i<size;i++)
		   {
		   	j=((index+i)%size);
		   	if(table[j]=="00")
		   	{
		   	table[j]=v;
		   	curEle++;
		   	cout<<j<<":  "<<v<<endl;
		   	return 1;
			}
		    else
		    {
		    	cout<<"EMPTY SLOT NOT FOUND";
		    	return 0;
			}
		}
}
}
    bool search(string name) {
        int index = hashFunction(name);
        for(int i=0;i<size;i++)
        {
        	cout<<endl;
        	cout<<i<<endl;
        	if(table[i]==name)
        	{
        		return true;
			}
		}
		return false;
    }

    bool remove(string name) {

        for(int i=0;i<size;i++)
        {
        	if(table[i]==name)
        	{
        		table[i]="00";
        		return 1;
        		curEle=curEle-1;
			}
			return 0;
		}    
    }
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "key: " << i << " , value: " << table[i] << " ";
            cout << endl;
        }
    }
    ~HashMap()
    {
    	for(int i=0;i<size;i++)
    	{
    		table[i]="00";
    		curEle=curEle-1;
		}
		table=NULL;
	}
};


int main()
{
    HashMap hm(6);

    hm.Insert("bisma");
    hm.Insert("hadiqa");
    hm.Insert("maha");
	
    cout << "\nAfter Insertions:\n";
    hm.display();   
    cout << "\nsearch maha: " << (hm.search("maha") ? "Exists" : "Not Found") << endl;
    cout << "Check key hadiqa: " << (hm.search("hadiqa") ? "Exists" : "Not Found") << endl;
    cout<<"\nDisplay load factor"<<endl;  
    cout<<hm.loadfactor();
    
    cout << "\nRemoving maha...\n";
    hm.remove("maha");
    hm.display();


    return 0;	
}