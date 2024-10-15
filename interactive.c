#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

#define MAX 1000
#define MAX_PATH 100

int main()
{
    char c[3]; // Command input
    int k = 0, i = 0, j = 0, p = 0;
    int ****image = NULL, N[MAX], M[MAX];
    float ***filter = NULL;
    int size[MAX];
    scanf("%s", c);

    // Main loop to process commands
    while (1)
    {
        // Exit program and free allocated memory when 'e' is entered
        if (strcmp(c, "e") == 0)
        {
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < N[i]; j++)
                {
                    for (int l = 0; l < M[i]; l++)
                    {
                        free(image[i][j][l]);
                    }
                    free(image[i][j]);
                }
                free(image[i]);
            }
            free(image);
            for (i = 0; i < p; i++)
            {
                for (j = 0; j < size[i]; j++)
                {
                    free(filter[i][j]);
                }
                free(filter[i]);
            }
            free(filter);
            break;
        }
        // Load an image from a file
        else if (strcmp(c, "l") == 0)
        {
            char path1[MAX_PATH];                 // Path to BMP file
            scanf("%d%d%s", &N[k], &M[k], path1); // Input image dimensions and file path

            // Allocate memory for the new image
            image = (int ****)realloc(image, (k + 1) * sizeof(int ***));
            image[k] = (int ***)malloc(N[k] * sizeof(int **));

            for (i = 0; i < N[k]; i++)
            {
                image[k][i] = (int **)malloc(M[k] * sizeof(int *));
                for (j = 0; j < M[k]; j++)
                {
                    image[k][i][j] = (int *)malloc(3 * sizeof(int));
                }
            }

            read_from_bmp(image[k], N[k], M[k], path1);
            k++;
        }
        // Save an image to a BMP file
        else if (strcmp(c, "s") == 0)
        {
            int index = 0;
            char path2[MAX_PATH];
            scanf("%d%s", &index, path2);
            write_to_bmp(image[index], N[index], M[index], path2);
        }
        // Flip an image horizontally
        else if (strcmp(c, "ah") == 0)
        {
            int index = 0;
            scanf("%d", &index);
            image[index] = flip_horizontal(image[index], N[index], M[index]);
        }
        // Rotate an image 90 degrees to the left
        else if (strcmp(c, "ar") == 0)
        {
            int index = 0;
            scanf("%d", &index);
            image[index] = rotate_left(image[index], N[index], M[index]);

            int a = N[index];
            N[index] = M[index];
            M[index] = a;
        }
        // Crop an image
        else if (strcmp(c, "ac") == 0)
        {
            int index = 0, x = 0, y = 0, w = 0, h = 0;
            scanf("%d%d%d%d%d", &index, &x, &y, &w, &h);
            image[index] = crop(image[index], N[index], M[index], x, y, h, w);

            N[index] = h;
            M[index] = w;
        }
        // Extend an image by adding borders
        else if (strcmp(c, "ae") == 0)
        {
            int index = 0, rows = 0, cols = 0, R = 0, G = 0, B = 0;
            scanf("%d%d%d%d%d%d", &index, &rows, &cols, &R, &G, &B);
            image[index] = extend(image[index], N[index], M[index], rows, cols, R, G, B);
            N[index] = N[index] + 2 * rows;
            M[index] = M[index] + 2 * cols;
        }
        // Paste one image onto another
        else if (strcmp(c, "ap") == 0)
        {
            int index_dst = 0, index_src = 0, x = 0, y = 0;
            scanf("%d%d%d%d", &index_dst, &index_src, &x, &y);
            image[index_dst] = paste(image[index_dst], N[index_dst], M[index_dst], image[index_src], N[index_src],
                                     M[index_src], x, y);
        }
        // Create a filter matrix
        else if (strcmp(c, "cf") == 0)
        {
            scanf("%d", &size[p]);

            // Allocate memory for the new filter
            filter = (float ***)realloc(filter, (p + 1) * sizeof(float **));
            filter[p] = (float **)malloc(size[p] * sizeof(float *));
            for (i = 0; i < size[p]; i++)
            {
                filter[p][i] = (float *)malloc(size[p] * sizeof(float));
                for (j = 0; j < size[p]; j++)
                {
                    scanf("%f", &filter[p][i][j]);
                }
            }
            p++;
        }
        // Apply a filter to an image
        else if (strcmp(c, "af") == 0)
        {
            int index_img = 0, index_filter = 0;
            scanf("%d%d", &index_img, &index_filter);
            image[index_img] = apply_filter(image[index_img], N[index_img], M[index_img], filter[index_filter],
                                            size[index_filter]);
        }
        // Delete a filter
        else if (strcmp(c, "df") == 0)
        {
            int index_filter = 0;
            scanf("%d", &index_filter);
            for (i = 0; i < size[index_filter]; i++)
            {
                free(filter[index_filter][i]);
            }

            free(filter[index_filter]);
            for (int l = index_filter; l < p - 1; l++)
            {
                filter[l] = filter[l + 1];
                size[l] = size[l + 1];
            }

            p--;
        }
        // Delete an image
        else if (strcmp(c, "di") == 0)
        {
            int index_img = 0;
            scanf("%d", &index_img);
            for (i = 0; i < N[index_img]; i++)
            {
                for (j = 0; j < M[index_img]; j++)
                {
                    free(image[index_img][i][j]);
                }
                free(image[index_img][i]);
            }
            free(image[index_img]);
            for (i = index_img; i < k - 1; i++)
            {
                image[i] = image[i + 1];
                N[i] = N[i + 1];
                M[i] = M[i + 1];
            }
            k--;
        }
        // Read the next command
        scanf("%s", c);
    }
    return 0;
}
