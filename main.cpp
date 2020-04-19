#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/option.hpp>

#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

#include "hello_world_api.h"

namespace po = boost::program_options;

class HelloHandler : public Pistache::Http::Handler {
public:

HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response) {
        response.send(Pistache::Http::Code::Ok, "Muie ba !!!");
    }
};

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));

    auto opts =Pistache::Http::Endpoint::options().threads(1);
    const auto server = std::make_shared<Pistache::Http::Endpoint>(addr);
    server->init(opts);

    HelloWorldApi helloWorldApi("Aici, un mesaj dubios...");
    helloWorldApi.setupEndpointHandlers(server);
    server->serve();
}
