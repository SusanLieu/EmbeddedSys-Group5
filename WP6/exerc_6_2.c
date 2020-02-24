// Program for exercise 6.2alt in DIT632
// Version 2020-02-12
// File : sortandfind_20.c
// **************************************
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define num_elems 200

int array[200];
int max_value;
int search;

void *runner1(void *param);
void *runner2(void *param);
void *runner3(void *param);

int main() {
	time_t t;
	pthread_t tid;
  pthread_t tid2;
  pthread_t tid3;
	pthread_attr_t attr;
	
	srand((unsigned) time(&t));
	pthread_attr_init(&attr);

	printf("Enter max value\n");
	scanf("%d", &max_value);

	pthread_create(&tid, &attr, runner1, NULL);
	pthread_join(tid, NULL);

  pthread_create(&tid2, &attr, runner2, NULL);
	pthread_join(tid2, NULL);

  pthread_create(&tid3, &attr, runner3, NULL);
	pthread_join(tid3, NULL);

	return 0;
}

void *runner1(void *param) {
  puts("Executing runner 1");
	int c = 0, n=0;

	for (c = 0; c < num_elems; c++) {
		for(n=0; n<1000; n++); // To delay a bit 
		array[c] = rand() % max_value;
	}

	pthread_exit(0);
}

void *runner2(void *param) {
  puts("Executing runner 2");

  int c, d, swap;

	for (c = 0; c < num_elems; c++) {
		for (d = 0; d < num_elems - c - 1; d++) {
			if (array[d] > array[d + 1]) {
				swap = array[d];
				array[d] = array[d + 1];
				array[d + 1] = swap;
			}
		}
	}

	pthread_exit(0);
}

void *runner3(void *param){
	int search;
  puts("Executing runner 3");

	printf("Enter value to find\n");
	scanf("%d", &search);

  int first = 0;
	int last = num_elems - 1;
	int middle = (first + last) / 2;
	int n;
	/*for(n=0; n<num_elems; n++){
	    printf("\n %d", array[n]);
	}*/

	while (first <= last) {
		if (array[middle] < search)
			first = middle + 1;
		else if (array[middle] == search) {
			printf("\n %d found at location %d.\n", search, middle + 1);
			break;
		} else
			last = middle - 1;

		middle = (first + last) / 2;
	}
	if (first > last)
		printf("\n Not found! %d is not present in the list.\n", search);

  pthread_exit(0);
}