#include <flecs.h>
#include <dd.h>
#include <nlohmann/json.hpp>

namespace misc_tests
{
using Json = ::nlohmann::json;

struct Position {
  float x, y;
};

struct Velocity {
  float x, y;
  std::vector<int> values;
};

std::string serPos(const Position& p)
{
    Json j;
    j["x"] = p.x;
    j["y"] = p.y;
    return j.dump();
}
std::string serVel(const Velocity& v)
{
    Json j;
    j["x"] = v.x;
    j["y"] = v.y;
    return j.dump();
}
Position deserPos(const std::string& s)
{
    Json j = Json::parse(s);
    Position p;
    p.x = j["x"];
    p.y = j["y"];
    return p;
}
Velocity deserVel(const std::string& s)
{
    Json j = Json::parse(s);
    Velocity v;
    v.x = j["x"];
    v.y = j["y"];
    return v;
}


void TestEcs()
{
    dd::engine engine;

    flecs::world world;
    world.import<flecs::units>();
    world.import<flecs::monitor>();

    world.component<Velocity>()
            .member<float>("x")
            .member<float, flecs::units::speed::KiloMetersPerHour>("y");

    world.component<Position>()
            .member<float, flecs::units::length::Pixels>("x")
            .member<float, flecs::units::length::Pixels>("y");

    world.system<Position, const Velocity>()
      .each([](Position& p, const Velocity& v) {
        p.x += v.x;
        p.y += v.y;
      });

    auto e1 = world.entity("e1")
      .set([](Position& p, Velocity& v) {
        p = {10, 20};
        v = {1, 2, {1, 2, 3}};
      });

    auto e2 = world.entity("e2")
      .set([](Position& p, Velocity& v) {
        p = {10000, 20000};
        v = {1000, 2000, {100, 200, 300, 400}};
      });

    e2.add(flecs::ChildOf, e1);

    world.set<flecs::Rest>({});
    while(true){
        world.progress( 1000.0f / 66.0f );
        engine.sleep(16);
    }
}


}
