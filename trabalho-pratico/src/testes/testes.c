#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <assert.h>

#include "queries.h"
#include "aeroportos.h"
#include "aeronaves.h"
#include "voos.h"

// ===========================================
// FUNÇÕES AUXILIARES PARA TESTES
// ===========================================

// Cria aeroporto de teste seguindo o padrão do código
Aeroportos* create_test_airport(const char *code, const char *name, const char *city, 
                               const char *country, const char *type) {
    return init_aeroporto(code, name, city, country, 0.0, 0.0, NULL, type);
}

// Cria aeronave de teste seguindo o padrão do código
Aeronaves* create_test_aircraft(const char *identifier, const char *manufacturer, 
                               const char *model) {
    return init_aeronave(identifier, manufacturer, model, 2020, 180, 5000);
}

// Cria voo de teste seguindo a estrutura real
Voo* create_test_flight(const char *flight_id, const char *aircraft, const char *origin,
                       const char *destination, const char *status, DataHora *actual_departure) {
    Voo *v = create_voo();
    if (!v) return NULL;
    
    set_flight_id(v, flight_id);
    set_aircraft(v, aircraft);
    set_origin(v, origin);
    set_destination(v, destination);
    set_status(v, status);
    if (actual_departure) {
        set_actual_departure(v, actual_departure);
    }
    
    return v;
}

// Função para comparar strings de forma segura
int safe_strcmp(const char *a, const char *b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    return strcmp(a, b);
}

// ===========================================
// TESTES QUERY 1
// ===========================================

void test_query1_existing_airport() {
    printf("Testing Query 1 - Existing Airport...\n");
    
    // Setup
    GestorAeroportos *ga = gestor_aeroportos_create();
    Aeroportos *airport = create_test_airport("LIS", "Lisbon Airport", "Lisbon", "Portugal", "International");
    gestor_aeroportos_add(ga, airport);
    
    FILE *output = tmpfile();
    
    // Test
    query1(ga, "LIS", output);
    
    // Verify
    rewind(output);
    char buffer[1024];
    fgets(buffer, sizeof(buffer), output);
    
    // Remove newline para comparação
    buffer[strcspn(buffer, "\n")] = 0;
    
    char expected[] = "LIS;Lisbon Airport;Lisbon;Portugal;International";
    assert(strcmp(buffer, expected) == 0);
    
    // Cleanup
    fclose(output);
    gestor_aeroportos_free(ga);
    
    printf("✅ Query 1 - Existing Airport: PASSED\n");
}

void test_query1_non_existing_airport() {
    printf("Testing Query 1 - Non-existing Airport...\n");
    
    // Setup
    GestorAeroportos *ga = gestor_aeroportos_create();
    FILE *output = tmpfile();
    
    // Test
    query1(ga, "XYZ", output);
    
    // Verify (should be empty line)
    rewind(output);
    char buffer[1024];
    char *result = fgets(buffer, sizeof(buffer), output);
    
    assert(result != NULL && strcmp(buffer, "\n") == 0);
    
    // Cleanup
    fclose(output);
    gestor_aeroportos_free(ga);
    
    printf("✅ Query 1 - Non-existing Airport: PASSED\n");
}

// ===========================================
// TESTES QUERY 2
// ===========================================

void test_query2_basic_functionality() {
    printf("Testing Query 2 - Basic Functionality...\n");
    
    // Setup gestores
    GestorAeronaves *gae = gestor_aeronaves_create();
    GestorVoos *gv = gestor_voos_create();
    
    // Criar aeronaves
    Aeronaves *aircraft1 = create_test_aircraft("CS-ABC", "Boeing", "737-800");
    Aeronaves *aircraft2 = create_test_aircraft("CS-DEF", "Airbus", "A320");
    gestor_aeronaves_add(gae, aircraft1);
    gestor_aeronaves_add(gae, aircraft2);
    
    // Criar voos (CS-ABC tem 3 voos, CS-DEF tem 2)
    Voo *v1 = create_test_flight("TP101", "CS-ABC", "LIS", "OPO", "On Time", NULL);
    Voo *v2 = create_test_flight("TP102", "CS-ABC", "OPO", "LIS", "On Time", NULL);
    Voo *v3 = create_test_flight("TP103", "CS-ABC", "LIS", "FAO", "Delayed", NULL);
    Voo *v4 = create_test_flight("TP201", "CS-DEF", "LIS", "MAD", "On Time", NULL);
    Voo *v5 = create_test_flight("TP202", "CS-DEF", "MAD", "LIS", "On Time", NULL);
    Voo *v6 = create_test_flight("TP999", "CS-ABC", "LIS", "BCN", "Cancelled", NULL); // Cancelado - não conta
    
    gestor_voos_add(gv, v1);
    gestor_voos_add(gv, v2);
    gestor_voos_add(gv, v3);
    gestor_voos_add(gv, v4);
    gestor_voos_add(gv, v5);
    gestor_voos_add(gv, v6);
    
    FILE *output = tmpfile();
    
    // Test - Top 2 aeronaves
    query2(gae, gv, 2, NULL, output);
    
    // Verify
    rewind(output);
    char buffer[1024];
    
    // Primeira linha: CS-ABC com 3 voos
    assert(fgets(buffer, sizeof(buffer), output) != NULL);
    assert(strstr(buffer, "CS-ABC") != NULL);
    assert(strstr(buffer, "Boeing") != NULL);
    assert(strstr(buffer, "737-800") != NULL);
    assert(strstr(buffer, "3") != NULL);
    
    // Segunda linha: CS-DEF com 2 voos
    assert(fgets(buffer, sizeof(buffer), output) != NULL);
    assert(strstr(buffer, "CS-DEF") != NULL);
    assert(strstr(buffer, "Airbus") != NULL);
    assert(strstr(buffer, "A320") != NULL);
    assert(strstr(buffer, "2") != NULL);
    
    // Cleanup
    fclose(output);
    gestor_voos_free(gv);
    gestor_aeronaves_free(gae);
    
    printf("✅ Query 2 - Basic Functionality: PASSED\n");
}

