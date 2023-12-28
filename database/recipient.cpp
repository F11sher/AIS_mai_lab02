#include "recipient.h"
#include "database.h"
#include "../config/config.h"

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>
#include <exception>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace database
{

    void Recipient::init()
    {
        try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_delivery(session);
            create_delivery << "CREATE TABLE IF NOT EXISTS `Recipient` (`id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                        << "`user_id` INT NOT NULL,"
                        << "`delivery_id` INT NOT NULL,"
                        << "`first_name` VARCHAR(256) NOT NULL,"
                        << "`last_name` VARCHAR(256) NOT NULL,"
                        << "`phone_number` VARCHAR(256) NOT NULL);",
                now;
          std::cout << "Recipient table initialized successfully." << std::endl;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    Poco::JSON::Object::Ptr Recipient::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        root->set("id", _id);
        root->set("user_id", _user_id);
        root->set("delivery_id", _delivery_id);
        root->set("first_name", _first_name);
        root->set("last_name", _last_name);
        root->set("phone_number", _phone_number);

        return root;
    }

    Recipient Recipient::fromJSON(const std::string &str)
    {
        Recipient recipient;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(str);
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        recipient.id() = object->getValue<long>("id");
        recipient.user_id() = object->getValue<long>("user_id");
        recipient.delivery_id() = object->getValue<long>("delivery_id");
        recipient.first_name() = object->getValue<std::string>("first_name");
        recipient.last_name() = object->getValue<std::string>("last_name");
        recipient.phone_number() = object->getValue<std::string>("phone_number");

        return recipient;
    }

     std::optional<Recipient> Recipient::get_trip(long id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement select(session);
            Recipient t;
            select << "SELECT id, user_id, delivery_id, first_name, last_name, phone_number FROM Recipient where id=?",
                into(t._id),
                into(t._user_id),
                into(t._delivery_id),
                into(t._first_name),
                into(t._last_name),
                into(t._phone_number),
                use(id),
                range(0, 1); //  iterate over result set one row at a time

            select.execute();
            Poco::Data::RecordSet rs(select);
            if (rs.moveFirst()) return t;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            
        }
        return {};
    }
     std::vector<Recipient> Recipient::get_all_trips()
    {
 try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement select(session);
            Recipient t;
            std::vector<Recipient> result;
            select << "SELECT id, user_id, delivery_id, first_name, last_name, phone_number FROM Recipient",
                into(t._id),
                into(t._user_id),
                into(t._delivery_id),
                into(t._first_name),
                into(t._last_name),
                into(t._phone_number),
                range(0, 1); //  iterate over result set one row at a time

             while (!select.done())
            {
                if (select.execute())
                    result.push_back(t);
            }
            return result;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            
        }
        return {};
    }

    void Recipient::save_to_mysql()
    {

        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            std::cout << "session+" << std::endl;
            Poco::Data::Statement insert(session);
            std::cout << "insert_session+" << std::endl;

            insert << "INSERT INTO Recipient (user_id,delivery_id,first_name,last_name,phone_number) VALUES(?, ?, ?, ?, ?)",
                use(_user_id),
                use(_delivery_id),
                use(_first_name),
                use(_last_name),
                use(_phone_number);

            insert.execute();
            std::cout << "insert+" << std::endl;
            Poco::Data::Statement select(session);
            select << "SELECT LAST_INSERT_ID()",
                into(_id),
                range(0, 1); //  iterate over result set one row at a time

            if (!select.done())
            {
                select.execute();
            }
            std::cout << "inserted:" << _id << std::endl;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    long Recipient::get_id() const
    {
        return _id;
    }

    long Recipient::get_user_id() const
    {
        return _user_id;
    }

   long Recipient::get_delivery_id() const
    {
        return _delivery_id;
    }
    const std::string &Recipient::get_first_name() const
    {
        return _first_name;
    }
    const std::string &Recipient::get_last_name() const
    {
        return _last_name;
    }
    const std::string &Recipient::get_phone_number() const
    {
        return _phone_number;
    }

  
    long &Recipient::id()
    {
        return _id;
    }

    long &Recipient::user_id()
    {
        return _user_id;
    }
    
    long &Recipient::delivery_id()
    {
        return _delivery_id;
    }
    std::string &Recipient::first_name()
    {
        return _first_name;
    }
    std::string &Recipient::last_name()
    {
        return _last_name;
    }
    std::string &Recipient::phone_number()
    {
        return _phone_number;
    }
}