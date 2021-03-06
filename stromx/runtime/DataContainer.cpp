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

#include "stromx/runtime/DataContainer.h"
#include "stromx/runtime/Recycler.h"
#include "stromx/runtime/impl/DataContainerImpl.h"

namespace stromx
{
    namespace runtime
    {
        DataContainer::DataContainer(Data* data)
          : m_impl(new impl::DataContainerImpl(data))
        {
        }
        
        bool operator==(const runtime::DataContainer& lhs, const runtime::DataContainer& rhs)
        {
            if(! lhs.m_impl.get() && ! rhs.m_impl.get())
                return true;
            
            if(! lhs.m_impl.get() || ! rhs.m_impl.get())
                return false;
            
            return lhs.m_impl->data() == rhs.m_impl->data();
        }
        
        bool operator!=(const runtime::DataContainer& lhs, const runtime::DataContainer& rhs)
        {
            return ! (lhs == rhs);
        }
        
        std::ostream& operator<<(std::ostream& out, const runtime::DataContainer& container)
        {
            if(! container.m_impl.get())
                out << 0;
            else
                out << container.m_impl->data();

            return out;
        }
    }
}