void test_query2_manufacturer_filter() {
    printf("Testing Query 2 - Manufacturer Filter...\n");
    
    // Setup gestores
    GestorAeronaves *gae = gestor_aeronaves_create();
    GestorVoos *gv = gestor_voos_create();
    
    // Criar aeronaves
    Aeronaves *aircraft1 = create_test_aircraft("CS-ABC", "Boeing", "737-800");
    Aeronaves *aircraft2 = create_test_aircraft("CS-DEF", "Airbus", "A320");
    gestor_aeronaves_add(gae, aircraft1);
    gestor_aeronaves_add(gae, aircraft2);
    
    // Criar voos
    Voo *v1 = create_test_flight("TP101", "CS-ABC", "LIS", "OPO", "On Time", NULL);
    Voo *v2 = create_test_flight("TP201", "CS-DEF", "LIS", "MAD", "On Time", NULL);
    gestor_voos_add(gv, v1);
    gestor_voos_add(gv, v2);
    
    FILE *output = tmpfile();
    
    // Test - Só aeronaves Boeing
    query2(gae, gv, 10, "Boeing", output);
    
    // Verify - só deve aparecer CS-ABC
    rewind(output);
    char buffer[1024];
    assert(fgets(buffer, sizeof(buffer), output) != NULL);
    assert(strstr(buffer, "CS-ABC") != NULL);
    assert(strstr(buffer, "Boeing") != NULL);
    
    // Não deve haver segunda linha
    char *result = fgets(buffer, sizeof(buffer), output);
    assert(result == NULL);
    
    // Cleanup
    fclose(output);
    gestor_voos_free(gv);
    gestor_aeronaves_free(gae);
    
    printf("✅ Query 2 - Manufacturer Filter: PASSED\n");
}

void test_query2_tie_breaking() {
    printf("Testing Query 2 - Tie Breaking...\n");
    
    // Setup gestores
    GestorAeronaves *gae = gestor_aeronaves_create();
    GestorVoos *gv = gestor_voos_create();
    
    // Criar aeronaves (mesma quantidade de voos, testa ordenação por identifier)
    Aeronaves *aircraft1 = create_test_aircraft("CS-ZZZ", "Boeing", "737");
    Aeronaves *aircraft2 = create_test_aircraft("CS-AAA", "Airbus", "A320");
    gestor_aeronaves_add(gae, aircraft1);
    gestor_aeronaves_add(gae, aircraft2);
    
    // Criar voos - ambas com 1 voo
    Voo *v1 = create_test_flight("TP101", "CS-ZZZ", "LIS", "OPO", "On Time", NULL);
    Voo *v2 = create_test_flight("TP201", "CS-AAA", "LIS", "MAD", "On Time", NULL);
    gestor_voos_add(gv, v1);
    gestor_voos_add(gv, v2);
    
    FILE *output = tmpfile();
    
    // Test
    query2(gae, gv, 2, NULL, output);
    
    // Verify - CS-AAA deve vir primeiro (menor lexicograficamente)
    rewind(output);
    char buffer[1024];
    assert(fgets(buffer, sizeof(buffer), output) != NULL);
    assert(strstr(buffer, "CS-AAA") != NULL);
    
    assert(fgets(buffer, sizeof(buffer), output) != NULL);
    assert(strstr(buffer, "CS-ZZZ") != NULL);
    
    // Cleanup
    fclose(output);
    gestor_voos_free(gv);
    gestor_aeronaves_free(gae);
    
    printf("✅ Query 2 - Tie Breaking: PASSED\n");
}

