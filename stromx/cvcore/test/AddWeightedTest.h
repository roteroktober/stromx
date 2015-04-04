#ifndef STROMX_CVCORE_ADDWEIGHTEDTEST_H
#define STROMX_CVCORE_ADDWEIGHTEDTEST_H

#include "stromx/cvcore/Config.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "stromx/runtime/OperatorTester.h"

namespace stromx
{
    namespace cvcore
    {
        class AddWeightedTest : public CPPUNIT_NS::TestFixture
        {
            CPPUNIT_TEST_SUITE(AddWeightedTest);
            CPPUNIT_TEST(testManual0);
            CPPUNIT_TEST(testManual1);
            CPPUNIT_TEST(testManual2);
            CPPUNIT_TEST(testAllocate0);
            CPPUNIT_TEST(testAllocate1);
            CPPUNIT_TEST_SUITE_END();
            
        public:
            AddWeightedTest() : m_operator(0) {}
            void setUp();
            void tearDown();
            
        protected:
            void testManual0();
            void testManual1();
            void testManual2();
            void testAllocate0();
            void testAllocate1();
            
        private:
            runtime::OperatorTester* m_operator;
        };
    } // cvcore
} // stromx

#endif // STROMX_CVCORE_ADDWEIGHTEDTEST_H
