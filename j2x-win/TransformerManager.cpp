#include "TransformerManager.h"

#include "J2XTransformer.h"
#include "EmptyTransformer.h"


TransformerManager::TransformerManager()
{
  m_transformers.insert(std::pair<std::string, ITransformer*>("text/json", new J2XTransformer()));
  m_transformers.insert(std::pair<std::string, ITransformer*>("empty", new EmptyTransformer()));
}


TransformerManager::~TransformerManager()
{
  for (std::map<std::string, ITransformer*>::iterator it = m_transformers.begin(); it != m_transformers.end(); ++it)
  {
    ITransformer* transformer = it->second;
    delete transformer;
  }
}

ITransformer* TransformerManager::getTransformer(const char* name)
{
  std::map<std::string, ITransformer*>::const_iterator it = m_transformers.find(name);

  return it != m_transformers.end() ? it->second : m_transformers.find("empty")->second;
}
