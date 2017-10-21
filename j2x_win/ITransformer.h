#pragma once

#include <string>

struct ITransformer
{
  virtual ~ITransformer() {}

  virtual const std::string transform(const char*) const = 0;
};
