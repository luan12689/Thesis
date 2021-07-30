/**
  ******************************************************************************
  * @file    BSP/Src/audio_record.c 
  * @author  MCD Application Team
  * @brief   This example code shows how to use AUDIO features for the record.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "audio_record.h"
#include "string.h"
#include "stdlib.h"
#include "arm_math.h"
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
#define AUDIO_BUFFER_SIZE 8192
#define MIN_ENERGY 5.0e-4f
#define MIN_ZCR 0.06f

typedef struct
{
  int32_t offset;
  uint32_t fptr;
} Audio_BufferTypeDef;

typedef enum
{
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
} BUFFER_StateTypeDef;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

__IO uint32_t ITCounter = 0;
Audio_BufferTypeDef BufferCtl;

/* Temporary data sample */
__IO uint32_t AUDIODataReady = 0, AUDIOBuffOffset = 0;

/* Variable used to replay audio sample (from play or record test) */
static uint32_t AudioTest;

/* Variable used for play in infinite loop */
extern __IO uint8_t UserPressButton;

/* Variables used in normal mode to manage audio file during DMA transfer */
extern uint32_t AudioTotalSize; /* This variable holds the total size of the audio file */
static uint32_t AudioRemSize;   /* This variable holds the remaining data in audio file */
static uint16_t *CurrentPos;    /* This variable holds the current position of audio pointer */

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief Test Audio Hardware.
  *   The main objective of this test is to check the hardware connection of the 
  *   Audio peripheral.
  * @param  None
  * @retval None
  */
void AudioRecord(float OutBuf[])
{
  float TempBuf[2 * PCM_OUT_SIZE];
  int16_t RecBuf[2 * PCM_OUT_SIZE];
  uint16_t InternalBuffer[INTERNAL_BUFF_SIZE];

  BufferCtl.offset = BUFFER_OFFSET_NONE;

  /* Turn ON LED3: start record */
  BSP_LED_On(LED6);

  /* Start the record */
  if (BSP_AUDIO_IN_Record((uint16_t *)&InternalBuffer[0], INTERNAL_BUFF_SIZE) != AUDIO_OK)
  {
    /* Record Error */
    Error_Handler();
  }
  BufferCtl.fptr = 0;

  AUDIODataReady = 0;

  float zero_cross = 0; // ty le qua diem 0
  uint16_t k = 0;
  float temp = 0; // bien chua x[n-1]
  float frame_power = 0;
  /* Wait for the data to be ready with PCM form */
  while (AUDIODataReady != 2)
  {
    if (BufferCtl.offset == BUFFER_OFFSET_HALF)
    {
      /* PDM to PCM data convert */
      BSP_AUDIO_IN_PDMToPCM((uint16_t *)&InternalBuffer[0], (uint16_t *)&RecBuf[0]);
      remove_copy(RecBuf, PCM_OUT_SIZE, RecBuf, 0);
      /* Copy PCM data in internal buffer */
      for (uint16_t i = 0; i < PCM_OUT_SIZE; i++)
      {
        TempBuf[i] = (float)RecBuf[i << 1] / 32768.0f - 0.95f * temp;
        if ((TempBuf[i] * temp) < 0)
          zero_cross++;
        temp = TempBuf[i] + 0.95f * temp;
      }

      BufferCtl.offset = BUFFER_OFFSET_NONE;

      if (ITCounter == (WR_BUFFER_SIZE / (PCM_OUT_SIZE * 4)) - 1)
      {
        AUDIODataReady = 1;
        AUDIOBuffOffset = 0;
        ITCounter++;
      }
      else if (ITCounter == (WR_BUFFER_SIZE / (PCM_OUT_SIZE * 2)) - 1)
      {
        AUDIODataReady = 2;
        AUDIOBuffOffset = WR_BUFFER_SIZE / 2;
        ITCounter = 0;
      }
      else
      {
        ITCounter++;
      }
    }

    if (BufferCtl.offset == BUFFER_OFFSET_FULL)
    {
      /* PDM to PCM data convert */
      BSP_AUDIO_IN_PDMToPCM((uint16_t *)&InternalBuffer[INTERNAL_BUFF_SIZE / 2], (uint16_t *)&RecBuf[0]);
      remove_copy(RecBuf, PCM_OUT_SIZE, RecBuf, 0);
      /* Copy PCM data in internal buffer */
      for (uint16_t i = PCM_OUT_SIZE; i < 2 * PCM_OUT_SIZE; i++)
      {
        TempBuf[i] = (float)RecBuf[(i - PCM_OUT_SIZE) << 1] / 32768.0f - 0.95f * temp;
        if ((TempBuf[i] * temp) < 0)
          zero_cross++;
        temp = TempBuf[i] + 0.95f * temp;
      }
      arm_power_f32(TempBuf, 2 * PCM_OUT_SIZE, &frame_power);
      if ((frame_power / (float)(2 * PCM_OUT_SIZE) > MIN_ENERGY) && ((zero_cross / (float)(2 * PCM_OUT_SIZE)) > MIN_ZCR))
      {
        if ((k > 1) && (k <= MAX_FRAME)) // 2 frame dau co nhieu rat lon
          arm_copy_f32(TempBuf, (float *)&OutBuf[(k - 2) * (PCM_OUT_SIZE * 2)], 2 * PCM_OUT_SIZE);
        k++;
      }
      zero_cross = 0;
      // remove_copy(OutBuf, (k - 2) * (PCM_OUT_SIZE * 2), OutBuf, 0);

      BufferCtl.offset = BUFFER_OFFSET_NONE;

      if (ITCounter == (WR_BUFFER_SIZE / (PCM_OUT_SIZE * 4)) - 1)
      {
        AUDIODataReady = 1;
        AUDIOBuffOffset = 0;
        ITCounter++;
      }
      else if (ITCounter == (WR_BUFFER_SIZE / (PCM_OUT_SIZE * 2)) - 1)
      {
        AUDIODataReady = 2;
        AUDIOBuffOffset = WR_BUFFER_SIZE / 2;
        ITCounter = 0;
      }
      else
      {
        ITCounter++;
      }
    }
  };

  /* Stop audio record */
  if (BSP_AUDIO_IN_Stop() != AUDIO_OK)
  {
    /* Record Error */
    Error_Handler();
  }

  //AudioTotalSize = (k-2);
  if (k < MAX_FRAME)
    AudioTotalSize = (k - 2) * PCM_OUT_SIZE * 2;
  else
    AudioTotalSize = OUT_BUFFER_SIZE;
  printf("AudioTotalsize = %d \n", AudioTotalSize);
  //OutBuf[OUT_BUFFER_SIZE-1] = AudioTotalSize;
  /* Set variable to indicate play from record buffer */
  AudioTest = 1;

  /*Set variable used to stop player before starting */
  UserPressButton = 0;

  /* Turn OFF LED3: record stopped */
  BSP_LED_Off(LED6);
  /* Turn ON LED6: play recorded file */
  BSP_LED_On(LED3);

  //  while(!UserPressButton)
  //  {
  //  }
}

