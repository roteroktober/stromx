/* 
 *  Copyright 2011 Thomas Fidler
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

#ifndef STROMX_RUNTIME_NETWORKTEST_H
#define STROMX_RUNTIME_NETWORKTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "stromx/runtime/None.h"

namespace stromx
{
    namespace runtime
    {
        namespace impl
        {
            class Network;
        }
        
        class SynchronizedOperatorKernel;
        
        class NetworkTest : public CPPUNIT_NS :: TestFixture
        {
            CPPUNIT_TEST_SUITE (NetworkTest);
            CPPUNIT_TEST(testAddOperator);
            CPPUNIT_TEST(testRemoveOperator);
            CPPUNIT_TEST(testActivate);
            CPPUNIT_TEST(testDeactivate);
            CPPUNIT_TEST(testDeactivateFails);
            CPPUNIT_TEST(testRemoveConnectedOperator);
            CPPUNIT_TEST(testConnectionSource);
            CPPUNIT_TEST_SUITE_END ();

        public:
            NetworkTest() : m_network(0) {}
            
            void setUp();
            void tearDown();

        protected:
            void testAddOperator();
            void testRemoveOperator();
            void testRemoveConnectedOperator();
            void testActivate();
            void testDeactivate();
            void testDeactivateFails();
            void testConnectionSource();
                
        private: 
            impl::Network* m_network;
        };
    }
}

#endif // STROMX_RUNTIME_NETWORKTEST_H