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

#ifndef STROM_IMPL_INPUTNODE_H
#define STROM_IMPL_INPUTNODE_H

namespace stromx
{
    namespace core
    {
        class DataContainer;
        class Operator;
        
        namespace impl
        {
            class OutputNode;
        
            class InputNode
            {
            public:
                InputNode(Operator* const op, const unsigned int inputId);
                
                const unsigned int inputId() const { return m_inputId; }
                Operator* const op() const { return m_operator; }
                const bool isConnected() const { return m_source != 0; }
                const OutputNode& source() const;
                void connect(OutputNode* const output);
                void disconnect();
                void setInputData();
                
            private:
                OutputNode *m_source;
                unsigned int m_inputId;
                Operator* m_operator;
            };
        }
    }
}

#endif // STROM_IMPL_INPUTNODE_H
