#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

#include "hello_world_api.h"

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));

    auto endpointOptions = Pistache::Http::Endpoint::options().threads(1);
    const auto server = std::make_shared<Pistache::Http::Endpoint>(addr);

    server->init(endpointOptions);

    HelloWorldApi helloWorldApi;
    helloWorldApi.setupEndpointHandlers(server);

    server->serve();
}
