/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 3 ;

Flight flight_from_file(FILE* file, char code)
{
    Flight flight;
    flight.code = code;
    int tipo_de_vuelo;
    int res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT,&tipo_de_vuelo,&flight.hour, &flight.passengers_amount);
    if (res != AMOUNT_OF_FLIGHT_VARS) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    if(tipo_de_vuelo == 0){
      flight.type = arrival;
    } else if(tipo_de_vuelo == 1){
      flight.type = departure;
    } else {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);      
    }
    return flight;
}
