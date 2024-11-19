#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#define colors 3
#define maxim 255
void free_mem(int ***x, int lines, int columns) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            free(x[i][j]);
        }
        free(x[i]);
    }
    free(x);
}


int ***flip_horizontal(int ***image, int N, int M) {
    int aux = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M / 2; j++) {
            for (int k = 0; k < colors; k++) {
                aux = image[i][j][k];
                image[i][j][k] = image[i][M - j - 1][k];
                image[i][M - j - 1][k] = aux;
                aux = 0;
            }
        }
    }
    return image;
}


int ***rotate_left(int ***image, int N, int M) {
    int ***p = (int ***)malloc(M * sizeof(int **));
    for (int i = 0; i < M; i++) {
        p[i] = (int **)malloc(N * sizeof(int *));
        for (int j = 0; j < N; j++) {
            p[i][j] = (int *)malloc(colors * sizeof(int));
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < colors; k++) {
                p[i][j][k] = image[j][M - i - 1][k];
            }
        }
    }
    free_mem(image, N, M);
    return p;
}


int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***m = (int ***)malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++) {
        m[i] = (int **)malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++) {
            m[i][j] = (int *)malloc(colors * sizeof(int));
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < colors; k++) {
                m[i][j][k] = image[i + y][j + x][k];
            }
        }
    }
    free_mem(image , N, M);
    return m;
}


int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int linii = N + 2 * rows;
    int coloane = M + 2 * cols;
    int ***e = (int ***)malloc(linii * sizeof(int **));
    for (int i = 0; i < linii; i++) {
        e[i] = (int **)malloc(coloane * sizeof(int *));
        for (int j = 0; j < coloane; j++) {
            e[i][j] = (int *)malloc(colors * sizeof(int));
        }
    }
    for (int i = 0; i < linii; i++) {
        for (int j = 0; j < coloane; j++) {
            for (int k = 0; k < colors; k++) {
                if ((i >= rows && i<= rows + N - 1) && (j >= cols && j <= cols + M - 1)) {
                    e[i][j][k] = image[i - rows][j - cols][k];
                } else {
                    if (k == 0) {
                        e[i][j][k] = new_R;
                    } else if (k == 1) {
                        e[i][j][k] = new_G;
                                        } else if (k == 2) {
                                            e[i][j][k] = new_B;
                                                            }
                        }
            }
        }
    }
    free_mem(image, N, M);
    return e;
}


int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    for (int i = 0; i < N_dst; i++) {
        for (int j = 0; j < M_dst; j++) {
            for (int k = 0; k < colors; k++) {
                if (i >= y && i <= y + N_src - 1 && j >= x && j <= x + M_src - 1) {
                    image_dst[i][j][k] = image_src[i - y][j - x][k];
                } else {
                    continue;
                        }
            }
        }
    }
    return image_dst;
}


int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int size = filter_size / 2;
    int ***m = extend(image, N, M, size, size, 0, 0, 0);
    int linii = N + 2 * size;
    int coloane = M + 2 * size;
    float ***mfl = (float ***)malloc(linii * sizeof(float **));
    for (int i = 0; i < linii; i++) {
        mfl[i] = (float **)malloc(coloane * sizeof(float *));
        for (int j = 0; j < coloane; j++) {
            mfl[i][j] = (float *)malloc(colors * sizeof(float));
        }
    }
    for (int i = 0; i < linii; i++) {
        for (int j = 0; j < coloane; j++) {
            for (int k = 0; k < colors; k++) {
                if ((i < size || i > linii - size - 1) && (j < size || j > coloane - size - 1)) {
                    mfl[i][j][k] = 0;
                } else {
                    continue;
                        }
            }
        }
    }
    for (int i = size; i < N + size; i++) {
        for (int j = size; j < M + size; j++) {
            for (int k = 0; k < colors; k++) {
                float aux = 0;
                for (int u = i - size, w = 0; u <= i + size && w < filter_size; u++, w++) {
                    for (int v = j - size, y = 0; v <= j + size && y < filter_size; v++, y++) {
                        aux =(float)aux + (float)m[u][v][k] * filter[w][y];
                    }
                }
                mfl[i][j][k] = aux;
            }
        }
    }
    for (int i = 0; i < linii; i++) {
        for (int j = 0; j < coloane; j++) {
            for (int k = 0; k < colors; k++) {
                if (mfl[i][j][k] > maxim) {
                    mfl[i][j][k] = maxim;
                }
                if (mfl[i][j][k] < 0) {
                    mfl[i][j][k] = 0;
                } else {
                    continue;
                        }
            }
        }
    }
    for (int i = 0; i < linii; i++) {
        for (int j = 0; j < coloane; j++) {
            for (int k = 0; k < colors; k++) {
                m[i][j][k] = (int)mfl[i][j][k];
            }
        }
    }
    int ***c = crop(m, linii, coloane, size, size, N, M);
    for (int i = 0; i < linii; i++) {
        for (int j = 0; j < coloane; j++) {
            free(mfl[i][j]);
        }
        free(mfl[i]);
    }
    free(mfl);
    return c;
}
