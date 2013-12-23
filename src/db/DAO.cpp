/* 
 * File:   DAO.cpp
 * Author: xaqq
 * 
 * Created on December 23, 2013, 2:09 AM
 */

#include "DAO.hpp"

using namespace DB;

DAO::DAO()
{
}

DAO::DAO(const DAO& orig)
{
}

DAO::~DAO()
{
}
//
//static Areas DAO::getAllAreas()
//{
//    try
//    {
//        typedef odb::query<DB::Area> query;
//        typedef odb::result<DB::Area> result;
//
//        //  odb::session s;
//        DB::ptr db = DB::DBManager::instance().db();
//
//        odb::transaction t(db->begin());
//        t.tracer(odb::stderr_tracer);
//        result r(db->query<DB::Area>());
//
//        for (result::iterator i(r.begin()); i != r.end(); ++i)
//        {
//            INFO("Hey an Area is described: " << i->name() << ". Nb Go: " <<
//                    i->spawnData().size())
//                    ;
//        }
//        return true;
//    }
//    catch (const odb::recoverable &r)
//    {
//        WARN(r.what());
//    }
//    catch (const odb::exception& e)
//    {
//        ERROR(e.what());
//    }
//    return false;
//}