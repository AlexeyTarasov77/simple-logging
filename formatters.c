#include "main.h"

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
  char *output = malloc(200);
  char level_s[10];
  level_to_str(level, level_s);
  sprintf(output, "%s%s: %s%s", colors[level], level_s, msg, COLOR_RESET);
  return output;
}

char *default_formatter(level_t level, const char msg[]) {
  struct tm *tm = localtime(&(time_t){time(NULL)});
  char curr_time[64];
  if (!strftime(curr_time, sizeof(curr_time), "%c", tm)) {
    puts("logger.default_formatter: Error setting curr_time");
    exit(1);
  }
  char *output = malloc(200);
  char level_s[10];
  level_to_str(level, level_s);
  sprintf(output, "%s(%s): %s", level_s, curr_time, msg);
  return output;
}
