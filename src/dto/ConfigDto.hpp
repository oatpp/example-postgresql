
#ifndef ConfigDto_hpp
#define ConfigDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigDto : public oatpp::DTO {
  
  DTO_INIT(ConfigDto, DTO)
  
  DTO_FIELD(Int32, port);
  DTO_FIELD(String, swaggerHost);
  DTO_FIELD(String, dbHost);
  DTO_FIELD(String, dbUser);
  DTO_FIELD(String, dbPass);
  DTO_FIELD(String, dbName);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ConfigDto_hpp */
