#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

// Function to flip an image horizontally
int ***flip_horizontal(int ***image, int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M / 2; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int aux = image[i][j][k];
                image[i][j][k] = image[i][M - 1 - j][k];
                image[i][M - 1 - j][k] = aux;
            }
        }
    }
    return image;
}

// Function to rotate an image 90 degrees to the left
int ***rotate_left(int ***image, int N, int M)
{
    int ***rimage = (int ***)malloc(M * sizeof(int **));
    for (int i = 0; i < M; i++)
    {
        rimage[i] = (int **)malloc(N * sizeof(int *));
        for (int j = 0; j < N; j++)
        {
            rimage[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                rimage[M - 1 - j][i][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return rimage;
}

// Function to crop a section of an image
int ***crop(int ***image, int N, int M, int x, int y, int h, int w)
{
    int ***cimage = (int ***)malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++)
    {
        cimage[i] = (int **)malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++)
        {
            cimage[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cimage[i][j][k] = image[y + i][x + j][k];
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return cimage;
}

// Function to extend an image with new rows/columns and fill border pixels
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B)
{
    int n = N + 2 * rows;
    int m = M + 2 * cols;
    int ***eimage = (int ***)malloc(n * sizeof(int **));
    for (int i = 0; i < n; i++)
    {
        eimage[i] = (int **)malloc(m * sizeof(int *));
        for (int j = 0; j < m; j++)
        {
            eimage[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                eimage[i + rows][j + cols][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i < rows || i >= N + rows || j < cols || j >= M + cols)
            {
                eimage[i][j][0] = new_R;
                eimage[i][j][1] = new_G;
                eimage[i][j][2] = new_B;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return eimage;
}

// Function to paste a source image onto a destination image at a specific location
int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y)
{
    if ((y + N_src > N_dst) && (x + M_src > M_dst))
    {
        for (int i = 0; i < N_dst - y; i++)
        {
            for (int j = 0; j < M_dst - x; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    image_dst[i + y][j + x][k] = image_src[i][j][k];
                }
            }
        }
    }
    else if ((y + N_src > N_dst) && (x + M_src <= M_dst))
    {
        for (int i = 0; i < N_dst - y; i++)
        {
            for (int j = 0; j < M_src; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    image_dst[i + y][j + x][k] = image_src[i][j][k];
                }
            }
        }
    }
    else if ((y + N_src <= N_dst) && (x + M_src > M_dst))
    {
        for (int i = 0; i < N_src; i++)
        {
            for (int j = 0; j < M_dst - x; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    image_dst[i + y][j + x][k] = image_src[i][j][k];
                }
            }
        }
    }
    else if ((y + N_src <= N_dst) && (x + M_src <= M_dst))
    {
        for (int i = 0; i < N_src; i++)
        {
            for (int j = 0; j < M_src; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    image_dst[i + y][j + x][k] = image_src[i][j][k];
                }
            }
        }
    }
    return image_dst;
}

// Function to apply a filter to an image
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size)
{
    const int min = 0;
    const int max = 255;
    int ***fimage = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++)
    {
        fimage[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++)
        {
            fimage[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                float s = 0;
                for (int a = 0; a < filter_size; a++)
                {
                    for (int b = 0; b < filter_size; b++)
                    {
                        int u = i - filter_size / 2 + a;
                        int v = j - filter_size / 2 + b;
                        if (u < 0 || u >= N || v < 0 || v >= M)
                        {
                            s += 0;
                        }
                        else
                        {
                            s += (float)image[u][v][k] * filter[a][b];
                        }
                    }
                }
                fimage[i][j][k] = (int)s;
                if (fimage[i][j][k] < min)
                {
                    fimage[i][j][k] = min;
                }
                else if (fimage[i][j][k] > max)
                {
                    fimage[i][j][k] = max;
                }
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                image[i][j][k] = fimage[i][j][k];
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            free(fimage[i][j]);
        }
        free(fimage[i]);
    }
    free(fimage);
    return image;
}
