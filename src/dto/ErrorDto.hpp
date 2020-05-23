
#ifndef ErrorDto_hpp
#define ErrorDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ErrorDto : public oatpp::DTO {
  
  DTO_INIT(ErrorDto, DTO)
  
  DTO_FIELD(String, service) = "example-postgresql: user-service";
  DTO_FIELD(Int32, code);
  DTO_FIELD(String, error);
  DTO_FIELD(String, message);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ErrorDto_hpp */
