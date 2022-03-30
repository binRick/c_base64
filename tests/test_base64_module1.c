/*******************/
#define MODULE_TEST_ENABLED    false
#define MODULE_EXEC_ENABLED    false
#define MODULE_LOG_LEVEL       LOG_INFO
/*******************/
#include "include/module.h"
/*******************/
#include "log/log.c"
/*******************/
#include "src/base64_module.c"
/*******************/


void init(){
  log_set_level(MODULE_LOG_LEVEL);
}


void module_hook(){
  char *s = "abc";
  char *e = "V2VkIE1hciAzMCAwODo1MDoxMyBQTSBVVEMgMjAyMgo=";
  char *encoded, *decoded;

  encoded = cm_base64->encode(s, strlen(s));
  log_info("encoded %db string '%s' => %db string '%s'", strlen(s), s, strlen(encoded), encoded);
  decoded = cm_base64->decode(e, strlen(e));
  log_info("decoded %db string '%s' => %db string '%s'", strlen(e), e, strlen(decoded), decoded);
}


/*******************/
void module_lifecycle(){
  pre();
  if (MODULE_TEST_ENABLED) {
    test();
  }
  if (MODULE_EXEC_ENABLED) {
    exec();
  }
  module_hook();
  post();
}


int main(void) {
  init();
  module_lifecycle();
  return(0);
}
/*******************/
