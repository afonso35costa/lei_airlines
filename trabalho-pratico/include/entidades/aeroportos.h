#ifndef AEROPORTOS_H
#define AEROPORTOS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct aeroportos Aeroportos;

// Cria um novo aeroporto e aloca memória
Aeroportos* create_aeroporto(void);

// Inicializa um aeroporto com dados
Aeroportos* init_aeroporto(const char *code, const char *name, const char *city,
                           const char *country, double latitude, double longitude,
                           const char *icao, const char *type);

// Liberta a memória associada a um aeroporto
void destroy_aeroporto(Aeroportos *a);




//GETTERS - Funções para obter valores

const char* get_code_aeroporto(const Aeroportos *a);
const char* get_name_aeroporto(const Aeroportos *a);
const char* get_city_aeroporto(const Aeroportos *a);
const char* get_country_aeroporto(const Aeroportos *a);
double get_latitude_aeroporto(const Aeroportos *a);
double get_longitude_aeroporto(const Aeroportos *a);
const char* get_icao_aeroporto(const Aeroportos *a);
const char* get_type_aeroporto(const Aeroportos *a);



//SETTERS - Funções para definir valores

void set_code_aeroporto(Aeroportos *a, const char *code);
void set_name_aeroporto(Aeroportos *a, const char *name);
void set_city_aeroporto(Aeroportos *a, const char *city);
void set_country_aeroporto(Aeroportos *a, const char *country);
void set_latitude_aeroporto(Aeroportos *a, double latitude);
void set_longitude_aeroporto(Aeroportos *a, double longitude);
void set_icao_aeroporto(Aeroportos *a, const char *icao);
void set_type_aeroporto(Aeroportos *a, const char *type);


#endif

