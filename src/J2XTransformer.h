#pragma once
#include "ITransformer.h"

#include <string>
#include <stack>


class J2XTransformer : public ITransformer
{
public:
  virtual const char* transform(const char* json);

private:
  void createXmlNode(const char* json, size_t index, size_t endIndex);
  void createXmlValue(const char* json, size_t index, size_t endIndex);

  void closeXmlNode();

private:
  std::string m_xml;

  std::stack<std::string> m_xmlTags;
};

