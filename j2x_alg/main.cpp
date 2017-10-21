#include <cstdio>

#include "J2XTransformer.h"

#define BUFSIZE 8096

int main()
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
    buffer[nbytes + 1] = '\0';
    std::string result = transformer->transform(buffer);

    fprintf(stdout, result.c_str());
  }

  fclose(fp);
  delete transformer;
  return 1;
}