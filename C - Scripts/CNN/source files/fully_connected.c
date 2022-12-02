void fully_connected(float output[], int out_dim, int in_dim, float weight[], float bias[], float input[])
{
    float sum = 0;
    for(int i = 0; i < out_dim; i++)
    {
        sum = bias[i];
        for(int j = 0; j < in_dim; j++)
        {
            sum += weight[i*in_dim+j] * input[j];
        }
        output[i] = sum;
    }
}

void fully_connected_fused_relu(float output[], int out_dim, int in_dim, float weight[], float bias[], float input[])
{
    float sum = 0;
    for(int i = 0; i < out_dim; i++)
    {
        sum = bias[i];
        for(int j = 0; j < in_dim; j++)
        {
            sum += weight[i*in_dim+j] * input[j];
        }
        if(sum>0)
        {
            output[i] = sum;
        }
        else
        {
            output[i] = 0;
        }
    }
}