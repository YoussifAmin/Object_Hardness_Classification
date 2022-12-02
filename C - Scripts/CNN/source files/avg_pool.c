void pool(float output[], int out_ch, int out_dim, int ker_dim, int in_dim, int stride, int padding, float input[])
{
    int i_ch_in, i_y, in;
    int k_y;
    int input_idx, output_idx;
    for (i_ch_in = 0; i_ch_in < out_ch; i_ch_in++)
    {
        for (i_y = 0; i_y < out_dim; i_y++)
        {
            float sum = 0;
            for (k_y = i_y * stride - padding; k_y < i_y * stride - padding + ker_dim; k_y++)
            {
                if (k_y >= 0 && k_y < in_dim)
                {
                    input_idx = i_ch_in + (out_ch * k_y);
                    sum += input[input_idx];
                }
            }
            output_idx = (i_ch_in + out_ch * i_y);
            output[output_idx] = sum/ker_dim;
        }
    }
}
