#ifndef DELIVERYHANDLER_H
#define DELIVERYHANDLER_H

#include "../../database/delivery.h"
#include "../../helper.h"

#include <iostream>
#include <ctime>
#include <iomanip>

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::ThreadPool;
using Poco::Timestamp;
using Poco::Net::HTMLForm;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::NameValueCollection;
using Poco::Net::ServerSocket;
using Poco::Util::Application;
using Poco::Util::HelpFormatter;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

static bool hasSubstrDelivery(const std::string &str, const std::string &substr)
{
    if (str.size() < substr.size())
        return false;
    for (size_t i = 0; i <= str.size() - substr.size(); ++i)
    {
        bool ok{true};
        for (size_t j = 0; ok && (j < substr.size()); ++j)
            ok = (str[i + j] == substr[j]);
        if (ok)
            return true;
    }
    return false;
}


class DeliveryHandler : public HTTPRequestHandler
{
private:
    bool check_user_id(const long &user_id, std::string &reason)
    {
       

        if (user_id < 0)
        {
            reason = "Wrong id";
            return false;
        }       

        return true;
    };

    bool check_userdelivery(std::vector<std::string> &results, std::string &reason)
    {
       reason = results[0];
       return true;
    }

    bool check_creation_date(const std::string &creation_date, std::string &reason)
    {       
        
        if (creation_date.find(' ') != std::string::npos)
        {

            std::string m = "Creation date can't contain spaces ";            
            reason =  m + creation_date;
            return false;
        }
        

        return true;
    };

public:
    DeliveryHandler(const std::string &format) : _format(format)
    {
    }

    void handleRequest(HTTPServerRequest &request,
                       HTTPServerResponse &response)
    {
        HTMLForm form(request, request.stream());
        try
        {
            if (form.has("user_id") && (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET))
            {
                long user_id = atol(form.get("user_id").c_str());

                auto results = database::Delivery::get_deliveries(user_id);
                Poco::JSON::Array arr;
                for (auto s : results)
                    arr.add(s.toJSON());
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                response.setChunkedTransferEncoding(true);
                response.setContentType("application/json");
                std::ostream &ostr = response.send();
                Poco::JSON::Stringifier::stringify(arr, ostr);
               
            }
            if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) 
            {
                if (form.has("user_id") && form.has("type") && form.has("creation_date") && form.has("departure_point") && form.has("receipt_point"))
                {
                    database::Delivery delivery;
                    std::cout << "delivery+" << std::endl;
                    delivery.user_id() =  atol(form.get("user_id").c_str()); 
                    std::cout << delivery.user_id() << "+" << std::endl;      
                    delivery.type() = form.get("type");
                    std::cout << delivery.type() << "+" << std::endl; 
                    delivery.creation_date() = form.get("creation_date");
                    std::cout << delivery.creation_date() << "+-" << std::endl;
                    delivery.departure_point() = form.get("departure_point");
                    std::cout << delivery.departure_point() << "+" << std::endl; 
                    delivery.receipt_point() = form.get("receipt_point");
                    std::cout << delivery.departure_point() << "+" << std::endl; 

                    
                   

                
                
                        delivery.save_to_mysql();
                        std::cout << "save+" << std::endl;
                        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                        response.setChunkedTransferEncoding(true);
                        response.setContentType("application/json");
                        std::ostream &ostr = response.send();
                        ostr << delivery.get_id();
                        return;
                }
            }
        }
        catch (...)
        {
                std::string message;
                std::string reason;
                
                if (1 == 1)
                    {                        
                        message += "запрос не работает";
                        message += "<br>";
                        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                        std::ostream &ostr = response.send();
                        ostr << message;
                        response.send();
                        return;
                    }
        }

        response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
        response.setChunkedTransferEncoding(true);
        response.setContentType("application/json");
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
        root->set("type", "/errors/not_found");
        root->set("title", "Internal exception");
        root->set("status", Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
        root->set("detail", "request not found");
        root->set("instance", "/delivery");
        std::ostream &ostr = response.send();
        Poco::JSON::Stringifier::stringify(root, ostr);
    }

private:
    std::string _format;
};
#endif