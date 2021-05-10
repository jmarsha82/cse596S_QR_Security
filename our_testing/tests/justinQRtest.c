
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <quirc.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <time.h>
#include "dbgutil.h"


extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t data_length)
{
  struct quirc *qr;

  qr = quirc_new();
  if (!qr) {
      perror("Failed to allocate memory");
  }
  if (quirc_resize(qr, 640, 480) < 0) {
      perror("Failed to allocate video memory");
  }
  uint8_t *image;
  int w, h;

  image = quirc_begin(qr, &w, &h);

/* Fill out the image buffer here.
* image is a pointer to a w*h bytes.
* One byte per pixel, w pixels per line, h lines in the buffer.
*/

  quirc_end(qr);

  int num_codes;
  int i;

  /* We've previously fed an image to the decoder via
  * quirc_begin/quirc_end.
  */

  num_codes = quirc_count(qr);
  for (i = 0; i < num_codes; i++) {
      struct quirc_code code;
      struct quirc_data data;
      quirc_decode_error_t err;

      quirc_extract(qr, i, &code);

      /* Decoding stage */
      err = quirc_decode(&code, &data);
      if (err)
          printf("DECODE FAILED: %s\n", quirc_strerror(err));
      else
          printf("Data: %s\n", data.payload);
  }
  quirc_destroy(qr);
  return 0;
}
