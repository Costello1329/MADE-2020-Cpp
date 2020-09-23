#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"


int32_t count_det (int32_t* numbers);

int main () {
	int32_t* numbers = malloc(sizeof(int32_t) * 9);
	
	for (uint8_t i = 0; i < 9; ++ i)
		scanf("%d", &numbers[i]);

	const int32_t det = count_det(numbers);

	printf("%d\n", det);

	free(numbers);

	return 0;
}

