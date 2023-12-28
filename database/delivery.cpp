#include "delivery.h"
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

    void Delivery::init()
    {
        try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_delivery(session);
            create_delivery << "CREATE TABLE IF NOT EXISTS `Delivery` (`id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                        << "`user_id` INT NOT NULL,"
                        << "`type` VARCHAR(256) NOT NULL,"
                        << "`creation_date` VARCHAR(256) NOT NULL,"
                        << "`departure_point` VARCHAR(256) NOT NULL,"
                        << "`receipt_point` VARCHAR(256) NOT NULL);",
                now;
              std::cout << "Delivery table initialized successfully." << std::endl;
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

    Poco::JSON::Object::Ptr Delivery::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        root->set("id", _id);
        root->set("user_id", _user_id);
        root->set("type", _type);
        root->set("creation_date", _creation_date);
        root->set("departure_point", _departure_point);
        root->set("receipt_point", _receipt_point);

        return root;
    }

    Delivery Delivery::fromJSON(const std::string &str)
    {
        Delivery delivery;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(str);
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        delivery.id() = object->getValue<long>("id");
        delivery.host_id() = object->getValue<long>("host_id");
        delivery.type() = object->getValue<std::string>("type");
        delivery.creation_date() = object->getValue<std::string>("creation_date");
        delivery.departure_point() = object->getValue<std::string>("departure_point");
        delivery.receipt_point() = object->getValue<std::string>("receipt_point");

        return delivery;
    }

    std::vector<Delivery> Delivery::get_deliveries(long host_id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement select(session);
            Delivery r;
            std::vector<Delivery> result;
            select << "SELECT id, user_id, type, creation_date, departure_point, receipt_point FROM Delivery where host_id=?",
                into(r._id),
                into(r._user_id),
                into(r._type),
                into(r._creation_date),
                into(r._departure_point),
                into(r._receipt_point),
                use(user_id),
                range(0, 1); //  iterate over result set one row at a time

              while (!select.done())
            {
                if (select.execute())
                    result.push_back(r);
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

    void Delivery::save_to_mysql()
    {

        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            insert << "INSERT INTO Delivery (user_id,type,creation_date,departure_point,receipt_point) VALUES(?, ?, ?, ?, ?, ?)",
                use(_user_id),
                use(_type),
                use(_creation_date),
                use(_departure_point),
                use(_receipt_point);

            insert.execute();

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

    long Delivery::get_id() const
    {
        return _id;
    }

    long Delivery::get_user_id() const
    {
        return _user_id;
    }

    const std::string &Delivery::get_title() const
    {
        return _title;
    }
    const std::string &Delivery::get_type() const
    {
        return _type;
    }
    const std::string &Delivery::get_creation_date() const
    {
        return _creation_date;
    }
    const std::string &Delivery::get_departure_point() const
    {
        return _departure_point;
    }

    const std::string &Delivery::get_receipt_point() const
    {
        return _receipt_point;
    }


    long &Delivery::id()
    {
        return _id;
    }

    long &Delivery::host_id()
    {
        return _user_id;
    }

    std::string &Delivery::type() 
    {
        return _type;
    }
    std::string &Delivery::creation_date()
    {
        return _creation_date;
    }
    std::string &Delivery::departure_point()
    {
        return _departure_point;
    }

    std::string &Delivery::receipt_point()
    {
        return _receipt_point;
    }
}