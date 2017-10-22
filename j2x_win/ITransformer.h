#pragma once

struct ITransformer
{
  virtual ~ITransformer() {}

  virtual const char* transform(const char*) = 0;
};
