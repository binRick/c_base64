#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE64_VERBOSE_MODE    true

int c_get_bool(const char *string, bool *value);

char * c_bool_to_str(bool b);

bool c_is_bool(const char *s);

bool c_str_to_bool(const char *s);
