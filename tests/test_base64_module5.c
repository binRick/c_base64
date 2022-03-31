/*******************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*******************/
#define MODULE_LOG_LEVEL    LOG_TRACE
#define LOGGER              log_info
#define MODULE_TYPE         base64_module
#define MODULE_NAME         cm_base64
/*******************/
#include "base64_module.h"
/*******************/
#include "deps/trim/trim.c"
/*******************/
typedef enum { 
    MOD_FXN_ENC = 0,
    MOD_FXN_DEC = 1,
} MOD_FXN_INDEXES;
/*******************/
/*******************/
module(MODULE_TYPE) * MODULE_NAME;
/*******************/
#define MODULE_REQUIRES               \
  MODULE_NAME = require(MODULE_TYPE); \
/*******************/
#define MODULE_EXPORTED_FUNCTIONS                                           \
  char *cm_b64_enc(STRING){ MODULE_NAME->encode(STRING, strlen(STRING)); }; \
  char *cm_b64_dec(STRING){ MODULE_NAME->decode(STRING, strlen(STRING)); };
/*******************/
#define MODULE_LOCAL_VARS                                                       \
  char *decoded_string = "Wed Mar 30 08:54:15 PM UTC 2022", *encoded, *decoded; \
/*******************/
typedef struct {
  unsigned int id;
  char         name[24];
  char         module_function_name[32];
  char* (*fn)(char *, int);
} __MOD_FXNS;
/*******************/
#define MODULE_RUN_FUNCTIONS                                                                                      \
  encoded = cm_b64_enc(decoded_string); LOGGER("encoded %db string '%s' => %db string '%s'",                      \
                                               strlen(decoded_string), decoded_string, strlen(encoded), encoded); \
  decoded = cm_b64_dec(encoded); LOGGER("decoded %db string '%s' => %db string '%s'",                             \
                                        strlen(encoded), encoded, strlen(decoded), decoded);                      \
  assert(strcmp(decoded, decoded_string) == 0);                                                                   \
/*******************/
MODULE_EXPORTED_FUNCTIONS
/*******************/
int main(void) {
  log_set_level(MODULE_LOG_LEVEL);
  MODULE_LOCAL_VARS
  MODULE_REQUIRES
  MODULE_RUN_FUNCTIONS
  clib_module_free(MODULE_NAME);

  return(0);
}
/*******************/

