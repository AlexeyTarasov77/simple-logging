#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum { DEBUG, INFO, WARNING, ERROR } level_t;
typedef char *(*formatter_t)(level_t level, const char msg[]);

typedef struct {
  FILE *out;
  formatter_t formatter;
  level_t min_level;
} Logger;

Logger *create_logger(FILE *out, level_t min_level, formatter_t formatter);
void debug(Logger *logger, const char msg[]);
void info(Logger *logger, const char msg[]);
void warning(Logger *logger, const char msg[]);
void error(Logger *logger, const char msg[]);

#endif
