#include "html.h"
#include "selection.h"

litehtml::selection::selection(
  const std::shared_ptr<litehtml::document>& doc,
  const std::shared_ptr<litehtml::element> &start_container,
  unsigned int start_offset,
  const std::shared_ptr<litehtml::element> &end_container,
  unsigned int end_offset,
  bool active
) : m_doc(doc), m_start_container(start_container),
  m_end_container(end_container), m_start_offset(start_offset),
  m_end_offset(end_offset),
  m_active(active)
{
}

bool litehtml::selection::update_end(
  const std::shared_ptr<litehtml::element>& new_end_container,
  const unsigned int new_end_offset)
{
  
  
  bool end_changed = (m_end_container != new_end_container) || (m_end_offset != new_end_offset);
  
  m_end_container = new_end_container;
  m_end_offset = new_end_offset;
  
  
  return end_changed;
}
