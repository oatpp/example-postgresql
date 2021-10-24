
#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "dto/ConfigDto.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

#include "oatpp/core/base/CommandLineArguments.hpp"

#include <cstdlib>

class AppComponent {
private:
  oatpp::base::CommandLineArguments m_cmdArgs;
public:
  AppComponent(const oatpp::base::CommandLineArguments& cmdArgs)
    : m_cmdArgs(cmdArgs)
  {}
public:
  
  /**
   * This should be configured through config-server ex. Consul
   */
  OATPP_CREATE_COMPONENT(oatpp::Object<ConfigDto>, config)([this] {

    const char* configPath = CONFIG_PATH;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    
    oatpp::String configText = oatpp::String::loadFromFile(configPath);
    if (configText) {

      auto profiles = objectMapper->readFromString<oatpp::Fields<oatpp::Object<ConfigDto>>>(configText);

      const char *profileArg = std::getenv("CONFIG_PROFILE"); // first read from env variable
      if (profileArg == nullptr) {
        profileArg = m_cmdArgs.getNamedArgumentValue("--profile", "dev"); // if no env varioable get from command line
      }

      OATPP_LOGD("Server", "Loading configuration profile '%s'", profileArg);

      auto profile = profiles.getValueByKey(profileArg, nullptr);
      if(!profile) {
        throw std::runtime_error("No configuration profile found. Server won't run.");
      }
      return profile;
      
    }
    
    OATPP_LOGE("AppComponent", "Can't load configuration file at path '%s'", configPath);
    throw std::runtime_error("[AppComponent]: Can't load configuration file");
    
  }());
  
};

#endif /* AppComponent_hpp */
