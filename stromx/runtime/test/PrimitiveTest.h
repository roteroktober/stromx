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

#ifndef STROMX_RUNTIME_PRIMITIVETEST_H
#define STROMX_RUNTIME_PRIMITIVETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "stromx/runtime/InputProvider.h"
#include "stromx/runtime/None.h"
#include "stromx/runtime/OutputProvider.h"
#include "stromx/runtime/Primitive.h"
#include "stromx/runtime/test/DummyInput.h"
#include "stromx/runtime/test/DummyOutput.h"
#include "stromx/runtime/Variant.h"

namespace stromx
{
    namespace runtime
    {
        template<class primitive_t, class repr_t>
        class PrimitiveTest : public CPPUNIT_NS :: TestFixture
        {
        public:
            void setUp() {}
            void tearDown() {}

        protected:
            void testDefaultConstructor()
            {
                CPPUNIT_ASSERT_EQUAL(repr_t(m_value), repr_t(0));
            }
            
            void testConstructor()
            {
                m_value = primitive_t(value());
                
                CPPUNIT_ASSERT_EQUAL(repr_t(m_value), value());
            }
            
            void testAssignment()
            {
                m_value = value();
                
                CPPUNIT_ASSERT_EQUAL(repr_t(m_value), value());
            }
            
            void testCopyConstructor()
            {
                m_value = value();
                primitive_t copy = primitive_t(m_value);
                
                CPPUNIT_ASSERT_EQUAL(repr_t(copy), value());
            }
            
            void testSerialize()
            {
                DummyOutput out;
                m_value = value();
                m_value.serialize(out);
                CPPUNIT_ASSERT_EQUAL(str(), out.value());
            }
            
            void testDeserialize()
            {
                DummyInput in(str());
                m_value.deserialize(in, VERSION);
                CPPUNIT_ASSERT_EQUAL(primitive_t(value()), m_value);
            }
            
            void testIsVariant()
            {
                CPPUNIT_ASSERT(m_value.variant().isVariant(variant()));
                CPPUNIT_ASSERT(! m_value.variant().isVariant(Variant::NONE));
            }
            
            void testPtrCast()
            {
                CPPUNIT_ASSERT(data_cast<Data>(&m_value));
                CPPUNIT_ASSERT(data_cast<primitive_t>(&m_value));
                CPPUNIT_ASSERT_EQUAL(data_cast<None>(&m_value), static_cast<None*>(0));
            }
            
            void testRefCast()
            {
                CPPUNIT_ASSERT_NO_THROW(data_cast<Data>(m_value));
                CPPUNIT_ASSERT_NO_THROW(data_cast<primitive_t>(m_value));
                CPPUNIT_ASSERT_THROW(data_cast<None>(m_value), BadCast);
            }
            
            void testToInt()
            {
                m_value = primitive_t(value());
                CPPUNIT_ASSERT_EQUAL(int64_t(value()), toInt(m_value));
            }
            
            void testToDouble()
            {
                m_value = primitive_t(value());
                CPPUNIT_ASSERT_DOUBLES_EQUAL(double(value()), toDouble(m_value),
                                             1e-6);
            }
            
            virtual repr_t value() const = 0;
            virtual std::string str() const = 0;
            virtual const VariantInterface & variant() const = 0;
                
        private:            
            const static Version VERSION;
            
            primitive_t m_value;
        };
        
        template<class primitive_t, class repr_t>
        const Version PrimitiveTest<primitive_t, repr_t>::VERSION(0, 1, 0);
    }
}

#endif // STROMX_RUNTIME_PRIMITIVETEST_H