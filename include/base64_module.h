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

  char          * (*encode)(const unsigned char *string, size_t len);
  unsigned char * (*decode)(const char *encoded, size_t len);
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
  char          * (*encode)(const unsigned char *string, size_t len);
  unsigned char * (*decode)(const char *encoded, size_t len);
};


// private `private` module base64_decodesymbol
static char * base64_module_private_base64_decode(const unsigned char *string, size_t len) {
  log_trace("base64_module_private_base64_decode():%s/%d", string, len);
  return(b64_decode(string, len));
}


// private `private` module base64_encode symbol
static char * base64_module_private_base64_encode(const unsigned char *string, size_t len) {
  log_trace("base64_module_private_base64_encode():%s/%d", string, len);
  return(b64_encode(string, len));
}


// `private` module exports
exports(private) {
  defaults(private, CLIB_MODULE_DEFAULT),
  .encode = base64_module_private_base64_encode,
  .decode = base64_module_private_base64_decode,
};


static char * base64_module_decode(const unsigned char *string, size_t len) {
  log_trace("base64_module_private_base64_decode():%s/%d", string, len);
  return(require(private)->decode(string, len));
}


static char * base64_module_encode(const unsigned char *string, size_t len) {
  log_trace("base64_module_private_base64_encode():%s/%d", string, len);
  return(require(private)->encode(string, len));
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
  exports->encode  = base64_module_encode;
  exports->decode  = base64_module_decode;
  exports->private = require(private);
  debug_private();

  return(0);
}


// `base64_module` module deinitializer
static void base64_module_deinit(module(base64_module) *exports) {
  log_trace("base64_module_deinit()");
  clib_module_free((module(private) *) exports->private);
}

