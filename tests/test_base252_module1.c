/*******************/
#define MODULE_LOG_LEVEL    LOG_TRACE
#define LOGGER              log_info
/*******************/
#include "../deps/base252/base252.c"
#include "../deps/trim/trim.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SKIP_LIST_C
#include "../../log/log.c"
/*******************/


/*******************/
void b252_test(){
  char input[BUFFER_SIZE], output[BUFFER_SIZE];
  int  size;
  char *orig = "THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.";

  strcpy(input, orig);

  strcpy(output, "");

  size = data_to_base252(input, strlen(input), output, BUFFER_SIZE);

  printf("input is:\n\n%s\n(%d) \n\noutput is:\n\n%s\n\n", input, strlen(input), output);

  memcpy(input, output, size + 1);

  strcpy(output, "");
  LOGGER("encoded %db string '%s' => %db string '%s'",
         strlen(input), input, strlen(output), output);

  base252_to_data(input, size, output, BUFFER_SIZE);

  printf("input is:\n\n%s\n(%d)\n\noutput is:\n\n%s\n\n", input, size, output);
  LOGGER("decoded %db string '%s' => %db string '%s'",
         strlen(input), input, strlen(output), output);

  assert(strcmp(output, orig) == 0);
}


/*******************/
int main(void) {
  log_set_level(MODULE_LOG_LEVEL);
  b252_test();

  return(0);
}
/*******************/

