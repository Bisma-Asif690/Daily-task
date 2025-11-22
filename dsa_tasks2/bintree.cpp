#include<iostream>
#include<cmath>
using namespace std;
template<typename T>
class Binarytree
{
private:
	int h;
	T *data;
	bool *status;
public:
	Binarytree(int h1=0)
	{
		h=h1;
		int size=pow(2, h) - 1;
		data=new T[size];
		status=new bool[size];
		for(int i=0;i<size;i++)
		{
			status[i]=false;
		}
	}
	void setroot(T v)
	{
		if(status[0]==false)
		{
			data[0]=v;
			status[0]=true;
		}
	}
	void setleftchild(T p,T v)
	{
		for(int i=0;i<pow(2, h) - 1;i++)
		{
			if(status[i]==true&&data[i]==p)
			{
				if((2*i)+1<pow(2, h) - 1 && status[(2*i)+1]==false)
				{
					data[(2*i)+1]=v;
					status[(2*i)+1]=true;
					return;
				}
			}
		}
	}
	void setrightchild(T p,T v)
	{
		for(int i=0;i<pow(2, h) - 1;i++)
		{
			if(status[i]==true&&data[i]==p)
			{
				if((2*i)+2<pow(2, h) - 1 && status[(2*i)+2]==false)
				{
					data[(2*i)+2]=v;
					status[(2*i)+2]=true;
					return;
				}
			}
		}
	}
	void display()
    {
        int size=pow(2, h) - 1;
        cout << "Tree elements: ";
        for (int i = 0; i < size; i++)
        {
            if (status[i])
                cout << data[i] << " ";
            else
                cout << "- ";
        }
        cout << endl;
    }

    ~Binarytree()
    {
        delete[] data;
        delete[] status;
    }
    void displayTree()
   {
    int index = 0;
    for (int level = 0; level < h; level++)
    {
        int nodes = pow(2, level);
        for (int i = 0; i < nodes && index < pow(2, h) - 1; i++, index++)
        {
            if (status[index])
                cout << data[index] << " ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

	
};
int main()
{
    Binarytree<char> b(3); 

    b.setroot('A');
    b.setleftchild('A', 'B');
    b.setrightchild('A', 'C');
    b.setleftchild('B', 'D');
    b.setrightchild('B', 'E');
    b.setleftchild('C', 'F');
    b.setrightchild('C', 'G');

    b.display();
    b.displayTree();

    return 0;
}

