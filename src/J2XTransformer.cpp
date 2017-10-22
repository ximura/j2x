#include "J2XTransformer.h"

#include <ctype.h>
#include <algorithm>

int isInvalid(char c)
{
  return c == '[' || c == ']' || c == '{';
}

int isInvalidXmlNodeName(char c)
{
  return isspace(c) || c == '"';
}

const char* J2XTransformer::transform(const char* pJson)
{
  std::string json(pJson);

  json.erase(std::remove_if(json.begin(), json.end(), isInvalid), json.end());
  size_t len = json.length();

  size_t startIndex = 0;

  for (size_t i = 0; i < len; ++i)
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
    else if (c == ',' && json[i - 1] != '}')
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

void J2XTransformer::createXmlNode(const char* json, size_t startIndex, size_t endIndex)
{
  std::string xmlTag(&json[startIndex], &json[endIndex]);
  xmlTag.erase(std::remove_if(xmlTag.begin(), xmlTag.end(), isInvalidXmlNodeName), xmlTag.end());
  m_xmlTags.push(xmlTag);
  m_xml.append("<").append(xmlTag.c_str()).append(">");
}

void J2XTransformer::createXmlValue(const char* json, size_t startIndex, size_t endIndex)
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
