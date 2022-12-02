#define N_CONV1_WT 1536
#define N_CONV1_BIAS 8
#define CONV1_IN_CH 16    //channels of filter
#define CONV1_IN_DIM 40
#define CONV1_KER_SIZE 12 //kernal size
#define CONV1_OUT_CH 8    // number of filters
#define CONV1_OUT_DIM 40
#define CONV1_STRIDE 1
#define CONV1_PADDING 5
extern float conv1_wt[N_CONV1_WT];
extern float conv1_bias[N_CONV1_BIAS];

#define POOL1_KER_SIZE 2
#define POOL1_STRIDE 2
#define POOL1_PADDING 0
#define POOL1_IN_DIM 40
#define POOL1_OUT_DIM 20
#define POOL1_CH 8

#define N_CONV2_WT 768
#define N_CONV2_BIAS 8
#define CONV2_IN_CH 8
#define CONV2_IN_DIM 20
#define CONV2_KER_SIZE 12
#define CONV2_OUT_CH 8
#define CONV2_OUT_DIM 20
#define CONV2_STRIDE 1
#define CONV2_PADDING 5
extern float conv2_wt[N_CONV2_WT];
extern float conv2_bias[N_CONV2_BIAS];

#define POOL2_KER_SIZE 2
#define POOL2_STRIDE 2
#define POOL2_PADDING 0
#define POOL2_IN_DIM 20
#define POOL2_OUT_DIM 10
#define POOL2_CH 8

#define N_FC1_WT 800
#define N_FC1_BIAS 10
#define FC1_IN_DIM 80
#define FC1_OUT_DIM 10
extern float fc1_wt[N_FC1_WT];
extern float fc1_bias[N_FC1_BIAS];

#define N_FC2_WT 50
#define N_FC2_BIAS 5
#define FC2_IN_DIM 10
#define FC2_OUT_DIM 5
extern float fc2_wt[N_FC2_WT];
extern float fc2_bias[N_FC2_BIAS];

