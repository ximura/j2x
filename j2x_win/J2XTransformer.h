#pragma once
#include "ITransformer.h"

#include <stack>


class J2XTransformer : public ITransformer
{
public:
  virtual const char* transform(const char*);
private:
  std::string m_xml;

  std::stack<std::string> m_xmlTags;
};

