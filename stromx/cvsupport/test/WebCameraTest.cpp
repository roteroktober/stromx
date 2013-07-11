/* 
*  Copyright 2013 Thomas Fidler
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

#include <stromx/runtime/OperatorTester.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvsupport/WebCamera.h"
#include "stromx/cvsupport/test/WebCameraTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvsupport::WebCameraTest);

namespace stromx
{
    namespace cvsupport
    {
        void WebCameraTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new WebCamera);
            try
            {
                m_operator->initialize();
            }
            catch(stromx::runtime::OperatorError&)
            {
                m_hasCamera = false;
            }
        }

        void WebCameraTest::testParameterFrameRate()
        {
            if(m_hasCamera)
            {
                if(checkParameter(WebCamera::FRAMERATE))
                {
                    m_operator->setParameter(WebCamera::FRAMERATE,runtime::Float64(0.1));
                    runtime::DataRef frameRate = m_operator->getParameter(WebCamera::FRAMERATE);
                    runtime::Float64 doubleFrameRate = runtime::data_cast<runtime::Float64>(frameRate);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(double(doubleFrameRate),double(runtime::Float64(0.1)),m_deltaAcceptance);
                    std::cout << "(Frame rate is configurable)";
                }
                else
                {
                    std::cout << "(Frame rate is not configurable)";
                }
            }
        }
        
        void WebCameraTest::testParameterBrightness()
        {
            if(m_hasCamera)
            {
                if(checkParameter(WebCamera::BRIGHTNESS))
                {
                    m_operator->setParameter(WebCamera::BRIGHTNESS,runtime::Float64(0.2));
                    runtime::DataRef brightness = m_operator->getParameter(WebCamera::BRIGHTNESS);
                    runtime::Float64 doubleBrightness = runtime::data_cast<runtime::Float64>(brightness);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(double(doubleBrightness),double(runtime::Float64(0.2)),m_deltaAcceptance);
                    std::cout << "(Brightness is configurable)";
                }
                else
                {
                    std::cout << "(Brightness is not configurable)";
                }
            }
        }
        
        void WebCameraTest::testParameterContrast()
        {
            if(m_hasCamera)
            {
                if(checkParameter(WebCamera::CONTRAST))
                {
                    m_operator->setParameter(WebCamera::CONTRAST,runtime::Float64(0.3));
                    runtime::DataRef contrast = m_operator->getParameter(WebCamera::CONTRAST);
                    runtime::Float64 doubleContrast = runtime::data_cast<runtime::Float64>(contrast);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(double(doubleContrast),double(runtime::Float64(0.3)),m_deltaAcceptance);
                    std::cout << "(Contrast is configurable)";
                }
                else
                {
                    std::cout << "(Contrast is not configurable)";
                }
            }
        }
        
        void WebCameraTest::testParameterSaturation()
        {
            if(m_hasCamera)
            {
                if(checkParameter(WebCamera::SATURATION))
                {
                    m_operator->setParameter(WebCamera::SATURATION,runtime::Float64(0.4));
                    runtime::DataRef saturation = m_operator->getParameter(WebCamera::SATURATION);
                    runtime::Float64 doubleSaturation = runtime::data_cast<runtime::Float64>(saturation);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(double(doubleSaturation),double(runtime::Float64(0.4)),m_deltaAcceptance);
                    std::cout << "(Saturation is configurable)";
                }
                else
                {
                    std::cout << "(Saturation is not configurable)";
                }
            }
        }
        
        void WebCameraTest::testParameterHue()
        {
            if(m_hasCamera)
            {
                if(checkParameter(WebCamera::HUE))
                {
                    m_operator->setParameter(WebCamera::HUE,runtime::Float64(0.5));
                    runtime::DataRef hue = m_operator->getParameter(WebCamera::HUE);
                    runtime::Float64 doubleHue = runtime::data_cast<runtime::Float64>(hue);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(double(doubleHue),double(runtime::Float64(0.5)),m_deltaAcceptance);
                    std::cout << "(Hue is configurable)";
                }
                else
                {
                    std::cout << "(Hue is not configurable)";
                }
            }
        }
        
        void WebCameraTest::testParameterGain()
        {
            if(m_hasCamera)
            {
                if(checkParameter(WebCamera::GAIN))
                {
                    m_operator->setParameter(WebCamera::GAIN,runtime::Float64(0.6));
                    runtime::DataRef gain = m_operator->getParameter(WebCamera::GAIN);
                    runtime::Float64 doubleGain = runtime::data_cast<runtime::Float64>(gain);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(double(doubleGain),double(runtime::Float64(0.6)),m_deltaAcceptance);
                    std::cout << "(Gain is configurable)";
                }
                else
                {
                    std::cout << "(Gain is not configurable)";
                }
            }
        }
        
        void WebCameraTest::testParameterExposure()
        {
            if(m_hasCamera)
            {
                if(checkParameter(WebCamera::EXPOSURE))
                {
                    m_operator->setParameter(WebCamera::EXPOSURE,runtime::Float64(0.7));
                    runtime::DataRef exposure = m_operator->getParameter(WebCamera::EXPOSURE);
                    runtime::Float64 doubleExposure = runtime::data_cast<runtime::Float64>(exposure);
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(double(doubleExposure),double(runtime::Float64(0.7)),m_deltaAcceptance);
                    std::cout << "(Exposure is configurable)";
                }
                else
                {
                    std::cout << "(Exposure is not configurable)";
                }
            }
        }
        
        void WebCameraTest::testExecute()
        {
            if(m_hasCamera)
            {
                m_operator->activate();
                runtime::DataContainer output = m_operator->getOutputData(WebCamera::OUTPUT);
            
                runtime::ReadAccess<runtime::Image> access(output);
                const runtime::Image& image = access();
            
                cvsupport::Image::save("WebCameraTest_testExecute.png", image);
                m_operator->deactivate();
            }
        }

        void WebCameraTest::tearDown()
        {
            delete m_operator;
        }
        
        bool WebCameraTest::checkParameter(const unsigned int id)
        {
            try
            {
                m_operator->info().parameter(id);
                return true;
            }
            catch(runtime::WrongId&)
            {
                return false;
            }
        }

    }
}
