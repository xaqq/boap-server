/* 
 * File:   DAO.hpp
 * Author: xaqq
 *
 * Created on December 23, 2013, 2:09 AM
 */

#ifndef DAO_HPP
#define	DAO_HPP

#include "Log.hpp"
#include <memory>
#include <vector>

#include "odb/core.hxx"
#include "odb/result.hxx"
#include "odb/exceptions.hxx"
#include "odb/exceptions.hxx"
#include "odb/query.hxx"


#include "DBManager.hpp"
#include "Area.hpp"
#include "AreaInstance.hpp"
#include "GameObject.hpp"
#include "GameObjectTemplate.hpp"
#include "GameObjectSpawn.hpp"
#include "db/Geometry2dBox.hpp"
#include "db/Geometry3dBox.hpp"
#include "db/GeometrySphere.hpp"


#include "odb_gen/Account_odb.h"
#include "odb_gen/Area_odb.h"
#include "odb_gen/AreaInstance_odb.h"
#include "odb_gen/GameObject_odb.h"
#include "odb_gen/GameObjectTemplate_odb.h"
#include "odb_gen/GameObjectSpawn_odb.h"
#include "odb_gen/GeometryObject_odb.h"
#include "odb_gen/Geometry3dBox_odb.h"
#include "odb_gen/Geometry2dBox_odb.h"
#include "odb_gen/GeometrySphere_odb.h"
#include "odb_gen/StatSheet_odb.h"


namespace DB
{

    typedef std::vector<std::shared_ptr<Area >> Areas;
    typedef std::vector<std::shared_ptr<GameObjectSpawn >> GameObjectSpawnList;

    typedef std::shared_ptr<AreaInstance> AreaInstancePtr;
    typedef std::shared_ptr<Area> AreaPtr;
    typedef std::shared_ptr<GameObject> GameObjectPtr;
    typedef std::shared_ptr<GameObjectTemplate> GameObjectTemplatePtr;
    typedef std::shared_ptr<GeometryObject> GeometryObjectPtr;
    typedef std::shared_ptr<StatSheet> StatSheetPtr;

    /**
     * A Data Access Object that hide the complexity of the ORM.
     * 
     * It's also supposed to be the "front-end" header for database related class.
     */
    class DAO
    {
    public:
        DAO();
        DAO(const DAO& orig);
        virtual ~DAO();

        template<typename T, typename PrimaryKey>
        static std::shared_ptr<T > find(const PrimaryKey &id)
        {
            try
            {
                DatabasePtr db = DBManager::instance().db();

                odb::transaction t(db->begin());
                // t.tracer(odb::stderr_tracer);
                std::shared_ptr<T> ptr = db->load<T>(id);
                return ptr;
            }
            catch (const odb::recoverable &recoverableException)
            {
                WARN(recoverableException.what());
            }
            catch (const odb::exception& e)
            {
                ERROR(e.what());
            }
        }

        template<typename T>
        static std::vector<std::shared_ptr<T >> findAll()
        {
            try
            {
                std::vector < std::shared_ptr < T >> ret;
                DatabasePtr db = DBManager::instance().db();

                odb::transaction t(db->begin());
                // t.tracer(odb::stderr_tracer);
                odb::result<T> r(db->query<T>());

                for (typename odb::result<T>::iterator i(r.begin()); i != r.end(); ++i)
                {
                    ret.push_back(i.load());
                }
                return ret;
            }
            catch (const odb::recoverable &recoverableException)
            {
                WARN(recoverableException.what());
            }
            catch (const odb::exception& e)
            {
                ERROR(e.what());
            }
        }

        template<typename T>
        static bool persist(std::shared_ptr<T> object)
        {
            try
            {
                DatabasePtr db = DBManager::instance().db();

                odb::transaction t(db->begin());
                //      t.tracer(odb::stderr_tracer);

                db->persist<T>(object);
                t.commit();
                return true;
            }
            catch (const odb::recoverable &recoverableException)
            {
                WARN(recoverableException.what());
            }
            catch (const odb::exception& e)
            {
                ERROR(e.what());
            }
            return false;
        }

        template<typename T>
        static bool erase(std::shared_ptr<T> object)
        {
            try
            {
                DatabasePtr db = DBManager::instance().db();

                odb::transaction t(db->begin());
                t.tracer(odb::stderr_tracer);

                db->erase<T>(object);
                t.commit();
                return true;
            }
            catch (const odb::recoverable &recoverableException)
            {
                WARN(recoverableException.what());
            }
            catch (const odb::exception& e)
            {
                ERROR(e.what());
            }
            return false;
        }

        template<typename T>
        static bool update(std::shared_ptr<T> object)
        {
            try
            {
                DatabasePtr db = DBManager::instance().db();

                odb::transaction t(db->begin());
                //  t.tracer(odb::stderr_tracer);

                db->update<T>(object);
                t.commit();
                return true;
            }
            catch (const odb::recoverable &recoverableException)
            {
                WARN(recoverableException.what());
            }
            catch (const odb::exception& e)
            {
                ERROR(e.what());
            }
            return false;
        }

        static GameObjectSpawnList GOSpawnForArea(AreaPtr a)
        {
            GameObjectSpawnList ret;
            try
            {
                DatabasePtr db = DBManager::instance().db();

                odb::transaction t(db->begin());
                // t.tracer(odb::stderr_tracer);

                for (auto &spawnInfoWeakPtr : a->goSpawnData_)
                {
                    ret.push_back(spawnInfoWeakPtr.load());
                }
                return ret;
            }
            catch (const odb::recoverable &recoverableException)
            {
                WARN(recoverableException.what());
            }
            catch (const odb::exception& e)
            {
                ERROR(e.what());
            }
            return ret;
        }

    private:
    };
}

#endif	/* DAO_HPP */

