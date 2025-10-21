#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/entidades/voos.h"
#include "include/parsing/datas.h"
#include <string.h>

typedef struct voo {
        char *flight_id;         // identificador único do voo
        DataHora *departure;         // data e hora de partida estimada (aaaa-mm-dd hh:mm)
        DataHora *actual_departure;  // data e hora de partida real
        DataHora *arrival;           // data e hora de chegada estimada
        DataHora *actual_arrival;    // data e hora de chegada real
        char *gate;              // porta de embarque
        char *status;            // estado: On Time, Delayed, Cancelled
        char *origin;            // código IATA do aeroporto de origem
        char *destination;       // código IATA do aeroporto de destino
        char *aircraft;          // identificador único da aeronave
        char *airline;           // nome da companhia aérea
        char *tracking_url;      // URL para rastreamento do voo
} Voo;

    /* Helper: duplicate string safely (returns NULL if input NULL)
        Uses strdup for simplicity (POSIX). */
    static char *dup_safe(const char *s) {
         return s ? strdup(s) : NULL;
    }

    /* Duplicate/free helpers for DataHora (assumes datas.h provides these) */
    static DataHora *dh_dup_safe(const DataHora *d) {
        return d ? datahora_clone(d) : NULL;
    }
    static void dh_free_safe(DataHora *d) {
        if (d) datahora_free(d);
    }

    /* Create a new Voo with provided values (duplicates all strings and DataHora).
       Any parameter may be NULL. Returns NULL on allocation failure. */
    Voo *voo_create(const char *flight_id,
                    const DataHora *departure,
                    const DataHora *actual_departure,
                    const DataHora *arrival,
                    const DataHora *actual_arrival,
                    const char *gate,
                    const char *status,
                    const char *origin,
                    const char *destination,
                    const char *aircraft,
                    const char *airline,
                    const char *tracking_url) {
        Voo *v = voo_inicializar();
        if (!v) return NULL;

        voo_set_flight_id(v, flight_id);
        voo_set_departure(v, departure);
        voo_set_actual_departure(v, actual_departure);
        voo_set_arrival(v, arrival);
        voo_set_actual_arrival(v, actual_arrival);
        voo_set_gate(v, gate);
        voo_set_status(v, status);
        voo_set_origin(v, origin);
        voo_set_destination(v, destination);
        voo_set_aircraft(v, aircraft);
        voo_set_airline(v, airline);
        voo_set_tracking_url(v, tracking_url);

        return v;
    }

    Voo* voo_inicializar() {
        Voo* v = malloc(sizeof(Voo));
        if (v == NULL) {
            return NULL; // Falha na alocação
        }
        v->flight_id = NULL;
        v->departure = NULL;
        v->actual_departure = NULL;
        v->arrival = NULL;
        v->actual_arrival = NULL;
        v->gate = NULL;
        v->status = NULL;
        v->origin = NULL;
        v->destination = NULL;
        v->aircraft = NULL;
        v->airline = NULL;
        v->tracking_url = NULL;

        return v;
    }

    /* Free all string members and DataHora members but do not free the struct itself */
    void voo_clear(Voo *v) {
        if (!v) return;
        free(v->flight_id); v->flight_id = NULL;
        dh_free_safe(v->departure); v->departure = NULL;
        dh_free_safe(v->actual_departure); v->actual_departure = NULL;
        dh_free_safe(v->arrival); v->arrival = NULL;
        dh_free_safe(v->actual_arrival); v->actual_arrival = NULL;
        free(v->gate); v->gate = NULL;
        free(v->status); v->status = NULL;
        free(v->origin); v->origin = NULL;
        free(v->destination); v->destination = NULL;
        free(v->aircraft); v->aircraft = NULL;
        free(v->airline); v->airline = NULL;
        free(v->tracking_url); v->tracking_url = NULL;
    }

    /* Free the struct and its contents */
    void voo_free(Voo *v) {
        if (!v) return;
        voo_clear(v);
        free(v);
    }

    /* Clone a Voo (deep copy). Returns NULL on allocation failure. */
    Voo *voo_clone(const Voo *src) {
        if (!src) return NULL;
        return voo_create(src->flight_id, src->departure, src->actual_departure,
                          src->arrival, src->actual_arrival, src->gate,
                          src->status, src->origin, src->destination,
                          src->aircraft, src->airline, src->tracking_url);
    }

    /* Generic setter used by the typed setters below for strings.
       Returns 0 on success, -1 on allocation failure. */
    static int voo_set_generic(char **field, const char *value) {
        char *dup = dup_safe(value);
        if (value && !dup) return -1;
        free(*field);
        *field = dup;
        return 0;
    }

    /* Generic setter for DataHora fields.
       Returns 0 on success, -1 on allocation failure. */
    static int voo_set_datahora(DataHora **field, const DataHora *value) {
        DataHora *dup = dh_dup_safe(value);
        if (value && !dup) return -1;
        dh_free_safe(*field);
        *field = dup;
        return 0;
    }

    /* Typed setters (return 0 on success, -1 on allocation failure) */
    int voo_set_flight_id(Voo *v, const char *s) { return voo_set_generic(&v->flight_id, s); }
    int voo_set_departure(Voo *v, const DataHora *s) { return voo_set_datahora(&v->departure, s); }
    int voo_set_actual_departure(Voo *v, const DataHora *s) { return voo_set_datahora(&v->actual_departure, s); }
    int voo_set_arrival(Voo *v, const DataHora *s) { return voo_set_datahora(&v->arrival, s); }
    int voo_set_actual_arrival(Voo *v, const DataHora *s) { return voo_set_datahora(&v->actual_arrival, s); }
    int voo_set_gate(Voo *v, const char *s) { return voo_set_generic(&v->gate, s); }
    int voo_set_status(Voo *v, const char *s) { return voo_set_generic(&v->status, s); }
    int voo_set_origin(Voo *v, const char *s) { return voo_set_generic(&v->origin, s); }
    int voo_set_destination(Voo *v, const char *s) { return voo_set_generic(&v->destination, s); }
    int voo_set_aircraft(Voo *v, const char *s) { return voo_set_generic(&v->aircraft, s); }
    int voo_set_airline(Voo *v, const char *s) { return voo_set_generic(&v->airline, s); }
    int voo_set_tracking_url(Voo *v, const char *s) { return voo_set_generic(&v->tracking_url, s); }


    /* Getters: retornam o ponteiro interno (ou NULL). Não transferem propriedade. */
    const char *voo_get_flight_id(const Voo *v) { return v ? v->flight_id : NULL; }
    DataHora *voo_get_departure(const Voo *v) { return v ? v->departure : NULL; }
    const DataHora *voo_get_actual_departure(const Voo *v) { return v ? v->actual_departure : NULL; }
    const DataHora *voo_get_arrival(const Voo *v) { return v ? v->arrival : NULL; }
    const DataHora *voo_get_actual_arrival(const Voo *v) { return v ? v->actual_arrival : NULL; }
    const char *voo_get_gate(const Voo *v) { return v ? v->gate : NULL; }
    const char *voo_get_status(const Voo *v) { return v ? v->status : NULL; }
    const char *voo_get_origin(const Voo *v) { return v ? v->origin : NULL; }
    const char *voo_get_destination(const Voo *v) { return v ? v->destination : NULL; }
    const char *voo_get_aircraft(const Voo *v) { return v ? v->aircraft : NULL; }
    const char *voo_get_airline(const Voo *v) { return v ? v->airline : NULL; }
    const char *voo_get_tracking_url(const Voo *v) { return v ? v->tracking_url : NULL; }



