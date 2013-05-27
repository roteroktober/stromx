/* 
*  Copyright 2011 Matthias Fuchs
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

#include <boost/thread.hpp>
#include <cppunit/TestAssert.h>
#include <stromx/runtime/DataContainer.h>
#include <stromx/runtime/Enum.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/OperatorTester.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/TriggerData.h>
#include "stromx/imgutil/Camera.h"
#include "stromx/imgutil/Image.h"
#include "stromx/imgutil/test/CameraTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::imgutil::CameraTest);

namespace stromx
{
    using namespace runtime;

    namespace imgutil
    {
        void CameraTest::setUp ( void )
        {
            Image image("lenna.jpg");
            
            m_operator = new runtime::OperatorTester(new Camera());
            m_operator->setParameter(Camera::OUTPUT_INDEX, Bool(true));
            m_operator->initialize();
            m_operator->setParameter(Camera::NUM_BUFFERS, UInt32(1));
            m_operator->setParameter(Camera::BUFFER_SIZE, UInt32(image.bufferSize()));
            m_operator->setParameter(Camera::IMAGE, image);
            
            // default to immediate, automatic trigger
            m_operator->setParameter(Camera::TRIGGER_MODE, Enum(Camera::INTERNAL));
            m_operator->setParameter(Camera::FRAME_PERIOD, UInt32(0));
        }
        
        void CameraTest::testExecuteSoftwareTrigger()
        {
            m_operator->setParameter(Camera::TRIGGER_MODE, Enum(Camera::SOFTWARE));
            m_operator->activate();
            
            {
                boost::this_thread::sleep(boost::posix_time::seconds(1));
                m_operator->setParameter(Camera::TRIGGER, runtime::TriggerData());
                DataContainer imageContainer = m_operator->getOutputData(Camera::OUTPUT);
                DataContainer indexContainer = m_operator->getOutputData(Camera::INDEX);
                UInt32 index = ReadAccess<UInt32>(indexContainer)();
                CPPUNIT_ASSERT_EQUAL(UInt32(0), index);
                
                const runtime::Image & image = ReadAccess<runtime::Image>(imageContainer)();
                imgutil::Image::save("CameraTest_testExecuteSoftwareTrigger.png", image);
            }
            
            m_operator->clearOutputData(Camera::OUTPUT);
            m_operator->clearOutputData(Camera::INDEX);
            
            {
                boost::this_thread::sleep(boost::posix_time::seconds(1));
                m_operator->setParameter(Camera::TRIGGER, runtime::TriggerData());
                DataContainer imageContainer = m_operator->getOutputData(Camera::OUTPUT);
                DataContainer indexContainer = m_operator->getOutputData(Camera::INDEX);
                UInt32 index = ReadAccess<UInt32>(indexContainer)();
                CPPUNIT_ASSERT_EQUAL(UInt32(1), index);
            }
            
        }
        
        void CameraTest::testExecuteInternalTrigger()
        {
            m_operator->setParameter(Camera::TRIGGER_MODE, Enum(Camera::INTERNAL));
            m_operator->setParameter(Camera::FRAME_PERIOD, UInt32(1000));
            m_operator->activate();
            
            {
                DataContainer imageContainer = m_operator->getOutputData(Camera::OUTPUT);
                DataContainer indexContainer = m_operator->getOutputData(Camera::INDEX);
                UInt32 index = ReadAccess<UInt32>(indexContainer)();
                CPPUNIT_ASSERT_EQUAL(UInt32(0), index);
            }
            
            m_operator->clearOutputData(Camera::OUTPUT);
            m_operator->clearOutputData(Camera::INDEX);
            
            {
                DataContainer imageContainer = m_operator->getOutputData(Camera::OUTPUT);
                DataContainer indexContainer = m_operator->getOutputData(Camera::INDEX);
                UInt32 index = ReadAccess<UInt32>(indexContainer)();
                CPPUNIT_ASSERT_EQUAL(UInt32(1), index);
            }
        }
        
        void CameraTest::testAdjustPixelType()
        {
            m_operator->setParameter(Camera::PIXEL_TYPE, Enum(runtime::Image::BAYERBG_8));
            m_operator->activate();
            DataContainer imageContainer = m_operator->getOutputData(Camera::OUTPUT);
            const runtime::Image & image = ReadAccess<runtime::Image>(imageContainer)();
            
            CPPUNIT_ASSERT_EQUAL(image.pixelType(), runtime::Image::BAYERBG_8);
            imgutil::Image::save("CameraTest_testAdjustPixelTypeBayerBg8.png", image);
        }

        void CameraTest::testAdjustRoi()
        {
            m_operator->setParameter(Camera::WIDTH, UInt32(319));
            m_operator->setParameter(Camera::LEFT, UInt32(51));
            m_operator->setParameter(Camera::HEIGHT, UInt32(217));
            m_operator->setParameter(Camera::TOP, UInt32(46));
            m_operator->activate();
            DataContainer imageContainer = m_operator->getOutputData(Camera::OUTPUT);
            const runtime::Image & image = ReadAccess<runtime::Image>(imageContainer)();
            
            CPPUNIT_ASSERT_EQUAL(image.width(), (unsigned int)(319));
            CPPUNIT_ASSERT_EQUAL(image.height(), (unsigned int)(217));
            imgutil::Image::save("CameraTest_testAdjustRoi.png", image);
        }
        
        void CameraTest::testAdjustExposure()
        {
            m_operator->setParameter(Camera::EXPOSURE, UInt32(5));
            m_operator->setParameter(Camera::PIXEL_TYPE, Enum(runtime::Image::RGB_24));
            m_operator->activate();
            DataContainer imageContainer = m_operator->getOutputData(Camera::OUTPUT);
            const runtime::Image & image = ReadAccess<runtime::Image>(imageContainer)();
            
            imgutil::Image::save("CameraTest_testAdjustExposure.png", image);
        }

        void CameraTest::testAdjustWhiteBalance()
        {
            m_operator->setParameter(Camera::WHITE_BALANCE_RED, Double(2.0));
            m_operator->setParameter(Camera::WHITE_BALANCE_GREEN, Double(1.0));
            m_operator->setParameter(Camera::WHITE_BALANCE_BLUE, Double(0.0));
            m_operator->setParameter(Camera::PIXEL_TYPE, Enum(runtime::Image::RGB_24));
            m_operator->activate();
            DataContainer imageContainer = m_operator->getOutputData(Camera::OUTPUT);
            const runtime::Image & image = ReadAccess<runtime::Image>(imageContainer)();
            
            imgutil::Image::save("CameraTest_testAdjustWhiteBalance.png", image);
        }
        
        void CameraTest::testValidateBufferSize()
        {
            UInt32 bufferSize = data_cast<UInt32>(m_operator->getParameter(Camera::BUFFER_SIZE));
            UInt32 singleChannelSize((unsigned int)(bufferSize) / 3);
            
            m_operator->setParameter(Camera::PIXEL_TYPE, Enum(runtime::Image::RGB_24));
            CPPUNIT_ASSERT_THROW(m_operator->setParameter(Camera::BUFFER_SIZE, singleChannelSize),
                                 WrongParameterValue);
            
            m_operator->setParameter(Camera::PIXEL_TYPE, Enum(runtime::Image::MONO_8));
            CPPUNIT_ASSERT_NO_THROW(m_operator->setParameter(Camera::BUFFER_SIZE, singleChannelSize));
            
            CPPUNIT_ASSERT_THROW(m_operator->setParameter(Camera::PIXEL_TYPE, Enum(runtime::Image::RGB_24)),
                                 WrongParameterValue);
        }

        void CameraTest::tearDown ( void )
        {
            boost::this_thread::sleep(boost::posix_time::seconds(1));
            m_operator->deactivate();
            delete m_operator;
        }
    }
}
