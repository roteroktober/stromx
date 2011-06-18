#include "ConstImage.h"

#include "Config.h"
#include "Image.h"
#include "Utilities.h"

#include <stream/DataContainer.h>
#include <stream/DataProvider.h>
#include <stream/Id2DataPair.h>
#include <stream/OperatorException.h>

using namespace stream;

namespace base
{
    const std::string ConstImage::NAME("Constant image source");
    
    const std::string ConstImage::PACKAGE(PACKAGE_NAME);
    const Version ConstImage::VERSION(BASE_VERSION_MAJOR, BASE_VERSION_MINOR);
    
    ConstImage::ConstImage()
      : Operator(NAME, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters()),
        m_image(0)
    {
        m_image = new DataContainer(new Image(0, 0, stream::Image::MONO_8));
    }
    
    ConstImage::~ConstImage()
    {
        delete m_image;
    }

    void ConstImage::setParameter(unsigned int id, const Data& value)
    {
        try
        {
            switch(id)
            {
            case IMAGE:
            {
                if(m_image)
                    m_image->dereference();
                
                Image* imagePtr = 0;
                try
                {
                    const stream::Image& image = dynamic_cast<const stream::Image&>(value);
                    imagePtr = new Image(image);
                }
                catch(std::bad_cast&)
                {
                    throw ParameterTypeException(*parameters()[id], *this);
                }
                
                m_image = new DataContainer(imagePtr);
                m_image->reference();
                break;
            }
            default:
                throw ParameterIdException(id, *this);
            }
        }
        catch(std::bad_cast&)
        {
            throw ParameterTypeException(*parameters()[id], *this);
        }
    }

    const Data& ConstImage::getParameter(unsigned int id)
    {
        switch(id)
        {
        case IMAGE:
            return *m_image->getWriteAccess();
        default:
            throw ParameterIdException(id, *this);
        }
    }  
    
    void ConstImage::execute(DataProvider& provider)
    {
        Id2DataPair outputDataMapper(OUTPUT, m_image);
        provider.sendOutputData( outputDataMapper);
    }
    
    const std::vector< Description* > ConstImage::setupInputs()
    {
        std::vector<Description*> inputs;
        
        return inputs;
    }
    
    const std::vector< stream::Description* > ConstImage::setupOutputs()
    {
        std::vector<Description*> outputs;
        
        Description* output = new Description(OUTPUT, DataType::IMAGE);
        output->setName("Output");
        outputs.push_back(output);
        
        return outputs;
    }
    
    const std::vector< stream::Parameter* > ConstImage::setupParameters()
    {
        std::vector<stream::Parameter*> parameters;
        
        Parameter* image = new Parameter(IMAGE, DataType::IMAGE);
        image->setInactiveAccessMode(stream::Parameter::READ_WRITE);
        image->setActiveAccessMode(stream::Parameter::READ_WRITE);
        parameters.push_back(image);
                                    
        return parameters;
    }
} 