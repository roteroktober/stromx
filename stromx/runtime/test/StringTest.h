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

#ifndef STROMX_RUNTIME_STRINGTEST_H
#define STROMX_RUNTIME_STRINGTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "stromx/runtime/String.h"

namespace stromx
{
    namespace runtime
    {
        class StringTest : public CPPUNIT_NS :: TestFixture
        {
            CPPUNIT_TEST_SUITE (StringTest);
            CPPUNIT_TEST(testStdStringConstructor);
            CPPUNIT_TEST(testCharConstructor);
            CPPUNIT_TEST(testSerialize);
            CPPUNIT_TEST(testDeserialize);
            CPPUNIT_TEST(testCastToStdString);
            CPPUNIT_TEST(testEquality);
            CPPUNIT_TEST(testInequality);
            CPPUNIT_TEST(testIsVariant);
            CPPUNIT_TEST(testPtrCast);
            CPPUNIT_TEST(testRefCast);
            CPPUNIT_TEST_SUITE_END ();

        public:
            StringTest() {}
            
            void setUp() {}
            void tearDown() {}

        protected:
            void testStdStringConstructor();
            void testCharConstructor();
            void testSerialize();
            void testDeserialize();
            void testCastToStdString();
            void testEquality();
            void testInequality();
            void testClone();
            void testIsVariant();
            void testPtrCast();
            void testRefCast();
                
        private:
            
            const static Version VERSION;
            
            String m_string;
        };
    }
}

#endif // STROMX_RUNTIME_STRINGTEST_H