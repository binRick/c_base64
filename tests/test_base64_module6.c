/*******************/
#define MODULE_LOG_LEVEL    LOG_TRACE
#define LOGGER              log_info
/*******************/
#include "base64_module.h"
#include "deps/trim/trim.c"
/*******************/
module(base64_module) * cm_base64;


/*******************/
char *cm_b64_enc(char *STRING){
  cm_base64->encode(STRING, strlen(STRING));
}


char *cm_b64_dec(char *STRING){
  cm_base64->decode(STRING, strlen(STRING));
}


/*******************/
int main(void) {
  log_set_level(MODULE_LOG_LEVEL);
  char *decoded_string = "Wed Mar", *encoded, *decoded;

  cm_base64 = require(base64_module);

  encoded = cm_b64_enc(decoded_string);
  decoded = cm_b64_dec(encoded);

  LOGGER("encoded %db string '%s' => %db string '%s'",
         strlen(decoded_string), decoded_string, strlen(encoded), encoded);
  LOGGER("decoded %db string '%s' => %db string '%s'",
         strlen(encoded), encoded, strlen(decoded), decoded);

  assert(strcmp(decoded, decoded_string) == 0);
  clib_module_free(cm_base64);

  return(0);
}
/*******************/

