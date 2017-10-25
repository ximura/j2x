#include "J2XTransformer.h"

#include <ctype.h>
#include <algorithm>

int isInvalid(char c)
{
  return c == '[' || c == '{';
}

int isInvalidXmlNodeName(char c)
{
  return isspace(c) || c == '"';
}

const char* J2XTransformer::transform(const char* pJson)
{
  std::string json(pJson);
  
  m_xml.clear();

  json.erase(std::remove_if(json.begin(), json.end(), isInvalid), json.end());
  size_t len = json.length();

  size_t startIndex = 0;
  size_t endIndex = 0;
  bool foundValue = false;

  bool wroteXmlValue = false;

  for (size_t i = 0; i < len; ++i)
  {
    const char& c = json[i];

    if (c == '"')
    {
      foundValue = !foundValue;
      if (foundValue)
      {
        startIndex = i;
      }
      else
      {
        endIndex = i;
      }
    }
    else if (!foundValue && c == ':')
    {
      createXmlNode(json.c_str(), startIndex, endIndex);
      startIndex = i + 1;
      wroteXmlValue = false;
    }
    else if (!foundValue && c == '}')
    {
      if (!wroteXmlValue)
      {
        if (endIndex < startIndex)
        {
          endIndex = i;
        }

        createXmlValue(json.c_str(), startIndex, endIndex);
        wroteXmlValue = true;
      }

      closeXmlNode();
    }
    else if (!foundValue && c == ']')
    {
      if (!wroteXmlValue)
      {
        if (endIndex < startIndex)
        {
          endIndex = i;
        }

        createXmlValue(json.c_str(), startIndex, endIndex);
        wroteXmlValue = true;
      }

      closeXmlNode();
    }
    else if (!foundValue && c == ',')
    {
      if (!wroteXmlValue)
      {
        if (endIndex < startIndex)
        {
          endIndex = i;
        }

        createXmlValue(json.c_str(), startIndex, endIndex);
        wroteXmlValue = true;
        closeXmlNode();
      }
    }
  }

  while (!m_xmlTags.empty())
  {
    closeXmlNode();
  }

  return m_xml.c_str();
}

void J2XTransformer::createXmlNode(const char* json, size_t startIndex, size_t endIndex)
{
  std::string xmlTag(&json[startIndex] + 1, &json[endIndex]);
  m_xmlTags.push(xmlTag);
  m_xml.append("<").append(xmlTag.c_str()).append(">");
}

void J2XTransformer::createXmlValue(const char* json, size_t startIndex, size_t endIndex)
{
  std::string xmlValue(&json[startIndex] + 1, &json[endIndex]);

  m_xml.append(xmlValue);
}

void J2XTransformer::closeXmlNode()
{
  if (m_xmlTags.empty())
  {
    return;
  }

  const std::string& xmlTag = m_xmlTags.top();

  m_xml.append("</").append(xmlTag.c_str()).append(">");

  m_xmlTags.pop();
}
