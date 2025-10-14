#include <iostream>
#include <cmath>
#include <string>

using namespace std;

template<typename t>
class Stack
{
private:
    t* data;
    int capacity;
    int top;

public:
    Stack(int c)
	{
		  if (c > 0)
    {
        capacity = c;
        top = 0;
        data = new t[c];
    }
    else
    {
        throw ("stack capacity must be > 0");
    }
	}
    Stack(Stack& s2)
    {
    	 this->capacity = s2.capacity;
        this->top = s2.top;
        data = new t[s2.capacity];
    if (top != 0)
    {
        for (int i = 0; i < top; i++)
        {
            data[i] = s2.data[i];
        }
    }
	}
    ~Stack()
    {
    	
    delete[] this->data;
	}
    int getTop()
    {
    	 return top;
	}
    void push(t value)
    {
    	 if (!isFull())
    {
        data[top] = value;
        top++;
    }
    else {
        throw ("Stack is full");
    }
	}
    t pop()
    {
    	if (!isEmpty())
    {
        top--;
        return data[top];
    }
    else
    {
        throw ("Stack is empty");

    }
	}
    t stackTop()
    {
    	if (top != 0)
    {
        return data[top - 1];
    }
    else
    {
        throw("Stack is empty");

    }
	}
    bool isEmpty()
    {
    	 bool empty = false;
    if (top == 0)
    {
        empty = true;
    }
    return empty;
	}
    bool isFull()
    {
    	bool full = false;
    if (top == capacity)
    {
        full = true;
    }
    return full;
	}
    Stack operator = (const Stack& other)
    {
    	
    if (this != &other)
    {
        delete[] data;
        this->capacity = other.capacity;
        this->top = other.top;
        this->data = new t[capacity];
        if (top != 0)
        {
            for (int i = 0; i < capacity; i++)
            {
                this->data[i] = other.data[i];
            }
        }
    }
    return *this;
	}
	t index(int i)
	{
		if(isEmpty())
		{
			 throw("Stack is empty");
		}
		else
		{
			return data[i];
		}
	}

};

int main()
{
	string s;
	cout<<"ENTER FORM OF A AND B AND C: ";
	getline(cin,s);
	
	Stack<char>s1(s.length());
	bool bstart=false;
	bool cstart=false;
	bool valid=true;
	int c1=0,c2=0,c3=0;
	
	for(char c:s)
	{
		if(c=='a')
		{
			if(bstart || cstart)
			{
				valid=false;
				break;
			}
			s1.push(c);
			c1++;
			
		}
		else if(c=='b')
		{
			if(cstart)
			{
				valid=false;
				break;
			}
			bstart=true;
			s1.push(c);
			c2++;
		}
		else if(c=='c')
		{
			cstart=true;
			s1.push(c);
			c3++;
		}
		else
		{
			valid=false;
			break;
		}
		
	}
	if(!(c1 > 0 && c2 > 0 && c3 > 0 && c1==c2 && c2==c3))
   {
    valid=false;
   }
	else
	{
		valid=true;
	}
	
	if(valid)
	{
		cout<<"string is valid";
	}
	else
	{
		cout<<"string is n0t valid";
	}
	return 0;
}