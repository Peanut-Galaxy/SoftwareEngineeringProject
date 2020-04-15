#include <string>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <unordered_map>
#include <iterator>
using namespace std;

class HistoryBuffer //: public list
{
	private:
		
	public:
		HistoryBuffer(){
			
		}
		void undo();
		void redoo();
};

class FileData{
	private:
		string uncleanedData;
		
};

class DataProcessor{
	private:

		unordered_map<int, int (*)(int, int&)> functionMap;
		int testData;
		
	public:
		DataProcessor(unordered_map<int, int (*)(int, int&)> &inmap)
		{
			functionMap = inmap;
			testData = 5;
		}
		
		int Driver()
		{
			char clear[4] = {27,'[','2','J'};
			char input[256];
			std::unordered_map<int, int (*)(int, int&)>::iterator temp;

			do
			{
				for(auto i = functionMap.cbegin(); i != functionMap.cend(); i++)
				{
					i->second(1, testData);
				}
				cout << "input something" << endl;
				
				int i = 0;

				// some shenanigins with cin leads to odd behavior if a user accidently inputs
				// multiple characters
				fgets(&input[0], 256, stdin);
				//debugging to check the numerical val of the char
				//cout << (int)input[0] << endl;

				//execute the function associated with input
				temp = functionMap.find(input[0]);
				if(temp == functionMap.end())
				{
					continue;
				}
				else
				{
				temp->second(0, testData);
				}

			}while(1);
				
				
				
		}
};
int testFunction(int mode, int &input)
{
	const char menuButton = 'a';
	if(mode == 0)
	{
		cout << "test complete, data = " << input << endl;
		input--;
	}
	else if(mode == 1)
	{
		cout << "Press \"a\" for \"testFunction\"" << endl;
	}
	else if(mode == 2)
	{
		return menuButton;
	}
}
int dummyfunc(int test, int &input)
{
	if(test == 1)
	{
		cout << "Press \"b\" for \"dummyfunc\"" << endl;
	}
	else
		cout << -test << endl;	
}

int stupidfunc(int test, int &input)
{
	if(test == 1)
		cout << "Press \"c\" for \"dummyfunc\"" << endl;
	else cout << "crap" << endl;
}


int dummyVal = 0;

int main()
{
	unordered_map<int, int (*)(int, int&)> test;
	test.emplace(testFunction(2, dummyVal), testFunction);
	
	std::unordered_map<int, int (*)(int, int&)>::iterator temp = test.find('a');
	
	DataProcessor myTest(test);
	myTest.Driver();
	
}