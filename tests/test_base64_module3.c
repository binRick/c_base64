/*******************/
#define MODULE_TEST_ENABLED    false
#define MODULE_EXEC_ENABLED    false
#define MODULE_LOG_LEVEL       LOG_TRACE
/******************************/
#define DBG_H_DEF_ONCE
/******************************/
#include "base64_module.h"
/*******************/
#include "deps/c_dbg/dbg.h"
/*******************/
#include "log/log.c"
/*******************/
#include "deps/trim/trim.c"
/*******************/
module(base64_module) * cm_base64;


/*******************/
void pre(void) {
  cm_base64 = require(base64_module);
}
/*******************/
#define CM_B64_ENCODE_LEN    cm_base64->encode
#define CM_B64_DECODE_LEN    cm_base64->decode


/*******************/
char * CM_B64_ENCODE_STR(STRING){
  CM_B64_ENCODE_LEN(STRING, strlen(STRING));
}


char * CM_B64_DECODE_STR(STRING){
  CM_B64_DECODE_LEN(STRING, strlen(STRING));
}


/*******************/
void post(void) {
  log_debug("Base64 unload>");
  clib_module_free(cm_base64);
}


/*******************/
void module_test(){
  char *decoded_string = "Wed Mar 30 08:54:15 PM UTC 2022";
  char *encoded, *decoded;

  encoded = CM_B64_ENCODE_LEN(decoded_string, strlen(decoded_string));
  dbg(encoded, % s);
  log_info("encoded %db string '%s' => %db string '%s'", strlen(decoded_string), decoded_string, strlen(encoded), encoded);
  encoded = CM_B64_ENCODE_STR(decoded_string);
  log_info("encoded %db string '%s' => %db string '%s'", strlen(decoded_string), decoded_string, strlen(encoded), encoded);
  decoded = CM_B64_DECODE_LEN(encoded, strlen(encoded));
  dbg(decoded, % s);
  log_info("decoded %db string '%s' => %db string '%s'", strlen(encoded), encoded, strlen(decoded), decoded);
  decoded = CM_B64_DECODE_STR(encoded);
  log_info("decoded %db string '%s' => %db string '%s'", strlen(encoded), encoded, strlen(decoded), decoded);

  log_info("decoded strings OK");
  if (strcmp(decoded, decoded_string) == 0) {
  }else{
    log_fatal("failed to decode strings");
  }
}


/*******************/
void module_lifecycle(){
  pre();
  module_test();
  post();
}


int main(void) {
  log_set_level(MODULE_LOG_LEVEL);
  module_lifecycle();

  return(0);
}
/*******************/
