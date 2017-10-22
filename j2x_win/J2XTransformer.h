#pragma once
#include "ITransformer.h"

#include <stack>


class J2XTransformer : public ITransformer
{
public:
  virtual const char* transform(const char* json);

private:
  int createXmlNode(const char* json, int index, size_t len);
  int createXmlValue(const char* json, int index, size_t len);

  void closeXmlValue();

private:
  std::string m_xml;

  std::stack<std::string> m_xmlTags;
};

