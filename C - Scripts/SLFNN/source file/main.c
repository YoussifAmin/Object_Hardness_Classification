#include <stdio.h>
#include <math.h>
#include "nn_params.h"
#include "Test_Sample.h"
// #include "main.h"

#define N_CLASS 5
#define INPUT_DIM 32
#define BUFFER_SIZE 100


//extern UART_HandleTypeDef huart3;
char buf[200];

void fully_connected_fused_ReLU (float out[], int in_dim, int out_dim, float weights[], float bias[], float input[]);
void fully_connected (float out[], int in_dim, int out_dim, float weights[], float bias[], float input[]);
void preprocess (float in[SAMPLE_DIM][SAMPLE_FEATURES], float out[], float min_data[], float max_data[]);

int main() // change the name (main) upon implementation
{
    float buffer[BUFFER_SIZE];
    float out_class[N_CLASS];
    float input[INPUT_DIM];
    float max = -100;
    int prediction;

   
    for(int i = 0; i < 1; i++)
    {
        max=-1000;
    
    preprocess(data, input, data_min, data_max);
    fully_connected_fused_ReLU(buffer, FC1_IN_DIM, FC1_OUT_DIM, fc1_wt, fc1_bias, input ); //data[i]
    fully_connected(out_class, FC2_IN_DIM, FC2_OUT_DIM, fc2_wt, fc2_bias, buffer);
    
    for(int j = 0; j < FC2_OUT_DIM; j++)
    {
        if(out_class[j] > max)
        {
            max = out_class[j];
            prediction = j;
        }
    }
    printf("prediction for sample %d is %d\n", i, prediction);
    }

// Uncomment to calculate the infernece time on the MCU.
    // uint32_t t2 = HAL_GetTick();
    // int inference_time = t2 - t1;
    // int buf_len;
    // buf_len = sprintf(buf, "Inference Time for 10 examples is: %d\r\n", inference_time);
    // HAL_UART_Transmit(&huart3, (uint32_t *)buf, buf_len, 10);
}

// Preprocess the input data (Feature Extraction)
void preprocess (float in[SAMPLE_DIM][SAMPLE_FEATURES], float out[], float min_data[], float max_data[])
{
    float mean[SAMPLE_FEATURES] = {0};
    float std[SAMPLE_FEATURES] = {0};
    
    // find mean across columns
    for(int i = 0; i < SAMPLE_FEATURES; i++)
    {
        for(int j = 0; j < SAMPLE_DIM; j++)
        {
            mean[i] += in[j][i];
        }
        mean[i] /= SAMPLE_DIM;
        out[i] = mean[i];
    }

    // find std across columns 
    for(int i = 0; i < SAMPLE_FEATURES; i++)
    {
        for(int j = 0; j < SAMPLE_DIM; j++)
        {
            std[i] += pow(in[j][i] - mean[i], 2);
        }
        std[i] = sqrt(std[i]/(SAMPLE_DIM));
        out[i+SAMPLE_FEATURES] = std[i];
    }
    
    // normalize the data by applying the MinMax scaling
    for(int i = 0; i < INPUT_DIM; i++)
    {
        out[i] = (out[i] - data_min[i])/(data_max[i] - data_min[i]);
    }
    
}

// Fully connected layer with fused ReLU
void fully_connected_fused_ReLU (float out[], int in_dim, int out_dim, float weights[], float bias[], float input[])
{
    float temp;
    for(int i = 0; i < out_dim; i++)
    {
        temp = bias[i];
        for(int j = 0; j < in_dim; j++)
        {
            temp += weights[i*in_dim+j] * input[j];
        }
        if(temp < 0)
        {
            out[i] = 0;
        }
        else
        {
            out[i] = temp;
        }
    }
}

// Fully connected layer
void fully_connected (float out[], int in_dim, int out_dim, float weights[], float bias[], float input[])
{
    float temp;
    for(int i = 0; i < out_dim; i++)
    {
        temp = bias[i];
        for(int j = 0; j < in_dim; j++)
        {
            temp = temp + weights[i*in_dim+j] * input[j];
        }
        out[i] = temp;
    }
}
