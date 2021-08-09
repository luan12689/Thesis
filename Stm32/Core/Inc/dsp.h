 /**
 * @file       dsp.c
 * @copyright  Copyright (C) BKU All rights reserved.
 * @license    This project is released under the BKU License.
 * @version    major.minor.patch
 * @date       19/3/2020
 * @author     Nguyen The Hung
 *             
 * @brief      digital signal process header file
 *             
 * @note          
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DSP_H
#define __DSP_H

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include "arm_math.h"
#include <math.h>
#include <stdlib.h>
#include "main.h"
//#include "dsp_coeffs.h"
/* Public defines ----------------------------------------------------- */
#define FFT_LENGTH 256
#define FRAME_OVERLAP 100
#define SAMPLE_RATE 8000
#define MELFB_LENGTH (FFT_LENGTH / 2 + 1)
#define SAMPLE_LENGTH 16000U
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
	DSP_UNKNOWN = 0,
	DSP_OK,
	DSP_ERROR
} dsp_return;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
// void merge_array(float32_t des[], int16_t *ndes, float32_t temp[], int16_t ntemp);
// void linspace(float a, float b, uint16_t n, float u[]);
void remove_copy(const int16_t *in, size_t n, int16_t *out, int16_t value);
dsp_return check_voice(float min_distance, uint32_t min_id);
dsp_return check_pass(uint32_t pass);
dsp_return block_frames(float mdes[], float src[], const float h[], uint16_t nsrc, uint16_t m, uint16_t n);
dsp_return mfcc(float mfcc_mat[], float signal[], const float hamming[], const float melfb[], uint32_t siglen);
// void remove_copy(const float *in, size_t n, float *out, float value);
void dct_log_transform(float outvect[], float invect[], size_t len);
float voice_compare(float Amat[], float Bmat[], uint32_t row, uint32_t colA, uint32_t colB);
//voice_id voice_recognition(float *min_distance);
//uint8_t voice_recognition(float *distance, float min_distance, float OutBuf[]);
uint8_t voice_recognition(float *distance, float min_distance, float OutBuf[], dsp_return* Voice, dsp_return* Pass);

#endif // __DSP_H

/* End of file -------------------------------------------------------- */
