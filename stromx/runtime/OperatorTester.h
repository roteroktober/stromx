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

#ifndef STROMX_RUNTIME_OPERATORTESTER_H
#define STROMX_RUNTIME_OPERATORTESTER_H

#include "stromx/runtime/Operator.h"

namespace stromx
{
    namespace runtime
    {
        /** \brief %Operator with utility functions for unit testing. */
        class OperatorTester : public Operator
        {
        public:
            explicit OperatorTester(OperatorKernel* const kernel) 
            : Operator(kernel)
            {}
            
            void initialize() { Operator::initialize(); }
            void deinitialize()  { Operator::deinitialize(); }
            void activate() { Operator::activate(); }
            void deactivate()  { Operator::deactivate(); }
            void interrupt()  { Operator::interrupt(); }
        };
    }
}

#endif // STROMX_RUNTIME_OPERATORTESTER_H
