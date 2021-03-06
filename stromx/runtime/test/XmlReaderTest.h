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

#ifndef STROMX_RUNTIME_XMLREADERTEST_H
#define STROMX_RUNTIME_XMLREADERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

namespace stromx
{
    namespace runtime
    {
        class Factory;
        class Stream;
        
        class XmlReaderTest : public CPPUNIT_NS :: TestFixture
        {
            CPPUNIT_TEST_SUITE (XmlReaderTest);
            CPPUNIT_TEST(testReadStream);
            CPPUNIT_TEST(testReadStreamEmpty);
            CPPUNIT_TEST(testReadStreamWrongFile);
            CPPUNIT_TEST(testReadStreamInvalidFile);
//             CPPUNIT_TEST(testReadStreamNonsenseFile);
            CPPUNIT_TEST(testReadStreamZip);
            CPPUNIT_TEST(testReadStreamStromx);
            CPPUNIT_TEST(testReadStreamDtd);
            CPPUNIT_TEST(testReadParameters);
            CPPUNIT_TEST(testReadParametersEmpty);
            CPPUNIT_TEST(testReadParametersWrongFile);
            CPPUNIT_TEST(testReadParametersInvalidFile);
            CPPUNIT_TEST(testReadParametersZip);
            CPPUNIT_TEST(testReadParametersStromx);
            CPPUNIT_TEST(testReadParametersDtd);
            CPPUNIT_TEST_SUITE_END ();

        public:
            XmlReaderTest() : m_factory(0), m_stream(0) {}
            
            void setUp();
            void tearDown();

        protected:
            void testReadStream();
            void testReadStreamEmpty();
            void testReadStreamWrongFile();
            void testReadStreamInvalidFile();
            void testReadStreamNonsenseFile();
            void testReadStreamZip();
            void testReadStreamStromx();
            void testReadStreamDtd();
            
            void testReadParameters();
            void testReadParametersEmpty();
            void testReadParametersWrongFile();
            void testReadParametersInvalidFile();
            void testReadParametersZip();
            void testReadParametersStromx();
            void testReadParametersDtd();
                
        private:
            Factory* m_factory;
            Stream* m_stream;
        };
    }
}

#endif // STROMX_RUNTIME_XMLREADERTEST_H