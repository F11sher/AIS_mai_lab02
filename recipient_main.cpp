#include <optional>
#include "recipient_service/http_recipient_service.h"

int main(int argc, char*argv[]) 
{
    HTTPRecipientOtherWebServer app;
    return app.run(argc, argv);
}