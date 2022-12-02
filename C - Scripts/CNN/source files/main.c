#include <stdio.h>
#include <stdbool.h>
#include "cnn_params.h"
#include "Test_Sample.h"

// number of parameter for conv layer: in_ch * out_ch * kernel_size
// number of parameters for dense layer: in_dim * out_dim
void conv(float output[], int out_ch, int out_dim, int ker_dim, int in_ch, int in_dim, int stride, int padding, float weight[], float bias[], float input[]);
void pool(float output[], int out_ch, int out_dim, int ker_dim, int in_dim, int stride, int padding, float input[]);
void flatten(float output[], int out_ch, int out_dim, float input[]);
void fully_connected (float output[], int out_dim, int in_dim, float weight[], float bias[], float input[]);
void fully_connected_fused_relu(float output[], int out_dim, int in_dim, float weight[], float bias[], float input[]);
int softmax(float output[], int out_dim, int prediction, float input[]);
int cnn(float X[]);

int main()
{
    int result;
    float correct = 0;
    float accuracy;
    for (int i = 0; i < N_SAMPLE; i++)
    {
        for(int  j= 0; j < SAMPLE_DIM; j+=16)
        {
            for(int k = 0; k < 16; k++) // 16 corresponds to the number of sensors
            {
                data[i][j+k] = (data[i][j+k] - data_min[k])/(data_max[k] - data_min[k]);
            }
        }
        result = cnn(data[i]);
        printf("Result: %d\n", result);
    }
}
int cnn(float X[])
{
    int prediction;
    float buffer1[CONV1_OUT_CH*CONV1_OUT_DIM];
    float buffer2[CONV2_OUT_CH*CONV2_OUT_DIM];
    conv(buffer1, CONV1_OUT_CH, CONV1_OUT_DIM, CONV1_KER_SIZE, CONV1_IN_CH, CONV1_IN_DIM, CONV1_STRIDE, CONV1_PADDING, conv1_wt, conv1_bias, X);
    pool(buffer2, POOL1_CH, POOL1_OUT_DIM, POOL1_KER_SIZE, POOL1_IN_DIM, POOL1_STRIDE, POOL1_PADDING, buffer1);
    conv(buffer1, CONV2_OUT_CH, CONV2_OUT_DIM, CONV2_KER_SIZE, CONV2_IN_CH, CONV2_IN_DIM, CONV2_STRIDE, CONV2_PADDING, conv2_wt, conv2_bias, buffer2);
    pool(buffer2, POOL2_CH, POOL2_OUT_DIM, POOL2_KER_SIZE, POOL2_IN_DIM, POOL2_STRIDE, POOL2_PADDING, buffer1);
    fully_connected_fused_relu(buffer1, FC1_OUT_DIM, FC1_IN_DIM, fc1_wt , fc1_bias, buffer2);
    fully_connected(buffer2, FC2_OUT_DIM, FC2_IN_DIM, fc2_wt , fc2_bias, buffer1);
    prediction = softmax(buffer1, FC2_OUT_DIM, prediction, buffer2);
    return prediction;
}
