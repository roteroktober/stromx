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

#ifndef BASE_TIMEPERIODTEST_H
#define BASE_TIMEPERIODTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace stream
{
    class OperatorWrapper;
    class DataContainer;
}

namespace base
{
    class TimePeriodTest : public CPPUNIT_NS :: TestFixture
    {
        CPPUNIT_TEST_SUITE (TimePeriodTest);
        CPPUNIT_TEST (testExecute);
        CPPUNIT_TEST (testExecuteZeroPeriod);
        CPPUNIT_TEST_SUITE_END ();

        public:
            TimePeriodTest() : m_operator(0), m_image(0) {}
            
            void setUp();
            void tearDown();

        protected:
            void testExecute();
            void testExecuteZeroPeriod();
            
        private:
            void getOutputDataInterrupted();
            
            stream::OperatorWrapper* m_operator;
            stream::DataContainer* m_image;
    };
}

#endif // BASE_TRIGGERTEST_H