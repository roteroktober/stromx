#ifndef STREAM_DATACONTAINERTEST_H
#define STREAM_DATACONTAINERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace stream
{
    class DataContainer;

    class DataContainerTest : public CPPUNIT_NS :: TestFixture
    {
        CPPUNIT_TEST_SUITE (DataContainerTest);
        CPPUNIT_TEST (dereferenceTest);
        CPPUNIT_TEST (getWriteAccessTest);
        CPPUNIT_TEST_SUITE_END ();

        public:
            DataContainerTest() : m_container(0) {}
            
            void setUp();
            void tearDown();

        protected:
            void dereferenceTest();
            void getWriteAccessTest();
            
        private:
        DataContainer* m_container; 
            
    };
}

#endif // STREAM_DATACONTAINERTEST_H