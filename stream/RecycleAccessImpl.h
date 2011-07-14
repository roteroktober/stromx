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

#ifndef STREAM_RECYCLEACCESSIMPL_H
#define STREAM_RECYCLEACCESSIMPL_H

#include "Recycler.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <set>
#include <deque>

namespace stream
{
    class Data;
    class DataContainer;
    class DataContainerImpl;
    
    class RecycleAccessImpl : public Recycler
    {
    public:
        RecycleAccessImpl(DataContainer& data);
        ~RecycleAccessImpl();    
        
        void recycle(DataContainerImpl* const container);
        Data* const operator()();
        Data* const operator()(const unsigned int timeout);
        void add(DataContainer& data);
        
    private:
        RecycleAccessImpl();
        
        typedef boost::lock_guard<boost::mutex> lock_t;
        typedef boost::unique_lock<boost::mutex> unique_lock_t;
        
        boost::mutex m_mutex;
        boost::condition_variable_any m_cond;

        std::deque<Data*> m_data;
        std::set<DataContainerImpl*> m_dataContainer;
    };
}

#endif // STREAM_RECYCLEACCESSIMPL_H
