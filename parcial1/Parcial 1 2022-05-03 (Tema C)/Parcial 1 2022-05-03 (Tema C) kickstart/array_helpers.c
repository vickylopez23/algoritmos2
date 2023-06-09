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

unsigned int extra_space_fee_cost (DeliveryTable a, unsigned int hour) {
  unsigned int p = 0u;

  // Ver cuanto va al deposito ese dia
  unsigned int total_boxes = 0u;
  unsigned int total_letters = 0u;
  // Asumo que para la hora h, el indice es h-1 y que los flights estan ordenados por hora
  for(unsigned int i=0u; i<=hour && i<HOURS; i++) { // i<=hour para que cuente el vuelo de la hora h
    if(a[boxes][i].items_amount > 0) {
      total_boxes += a[boxes][i].items_amount; // a[boxes][i] es un flight
    }
    if(a[letters][i].items_amount > 0) { // a[letters][i] es un flight
      total_letters += a[letters][i].items_amount; // a[letters][i] es un flight
    }
  }

  // Calcular penalty total
  if(total_boxes > MAX_ALLOWED_BOXES) {
    p += BOX_PENALTY*(total_boxes - MAX_ALLOWED_BOXES); // BOX_PENALTY es 10
  }
  if(total_letters > MAX_ALLOWED_LETTERS) {
    p += LETTER_PENALTY*(total_letters - MAX_ALLOWED_LETTERS); // LETTER_PENALTY es 5
  }

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
  unsigned int arrival_hour;
  int i = 0;
  while (i < HOURS && !feof(file)) {
    // Leo el codigo
    int res = fscanf(file, "\n_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    // Leo la hora
    res = fscanf(file, " %u ", &arrival_hour);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }

    Flight flight_boxes = flight_from_file(file, code, arrival_hour); // flight_from_file esta en flight.c
    Flight flight_letters = flight_from_file(file, code, arrival_hour);   // flight_from_file esta en flight.c

    // Guardo los flights usando el indice h-1 para la hora h
    array[boxes][arrival_hour-1] = flight_boxes;
    array[letters][arrival_hour-1] = flight_letters;
    i++;
  }
}