/**
  * @brief Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
  BufferCtl.offset = BUFFER_OFFSET_FULL;
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
  BufferCtl.offset = BUFFER_OFFSET_HALF;
}

/**
  * @brief  Audio IN Error callback function
  * @param  pData
  * @retval None
  */
void BSP_AUDIO_IN_Error_Callback(void)
{
  /* Stop the program with an infinite loop */
  Error_Handler();
}

/*--------------------------------
Callbacks implementation:
The callbacks prototypes are defined in the stm32f4_discovery_audio.h file
and their implementation should be done in the user code if they are needed.
Below some examples of callback implementations.
--------------------------------------------------------*/
/**
* @brief  Calculates the remaining file size and new position of the pointer.
* @param  None
* @retval None
*/
void BSP_AUDIO_OUT_TransferComplete_CallBack()
{
  uint32_t replay = 0;

  if (AudioRemSize > 0)
  {
    /* Replay from the current position */
    BSP_AUDIO_OUT_ChangeBuffer((uint16_t *)CurrentPos, DMA_MAX(AudioRemSize / AUDIODATA_SIZE));

    /* Update the current pointer position */
    CurrentPos += DMA_MAX(AudioRemSize);

    /* Update the remaining number of data to be played */
    AudioRemSize -= AUDIODATA_SIZE * DMA_MAX(AudioRemSize / AUDIODATA_SIZE);
  }
  else
  {
    /* Request to replay audio file from beginning */
    replay = 1;
  }

  /* Audio sample saved during record */
  if ((AudioTest == 1) && (replay == 1))
  {
    /* Replay from the beginning */
    BSP_AUDIO_OUT_Play(CurrentPos, AudioTotalSize);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
