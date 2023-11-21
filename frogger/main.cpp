#include "all_modules.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <chrono>
#include <entt/entt.hpp>

using Json = ::nlohmann::json;

void Test()
{
    std::string api_key = "...";
    //std::string url = "https://api.openai.com/v1/completions";
std::string url = "https://api.openai.com/v1/chat/completions";

    // Данни за заявката
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
                          "content": "Здравей, дай ми съвет как да сменя гумата на колата."
                        }
                    ]
                }
        )");

    dd::println("Prompt: {}", t.dump(3));
    dd::println();
    Json data = {
        {"model", "gpt-3.5-turbo-instruct"},
        {"prompt", "Say something postive about the humanity."},  // Примерен въпрос
        {"max_tokens", 7}
    };

    // Заглавки на заявката
    cpr::Header headers = {
        {"Authorization", "Bearer " + api_key},
        {"Content-Type", "application/json"}
    };

    // Изпращане на заявката
    cpr::Response response = cpr::Post(cpr::Url{url}, headers, cpr::Body{t.dump()});

    // Проверка за успешен отговор
    if (response.status_code == 200) {
        // Обработка на отговора
        Json response_data = nlohmann::json::parse(response.text);
        dd::println("Response: {}", std::string(response_data["choices"][0]["message"]["content"]));
        dd::println("Full Response: {}", response_data.dump(3));
    } else {
        Json response_data = nlohmann::json::parse(response.text);
        dd::println("Error: {}", response.status_code);
        dd::println("Error full: {}", response.status_line);
        dd::println("Response data: {}", response_data.dump(3));
    }
}


struct position {
    float x;
    float y;
};

struct velocity {
    float dx;
    float dy;
};

struct data {
    std::string name;
};


void update(entt::registry &registry)
{
    auto view = registry.view<const position, velocity>();

    // use a callback
    view.each([](const auto &pos, auto &vel) { /* ... */ });

    // use an extended callback
    view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

    // use a range-for
    for(auto [entity, pos, vel]: view.each()) {
        // ...
        auto& pos2 = registry.get<position>(entity);
        registry.has<position>(entity);
    }

    // use forward iterators and get only the components of interest
    for(auto entity: view) {
        auto &vel = view.get<velocity>(entity);
        // ...
    }
}

int main()
{
    entt::registry registry;

    for(auto i = 0u; i < 10u; ++i) {
        const auto entity = registry.create();
        registry.emplace<position>(entity, i * 1.f, i * 1.f);
        if(i % 2 == 0) { registry.emplace<velocity>(entity, i * .1f, i * .1f); }
    }
    update(registry);


    //Test(); return 0;
    FroggerGame::game.Init();
    FroggerGame::game.MainLoop();
    FroggerGame::game.Deinit();
    return 0;
}
