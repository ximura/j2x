#include <cstdio>

#include "J2XTransformer.h"

#define BUFSIZE 8096

int __main()
{
  FILE   *fp;
  long    nbytes;
  char buffer[BUFSIZE + 1];

  if ((fp = fopen("test.json", "rb")) == NULL)
  {
    printf("Error");
    return -1;
  }

  ITransformer* transformer = new J2XTransformer();

  while ((nbytes = fread(buffer, 1, BUFSIZE, fp)) > 0)
  {
    buffer[nbytes] = '\0';
    const char* result = transformer->transform(buffer);

    printf(result);
  }

  fclose(fp);
  delete transformer;
  return 1;
}

