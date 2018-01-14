//Family Name: Leang	
//Given Name:Enghuot

//Section: z

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//structure for unique words found in a file
typedef struct{

     char  word[101] ;

     int   freq ;

}WordArray;

//structure for each file with top three most frequent words and number of unique words
typedef struct{

     char  word1[101] ;
     char  word2[101] ;
     char  word3[101] ;
     char  filename[101];
     int   numOfUniq ;

}SortWord;

//Compare function for SortWord structure
int cmpForOrder( const void *a,const void *b) {

	SortWord *wa = (SortWord *)a;
	SortWord *wb = (SortWord *)b;
	
	if(wa->numOfUniq < wb->numOfUniq){
		return 1;	
	}
	else if(wa->numOfUniq >  wb->numOfUniq){
		return -1;	
	}else   return  0;
}

//Compare function for WordArray structure
int cmpf( const void *a,const void *b) {

	WordArray *wa = (WordArray *)a;
	WordArray *wb = (WordArray *)b;
	
	if(wa->freq < wb->freq){
		return 1;	
	}
	else if(wa->freq >  wb->freq){
		return -1;	
	}else   return  0;
}


int main( int argc, char *argv[])
{
	int numOfArg ;
	SortWord sw[argc-1];
	
	for(numOfArg = 1; numOfArg < argc; numOfArg++){//loops for each file input
		
		WordArray w1[99999];
		FILE *f1;
		char currWord[101];
		f1 = fopen(argv[numOfArg], "r");
		int arrSize;
		int numOfUniqWord = 0;
		fscanf(f1, "%s", currWord);
		strcpy(w1[0].word, currWord);
		w1[0].freq = 1;
		numOfUniqWord++;
		
		while(fscanf(f1, "%s", currWord) != EOF){//read word by word on the file, cpoying the word into variable called currWord
	
			for(arrSize = 0; arrSize < numOfUniqWord ; arrSize++){//loops that compare the current word with the existing words in the array
				if(strcmp(w1[arrSize].word,currWord) == 0){//if there is the same word,freq is incremented by 1
					w1[arrSize].freq++;
					break;
							
				}
				else if(arrSize == numOfUniqWord -1){//else if the current word is not in the array, and if the search is exhuasted, it add the current word to the array, 
								     //initialize the freq variable by 1 and increment the number of unique word by 1
						
					strcpy(w1[numOfUniqWord].word, currWord);
					w1[numOfUniqWord].freq = 1;
					numOfUniqWord++;
						
				}
			}					
		}
		qsort(w1, numOfUniqWord, sizeof(WordArray),cmpf);//sort the word element in the array in descending order
		
		//copy top three most frequent words into sortWord structure for each file
		strcpy(sw[numOfArg-1].word1, w1[0].word);
		strcpy(sw[numOfArg-1].word2, w1[1].word);
		strcpy(sw[numOfArg-1].word3, w1[2].word);
		//copy number of unique words for each file into sordWord structure
		sw[numOfArg-1].numOfUniq = numOfUniqWord;
		//copy the file name into their structure
		strcpy(sw[numOfArg-1].filename, argv[numOfArg]);
	
		memset(w1, 0, 99999);//reset the array space
		fclose(f1);//close the current file
		
	}
	qsort(sw, argc - 1, sizeof(SortWord),cmpForOrder);//sort the number of unique word element in the array of input files in descending order
	
	//printing out the top three most frequent word for each file and thier number of unique word
	for(numOfArg = 1; numOfArg < argc; numOfArg++){
		printf("%s %d %s %s %s\n",sw[numOfArg-1].filename,sw[numOfArg-1].numOfUniq,sw[numOfArg-1].word1,sw[numOfArg-1].word2,sw[numOfArg-1].word3);	
	
	}
	return 0;

}



