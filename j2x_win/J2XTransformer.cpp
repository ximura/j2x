#include "stdafx.h"

#include "J2XTransformer.h"

#include <ctype.h>
#include <algorithm>

int isInvalid(char c)
{
  return isspace(c) || c == '[' || c == ']' || c == '{' || c == '}';
}

const char* J2XTransformer::transform(const char* pJson)
{
  std::string json(pJson);

  json.erase(std::remove_if(json.begin(), json.end(), isInvalid), json.end());
  size_t len = json.length();

  for (int i = 0; i < len; ++i)
  {
    const char& c = json[i];

    if (c == '{')
    {
      i = createXmlNode(json.c_str(), i, len);
    }
    else if (c == ':')
    {
      i = createXmlValue(json.c_str(), i, len);
    }
    else if (c == ',')
    {
      closeXmlValue();
      i = createXmlNode(json.c_str(), i, len);
    }
    else if (c == '}')
    {
      closeXmlValue();
    }
  }

  return m_xml.c_str();
}

int J2XTransformer::createXmlNode(const char* json, int index, size_t len)
{
  int i = index;
  int startIndex = -1;
  // find start of xml node
  for (; i < len; ++i)
  {
    const char& c = json[i];
    if (c == '"')
    {
      startIndex = ++i;
      break;
    }
  }

  //find end of xml node
  for (; i < len; ++i)
  {
    const char& c = json[i];
    if (c == '"')
    {
      break;
    }
  }

  std::string xmlTag(&json[startIndex], &json[i]);
  m_xmlTags.push(xmlTag);
  m_xml.append("<").append(xmlTag.c_str()).append(">");

  return i;
}

int J2XTransformer::createXmlValue(const char * json, int index, size_t len)
{
  int i = index;
  int startIndex = -1;
  // find start of xml node
  for (; i < len; ++i)
  {
    const char& c = json[i];
    if (c == '{' || c == '[') //start of next node
    {
      return --i;
    }
    else  if (!isspace(c) && c != '"' && c != ':')
    {
      startIndex = i;
      break;
    }
  }

  //find end of xml node
  for (; i < len; ++i)
  {
    const char& c = json[i];
    if (isspace(c) || c == '"' || c== ',' || c == '}')
    {
      break;
    }
  }

  std::string xmlValue(&json[startIndex], &json[i]);
  m_xml.append(xmlValue);

  const char& c = json[i];
  if (c == ',' || c == '}')
  {
    --i;
  }

  return i;
}

void J2XTransformer::closeXmlValue()
{
  const std::string& xmlTag = m_xmlTags.top();

  m_xml.append("</").append(xmlTag.c_str()).append(">");

  m_xmlTags.pop();
}
