#ifndef STROMX_CVOBJDETECT_FACEDETECTION_H
#define STROMX_CVOBJDETECT_FACEDETECTION_H

#include "stromx/cvobjdetect/Config.h"
#include <stromx/runtime/OperatorKernel.h>

namespace stromx
{
    namespace cvobjdetect
    {
        class STROMX_CVOBJDETECT_API FaceDetection : public runtime::OperatorKernel
        {
        public:
            FaceDetection();
            virtual OperatorKernel* clone() const { return new FaceDetection; }
            virtual void execute(runtime::DataProvider& provider){};

        private:
            static const std::string PACKAGE;
            static const runtime::Version VERSION;
            static const std::string TYPE;

            const std::vector<const runtime::Parameter*> setupParameters();
        };
    }
}

#endif // STROMX_CVOBJDETECT_FACEDETECTION_H
