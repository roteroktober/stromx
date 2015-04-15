#ifndef STROMX_CVOBJDETECT_CASCADECLASSIFIER_H
#define STROMX_CVOBJDETECT_CASCADECLASSIFIER_H

#include "stromx/cvobjdetect/Config.h"
#include <stromx/runtime/OperatorKernel.h>
#include <stromx/runtime/File.h>

namespace stromx
{
    namespace cvobjdetect
    {
        class CascadeClassifier : public runtime::OperatorKernel
        {
        public:
            enum OutputId
            {
                OBJECTS
            };

            enum InputId
            {
                IMAGE
            };

            enum ParameterId
            {
                CLASSIFIER
            };

            CascadeClassifier();
            virtual OperatorKernel* clone() const { return new CascadeClassifier; }
            virtual void setParameter(const unsigned int, const runtime::Data&);
            virtual const runtime::DataRef getParameter(unsigned int id) const;
            virtual void execute(runtime::DataProvider& provider){};

        private:
            static const std::string PACKAGE;
            static const runtime::Version VERSION;
            static const std::string TYPE;

            static const std::vector<const runtime::Description*> setupInputs();
            static const std::vector<const runtime::Description*> setupOutputs();
            const std::vector<const runtime::Parameter*> setupParameters();
            
            runtime::File m_classifierFile;
        };
    }
}

#endif // STROMX_CVOBJDETECT_CASCADECLASSIFIER_H