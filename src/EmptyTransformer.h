#pragma once
#include "ITransformer.h"

class EmptyTransformer : public ITransformer
{
public:
  virtual const char* transform(const char* text);
};

