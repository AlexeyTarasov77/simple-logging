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

char *default_formatter(level_t level, const char msg[]) {
  struct tm *tm = localtime(&(time_t){time(NULL)});
  char curr_time[64];
  if (!strftime(curr_time, sizeof(curr_time), "%c", tm)) {
    puts("logger.default_formatter: Error setting curr_time");
    exit(1);
  }
  char *output = malloc(200);
  char level_s[10];
  switch (level) {
  case DEBUG:
    strcpy(level_s, "DEBUG");
    break;
  case INFO:
    strcpy(level_s, "INFO");
    break;
  case WARNING:
    strcpy(level_s, "WARNING");
    break;
  case ERROR:
    strcpy(level_s, "ERROR");
    break;
  default:
    puts("logger.default_formatter: got invalid level");
    exit(1);
  }
  sprintf(output, "%s(%s): %s", level_s, curr_time, msg);
  return output;
}

Logger *create_logger(FILE *out, level_t min_level, formatter_t formatter) {
  if (out == NULL) {
    out = stdout;
  }
  if (formatter == NULL) {
    formatter = default_formatter;
  }
  Logger *logger = malloc(sizeof(Logger));
  logger->out = out;
  logger->formatter = formatter;
  return logger;
}

static void log_msg(Logger *logger, level_t level, const char msg[]) {
  if (level >= logger->min_level) {
    char *record = logger->formatter(level, msg);
    puts(record);
    free(record);
  }
}

void debug(Logger *logger, const char msg[]) { log_msg(logger, DEBUG, msg); }
void info(Logger *logger, const char msg[]) { log_msg(logger, INFO, msg); }
void warning(Logger *logger, const char msg[]) {
  log_msg(logger, WARNING, msg);
}
void error(Logger *logger, const char msg[]) { log_msg(logger, ERROR, msg); }

int main() {
  Logger *logger = create_logger(NULL, DEBUG, NULL);
  debug(logger, "Debug log");
  warning(logger, "It's a warning");
}
