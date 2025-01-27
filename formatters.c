#include "main.h"
#include <string.h>

#define RECORD_SIZE 200
#define DATETIME_SIZE 64

// COLORS
#define COLOR_GREY "\x1b[0;37m"   // -> DEBUG
#define COLOR_BLUE "\x1b[1;34m"   // -> INFO
#define COLOR_YELLOW "\x1b[1;33m" // -> WARNING
#define COLOR_RED "\x1b[1;31m"    // -> ERROR
#define COLOR_RESET "\x1b[0m"

const char *colors[4] = {COLOR_GREY, COLOR_BLUE, COLOR_YELLOW, COLOR_RED};

static void level_to_str(level_t level, char buf[10]) {
  switch (level) {
  case DEBUG:
    strcpy(buf, "DEBUG");
    break;
  case INFO:
    strcpy(buf, "INFO");
    break;
  case WARNING:
    strcpy(buf, "WARNING");
    break;
  case ERROR:
    strcpy(buf, "ERROR");
    break;
  default:
    puts("logger.default_formatter: got invalid level");
    exit(1);
  }
}

char *colorized_formatter(level_t level, const char msg[]) {
  if (level >= sizeof(colors)) {
    printf("colorized_formatter: unknown level: %d\n", level);
    exit(1);
  }
  char *output = malloc(RECORD_SIZE);
  char level_s[10];
  level_to_str(level, level_s);
  sprintf(output, "%s%s: %s%s", colors[level], level_s, msg, COLOR_RESET);
  return output;
}

static void parse_curr_time(char buf[DATETIME_SIZE]) {
  struct tm *tm = localtime(&(time_t){time(NULL)});
  if (!strftime(buf, DATETIME_SIZE, "%c", tm)) {
    puts("Failed to parse curr time");
    exit(1);
  }
}

static char *base_formatter(level_t level, const char msg[], char *format) {
  char *output = malloc(RECORD_SIZE);
  char curr_time[DATETIME_SIZE];
  parse_curr_time(curr_time);
  char level_s[10];
  level_to_str(level, level_s);
  sprintf(output, format, level_s, curr_time, msg);
  return output;
}

char *default_formatter(level_t level, const char msg[]) {
  return base_formatter(level, msg, "%s(%s): %s");
}

char *json_formatter(level_t level, const char msg[]) {
  return base_formatter(level, msg, "{\"%s(%s)\": \"%s\"}");
}
