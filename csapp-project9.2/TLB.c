//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "clock.h"

#define NPAD 511
#define MinSize 1<<10
#define MaxSize 1<<24
#define CYCLE_TIME (1 / 2.5 / 1000 /1000)

struct l {
	struct l *n;
	long long pad[NPAD];
};

int main()
{
	int size,i;
	for (size = MinSize; size <= MaxSize; size = size <<1)
	{
		struct l *first = (struct l *)malloc(sizeof(struct l));
		if (first == NULL)
		{
			printf("%s\n", "malloc failed.");
			exit(0);
		}

		first->n = first;
		struct l *tmp = first;

		for (i = 0; i < size /64; i++)
		{
			struct l *node = (struct l *)malloc(sizeof(struct l));
			if (node == NULL)
			{
				printf("%s\n", "malloc failed.");
				exit(0);
			}
			node->n = first;
			tmp->n = node;
			tmp = node;
		}

		struct l *t = first;
		//clock_t start, end;
		double cyc = 0.0;
		//start = clock();
		start_comp_counter();
		do
		{
			t = t->n;
		} while (t->n != first);
		//end = clock();
		cyc=get_comp_counter();
		printf("%s", "cost_time: ");
		//time = (end - start);
		printf("%.10f\n", cyc/ (size / 64));
	}

	system("pause");
    return 0;
}

