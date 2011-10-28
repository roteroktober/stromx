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

#include "Id2DataMap.h"
#include "../Exception.h"
#include "../DataContainer.h"

namespace stromx
{
    namespace core
    {
        namespace impl
        {
            Id2DataMap::Id2DataMap(const std::vector<const Description*> & descriptions)
            {
                for(std::vector<const Description*>::const_iterator iter = descriptions.begin();
                    iter != descriptions.end();
                    ++iter)
                {
                    if(m_map.count((*iter)->id()))
                        throw WrongArgument("Two descriptors with the same ID");
                    
                    m_map[(*iter)->id()] = DataContainer();
                }
            }
            
            Id2DataMap::Id2DataMap()
            {
            }
            
            core::DataContainer Id2DataMap::operator[](const unsigned int id) const
            {
                std::map<unsigned int, DataContainer>::const_iterator iter = m_map.find(id);
                if(iter == m_map.end())
                    throw WrongId("No data with ID " + id);
                
                return iter->second;
            }
            
            DataContainer & Id2DataMap::operator[](const unsigned int id)
            {
                std::map<unsigned int, DataContainer>::iterator iter = m_map.find(id);
                if(iter == m_map.end())
                    throw WrongId("No data with ID " + id);
                
                return iter->second;
            }
            
            void Id2DataMap::clear()
            {
                for(std::map<unsigned int, DataContainer>::iterator iter = m_map.begin();
                    iter != m_map.end();
                    ++iter)
                {
                    iter->second = DataContainer();
                }       
            }
            
            const bool Id2DataMap::isEmpty() const
            {
                bool value = true;
                for(std::map<unsigned int, DataContainer>::const_iterator iter = m_map.begin();
                    iter != m_map.end();
                    ++iter)
                {
                    if(! iter->second.empty())
                    {
                        value = false;
                        break;
                    }
                }   
                
                return value;
            }
        }
    }
}
