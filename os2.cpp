#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <iomanip>

using namespace std;

pthread_mutex_t S_One, S_Two, S_Three;
long row;

char array[200][60]; 
ifstream file ("input.txt");
char character;

void * organizeGroup1 ( void * );
void * organizeGroup2 ( void * );
void * organizeGroup3 ( void * );

int main () {
	
	for ( long i = 0; i < 200; i ++ ) {
		for ( long col = 0; col < 60; col ++ ) {
			array[i][col] = ' ';
		}
	}

	
	pthread_t thread1, thread2, thread3;
	long group1, group2, group3;

	
	pthread_mutex_init(&S_One, NULL);
	pthread_mutex_init(&S_Two, NULL);
	pthread_mutex_init(&S_Three, NULL);

   
	pthread_mutex_lock(&S_Two);
	pthread_mutex_lock(&S_Three);

	group1 = 1;
	pthread_create (&thread1, NULL, organizeGroup1, (void *) group1);

	group2 = 2;
	pthread_create (&thread2, NULL, organizeGroup2, (void *) group2);

	group3 = 3;
	pthread_create (&thread3, NULL, organizeGroup3, (void *) group3);

	pthread_join(thread1, NULL); 
	pthread_join(thread2, NULL); 
	pthread_join(thread3, NULL); 

	pthread_mutex_destroy(&S_One);
	pthread_mutex_destroy(&S_Two);
	pthread_mutex_destroy(&S_Three);


	return 0;

}


void * organizeGroup1 ( void* ptr) { 
	pthread_mutex_lock (&S_One);
	long someNum = (long) ptr;

	if ( someNum == 1 ) { 
		
		long col = 0;
		row = 0;
		
		if ( file.is_open() ) {

			while ( file.get(character) ) { 

				array[row][col] = character;
				col ++;

				if ( character == '\n' ) {
					row ++;
					col = 0;
					
				}//if
				
			}//while 
			
			pthread_mutex_unlock (&S_Two); 
			
		}//if file
		else {
			cout << "Sorry. Cannot locate your file." << endl;
			exit(-1);
		}//else
		
	}//if
}//void



void * organizeGroup2 ( void* ptr) {
	
	pthread_mutex_lock (&S_Two);
	long someNum = (long) ptr;

	if ( someNum == 2 ) { 
	
		for ( int i = 0; i < 200; i++ ) {
			for ( int j = 0; j < 60; j++ ) {
				if ( array[i][j] == '\\' ) { 
						if ( array[i][j+1] == 'c' ) { 
							array[i][j] = ' '; 
							array[i][j+1] = ' '; 
							array[i][j+2] = toupper( array[i][j+2] ); 
						}//if

						else if ( array[i][j+1] == 'C' ) {
							bool noSpace = true;
							int insideOneRow = j+2;
							while ( noSpace ) { 
								if ( array[i][insideOneRow] == ' ' ) { 
									noSpace = false;
								}//if
								else {
									if ( insideOneRow < 60  ) {
										array[i][j] = ' '; 
										array[i][j+1] = ' '; 
										array[i][insideOneRow] = toupper( array[i][insideOneRow] ); 
										insideOneRow ++; 
									}
								}//else
							}//while;
						}//else if

						else { // array[i][j+1] == 'u'

							int inword = j+1;
							array[i][j] = '_';

							while ( array[i][inword] != ' ' ) {
							
								if ( array[i][inword+1] == '\n' ) {
								
									array[i][inword+2] = array[i][inword+1];
									array[i][inword+1] = ' '; 
								}
								
								array[i][inword] = array[i][inword+1]; 
								inword++;
							}
							inword--;
							array[i][inword] = '_';

						}//else

				}//if
				
			}//for
			

		}//for
		
	
		pthread_mutex_unlock(&S_Three);
	}//if
	

}//void


void * organizeGroup3 ( void* ptr) { 

	pthread_mutex_lock (&S_Three);
	long someNum = (long) ptr;
	
	if ( someNum == 3 ) {
		ofstream myfile;
	  	myfile.open ("guanjia.txt");
	  	

	  	for ( int i = 0; i < row + 1; i ++ ) {
	  		int insideOneRowCounter = 0;

	  		while ( insideOneRowCounter < 60 && array[i][insideOneRowCounter] != '\n' ) {
	  			if (array[i][insideOneRowCounter] != '\n'){
	  				
	  			}
	  			myfile << array[i][insideOneRowCounter];
	  			insideOneRowCounter ++;
	  		}

	  		myfile << '\n';
	  		
	  	}

	  	myfile.close();
	}

}//void














