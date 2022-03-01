#ifndef HSCDEVICE_H
#define HSCDEVICE_H

#define AI10_DI8_AO0_DO2     1
#define AI10_DI8_AO0_DO10    2
# ifndef HSC_DEVICE
#   define HSC_NUM_AI  10
#   define HSC_NUM_AO  0
#   define HSC_NUM_DI  8
#   define HSC_NUM_DO  2
#elif HSC_DEVICE == AI10_DI8_AO0_DO2
#   define HSC_NUM_AI  10
#   define HSC_NUM_AO  0
#   define HSC_NUM_DI  8
#   define HSC_NUM_DO  2
#elif HSC_DEVICE == AI10_DI8_AO0_DO10
#   define HSC_NUM_AI  10
#   define HSC_NUM_AO  0
#   define HSC_NUM_DI  8
#   define HSC_NUM_DO  10
#endif
#define HSC_CNT_AI  HSC_NUM_AI
#define HSC_CNT_AO  HSC_NUM_AO
#define HSC_CNT_DI  int((HSC_NUM_DI+7)/8)
#define HSC_CNT_DO  int((HSC_NUM_DO+7)/8)

#endif // HSCDEVICE_H
