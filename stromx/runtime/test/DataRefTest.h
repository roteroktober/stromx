/* 
*  Copyright 2012 Matthias Fuchs
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

#ifndef STROMX_RUNTIME_DATAREFTEST_H
#define STROMX_RUNTIME_DATAREFTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

namespace stromx
{
    namespace runtime
    {
        class Data;
        
        class DataRefTest : public CPPUNIT_NS :: TestFixture
        {
            CPPUNIT_TEST_SUITE (DataRefTest);
            CPPUNIT_TEST(testDataRef);
            CPPUNIT_TEST(testConstDataRef);
            CPPUNIT_TEST(testIsNull);
            CPPUNIT_TEST_SUITE_END ();

        public:
            DataRefTest() {}
            
            void setUp() {}
            void tearDown() {}
            
        private:
            void dataFunction(const Data &) {}

        protected:
            void testDataRef();
            void testConstDataRef();
            void testIsNull();
        };
    }
}

#endif // STROMX_RUNTIME_DATAREFTEST_H
