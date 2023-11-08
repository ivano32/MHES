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
	int english = 100;
	int french = 100;
	printf( "Battle against the French! %d English %d French. Press ENTER when ready...\n", english, french );
	char c = getchar();

	// Initialize random number generator
	time_t t;
	srand( (unsigned) time(&t) );

	struct operations* operations = createOperations();

	// Loop until there are no more operations left
	while( operations->size > 0 && english > 0 && french > 0 ) {
		int index = rand() % operations->size;

		struct operation operation = operations->operations[index];
		int product;
		int correct_answer = 0;

		// Loop until the answer is correct or the battle is finished
		while( correct_answer == 0 && english > 0) {
			// Prompt and request input
			printf( "%d*%d or %d*%d= ", operation.factor1, operation.factor2, operation.factor2, operation.factor1 );
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
				}
			} else {
				english--;
				if( english > 0 ) {
					printf( "Incorrect! We lost a solider..... :( English=%d French=%d\n", english, french );
				} else {
					printf( "Incorrect! Game Over, no more soldiers to fight! :(\n");
				}
			}
		}
	}

	free(operations);
	return 0;
}

