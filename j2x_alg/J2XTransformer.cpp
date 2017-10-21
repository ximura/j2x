#include "J2XTransformer.h"
#include <string.h>

const std::string J2XTransformer::transform(const char* json) const
{
  std::string result(json);

  result.replace(result.begin(), result.end(), "\t", "");
  result.replace(result.begin(), result.end(), "\"", "");
  result.replace(result.begin(), result.end(), "{", "<");

  return result;
}
