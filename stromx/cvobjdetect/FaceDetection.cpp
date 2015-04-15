#include "stromx/cvobjdetect/FaceDetection.h"

namespace stromx
{
    namespace cvobjdetect
    {
        const std::string FaceDetection::PACKAGE(STROMX_CVOBJDETECT_PACKAGE_NAME);
        const runtime::Version FaceDetection::VERSION(STROMX_CVOBJDETECT_VERSION_MAJOR, STROMX_CVOBJDETECT_VERSION_MINOR, STROMX_CVOBJDETECT_VERSION_PATCH);
        const std::string FaceDetection::TYPE("FaceDetection");

        FaceDetection::FaceDetection()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupParameters())
        {
        }

        const std::vector<const runtime::Parameter*> FaceDetection::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            return parameters;
        }
    }
}