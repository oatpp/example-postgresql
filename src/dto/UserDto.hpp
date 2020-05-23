
#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class UserDto : public oatpp::DTO {
  
  DTO_INIT(UserDto, DTO)
  
  DTO_FIELD(String, userId);
  DTO_FIELD(String, login);
  DTO_FIELD(String, password);
  DTO_FIELD(String, email);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
