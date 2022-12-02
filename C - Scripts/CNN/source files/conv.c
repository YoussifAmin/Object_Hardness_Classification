#include <stdio.h>

void conv(float output[], int out_ch, int out_dim, int ker_dim, int in_ch, int in_dim, int stride, int padding, float weight[], float bias[], float input[])
{
    float sum = 0;
    int i,j,m,l;
    int in_row, in_col, ker;
    int img_idx,ker_idx,out_idx;
    
    for (i = 0; i < out_ch; i++)
    {
        for (j = 0; j < out_dim; j++)
        {
            sum = bias[i];
            for (m = 0; m < ker_dim; m++)
            {
                in_row = stride * j + m - padding;
                if (in_row >= 0 && in_row < in_dim)
                {
                    for (l = 0; l < in_ch; l++)
                    {
                        img_idx = (in_row * in_ch) + l;
                        ker_idx = (i * in_ch * ker_dim) + (m *in_ch) + l;
                        sum += weight[ker_idx] * input[img_idx];
                    }
                }
            }
            if(sum>0)
            {
                out_idx = i + (j * out_ch);
                output[i + (j * out_ch)] = sum;
            }
            else
            {
                out_idx = i + (j * out_ch);
                output[i + (j * out_ch)] = 0;
            }
        }
    }
}