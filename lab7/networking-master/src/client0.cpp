/**
@file
@author Ben Yuan
@date 2013
@copyright 2-clause BSD; see License section

@brief
A simple echo client to validate the network wrapper.

@section License

Copyright (c) 2012-2013 California Institute of Technology.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the California Institute of Technology.

*/

#include "client0.hpp"

int main(int argc, char ** argv)
{



    REQUIRE(argc == 3, "usage: %s hostname port", argv[0]);

    /* TODO: write this code.
     *
     * This should be a simple client that connects to the given server,
     * sends a message of your choice,
     * recvs and prints the response,
     * and disconnects.
     *
     **/
    CS2Net::Socket sock;
    std::string hostname(argv[1]);
    std::string to_send("test message to Caltech CMS server from Ruddock");
    uint16_t port = std::stoi(argv[2]);
    Connect(hostname, port, sock);
    Send(to_send, sock);
    auto ReceivedPtr = Receive(sock);
    if(ReceivedPtr != nullptr){
        std::cout<<"message received from " << hostname << " is " << std::endl << "*****"<< std::endl << *ReceivedPtr << std::endl;
    }else{
        std::cout <<"no message received"<<std::endl;
    }

    return 0;

}

void Send(std::string &to_send, CS2Net::Socket& sock){
    int ret = sock.Send(&to_send);
    if(ret < 0){
    // bad stuff happened
        if(ret == -1){
            ERROR("send error: %s", strerror(errno));
        }
        else{
            ERROR("this error should never occur");
        }
    }
    else{
    // we sent some data yay
        std::cout<<"message sent" <<std::endl;
    }
}

void Connect(std::string &hostname, uint16_t port, CS2Net::Socket& sock){
    int ret = sock.Connect(&hostname, port);
    if(ret < 0){
    // something terrifying happened x_X
        if(ret == -1)
        {
            ERROR("connect error: %s", strerror(errno));
        }
        else if(ret == -3)
        {
            ERROR("connect error: %s", gai_strerror(errno));
        }
        else
        {
            ERROR("this error should never occur");
        }
    }
    else{
    // we connected yay
        std::cout<<"connection established"<<std::endl;
    }

}
std::string* Receive(CS2Net::Socket& sock){
    std::string * incoming = sock.Recv(1024, false);
    if(incoming == NULL)
    {
    // bad stuff happened
        ERROR("recv error: %s", strerror(errno));
    }
    else
    {
    // we got some data yay
        std::cout<<"message received"<<std::endl;
        return incoming;
    }
    return nullptr;
} 
