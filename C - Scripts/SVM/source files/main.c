#include <stdio.h>
#include <math.h>
#include "svm_params.h"
#include "Test_Sample.h"
// #include "main.h" 

#define N_CLASS 5
#define INPUT_DIM 32

// uncomment below to measure inference
// extern UART_HandleTypeDef huart3;
// char buff[200];

void preprocess (float in[SAMPLE_DIM][SAMPLE_FEATURES], float out[], float min_data[], float max_data[]);
int svm_classification(float X[]);

int main() 
{
    float out_class[N_CLASS];
    float input[INPUT_DIM];
    int prediction[250];
    int datumm = 0;
    
// uncomment below to measure inference 
    // uint32_t t1 = HAL_GetTick();

// For loop for classifing 250 samples (50 samples from each class)
    for (int i = 0; i < 250; i++)
    {
    prediction[i] = svm_classification(data[i]);
    printf("Predicted class: %d \n", prediction[i]);

    datumm = datumm + 40;

// uncomment below to measure inference 
    // uint32_t t2 = HAL_GetTick();
    // int inference_time = t2 - t1;
    // int buff_len;
    // buff_len = sprintf(buff, "Inference Time for 1000 examples is: %d\r\n", inference_time);
    // HAL_UART_Transmit(&huart3, (uint32_t *)buff, buff_len, 10);

    }
}

// Preprocess the input data
void preprocess (float in[SAMPLE_DIM][SAMPLE_FEATURES], float out[], float min_data[], float max_data[])
{
    float mean[SAMPLE_FEATURES] = {0};
    float std[SAMPLE_FEATURES] = {0};
        
    // find mean across columns (each coloumn corresponds to a channel/sensor)
    for(int i = 0; i < SAMPLE_FEATURES; i++)
    {
        for(int j = 0; j < SAMPLE_DIM; j++)
        {
            mean[i] += in[j][i];
        }
        mean[i] /= SAMPLE_DIM;
        out[i] = mean[i];
    }

    // find std across columns (each coloumn corresponds to a channel/sensor)
    for(int i = 0; i < SAMPLE_FEATURES; i++)
    {
        for(int j = 0; j < SAMPLE_DIM; j++)
        {
            std[i] += pow(in[j][i] - mean[i], 2);
        }
        std[i] = sqrt(std[i]/(SAMPLE_DIM));
        out[i+SAMPLE_FEATURES] = std[i];
    }

    // Normalization of features using MinMax equation
    for(int i = 0; i < INPUT_DIM; i++)
        {
            out[i] = (out[i] - data_min[i])/(data_max[i] - data_min[i]);
        }
}

// Classification
int svm_classification(float X[])
{
    float max = -100;
    int prediction;
    int count[5] = {0};

    for (int i = 0; i < N_VECTOR; i++)
    {
        float distance = 0;
        float y[N_VECTOR];
        y[i] = bias[i];

        for (int k = 0; k < N_FEATURE; k++)
        {y[i] += X[k] * support_vectors[i][k];}

        if (y[i] > 0)
        {count[CLAS[i][0]]+= 1;}
        
        else
        {count[CLAS[i][1]]+= 1;}
    }
    //  prediction based on the highest magority voting 
    for(int j = 0; j < 5; j++)
    {   if(count[j] > max)
            {   max = count[j];
                prediction = j;
            }
        
    }
    return prediction;   
}