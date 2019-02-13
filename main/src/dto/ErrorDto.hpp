//
//  ErrorDto.hpp
//  file-service
//
//  Created by Leonid on 8/13/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef ErrorDto_hpp
#define ErrorDto_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ErrorDto : public oatpp::data::mapping::type::Object {
  
  DTO_INIT(ErrorDto, Object)
  
  DTO_FIELD(String, service) = "user-service";
  DTO_FIELD(Int32, code);
  DTO_FIELD(String, error);
  DTO_FIELD(String, message);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ErrorDto_hpp */
