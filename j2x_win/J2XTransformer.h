#pragma once
#include "ITransformer.h"

class J2XTransformer : public ITransformer
{
public:
  virtual const std::string transform(const char*) const;
};

