//
//  SwaggerComponent.hpp
//  file-service
//
//  Created by Leonid on 8/13/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef SwaggerComponent_hpp
#define SwaggerComponent_hpp

#include "dto/ConfigDto.hpp"

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include "oatpp/core/macro/component.hpp"

class SwaggerComponent {
public:
  
  /**
   *  General API docs info
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
    OATPP_COMPONENT(ConfigDto::ObjectWrapper, config); // Get config component
    
    oatpp::swagger::DocumentInfo::Builder builder;
    
    builder
    .setTitle("File upload service")
    .setDescription("Service which uploads files to S3-compatible storage")
    .setVersion("1.0")
    
    .addServer("http://localhost:" + oatpp::utils::conversion::int32ToStr(config->port), "server on localhost");
    
    return builder.build();
    
  }());
  
  
  /**
   *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
    // Make sure to specify correct full path to oatpp-swagger/res folder !!!
    return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
  }());
  
};

#endif /* SwaggerComponent_hpp */
