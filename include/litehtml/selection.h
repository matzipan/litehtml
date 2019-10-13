#ifndef LH_SELECTION_H
#define LH_SELECTION_H

#include <memory>
#include "element.h"

namespace litehtml
{
  
  class selection {
  protected:
    std::weak_ptr<litehtml::document>	  m_doc;
    std::shared_ptr<litehtml::element>	m_start_container;
    std::shared_ptr<litehtml::element>	m_end_container;
    unsigned int                        m_start_offset;
    unsigned int                        m_end_offset;
    bool                                m_active = false;

  public:
    typedef std::shared_ptr<litehtml::selection>	ptr;
    
    selection(
      const std::shared_ptr<litehtml::document>& doc,
      const std::shared_ptr<litehtml::element> &start_container,
      unsigned int start_offset,
      const std::shared_ptr<litehtml::element> &end_container,
      unsigned int end_offset,
      bool active
    );
    virtual ~selection() = default;
    
    bool update_end(const std::shared_ptr<litehtml::element>& new_end_container, const unsigned int end_offset);
    
    inline std::shared_ptr<document> get_document() const
    {
      return m_doc.lock();
    }
    
    inline std::shared_ptr<litehtml::element> get_start_container() const
    {
      return m_start_container;
    }
    
    inline std::shared_ptr<litehtml::element> get_end_container() const
    {
      return m_end_container;
    }
    
    inline unsigned int get_start_offset() const
    {
      return m_start_offset;
    }
    
    inline unsigned int get_end_offset() const
    {
      return m_end_offset;
    }
    
    inline bool is_active()
    {
      return m_active;
    }
    
    inline void set_active()
    {
      m_active = true;
    }
    
    inline void set_inactive()
    {
      m_active = false;
    }
    
    //@TODO return range
  };
}
#endif
