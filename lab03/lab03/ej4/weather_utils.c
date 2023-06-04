#include "weather_utils.h"

int temp_min (WeatherTable array){
    int min_aux=array[0][january][0]._min_temp;

    for (unsigned int year=0; year< YEARS; ++year){
        for (month_t month=january; month <= december; ++month){
            for (unsigned int day=0; day < LST_DAY; ++day){
                if( min_aux > array[year][month][day]._min_temp){
                    min_aux= array[year][month][day]._min_temp;
                }
            }
        }
    }
    return min_aux;
}

void temp_max_year (WeatherTable array, int output[YEARS]){
    
    for (unsigned int year=0; year< YEARS; ++year){
        int max_temp = array[year][january][0]._max_temp;
        for (month_t month=january; month <= december ; ++month){
            for (unsigned int day=0; day <LST_DAY; ++day){
                if (max_temp < array[year][month][day]._max_temp){
                    max_temp= array[year][month][day]._max_temp;
                }
            }
        }
        output[year]=max_temp;
    }

}

void month_max_rainfall (WeatherTable array, month_t output[YEARS]){

    for (unsigned int year=0 ; year< YEARS; ++year){
        month_t month_max = january;
        unsigned int max_prec=0.0;
        for (month_t month=january; month <=december ; ++month){
            unsigned int suma_prec=0.0; 
            for (unsigned int day=0; day < LST_DAY; ++day){
                suma_prec+= array[year][month][day]._rainfall;
            }
            if (suma_prec > max_prec){
                max_prec = suma_prec;
                month_max=month;
            }
        }
        output[year]=month_max;
    }

}