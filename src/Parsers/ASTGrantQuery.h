#pragma once

#include <Parsers/IAST.h>
#include "src/Access/AccessRightsElement.h"
#include <Parsers/ASTQueryWithOnCluster.h>


namespace DB
{
class ASTRolesOrUsersSet;


/** GRANT access_type[(column_name [,...])] [,...] ON {db.table|db.*|*.*|table|*} TO {user_name | CURRENT_USER} [,...] [WITH GRANT OPTION]
  * REVOKE access_type[(column_name [,...])] [,...] ON {db.table|db.*|*.*|table|*} FROM {user_name | CURRENT_USER} [,...] | ALL | ALL EXCEPT {user_name | CURRENT_USER} [,...]
  *
  * GRANT role [,...] TO {user_name | role_name | CURRENT_USER} [,...] [WITH ADMIN OPTION]
  * REVOKE [ADMIN OPTION FOR] role [,...] FROM {user_name | role_name | CURRENT_USER} [,...] | ALL | ALL EXCEPT {user_name | role_name | CURRENT_USER} [,...]
  */
class ASTGrantQuery : public IAST, public ASTQueryWithOnCluster
{
public:
    enum class Kind
    {
        GRANT,
        REVOKE,
    };
    Kind kind = Kind::GRANT;
    bool attach = false;
    AccessRightsElements access_rights_elements;
    std::shared_ptr<ASTRolesOrUsersSet> roles;
    std::shared_ptr<ASTRolesOrUsersSet> to_roles;
    bool grant_option = false;
    bool admin_option = false;

    String getID(char) const override;
    ASTPtr clone() const override;
    void formatImpl(const FormatSettings & settings, FormatState &, FormatStateStacked) const override;
    void replaceCurrentUserTagWithName(const String & current_user_name) const;
    ASTPtr getRewrittenASTWithoutOnCluster(const std::string &) const override { return removeOnCluster<ASTGrantQuery>(clone()); }
};
}
