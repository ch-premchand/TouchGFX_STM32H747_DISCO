/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file is generated by TouchGFX Generator 4.19.1.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>
#include "stm32h747i_discovery_ts.h"

static bool bsp_ts_initialized = false;
TS_Init_t* hTS;
TS_State_t  TS_State = {0};

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
    hTS->Width = 800;
    hTS->Height = 480;
    hTS->Orientation = TS_SWAP_XY | TS_SWAP_Y;
    hTS->Accuracy = 0;

    if (BSP_TS_Init(0, hTS) == BSP_ERROR_NONE)
    {
        bsp_ts_initialized = true;
    }

    assert(bsp_ts_initialized);
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
    if (bsp_ts_initialized)
    {
        BSP_TS_GetState(0, &TS_State);
        if (TS_State.TouchDetected)
        {
            x = TS_State.TouchX;
            y = TS_State.TouchY;
            return true;
        }
    }
    return false;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
