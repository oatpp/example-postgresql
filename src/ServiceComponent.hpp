
#ifndef ServiceComponent_hpp
#define ServiceComponent_hpp

#include "dto/ConfigDto.hpp"

#include "db/Database.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"

class ServiceComponent {
public:
  
  class ErrorHandler : public oatpp::web::server::handler::ErrorHandler {
  public:
    typedef oatpp::web::protocol::http::outgoing::Response OutgoingResponse;
    typedef oatpp::web::protocol::http::Status Status;
    typedef oatpp::web::protocol::http::outgoing::ResponseFactory ResponseFactory;
  private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;
  public:
    
    ErrorHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper)
      : m_objectMapper(objectMapper)
    {}
    
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);
    
    
    std::shared_ptr<OutgoingResponse> handleError(const Status& status, const oatpp::String& message, const Headers& headers) override {

      auto error = ErrorDto::createShared();
      error->code = 500;
      error->error = "Unhandled Error";
      error->message = message;

      auto response = ResponseFactory::createResponse(Status::CODE_500, error, m_objectMapper);

      for(const auto& pair : headers.getAll()) {
        response->putHeader(pair.first, pair.second);
      }

      return response;

    }
    
  };
  
public:
  
  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());
  
  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
    OATPP_COMPONENT(oatpp::Object<ConfigDto>, config); // Get config component
    return oatpp::network::server::SimpleTCPConnectionProvider::createShared(config->port);
  }());
  
  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
    return oatpp::web::server::HttpRouter::createShared();
  }());
  
  /**
   *  Create ConnectionHandler component which uses Router component to route requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::server::ConnectionHandler>, serverConnectionHandler)([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper); // get ObjectMapper component
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
    connectionHandler->setErrorHandler(std::make_shared<ErrorHandler>(objectMapper));
    return connectionHandler;
  }());
  
  OATPP_CREATE_COMPONENT(std::shared_ptr<Database>, database)([] {
    OATPP_COMPONENT(oatpp::Object<ConfigDto>, config); // Get config component
    auto db = std::make_shared<Database>(config->dbHost, config->dbUser, config->dbPass, config->dbName);
    db->connect();
    db->init();
    return db;
  }());

};

#endif /* ServiceComponent_hpp */
