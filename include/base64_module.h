/***********************************/
#include <stdio.h>
/***********************************/
#include "../deps/def.h"
/***********************************/
#include "log/log.h"
/***********************************/
#include "../deps/module.h"
/***********************************/
#include "../deps/require.h"
/***********************************/
#ifndef MODULE_LOG_LEVEL
#define MODULE_LOG_LEVEL    LOG_DEBUG
#endif
/***********************************/

// `base64_module` module definition
module(base64_module) {
  defaults(base64_module, CLIB_MODULE);
  void *private;

  bool (*string_to_bool)(const char *);
  bool (*is_base64)(const char *);
  char * (*bool_to_string)(const base64);
};

// `base64_module` module prototypes
static int  base64_module_init(module(base64_module) * exports);

static void base64_module_deinit(module(base64_module) * exports);

// `base64_module` module exports
exports(base64_module) {
  .init   = base64_module_init,
  .deinit = base64_module_deinit,
};

// `private` module definition
module(private) {
  define(private, CLIB_MODULE);
  bool (*string_to_bool)(const char *);
  bool (*is_base64)(const char *);
  char * (*bool_to_string)(const base64);
};


// private `private` module bool_to_string symbol
static char * base64_module_private_bool_to_string(const bool b) {
  log_trace("base64_module_private_bool_to_string():%d", b);
  return(c_bool_to_str(b));
}


static bool base64_module_private_is_base64(const char *s) {
  log_trace("base64_module_is_base64():%s", s);
  return(c_is_bool(s));
}


static bool base64_module_private_string_to_bool(const char *s) {
  log_trace("base64_module_private_string_to_string():%s", s);
  return(c_str_to_bool(s));
}



// `private` module exports
exports(private) {
  defaults(private, CLIB_MODULE_DEFAULT),
  .bool_to_string = base64_module_private_bool_to_string,
  .string_to_bool = base64_module_private_string_to_bool,
};


static bool base64_module_is_base64(const char *s) {
  log_trace("base64_module_is_base64(%s)", s);
  return(require(private)->is_base64(s));
}


static bool base64_module_string_to_bool(const char *s) {
  log_trace("base64_module_string_to_bool(%s)", s);
  return(require(private)->string_to_bool(s));
}


// private `base64_module` module bool_to_string symbol
static char * base64_module_bool_to_string(const bool b) {
  log_trace("base64_module_bool_to_string()");
  return(require(private)->bool_to_string(b));
}



// `base64_module` module initializer
static int base64_module_init(module(base64_module) *exports) {
  void debug_private(){
    if (0 != exports->private) {
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_YELLOW "init> NON PRIVATE MODE" AC_RESETALL);
    }else{
      log_info(AC_RESETALL AC_BOLD AC_REVERSED AC_BLUE "init> PRIVATE MODE" AC_RESETALL);
    }
  }

  debug_private();
  exports->bool_to_string = base64_module_bool_to_string;
  exports->string_to_bool = base64_module_string_to_bool;
  exports->is_base64        = base64_module_is_base64;
  exports->private        = require(private);
  debug_private();

  return(0);
}


// `base64_module` module deinitializer
static void base64_module_deinit(module(base64_module) *exports) {
  log_trace("base64_module_deinit()");
  clib_module_free((module(private) *) exports->private);
}

