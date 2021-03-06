#include "hello_world_api.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <writer.h>

HelloWorldApi::HelloWorldApi() : d_returnableMessage("Hai, salut!") {}

HelloWorldApi::HelloWorldApi(std::string givenMessage) : d_returnableMessage(givenMessage) {}

void HelloWorldApi::greetAll(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    rapidjson::StringBuffer outputBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(outputBuffer);
    if (writer.StartObject()) {
        writer.Key("currentReturnableMessage");
        writer.String(d_returnableMessage.c_str());

        writer.EndObject();
    }

    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    response.send(
        Pistache::Http::Code::Ok,
        outputBuffer.GetString()
    );
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

void HelloWorldApi::changeGreet(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    rapidjson::Document document;
    document.Parse(request.body().c_str());

    if (document.HasMember("newGreeting") && !document["newGreeting"].IsNull()) {
        d_returnableMessage = document["newGreeting"].GetString();
    }

    response.send(Pistache::Http::Code::Ok);
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
    Pistache::Rest::Routes::Post(
            router,
            "/changeGreeting",
            Pistache::Rest::Routes::bind(&HelloWorldApi::changeGreet, this)
    );

    endpointSPtr->setHandler(router.handler());
}
