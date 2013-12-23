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

        template<typename T>
        static std::vector<std::shared_ptr<T >> findAll()
        {
            try
            {
                std::vector < std::shared_ptr < T >> ret;
                DatabasePtr db = DBManager::instance().db();

                odb::transaction t(db->begin());
                t.tracer(odb::stderr_tracer);
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
                std::vector < std::shared_ptr < T >> ret;
                DatabasePtr db = DBManager::instance().db();

                odb::transaction t(db->begin());
                t.tracer(odb::stderr_tracer);

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
    private:
    };
}

#endif	/* DAO_HPP */

