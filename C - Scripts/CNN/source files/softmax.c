#include <math.h>

int softmax(float output[], int out_dim, int prediction, float input[])
{
    float exponential_sum = 0;
    float max = -1;
    for(int i = 0; i < out_dim; i++)
    {
        exponential_sum = exponential_sum + exp(input[i]);
    }

    for(int i = 0; i < out_dim; i++)
    {
        output[i] = exp(input[i]) / exponential_sum;
    }

    for(int i = 0; i < out_dim; i++)
    {
        if(output[i]>max)
        {
            max = output[i];
            prediction = i;
        }
    }
    return prediction;
}   