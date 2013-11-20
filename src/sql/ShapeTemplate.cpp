
#include "Log.hpp"
#include "Scheduler.hpp"
#include "sql/ISqlResult.hpp"
#include "world/EntityFactory.hpp"
#include "sql/ShapeTemplate.hpp"
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>

SqlTaskReturnType ShapeTemplate::loadTemplate(sql::Connection *c, std::size_t id)
{
  std::shared_ptr<ISqlResult> resultWrapper(new ISqlResult());

  if (!c)
    return resultWrapper;

  std::list<EntityTemplate> *entities = new std::list<EntityTemplate > ();
  try
    {
      std::shared_ptr<sql::PreparedStatement> pstmt(c->prepareStatement("SELECT id, name, param1, param2, param3 FROM shape"));
      std::shared_ptr<sql::ResultSet> res;

      res = std::shared_ptr<sql::ResultSet > (pstmt->executeQuery());
      while (res->next())
        {
          ShapeTemplate shape;
          shape.id_ = res->getInt("id");
          shape.name_ = res->getString("name");
          shape.params_[0] = res->getDouble("param1");
          shape.params_[1] = res->getDouble("param2");
          shape.params_[2] = res->getDouble("param3");
        }

      resultWrapper->error_ = false;
      resultWrapper->result_ = entities;

      return resultWrapper;
    }
  catch (sql::SQLException &e)
    {
      ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
      resultWrapper->error_ = true;
      delete entities;
      resultWrapper->result_ = nullptr;
      return resultWrapper;
    }
}

SqlTaskReturnType ShapeTemplate::loadAllTemplate(sql::Connection *c)
{
  std::shared_ptr<ISqlResult> resultWrapper(new ISqlResult());
  if (!c)
    return resultWrapper;

  std::list<ShapeTemplate> *shapes = new std::list<ShapeTemplate> ();
  try
    {
      std::shared_ptr<sql::PreparedStatement> pstmt(c->prepareStatement("SELECT id, name, param1, param2, param3 FROM shape"));
      std::shared_ptr<sql::ResultSet> res;

      res = std::shared_ptr<sql::ResultSet > (pstmt->executeQuery());
      while (res->next())
        {
          ShapeTemplate shape;
          shape.id_ = res->getInt("id");
          shape.name_ = res->getString("name");
          shape.params_[0] = res->getDouble("param1");
          shape.params_[1] = res->getDouble("param2");
          shape.params_[2] = res->getDouble("param3");
          shapes->push_back(std::move(shape));
        }

      resultWrapper->error_ = false;
      resultWrapper->result_ = shapes;

      return resultWrapper;
    }
  catch (sql::SQLException &e)
    {
      ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
      resultWrapper->error_ = true;
      delete shapes;
      resultWrapper->result_ = nullptr;
      return resultWrapper;
    }
}