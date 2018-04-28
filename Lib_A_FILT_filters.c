/*
 * Lib_A_FILT_filters.c
 *
 *  Created on: 1 мар. 2018 г.
 *      Author: m.isaev
 */



/******************************************************************************/
// Секция include: здесь подключается заголовочный файл к модулю
#include "Lib_A_FILT_filters.h"
/******************************************************************************/


/******************************************************************************/
/*============================================================================*/
// Глобальные переменные
/*============================================================================*/


/*============================================================================*/
// Локальные переменные
/*============================================================================*/
/******************************************************************************/


/******************************************************************************/
// Секция прототипов локальных функций
static void FILT_CheckMaxCntValue (
  uint32_t *pCnt,
  uint32_t windowWidht);
/******************************************************************************/

/******************************************************************************/
// Секция описания функций (сначала глобальных, потом локальных)

/*============================================================================*/
float
FILT_ComplFilt_f32(
  FILT_comp_filt_s *pStruct,
  float value)
{
  pStruct->filtValue = pStruct->filtValue * pStruct->filtCoeff
                       + value * (1 - pStruct->filtCoeff);

  return pStruct->filtValue;
}

float
FILT_MovAverageFilt_f32 (
  FILT_moving_average_filt_f32_s *pStruct,
  float newValue,
  float pValueArr[])
{
  if ((pStruct->init_windowWidth != 0)
      && (pStruct->init_windowWidth != 1))
  {
    pStruct->filtValue = pStruct->filtValue
                         + ((newValue - pValueArr[pStruct->cnt]));

    pValueArr[pStruct->cnt] = newValue;

    pStruct->cnt = (pStruct->cnt + 1) % pStruct->init_windowWidth;

    return pStruct->filtValue / (float) pStruct->init_windowWidth;
  }
  else
  {
    return newValue;
  }
}

float
FILT_MovAverageFiltWithWindow_f32 (
  FILT_moving_average_filt_f32_s *pStruct,
  float newValue,
  float pValueArr[],
  float windowArr[])
{
  pStruct->cnt = (pStruct->cnt + 1) % pStruct->init_windowWidth;

  pValueArr[pStruct->cnt] = newValue;

  float resultArr[pStruct->init_windowWidth];

  uint32_t i = 0;
  for (i = 0; i < pStruct->init_windowWidth; i++)
  {
    FILT_CheckMaxCntValue (
      &pStruct->cnt,
      pStruct->init_windowWidth);
    
    resultArr[i] = windowArr[i] * pValueArr[pStruct->cnt];
    pStruct->cnt++;
  }

  float returnValue = 0;

  for (i = 0; i < pStruct->init_windowWidth; i++)
  {
    returnValue += resultArr[i];
  }

  return returnValue / (float) pStruct->init_windowWidth;
}

int32_t
FILT_MovAverFilt_u32 (
  FILT_moving_average_filt_i32_s *pStruct,
  int32_t newValue,
  int32_t pValueArr[])
{
  pStruct->filtValue = pStruct->filtValue + (newValue - pValueArr[pStruct->cnt]);

  pValueArr[pStruct->cnt] = newValue;

  pStruct->cnt = (pStruct->cnt + 1) % pStruct->init_windowWidth;

  return (int32_t) pStruct->filtValue / pStruct->init_windowWidth;
}

void
FILT_CheckMaxCntValue (
  uint32_t *pCnt,
  uint32_t windowWidht)
{
  if (*pCnt >= windowWidht)
  {
    *pCnt = 0;
  }
}
/*============================================================================*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
//  END OF FILE
////////////////////////////////////////////////////////////////////////////////
