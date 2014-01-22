#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_IN_NAME "vanban.txt"    // source file name
#define FILE_OUT_NAME "phantich.txt" // output file name
#define DONT_CARE_FILE "stopw.txt"	 // dont care words list
#define MAX_NUMBER 1000				 // assume max number of words in the source file
//data type to save word and its position in the source file
typedef struct w{
	char word[30];
	int index;
} wtype;

//main program
int main(int argc, char const *argv[])
{
	int i;
	int numberOfWord, numberDontCare;
	
	//inital array to save data
	wtype data[MAX_NUMBER];				//words in file
	wtype dontCareWords[MAX_NUMBER];	//words in dont care list

	//read data in file and save to array
	numberOfWord = ReadFile(FILE_IN_NAME, data);
	numberDontCare = ReadFile(DONT_CARE_FILE,dontCareWords);
	
	//sort words in array
	ReIndex(data, numberOfWord);
	ReIndex(dontCareWords,numberDontCare);

	//If there are some words in the source file, write data to the destination file
	if(numberOfWord != 0){
		WriteFile(FILE_OUT_NAME, data, numberOfWord, dontCareWords,numberDontCare);
	}
	return 0;
}

/*
*read data from input file and save data to array
*@param: 
*	fileName: input file name
*	data: array to save data 
*/
int ReadFile(char* fileName, wtype* data){
	FILE *file;
	int LineNo = 1;

	file = fopen(fileName, "r");
	if (file == NULL)
	{
		printf("Can not open %s\n", fileName);
		return 0;
	}
	else{
		//open successly, parse input file and save data to array
		return ParseFile(file, data, &LineNo); 
	}
}

/*
*Write data in data set to output file
*@param:
*	fileName: output file name
*	data: array of data
*	number: number of items in data set
*/
int WriteFile(char* fileName, wtype* data, int total, wtype* dontCarelist, int numberDontCare){
	FILE *file;  
	int currentIndex = 0;    // the current word index
	int nextIndex;		     // few next words index


	// open file to write data
	file = fopen(fileName, "w"); 
	if (file == NULL){
		printf("%s\n","Can not open file to write data");
		return 0;
	}

	//write data from a sorted list to file according to the instuction
	while(currentIndex < total){
		if(IsDontCare(data[currentIndex], dontCarelist,numberDontCare) == 0){
			//print current list item data
			fprintf(file, "%s\t",data[currentIndex].word);
			fprintf(file, "%d",data[currentIndex].index);
			//try next few items if its is in the same with the current word
			nextIndex = currentIndex + 1;
			while( nextIndex < total && strcmp(data[currentIndex].word, data[nextIndex].word) == 0){
				fprintf(file, ",%d",data[nextIndex].index);
				nextIndex++;
			}
			fprintf(file, "\n");
			//set current index by the index of new word
			currentIndex = nextIndex;
		}else currentIndex++;
	}

	fclose(file);
}

/*
* This funtion find next word in the file.
* It increment noLine if gets a '\n'
* return 0 if gets EOF
* @param:
* 	file: input stream
* 	buffer: string to save next word
*/
int NextWord(FILE *file, char* buffer, int* lineNo){
	char c;         //next char in the file
	int index = 0;  //index of current char in a token

	//read one charater in the file
	c = fgetc(file);

	//if eof(file) return 0
	if(c == -1){
		return 0;
	}

	//Reach to next suitable char in file: a-z or A-Z
	while(c < 'A' || ('Z' <c && c < 'a') || c > 'z'){
		c = fgetc(file);
		if (c == '\n') (*lineNo)++;
		if(c == -1)	
			return 0;
	}

	//if the next char in a-z, add it to buffer
	//if the next char in A-Z,  set it to lowerCase and add to buffer
	//if the next char not it a-z, A-Z stop try

	while(c != -1){
		
		if (c == '\n') 
			(*lineNo)++;

		if ('a'<= c && c <= 'z' )
		{
			buffer[index++] = c;
			c = fgetc(file);
		}else if ('A' <= c && c <= 'Z')
		{
			buffer[index++] = c - 'A' + 'a';
			c = fgetc(file);
		}else break;
	}
	//add ending for buffer
	buffer[index] = '\0';
	//return line index of found word
	return *lineNo;
}
/*
* This function gets the next word in the input file and saves it to data array
* @param:
*	file: input file 
*	data: data array of wType
*/

int ParseFile(FILE *file, wtype* data, int* lineNo){
	int total  = 0;   //count number of word in the file
	char buffer[30];  // save current word

	//while NextWord return a value != 0 we get a new word
	while(NextWord(file, buffer, lineNo) != 0){
		strcpy((data[total]).word,buffer);
		(data[total]).index = *lineNo;
		total++;
	}
	return total;
}

/*
* generic compare funtion for two wType element
* used for bsearch and qsort funtion
* return -1/0/1 if a < b/a = b/ a >b
* @param:
*	a: the first element
*	b: the second element
*/
int myCompare(const void *a, const void * b){
	char *x = (*(wtype *)a).word;
	char *y = (*(wtype *)b).word;
	return strcmp(x,y);
}

/*
* Sort the array, use qsort
* @param: 
*	data: array data
*   number: number of items in the array
*/
int ReIndex(wtype* data, int number){
	qsort(data,number, sizeof(wtype),myCompare);
}

/*
*check if a word is in the don't care list
*use bsearch.
*@param:
*	data: array data
*	element: element has the word need to check
*	number: number items in data set
*/
int IsDontCare(wtype element, wtype* list, int number){
	wtype dat = element;
	wtype* tmp;
	tmp = (wtype*)bsearch(&dat,list,number, sizeof(wtype), myCompare);
	if(tmp != NULL)
		return 1;
	return 0;
}