
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE IF NOT EXISTS AppUser (
    id                      varchar (256) PRIMARY KEY,
    username                varchar (256) NOT NULL,
    email                   varchar (256) NOT NULL,
    password                varchar (256) NOT NULL,
    role                    varchar (256) NULL,
    CONSTRAINT              UK_APPUSER_USERNAME UNIQUE (username),
    CONSTRAINT              UK_APPUSER_EMAIL UNIQUE (email)
);

INSERT INTO AppUser
(id, username, email, password, role) VALUES (uuid_generate_v4(), 'admin', 'admin@domain.com', 'admin', 'ROLE_ADMIN');
