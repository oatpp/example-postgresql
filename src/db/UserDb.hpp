
#ifndef EXAMPLE_POSTGRESQL_USERDB_HPP
#define EXAMPLE_POSTGRESQL_USERDB_HPP

#include "dto/UserDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
class UserDb : public oatpp::orm::DbClient {
public:

  UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("UserDb", "Migration - OK. Version=%d.", version);

  }

  QUERY(createUser,
        "INSERT INTO AppUser"
        "(id, username, email, password, role) VALUES "
        "(uuid_generate_v4(), :user.username, :user.email, :user.password, :user.role)"
        "RETURNING *;",
        PREPARE(true), // user prepared statement!
        PARAM(oatpp::Object<UserDto>, user))

  QUERY(updateUser,
        "UPDATE AppUser "
        "SET "
        " username=:user.username, "
        " email=:user.email, "
        " password=:user.password, "
        " role=:user.role "
        "WHERE "
        " id=:user.id "
        "RETURNING *;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::Object<UserDto>, user))

  QUERY(getUserById,
        "SELECT * FROM AppUser WHERE id=:id;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::String, id))

  QUERY(getAllUsers,
        "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deleteUserById,
        "DELETE FROM AppUser WHERE id=:id;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::String, id))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //EXAMPLE_POSTGRESQL_USERDB_HPP
