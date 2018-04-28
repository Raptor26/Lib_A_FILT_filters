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
/******************************************************************************/


/******************************************************************************/
// Секция определения типов
typedef struct
{
	/**
	 * @brief	Коэффициент фильтра;
	 */
	float filtCoeff;

	/**
	 * @brief	Выходное значение фильтра за предыдущий вызов функции;
	 */
	float filtValue;
} FILT_comp_filt_s;

/**
 * @brief	Структура для функции скользящего среднего FILT_MovAverageFilt_f32()
 */
typedef struct
{
	/**
	 * @brief	Количество последних "n" измерений, по которым будет
	 * 			производится усреднение
	 */
	uint32_t init_windowWidth;

	/**
	 * @brief	Счетчик номера ячейки массива, куда будет записано новое значение
	 */
	uint32_t cnt;

	/**
	 * @brief	Фильтрованное значение на шаге <t-1>
	 */
	float preFiltValue;

	/**
	 * @brief	Фильтрованное значение, которое будет рассчитано при вызове функции
	 */
	float filtValue;

} FILT_moving_average_filt_f32_s;

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

} FILT_moving_average_filt_i32_s;
/******************************************************************************/

/******************************************************************************/
// Секция определения глобальных переменных
/******************************************************************************/

/******************************************************************************/
// Секция прототипов глобальных функций
extern float FILT_ComplFilt_f32(
    FILT_comp_filt_s *pStruct,
    float value);

extern float FILT_MovAverageFilt_f32(
    FILT_moving_average_filt_f32_s *pStruct,
    float newValue,
    float pValueArr[]);

extern float FILT_MovAverageFiltWithWindow_f32(
    FILT_moving_average_filt_f32_s *pStruct,
    float newValue,
    float pValueArr[],
    float windowArr[]);

extern int32_t FILT_MovAverFilt_u32(
    FILT_moving_average_filt_i32_s *pStruct,
    int32_t newValue,
    int32_t pValueArr[]);
/******************************************************************************/


/******************************************************************************/
// Секция определения макросов
/******************************************************************************/
#endif /* LIB_A_FILT_FILTERS_H_ */

////////////////////////////////////////////////////////////////////////////////
//  END OF FILE
////////////////////////////////////////////////////////////////////////////////
