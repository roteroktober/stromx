#include "stromx/cvobjdetect/CascadeClassifier.h"

#include <stromx/runtime/Variant.h>
#include <stromx/runtime/OperatorException.h>

namespace stromx
{
    namespace cvobjdetect
    {
        const std::string CascadeClassifier::PACKAGE(STROMX_CVOBJDETECT_PACKAGE_NAME);
        const runtime::Version CascadeClassifier::VERSION(STROMX_CVOBJDETECT_VERSION_MAJOR, STROMX_CVOBJDETECT_VERSION_MINOR, STROMX_CVOBJDETECT_VERSION_PATCH);
        const std::string CascadeClassifier::TYPE("CascadeClassifier");

        CascadeClassifier::CascadeClassifier()
            : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters()),
              m_classifierFile(runtime::File(std::string(".xml"), runtime::File::TEXT))
        {
        }

        const std::vector<const runtime::Parameter*> CascadeClassifier::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            runtime::Parameter* classifier = new runtime::Parameter(CLASSIFIER, runtime::Variant::FILE);
            classifier->setTitle("Classifier");
            classifier->setAccessMode(runtime::Parameter::INITIALIZED_WRITE);
            parameters.push_back(classifier);
            
            return parameters;
        }

        const std::vector<const runtime::Description*> CascadeClassifier::setupInputs()
        {
            std::vector<const runtime::Description*> inputs;

            runtime::Description* input = new runtime::Description(IMAGE, runtime::Variant::IMAGE);
            input->setTitle("Input image");
            inputs.push_back(input);

            return inputs;
        }

        const std::vector<const runtime::Description*> CascadeClassifier::setupOutputs()
        {
            std::vector<const runtime::Description*> outputs;
 
            runtime::Description* output = new runtime::Description(OBJECTS, runtime::Variant::MATRIX);
            output->setTitle("Detected objects");
            outputs.push_back(output);

            return outputs;
        }
        
        void CascadeClassifier::setParameter(const unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
                case CLASSIFIER:
                {
                    const runtime::File& classifierFile = stromx::runtime::data_cast<runtime::File>(value);
                    m_classifierFile = classifierFile;
                    break;
                }
                default:
                    throw runtime::WrongParameterId(id, *this);
                }
            }
            catch(std::bad_cast&)
            {
                throw runtime::WrongParameterType(parameter(id), *this);
            }
        }
        
        const runtime::DataRef CascadeClassifier::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case CLASSIFIER:
                return m_classifierFile;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }  

    }
}