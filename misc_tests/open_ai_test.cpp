#include <string.h>
#include <nlohmann/json.hpp>

#include <dd.h>
#include <cpr/cpr.h>
namespace misc_tests
{


using Json = ::nlohmann::json;

void TestOpenAI()
{

    std::string api_key = "...";
    //std::string url = "https://api.openai.com/v1/completions";
std::string url = "https://api.openai.com/v1/chat/completions";

    // Request data
    Json t =nlohmann::json::parse(
        R"(
                {
                    "model": "gpt-4",
                    "messages": [
                        {
                          "role": "system",
                          "content": "You are a helpful assistant. DO NOT ANSWER TO QUESTIONS THAT ARE NOT RELATED TO PROGRAMMING OR COOCKING!"
                        },
                        {
                          "role": "user",
                          "content": "Hello, tell me a joke."
                        }
                    ]
                }
        )");

    dd::println("Prompt: {}", t.dump(3));
    dd::println();
    Json data = {
        {"model", "gpt-3.5-turbo-instruct"},
        {"prompt", "Say something postive about the humanity."},  // Example question
        {"max_tokens", 7}
    };

    // Request header
    cpr::Header headers = {
        {"Authorization", "Bearer " + api_key},
        {"Content-Type", "application/json"}
    };

    // Send request
    cpr::Response response = cpr::Post(cpr::Url{url}, headers, cpr::Body{t.dump()});

    // Check if respone is successful
    if (response.status_code == 200) {
        // Response process
        Json response_data = nlohmann::json::parse(response.text);
        dd::println("Response: {}", std::string(response_data["choices"][0]["message"]["content"]));
        dd::println("Full Response: {}", response_data.dump(3));
    } else {
        // Error process
        Json response_data = nlohmann::json::parse(response.text);
        dd::println("Error: {}", response.status_code);
        dd::println("Error full: {}", response.status_line);
        dd::println("Response data: {}", response_data.dump(3));
    }

}
}

