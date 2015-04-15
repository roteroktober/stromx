/* 
*  Copyright 2015 Thomas Fidler
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

#include "stromx/cvobjdetect/CascadeClassifier.h"
#include "stromx/cvobjdetect/test/CascadeClassifierTest.h"
#include "stromx/runtime/OperatorTester.h"
#include <cppunit/TestAssert.h>

// #include <stromx/cvsupport/Image.h>
// #include <stromx/runtime/OperatorException.h>
// #include <stromx/runtime/ReadAccess.h>


CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvobjdetect::CascadeClassifierTest);

namespace stromx
{
    using namespace runtime;

    namespace cvobjdetect
    {
        void CascadeClassifierTest::setUp()
        {
            m_operator = new OperatorTester(new CascadeClassifier);
        }
        
        void CascadeClassifierTest::tearDown()
        {
            delete m_operator;
        }

        void CascadeClassifierTest::testInitialize()
        {
            CPPUNIT_ASSERT_NO_THROW(m_operator->initialize());
        }
    }
}