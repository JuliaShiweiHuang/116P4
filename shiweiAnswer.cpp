/*
Developer: Shiwei Huang
Purpose: 
*. This program is a object-oriented program that includes a class and member functions;
1. This program should read a file and keep track of number of times words are used in the textfile; 
2. The program should prompt for the name of a file that contains the text to process. The file will contain one normal English paragraph; 
3. The program should display a list of all the words found in the text along with number of occurances of that word. Words used only once should list separately;

Input: 
1. The program should prompt for the name of a file that contains the text to process;
*. The file will contain one normal English paragraph, including punctuation;
*. The word "DONE" denotes the end of the file, but should be ignored in the "Number of Occurances" process;

Output: 
1. The program should display a list of words found in the text along with number of occurences of that word;
2. Word that are used only once should be listed separately;
3. The list should be ordered according to the number of occurances;
4. However, words with only 1 occurance does not need to be sorted;
5. Capitalization and punctuation should be eliminated. For example; "Hello," == "Hello" == "hello"; You may assume that apostrophes are part of a word;
6. Words with more than one occurence should be perfectly aligned;
7. Words with only one occurence should be displayed ith one space in between each word, with at most 10 words on a line;

*/



#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <ctype.h>


using namespace std;

const int MAX = 100000 ; //global constant for the MAXIMUM length of word[] array and counting[] array;

class trout {

	// numItems is a constant that (1) keeps track of NON-REPECTIVE token; 
	// (2) It's an index number for both word[] array && counting[] array (for example: word[3]; counting[3] should reference the word with its occurance);
	int numItems;

public:

	void readText (string ); // readText method: read a text file;
	void displayStats ( ); // displayStats method: display my results to the console;
	bool checkPunctuation (string ); // checkPunctuation method: returns true if there is punctuation at the end of the word;
	bool checkCapital (string ); // checkCapital method: return true if the first ch is Capital Letter;
	string word [MAX]; // word[] array stores token from my textfile;
	int counting [MAX]; // counting[] array stores integer, which represents number of token occurances from my file;
	string wordCopy [MAX]; // wordCopy[] array copies the same information from my word[] array when it hasn't be sorted;
	int countingCopy [MAX]; // countingCopy[] array copies the same information from my counting[] array when it hasn't be sorted;

} ;

int main () {

	trout myList;
	string fileName;

	cout << "Enter file name: ";
	cin >> fileName;
	myList.readText ( fileName.c_str() );
	myList.displayStats ();
	return 0;

}

void trout :: displayStats ( ) {

	// making copies of word[] and counting[] before it's SORTED. 
	// Reason for making a arrayCopy for array[]: after word[] and counting[] being sorted, when I print "Words with one occurance", it will mess up my [index] number;
	for ( int index = 0; index < numItems; index++ ) {
		wordCopy [index] = word[index];
		countingCopy [index] = counting [index];
	}
	
	// The following part is my bubble sorting algorithm;
	// The bubble sorting algorithm sorts counting[] array from smallest number to largest number;
	// While re-organizing counting[] array, I am also re-organizing word[] array;
	bool swapped = true;
	int j = 0;
	int tmp;
	string tmpString;

	while ( swapped ) {
		swapped = false;
		j ++;

		for (int k = 0; k < numItems-j; k++) {
			if ( counting [k] > counting [k+1] ) {
				tmp = counting [k];
				tmpString = word [k];
				counting [k] = counting [k+1];
				word [k] = word [k+1];
				counting [k+1] = tmp;
				word [k+1] = tmpString;
				
				swapped = true;
			}
		}
	}
	cout << endl;
	cout << "Word 			Number of Occurances" << endl;
	cout << "==============================================" << endl;
	
	// This part of algorithm prints word[] and counting[] backwards;
	// Since my bubblesort algorithm organizes counting[] from smallest to largest, I print word[] and counting[] backwards;
		for ( int n = numItems-1; n > -1; n-- ) {
			if ( counting[n]!= 1 ) {
				cout << word [n] << setw( 40 - word[n].length() ) << counting [n] << endl; // setw( 40 - word[n].length() ) is a "variable space" that will adjust from the token length;
			}
		}

		
		cout << endl;
		cout << "Word with one occurrences" << endl;
		cout << "==============================================" << endl;
		
		//Note: I am printing the "words with one occurance" from my wordCopy[], which is UNSORTED;
		for ( int index = 0; index < numItems; index ++) {
				if ( countingCopy [index] == 1 ) {
					cout << wordCopy [index] << " ";
					
			}
		}

		cout << '\n';


}

