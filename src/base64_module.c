/*******************/
#include <stdio.h>
/*******************/
#include "../deps/def.h"
#include "../deps/module.h"
#include "../deps/require.h"
/*******************/
#include "base64_module.h"
/*******************/
#include "log/log.c"
/*******************/
/*******************/

/*******************/
module(base64_module) * cm_base64;
/*******************/


/*******************/
void pre(void) {
  log_set_level(MODULE_LOG_LEVEL);
  cm_base64 = require(base64_module);
}


/*******************/
void test(void) {
}


/*******************/


/*******************/
void exec(void){
  log_info("base64 exec>");
}


/*******************/


/*******************/
void post(void) {
  log_debug("base64 unload>");
  clib_module_free(cm_base64);
}


/*******************/


/*******************/
