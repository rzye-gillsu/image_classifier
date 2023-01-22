#include "functions.hpp"

// This function extract 32 numbers from the matrix -img- and add each 32 nums to each of the rows of matrix -matrix-.
void feature_extract(float img[][IMAGE_SIZE], float matrix[][ti], int row)
{
    int count = 0;
    for (int i = 0; i < 4; i++)     // i shows the rows
        for (int j = 0; j < 4; j++) // j shows the columns
        {
            matrix[row][count++] = Mean(img, i, j);
            matrix[row][count++] = Std(img, i, j);
        }
}

// This function calculates the average of 1/16 martix -img-'s numbers.
float Mean(float img[][IMAGE_SIZE], int i, int j)
{
    float sum = 0.0;

    for (int q = i * 7; q < (i + 1) * 7; q++)
        for (int z = j * 7; z < (j + 1) * 7; z++)
            sum += img[q][z];

    float avg = sum / 49.0;
    return avg;
}

// This function calculates the standard deviation of 1/16 matrix -img- numbers using -Mean- function.
float Std(float img[][IMAGE_SIZE], int i, int j)
{
    float sum = 0.0, avg = Mean(img, i, j);

    for (int q = i * 7; q < (i + 1) * 7; q++)
        for (int z = j * 7; z < (j + 1) * 7; z++)
            sum += pow((img[q][z] - avg), 2);

    float std = sqrt(sum / 48.0);
    return std;
}

// This function gets 2 arrays and calculates the Euclidian distance between them.
float distance(float t_data[], float input[])
{
    float sum = 0.0;
    for (int i = 0; i < ti; i++)
    {
        sum += pow((t_data[i] - input[i]), 2);
    }
    float d = sqrt(sum);
    return d;
}

// This fucntion save distances gotten from function "distance" into an array called "distances".
void save_distances(float t_data[], float input_array[], float distances[], int row)
{
    float distant = distance(t_data, input_array);
    distances[row] = distant;
}

// It gets a row and a matrix and changes that row to an array called "t_data" -> which stands for train data.
void matrix_row_to_array(float matrix[][ti], float t_data[], int row)
{
    for (int i = 0; i < ti; i++)
        t_data[i] = matrix[row][i];
}

// This function is implemented to test the execution of the functions -Mean- , -Std- and -distance-
int test_calcualations()
{
    float matri[28][28]{
        {0., 1., 0., 2., 0., 3., 0.},
        {0., 1., 0., 2., 0., 3., 0.},
        {1., 0., 2., 0., 3., 0., 4.},
        {0., 1., 0., 2., 0., 3., 0.},
        {1., 0., 2., 0., 3., 0., 4.},
        {0., 1., 0., 2., 0., 3., 0.},
        {1., 0., 2., 0., 3., 0., 4.}};
    int M = Mean(matri, 0, 0); // answer : 1.102
    int S = Std(matri, 0, 0);  // answer : 1.342

    float arra1[32] = {1., 2., 3.}, arra2[32] = {4., 5., 6.};
    int D = distance(arra1, arra2); // answer : 27.000

    // cout <<  M << "    " << S << "    " << D << "    " << endl;

    if ((M == 1) && (S == 1) && (D == 5))
        return 0;
    return 1;
}

// It extract features from the 10 floders data.dat files. And add them to row of the matrix "matrix".
void train(float matrix[][ti], int label[])
{
    int row = 0;
    float img[IMAGE_SIZE][IMAGE_SIZE];
    srand((unsigned)time(0));
    while (row < to)
        for (int i = 0; i < 10; i++)
        {
            string image_path = interpolation("data\\mnist", "train", i);
            for (int j = 0; j < 1000; j++)
            {
                int q = (rand() % 1000) + 1;
                load_image(image_path, q, img);
                feature_extract(img, matrix, row);
                label[row] = i;
                row++;
            }
        }
}

// This function put each dustant and it's label in a struct called dl. Sort it descendingly and seperate the k first ones. Then We count the repeated ones and return the label which has the maximum count.
int K_minimums(int label[], float distances[], distant_labels dl[], int k)
{
    for (int i = 0; i < to; i++)
    {
        dl[i].label = label[i];
        dl[i].distant = distances[i];
    }

    float temp;
    for (int i = 0; i < to - 1; i++)
    {
        for (int j = 0; j < (to - i - 1); j++)
        {
            if (dl[j].distant > dl[j + 1].distant)
            {
                temp = dl[j].distant;
                dl[j].distant = dl[j + 1].distant;
                dl[j + 1].distant = temp;

                temp = dl[j].label;
                dl[j].label = dl[j + 1].label;
                dl[j + 1].label = temp;
            }
        }
    }

    int max = 0, lab;
    for (int i = 0; i < k; i++)
    {
        int count = 0;
        for (int j = i + 1; j < k; j++)
            if (dl[i].label == dl[j].label)
                count++;

        if (count > max)
        {
            max = count;
            lab = dl[i].label;
        }
    }

    return lab;
}

