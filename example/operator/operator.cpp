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

#include <stromx/runtime/Factory.h>
#include <stromx/runtime/XmlReader.h>
#include <stromx/runtime/Stream.h>
#include <stromx/runtime/Runtime.h>
#include <stromx/runtime/Operator.h>
#include <stromx/runtime/Primitive.h>
#include <stromx/runtime/ReadAccess.h>

#include "math/Add.h"

#include <iostream>

using namespace stromx;

int main (int, char**)
{
    runtime::Factory factory;
    
    stromxRegisterRuntime(&factory);
    
    runtime::OperatorKernel* op = new math::Add;
    factory.registerOperator(op);
    
    runtime::Stream* stream = runtime::XmlReader().readStream("operator.xml", &factory);
    
    stream->start();
    
    runtime::Operator* timer = stream->operators()[2];
    
    for(unsigned int i = 0; i < 5; ++i)
    {
        runtime::DataContainer data = timer->getOutputData(0);
        runtime::ReadAccess count(data);
        std::cout << "Received " 
                  << (unsigned int)(count.get<runtime::UInt32>()) 
                  << std::endl;
        
        timer->clearOutputData(0);
    }
    
    stream->stop();
    stream->join();
    
    delete stream;
}