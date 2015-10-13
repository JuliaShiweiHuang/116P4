/*
 * Joe Schmoe
 *
 * File   : p4.cpp
 * Purpose: Program to aid Professor Trout in his quest to count the number of unique words
 *          in an arbitrary text file.
 * Input  : A valid file name of a file that contains arbitrary text, ending with "DONE".  Valid
 *          punctuation includes the set {'.', ',', '!', '?'}.
 * Output : An aligned table showing each unique word and its frequency, in order from highest
 *          to lowest frequency.  Finally, words that appear once are displayed, 10 per line.
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX = 1000;		// maximum number of unique words
const int MAXLINE = 10;		// maximum words displayed per line

class trout {
   string allWords [MAX];	// array storing all the unique words
   int wordCounts [MAX];	// parallel array storing the frequencies of the words
   int count;			// total number of unique words
   int max;			// the maximum number of times any word appears
public:
   void readText (string);
   void displayStats ();
};

/*******************************************************************************************/

int main () {
   trout myList;	// instance of the trout class
   string fileName;	// user's input file name

   cout << "Enter file name: ";
   cin >> fileName;

   myList.readText (fileName);

   myList.displayStats();
  
   return 0;
}

/*******************************************************************************************/

void trout :: readText (string fname)
/*
 * Method to read the input text and store all of the unique words.
 * Precondition : fname is a valid string 
 * Postcondition: allWords[] contains all of the unique words &&
 *                wordCounts[] contains all of the frequencies of the words
 */
{
   ifstream inFP;	// input file pointer
   int i;		// looper
   bool found;		// used to determine if a word match has been found
   string oneword;	// current word being processed
   
   count = 0;	// no words yet!
   inFP.open (fname.c_str());

   if (! inFP) {
      cout << "Error - file " << fname << " not found!" << endl;


   } else {
      max = 0;	// maximum number of times any words has been seen
      inFP >> oneword;
      while (oneword != "DONE") {
         // clean the word
         oneword[0] = tolower (oneword[0]);
         if (oneword[oneword.length()-1] == '.' || oneword[oneword.length()-1] == ',' ||
             oneword[oneword.length()-1] == '!' || oneword[oneword.length()-1] == '?')
            oneword.erase(oneword.length()-1);

         // search...
         i = 0;
         found = false;
         while (i < count && !found) {		// "!found" same as "found == false"
            // check if there's a match in the array
            if (allWords [i] == oneword) {
               // there is a match, so update the count
               wordCounts [i] ++;
               found = true;   			// this will stop the loop
               // keep track of the highest frequency word
               if (wordCounts [i] > max)
                  max = wordCounts [i];
            } else
               i++;
         }

         // if there was no match, add the word to the array and update the count
         if (!found) {
            allWords [i] = oneword;
            wordCounts [i] = 1;
            if (max == 0)
               max = 1;		// first word found!
            count++;
         }
         inFP >> oneword;
      }
   }  // else
}  // readText

/*******************************************************************************************/

void trout :: displayStats ()
/*
 * Method to display various statistics.
 * Precondition : allWords contains all the unique words in the file &&
 *                wordCounts contains all the frequencies of the words &&
 *                count == number of unique words &&
 *                max == maximum frequency
 * Postcondition: displays an aligned chart of words and frequencies &&
 *                frequencies are sorted highest to lowest &&
 *                those words that appear just once are displayed 10/line 
 */
{
   int i, j;		// loopers
   int linecount = 0;	// number of words displayed per line

   // don't bother displaying anything if there are no words!
   if (count > 0) {
      cout << "Word          Number of Occurrences" << endl;
      cout << "===================================" << endl;
      while (max > 0) {
         for (i = 0; i < count; i++) 
            if (wordCounts [i] == max)
               if (max == 1) {
                  cout << allWords[i] << " ";
                  linecount++;
                  if (linecount == MAXLINE) {
                     cout << endl;		// endl when 10 words have been reached
                     linecount = 0;
                  }
               }
               else {
                  cout << allWords [i];
                  for (j = 0; j < MAXLINE-allWords[i].length(); j++)
                     cout << " ";              
                  cout << setw (15) << wordCounts [i] << endl;
               }
               
         max--;
         if (max == 1) {
            cout << endl << "Words with one occurrence" << endl;
            cout << "===================================" << endl;
         }
      }
      cout << endl;
   }
}  // displayStats