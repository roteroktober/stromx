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

#ifndef STROMX_RUNTIME_OPERATORKERNEL_H
#define STROMX_RUNTIME_OPERATORKERNEL_H

#include <map>
#include <set>
#include "stromx/runtime/DataRef.h"
#include "stromx/runtime/Exception.h"
#include "stromx/runtime/OperatorInfo.h"

namespace stromx
{
    namespace runtime
    {
        class DataContainer;
        class DataProvider;
        
        namespace impl
        {
            class SynchronizedOperatorKernel;
        }
        
        /**
         * \brief Abstract operator kernel.
         * 
         * An operator kernel implements an operator in its raw form, i.e. without
         * the infrastructure code which is necessary to be a node in a stream network.
         * It is never directly used in a stream but serves as a base class for the 
         * implementation of custom operators. 
         */
        class STROMX_RUNTIME_API OperatorKernel : public OperatorInfo
        {
            friend class impl::SynchronizedOperatorKernel;
            friend class OperatorKernelTest;
            
        public:
            virtual ~OperatorKernel();
            
            /**
             * Returns a copy of the operator, i.e. a object of the same type is
             * allocated and returned. The current status of the operator is \em not
             * reproduced.
             */
            virtual OperatorKernel* clone() const = 0;
            
            const std::string& type() const { return m_type; }
            
            const std::string& package() const { return m_package; }
            
            const Version& version() const { return m_version; }

            const std::vector<const Description*>& inputs() const { return m_inputs; }
            
            const std::vector<const Description*>& outputs() const { return m_outputs; }
            
            const std::vector<const Parameter*>& parameters() const { return m_parameters; }
            
            const Parameter & parameter(const unsigned int id) const;
            
            virtual const Description & input(const unsigned int id) const;
            
            virtual const Description & output(const unsigned int id) const;
            
            const OperatorProperties & properties() const;
            
            /** Sets a parameter \c id to \c value. */
            virtual void setParameter(const unsigned int, const Data&) { throw NotImplemented(); };
            
            /** Gets the current value of the parameter \c id. */
            virtual const DataRef getParameter(const unsigned int) const { throw NotImplemented(); };
            
            /**
             * Executes the operator.
             * \param provider Provides the input data for the execution and accepts its results.
             */
            virtual void execute(DataProvider& provider) = 0;
            
            /** 
             * Initializes the operator. After initialization the operator kernel must
             * be prepared to accept calls to activate().
             */
            virtual void initialize() {}
            
            /**
             * Deinitializes the operator. Must be called from
             * any overloads of this function in derived classes.
             */
            virtual void deinitialize();

            /** 
             * Activates the operator. After activation the operator kernel must
             * be prepared to accept calls to execute().
             */
            virtual void activate() {}

            /** 
             * Deactivates the operator, i.e. returns its state to the same as before
             * activation.
             */
            virtual void deactivate() {}

            /** 
             * Interrupts an executing operator, i.e. the operator stops its 
             * execution as soon as possible. The function has no effect if the
             * operator is not currently executing. Note that this function can be called
             * from a thread different than the executing thread at any time.
             */
            virtual void interrupt() {}
            
            
        protected:
            /**
             * Constructs an operator kernel.
             * 
             * \param parameters A list of parameter descriptions. The descriptions will
             *                   be owned by the parent class, i.e. they must not be 
             *                   manually deleted. The list must contain descriptions of
             *                   all operator parameters which
             *                   can be edited before initialization. It can contain the 
             *                   description of parameters which can be edited only
             *                   after initialization.
             * 
             * \param properties Optionally, the properties of this operator.
             */
            OperatorKernel(const std::string & type,
                    const std::string & package,
                    const Version & version,
                    const std::vector<const Parameter*>& parameters,
                    const OperatorProperties & properties = OperatorProperties());
                