// This function prints the chosen image.
void print(float img[][IMAGE_SIZE], int folder_name)
{
    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        for (int j = 0; j < IMAGE_SIZE; j++)
        {
            if (img[i][j] == 0.)
                cout << ' ';
            else
                cout << folder_name;
        }
        cout << endl;
    }
}

void test(float matrix[][ti], int label[to])
{
    float img[IMAGE_SIZE][IMAGE_SIZE], input_matrix[1][ti];

    int folder_name, image_number;
    cout << "Folder name: ";
    cin >> folder_name;
    cout << "Image number: ";
    cin >> image_number;
    string image_path = interpolation("data\\mnist", "test", folder_name);
    load_image(image_path, image_number, img);
    feature_extract(img, input_matrix, 0);

    print(img, folder_name);

    // main part *****************************************************************
    float t_data[ti], input_array[ti], distances[to];
    matrix_row_to_array(input_matrix, input_array, 0);

    for (int i = 0; i < to; i++)
    {
        matrix_row_to_array(matrix, t_data, i);
        save_distances(t_data, input_array, distances, i); // now array "distances" contains '30000' numbers which are the distance between features of input_array and t_data
    }

    int k;
    cout << "K would be: ";
    cin >> k;

    distant_labels dl[to];
    int lab = K_minimums(label, distances, dl, k);

    cout << "The first K labels which are closest in shape to the input image: ";
    for (int i = 0; i < k; i++)
    {
        cout << dl[i].label << "  ";
    }
    cout << "\n\n";
    cout << "The distance between the input image and the k nearest images: ";
    for (int i = 0; i < k; i++)
    {
        cout << dl[i].distant << "  ";
    }
    cout << "\n\n";

    cout << "The image is : " << lab << endl
         << endl;

    // *****************************************************************************
    // to test the functions :
    cout << "Result of the test:" << endl;
    if (test_calcualations() == 0)
        cout << "Functions -Mean-, -Sti- and -distance- work properly." << endl;
    else
        cout << "There is sth wrong with Functions -Mean-, -Sti- and -distance-" << endl;
}

void test_algorithem_training(float matrix[][ti])
{
    int row = 0;
    float img[IMAGE_SIZE][IMAGE_SIZE];
    while (row < to)
    {
        string image_path = interpolation("data\\mnist", "test", 6);
        for (int i = 1; i <= 5000; i++)
        {
            load_image(image_path, i, img);
            feature_extract(img, matrix, row);
            row++;
        }
    }
}

void test_algorithem(float matrix[][ti], int label[])
{
    cout << "We will calculate the accuracy on some random images from your chosen folder." << endl
         << "folder name(choose between 0-9):  ";
    int folder_name;
    cin >> folder_name;
    float img[IMAGE_SIZE][IMAGE_SIZE], test_mat[1][ti], test_arr[ti], train_arr[ti], distances[to];
    int count = 0;

    string image_path = interpolation("data\\mnist", "test", folder_name);
    cout << "100 random image numbers will be chosen and we will test the accuracy on them." << endl;
    cout << "Random image numbers of folder (" << folder_name << "):  ";
    srand((unsigned)time(0));
    int q;
    for (int i = 0; i < 100; i++)
    {
        q = (rand() % 500) + 1;
        cout << q << "  ";

        load_image(image_path, q, img);
        feature_extract(img, test_mat, 0);
        matrix_row_to_array(test_mat, test_arr, 0);

        for (int j = 0; j < to; j++)
        {
            matrix_row_to_array(matrix, train_arr, j);
            save_distances(train_arr, test_arr, distances, j); // now array "distances" contains '30000' numbers which are the distance between features of input_array and t_data
        }
        distant_labels dl[to];
        int lab = K_minimums(label, distances, dl, 20);
        if (lab == folder_name)
            count++;
    }
    cout << endl
         << "The accuracy of this algorithem for number (" << folder_name << ") is : " << count << endl;
}

void exploring_images()
{
    float img[IMAGE_SIZE][IMAGE_SIZE];
    int folder_name, image_number;
    cout << "Folder name: ";
    cin >> folder_name;
    cout << "Image number: ";
    cin >> image_number;
    string image_path = interpolation("data\\mnist", "test", folder_name);
    load_image(image_path, image_number, img);
    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        for (int j = 0; j < IMAGE_SIZE; j++)
        {
            if (img[i][j] == 0.)
                cout << ' ';
            else
                cout << folder_name;
        }
        cout << endl;
    }
}