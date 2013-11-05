/* 
 *  Copyright 2012 Matthias Fuchs
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

#include "stromx/runtime/Client.h"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include "stromx/runtime/DataProvider.h"
#include "stromx/runtime/Id2DataComposite.h"
#include "stromx/runtime/Id2DataPair.h"
#include "stromx/runtime/NumericParameter.h"
#include "stromx/runtime/OperatorException.h"

namespace stromx
{
    namespace runtime
    {
        const std::string Client::TYPE("Client");
        const std::string Client::PACKAGE(STROMX_RUNTIME_PACKAGE_NAME);
        const Version Client::VERSION(0, 1, 0);
        const unsigned int Client::MIN_PORT = 49152;
        const unsigned int Client::MAX_PORT = 65535;
        
        Client::Client()
          : OperatorKernel(TYPE, PACKAGE, VERSION, setupParameters()),
            m_url("localhost"),
            m_port(MIN_PORT)
        {
        }
        
        void Client::setParameter(unsigned int id, const runtime::Data& value)
        {
            UInt16 uintValue;
            
            switch(id)
            {
            case URL:
                m_url = data_cast<String>(value);
                break;
            case PORT:
                uintValue = data_cast<UInt16>(value);
                if(uintValue < MIN_PORT)
                    throw WrongParameterValue(parameter(PORT), *this, "Too small port number.");
                if(uintValue > MAX_PORT)
                    throw WrongParameterValue(parameter(PORT), *this, "Too large port number.");
                m_port = uintValue;
                break;
            default:
                throw WrongParameterId(id, *this);
            }
        }

        const DataRef Client::getParameter(const unsigned int id) const
        {
            switch(id)
            {
            case URL:
                return m_url;
            case PORT:
                return m_port;
            default:
                throw WrongParameterId(id, *this);
            }
        }
        
        void Client::initialize()
        {
            OperatorKernel::initialize(setupInputs(),
                                       setupOutputs(),
                                       std::vector<const Parameter*>());
        }
        
        void Client::execute(DataProvider& provider)
        {
            using boost::asio::ip::tcp;
            
            std::ostringstream result;
            try
            {
                std::string portString = boost::lexical_cast<std::string>(m_port);
                boost::asio::io_service io_service;

                tcp::resolver resolver(io_service);
                tcp::resolver::query query(m_url, portString);
                tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

                tcp::socket socket(io_service);
                boost::asio::connect(socket, endpoint_iterator);

                for (;;)
                {
                    char buf[128];
                    boost::system::error_code error;

                    size_t len = socket.read_some(boost::asio::buffer(buf), error);

                    if (error == boost::asio::error::eof)
                        break; // Connection closed cleanly by peer.
                    else if (error)
                        throw boost::system::system_error(error); // Some other error.

                    result << buf;
                }
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
            
            Data* outData = new String(result.str());
            Id2DataPair outputDataMapper(OUTPUT, DataContainer(outData));
            provider.sendOutputData(outputDataMapper);
        }
        
        const std::vector<const Description*> Client::setupInputs()
        {
            std::vector<const Description*> inputs;
            return inputs;
        }
        
        const std::vector<const Description*> Client::setupOutputs() const
        {
            std::vector<const Description*> outputs;
            
            Description* ouput = new Description(OUTPUT, DataVariant::DATA);
            ouput->setTitle("Output");
            outputs.push_back(ouput);
            
            return outputs;
        }
        
        const std::vector<const Parameter*> Client::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            Parameter* url = new Parameter(URL, DataVariant::STRING);
            url->setTitle("URL");
            url->setAccessMode(runtime::Parameter::INITIALIZED_WRITE);
            parameters.push_back(url);
            
            NumericParameter<UInt16>* port = new NumericParameter<UInt16>(PORT);
            port->setTitle("TCP port");
            port->setAccessMode(runtime::Parameter::INITIALIZED_WRITE);
            port->setMin(UInt16(MIN_PORT));
            port->setMax(UInt16(MAX_PORT));
            parameters.push_back(port);
            
            return parameters;
        }
    }
}