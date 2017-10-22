#include "stdafx.h"

#include "J2XTransformer.h"

#include <algorithm>
#include <ctype.h>

const char* J2XTransformer::transform(const char* json)
{
  size_t len = strlen(json);

  m_xml.clear();
  m_xml.reserve(len);

  int tagStartIndex = -1;
  for (int i = 0; i < len; ++i)
  {
    const char& c = json[i];

    if (isspace(c) || c == '\"') // skip whitespaces and " symbol
    {
      continue;
    }
    else if (c == '{') // tag start
    {
      tagStartIndex = i + 2;
    }
    else if (c == ':') // tag value start
    {
      std::string xmlTag(&json[tagStartIndex], &json[i - 1]);
      xmlTag.erase(remove_if(xmlTag.begin(), xmlTag.end(), isspace), xmlTag.end());
      m_xmlTags.push(xmlTag);
      tagStartIndex = -1;

      m_xml.append("<").append(xmlTag.c_str()).append(">");
    }
    else if (c == ',' || c == '}') // close tag
    {
      tagStartIndex = i + 1;
      const std::string& xmlTag= m_xmlTags.top();

      m_xml.append("</").append(xmlTag.c_str()).append(">");

      m_xmlTags.pop();
    }
    else if (tagStartIndex == -1) // tag value
    {
      m_xml.append(1, c);
    }
  }


  return m_xml.c_str();
}
