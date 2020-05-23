#ifndef UserController_hpp
#define UserController_hpp

#include "db/Database.hpp"

#include "dto/ErrorDto.hpp"
#include "dto/ConfigDto.hpp"

#include "oatpp-swagger/Types.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <iostream>
#include <fstream>

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- codegen begin

/**
 *  EXAMPLE ApiController
 *  Basic examples of howto create ENDPOINTs
 *  More details on oatpp.io
 */
class UserController : public oatpp::web::server::api::ApiController {
protected:
  UserController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  OATPP_COMPONENT(oatpp::Object<ConfigDto>, config); // Inject config
  OATPP_COMPONENT(std::shared_ptr<Database>, database); // Inject database
private:
  void assertUid(const oatpp::String& uid);
  void assertLogin(const oatpp::String& login);
  void assertEmail(const oatpp::String& email);
  void assertPassword(const oatpp::String& password);
public:
  
  /**
   *  Inject @objectMapper component here as default parameter
   *  Do not return bare Controllable* object! use shared_ptr!
   */
  static std::shared_ptr<UserController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)){
    return std::shared_ptr<UserController>(new UserController(objectMapper));
  }
  
  ENDPOINT_INFO(createUser) {
    info->summary = "Create new User";
    info->addConsumes<oatpp::Object<UserDto>>("application/json");
    info->addResponse<oatpp::Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<oatpp::Object<ErrorDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "/users", createUser,
           BODY_DTO(Object<UserDto>, user)) {
    assertLogin(user->login);
    assertEmail(user->email);
    assertPassword(user->password);
    auto createdUser = database->createUser(user);
    OATPP_ASSERT_HTTP(createdUser, Status::CODE_500, "User was not created");
    return createDtoResponse(Status::CODE_200, createdUser);
  }
  
  
  ENDPOINT_INFO(getUserByUid) {
    info->summary = "Get user by UID";
    info->addResponse<oatpp::Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<oatpp::Object<ErrorDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "/users/uid/{userId}", getUserByUid,
           PATH(String, userId)) {
    assertUid(userId);
    auto user = database->getUserByUid(userId);
    OATPP_ASSERT_HTTP(user, Status::CODE_404, "User not found");
    return createDtoResponse(Status::CODE_200, user);
  }
  
  
  ENDPOINT_INFO(getUserByLogin) {
    info->summary = "Get user by Login";
    info->addResponse<oatpp::Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<oatpp::Object<ErrorDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "/users/login/{login}", getUserByLogin,
           PATH(String, login)) {
    assertLogin(login);
    auto user = database->getUserByLogin(login);
    OATPP_ASSERT_HTTP(user, Status::CODE_404, "User not found");
    return createDtoResponse(Status::CODE_200, user);
  }
  
  
  ENDPOINT_INFO(getUserByEmail) {
    info->summary = "Get user by Email";
    info->addResponse<oatpp::Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<oatpp::Object<ErrorDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "/users/email/{email}", getUserByEmail,
           PATH(String, email)) {
    assertEmail(email);
    auto user = database->getUserByEmail(email);
    OATPP_ASSERT_HTTP(user, Status::CODE_404, "User not found");
    return createDtoResponse(Status::CODE_200, user);
  }
  
  // TODO Insert Your endpoints here !!!

};

#include OATPP_CODEGEN_END(ApiController) //<-- codegen end

#endif /* UserController_hpp */
