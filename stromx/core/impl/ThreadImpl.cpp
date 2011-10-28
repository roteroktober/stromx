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

#include "ThreadImpl.h"

#include "../Exception.h"
#include "../OperatorInfo.h"

#include "InputNode.h"

#include <boost/bind.hpp>

namespace stromx
{
    namespace core
    {
        namespace impl
        {
            ThreadImpl::ThreadImpl()
            : m_thread(0),
                m_status(INACTIVE)
            {
            }
            
            ThreadImpl::~ThreadImpl()
            {
                stop();
            }
            
            void ThreadImpl::addNode(InputNode* const op)
            {
                if(m_status != INACTIVE)
                    throw WrongState("Thread must be inactive.");
                
                if(! op)
                    throw WrongArgument("Passed null as input node.");
                
                m_nodeSequence.push_back(op);
            }

            void ThreadImpl::insertNode(const unsigned int position, InputNode* const op)
            {
                if(m_status != INACTIVE)
                    throw WrongState("Thread must be inactive.");
                
                if(position > m_nodeSequence.size())
                    throw WrongArgument("Can only insert at an existing position of at the end of the node sequence.");
                
                m_nodeSequence.insert(m_nodeSequence.begin() + position, op);
            }

            void ThreadImpl::removeNode(const unsigned int position)
            {
                if(m_status != INACTIVE)
                    throw WrongState("Thread must be inactive.");
                
                if(position >= m_nodeSequence.size())
                    throw WrongArgument("No node at this position.");
                
                m_nodeSequence.erase(m_nodeSequence.begin() + position);
            }

            void ThreadImpl::start()
            {
                if(m_status != INACTIVE)
                    throw WrongState("Thread must be inactive.");
                
                BOOST_ASSERT(! m_thread);
                
                m_thread = new boost::thread(boost::bind(&ThreadImpl::loop, this));
                
                m_status = ACTIVE;
            }

            void ThreadImpl::stop()
            {
                if(m_status != ACTIVE)
                    return;
                
                BOOST_ASSERT(m_thread);
                
                m_thread->interrupt();
                
                m_status = DEACTIVATING;
            }

            void ThreadImpl::join()
            {
                if(m_status != DEACTIVATING)
                    throw WrongState("Thread must have been stopped.");
                
                BOOST_ASSERT(m_thread);
                
                m_thread->join();
                
                m_thread = 0;
                
                m_status = INACTIVE;
            }
            
            void ThreadImpl::loop()
            {
                try
                {      
                    while(true)
                    {
                        for(std::vector<InputNode*>::iterator node = m_nodeSequence.begin();
                                node != m_nodeSequence.end();
                                ++node)
                        {
                            (*node)->setInputData();
                            // TODO: handle exceptions in setInputData(), i.e. in OperatorKernel::execute()
                            
                            try
                            {
                                boost::this_thread::interruption_point();
                            }
                            catch(boost::thread_interrupted&)
                            {
                                throw Interrupt();
                            } 
                        }
                    }
                }
                catch(Interrupt&)
                {
                }
            }
        }
    }
}
