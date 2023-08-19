#define TEST_NO_MAIN 1

#include "ServerEventsTest.h"
#include "acutest.h"
#include <thread>

namespace Casper
{

void Hello_SSE_Test(void)
{
    ServerEventsClient sseClient("http://93.190.141.13:9999");
    sseClient.listen();
    // Block the main thread to keep the program running
}

} // namespace Casper