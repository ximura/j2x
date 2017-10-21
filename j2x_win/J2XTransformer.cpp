#include "stdafx.h"

#include "J2XTransformer.h"
#include <string.h>
#include <algorithm>

const std::string J2XTransformer::transform(const char* json) const
{
  std::string result(json);
  
  result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
  result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
  result.erase(std::remove(result.begin(), result.end(), '\t'), result.end());
  result.erase(std::remove(result.begin(), result.end(), '"'), result.end());
  std::replace(result.begin(), result.end(), '{', '<');

  return result;
}