void test_query2_cancelled_flights_excluded() {
    printf("Testing Query 2 - Cancelled Flights Excluded...\n");
    
    // Setup gestores
    GestorAeronaves *gae = gestor_aeronaves_create();
    GestorVoos *gv = gestor_voos_create();
    
    // Criar aeronave
    Aeronaves *aircraft1 = create_test_aircraft("CS-ABC", "Boeing", "737-800");
    gestor_aeronaves_add(gae, aircraft1);
    
    // Criar voos - 2 normais, 1 cancelado
    Voo *v1 = create_test_flight("TP101", "CS-ABC", "LIS", "OPO", "On Time", NULL);
    Voo *v2 = create_test_flight("TP102", "CS-ABC", "OPO", "LIS", "Delayed", NULL);
    Voo *v3 = create_test_flight("TP999", "CS-ABC", "LIS", "BCN", "Cancelled", NULL); // Cancelado
    
    gestor_voos_add(gv, v1);
    gestor_voos_add(gv, v2);
    gestor_voos_add(gv, v3);
    
    FILE *output = tmpfile();
    
    // Test
    query2(gae, gv, 1, NULL, output);
    
    // Verify - deve contar apenas 2 voos (excluindo cancelado)
    rewind(output);
    char buffer[1024];
    assert(fgets(buffer, sizeof(buffer), output) != NULL);
    assert(strstr(buffer, "CS-ABC") != NULL);
    assert(strstr(buffer, "2") != NULL); // Só 2 voos contados
    
    // Cleanup
    fclose(output);
    gestor_voos_free(gv);
    gestor_aeronaves_free(gae);
    
    printf("✅ Query 2 - Cancelled Flights Excluded: PASSED\n");
}

// ===========================================
// TESTES QUERY 3
// ===========================================

void test_query3_no_flights_in_range() {
    printf("Testing Query 3 - No Flights in Range...\n");
    
    // Setup gestores
    GestorAeroportos *ga = gestor_aeroportos_create();
    GestorVoos *gv = gestor_voos_create();
    
    // Criar datas fictícias (assumindo que DataHora existe)
    DataHora *start = NULL; // Simplificado para teste
    DataHora *end = NULL;
    
    FILE *output = tmpfile();
    
    // Test - sem voos no sistema
    query3(ga, gv, start, end, output);
    
    // Verify - linha vazia
    rewind(output);
    char buffer[1024];
    char *result = fgets(buffer, sizeof(buffer), output);
    assert(result != NULL && strcmp(buffer, "\n") == 0);
    
    // Cleanup
    fclose(output);
    gestor_voos_free(gv);
    gestor_aeroportos_free(ga);
    
    printf("✅ Query 3 - No Flights in Range: PASSED\n");
}

// ===========================================
// TESTES DE EDGE CASES
// ===========================================

void test_query1_null_parameters() {
    printf("Testing Query 1 - Null Parameters...\n");
    
    FILE *output = tmpfile();
    
    // Test com parâmetros NULL
    query1(NULL, "LIS", output); // Gestor NULL
    query1(gestor_aeroportos_create(), NULL, output); // Código NULL
    query1(gestor_aeroportos_create(), "LIS", NULL); // Output NULL
    
    // Se chegou aqui, não houve crash
    fclose(output);
    
    printf("✅ Query 1 - Null Parameters: PASSED\n");
}

void test_query2_null_parameters() {
    printf("Testing Query 2 - Null Parameters...\n");
    
    FILE *output = tmpfile();
    
    // Test com parâmetros NULL
    query2(NULL, gestor_voos_create(), 5, NULL, output);
    query2(gestor_aeronaves_create(), NULL, 5, NULL, output);
    query2(gestor_aeronaves_create(), gestor_voos_create(), 0, NULL, output); // N = 0
    
    // Se chegou aqui, não houve crash
    fclose(output);
    
    printf("✅ Query 2 - Null Parameters: PASSED\n");
}

void test_query2_empty_gestors() {
    printf("Testing Query 2 - Empty Gestors...\n");
    
    // Setup gestores vazios
    GestorAeronaves *gae = gestor_aeronaves_create();
    GestorVoos *gv = gestor_voos_create();
    
    FILE *output = tmpfile();
    
    // Test com gestores vazios
    query2(gae, gv, 5, NULL, output);
    
    // Verify - nenhuma output
    rewind(output);
    char buffer[1024];
    char *result = fgets(buffer, sizeof(buffer), output);
    assert(result == NULL); // Nenhuma linha escrita
    
    // Cleanup
    fclose(output);
    gestor_voos_free(gv);
    gestor_aeronaves_free(gae);
    
    printf("✅ Query 2 - Empty Gestors: PASSED\n");
}

// ===========================================
// FUNÇÃO PRINCIPAL DOS TESTES
// ===========================================

int main() {
    printf("🧪 EXECUTANDO TESTES DAS QUERIES\n");
    printf("================================\n\n");
    
    // Testes Query 1
    printf("--- QUERY 1 TESTS ---\n");
    test_query1_existing_airport();
    test_query1_non_existing_airport();
    test_query1_null_parameters();
    
    printf("\n--- QUERY 2 TESTS ---\n");
    test_query2_basic_functionality();
    test_query2_manufacturer_filter();
    test_query2_tie_breaking();
    test_query2_cancelled_flights_excluded();
    test_query2_null_parameters();
    test_query2_empty_gestors();
    
    printf("\n--- QUERY 3 TESTS ---\n");
    test_query3_no_flights_in_range();
    
    printf("\n🎉 TODOS OS TESTES PASSARAM!\n");
    printf("=============================\n");
    
    return 0;
}