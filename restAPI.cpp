/*This is created by Michael otote*/
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace std;

// Define your API endpoint
const utility::string_t base_uri = U("http://localhost:8080");

// Handler function to process incoming requests
void handle_get(http_request request)
{
    // Create a JSON response
    web::json::value response;
    response[U("message")] = web::json::value::string(U("Hello, World!"));

    // Set the content type of the response
    http_response res(status_codes::OK);
    res.headers().set_content_type(U("application/json"));

    // Send the JSON response
    res.set_body(response);
    request.reply(res);
}

int main()
{
    // Create an HTTP listener
    http_listener listener(base_uri);

    // Handle GET requests on the endpoint
    listener.support(methods::GET, handle_get);

    try
    {
        // Start listening for requests
        listener.open().wait();

        // Keep the server running until user input
        ucout << U("Listening for requests at: ") << base_uri << endl;
        ucout << U("Press Enter to exit.") << endl;
        string line;
        getline(cin, line);

        // Close the listener when done
        listener.close().wait();
    }
    catch (const std::exception& ex)
    {
        ucerr << U("Error: ") << ex.what() << endl;
        return 1;
    }

    return 0;
}
