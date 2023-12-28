#ifndef RECIPIENT_H
#define RECIPIENT_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Trip{
        private:
            long _id;
            long _user_id;
            long _delivery_id;
            std::string _first_name;
            std::string _last_name;
            std::string _phone_number;
            

        public:

            static Trip fromJSON(const std::string & str);

            long get_id() const;
            long get_user_id() const;
            long get_delivery_id() const;
            const std::string &get_first_name() const;
            const std::string &get_last_name() const;
            const std::string &get_phone_number() const;

            long &id();
            long &user_id();
            long &delivery_id();
            std::string &first_name();
            std::string &last_name();
            std::string &phone_number();

            static void init();
            static std::optional<Trip> get_recipient(long id);
            static std::vector<Trip> get_all_recipients();
            void save_to_mysql();

            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif