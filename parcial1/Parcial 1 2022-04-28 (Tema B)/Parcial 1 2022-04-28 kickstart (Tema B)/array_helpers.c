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
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}
    /* printf("\n"); */
    /* // -1 ya que cada hora se entrega un item de cada tipo */

unsigned int extra_space_fee_cost (DeliveryTable a) {
  unsigned int p = 0u;

  // Ver cuanto va al deposito ese dia
  unsigned int total_boxes = 0u; // Cantidad de cajas que van al deposito
  unsigned int total_letters = 0u; // Cantidad de cartas que van al deposito
  // Asumo que para la hora h, el indice es h-1
  for(unsigned int i=0u; i<=FEE_CLOSE_HOUR; i++) {
    if(a[boxes][i].items_amount > 0) { // Si hay cajas en la hora i
      total_boxes += a[boxes][i].items_amount; // Sumo la cantidad de cajas
    }
    if(a[letters][i].items_amount > 0) { // Si hay cartas en la hora i
      total_letters += a[letters][i].items_amount; // Sumo la cantidad de cartas
    }
  }

  // Calcular penalty total
  
  p = BOX_PENALTY*(total_boxes - MAX_ALLOWED_BOXES) + LETTER_PENALTY*(total_letters - MAX_ALLOWED_LETTERS); // Penalidad total

  return p;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (i < HOURS && !feof(file)) {
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_boxes = flight_from_file(file, code, boxes); // Cajas
    Flight flight_letters = flight_from_file(file, code, letters); // Cartas
    array[boxes][flight_boxes.hour-1] = flight_boxes; // -1 ya que cada hora se entrega un item de cada tipo
    array[letters][flight_boxes.hour-1] = flight_letters; // -1 ya que cada hora se entrega un item de cada tipo
    /* array[boxes][i] = flight_boxes; */
    /* array[letters][i] = flight_letters; */
    i++;
  }
}