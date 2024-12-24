#include "../Octree/Octree.hpp"
#include "../Storage/Storage.hpp"
#include "../Container/Container.hpp"
#include "../Terminal/Terminal.hpp"
#include "../Container/FragileContainer.hpp"
#include "../Container/RefragedContainer.hpp"
#include "../Request/Request.hpp"


int main(){
    Storage st(1, 16, 16, 8, 23.4);
    Request request(st, 1500);
    std::thread requestThread(&Request::RequestQ, &request);
    requestThread.join();
}