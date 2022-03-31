/*******************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*******************/
#define MODULE_LOG_LEVEL    LOG_TRACE
#define LOGGER              log_info
#define MODULE_TYPE         base64_module
/*******************/
#include "base64_module.h"
#include "deps/trim/trim.c"
/*******************/
module(MODULE_TYPE) * cm_base64;
/*******************/
#define MODULE_REQUIRES             \
  cm_base64 = require(MODULE_TYPE); \
/*******************/
#define MODULE_EXPORTED_FUNCTIONS                                         \
  char *cm_b64_enc(STRING){ cm_base64->encode(STRING, strlen(STRING)); }; \
  char *cm_b64_dec(STRING){ cm_base64->decode(STRING, strlen(STRING)); };
/*******************/
#define MODULE_LOCAL_VARS                               \
  char *decoded_string = "Wed Mar", *encoded, *decoded; \
/*******************/
typedef struct {
  unsigned int id;
  char         name[24];
  char         module_function_name[32];
  char * (*fn)(char *, int);
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
  clib_module_free(cm_base64);

  return(0);
}
/*******************/

