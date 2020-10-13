
#include "controller/UserController.hpp"
#include "AppComponent.hpp"
#include "DatabaseComponent.hpp"
#include "ServiceComponent.hpp"
#include "SwaggerComponent.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run(const oatpp::base::CommandLineArguments& args) {

  AppComponent appComponent(args);
  ServiceComponent serviceComponent;
  SwaggerComponent swaggerComponent;
  DatabaseComponent databaseComponent;

  /* create ApiControllers and add endpoints to router */

  auto router = serviceComponent.httpRouter.getObject();
  auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();

  auto userController = UserController::createShared();
  userController->addEndpointsToRouter(router);

  docEndpoints->pushBackAll(userController->getEndpoints()); // Add userController to swagger

  auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints);
  swaggerController->addEndpointsToRouter(router);

  /* create server */

  oatpp::network::Server server(serviceComponent.serverConnectionProvider.getObject(),
                                serviceComponent.serverConnectionHandler.getObject());

  OATPP_LOGD("Server", "Running on port %s...", serviceComponent.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());

  server.run();

}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  run(oatpp::base::CommandLineArguments(argc, argv));

  oatpp::base::Environment::destroy();

  return 0;
}
