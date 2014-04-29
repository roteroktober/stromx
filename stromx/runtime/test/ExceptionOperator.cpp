/* 
*  Copyright 2014 Matthias Fuchs
*
*  This file is part of stromx-studio.
*
*  Stromx-studio is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  Stromx-studio is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with stromx-studio.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stromx/runtime/test/ExceptionOperator.h"

#include <boost/thread.hpp>
#include "stromx/runtime/DataProvider.h"
#include "stromx/runtime/Id2DataPair.h"
#include "stromx/runtime/OperatorException.h"
#include "stromx/runtime/Primitive.h"

using namespace stromx::runtime;

namespace stromx
{
    namespace runtime
    {
        const std::string ExceptionOperator::TYPE("ExceptionOperator");
        const std::string ExceptionOperator::PACKAGE(STROMX_RUNTIME_PACKAGE_NAME);
        const Version ExceptionOperator::VERSION(0, 1, 0);

        ExceptionOperator::ExceptionOperator()
        : OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs(),
                        setupParameters())
        {
        }

        void ExceptionOperator::setParameter(unsigned int id, const Data& value)
        {
            try
            {
                switch(id)
                {
                case THROW_DEACTIVATE:
                    m_throwDeactivate = data_cast<Bool>(value);
                    break;
                case BLOCK_EXECUTE:
                    m_blockExecute.store(data_cast<Bool>(value));
                    break;
                default:
                    throw WrongParameterId(id, *this);
                }
            }
            catch(std::bad_cast&)
            {
                throw WrongParameterType(*parameters()[id], *this);
            }
        }

        const DataRef ExceptionOperator::getParameter(const unsigned int id) const
        {
            switch(id)
            {
            case THROW_DEACTIVATE:
                return m_throwDeactivate;
            case BLOCK_EXECUTE:
                return Bool(m_blockExecute.load());
            default:
                throw WrongParameterId(id, *this);
            }
        }

        void ExceptionOperator::deactivate()
        {
            if(m_throwDeactivate)
                throw OperatorError(*this, "Failed to deactivate operator.");
        }

        void ExceptionOperator::execute(DataProvider& provider)
        {
            while(m_blockExecute.load())
            {
                boost::this_thread::disable_interruption disable;
                boost::this_thread::sleep(boost::posix_time::seconds(1));
            } 
            
            DataContainer data(new None);
            Id2DataPair out(OUTPUT, data);
            provider.sendOutputData(out);
        }
        
        void ExceptionOperator::interrupt()
        {
            m_blockExecute.store(false);
        }
                
        const std::vector<const Description*> ExceptionOperator::setupInputs()
        {
            std::vector<const Description*> inputs;
            
            return inputs;
        }

        const std::vector<const Description*> ExceptionOperator::setupOutputs()
        {
            std::vector<const Description*> outputs;
            
            outputs.push_back(new Description(OUTPUT, DataVariant::NONE));
            
            return outputs;
        }

        const std::vector<const Parameter*> ExceptionOperator::setupParameters()
        {
            std::vector<const Parameter*> parameters;
            
            Parameter* param = new Parameter(THROW_DEACTIVATE, DataVariant::BOOL);
            param->setAccessMode(Parameter::NONE_WRITE);
            parameters.push_back(param);
            
            param = new Parameter(BLOCK_EXECUTE, DataVariant::BOOL);
            param->setAccessMode(Parameter::NONE_WRITE);
            parameters.push_back(param);
            
            return parameters;
        }
    }
}


