#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// Definición de niveles
#define LOG_LEVEL_NONE  0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_INFO  3

// Si no se define al compilar, por defecto mostramos hasta WARNINGS
#ifndef LOG_LEVEL
    #define LOG_LEVEL LOG_LEVEL_WARN
#endif

#define ANSI_RED    "\x1b[31m"
#define ANSI_YEL    "\x1b[33m"
#define ANSI_RESET  "\x1b[0m"

// Macros inteligentes: solo compilan el printf si el nivel es el adecuado
#define LOG_ERROR(msg, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_ERROR)  fprintf(stderr, ANSI_RED "[ERROR] " msg ANSI_RESET "\n", ##__VA_ARGS__)

#define LOG_WARN(msg, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_WARN)  fprintf(stdout, ANSI_YEL "[WARN]  " msg ANSI_RESET "\n", ##__VA_ARGS__)

#define LOG_INFO(msg, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_INFO)  fprintf(stdout, "[INFO]  " msg "\n", ##__VA_ARGS__)

#endif