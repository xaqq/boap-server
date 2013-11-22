
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
  std::shared_ptr<ISqlResult> resultWrapper(new ISqlResult());
  if (!c)
    return resultWrapper;

  EntityTemplate *eTpl = new EntityTemplate();

  try
    {
      std::shared_ptr<sql::PreparedStatement> pstmt(c->prepareStatement("SELECT id, name, script_name, shape_id, affect_nav_mesh FROM entity_template WHERE id = (?)"));
      std::shared_ptr<sql::ResultSet> res;
      pstmt->setInt(1, id);

      res = std::shared_ptr<sql::ResultSet > (pstmt->executeQuery());
      while (res->next())
        {
          eTpl->id_ = res->getInt("id");
          eTpl->name_ = res->getString("name");
          eTpl->scriptName_ = res->getString("script_name");
          eTpl->shape_id = res->getInt("shape_id");
          eTpl->affectNavMesh_ = res->getBoolean("affect_nav_mesh");
          INFO("SQL REPLIES: " << res->getString("name") << " with id " << res->getInt("id") << " with scriptName " << res->getString("script_name"));
        }

      resultWrapper->error_ = false;
      resultWrapper->result_ = eTpl;

      return resultWrapper;
    }
  catch (sql::SQLException &e)
    {
      ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
      resultWrapper->error_ = true;
      resultWrapper->result_ = nullptr;
      delete eTpl;
      return resultWrapper;
    }
}

SqlTaskReturnType EntityTemplate::loadAllTemplate(sql::Connection *c)
{
  std::shared_ptr<ISqlResult> ptr(new ISqlResult());
  std::list<EntityTemplate> *entities = new std::list<EntityTemplate > ();
  try
    {
      std::shared_ptr<sql::PreparedStatement> pstmt(c->prepareStatement("SELECT id, name, script_name, shape_id, affect_nav_mesh FROM entity_template"));
      std::shared_ptr<sql::ResultSet> res;

      res = std::shared_ptr<sql::ResultSet > (pstmt->executeQuery());
      while (res->next())
        {
          EntityTemplate e;
          e.id_ = res->getInt("id");
          e.name_ = res->getString("name");
          e.scriptName_ = res->getString("script_name");
          e.shape_id = res->getInt("shape_id");
          e.affectNavMesh_ = res->getBoolean("affect_nav_mesh");
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