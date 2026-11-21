# LEI Airlines — Flight & Airport Data Processing Engine

[![Language: C](https://img.shields.io/badge/Language-C99%20%2F%20C11-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Library: GLib 2.0](https://img.shields.io/badge/Library-GLib%202.0-orange.svg)](https://docs.gtk.org/glib/)
[![Build: GNU Make](https://img.shields.io/badge/Build-GNU%20Make-brightgreen.svg)](https://www.gnu.org/software/make/)
[![Academic: UMinho LEI](https://img.shields.io/badge/Course-LI3%20%7C%20LEI%20UMinho-lightgrey.svg)](https://www.uminho.pt)
[![Academic Year: 2025/2026](https://img.shields.io/badge/Year-2025%2F2026-blueviolet.svg)](#authors)

A high-performance data processing and analytical querying engine implemented in **C**, developed for the **Laboratórios de Informática III (LI3)** course of the **Licenciatura em Engenharia Informática (LEI)** at the **University of Minho (2025/2026)**.

The system ingests, validates, organizes, and queries large volumes of interconnected aviation and travel data, including **airports**, **aircrafts**, **flights**, **passengers**, and **flight reservations**. It is designed with modularity, strict data encapsulation, robust validation rules, and low-latency query execution powered by GLib data structures.

---

## Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [System Architecture](#system-architecture)
- [Supported Queries](#supported-queries)
- [Dataset & Validation Rules](#dataset--validation-rules)
- [Dependencies & Prerequisites](#dependencies--prerequisites)
- [Compilation & Build](#compilation--build)
- [Usage & Execution Modes](#usage--execution-modes)
  - [1. Batch Mode (`programa-principal`)](#1-batch-mode-programa-principal)
  - [2. Interactive CLI Mode (`programa-interativo`)](#2-interactive-cli-mode-programa-interativo)
  - [3. Testing & Benchmarking Mode (`programa-testes`)](#3-testing--benchmarking-mode-programa-testes)
- [Repository Layout](#repository-layout)
- [Performance & Memory Safety](#performance--memory-safety)
- [Authors](#authors)

---

## Overview

Aviation systems handle hundreds of thousands of operational records daily. This project provides a robust engine capable of:
1. **Streaming & Parsing Large CSV Datasets:** Reads raw CSV records representing airports, aircraft fleets, scheduled and historical flights, passenger profiles, and flight bookings.
2. **Multi-Stage Validation:** Discards malformed or logically incoherent records, isolating them into dedicated error files (`*_errors.csv`) while loading only sanitized records into memory.
3. **In-Memory Analytical Queries:** Executes complex analytical queries with minimal overhead, supporting both standard (`<id>`) and formatted/alternative (`<id>S`) output formats.
4. **Three Execution Targets:** Supports automated batch evaluation, a user-friendly interactive terminal interface, and an automated testing suite with execution timers and memory profiling (`getrusage`).

---

## Key Features

- **Strict Encapsulation:** Opaque data structures for all entities; internal struct layouts are hidden from consumers, interacting solely through getters and setters.
- **Fast In-Memory Indexing:** Leverages **GLib 2.0** data structures (`GHashTable`, `GPtrArray`, `GList`) for $O(1)$ key-value lookups and sequential iteration with high cache locality.
- **Syntactic & Semantic Validation:** Validates field types, formats (IATA codes, ICAO codes, dates/times, email addresses), and logical consistency (e.g., flight departure precedes arrival, aircraft references exist, reservation flight legs are valid).
- **Dual Output Formats:**
  - **Standard format (`1`, `2`, `3`, `5`, `6`):** Semicolon-delimited fields (`;`).
  - **Formatted mode (`1S`, `2S`, `3S`, `5S`, `6S`):** Equals-delimited fields (`=`).
- **Benchmarking & Automated Diffing:** Built-in test program compares execution outputs line-by-line against ground truth files, detailing execution time per query and peak resident memory usage (RSS).

---

## System Architecture

The project follows a multi-tier modular architecture with clear separation of concerns:

```
┌─────────────────────────────────────────────────────────────┐
│                      Entry Points                           │
│  programa-principal   programa-interativo   programa-testes │
└──────────────┬──────────────────────┬──────────────┬────────┘
               │                      │              │
               ▼                      ▼              ▼
┌─────────────────────────────────────────────────────────────┐
│                      Queries Engine                         │
│               (queries.c / queries.h)                       │
└──────────────────────────────┬──────────────────────────────┘
                               │
               ┌───────────────┴───────────────┐
               ▼                               ▼
┌──────────────────────────────┐ ┌────────────────────────────┐
│      Managers / Gestores     │ │        I/O & Format        │
│  gestor_aeroportos           │ │  leitura.c (CSV streams)   │
│  gestor_aeronaves            │ │  escrita.c (Result/Errors) │
│  gestor_voos                 │ └────────────────────────────┘
│  gestor_passageiros          │
│  gestor_reservas             │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐ ┌────────────────────────────┐
│      Parsing & Validation    │ │         Entities           │
│  parser_geral / parser_*     │ │  aeroportos, aeronaves,    │
│  validacao_*                 │ │  voos, passageiros,        │
│  utils (datas, parser_utils) │ │  reservas (opaque structs) │
└──────────────────────────────┘ └────────────────────────────┘
```

### Module Responsibilities

| Module | Location | Responsibilities |
|---|---|---|
| **Entities** | `src/entidades/`, `include/entidades/` | Defines domain models (`Aeroportos`, `Aeronaves`, `Voos`, `Passageiros`, `Reservas`) with opaque structs and interface functions. |
| **Managers** | `src/gestores/`, `include/gestores/` | Collections managing entity lifecycles, hash indexing, and lookup operations. |
| **Parsing** | `src/parsing/`, `include/parsing/` | Reads CSV rows, extracts fields, and delegates records to validation and entity factories. |
| **Validation** | `src/validacao/`, `include/validacao/` | Verifies field formats, date consistency, numeric bounds, and cross-entity references. |
| **Queries** | `src/gestores/queries.c`, `include/gestores/queries.h` | Implements business logic and aggregations for all assignment queries. |
| **I/O** | `src/io/`, `include/io/` | File stream management, error CSV serialization, and query output formatting. |
| **Utils** | `src/utils/`, `include/utils/` | Date-time operations (`DataHora`, time delta computations) and string tokenization utilities. |

---

## Supported Queries

| Query | Command | Arguments | Description | Output Format |
|---|---|---|---|---|
| **Q1** | `1` / `1S` | `<airport_code>` | Summarizes airport metadata and counts of total arrivals and departures from active reservations. | `<code;name;city;country;type;dep;arr>` |
| **Q2** | `2` / `2S` | `<N> [manufacturer]` | Lists the top $N$ aircrafts with the highest number of completed flights. Can be filtered by aircraft manufacturer. | `<identifier;manufacturer;model;flight_count>` |
| **Q3** | `3` / `3S` | `<start_date> <end_date>` | Finds the airport with the greatest number of departed flights within a date interval (`YYYY-MM-DD`). | `<code;name;city;country;departures>` |
| **Q4** | `4` / `4S` | *None* | Specification placeholder (reserved for future extensions; outputs a blank line). | `\n` |
| **Q5** | `5` / `5S` | `<N>` | Lists the top $N$ airlines with the highest average departure delay on delayed flights (rounded to 3 decimals). | `<airline;delayed_flights_count;average_delay>` |
| **Q6** | `6` / `6S` | `<nationality>` | Identifies the most frequent destination airport for passengers of a specified nationality (supports multi-word names). | `<airport_code;passenger_count>` |

> **Note on Delimiters:** Standard query commands (`1`, `2`, `3`, `5`, `6`) output results separated by semicolons (`;`). Commands with the `S` suffix (`1S`, `2S`, `3S`, `5S`, `6S`) output results separated by equals signs (`=`).

---

## Dataset & Validation Rules

The application ingests five CSV datasets containing double-quoted, comma-delimited columns:

1. **`airports.csv`**: `code`, `name`, `city`, `country`, `latitude`, `longitude`, `icao`, `type`
   - *Validation:* 3-letter uppercase IATA code, 2-letter ISO country code, valid geographic coordinates, allowed airport types (`small_airport`, `medium_airport`, `large_airport`, `heliport`, `seaplane_base`, etc.).
2. **`aircrafts.csv`**: `identifier`, `manufacturer`, `model`, `year`, `capacity`, `range`
   - *Validation:* Positive integer capacity and range, valid registration identifier.
3. **`flights.csv`**: `flight id`, `departure`, `actual departure`, `arrival`, `actual arrival`, `gate`, `status`, `origin`, `destination`, `aircraft`, `airline`, `tracking url`
   - *Validation:* Valid status (`On Time`, `Delayed`, `Cancelled`), logical timestamp sequence (`actual_departure >= departure`, `arrival >= departure`), origin != destination, valid referenced aircraft and airport codes.
4. **`passengers.csv`**: `document number`, `first name`, `last name`, `dob`, `nationality`, `gender`, `email`, `phone`, `address`, `photo`
   - *Validation:* Valid email syntax (`user@domain`), document number, ISO date of birth, non-empty name and nationality.
5. **`reservations.csv`**: `reservation id`, `flight ids`, `document number`, `seat`, `price`, `extra luggage`, `priority boarding`, `qr code`
   - *Validation:* Valid price, seat identifier, passenger document reference, and referenced flight identifiers.

### Error Logging

When an input row fails any syntactic or semantic validation check, the raw offending line is written to `resultados/<dataset_name>_errors.csv` (preserving the original header), preventing corrupted state from entering memory.

---

## Dependencies & Prerequisites

- **Operating System:** Linux / POSIX-compliant environment
- **C Compiler:** `gcc` (version 9+ recommended) or `clang`
- **Build Tool:** GNU `make`
- **Libraries:**
  - **GLib 2.0** (`glib-2.0` and its development headers)
  - `pkg-config` (to resolve compiler and linker flags)

### Installing Dependencies

#### Ubuntu / Debian
```bash
sudo apt update
sudo apt install build-essential libglib2.0-dev pkg-config
```

#### Fedora / RHEL
```bash
sudo dnf install gcc make glib2-devel pkgconf-pkg-config
```

#### Arch Linux
```bash
sudo pacman -S base-devel glib2 pkgconf
```

---

## Compilation & Build

The build system is managed via the `Makefile` located in the `trabalho-pratico` directory.

1. Navigate to the project directory:
   ```bash
   cd 2526-G75/trabalho-pratico
   ```

2. Compile all targets:
   ```bash
   make
   ```
   This builds all three executables:
   - `programa-principal`
   - `programa-interativo`
   - `programa-testes`

3. Clean compiled binaries and temporary query outputs:
   ```bash
   make clean
   ```

### Compiler Flags

The build compiles with safety checks enabled:
```makefile
CFLAGS = -Werror=discarded-qualifiers -Wall -Wextra -g -DDEBUG `pkg-config --cflags glib-2.0`
```

---

## Usage & Execution Modes

Make sure your working directory is `2526-G75/trabalho-pratico` so the programs can find the `resultados/` output directory.

### 1. Batch Mode (`programa-principal`)

Runs a batch query script against a given dataset and produces individual output files for each query.

```bash
./programa-principal <path_to_csv_folder> <path_to_queries_file>
```

#### Example
```bash
./programa-principal dataset-fase-1/com_erros inputs_fase2.txt
```

#### Outputs
- Query outputs: `resultados/command1_output.txt`, `resultados/command2_output.txt`, ...
- Validation error logs: `resultados/airports_errors.csv`, `resultados/flights_errors.csv`, etc.

---

### 2. Interactive CLI Mode (`programa-interativo`)

Provides an interactive prompt to execute queries on demand with guided input prompts and input validation.

```bash
./programa-interativo
```

#### Workflow
1. The program prompts for the dataset directory (defaults to `dataset-fase-2/com_erros` if left blank).
2. Enter the query number (e.g. `1`, `2`, `2S`, `3`, `5`, `6`).
3. Provide the requested parameters as prompted.
4. Output is rendered directly to `stdout`.
5. Enter `r` or `reset` to reset, or `0`, `exit`, or `quit` to exit.

---

### 3. Testing & Benchmarking Mode (`programa-testes`)

Executes batch queries, automatically verifies the results against ground truth files, and prints a performance benchmark summary.

```bash
./programa-testes <path_to_csv_folder> <path_to_queries_file> <path_to_expected_results_folder>
```

#### Example
```bash
./programa-testes dataset-fase-1/com_erros inputs_fase2.txt resultados-esperados/res_fase2
```

#### Benchmark Output Includes
- Pass/Fail count for each query type ($Q_1$ through $Q_6$).
- Line-by-line mismatch discrepancy reporting.
- Memory usage snapshot (`ru_maxrss` in KB via `getrusage`).
- High-precision execution timings (`CLOCK_REALTIME`) for parsing and individual query execution.

---

## Repository Layout

```
.
├── 2526-G75/
│   ├── README.md                      # Repository documentation
│   └── trabalho-pratico/
│       ├── Makefile                   # Build automation configuration
│       ├── dataset-fase-1/            # Sample dataset (com_erros / sem_erros)
│       │   ├── com_erros/             # Datasets containing syntax/logical errors
│       │   └── sem_erros/             # Sanitized clean datasets
│       ├── include/                   # Header files (.h)
│       │   ├── entidades/             # Entity structures and interfaces
│       │   ├── gestores/              # In-memory managers and query headers
│       │   ├── io/                    # File stream and serialization headers
│       │   ├── parsing/               # CSV parsers
│       │   ├── utils/                 # Utilities (dates, parser helpers)
│       │   └── validacao/             # Validation logic headers
│       ├── src/                       # Source implementation files (.c)
│       │   ├── main.c                 # Batch mode entry point
│       │   ├── main_interativo.c      # Interactive CLI entry point
│       │   ├── main_testes.c          # Automated test & benchmark entry point
│       │   ├── entidades/             # Entity implementations
│       │   ├── gestores/              # Managers & query logic implementation
│       │   ├── io/                    # File I/O implementation
│       │   ├── parsing/               # CSV parser implementations
│       │   ├── utils/                 # Date/time & parser utility functions
│       │   └── validacao/             # Syntactic and logical validation
│       ├── inputs_fase2.txt           # Sample query input commands
│       ├── resultados/                # Generated query outputs & error logs
│       ├── resultados-esperados/      # Ground truth outputs for automated testing
│       └── realatorio-fase1.pdf       # Academic report (Phase 1)
```

---

## Performance & Memory Safety

- **Memory Management:** Memory allocation is paired with explicit deallocation functions (`*_free`). Managers utilize `GDestroyNotify` callbacks to ensure clean destruction of dynamically allocated hash table entries and lists.
- **Valgrind Compliance:** Designed to be free of memory leaks and invalid accesses when tested with Valgrind:
  ```bash
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
    ./programa-principal dataset-fase-1/sem_erros inputs_fase2.txt
  ```
- **Algorithmic Efficiency:**
  - Airport lookup ($Q_1$): $O(1)$ average time complexity via hash indexing.
  - Aircraft flight statistics ($Q_2$): $O(V + A \log A)$ pre-computed list sort.
  - Delay calculation ($Q_5$): $O(V)$ aggregation followed by $O(C \log C)$ airline sort.

---

## Authors

Developed by **Group 75** for **Laboratórios de Informática III (2025/2026)**:

| Name | Student Number | GitHub |
|---|---|---|
| **Afonso Manuel Almeida da Costa** | A110544 | [@afonso35costa](https://github.com/afonso35costa) |
| **André Brites de Almeida** | A112031 | [@a112031](https://github.com/a112031) |
| **Domingos Augusto da Silva Pimenta** | A109761 | [@domingos37](https://github.com/domingos37) |

**Universidade do Minho** — Licenciatura em Engenharia Informática (LEI)
