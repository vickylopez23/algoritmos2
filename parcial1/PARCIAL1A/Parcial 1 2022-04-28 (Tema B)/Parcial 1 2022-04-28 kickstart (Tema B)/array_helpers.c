/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last entry in flight table
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}
//esquema es codigo,hora de llegada,numero de items ,hora de llegada,numero de items
unsigned int extra_space_fee_cost (DeliveryTable a) {
    unsigned int extra_space_fee = 0u;
  for (unsigned int  hour = 0u; hour < HOURS; ++hour) {
    unsigned int boxes = 0u;
    unsigned int letters = 0u;
    //recorro los tipos de vuelos
    for (unsigned int type = 0u; type < TYPE; ++type) {
      //obtengo el vuelo
      Flight f = a[type][hour];
      //si es de tipo 0 es un vuelo de cajas
      if (f.type == 0) {
        //sumo la cantidad de cajas
        boxes += f.items_amount;
      } else {
        //sumo la cantidad de cartas
        letters += f.items_amount;
      }
    }
    //si hay mas cajas que cartas
    if (boxes > letters) {
      //calculo el costo extra
      extra_space_fee += (boxes - letters) * 10;
    }

  }
  
  return 0;
}
/*
unsigned int extra_space_fee_cost (DeliveryTable a) {
  unsigned int p = 0u;

  // Ver cuanto va al deposito ese dia
  unsigned int total_boxes = 0u;
  unsigned int total_letters = 0u;
  // Asumo que para la hora h, el indice es h-1
  for(unsigned int i=0u; i<=FEE_CLOSE_HOUR; i++) {
    if(a[boxes][i].items_amount > 0) {
      total_boxes += a[boxes][i].items_amount;
    }
    if(a[letters][i].items_amount > 0) {
      total_letters += a[letters][i].items_amount;
    }
  }

  // Calcular penalty total
  
  p = BOX_PENALTY*(total_boxes - MAX_ALLOWED_BOXES) + LETTER_PENALTY*(total_letters - MAX_ALLOWED_LETTERS);

  return p;
}*/


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (!feof(file)) {
    int res = fscanf(file,"_%c_", &code );
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_boxes = flight_from_file(file,code, boxes);
    Flight flight_letters = flight_from_file(file,code, letters);
    array[boxes][flight_boxes.hour-1] = flight_boxes;
    array[letters][flight_boxes.hour-1] = flight_letters;
    i++;
    
  }
}
