#include "hello_world_api.h"

HelloWorldApi::HelloWorldApi() : d_returnableMessage("Hai, salut!") {}

HelloWorldApi::HelloWorldApi(std::string givenMessage) : d_returnableMessage(givenMessage) {}

void HelloWorldApi::greetAll(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok, "Muie la toti ba!!!..." + d_returnableMessage);
}

void HelloWorldApi::greetName(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    response.send(
    Pistache::Http::Code::Ok,
    "Muie ba " + request.param(":name").as<std::string>() + "!!!..." + d_returnableMessage
    );
}

void HelloWorldApi::greetNumber(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    response.send(
    Pistache::Http::Code::Ok,
    "Muie la toti " + request.param(":number").as<std::string>() + " ba!!!..." + d_returnableMessage
    );
}

void HelloWorldApi::setupEndpointHandlers(const std::shared_ptr<Pistache::Http::Endpoint>& endpointSPtr) {
    Pistache::Rest::Router router;

    Pistache::Rest::Routes::Get(
            router,
            "/greet/all",
            Pistache::Rest::Routes::bind(&HelloWorldApi::greetAll, this)
    );
    Pistache::Rest::Routes::Get(
            router,
            "/greet/person/:name",
            Pistache::Rest::Routes::bind(&HelloWorldApi::greetName, this)
    );
    Pistache::Rest::Routes::Get(
            router,
            "/greet/groupOf/:number",
            Pistache::Rest::Routes::bind(&HelloWorldApi::greetNumber, this)
    );

    endpointSPtr->setHandler(router.handler());
}
