#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct operation {
	int factor1;
	int factor2;
};

struct operations {
	struct operation* operations;
	int size;
};

struct operations* createOperations() {
	struct operations* answer = malloc( sizeof( struct operations) );
	answer->operations = malloc( sizeof(struct operation)*100 );
	for( int i = 0; i < 10; i++ ) {
		for( int j = 0; j < 10; j++ ) {
			answer->operations[(i*10)+j].factor1 = i;
			answer->operations[(i*10)+j].factor2 = j;
		}
	}
	answer->size = 100;
	return answer;
}

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

int main( int argc, char* argv[] ) {
	int romans = 100;
	int french = 100;
	printf( "Battle of Pavia against the french! %d romans and %d french. Press ENTER when ready...\n", romans, french );
	char c = getchar();

	// Initialize random number generator
	time_t t;
	srand( (unsigned) time(&t) );

	struct operations* operations = createOperations();

	// Loop until there are no more operations left
	while( operations->size > 0 && romans > 0 && french > 0 ) {
		int index = rand() % operations->size;

		struct operation operation = operations->operations[index];
		int test;
		int correct_answer = 0;

		// Loop until the answer is correct or the battle is finished
		while( correct_answer == 0 && romans > 0) {
			// Prompt and request input
			printf( "%d*?=%d\n", operation.factor1, operation.factor1 * operation.factor2 );
			printf( "? = " );
			fflush(stdin); // Flush before requesting input to discard any leftover characters
			scanf( "%d", &test ); 

			// Check input vs. operation
			if( (operation.factor1 * test) == (operation.factor1 * operation.factor2) ) {
				correct_answer = 1;
				operations = removeOperation( operations, index );
				french--;
				if( french > 0 ) {
					printf( "Correct! One French down!!! Romans=%d French=%d\n", romans, french );
				} else {
 					printf( "Correct! That was the last French. Game over! Long live the Holy Roman Empire!\n");
				}
			} else {
				romans--;
				if( romans > 0 ) {
					printf( "Incorrect! We lost a soldier... :( Romans=%d French=%d\n", romans, french );
				} else {
					printf( "Incorrect! Game over! No more soldiers to fight! :( \n");
				}
			}
		}
	}

	free(operations);
	return 0;
}

