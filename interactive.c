#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "imageprocessing.h"
#define MAX_PATH 100
#define MAX_IMAGES 20
#define MAX_DIMENSIONS 3
#define COLORS 3
#define CROP_DIMENSIONS 2

int main() {
  // TODO(catalin.vasile2812) Task 7
  char path[MAX_PATH];
  int ****imagine = (int ****)malloc(MAX_IMAGES * sizeof(int ***));
  char comanda[3];
  float ***filter = (float ***)malloc(MAX_IMAGES * sizeof(float **));
  int *filterIndex = (int *)malloc(sizeof(int));
  int *filterDimesionSize = (int *)malloc(MAX_IMAGES * sizeof(int));
  int **imageDimensions = (int **)malloc(MAX_IMAGES * sizeof(int *));
  for (int q = 0; q < MAX_IMAGES; q++) {
    imageDimensions[q] = (int *)malloc(MAX_DIMENSIONS * sizeof(int));
  }
  int indexCount = 0, imageIndex = 0;
  *filterIndex = 0;
  int *selectedImage = (int *)malloc(sizeof(int));
  int *secondImage = (int *)malloc(sizeof(int));
  scanf("%s", comanda);
  if (strcmp(comanda, "l") == 0) {
    scanf("%d %d", &imageDimensions[indexCount][imageIndex], &imageDimensions[indexCount][imageIndex + 1]);
    scanf("%s", path);
    imagine[indexCount] = (int ***)malloc(imageDimensions[indexCount][imageIndex] * sizeof(int **));
    for (int i = 0; i < imageDimensions[indexCount][imageIndex]; i++) {
      imagine[indexCount][i] = (int **)malloc(imageDimensions[indexCount][imageIndex + 1] * sizeof(int *));
      for (int j = 0; j < imageDimensions[indexCount][imageIndex + 1]; j++) {
        imagine[indexCount][i][j] = (int *)malloc(COLORS * sizeof(int));
      }
    }
    read_from_bmp(imagine[indexCount], imageDimensions[indexCount][imageIndex], imageDimensions[indexCount][imageIndex + 1], path);
    indexCount = indexCount + 1;
  }
  do {
    printf("\n");
    scanf("%s", comanda);
    if (strcmp(comanda, "l") == 0) {
      scanf("%d %d", &imageDimensions[indexCount][imageIndex], &imageDimensions[indexCount][imageIndex + 1]);
      scanf("%s", path);
      imagine[indexCount] = (int ***)malloc(imageDimensions[indexCount][imageIndex] * sizeof(int **));
      for (int i = 0; i < imageDimensions[indexCount][imageIndex]; i++) {
        imagine[indexCount][i] = (int **)malloc(imageDimensions[indexCount][imageIndex + 1] * sizeof(int *));
        for (int j = 0; j < imageDimensions[indexCount][imageIndex + 1]; j++) {
          imagine[indexCount][i][j] = (int *)malloc(COLORS * sizeof(int));
        }
      }
      read_from_bmp(imagine[indexCount], imageDimensions[indexCount][imageIndex], imageDimensions[indexCount][imageIndex + 1], path);
      indexCount = indexCount + 1;
    } else {
      if (strcmp(comanda, "ah") == 0) {
        scanf("%d", selectedImage);
        imagine[*selectedImage] = flip_horizontal(imagine[*selectedImage], imageDimensions[*selectedImage][imageIndex], imageDimensions[*selectedImage][imageIndex + 1]);
      } else {
        if (strcmp(comanda, "s") == 0) {
          scanf("%d", selectedImage);
          scanf("%s", path);
          write_to_bmp(imagine[*selectedImage], imageDimensions[*selectedImage][imageIndex], imageDimensions[*selectedImage][imageIndex + 1], path);
        } else {
          if (strcmp(comanda, "ar") == 0) {
            scanf("%d", selectedImage);
            imagine[*selectedImage] = rotate_left(imagine[*selectedImage], imageDimensions[*selectedImage][imageIndex], imageDimensions[*selectedImage][imageIndex + 1]);
            int *tmp = (int *)malloc(sizeof(int));
            *tmp = 0;
            *tmp = imageDimensions[*selectedImage][imageIndex];
            imageDimensions[*selectedImage][imageIndex] = imageDimensions[*selectedImage][imageIndex + 1];
            imageDimensions[*selectedImage][imageIndex + 1] = *tmp;
            free(tmp);
          } else {
            if (strcmp(comanda, "ac") == 0) {
              scanf("%d", selectedImage);
              int *p1 = (int *)malloc(CROP_DIMENSIONS * sizeof(int));
              scanf("%d", &p1[imageIndex]);
              scanf("%d", &p1[imageIndex + 1]);
              int *dim = (int *)malloc(CROP_DIMENSIONS * sizeof(int));
              scanf("%d", &dim[imageIndex]);
              scanf("%d", &dim[imageIndex + 1]);
              imagine[*selectedImage] = crop(imagine[*selectedImage], imageDimensions[*selectedImage][imageIndex], imageDimensions[*selectedImage][imageIndex + 1], p1[imageIndex],
                                 p1[imageIndex + 1], dim[imageIndex + 1], dim[imageIndex]);
              imageDimensions[*selectedImage][imageIndex] = dim[imageIndex + 1];
              imageDimensions[*selectedImage][imageIndex + 1] = dim[imageIndex];

            } else {
              if (strcmp(comanda, "ae") == 0) {
                scanf("%d", selectedImage);
                int *dimen = (int *)malloc(CROP_DIMENSIONS * sizeof(int));
                int *culori = (int *)malloc(COLORS * sizeof(int));
                for (int i = 0; i < CROP_DIMENSIONS; i++) {
                  scanf("%d", dimen + i);
                }
                for (int i = 0; i < COLORS; i++) {
                  scanf("%d", culori + i);
                }
                imagine[*selectedImage] = extend(imagine[*selectedImage], imageDimensions[*selectedImage][imageIndex], imageDimensions[*selectedImage][imageIndex + 1],
                                     dimen[imageIndex], dimen[imageIndex + 1], culori[imageIndex],
                                     culori[imageIndex + 1], culori[imageIndex + CROP_DIMENSIONS]);
                imageDimensions[*selectedImage][imageIndex] = imageDimensions[*selectedImage][imageIndex] + 2 * dimen[imageIndex];
                imageDimensions[*selectedImage][imageIndex + 1] = imageDimensions[*selectedImage][imageIndex + 1] + 2 * dimen[imageIndex + 1];
                free(dimen);
                free(culori);
              } else {
                if (strcmp(comanda, "ap") == 0) {
                  scanf("%d", selectedImage);
                  scanf("%d", secondImage);
                  int *v = (int *)malloc(CROP_DIMENSIONS * sizeof(int));
                  for (int i = 0; i < CROP_DIMENSIONS; i++) {
                    scanf("%d", v + i);
                  }
                  imagine[*selectedImage] =
                      paste(imagine[*selectedImage], imageDimensions[*selectedImage][imageIndex], imageDimensions[*selectedImage][imageIndex + 1], imagine[*secondImage],
                            imageDimensions[*secondImage][imageIndex], imageDimensions[*secondImage][imageIndex + 1], v[imageIndex], v[imageIndex + 1]);
                  free(v);
                } else {
                  if (strcmp(comanda, "cf") == 0) {
                    scanf("%d", &filterDimesionSize[*filterIndex]);
                    filter[*filterIndex] = (float **)malloc(filterDimesionSize[*filterIndex] * sizeof(float *));
                    for (int i = 0; i < filterDimesionSize[*filterIndex]; i++) {
                      filter[*filterIndex][i] =
                          (float *)malloc(filterDimesionSize[*filterIndex] * sizeof(float));
                    }
                    for (int i = 0; i < filterDimesionSize[*filterIndex]; i++) {
                      for (int j = 0; j < filterDimesionSize[*filterIndex]; j++) {
                        scanf("%f", &filter[*filterIndex][i][j]);
                      }
                    }
                    (*filterIndex) = (*filterIndex) + 1;
                  } else {
                    if (strcmp(comanda, "af") == 0) {
                      scanf("%d", selectedImage);
                      scanf("%d", secondImage);
                      imagine[*selectedImage] =
                          apply_filter(imagine[*selectedImage], imageDimensions[*selectedImage][imageIndex], imageDimensions[*selectedImage][imageIndex + 1],
                                       filter[*secondImage], filterDimesionSize[*secondImage]);
                    } else {
                      if (strcmp(comanda, "df") == 0) {
                        scanf("%d", selectedImage);
                        for (int i = 0; i < filterDimesionSize[*selectedImage]; i++) {
                          free(filter[*selectedImage][i]);
                        }
                        free(filter[*selectedImage]);
                        for (int i = *selectedImage; i < *filterIndex; i++) {
                          filter[i] = filter[i + 1];
                          filterDimesionSize[i] = filterDimesionSize[i + 1];
                        }
                        *filterIndex = *filterIndex - 1;

                      } else {
                        if (strcmp(comanda, "di") == 0) {
                          scanf("%d", selectedImage);
                          for (int i = 0; i < imageDimensions[*selectedImage][imageIndex]; i++) {
                            for (int j = 0; j < imageDimensions[*selectedImage][imageIndex + 1]; j++) {
                              free(imagine[*selectedImage][i][j]);
                            }
                            free(imagine[*selectedImage][i]);
                          }
                          free(imagine[*selectedImage]);
                          for (int i = *selectedImage; i < indexCount; i++) {
                            imagine[i] = imagine[i + 1];
                            imageDimensions[i][imageIndex] = imageDimensions[i + 1][imageIndex];
                            imageDimensions[i][imageIndex + 1] = imageDimensions[i + 1][imageIndex + 1];
                          }
                          indexCount = indexCount - 1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  } while (strcmp(comanda, "e") != 0);
  free(selectedImage);
  free(secondImage);
  for (int i = 0; i < indexCount; i++) {
    if (imagine[i] != NULL) {
      for (int j = 0; j < imageDimensions[i][imageIndex]; j++) {
        for (int k = 0; k < imageDimensions[i][imageIndex + 1]; k++) {
          free(imagine[i][j][k]);
        }
        free(imagine[i][j]);
      }
      free(imagine[i]);
    } else {
        continue;
          }
  }
  free(imagine);
  for (int i = 0; i < (*filterIndex); i++) {
    if (filter[i] != NULL) {
      for (int j = 0; j < filterDimesionSize[i]; j++) {
        free(filter[i][j]);
      }
      free(filter[i]);
    } else {
        continue;
          }
  }
  free(filter);
  for (int i = 0; i < indexCount; i++) {
    free(imageDimensions[i]);
  }
  free(imageDimensions);
  free(filterDimesionSize);
  free(filterIndex);
  return 0;
}