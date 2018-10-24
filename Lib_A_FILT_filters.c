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
static void
FILT_CheckMaxCntValue (
	uint32_t *pCnt,
	uint32_t windowWidht);
/******************************************************************************/

/******************************************************************************/
// Секция описания функций (сначала глобальных, потом локальных)

/*============================================================================*/
__FILT_FPT__
FILT_Complementary_fpt(
	filt_complementary_s *pStruct,
	__FILT_FPT__ value)
{
	if ( pStruct->filtCoeff > 1.0f)
	{
		pStruct->filtCoeff = 1.0f;
	}
	pStruct->filtValue =
		pStruct->filtValue * pStruct->filtCoeff
		+ value * (1 - pStruct->filtCoeff);

	return pStruct->filtValue;
}

__FILT_FPT__
FILT_MovAverage_fpt (
	filt_moving_average_fpt_s *pStruct,
	__FILT_FPT__ newValue,
	__FILT_FPT__ pValueArr[])
{
	if ((pStruct->init_windowWidth != 0)
			&& (pStruct->init_windowWidth != 1))
	{
		pStruct->filtValue =
			pStruct->filtValue + ((newValue - pValueArr[pStruct->cnt]));

		pValueArr[pStruct->cnt] = newValue;

		pStruct->cnt = (pStruct->cnt + 1) % pStruct->init_windowWidth;

		return pStruct->filtValue / (__FILT_FPT__) pStruct->init_windowWidth;
	}
	else
	{
		return newValue;
	}
}

__FILT_FPT__
FILT_MovAverageFiltWithWindow_fpt (
	filt_moving_average_fpt_s *pStruct,
	__FILT_FPT__ newValue,
	__FILT_FPT__ pValueArr[],
	__FILT_FPT__ windowArr[])
{
	pStruct->cnt = (pStruct->cnt + 1) % pStruct->init_windowWidth;

	pValueArr[pStruct->cnt] = newValue;

	__FILT_FPT__ resultArr[pStruct->init_windowWidth];

	uint32_t i = 0;
	for (i = 0; i < pStruct->init_windowWidth; i++)
	{
		FILT_CheckMaxCntValue (
			&pStruct->cnt,
			pStruct->init_windowWidth);

		resultArr[i] = windowArr[i] * pValueArr[pStruct->cnt];
		pStruct->cnt++;
	}

	__FILT_FPT__ returnValue = 0;

	for (i = 0; i < pStruct->init_windowWidth; i++)
	{
		returnValue += resultArr[i];
	}

	return returnValue / (__FILT_FPT__) pStruct->init_windowWidth;
}

int32_t
FILT_MovAverFilt_u32 (
	filt_moving_average_i32_s *pStruct,
	int32_t newValue,
	int32_t pValueArr[])
{
	pStruct->filtValue = pStruct->filtValue + (newValue - pValueArr[pStruct->cnt]);

	pValueArr[pStruct->cnt] = newValue;

	pStruct->cnt = (pStruct->cnt + 1) % pStruct->init_windowWidth;

	return (int32_t) pStruct->filtValue / pStruct->init_windowWidth;
}


/**
 * @brief Функция выполняет фильтрацию сигнала по N измерениям
 * @param[in] In: Указатель на нулевой элемент массива, в котором содержатся
 *                N последних измерений сигнала
 * @param[in] length_In:  Количество ячеек массива измерений (количество
 *                        измерений, по которым будет произведена фильтрация
 *                        сигнала)
 * @return  Фильтрованное по последним N измерениям значение сигнала
 */
__FILT_FPT__
filter_db2 (
	__FILT_FPT__* In,
	size_t length_In)
{
	const size_t m = 4;

	__FILT_FPT__ db_2[] =
	{
		-0.0914996174855392,
		0.158462629663905,
		0.591494822462547,
		0.341532575313102,
	};

	__FILT_FPT__ arr[length_In];
	size_t length_db_2;
	__FILT_FPT__ *Out = &arr[0];

	size_t i = 0;
	for (i = 0; i < length_In; i++)
	{
		Out[i] = 0;

		if (i < m)
		{
			length_db_2 = i + 1;
		}
		else
		{
			length_db_2 = m;
		}

		size_t j = 0;
		for (j = 0; j < length_db_2; j++)
		{
			Out[i] += In[i - j] * db_2[j];
		}
	}
	return arr[3];
}

__FILT_FPT__
__filter_db2(
	__FILT_FPT__* In,
	size_t length_In)
{
	__FILT_FPT__ res = 0.0f;

	__FILT_FPT__ db_2[] = {
		0.341532575313102,
		0.591494822462547,
		0.158462629663905,
		-0.0914996174855392,
	};

	size_t j = 0;
	for (j = 0; j < length_In; j++)
	{
		res += In[j] * db_2[j];
	}

	return res;
}

void
FILT_GetLastVal (
	__FILT_FPT__ *pData,
	__FILT_FPT__ val,
	uint16_t lenght)
{
	/* Указатель на начало массива */
	__FILT_FPT__ *pArr = pData;

	/* Смещение массива */
	uint16_t i;
	pData++;
	for (i = 0; i < (lenght - 1); i++)
	{
		*pArr++ = *pData++;
	}

	pData--;
	/* Копирование нового значения в крайний элемент массива */
	*pData = val;
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
