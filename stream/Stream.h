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

#ifndef STREAM_STREAM_H
#define STREAM_STREAM_H

namespace stream
{
    class Thread;
    class Network;
    
    class Stream
    {
    public:
        Stream();
        ~Stream();
        void addThread(Thread* const thr);
        void removeThread(Thread* const thr);
        
    private:
        Network* m_network;
    };
}


#endif // STREAM_STREAM_H