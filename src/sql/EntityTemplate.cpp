
#include "Log.hpp"
#include "sql/EntityTemplate.hpp"
#include "Scheduler.hpp"
#include "sql/ISqlResult.hpp"
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

SqlTaskReturnType EntityTemplate::loadTemplate(sql::Connection *c, std::size_t id)
{
  sql::PreparedStatement *pstmt;
  sql::ResultSet *res;

  pstmt = c->prepareStatement("SELECT * FROM entity_template WHERE id = (?)");
  pstmt->setInt(1, id);

  res = pstmt->executeQuery();
  EntityTemplate *e = new EntityTemplate();
  while (res->next())
    {
      e->id_ = res->getInt("id");
      e->name_ = res->getString("name");
      e->scriptName_ = res->getString("script_name");
      INFO("SQL REPLIES: " << res->getString("name") << " with id " << res->getInt("id") << " with scriptName " << res->getString("script_name"));
    }
  ISqlResult *ptr = new ISqlResult();
  ptr->error_ = false;
  ptr->result_ = e;

  delete res;
  delete pstmt;
 // std::shared_ptr<ISqlResult> temp(ptr);
  //DEBUG("BOAP:" << temp.get());
  return SqlTaskReturnType(ptr);
}