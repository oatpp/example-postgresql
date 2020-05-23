
#ifndef Database_hpp
#define Database_hpp

#include "dto/UserDto.hpp"

#include "oatpp/core/Types.hpp"

#include <libpq-fe.h>
#include <mutex>

class Database {
private:
  static const char* DDL;
  static const char* SQL_INSERT_USER;
  static const char* SQL_SELECT_USER_BY_USERID;
  static const char* SQL_SELECT_USER_BY_LOGIN;
  static const char* SQL_SELECT_USER_BY_EMAIL;
private:
  
  class ResultWrapper {
  private:
    PGresult* m_result;
  public:
    
    ResultWrapper(PGresult* result)
      : m_result(result)
    {}
    
    ~ResultWrapper() {
      if(m_result != nullptr) {
        PQclear(m_result);
        m_result = nullptr;
      }
    }
    
    PGresult* get() const {
      return m_result;
    }
    
  };
private:
  PGconn* m_connection;
  oatpp::String m_connectionString;
  std::mutex m_mutex;
private:
  void tryReconnect();
  oatpp::Object<UserDto> readUserFromResult(const ResultWrapper& result, v_int32 index);
  bool checkResultOrThrow(const ResultWrapper& result);
public:
  void connect();
  void disconnect();
public:
  
  Database(const oatpp::String& dbHost,
           const oatpp::String& dbUser,
           const oatpp::String& dbPassword,
           const oatpp::String& dbName);
  
  ~Database();
  
  void init();
  
  oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto>& user);
  
  oatpp::Object<UserDto> getUserByUid(const oatpp::String& uid);
  oatpp::Object<UserDto> getUserByLogin(const oatpp::String& login);
  oatpp::Object<UserDto> getUserByEmail(const oatpp::String& email);
  
};

#endif /* Database_hpp */
