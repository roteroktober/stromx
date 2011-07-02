#include "CameraBuffer.h"

#include "Config.h"

#include <stream/OperatorException.h>
#include <stream/NumericParameter.h>
#include <stream/DataContainer.h>
#include <stream/Id2DataPair.h>
#include <stream/DataProvider.h>

#include <base/Image.h>

#include <typeinfo>

using namespace stream;

namespace base
{
    namespace camera
    {
        const std::string CameraBuffer::NAME("CameraBuffer");
        const std::string CameraBuffer::PACKAGE(PACKAGE_NAME);
        const Version CameraBuffer::VERSION(BASE_VERSION_MAJOR, BASE_VERSION_MINOR);
        
        CameraBuffer::CameraBuffer()
          : Operator(NAME, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters())
        {
        }

        void CameraBuffer::setParameter(const unsigned int id, const Data& value)
        {
            try
            {
                switch(id)
                {
                case BUFFER_SIZE:
                    m_bufferSize = dynamic_cast<const UInt32 &>(value);
                case NUM_BUFFERS:
                    m_numBuffers = dynamic_cast<const UInt32 &>(value);
                default:
                    throw ParameterIdException(id, *this);
                }
            }
            catch(std::bad_cast&)
            {
                throw ParameterTypeException(*parameters()[id], *this);
            }
        }
        
        void CameraBuffer::activate()
        {
            // allocate all buffers and add them to the recycler
            for(unsigned int i = 0; i < m_numBuffers; ++i)
                m_buffers.add(DataContainer(new Image(m_bufferSize)));
        }

        void CameraBuffer::deactivate()
        {
            Data* buffer = 0;
            
            // delete all buffers in the recycling access
            while(buffer = m_buffers())
                delete buffer;
        }

        const Data& CameraBuffer::getParameter(const unsigned int id)
        {
            switch(id)
            {
            case BUFFER_SIZE:
                return m_bufferSize;
            case NUM_BUFFERS:
                return m_numBuffers;
            default:
                throw ParameterIdException(id, *this);
            }
        }  
        
        void CameraBuffer::execute(DataProvider& provider)
        {
            Id2DataPair inputMapper(INPUT);
            provider.receiveInputData(inputMapper);
        }
        
        const std::vector<Description*> CameraBuffer::setupInputs()
        {
            std::vector<Description*> inputs;
        
            Description* input = new Description(INPUT, DataType::IMAGE);
            input->setName("Input");
            inputs.push_back(input);
            
            return inputs;
        }
        
        const std::vector<Description*> CameraBuffer::setupOutputs()
        {
            std::vector<Description*> outputs;
        
            Description* output = new Description(OUTPUT, DataType::IMAGE);
            output->setName("Output");
            outputs.push_back(output);
        
            Description* buffer = new Description(BUFFER, DataType::IMAGE);
            buffer->setName("Buffer");
            outputs.push_back(buffer);
        
            Description* index = new Description(ID, DataType::UINT_32);
            index->setName("Index");
            outputs.push_back(index);
            
            return outputs;
        }
        
        const std::vector<Parameter*> CameraBuffer::setupParameters()
        {
            std::vector<Parameter*> parameters;
        
            NumericParameter<UInt32>* numBuffers = new NumericParameter<UInt32>(NUM_BUFFERS, DataType::UINT_32);
            numBuffers->setName("Number of buffers");
            numBuffers->setInactiveAccessMode(stream::Parameter::READ_WRITE);
            numBuffers->setActiveAccessMode(stream::Parameter::READ);
            parameters.push_back(numBuffers);
        
            NumericParameter<UInt32>* bufferSize = new NumericParameter<UInt32>(BUFFER_SIZE, DataType::UINT_32);
            bufferSize->setName("Buffer size in bytes");
            bufferSize->setInactiveAccessMode(stream::Parameter::READ_WRITE);
            bufferSize->setActiveAccessMode(stream::Parameter::READ);
            parameters.push_back(bufferSize);
                                        
            return parameters;
        }
    }
} 
