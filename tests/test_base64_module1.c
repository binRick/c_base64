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
  bool b0 = true, b1 = false;
  char *bs0 = cm_base64->bool_to_string(b0);
  char *bs1 = cm_base64->bool_to_string(b1);

  log_info(">cm_base64->bool_to_string(%d):%s", b0, bs0);
  log_info(">cm_base64->bool_to_string(%d):%s", b1, bs1);
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
