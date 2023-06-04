#ifndef _WEATHER_UTILS_H_
#define _WEATHER_UTILS_H_
#include "weather.h"
#include "array_helpers.h"

//The minim temperature recored in Cordoba in the his history
int temp_min (WeatherTable array);

//The maxim temperature per year in Cordoba
void temp_max_year (WeatherTable array, int output[YEARS]);

//The months with more rainfalls per each year
void month_max_rainfall (WeatherTable array, month_t output[YEARS]);





#endif