            /**
             * Constructs an operator kernel.
             * 
             * \param inputs A list of operator input descriptions. The descriptions will
             *               be owned by the parent class, i.e. they must not be 
             *               manually deleted.
             * 
             * \param outputs A list of operator input descriptions. The descriptions will
             *                be owned by the parent class, i.e. they must not be 
             *                manually deleted.
             * 
             * \param parameters A list of parameter descriptions. The descriptions will
             *                   be owned by the parent class, i.e. they must not be 
             *                   manually deleted. The list must contain descriptions of
             *                   all operator parameters which
             *                   can be edited before initialization. It can contain the 
             *                   description of parameters which can be edited only
             *                   after initialization.
             * 
             * \param properties Optionally, the properties of this operator.
             */    
            OperatorKernel(const std::string & type,
                    const std::string & package,
                    const Version & version,
                    const std::vector<const Description*>& inputs,
                    const std::vector<const Description*>& outputs,
                    const std::vector<const Parameter*>& parameters,
                    const OperatorProperties & properties = OperatorProperties());

	    /**
             * Constructs an operator kernel.
             * 
             * \param inputs A list of operator input descriptions. The descriptions will
             *               be owned by the parent class, i.e. they must not be 
             *               manually deleted.
             * 
             * \param outputs A list of operator input descriptions. The descriptions will
             *                be owned by the parent class, i.e. they must not be 
             *                manually deleted.
             * 
             * \param properties Optionally, the properties of this operator.
             */  
            OperatorKernel(const std::string& type,
                    const std::string& package,
                    const runtime::Version& version,
                    const std::vector<const Description* >& inputs,
                    const std::vector<const Description* >& outputs,
                    const OperatorProperties & properties = OperatorProperties());
             
            /**
             * Constructs an operator kernel.
             * 
             * \param properties Optionally, the properties of this operator.
             */       
            OperatorKernel(const std::string & type,
                    const std::string & package,
                    const Version & version,
                    const OperatorProperties & properties = OperatorProperties());
            
            /**
             * Initializes an operator kernel. Must only be called from
             * OperatorKernel::initialize() and overloads of this function
             * in derived classes.
             * 
             * \param inputs A list of operator input descriptions. The descriptions will
             *               be owned by the parent class, i.e. they must not be 
             *               manually deleted.
             * 
             * \param outputs A list of operator input descriptions. The descriptions will
             *                be owned by the parent class, i.e. they must not be 
             *                manually deleted.
             * 
             * \param parameters A list of parameter descriptions. The descriptions will
             *                   be owned by the parent class, i.e. they must not be 
             *                   manually deleted. Note that adding parameters which 
             *                   should be edited before initialization at this stage does
             *                   not make any sense but should be done in the constructor.
             */
            virtual void initialize(const std::vector<const Description*>& inputs,
                                    const std::vector<const Description*>& outputs,
                                    const std::vector<const Parameter*>& parameters);
            
            /**
             * Returns the parameter \c id.
             */
            Parameter & parameter(const unsigned int id);
            
        private:
            void validateInputs(const std::vector<const Description*>& descriptors);
            void validateOutputs(const std::vector<const Description*>& descriptors);
            void validateParameters(const std::vector<const Parameter*>& descriptors);
            const Parameter & findParameter(const unsigned int id) const;
            
            std::string m_type;
            std::string m_package;
            Version m_version;
            std::vector<const Description*> m_inputs;
            std::vector<const Description*> m_outputs;
            std::vector<const Parameter*> m_parameters;
            
            std::map<unsigned int, const Parameter*> m_parameterMap;
            std::map<unsigned int, const Description*> m_inputMap;
            std::map<unsigned int, const Description*> m_outputMap;
            
            // the indices of all inputs, output and parameters which are
            // have been during initialization, i.e. which must be removed
            // upon deinitialization
            std::set<unsigned int> m_activeInputs;
            std::set<unsigned int> m_activeOutputs;
            std::set<unsigned int> m_activeParameters;
            
            OperatorProperties m_properties;
        };
    }
}

#endif // STROMX_RUNTIME_OPERATORKERNEL_H
