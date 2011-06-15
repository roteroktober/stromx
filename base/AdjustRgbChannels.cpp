#include "AdjustRgbChannels.h"

#include "Config.h"
#include "Image.h"
#include "Utilities.h"

#include <stream/NumericParameter.h>
#include <stream/Primitive.h>
#include <stream/OperatorException.h>
#include <stream/DataContainer.h>
#include <stream/DataProvider.h>

#include <stream/Id2DataPair.h>

using namespace stream;

namespace base
{
    const std::string AdjustRgbChannels::NAME("Clip");
    
    const std::string AdjustRgbChannels::PACKAGE(PACKAGE_NAME);
    const Version AdjustRgbChannels::VERSION(BASE_VERSION_MAJOR, BASE_VERSION_MINOR);
    
    AdjustRgbChannels::AdjustRgbChannels()
      : Operator(NAME, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters())
    {
    }

    void AdjustRgbChannels::setParameter(unsigned int id, const Data& value)
    {
        try
        {
            switch(id)
            {
            case RED:
                m_red = dynamic_cast<const Double&>(value);
                break;
            case GREEN:
                m_green = dynamic_cast<const Double&>(value);
                break;
            case BLUE:
                m_blue = dynamic_cast<const Double&>(value);
                break;
            default:
                throw ParameterIdException(id, *this);
            }
        }
        catch(std::bad_cast&)
        {
            throw ParameterTypeException(parameters()[id], *this);
        }
    }

    const Data& AdjustRgbChannels::getParameter(unsigned int id)
    {
        switch(id)
        {
        case RED:
            return m_red;
        case GREEN:
            return m_green;
        case BLUE:
            return m_blue;
        default:
            throw ParameterIdException(id, *this);
        }
    }  
    
    void AdjustRgbChannels::execute(DataProvider& provider)
    {
        Id2DataPair inputDataMapper(INPUT);
        provider.receiveInputData(inputDataMapper);
        
        DataContainer* container = inputDataMapper.data();
        const Data* data = container->getReadAccess();
        const Image* image = dynamic_cast<const Image*>(data);

        cv::Mat cvImage = getOpenCvMat(*image);
        
        switch(image->pixelType())
        {
        case stream::Image::RGB_24:
        {
            cv::MatIterator_<unsigned char> it = cvImage.begin<unsigned char>();
            cv::MatIterator_<unsigned char> it_end = cvImage.end<unsigned char>();
            for(; it != it_end; ++it)
            {
                *it = cv::saturate_cast<unsigned char>((unsigned char)(double(*it) * m_red)); ++it;
                *it = cv::saturate_cast<unsigned char>((unsigned char)(double(*it) * m_green)); ++it;
                *it = cv::saturate_cast<unsigned char>((unsigned char)(double(*it) * m_blue));
            }
            break;
        }
        default:
            throw InputTypeException(INPUT, *this);
        }
        
        Id2DataPair outputDataMapper(INPUT, container);
        provider.sendOutputData( outputDataMapper);
    }
    
    const std::vector< Description > AdjustRgbChannels::setupInputs()
    {
        std::vector<Description> inputs;
        
        Description input(INPUT, DataType::RGB_IMAGE);
        input.setName("Input");
        inputs.push_back(input);
        
        return inputs;
    }
    
    const std::vector< stream::Description > AdjustRgbChannels::setupOutputs()
    {
        std::vector<Description> outputs;
        
        Description output(OUTPUT, DataType::RGB_IMAGE);
        output.setName("Output");
        outputs.push_back(output);
        
        return outputs;
    }
    
    const std::vector< stream::Parameter > AdjustRgbChannels::setupParameters()
    {
        std::vector<stream::Parameter> parameters;
        
        NumericParameter<Double> red(RED, Double(0.0), Double(10.0));
        red.setName("Red");
        red.setInactiveAccessMode(stream::Parameter::READ_WRITE);
        red.setActiveAccessMode(stream::Parameter::READ_WRITE);
        parameters.push_back(red);
        
        NumericParameter<Double> green(GREEN, Double(0.0), Double(10.0));
        green.setName("Green");
        green.setInactiveAccessMode(stream::Parameter::READ_WRITE);
        green.setActiveAccessMode(stream::Parameter::READ_WRITE);
        parameters.push_back(green);
        
        NumericParameter<Double> blue(BLUE, Double(0.0), Double(10.0));
        blue.setName("Blue");
        blue.setInactiveAccessMode(stream::Parameter::READ_WRITE);
        blue.setActiveAccessMode(stream::Parameter::READ_WRITE);
        parameters.push_back(blue);
                                    
        return parameters;
    }
} 
