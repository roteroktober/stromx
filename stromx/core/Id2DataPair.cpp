/* 
 *  Copyright 2011 Matthias Fuchs
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "DataContainer.h"
#include "Exception.h"
#include "Id2DataPair.h"
#include "impl/Id2DataMap.h"

namespace stromx
{
    namespace core
    {      
        const bool Id2DataPair::trySet(const impl::Id2DataMap& id2DataMap) const
        {
            return id2DataMap[m_id].empty();   
        }
        
        const bool Id2DataPair::tryGet(const impl::Id2DataMap& id2DataMap) const
        {
            return ! id2DataMap[m_id].empty();
        }
        
        void Id2DataPair::get(core::impl::Id2DataMap& id2DataMap) const
        {
            if(! m_data.empty())
                throw WrongState("Data has already been assigned to this ID-data pair");
                
            if(id2DataMap[m_id].empty())
                throw WrongState("The requested output is empty");
            
            m_data = id2DataMap[m_id];
            id2DataMap[m_id] = DataContainer();
        }

        void Id2DataPair::set(core::impl::Id2DataMap& id2DataMap) const
        {
            if(m_data.empty())
                throw WrongState("This ID-data pair contains no data");
            
            if(! id2DataMap[m_id].empty())
                throw WrongState("Data has already been assigned to this input ID");
            
            id2DataMap[m_id] = m_data;
            m_data = DataContainer();
        }
    }
}
