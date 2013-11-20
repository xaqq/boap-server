
#include "Log.hpp"
#include "sql/EntityTemplate.hpp"
#include "Scheduler.hpp"
#include "sql/ISqlResult.hpp"
#include "world/EntityFactory.hpp"
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>

SqlTaskReturnType EntityTemplate::loadTemplate(sql::Connection *c, std::size_t id)
{
  sql::PreparedStatement *pstmt;
  sql::ResultSet *res;

  pstmt = c->prepareStatement("SELECT id, name, script_name, shape_id FROM entity_template WHERE id = (?)");
  pstmt->setInt(1, id);

  res = pstmt->executeQuery();
  EntityTemplate *e = new EntityTemplate();
  while (res->next())
    {
      e->id_ = res->getInt("id");
      e->name_ = res->getString("name");
      e->scriptName_ = res->getString("script_name");
      e->shape_id = res->getInt('shape_id');
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

SqlTaskReturnType EntityTemplate::loadAllTemplate(sql::Connection *c)
{
  std::shared_ptr<ISqlResult> ptr (new ISqlResult());
  std::list<EntityTemplate> *entities = new std::list<EntityTemplate>();
  try
    {
      std::shared_ptr<sql::PreparedStatement> pstmt(c->prepareStatement("SELECT id, name, script_name, shape_id FROM entity_template"));
      std::shared_ptr<sql::ResultSet> res;

      res = std::shared_ptr<sql::ResultSet>(pstmt->executeQuery());
      while (res->next())
        {
          EntityTemplate e;
          e.id_ = res->getInt("id");
          e.name_ = res->getString("name");
          e.scriptName_ = res->getString("script_name");
          e.shape_id = res->getInt("shape_id");;
          entities->push_back(std::move(e));
          INFO("SQL REPLIES: " << res->getString("name") << " with id " << res->getInt("id") << " with scriptName " << res->getString("script_name"));
        }

      ptr->error_ = false;
      ptr->result_ = entities;

      return ptr;
    }
  catch (sql::SQLException &e)
    {
      ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
      ptr->error_ = true;
      delete entities;
      ptr->result_ = nullptr;
      return ptr;
    }
}