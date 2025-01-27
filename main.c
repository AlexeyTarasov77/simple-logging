#include "main.h"
#include "formatters.h"

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

static void log_msg(Logger *logger, level_t level, const char msg[]) {
  if (level >= logger->min_level) {
    char *record = logger->formatter(level, msg);
    fprintf(logger->out, "%s\n", record);
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
  /* FILE *log_file = fopen("logs.json", "a"); */
  /* if (log_file == NULL) { */
  /*   perror("logs.json"); */
  /*   return 1; */
  /* } */
  Logger *logger = create_logger(NULL, DEBUG, colorized_formatter);
  debug(logger, "Debug log");
  info(logger, "Info log");
  warning(logger, "Warning log");
  error(logger, "Error log");
}
