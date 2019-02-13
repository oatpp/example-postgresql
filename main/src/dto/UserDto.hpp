//
//  UserDto.hpp
//  crud
//
//  Created by Leonid on 3/13/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class UserDto : public oatpp::data::mapping::type::Object {
  
  DTO_INIT(UserDto, Object)
  
  DTO_FIELD(String, userId);
  DTO_FIELD(String, login);
  DTO_FIELD(String, password);
  DTO_FIELD(String, email);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
