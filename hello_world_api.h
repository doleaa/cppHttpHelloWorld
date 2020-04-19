#ifndef HELLOWORLD_HELLO_WORLD_API_H
#define HELLOWORLD_HELLO_WORLD_API_H

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

#include <string>

class HelloWorldApi {
public:
    HelloWorldApi();
    explicit HelloWorldApi(std::string givenMessage);

    void setupEndpointHandlers(const std::shared_ptr<Pistache::Http::Endpoint>& endpointSPtr);

    void greetAll(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void greetName(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void greetNumber(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

private:
    std::string d_returnableMessage;
};


#endif //HELLOWORLD_HELLO_WORLD_API_H
