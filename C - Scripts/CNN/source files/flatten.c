void flatten(float output[], int out_ch, int out_dim, float input[])
{
    int flat_ind = 0;
    for(int i = 0; i < out_dim; i++)
    {
        for(int j = 0; j < out_ch; j++)
        { 
            output[flat_ind] = input[i+(j*out_dim)];
            flat_ind++;
        }
    }
}