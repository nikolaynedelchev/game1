#include "game.h"
#include <tiny_dnn/tiny_dnn.h>
#include <entt/entt.hpp>
#include <memory>
#include "engine/textures.h"

namespace ndn::CheckersGame
{
// Компонент за позиция
struct Position {
    float x;
    float y;
};

// Компонент за скорост
struct Velocity {
    float dx;
    float dy;
};

#define COMP_EX(comp_name)                                                 \
    private:\
        std::unique_ptr<comp_name> impl_;\
        \
    public:\
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<comp_name, T>>>\
        comp_name(T ex) : impl_(std::make_unique<T>(std::move(ex))){}\
        \
        void RegisterImpl(std::unique_ptr< comp_name > impl)\
        {\
            impl_ = std::move(impl);\
        }\
    \
        template<typename T>\
        T* Ex()\
        {\
            return dynamic_cast<T*>(impl_.get());\
        }\


struct IMove
{
    COMP_EX(IMove);
    IMove() = default;
    IMove(int t):testValue(t){};

    virtual void InstantMove(int x, int y){};
    virtual void AnimatedMove(int x, int y, float ms){};
    virtual void Process(int dt){};

    int testValue = 0;

};

struct MoveEx : public IMove
{
    int exValue = 12;
};

struct MoveEx2 : public IMove
{
    int exValue = 11;
};

void main() {

    entt::registry registry;
    eng::Textures textures;

    // Създаваме entity и добавяме компоненти
    auto entity = registry.create();
    Position p = {0, 0};
    registry.emplace<IMove>(entity, 444);
    registry.emplace<Position>(entity, p);
    registry.emplace<Velocity>(entity, 1.0f, 1.0f);

    // Система за обновяване на позицията
    auto view = registry.view<Position, Velocity>();
    for (auto entity : view) {
        auto& pos = view.get<Position>(entity);
        auto& vel = view.get<Velocity>(entity);

        auto m2Ptr = registry.try_get<IMove>(entity);
        auto& m2 = registry.get<IMove>(entity);
        m2.InstantMove(100, 100);

        auto mex = m2.Ex<MoveEx>();
        // Обновяване на позицията
        pos.x += vel.dx;
        pos.y += vel.dy;

        std::cout << "Entity position: (" << pos.x << ", " << pos.y << ")\n";
    }
}

void DoTest()
{
    main();
}

}


int main()
{
    ndn::CheckersGame::DoTest();
    tiny_dnn::network<tiny_dnn::sequential> net;
    (void)net;

    ndn::CheckersGame::game.Init();
    ndn::CheckersGame::game.MainLoop();
    ndn::CheckersGame::game.Deinit();
    return 0;
}
