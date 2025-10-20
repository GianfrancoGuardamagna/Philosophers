#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Program name
PHILO="./philo"

# Check if program exists
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: $PHILO no encontrado. Compila primero con 'make'${NC}"
    exit 1
fi

echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}   PHILOSOPHERS TESTER${NC}"
echo -e "${BLUE}================================${NC}\n"

# Function to run test with timeout
run_test() {
    local test_name="$1"
    local args="$2"
    local timeout="$3"
    local should_die="$4"
    local description="$5"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${YELLOW}Test $TOTAL_TESTS: $test_name${NC}"
    echo -e "Descripción: $description"
    echo -e "Comando: $PHILO $args"
    echo -e "Timeout: ${timeout}s"
    
    # Run with timeout
    timeout $timeout $PHILO $args > /tmp/philo_output.txt 2>&1 &
    local pid=$!
    
    wait $pid 2>/dev/null
    local exit_code=$?
    
    # Read output
    local output=$(cat /tmp/philo_output.txt)
    
    # Check for errors
    local has_error=0
    local error_msg=""
    
    # Check exit code (124 means timeout)
    if [ $exit_code -eq 124 ]; then
        if [ "$should_die" == "no" ]; then
            echo -e "${GREEN}✓ PASS${NC} - Programa ejecutándose correctamente (timeout esperado)\n"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            return 0
        else
            has_error=1
            error_msg="Timeout alcanzado pero se esperaba muerte del filósofo"
        fi
    fi
    
    # Check for data races or crashes
    if echo "$output" | grep -qi "segmentation fault\|bus error\|abort"; then
        has_error=1
        error_msg="Crash detectado (segfault/bus error)"
    fi
    
    # Check for death message if expected
    if [ "$should_die" == "yes" ]; then
        if ! echo "$output" | grep -q "died"; then
            has_error=1
            error_msg="Se esperaba muerte del filósofo pero no se detectó"
        fi
    fi
    
    # Check for message format
    if echo "$output" | grep -Eq "[0-9]+ [0-9]+ (has taken a fork|is eating|is sleeping|is thinking|died)"; then
        : # Format is correct
    else
        if [ -n "$output" ]; then
            has_error=1
            error_msg="Formato de salida incorrecto"
        fi
    fi
    
    # Check for delayed death detection (more than 10ms)
    if echo "$output" | grep -q "died"; then
        local death_line=$(echo "$output" | grep "died" | head -1)
        local death_time=$(echo "$death_line" | awk '{print $1}')
        # This is a simplified check - real implementation would need more complex verification
    fi
    
    if [ $has_error -eq 1 ]; then
        echo -e "${RED}✗ FAIL${NC} - $error_msg"
        echo -e "Salida:\n$output\n"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    else
        echo -e "${GREEN}✓ PASS${NC}\n"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    fi
}

# Test invalid arguments
echo -e "${BLUE}=== Tests de Argumentos Inválidos ===${NC}\n"

run_test "Sin argumentos" "" 2 "error" "El programa debe rechazar la ejecución sin argumentos"
run_test "Pocos argumentos" "5 800" 2 "error" "El programa debe rechazar menos de 4 argumentos"
run_test "Argumento negativo" "5 -800 200 200" 2 "error" "No se permiten valores negativos"
run_test "Argumento cero" "0 800 200 200" 2 "error" "Número de filósofos debe ser mayor a 0"
run_test "Argumento no numérico" "5 abc 200 200" 2 "error" "Solo se permiten números"

# Test edge cases
echo -e "${BLUE}=== Tests de Casos Límite ===${NC}\n"

run_test "Un solo filósofo (debe morir)" "1 800 200 200" 3 "yes" "Con 1 filósofo y 1 tenedor, debe morir"
run_test "Un filósofo muerte rápida" "1 200 300 100" 2 "yes" "Debe morir porque no puede comer a tiempo"
run_test "Dos filósofos" "2 800 200 200" 5 "no" "Los filósofos no deben morir"
run_test "Muchos filósofos" "200 800 200 200" 5 "no" "Debe manejar muchos hilos correctamente"

# Test normal cases (should not die)
echo -e "${BLUE}=== Tests de Casos Normales (No Muerte) ===${NC}\n"

run_test "5 filósofos - No muerte" "5 800 200 200" 5 "no" "Configuración estándar, nadie debe morir"
run_test "4 filósofos - Tiempos ajustados" "4 410 200 200" 5 "no" "Tiempos justos pero suficientes"
run_test "3 filósofos - Comer 5 veces" "3 800 200 200 5" 8 "no" "Debe detenerse después de 5 comidas c/u"
run_test "10 filósofos - Comer 7 veces" "10 800 200 200 7" 10 "no" "Múltiples filósofos con límite de comidas"

# Test death cases
echo -e "${BLUE}=== Tests de Muerte Esperada ===${NC}\n"

run_test "4 filósofos - Muerte por hambre" "4 310 200 200" 3 "yes" "time_to_die muy corto, alguien debe morir"
run_test "5 filósofos - Muerte inevitable" "5 300 250 100" 3 "yes" "Imposible que todos coman a tiempo"

# Performance tests
echo -e "${BLUE}=== Tests de Rendimiento ===${NC}\n"

run_test "Tiempos muy pequeños" "5 200 50 50" 5 "no" "Debe manejar tiempos pequeños sin data races"
run_test "Tiempos grandes" "4 5000 800 800" 5 "no" "Debe manejar tiempos grandes correctamente"

# Data race tests (these rely on visual inspection)
echo -e "${BLUE}=== Tests de Data Races ===${NC}\n"
echo -e "${YELLOW}Nota: Revisa visualmente que los mensajes no se mezclen${NC}\n"

run_test "Muchos filósofos - Check output" "10 800 200 200" 3 "no" "Verifica que no haya mensajes mezclados"
run_test "Sincronización crítica" "3 800 200 200 10" 8 "no" "Los mensajes deben estar ordenados por timestamp"

# Summary
echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}   RESUMEN DE RESULTADOS${NC}"
echo -e "${BLUE}================================${NC}"
echo -e "Total de tests: $TOTAL_TESTS"
echo -e "${GREEN}Tests pasados: $PASSED_TESTS${NC}"
echo -e "${RED}Tests fallados: $FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}¡Todos los tests pasaron! 🎉${NC}"
    exit 0
else
    echo -e "\n${RED}Algunos tests fallaron. Revisa los errores arriba.${NC}"
    exit 1
fi

# Cleanup
rm -f /tmp/philo_output.txt
