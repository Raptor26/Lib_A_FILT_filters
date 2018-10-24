/*
 * Lib_A_FILT_filters.h
 *
 *  Created on: 1 мар. 2018 г.
 *      Author: m.isaev
 */

#ifndef LIB_A_FILT_FILTERS_H_
#define LIB_A_FILT_FILTERS_H_


/******************************************************************************/
// Секция include (подключаем заголовочные файлы используемых модулей)
/*============================================================================*/
// Стандартные библиотеки языка С
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
/*============================================================================*/


/*============================================================================*/
// Библиотеки для работы с периферией микроконтроллера
/*============================================================================*/


/*============================================================================*/
// Внешние модули
/*============================================================================*/
/******************************************************************************/


/******************************************************************************/
// Секция определения констант
#if !defined (__FILT_FPT__)
#error "Please, set __FILT_FPT__ = 'f' or 'd'"
#endif

/* Если __FILT_FPT__ равен __FILT_FPT__ */
#if 	__FILT_FPT__ == 	'f'
#undef 	__FILT_FPT__
#define __FILT_FPT__		float

/* Если __FILT_FPT__ равен double */
#elif 	__FILT_FPT__ == 	'd'
#undef  __FILT_FPT__
#define __FILT_FPT__		double
#endif
/******************************************************************************/


/******************************************************************************/
// Секция определения типов
typedef enum
{
	FILT_ERROR = 0,
	FILT_SUCCESS,
} filt_fnc_status_e;

typedef struct
{
	/**
	 * @brief	Коэффициент фильтра;
	 */
	__FILT_FPT__ filtCoeff;

	/**
	 * @brief	Выходное значение фильтра за предыдущий вызов функции;
	 */
	__FILT_FPT__ filtValue;
} filt_complementary_s;

/**
 * @brief	Структура для функции скользящего среднего FILT_MovAverageFilt_f32()
 */
typedef struct
{
	/**
	 * @brief	Количество последних "n" измерений, по которым будет
	 * 			производится усреднение
	 */
	uint32_t windowWidth;

	/**
	 * @brief	Счетчик номера ячейки массива, куда будет записано новое значение
	 */
	uint32_t cnt;

	/**
	 * @brief	Фильтрованное значение на шаге <t-1>
	 */
	__FILT_FPT__ preFiltValue;

	/**
	 * @brief	Фильтрованное значение, которое будет рассчитано при вызове функции
	 */
	__FILT_FPT__ filtValue;

	/**
	 * @brief 	Указатель на массив для хранения последних n измерений
	 */
	__FILT_FPT__ *pWindowArr;

	filt_fnc_status_e initStatus_e;
} filt_moving_average_fpt_s;

typedef struct
{
	/**
	 * @brief	Размерность массива для фильтра скользящего среднего
	 */
	uint32_t windowWidth;

	/**
	 * @brief	Указатель на массив для хранения последних n измерений
	 */
	__FILT_FPT__ *pWindowArr;
} filt_moving_average_init_struct_fpt_s;

typedef struct
{
	/**
	 * @brief	Количество измерений, по которым будет производится усреднение
	 */
	uint32_t init_windowWidth;

	/**
	 * @brief	Счетчик номера ячейки массива, куда будет записано новое значение
	 */
	uint32_t cnt;

	int32_t filtValue;
} filt_moving_average_i32_s;
/******************************************************************************/

/******************************************************************************/
// Секция определения глобальных переменных
/******************************************************************************/

/******************************************************************************/
// Секция прототипов глобальных функций
extern __FILT_FPT__
FILT_Complementary_fpt(
	filt_complementary_s *pStruct,
	__FILT_FPT__ value);

extern __FILT_FPT__
FILT_MovAverage_fpt(
	filt_moving_average_fpt_s *pStruct,
	__FILT_FPT__ newValue);

extern filt_fnc_status_e
FILT_Init_MovAverage_fpt(
	filt_moving_average_fpt_s 				*pFilt_s,
	filt_moving_average_init_struct_fpt_s 	*pInitFilt_s);

extern void
FILT_MovAverage_StructInit(
	filt_moving_average_init_struct_fpt_s   *pInitFilt_s);

extern __FILT_FPT__
FILT_MovAverageFiltWithWindow_fpt(
	filt_moving_average_fpt_s *pStruct,
	__FILT_FPT__ newValue,
	__FILT_FPT__ pValueArr[],
	__FILT_FPT__ windowArr[]);

extern int32_t
FILT_MovAverFilt_u32(
	filt_moving_average_i32_s *pStruct,
	int32_t newValue,
	int32_t pValueArr[]);

extern __FILT_FPT__
filter_db2 (
	__FILT_FPT__* In,
	size_t length_In);

extern __FILT_FPT__
__filter_db2(
	__FILT_FPT__* In,
	size_t length_In);

extern void
FILT_GetLastVal (
	__FILT_FPT__ *pData,
	__FILT_FPT__ val,
	uint16_t lenght);
/******************************************************************************/


/******************************************************************************/
// Секция определения макросов
/******************************************************************************/
#endif /* LIB_A_FILT_FILTERS_H_ */

////////////////////////////////////////////////////////////////////////////////
//  END OF FILE
////////////////////////////////////////////////////////////////////////////////
