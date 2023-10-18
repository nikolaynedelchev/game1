#include <dd.h>
#include "resource_loader.h"

dd::engine engine;
dd::rect sampleRect = {50, 100, 120, 150};
dd::vec scale = {1, 1};
dd::vec offset = {0, 0};
dd::text sampleText;
dd::text rssText;

void Init()
{
    int screenWidth = 1440;
    int screenHeight = 900;
    engine.init(DD_RSS_FOLDER, screenWidth, screenHeight, "FROGGER", false);
    //
    engine.target_fps(60);
    engine.mouse_cursor_hide();

    dd::println("Loading resources...");
    //

    sampleText.color = dd::colors::yellow;
    sampleText.position = {10, 10};
    sampleText.font_size = 50.0f;
    sampleText.set_font("OpenSans-Regular.ttf");

    rssText.color = dd::colors::red;
    rssText.position = {10, 70};
    rssText.font_size = 50.0f;
    rssText.set_font("OpenSans-Regular.ttf");

    Rss::LoadFroggerResources();

    dd::println("Resource loaded!");
}

void Deinit()
{
    engine.close();
}

void choose_position( const dd::sprite& srcSprite, dd::point sampleAnchor, dd::sprite& target )
{
    auto src = srcSprite.rect();
    auto toTop = sampleAnchor.y - src.y;
    auto toBottom = src.y + src.height - sampleAnchor.y;
    auto toLeft = sampleAnchor.x - src.x;
    auto toRight = src.x + src.width - sampleAnchor.x;
    target.position = sampleAnchor;

    if (toTop < toBottom && toTop < toLeft && toTop < toRight)
    {
        // top
        target.change_anchor(dd::anchors::down_mid);
        target.position.y = src.y - 20;
    }
    else if(toBottom < toTop && toBottom < toRight && toBottom < toLeft)
    {
        // bottom
        target.change_anchor(dd::anchors::up_mid);
        target.position.y = src.y + src.height + 20;
    }
    else if (toRight < toTop && toRight < toBottom && toRight < toLeft)
    {
        // right
        target.change_anchor(dd::anchors::mid_left);
        target.position.x = src.x + src.width + 20;
    }
    else
    {
        // left
        target.change_anchor(dd::anchors::mid_right);
        target.position.x = src.x - 20;
    }

}

void MainLoop()
{
    size_t rssIdx = 0;
    auto allRss = Rss::GetAllGameSprites();
    while ( !engine.should_close() )
    {
        if (engine.key_down(dd::keys::LEFT_CONTROL) && false == engine.key_down(dd::keys::LEFT_SHIFT))
        {
            // CTRL fast move src rect
            if (engine.key_down(dd::keys::UP))       { sampleRect.y-=3; }
            if (engine.key_down(dd::keys::DOWN))     { sampleRect.y+=3; }
            if (engine.key_down(dd::keys::LEFT))     { sampleRect.x-=3; }
            if (engine.key_down(dd::keys::RIGHT))    { sampleRect.x+=3; }
        }
        else if (engine.key_down(dd::keys::LEFT_CONTROL) && engine.key_down(dd::keys::LEFT_SHIFT))
        {
            // CTRL+SHIFT slow move src rect
            if (engine.key_pressed(dd::keys::UP))       { sampleRect.y--; }
            if (engine.key_pressed(dd::keys::DOWN))     { sampleRect.y++; }
            if (engine.key_pressed(dd::keys::LEFT))     { sampleRect.x--; }
            if (engine.key_pressed(dd::keys::RIGHT))    { sampleRect.x++; }
        }
        else if(engine.key_down(dd::keys::LEFT_ALT) && false == engine.key_down(dd::keys::LEFT_SHIFT))
        {
            // ALT fast resize src rect
            if (engine.key_down(dd::keys::UP))       { sampleRect.height-=3; }
            if (engine.key_down(dd::keys::DOWN))     { sampleRect.height+=3; }
            if (engine.key_down(dd::keys::LEFT))     { sampleRect.width-=3; }
            if (engine.key_down(dd::keys::RIGHT))    { sampleRect.width+=3; }
        }
        else if(engine.key_down(dd::keys::LEFT_ALT) && engine.key_down(dd::keys::LEFT_SHIFT))
        {
            // ALT+SHIFT slow resize src rect
            if (engine.key_pressed(dd::keys::UP))       { sampleRect.height--; }
            if (engine.key_pressed(dd::keys::DOWN))     { sampleRect.height++; }
            if (engine.key_pressed(dd::keys::LEFT))     { sampleRect.width--; }
            if (engine.key_pressed(dd::keys::RIGHT))    { sampleRect.width++; }
        }
        else if(false == engine.key_down(dd::keys::LEFT_CONTROL) && false == engine.key_down(dd::keys::LEFT_ALT))
        {
            if (engine.key_down(dd::keys::UP))          { offset += {0, -5}; }
            if (engine.key_down(dd::keys::DOWN))        { offset += {0, 5}; }
            if (engine.key_down(dd::keys::LEFT))        { offset += {-5, 0}; }
            if (engine.key_down(dd::keys::RIGHT))       { offset += {5, 0}; }
        }
        if (engine.key_down(dd::keys::PAGE_UP)) {scale += {0.02f, 0.02f}; }
        if (engine.key_down(dd::keys::PAGE_DOWN)) {scale -= {0.02f, 0.02f}; }
        if (engine.key_pressed(dd::keys::HOME))
        {
            if (rssIdx == 0) rssIdx = allRss.size();
            rssIdx--;
        }
        if (engine.key_pressed(dd::keys::END))
        {
            rssIdx++;
            if (rssIdx == allRss.size()) rssIdx = 0;
        }

        engine.begin_frame();
        engine.clear_frame(dd::colors::dark_purple);

        dd::sprite allSprites;
        allSprites.load("sprites.png", {}, {});
        allSprites.change_anchor(dd::anchors::centered);

        allSprites.position = {720, 450};
        allSprites.position += offset;
        allSprites.size *= scale;
        allSprites.draw();

        dd::rect boundRect = sampleRect;
        boundRect.position( boundRect.position() * scale );
        boundRect += allSprites.rect().position();
        boundRect.size( boundRect.size() * scale );
        boundRect = boundRect.bounding_rect();
        boundRect.draw(dd::colors::red, false);

        dd::sprite sampleSprite;
        sampleSprite.load("sprites.png", sampleRect, {});

        sampleSprite.size *= scale;
        choose_position(allSprites, boundRect.anchor(dd::anchors::centered), sampleSprite );

        //sampleSprite.change_anchor(dd::anchors::up_right);
        //sampleSprite.position = allSprites.rect().anchor(dd::anchors::up_left) - dd::vec(20, 0);
        //sampleSprite.draw();


        allSprites.rect().bounding_rect().draw(dd::colors::red, false);
        //BoundBox(sampleSprite).draw(dd::colors::red, false);

        sampleText.symbols = (fmt::format("Sample: {}", sampleRect));
        sampleText.clear_background(dd::colors::magenta);
        sampleText.draw();

        auto rss = allRss[rssIdx];

        rssText.symbols = (rss.first);
        rssText.clear_background(dd::colors::black);
        rssText.draw();

        rss.second.change_anchor(dd::anchors::up_left);
        rss.second.size *= scale * 2.0f;
        rss.second.position = {30, 140};
        rss.second.rect().bounding_rect().draw(dd::colors::red, false);
        rss.second.draw();
        
        engine.end_frame();
    }
}

int main()
{
    Init();

    MainLoop(); // this is the real game

    Deinit();

    return 0;
}
