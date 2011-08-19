/* 
*  Copyright 2011 Thomas Fidler
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

#ifndef STREAM_REGISTRY_H
#define STREAM_REGISTRY_H

namespace stream
{
    class OperatorKernel;
    class Data;
    
    class Registry
    {
    public:
        virtual void registerOperator(const OperatorKernel* const op) = 0;
        
        virtual void registerData(const Data* const data) = 0;
    };
}

#endif // STREAM_REGISTRY_H
