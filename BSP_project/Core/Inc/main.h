/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32f4_discovery.h"
#include "stm32f4_discovery_audio.h"
#include "dsp_coeffs.h"
#include "audio_record.h"
#include <stdio.h>
#include "dsp.h"
#include "arm_math.h"
#include "lcd16x2.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
  // typedef struct
  // {
  //   void (*DemoFunc)(void);
  //   uint8_t DemoName[50];
  //   uint32_t DemoIndex;
  // } BSP_DemoTypedef;
  typedef enum
  {
    RED1,
    GREEN1,
    BLUE1,
    YELLOW1,
    OFF1,
    RED2,
    GREEN2,
    BLUE2,
    YELLOW2,
    OFF2,
  } led_t;

  typedef enum
  {
    RELAY_ON,
    RELAY_OFF
  } relay_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* Size of the recorder buffer (Multiple of 4096, RAM_BUFFER_SIZE used in BSP)*/
#define WR_BUFFER_SIZE 4096 * 6
#define MAX_FRAME 300
#define OUT_BUFFER_SIZE 2 * PCM_OUT_SIZE *MAX_FRAME
#define MAX_MEL_FRAME ((OUT_BUFFER_SIZE - 256) / 100 + 1)

#define COUNT_OF_EXAMPLE(x) (sizeof(x) / sizeof(BSP_DemoTypedef))

/* Defines for the Audio playing process */
#define PAUSE_STATUS ((uint32_t)0x00)  /* Audio Player in Pause Status */
#define RESUME_STATUS ((uint32_t)0x01) /* Audio Player in Resume Status */
#define IDLE_STATUS ((uint32_t)0x02)   /* Audio Player in Idle Status */
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
  void Toggle_Leds(void);
  void Off_Leds(void);
  void blink_rgb(void);
  void toggle_leds_rgb(led_t color);
  void toggle_relay(relay_t relay);

  //	void set_rgb (uint8_t red, uint8_t green, uint8_t blue);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
