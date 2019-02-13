//
//  ConfigDto.hpp
//  file-service
//
//  Created by Leonid on 8/12/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef ConfigDto_hpp
#define ConfigDto_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigDto : public oatpp::data::mapping::type::Object {
  
  DTO_INIT(ConfigDto, Object)
  
  DTO_FIELD(Int32, port);
  DTO_FIELD(String, swaggerHost);
  DTO_FIELD(String, dbHost);
  DTO_FIELD(String, dbUser);
  DTO_FIELD(String, dbPass);
  DTO_FIELD(String, dbName);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ConfigDto_hpp */
