#ifndef FORMATTERS_H
#define FORMATTERS_H
#include "main.h"

char *colorized_formatter(level_t level, const char msg[]);
char *default_formatter(level_t level, const char msg[]);
char *json_formatter(level_t level, const char msg[]);

#endif
