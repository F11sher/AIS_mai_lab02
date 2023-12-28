#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Delivery{
        private:
            long _id;
            long _user_id;
            std::string _type;
            std::string _creation_date;
            std::string _departure_point;
            std::string _receipt_point;
            

        public:

            static Delivery fromJSON(const std::string & str);

            long get_id() const;
            long get_user_id() const;
            const std::string &get_type() const;
            const std::string &get_creation_date() const;
            const std::string &get_departure_point() const;
            const std::string &get_receipt_point() const;

            long &id();
            long &user_id();
            std::string &type();
            std::string &creation_date();
            std::string &departure_point();
            std::string &receipt_point();

            static void init();
            static std::vector<Delivery> get_delivery(long user_id);
            void save_to_mysql();

            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif