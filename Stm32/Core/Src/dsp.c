/**
 * @file       dsp.c
 * @copyright  Copyright (C) BKU All rights reserved.
 * @license    This project is released under the BKU License.
 * @version    major.minor.patch
 * @date       17/5/2021
 * @author     Vo Mai Tri Luan
 *             
 * @brief      
 *             
 * @note          
 */

/* Includes ----------------------------------------------------------- */
#include "dsp.h"
//#include "dsp_coeffs.c"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
extern const float Word[WORD_NUM][20 * CENTROID];
extern const float HamWindow[256];
extern const float MelFb[20 * 129];
extern const word_t word_id[WORD_NUM];
uint32_t AudioTotalSize;
/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
void remove_copy(const int16_t *in, size_t n, int16_t *out, int16_t value)
{
	for (size_t i = 0; i != n; i++)
	{
		if (in[i] != value)
			*out++ = in[i];
	}
}
dsp_return check_pass(uint32_t pass)
{
	const uint32_t mypass = 9;

	if (pass == mypass)
	{
		return DSP_OK;
	}
	else
	{
		return DSP_ERROR;
	}
}

dsp_return check_voice(float min_distance, uint32_t min_id)
{
	const float32_t thresh0 = 6.8f;
	const float32_t thresh1 = 6.4f;
	const float32_t thresh2 = 6.9f;
	const float32_t thresh3 = 6.9f;
	const float32_t thresh4 = 6.6f;
	const float32_t thresh5 = 7.0f;
	const float32_t thresh6 = 7.3f;
	const float32_t thresh7 = 6.8f;
	const float32_t thresh8 = 6.5f;
	const float32_t thresh9 = 6.5f;

	switch (min_id)
	{
	case 0:
		if (min_distance > thresh0)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;
	case 1:
		if (min_distance > thresh1)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;
	case 2:
		if (min_distance > thresh2)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;
	case 3:
		if (min_distance > thresh3)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;
	case 4:
		if (min_distance > thresh4)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;
	case 5:
		if (min_distance > thresh5)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;
	case 6:
		if (min_distance > thresh6)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;
	case 7:
		if (min_distance > thresh7)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;
	case 8:
		if (min_distance > thresh8)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Granted");
			return DSP_OK;
		}
		break;
	case 9:
		if (min_distance > thresh9)
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Acess Denied");
			return DSP_ERROR;
		}
		else
		{
			lcd16x2_setCursor(1, 1);
			lcd16x2_printf("Access Granted");
			return DSP_OK;
		}
		break;

	default:
		break;
	}
}

dsp_return block_frames(float mdes[], float src[], const float h[], uint16_t nsrc, uint16_t m, uint16_t n)
{
	uint16_t nbFrame = floor((nsrc - n) / m) + 1;
	uint16_t i, j;
	float fft_1[n + 1], fft_2[n + 1];
	arm_rfft_fast_instance_f32 real_fft;

	if (arm_rfft_fast_init_f32(&real_fft, n) != ARM_MATH_SUCCESS)
	{
		return DSP_ERROR;
	}
	/*           Run through every 2D array: nbFram*256           */
	for (i = 0; i < nbFrame; i++)
	{

		for (j = 0; j < n; j++)
		{
			fft_1[j] = src[i * m + j] * h[j]; /*  apply hamming window for every frame */
		}

		arm_rfft_fast_f32(&real_fft, fft_1, fft_2, 0); /*caculate fft*/
		fft_2[n] = fft_2[1];
		fft_2[1] = 0;
		/*		Computes the magnitude squared of the elements of a complex data vector.		
		for (n = 0; n < numSamples; n++) {
    pDst[n] = pSrc[(2*n)+0]^2 + pSrc[(2*n)+1]^2;
}
		*/
		arm_abs_f32(fft_2, fft_2, n / 2 + 1);

		arm_cmplx_mag_squared_f32(fft_2, fft_1, n / 2 + 1);

		for (j = 0; j < (n / 2 + 1); j++)
		{

			mdes[j * nbFrame + i] = fft_1[j];
			//mdes[k++] = fft_1[j];
		}
	}
	return DSP_OK;
}

// DCT type II, unscaled.
// See: https://en.wikipedia.org/wiki/Discrete_cosine_transform#DCT-II
void dct_log_transform(float outvect[], float invect[], size_t len)
{
	float factor = PI / (float)len;
	float scale = sqrtf(2.0f / (float)len);
	for (size_t i = 0; i < len; i++)
	{
		float sum = 0;
		for (size_t j = 0; j < len; j++)
			sum += logf(invect[j]) * cosf(((float)j + 0.5f) * (float)i * factor); /* formula DCT II*/
		if (i == 0)
			outvect[i] = sum * scale * 1.0f / sqrtf(2.0f);
		else
			outvect[i] = sum * scale;
	}
}

dsp_return mfcc(float mfcc_mat[], float signal[], const float hamming[], const float melfb[], uint32_t siglen)
{
	uint32_t nbFrame;
	float frame[MELFB_LENGTH * MAX_MEL_FRAME]; /*129*300 */
	float result[MELFB_NUM * MAX_MEL_FRAME];   /*20*300*/
	float invect[MELFB_NUM], outvect[MELFB_NUM];
	uint8_t k = 0;
	arm_matrix_instance_f32 fb;
	arm_matrix_instance_f32 fr;
	arm_matrix_instance_f32 res;

	arm_mat_init_f32(&fb, MELFB_NUM, MELFB_LENGTH, (float32_t *)melfb);

	if (siglen > 1000)
	{
		nbFrame = (siglen - FFT_LENGTH) / FRAME_OVERLAP + 1;
		/* init matrix */
		arm_mat_init_f32(&fr, MELFB_LENGTH, nbFrame, (float32_t *)frame);
		arm_mat_init_f32(&res, MELFB_NUM, nbFrame, (float32_t *)result);
		/*framing Hamming window and fft*/
		block_frames(frame, signal, hamming, (uint16_t)siglen, FRAME_OVERLAP, FFT_LENGTH);
		/*mult with melfb*/
		if (arm_mat_mult_f32(&fb, &fr, &res) != ARM_MATH_SUCCESS)
			return DSP_ERROR;

		for (uint8_t j = 0; j < nbFrame; j++)
		{
			k = 0;
			for (uint8_t i = 0; i < MELFB_NUM; i++)
			{
				invect[k++] = result[i * nbFrame + j];
			}
			dct_log_transform(outvect, invect, MELFB_NUM);
			k = 0;
			for (uint8_t i = 0; i < MELFB_NUM; i++)
			{
				mfcc_mat[i * nbFrame + j] = outvect[k++];
			}
		}
	}
	return DSP_OK;
}

float euclidean(float Avect[], float Bvect[], uint32_t len)
{
	/* out = sum(abs(x-y).*pesi); */
	float Cvect[len];
	float result;
	float pesi[MELFB_NUM] = {0.2f, 0.9f, 0.95f, 0.9f, 0.7f, 0.9f, 1.0f, 1.0f, 1.0f, 0.95f, 0.3f, 0.3f, 0.3f};
	/*Element-by-element subtraction of two vectors.
    pDst[n] = pSrcA[n] - pSrcB[n],   0 <= n < blockSize.*/
	arm_sub_f32(Avect, Bvect, Cvect, len);
	/*Computes the absolute value of a vector on an element-by-element basis.
    pDst[n] = abs(pSrc[n]),   0 <= n < blockSize. */
	arm_abs_f32(Cvect, Cvect, len);
	/*Element-by-element multiplication of two vectors. */
	arm_mult_f32(Cvect, pesi, Cvect, len);
	/*Calculates the mean of the input vector. 
	Mean is defined as the average of the elements in the vector.*/
	arm_mean_f32(Cvect, len, &result);
	return (result * len);
}

float voice_compare(float Amat[], float Bmat[], uint32_t row, uint32_t colA, uint32_t colB)
{
	/*
	Amat[] = mfcc_data
	Bmat[] = Codebook
	row = MELFB_NUM
	colA = nbframe
	colB = centroid
	*/
	float d_mat[colA][colB];
	float min_sum = 0, min;
	uint32_t id;
	float AmatT[row * colA]; //20*nbframe
	float BmatT[row * colB]; //20*32

	arm_matrix_instance_f32 A, B, AT, BT;

	arm_mat_init_f32(&A, row, colA, Amat);
	arm_mat_init_f32(&B, row, colB, Bmat);
	arm_mat_init_f32(&AT, colA, row, AmatT);
	arm_mat_init_f32(&BT, colB, row, BmatT);
	/*Mu T ma tran*/
	arm_mat_trans_f32(&A, &AT);
	arm_mat_trans_f32(&B, &BT);

	for (uint32_t i = 0; i < colA; i++)
	{
		for (uint32_t j = 0; j < colB; j++)
		{
			d_mat[i][j] = euclidean(&AmatT[i * row], &BmatT[j * row], row);
		}

		/*Computes the minimum value of an array of data. 
		The function returns both the minimum value and its position within the array*/
		arm_min_f32(d_mat[i], colB, &min, &id);
		min_sum += min;
	}

	return (min_sum / (float)colA);
}
uint8_t voice_recognition(float *distance, float min_distance, float OutBuf[],dsp_return* Voice,dsp_return* Pass)
{
	float nbFrame, internal_min;
	float mfcc_data[MELFB_NUM * MAX_MEL_FRAME];
	uint32_t id;

	AudioRecord(OutBuf);

	if (AudioTotalSize > 1000)
	{
		nbFrame = (AudioTotalSize - FFT_LENGTH) / FRAME_OVERLAP + 1;
		dsp_return check = mfcc((float32_t *)&mfcc_data[0], (float32_t *)&OutBuf[0], HamWindow, MelFb, AudioTotalSize);
		// printf("MFCC DONE \n");
		for (uint16_t i = 0; i < WORD_NUM; i++)
		{
			distance[i] = voice_compare((float32_t *)&mfcc_data[0], (float32_t *)&Word[i], MELFB_NUM, nbFrame, CENTROID);
		}
		arm_min_f32(distance, WORD_NUM, &internal_min, &id);
		lcd16x2_clear();
		dsp_return vFlag = check_voice(internal_min, id);
		*Voice = vFlag;
		//dsp_return vFlag = check_voice(distance[9], id);
		dsp_return passFlag = check_pass(id);
		*Pass = passFlag;
		/*Voice && Flag check */
		toggle_leds_rgb(OFF1);
		lcd16x2_clear();
		if ((vFlag == DSP_OK) && (passFlag == DSP_OK))
		{
			toggle_leds_rgb(GREEN1);
			lcd16x2_setCursor(1,1);
			//lcd16x2_printf("Welcome Luan !");
		}
		else if(vFlag == DSP_OK)
		{
			toggle_leds_rgb(YELLOW1);
			lcd16x2_setCursor(1,1);
			lcd16x2_printf("Wrong Password!");
		}
		else if(vFlag == DSP_ERROR)
		{
			toggle_leds_rgb(RED1);
			lcd16x2_setCursor(1,3);
			lcd16x2_printf("Imposter!");
		}
		/*Return ID*/
		if (internal_min <= min_distance)
		{
			printf("id = %d \n", id);
			return word_id[id];
		}
	}
	printf("audio < 1000 \n");
	return UNKNOWN;
}

/* End of file -------------------------------------------------------- */

/*
Reference : function r = mymfcc(s, fs)
n = 256; % N point FFT
m = 100; % Overlapping
l = length(s);
%%framing
nbFrame = floor((l - n) / m) + 1;

M=0;
for i = 1:n
 for j = 1:nbFrame
 M(i, j) = s(((j - 1) * m) + i);
 end
end
 %size(M)
 %%windowing
 h = hamming(n);
 
 M2 = diag(h) * M;
 %%fft calculation
 
 for i = 1:nbFrame
  frame(:,i) = fft(M2(:, i));
 end 
%t = n / 2;
%tmax = l / fs;
 %%filter banks
 m = melfb_v2(20, n, fs);
 %plot(m);
 n2 = 1 + floor(n / 2);
 z = m * abs(frame(1:n2, :)).^2;
 %%dct calculation
 r = dct(log(z));
 %r(1,:) = [];
 %melceps=r;
 %plot(r);
*/
