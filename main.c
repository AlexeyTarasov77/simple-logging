#include "main.h"
#include "formatters.h"
#include <errno.h>
#include <stdarg.h>
#define LOG(level)                                                             \
  va_list args;                                                                \
  va_start(args, format);                                                      \
  log_msg(logger, level, format, args);                                        \
  va_end(args);

Logger *create_logger(FILE *out, level_t min_level, formatter_t formatter) {
  if (out == NULL) {
    out = stdout;
  }
  if (formatter == NULL) {
    formatter = default_formatter;
  }
  Logger *logger = malloc(sizeof(Logger));
  logger->out = out;
  logger->min_level = min_level;
  logger->formatter = formatter;
  return logger;
}

static void log_msg(Logger *logger, level_t level, const char format[],
                    va_list args) {
  if (level < logger->min_level) {
    return;
  }
  char *record = logger->formatter(level, format);
  vsprintf(record, format, args);
  fprintf(logger->out, "%s\n", record);
  free(record);
}

void debug(Logger *logger, const char format[], ...) { LOG(DEBUG); }

void info(Logger *logger, const char format[], ...) { LOG(INFO); }
void warning(Logger *logger, const char format[], ...) { LOG(WARNING); }
void error(Logger *logger, const char format[], ...) { LOG(ERROR); }

int main() {
  FILE *log_file = fopen("logs.json", "a");
  if (log_file == NULL) {
    if (errno == ENOENT) {
    }
    perror("logs.json");
    return 1;
  }
  Logger *logger = create_logger(NULL, DEBUG, json_formatter);
  debug(logger, "Debug log %s", "embedded");
  info(logger, "Info log");
  warning(logger, "Warning log");
  error(logger, "Error log");
}
