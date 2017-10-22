#include "stdafx.h"

#include "J2XTransformer.h"

#include <ctype.h>
#include <algorithm>

int isInvalid(char c)
{
  return isspace(c) || c == '[' || c == ']' || c == '{' || c == '"';
}

const char* J2XTransformer::transform(const char* pJson)
{
  std::string json(pJson);

  json.erase(std::remove_if(json.begin(), json.end(), isInvalid), json.end());
  size_t len = json.length();

  int startIndex = 0;

  for (int i = 0; i < len; ++i)
  {
    const char& c = json[i];

    if (c == ':')
    {
      createXmlNode(json.c_str(), startIndex, i);
      startIndex = i + 1;
    }
    else if (c == '}')
    {
      createXmlValue(json.c_str(), startIndex, i);
      startIndex = i + 1;
      closeXmlNode();
    }
    else if ( c == ',' && json[i-1] != '}')
    {
      createXmlValue(json.c_str(), startIndex, i);
      closeXmlNode();
    }

    if (c == ',')
    {
      startIndex = i + 1;
    }
  }

  return m_xml.c_str();
}

void J2XTransformer::createXmlNode(const char* json, int startIndex, int endIndex)
{
  std::string xmlTag(&json[startIndex], &json[endIndex]);
  m_xmlTags.push(xmlTag);
  m_xml.append("<").append(xmlTag.c_str()).append(">");
}

void J2XTransformer::createXmlValue(const char* json, int startIndex, int endIndex)
{
  std::string xmlValue(&json[startIndex], &json[endIndex]);
  m_xml.append(xmlValue);
}

void J2XTransformer::closeXmlNode()
{
  const std::string& xmlTag = m_xmlTags.top();

  m_xml.append("</").append(xmlTag.c_str()).append(">");

  m_xmlTags.pop();
}
