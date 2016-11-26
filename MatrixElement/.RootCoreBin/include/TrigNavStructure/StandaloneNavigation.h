// Emacs -*- c++ -*-
#ifndef TRIGNAVSTRUCTUE_STANDALONENAVIGATION_H
#define TRIGNAVSTRUCTUE_STANDALONENAVIGATION_H

#include <memory>
#include "TrigNavStructure/TrigNavStructure.h"

class ITrigHolderFactory;

namespace HLT{
  class StandaloneNavigation : public HLT::TrigNavStructure {
  public:
    StandaloneNavigation();
    virtual ~StandaloneNavigation();

    /**
     * @brief method serizlizes the helper objects allowing use of FeatureAccessHelpers w/o CLID
     * This methods should be owerwritten by the derived classes
     *
     * @param output vector to place the result
     *
     * @return if true then OK else some sort of failure happened (likely badly truncated structure)     
     */
    virtual bool serializeHolders( std::vector<uint32_t>& output ) const;
    virtual bool deserializeHolders(std::vector<uint32_t>::const_iterator& start,  const std::vector<uint32_t>::const_iterator& end);

    /**
     * @brief method serizlizes entire navigation
     *
     * @param output vector to place the result
     *
     * @return if true then OK else some sort of failure happened (likely badly truncated structure)
     */
    virtual bool serialize( std::vector<uint32_t>& output ) const;
    virtual bool deserialize( const std::vector<uint32_t>& input );


  private:
    ITrigHolderFactory* m_holderfactory;
  };
}//end of HLT namespace
#endif
