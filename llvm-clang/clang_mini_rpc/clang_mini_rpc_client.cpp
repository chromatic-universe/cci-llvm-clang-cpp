//clang_mini_rpc_client.cpp   william k. johnson

#include <iostream>
#include <memory>
#include <string>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen-cpp/cci_mini_clang_rpc.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace shared;
using cci_rpc = cci_mini_clang_rpcClient;

int main( int argc , char* argv[] )
{
    boost::shared_ptr<TTransport> socket( new TSocket( "localhost" , 9090 ) );
    boost::shared_ptr<TTransport> transport( new TBufferedTransport( socket) );
    boost::shared_ptr<TProtocol> protocol( new TBinaryProtocol(transport ) );

    std::unique_ptr<cci_rpc> clang_rpc_client( new cci_rpc( protocol ) );

    try
    {
        transport->open();

        std::string str;
        std::string str_idx( "foo" );
        try
        {
            clang_rpc_client->perform_diag( str , str_idx );
            std::cout << str << "\n";
        }
        catch( invalid_clang_op& err )
        {
            std::cerr << err << "\n";
        }

        transport->close();

    }
    catch ( TException& tx )
    {
        std::cerr << "error: " << tx.what() << std::endl;
    }

    return 0;
}
