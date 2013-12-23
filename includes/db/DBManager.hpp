/* 
 * File:   DBManager.hpp
 * Author: xaqq
 *
 * Created on December 20, 2013, 8:10 PM
 */

#ifndef DBMANAGER_HPP
#define	DBMANAGER_HPP

#include <memory>
#include "odb/core.hxx"
#include "odb/database.hxx"
#include "odb/transaction.hxx"
#include "odb/mysql/database.hxx"

namespace DB
{

    /**
     * DB::ptr is a database pointer type
     */
    typedef std::shared_ptr<odb::database> DatabasePtr;
    
    /**
     * This class is the database manager. Basically, it is implemented as a singleton to allow anyone
     * to get a database connection handle.
     * 
     * It uses a MySQL ODB connection pool.
     * 
     * The DBManager is thread safe.
     */
    class DBManager
    {
    public:
        DBManager(const DBManager&) = delete;
        virtual ~DBManager();

        /**
         * Access the single instance of the DBManager
         * @return DBManager instance
         */
        static DBManager &instance();
        
        /**
         * Return a database handler. When using the returned pointer, a connection from the pool
         * will be used.
         * @return  a database handler
         */
        std::shared_ptr<odb::database> db()
        {
            return database_;
        }
        
    private:
        /**
         * Constructor is private: singleton
         */
        DBManager();
        
        static std::shared_ptr<DBManager> instance_;
        
        /**
         * Connection factory that works as a connection pool.
         */
        std::auto_ptr<odb::mysql::connection_factory> connectionFactory_;

        /**
         * A thread safe, multi connection database instance (that rely on the connectionFactory_)
         */
        std::shared_ptr<odb::database> database_;

    };
}
#endif	/* DBMANAGER_HPP */

