/*
  @file weather.c
  @brief Implements weather mesuarement structure and methods
*/
#include <stdlib.h>
#include "weather.h"

static const int AMOUNT_OF_WEATHER_VARS = 6 ;

Weather weather_from_file(FILE* file){    //cargo mis datos en weather
    int res;
    Weather weather;
        res= fscanf (file, EXPECTED_WEATHER_FILE_FORMAT ,&weather._average_temp, &weather._max_temp,&weather._min_temp,
                   &weather._pressure, &weather._moisture, &weather._rainfall);
        if (res!=AMOUNT_OF_WEATHER_VARS){
          printf ("Data load error\n");
          exit(EXIT_FAILURE);
        }

    return weather;
} 

void weather_to_file(FILE* file, Weather weather)   //escribe los datos de weather en file
{
    fprintf(file, EXPECTED_WEATHER_FILE_FORMAT, weather._average_temp, 
            weather._max_temp, weather._min_temp, weather._pressure, weather._moisture, weather._rainfall);
}
