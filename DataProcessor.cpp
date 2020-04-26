#include <string>
#include <iostream>
#include <unistd.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <functional>
#include <unordered_map>
#include <iterator>
#include "csvScanner.yy.c"
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
		unordered_map<int, int (*)(int, fileData&)> functionMap;
		fileData data;
		
	public:
		DataProcessor(unordered_map<int, int (*)(int, fileData&)> &inmap, fileData data)
		{
			functionMap = inmap;
			this->data = data;
		}
		
		int Driver()
		{
			char clear[4] = {27,'[','2','J'};
			char input[256];
			std::unordered_map<int, int (*)(int, fileData&)>::iterator temp;

			do
			{
				for(auto i = functionMap.cbegin(); i != functionMap.cend(); i++)
				{
					i->second(1, data);
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
				temp->second(0, data);
				}

			}while(1);
				
				
				
		}
};
int avg(int mode, fileData &input)
{
	const char menuButton = 'a';
	if(mode == 0)
	{

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
	{
		
	}
}

int stupidfunc(int test, int &input)
{
	if(test == 1)
		cout << "Press \"c\" for \"dummyfunc\"" << endl;
	else cout << "crap" << endl;
}


fileData dummyVal;


int main()
{
	fileData readCsv;
	readCsv = csvScan("test.csv");
	
	unordered_map<int, int (*)(int, fileData&)> functions;
	functions.emplace(avg(2, dummyVal), avg);
	
	std::unordered_map<int, int (*)(int, fileData&)>::iterator temp = functions.find('a');
	
	DataProcessor myTest(functions, readCsv);
	myTest.Driver();
	
}