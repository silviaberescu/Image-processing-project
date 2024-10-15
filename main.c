#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#include "bmp.h"

// This is a sample file to demonstrate
// how to use the functions read_from_bmp and write_to_bmp

// You can use this file for manually testing
// the functions in imageprocessing.c

int main()
{
    // Allocate a matrix for the image

    int N = 789, M = 1024;
    int ***m = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++)
    {
        m[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++)
        {
            m[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

    read_from_bmp(m, N, M, "./4964064451_25410b9741_b.bmp");

    // Little image processing as an exemple

    // Add a red band to add to the image
    for (int i = 20; i < 40; i++)
    {
        for (int j = 0; j < M; j++)
        {
            m[i][j][0] = 255;
        }
    }

    // Add a green band to image
    for (int j = 100; j < 200; j++)
    {
        for (int i = 0; i < N; i++)
        {
            m[i][j][1] = 255;
        }
    }

    // Save the image to output.bmp
    write_to_bmp(m, N, M, "./output.bmp");

    // free matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            free(m[i][j]);
        }
        free(m[i]);
    }
    free(m);

    // Test the flip_horizontal function

    /* flip_horizontal(m, N, M);
    write_to_bmp(m, N, M, "./flipped_horizontal.bmp");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(m[i][j]);
        }
        free(m[i]);
    }
    free(m); */

    // Test the rotate_left function

    /* int ***rotated_image = rotate_left(m, N, M);
    if (rotated_image != NULL) {
        write_to_bmp(rotated_image, M, N, "./rotated_left.bmp"); // Note: dimensions are swapped after rotation

        // Free the rotated image matrix
        for (int i = 0; i < M; i++) { // Assuming rotated image has dimensions (M x N)
            for (int j = 0; j < N; j++) {
                free(rotated_image[i][j]);
            }
            free(rotated_image[i]);
        }
        free(rotated_image);
    } */
    // mica procesare pe imagine ca exemplu

    /*// adaugam o banda orizontala rosie
    for (int i=20; i<40; i++) {
        for (int j=0; j<M; j++) {
            m[i][j][0] = 255;
        }
    }

    // adaugam o banda verticala verde
    for (int j=100; j<200; j++) {
        for (int i=0; i<N; i++) {
            m[i][j][1] = 255;
        }
    }

    // salvam imaginea sub numele output.bmp
    write_to_bmp(m, N, M, "./output.bmp");*/

    // free matrice
    /*for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(m[i][j]);
        }
        free(m[i]);
    }
    free(m);*/

    printf("Done\n");
    return 0;
}
