#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// A multiplication operation with a level of complexity assignment
struct operation {
	int factor1;
	int factor2;
	int level;
};

// The list of operations to run the game on
struct operations {
	struct operation* operations;
	int size;
};

// We probably want to load these from a files :) right now it's the same flag for both parties... the Canadian flag :)
char english_flag[] = "-------------------------------------------------------------------\nXWXWXWXWXWXWXWXW                                   WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX                 A                 XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW                AWA                WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX           AA  AWXWA  AA           XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW            VWXWXWXWXWV            WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX        AA   VWXWXWXWV   AA        XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW    VWXWXWXA  VWXWXWV  AXWXWXWV    WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX     XWXWXWXWXWXWXWXWXWXWXWXWX     XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW   AXWXWXWXWXWXWXWXWXWXWXWXWXWXA   WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX      VXWXWXWXWXWXWXWXWXWXWXV      XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW         VXWXWXWXWXWXWXWXV         WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX           XWXWXWXWXWXWX           XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW         AXWXWXWXWXWXWXWXA         WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX                 I                 XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW                 I                 WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX                 I                 XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW                                   WXWXWXWXWXWXWXWX\n-------------------------------------------------------------------\n";
char french_flag[] = "-------------------------------------------------------------------\nXWXWXWXWXWXWXWXW                                   WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX                 A                 XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW                AWA                WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX           AA  AWXWA  AA           XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW            VWXWXWXWXWV            WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX        AA   VWXWXWXWV   AA        XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW    VWXWXWXA  VWXWXWV  AXWXWXWV    WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX     XWXWXWXWXWXWXWXWXWXWXWXWX     XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW   AXWXWXWXWXWXWXWXWXWXWXWXWXWXA   WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX      VXWXWXWXWXWXWXWXWXWXWXV      XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW         VXWXWXWXWXWXWXWXV         WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX           XWXWXWXWXWXWX           XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW         AXWXWXWXWXWXWXWXA         WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX                 I                 XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW                 I                 WXWXWXWXWXWXWXWX\nWXWXWXWXWXWXWXWX                 I                 XWXWXWXWXWXWXWXW\nXWXWXWXWXWXWXWXW                                   WXWXWXWXWXWXWXWX\n-------------------------------------------------------------------\n";

// Creates the operations for the given level of complexity, 1 to 3
struct operations* createOperations( int level ) {
	struct operations* answer = malloc( sizeof( struct operations) );
	answer->operations = malloc( sizeof(struct operation) * 100 ); // 100 operations is the total as if it were no levels

	// Argument check
	if( level < 1 || level > 3 ) { return NULL; }

	int counter = 0;
	for( int i = 0; i < 10; i++ ) {
		for( int j = 0; j < 10; j++ ) {
			// Given the operation (i is factor1, k is factor2, assign the complexity level)
			int card_level = 0;
			if( (i >= 0 && i <= 3) || (j >= 0 && j<= 3) ) { card_level = 1; } 
			else if( (i >= 4 && i <= 6) || (j >= 4 && j<= 6) )  { card_level = 2; }
			else if( (i >= 7 && i <= 9) || (j >= 7 && j<= 9) )  { card_level = 3; }

			if( card_level == level ) {
				answer->operations[counter].factor1 = i;
				answer->operations[counter].factor2 = j;
				answer->operations[counter].level = card_level;
				counter++;
			}
		}
	}
	answer->size = counter; // Assign the total number of operations that we added for this level

	return answer;
}

// So we remove operations that have been presented to the user during the game
struct operations* removeOperation( struct operations* operations, int index ) {
	struct operation* current = operations->operations;
	operations->operations = malloc( sizeof(struct operation) * operations->size - 1 );
	for( int i = 0; i < index; i++ ) {
		operations->operations[i] = current[i];
	}
	for( int i = index+1; i < operations->size; i++ ) {
		operations->operations[i-1] = current[i];
	}
	free(current);
	operations->size--;
	return operations;
}

// Main program
int main( int argc, char* argv[] ) {
	int english = 100;
	int french = 100;
	int level = -1;

	while( level < 1 || level > 3 ) {
		printf( "Select level 1, 2 or 3:\n" );
		scanf( "%d", &level ); 
	}

	printf( "Battle against the French! %d English %d French. Press ENTER when ready...\n", english, french );
	char c = getchar();

	// Initialize random number generator
	time_t t;
	srand( (unsigned) time(&t) );

	// Create the operations for the selected level
	struct operations* operations = createOperations(level);

	// Loop until there are no more operations left
	while( operations->size > 0 && english > 0 && french > 0 ) {
		int index = rand() % operations->size;

		struct operation operation = operations->operations[index];
		int product;
		int correct_answer = 0;

		// Loop until the answer is correct or the battle is finished
		while( correct_answer == 0 && english > 0) {
			// Prompt and request input
			printf( "LEVEL %d : %d*%d or %d*%d= ", operation.level, operation.factor1, operation.factor2, operation.factor2, operation.factor1 );
			fflush(stdin); // Flush before requesting input to discard any leftover characters
			scanf( "%d", &product ); 

			// Correct answer?
			if( product == ( (operation.factor1) * (operation.factor2) ) ) {
				correct_answer = 1;
				operations = removeOperation( operations, index );
				french--;
				if( french > 0 ) {
					printf( "Yay! One french down!!! English=%d French=%d\n", english, french );
				} else {
					printf( "¡Yay! That was the last French. Game Over! Long live England!\n");
					printf( "%s" , english_flag );
				}
			} else {
				english--;
				if( english > 0 ) {
					printf( "Incorrect! We lost a solider..... :( English=%d French=%d\n", english, french );
				} else {
					printf( "Incorrect! Game Over, no more soldiers to fight! :(\n");
					printf( "%s", french_flag );
				}
			}
		}
	}

	free(operations);
	return 0;
}

