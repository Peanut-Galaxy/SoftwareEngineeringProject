%option noyywrap
%{
bool afterTitles = false;
bool firstScan = true;

struct fileData{
	char **titleTokens;
	char ***dataTokens;
	
	int numCollumns = 1;
	/*technically can be 0 if there exists ONLY the titles of the collumns*/
	int numRows = 0;	
};
fileData csvData;



int currentCollumn = 0;
int currentRow = 0;

const int bufferSize = 256;
char dataBuffer[bufferSize];


%}
DIGIT	[0-9]
LETTER	[A-z]



%%

(\+|\-)?{DIGIT}+	{
		//printf("%s is an int\n", yytext);
		if(firstScan)
		{
			
		}
		else
		{
			if(afterTitles)
			{
				strcpy(csvData.dataTokens[currentRow][currentCollumn], yytext);
			}
			else
			{
				strcpy(csvData.titleTokens[currentCollumn], yytext);
			}
		}
}


({LETTER}|{DIGIT})+	{
		//printf("%s is a string\n", yytext);
		if(firstScan)
		{
			
		}
		else
		{
			if(afterTitles)
			{
				strcpy(csvData.dataTokens[currentRow][currentCollumn], yytext);
			}
			else
			{
				strcpy(csvData.titleTokens[currentCollumn], yytext);
			}
			
		}
}


(\+|\-)?{DIGIT}+"."{DIGIT}?	{
		//printf("%s is a decimal", yytext);
		if(firstScan)
		{
			
		}
		else
		{
			if(afterTitles)
			{
				strcpy(csvData.dataTokens[currentRow][currentCollumn], yytext);
			}
			else
			{
				strcpy(csvData.titleTokens[currentCollumn], yytext);
			}
		}
}

,	{
		if(firstScan)
		{
			if(!afterTitles)
			{
				csvData.numCollumns++;
			}
			
		}
		else
		{
			currentCollumn++;
		}
}

" "	//printf("space encountered\n");

\n	{
		if(firstScan)
		{
			csvData.numRows++;
			afterTitles = true;
		}
		else
		{
			//printf("newline encountered, after titles\n");
			afterTitles = true;	

			currentCollumn = 0;
		}


}
	
<<EOF>> {
		if(firstScan)
		{
			printf("preliminary scan done\n%d collumns and %d rows\n\nSecond scan starting...\n", csvData.numCollumns, csvData.numRows);
			afterTitles = false;
			firstScan = false;
			csvData.titleTokens = new char*[csvData.numCollumns];
			for(int i = 0; i < csvData.numCollumns; i++)
			{
				csvData.titleTokens[i] = new char[256];
			}
			csvData.dataTokens = new char**[csvData.numRows];
			for(int i = 0; i < csvData.numRows; i++)
			{
				csvData.dataTokens[i] = new char*[csvData.numCollumns];
				for(int j = 0; j < csvData.numCollumns; j++)
				{
					csvData.dataTokens[i][j] = new char[256];
				}
			}
		}
		currentCollumn = 0;
		currentRow = 0;
		
		
		return 1;
}

%%


fileData* csvScan(char *filepath = NULL)
{
	
	if(filepath == NULL)
	{
		return NULL;
	}
	else
	{
		printf ("opening \"%s\"\n", filepath);
		FILE *csv = fopen(filepath, "r");;
		yyin = csv;
		yylex();
		//yyrestart(stdin);
		yyin = csv;
		yylex();
		fclose(csv);
	}
	
	return &csvData;
}