// checkCapital method pass my token by value;
bool trout :: checkCapital ( string token ) {
	char ch = token [0]; // I take first character from the new token;
	return isupper (ch); // return true if new token has capital letter;
}


// checkPunctuation method pass my token by value;
// * It is a member function under trout class that takes the last character from the token;
// Return true if new token has a punctuation;
bool trout :: checkPunctuation ( string token ) {
	char c = token [token.size()-1];
	if ( c == '.' || c == '!' || c == '?' || c == ':' || c == ';' || c == ',' ) {
		return true; 
	}

	else {
		return false;
	}
}

/*
 * readText method reads the file from desktop;
 * It import each new token is processed token by token;
 */
void trout :: readText (string file) {
	ifstream inFP;
	inFP.open(file);
	string token; // string token represents new token needs to be read from file;
	int i;
 	 // Initialize counting [] with 0;
	for ( i = 0; i<= MAX; i++ ) {
		counting [i] = 0;
	 }

	if (! inFP) {
		cout << "Error: the input file does not exist." << endl;
		
	}

	else {
		numItems = 0; // numItems: never-occured token; Note: numItems won't increment if the token has appeared before in the file;
		inFP >> token;

		// Check whether the token has punctuation. If token has punctuation, then remove the punctuation; 
		bool hasPunctuation = checkPunctuation ( token );

		if ( hasPunctuation ) {
			token = token.substr ( 0, token.length()-1 );
		}

		// Check whether the token has capital letter. If token has capital letter, then convert the capital letter to lowercase;
		bool hasCapital = checkCapital ( token );

		if ( hasCapital ) {
			token [0] = tolower ( token[0] );
		}


		while ( token != "DONE"  ) {
			i = 0; // i is a variable that will go through the word[] and check whether the new token == to any previous token. 
			// If new token is a repective token, i will go to the if loop, change (now = false) and excute the while loop;
			bool now = true ;

			while ( ( i < numItems ) && ( now == true ) ) { //check the new token matches to any previous token; (i < numItems) because i will increment if new token doesn't match to previous token;
			//  if token matches to any previous token from word[], then only increment the counting[i];
			// When the program reads first token from file, it won't go through the while loop;
				if ( token == word[i] ) {
					counting [i] = counting[i] + 1; //update my counting[i] if ( new token == previous token );
					now = !true ;
				}

				else {
					i ++; // increment i if (new token != any previous token) ;
					
				}


			}

			
			if ( now == true ) { // now is a condition. ( now == true ) will only be true if my token has never occured before;

					word [numItems] = token;
					counting [numItems] = 1 ; // counting[] will change to 1 after the token has appeared once;
					numItems ++; // increment numItems. For example, numItems incremented to 2; 2 represents 2 non-repective words && the position in the array; Note to access the array, need to reference word[numItems-1];
					inFP >> token;

					/* 
					 * The following part checks whether the next token has either capital letter or punctuation;
					 * If there is:
					 * (1) capital letter OR (2) If there is punctuation
					 * We should (1) make capital letter to lower case (2) Remove the punctuation;
					 * WARNING: >> token != 'DONE' is very important because we don't want to change 'DONE'. 
					 * Otherwise, if token = 'DONE' and we change DONE to lowercase, when we go to the >>> while ( token != "DONE"  ), it will become an infinite loop. 
					 * Cautions about the case for infinite loop; 
					 */

					// Repeating the same process again. (1) Remove the punctuation; (2) Make my uppercase to lowercase IF there is any;
					bool hasPunctuation = checkPunctuation ( token );


					if ( hasPunctuation && token != "DONE" ) {  
						token = token.substr ( 0, token.length()-1 );
					}


					bool hasCapital = checkCapital ( token );

					if ( hasCapital && token != "DONE") {
						token [0] = tolower ( token[0] );
					}

			}


			else {
				// same token processing process: fixing punctuation && capital letter;
				inFP >> token;
				bool hasPunctuation = checkPunctuation ( token );

				if ( hasPunctuation && token != "DONE") {
					token = token.substr ( 0, token.length()-1 );
				}


				bool hasCapital = checkCapital ( token );

				if ( hasCapital && token != "DONE") {
					token [0] = tolower ( token[0] );
				}
		
			}

			
		}


	}

	
}
