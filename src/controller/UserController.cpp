#include "UserController.hpp"

#include <stdio.h>

void UserController::assertUid(const oatpp::String& uid) {
  
  OATPP_ASSERT_HTTP(uid && uid->getSize() > 0, Status::CODE_400, "UID can't be empty");
  
  for(v_int32 i = 0; i < uid->getSize(); i++) {
    v_char8 a = uid->getData()[i];
    bool validChar = (a >= 'a' && a <= 'z') || (a >= '0' && a <= '9') || a == '-';
    if(!validChar) {
      throw std::runtime_error("Valid characters for UID are: [a-z], [0-9], and symbols: -");
    }
  }
  
}

void UserController::assertLogin(const oatpp::String& login) {
  
  OATPP_ASSERT_HTTP(login && login->getSize() > 0, Status::CODE_400, "Login can't be empty");
  
  for(v_int32 i = 0; i < login->getSize(); i++) {
    v_char8 a = login->getData()[i];
    bool validChar = (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9');
    if(!validChar) {
      throw std::runtime_error("Valid characters for login are: [a-z], [A-Z], [0-9]");
    }
  }
  
}

void UserController::assertEmail(const oatpp::String& email) {
  
  OATPP_ASSERT_HTTP(email && email->getSize() > 0, Status::CODE_400, "Email can't be empty");
  
  for(v_int32 i = 0; i < email->getSize(); i++) {
    v_char8 a = email->getData()[i];
    bool validChar = (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || a == '@' || a == '.' || a == '_' || a == '-';
    if(!validChar) {
      throw std::runtime_error("Valid characters for email are: [a-z], [A-Z], [0-9], and symbols: @._-");
    }
  }
  
}

void UserController::assertPassword(const oatpp::String& password) {
  
  OATPP_ASSERT_HTTP(password && password->getSize() > 0, Status::CODE_400, "Password can't be empty");
  
  for(v_int32 i = 0; i < password->getSize(); i++) {
    v_char8 a = password->getData()[i];
    bool validChar = (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || a == '!' || a == '.' || a == '_' || a == '-';
    if(!validChar) {
      throw std::runtime_error("Valid characters for password are: [a-z], [A-Z], [0-9], and symbols: !._-");
    }
  }
  
}

