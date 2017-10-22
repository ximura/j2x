#pragma once
#include "ITransformer.h"

#include <map>
#include <string>

class TransformerManager
{
public:
  TransformerManager();
  ~TransformerManager();

  ITransformer* getTransformer(const char* name);

private:
  std::map<std::string, ITransformer*> m_transformers;
};

