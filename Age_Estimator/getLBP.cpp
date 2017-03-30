#include <stdio.h>

void getLBP(unsigned char** matrix, int width, int height, int* histogram) {
	unsigned char pattern;

	// histogram size is 256
	for(int i = 0; i < 256; i++)
		histogram[i] = 0;

	for(int i = 1; i < height-1; i++) {
		for(int j = 1; j < width-1; j++) {
			pattern = 0;
			if(matrix[i-1][j-1] > matrix[i][j]) pattern += 128;  // top left
			if(matrix[i-1][j] > matrix[i][j])   pattern += 64;   // top
			if(matrix[i-1][j+1] > matrix[i][j]) pattern += 32;   // top right
			if(matrix[i][j+1] > matrix[i][j])   pattern += 16;   // right
			if(matrix[i+1][j+1] > matrix[i][j]) pattern += 8;    // bottom right
			if(matrix[i+1][j] > matrix[i][j])   pattern += 4;    // bottom
			if(matrix[i+1][j-1] > matrix[i][j]) pattern += 2;    // bottom left
			if(matrix[i][j-1] > matrix[i][j])   pattern += 1;    // left
			histogram[pattern] += 1;
		}
	}

}

			




