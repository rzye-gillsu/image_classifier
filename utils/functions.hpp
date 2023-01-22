#pragma once

#include "timer.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

#define ti 32
#define to 10000

struct distant_labels
{
    int label;
    float distant;
};

void test(float[][ti], int[]);
void train(float[][ti], int[]);
void feature_extract(float[][IMAGE_SIZE], float[][32], int);
float Mean(float[][IMAGE_SIZE], int, int);
float Std(float[][IMAGE_SIZE], int, int);
float distance(float[], float[]);
void save_distances(float[], float[], float[], int);
void matrix_row_to_array(float[][ti], float[], int);
int K_minimums(int[], float[], distant_labels[], int);
int test_calcualations();
void print(float[][IMAGE_SIZE], int);
void test_algorithem(float[][ti], int[]);
void exploring_images();