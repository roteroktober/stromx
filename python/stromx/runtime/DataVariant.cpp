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

#include <stromx/runtime/DataVariant.h>
#include <stromx/runtime/Data.h>

#include <boost/python.hpp>

using namespace boost::python;
using namespace stromx::runtime;

void exportDataVariant()
{         
    class_<DataVariant>("DataVariant", no_init)
        .def_readonly("NONE", DataVariant::NONE)
        .def("title", &DataVariant::title, return_internal_reference<>())
        .def("isVariant", &DataVariant::isVariant)
        .def("id", &DataVariant::id)
        .def("package", &DataVariant::package, return_internal_reference<>())
    ;
}
