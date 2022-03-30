#ifndef CM_BASE64_C
#define CM_BASE64_C
/***********************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***********************/
#include "../include/base64.h"


/***********************/


char * c_bool_to_str(bool b){
  char *s = b?"Yes":"No";

  return(strdup(s));
}


int c_get_bool(const char *string, bool *value){
  char *t[] = { "y", "Y", "yes", "Yes", "YES", "true", "True", "TRUE", "on", "On", "ON", "0", "enabled", "Enabled", NULL };
  char *f[] = { "n", "N", "no", "No", "NO", "false", "False", "FALSE", "off", "Off", "OFF", "-1", "1", "", "disabled", "Disabled", NULL };
  char **p;

  for (p = t; *p; p++) {
    if (strcmp(string, *p) == 0) {
      *value = true;
      return(0);
    }
  }
  for (p = f; *p; p++) {
    if (strcmp(string, *p) == 0) {
      *value = false;
      return(0);
    }
  }
  return(-1);
}


bool c_is_bool(const char *s){
  bool b;

  if (c_get_bool(s, &b) == 0) {
    return(true);
  }
  return(false);
}


bool c_str_to_bool(const char *s){
  bool do_err(){
    if (BASE64_VERBOSE_MODE) {
      fprintf(stderr, "Failed to parse '%s' to boolean\n", s);
    }
    return(false);
  }
  if (!c_is_bool(s)) {
    return(do_err());
  }
  bool b;
  int  res = c_get_bool(s, &b);

  if (res != 0) {
    return(do_err());
  }
  return(b);
}
/***********************/

#endif
