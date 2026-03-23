#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

#include "com\\metanet\\App_MultiPurpose.h"
#include "com\\foxarc\\util\\Base64.h"
#include "com\\metanet\\commands\\StoreDefaults.h"

#include "audiovisual\\entitygraphics\\EntityGraphics_Door_Locked.h"
#include "audiovisual\\entitygraphics\\EntityGraphics_ExitDoor.h"
#include "audiovisual\\entitygraphics\\EntityGraphics_ExitSwitch.h"
#include "audiovisual\\entitygraphics\\EntityGraphics_Gold.h"
#include "audiovisual\\entitygraphics\\EntityGraphics_Mine.h"
#include "audiovisual\\entitygraphics\\EntityGraphics_FloorGuard.h"
#include "audiovisual\\entitygraphics\\EntityGraphics_BounceBlock.h"
#include "audiovisual\\entitygraphics\\EntityGraphics_Turret.h"

using namespace std;

void Initialize(App_MultiPurpose& app);
void Inject(App_MultiPurpose& app);
vector<int> ImportantKeys(PlayerKeys* soloKeys, GlobalKeys* globalKeys);
void CheckKeys(SimpleInput& input, vector<int>& keys);

string straightForward = "00000000000010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101060000070101010106000007010101010600000701010101010101010101010000000001010101000000000101010100000000010101010101010101010100000000010101010000000001010101000000000101010101010101010106000000000701010600000000070101060000000007010101010101010106000000000000000000000000000000000000000000000000000000000700000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000900000000000000000000000000000000000000000000000000000008010101010101010109000000000801010900000000080101090000000008010101010101010101010000000001010101000000000101010100000000010101010101010101010100000000010101010000000001010101000000000101010101010101010101090000080101010109000008010101010900000801010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010100010a0a3000000f062e282e2a2e281a3a1a361a383a3a3a363a385a365a3a5a364e284e2a4e20010c763872300000000000000000000000000000000000000000000000000000000";
string tutorialJumpingLong = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000041000000005100000000000041000000000000000000510000000000004181210000000031915100004181210000000000000000003191510000101010100000000000001010101010100000000000000000000000101010101010101000000000000010101010101000000000000000000000001010101010101010000000000000101010101010000000000000000000000010101010101010100000000000001010101010100000000000000000000000101010101010101000000000000010101010101000000000000000000000001010101010101010000000000000101010101010000000000000000000000010101010101010100000000000001010101010100000000000000000000000101010101010101000000000000010101010101000000000000000000000001010101010101010404040404040101010101010404040404040404040404010101010001080a3001361c3610461c561856145610561c461846144a1c5e1c522c562c5a2c5a285a245a205a2c4a284a244a204a2c364c364046444648464c464056445648564c5a4c5e4c525c565c5a5c5e5c526c566c5a6c5e6c5e685e645e605e6c4e684e644e604e6c30050c742c782c7c2c703c7430010c7a383a300000000000000000000000000000000000000000000000000000000";
string breathingRoom = "0000000000006000000000000000000000000000000000000000000000000000000000007000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000008010101010101010101010101010101010101010101010109000000000000010101010101010101010101010101010101010101010101010000000000000101060000000000000000000000000000000000000007010100000001200801010000000000000000000000000000000000000000000101090000210101010100000000000000000000000000000000000000000001010101010e10070101000000000000000000000000000000000000000000010106000f100000010109000000000000000000000000000000000000000801010000000000000101010101010101010101010101010101010101010101010100000000000007010101010101010101010101010101010101010101010106000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000900000000000000000000000000000000000000000000000000000000000800010e1a200402322252224c266c200c046e126e106e106c126c146c114e134e134c114c122e122c1001022a28622000000000000000000000000000000000000001026b20030222226222422000000000000";
string pokeyman = "000000000000101010101010101010101010101010101010101010101010101010101010101010612100000000000000000000000000000000000000000000003171101010600000000000000000000000000000000000000000000000000000007010e10000000000000000000000000000000000000000000000000000000000f1a10000000000000000000000000000000000000000000000000000000000b1000000000000000000000000418191008191510000000000000000000000000000000000000000000000801010100010101090000000000000000000000000000000000000000000801010106000701010109000000000000000000000000000000000000000c11010101000000010101010d100000000000000000000000000000000000002101010109000801010101012000000000000000000000000000000000000711010101010101010101010610000000000000000009000000000000000000000000000000000000000000000000000000000008010000080101010109000000000000000000000000000801010101090000010109000101010101010d10000000000000000000000c1101010101010008010101000101010101010120000000000000000000000021010101010100010101010001010101010101090000000000000000000801010101010101000101010600010101010101010109000000000000000801010101010101010007010100080101010101010101010915100000041811010101010101010109000101000101010101010101010101010101010101010101010101010101010001010000000701010101010101010101010101010101010101010106000000010100000000070101010101010101010101010101010101010106000000000101090000000000000000000000000000000000000000000000000000000801010101010101010101010101010101010101010101010101010101010101010001024a4000000516462648244a224a204a2e382e362e3420422242244226442444224420442046224624462448224820482001024a424e000000020240220a2a524c120a5a50000000000000000000000000000001024b5000000000020e72260220000";
string shakeItMadam = "0000000000001010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010a10000000010101010101010101010101010101010101010101000000000b100000000c1101010101010101010101010101010101010101010d10000000000001010101010101010101010101010101010101010101010101010100000d100f110101010101010101010101010101010101010101010101010e100c11200b110101010101010101010101010101010101010101010101010a1000210000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000001010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010001027a200223783118371043204f204b304d604d3041304520491043183d183f1839283b2835383738314833483d483f4839583b583568376831783b6041604f50455043504940474040000001021a224d30000000000000000002080e300c7e3400000000000000000002060f3e7f30000000000000000";
string piratePete = "00000000000010101010101010101010101010101010101010101010102100007010101010101010101010101010101010101010101010101010e1210000000071e110101010101010101010101010101010101010101010105100000000000000f11010101010101010101010101010101010101010101010e100000000000000f110101010101010101010101010101010101010101010a100000000000000b1101010a1f110101010101010101010101010101010100000000000000000001010210000f1101010600000000031101010101010610000000000000000001010900012021010a10000000000007010101010100000000000000000000010101051101010e10080101010109151000070106000000000c1109002120010101010101021000210101010101010120000000000000000b110101010001010101010600000101010101010101010900000000000000000f1101061001010101010d100c1101010101010e0f0101000000000000000000210e10000101010101050003010101010101011011010d1000000000000c11010a100001010101010a100b11010e0f0101010101010500000000000000210e1000000101010101000000010101101101010101010a100004140811010101010510010101010e1000000f11010101010107110100000001010101010101010100210101060000000000031101010e1101010600000c1101010101010101010101010a1000000000000007010101010e131005100301010101010101010101010100000000000000000000070106000801010a1301010101010101010101010100000000000000000000000b1005110101000b1101010101010101010101010510000000000000000000000411010106000801010101010101010101010101012000000000000000000b1101060000000101010101010101010101010101010109000000000004140510000000000c110101010101010101010100010c7830061e6e12781c64186a0a16381e391a345a5052567224601c424e4a3c423d4637564852463e5670161c531a542e30091e163c143e1430243e183e1230263a4e5c4c5c4e5e4e505c5e4a5e4c5c603a6c2a643b6e2b623a6030165e0450145216501250010e5e0e1e300000010446200828400000000000000000000000000000020233222f50030c7c3a7a1a6e00000002025a261640000";
// added 4 0's to all above (empty title)

int main(int argc, char *argv[]) {
    const int gameWidth = 33;
    const int gameHeight = 25;
    constexpr int CELL_SIZE = 24;
    constexpr int WINDOW_WIDTH = CELL_SIZE * gameWidth;
    constexpr int WINDOW_HEIGHT = CELL_SIZE * gameHeight;
    const int FRAME_RATE = 60;
    const int bgColor = 0xCACAD000;
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Nv2 Simulation");
    window.setFramerateLimit(FRAME_RATE);

    sf::Font font;
    if (!font.loadFromFile("audiovisual/assets/Uni0553.ttf")) {
        cerr << "Error: could not load font" << endl;
        return EXIT_FAILURE;
    }
    sf::Text timebarText;
    timebarText.setFont(font);
    timebarText.setCharacterSize(8);
    timebarText.setFillColor(sf::Color::Black);
    //timebarText.setStyle(sf::Text::Bold);
    timebarText.setPosition(30.f, 6.f);
    timebarText.setLetterSpacing(2.f);
    
    vector<sf::Texture> tiles(42);
    for (int i = 0; i < 34; ++i) {
        tiles.at(i).loadFromFile("audiovisual/assets/tilesTransparent.png", sf::IntRect(i * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
    }
    for (int i = 34; i < 42; ++i) tiles.at(i) = tiles.at(1);

    bool useTextures = false;
    sf::Texture goldTexture;
    goldTexture.loadFromFile("audiovisual/assets/gold.png");
    sf::Texture mineTexture;
    mineTexture.loadFromFile("audiovisual/assets/mine.png");
    sf::Texture ninjaTexture;
    ninjaTexture.loadFromFile("audiovisual/assets/ninja.png");
    sf::Texture doorClosedTexture;
    doorClosedTexture.loadFromFile("audiovisual/assets/door.png");
    sf::Texture doorOpenTexture;
    doorOpenTexture.loadFromFile("audiovisual/assets/doorOpen.png");
    sf::Texture switchClosedTexture;
    switchClosedTexture.loadFromFile("audiovisual/assets/switch.png");
    sf::Texture switchOpenTexture;
    switchOpenTexture.loadFromFile("audiovisual/assets/switchOpen.png");
    sf::Texture floorGuardTexture;
    floorGuardTexture.loadFromFile("audiovisual/assets/floorguard.png");
    sf::Texture bounceBlockTexture;
    bounceBlockTexture.loadFromFile("audiovisual/assets/bounceblock.png");
    sf::Texture lockedSwitchTexture;
    lockedSwitchTexture.loadFromFile("audiovisual/assets/lockedSwitch.png");
    sf::Texture lockedDoorTexture;
    lockedDoorTexture.loadFromFile("audiovisual/assets/lockedDoor.png");
    sf::Texture lockedSwitchOpenTexture;
    lockedSwitchOpenTexture.loadFromFile("audiovisual/assets/lockedSwitchOpen.png");
    sf::Texture lockedDoorOpenTexture;
    lockedDoorOpenTexture.loadFromFile("audiovisual/assets/lockedDoorOpen.png");
    sf::Texture turretBaseTexture;
    turretBaseTexture.loadFromFile("audiovisual/assets/gaussBase.png");
    sf::Texture turretCrosshairTexture;
    turretCrosshairTexture.loadFromFile("audiovisual/assets/gaussAim.png");
    
    App_MultiPurpose app;
    Initialize(app);
    Inject(app);
    vector<int> keys = ImportantKeys(app.soloKeys, app.globalKeys);
    ByteArray levelBytes = sim_globals::StringtoBA(piratePete);
    app.playSingleLevelFromBytes(&levelBytes, "1");

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::T) {
                        useTextures = !useTextures;
                    }
                    break;
                default:
                    break;
            }
        }

        CheckKeys(app.input, keys);
        app.tick();
        
        window.clear(sf::Color(bgColor));
        
        Simulator* sim = app.NEW_getSim();
        if (sim == nullptr) {
            window.display();
            continue;
        }
        vector<int>& tileIDs = sim->GFX_GetTileIDs();
        vector<Ninja*> playerList = sim->GFX_GetPlayerList();
        vector<Entity_Base*> entityList = sim->GFX_GetEntityList();

        if (entityList.size() != 0) {
            vector<DisplayObject*> graphics;
            for (size_t i = 0; i < entityList.size(); ++i) {
                sf::Sprite entity;
                sf::CircleShape entityCircle;
                double r = 0;
                if (entityList[i] != nullptr) {
                    if (dynamic_cast<Entity_Gold*>(entityList[i])) {
                        EntityGraphics_Gold* gold = dynamic_cast<EntityGraphics_Gold*>(entityList[i]->GenerateGraphicComponent());
                        gold->UpdateState();
                        gold->RegisterGraphics(graphics);
                        if (useTextures) {
                            entity.setTexture(goldTexture);
                            r = 7/2;
                            entity.setPosition(graphics.back()->x - r, graphics.back()->y - r);
                        }
                        else {
                            entityCircle.setRadius(r = 6);
                            entityCircle.setFillColor(sf::Color::Yellow);
                            entityCircle.setPosition(graphics.back()->x - r, graphics.back()->y - r);
                        }
                        if (gold->anim == EntityGraphics_Gold::ANIM_NOT_COLLECTED) {
                            if (useTextures) window.draw(entity);
                            else window.draw(entityCircle);
                        }
                    }
                    else if (dynamic_cast<Entity_Mine*>(entityList[i])) {
                        EntityGraphics_Mine* mine = dynamic_cast<EntityGraphics_Mine*>(entityList[i]->GenerateGraphicComponent());
                        mine->UpdateState();
                        mine->RegisterGraphics(graphics);
                        if (useTextures) {
                            entity.setTexture(mineTexture);
                            r = 8/2;
                            double ry = 9/2;
                            entity.setPosition(graphics.back()->x - r, graphics.back()->y - ry);
                        }
                        else {
                            entityCircle.setRadius(r = 4);
                            entityCircle.setFillColor(sf::Color::Red);
                            entityCircle.setPosition(graphics.back()->x - r, graphics.back()->y - r);
                        }
                        if (mine->anim == EntityGraphics_Mine::ANIM_UNEXPLODED) {
                            if (useTextures) window.draw(entity);
                            else window.draw(entityCircle);
                        }
                    }
                    else if (dynamic_cast<Entity_ExitSwitch*>(entityList[i])) {
                        EntityGraphics_ExitSwitch* switch_ = dynamic_cast<EntityGraphics_ExitSwitch*>(entityList[i]->GenerateGraphicComponent());
                        switch_->UpdateState();
                        switch_->RegisterGraphics(graphics);
                        double ry = 8/2;
                        if (useTextures) {
                            entity.setTexture(switchClosedTexture);
                            r = 13/2;
                            entity.setPosition(graphics.front()->x - r, graphics.front()->y - ry);
                        }
                        else {
                            entityCircle.setRadius(r = 6);
                            entityCircle.setFillColor(sf::Color::Cyan);
                            entityCircle.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                        }
                        if (switch_->anim == EntityGraphics_ExitSwitch::ANIM_OPEN) {
                            if (useTextures) {
                                entity.setTexture(switchOpenTexture);
                                entity.setPosition(graphics.front()->x - r, graphics.front()->y - ry);
                            }
                            else {
                                entityCircle.setRadius(6);
                                entityCircle.setFillColor(sf::Color::White);
                            }
                        }
                        if (useTextures) window.draw(entity);
                        else window.draw(entityCircle);
                    }
                    else if (dynamic_cast<Entity_ExitDoor*>(entityList[i])) {
                        EntityGraphics_ExitDoor* door = dynamic_cast<EntityGraphics_ExitDoor*>(entityList[i]->GenerateGraphicComponent());
                        door->UpdateState();
                        door->RegisterGraphics(graphics);
                        if (useTextures) {
                            entity.setTexture(doorClosedTexture);
                            r = 25/2;
                            entity.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                        }
                        else {
                            entityCircle.setRadius(r = 12);
                            entityCircle.setFillColor(sf::Color(0x7F7F7FFF));
                            entityCircle.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                        }
                        if (door->anim == EntityGraphics_ExitDoor::ANIM_OPEN) {
                            if (useTextures) {
                                entity.setTexture(doorOpenTexture, true);
                                entity.setPosition(graphics.front()->x - 49/2, graphics.front()->y - 25/2);
                            }
                            else {
                                entityCircle.setRadius(12);
                                entityCircle.setFillColor(sf::Color::Magenta);
                            }
                        }
                        if (useTextures) window.draw(entity);
                        else window.draw(entityCircle);
                    }
                    else if (dynamic_cast<Entity_FloorGuard*>(entityList[i])) {
                        EntityGraphics_FloorGuard* floorguard = dynamic_cast<EntityGraphics_FloorGuard*>(entityList[i]->GenerateGraphicComponent());
                        floorguard->UpdateState();
                        floorguard->RegisterGraphics(graphics);
                        double ry = 12/2;
                        if (useTextures) {
                            entity.setTexture(floorGuardTexture);
                            r = 14/2;
                            entity.setPosition(graphics.back()->x - r, graphics.back()->y - ry);
                        }
                        else {
                            entityCircle.setRadius(r = 6);
                            entityCircle.setFillColor(sf::Color::Blue);
                            entityCircle.setPosition(graphics.back()->x - r, graphics.back()->y - r);
                        }
                        if (useTextures) window.draw(entity);
                        else window.draw(entityCircle);
                    }
                    else if (dynamic_cast<Entity_BounceBlock*>(entityList[i])) {
                        EntityGraphics_BounceBlock* bounceblock = dynamic_cast<EntityGraphics_BounceBlock*>(entityList[i]->GenerateGraphicComponent());
                        bounceblock->UpdateState();
                        bounceblock->RegisterGraphics(graphics);
                        sf::RectangleShape entitySquare;
                        if (useTextures) {
                            entity.setTexture(bounceBlockTexture);
                            r = 20/2;
                            entity.setPosition(graphics.back()->x - r, graphics.back()->y - r);
                        }
                        else {
                            r = 9.6;
                            entitySquare.setSize(sf::Vector2f(r * 2, r * 2));
                            entitySquare.setFillColor(sf::Color::White);
                            entitySquare.setPosition(graphics.back()->x - r, graphics.back()->y - r);
                        }
                        if (useTextures) window.draw(entity);
                        else window.draw(entitySquare);
                    }
                    else if (dynamic_cast<Entity_Door_Locked*>(entityList[i])) {
                        EntityGraphics_Door_Locked* lockedDoor = dynamic_cast<EntityGraphics_Door_Locked*>(entityList[i]->GenerateGraphicComponent());
                        lockedDoor->UpdateState();
                        lockedDoor->RegisterGraphics(graphics);
                        sf::VertexArray entityLine(sf::Lines, 2);
                        sf::Sprite entityDoor;
                        if (lockedDoor->anim == EntityGraphics_Door_Locked::ANIM_OPEN) {
                            if (useTextures) {
                                entity.setTexture(lockedSwitchOpenTexture);
                                r = 9/2;
                                entity.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                                entityDoor.setTexture(lockedDoorOpenTexture);
                                entityDoor.setOrigin(ceil(5.f/2.f), 24/2);
                                entityDoor.setPosition(graphics.back()->x, graphics.back()->y);
                                if (int(graphics.back()->rotation) % 180 == 90) {
                                    entityDoor.setRotation(90);
                                }
                            }
                            else {
                                entityCircle.setRadius(r = 5);
                                entityCircle.setFillColor(sf::Color::White);
                                entityCircle.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                            }
                        }
                        else {
                            if (useTextures) {
                                entity.setTexture(lockedSwitchTexture);
                                r = 9/2;
                                entity.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                                entityDoor.setTexture(lockedDoorTexture);
                                entityDoor.setOrigin(ceil(5.f/2.f), 24/2);
                                entityDoor.setPosition(graphics.back()->x, graphics.back()->y);
                                if (int(graphics.back()->rotation) % 180 == 90) {
                                    entityDoor.setRotation(90);
                                }
                            }
                            else {
                                entityCircle.setRadius(r = 5);
                                entityCircle.setFillColor(sf::Color(0x7F0000FF));
                                entityCircle.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                                if (graphics.back()->rotation == 0) {
                                    entityLine[0].position = sf::Vector2f(graphics.back()->x, graphics.back()->y - 12);
                                    entityLine[1].position = sf::Vector2f(graphics.back()->x, graphics.back()->y + 12);
                                }
                                else {
                                    entityLine[0].position = sf::Vector2f(graphics.back()->x - 12, graphics.back()->y);
                                    entityLine[1].position = sf::Vector2f(graphics.back()->x + 12, graphics.back()->y);
                                }
                                entityLine[0].color = sf::Color::Black;
                                entityLine[1].color = sf::Color::Black;
                            }
                        }
                        if (useTextures) {
                            window.draw(entity);
                            window.draw(entityDoor);
                        }
                        else {
                            window.draw(entityCircle);
                            window.draw(entityLine);
                        }
                    }
                    else if (dynamic_cast<Entity_Turret*>(entityList[i])) {
                        EntityGraphics_Turret* turret = dynamic_cast<EntityGraphics_Turret*>(entityList[i]->GenerateGraphicComponent());
                        turret->UpdateState();
                        turret->RegisterGraphics(graphics);
                        sf::CircleShape entityCircleInner;
                        sf::VertexArray entityLine(sf::Lines, 2);
                        sf::Sprite entityCross;
                        sf::RectangleShape entitySquare;
                        if (useTextures) {
                            entity.setTexture(turretBaseTexture);
                            r = 13/2;
                            entity.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                            entityCross.setTexture(turretCrosshairTexture);
                            double rCross = 7/2;
                            entityCross.setPosition(graphics.back()->x - rCross, graphics.back()->y - rCross);
                        }
                        else {
                            entityCircle.setRadius(r = 13/2);
                            entityCircle.setFillColor(sf::Color::Transparent);
                            entityCircle.setOutlineColor(sf::Color::Black);
                            entityCircle.setOutlineThickness(1);
                            entityCircle.setPosition(graphics.front()->x - r, graphics.front()->y - r);
                            double rInner = 3.5;
                            entityCircleInner.setRadius(rInner);
                            entityCircleInner.setFillColor(sf::Color::Transparent);
                            entityCircleInner.setOutlineColor(sf::Color::Magenta);
                            entityCircleInner.setOutlineThickness(1);
                            entityCircleInner.setPosition(graphics.front()->x - rInner, graphics.front()->y - rInner);
                            double dCross = 7;
                            if (turret->anim_crosshair <= 3) {
                                dCross = turret->anim_crosshair * 2 + 1;
                            }
                            entitySquare.setSize(sf::Vector2f(dCross - 2, dCross - 2));
                            entitySquare.setFillColor(sf::Color::Transparent);
                            entitySquare.setOutlineColor(sf::Color::Black);
                            entitySquare.setOutlineThickness(1);
                            if (turret->anim_crosshair == EntityGraphics_Turret::CROSSHAIR_PREFIRE) {
                                entitySquare.setOutlineColor(sf::Color::Red);
                            }
                            if (turret->anim_crosshair == EntityGraphics_Turret::CROSSHAIR_POSTFIRE) {
                                entitySquare.setOutlineColor(sf::Color::White);
                            }
                            entitySquare.setPosition(graphics.back()->x - (dCross/2 - 1), graphics.back()->y - (dCross/2 - 1));
                        }
                        if (turret->anim_base == EntityGraphics_Turret::ANIM_FIRING) {
                            vec2 aimDir(graphics.back()->x - graphics.front()->x, graphics.back()->y - graphics.front()->y);
                            aimDir.Normalize();
                            vec2 hit_pos, hit_n;
                            sim->segGrid->GetRaycastDistance(graphics.front()->x, graphics.front()->y, aimDir.x, aimDir.y, hit_pos, hit_n);
                            entityLine[0].position = sf::Vector2f(graphics.front()->x, graphics.front()->y);
                            entityLine[1].position = sf::Vector2f(hit_pos.x, hit_pos.y);
                            entityLine[0].color = sf::Color::Black;
                            entityLine[1].color = sf::Color::Black;
                            entityCircleInner.setFillColor(sf::Color::Magenta);
                        }
                        if (useTextures) {
                            window.draw(entity);
                            if (turret->anim_crosshair != EntityGraphics_Turret::CROSSHAIR_OFF) {
                                window.draw(entityCross);
                            }
                        }
                        else {
                            window.draw(entityCircle);
                            window.draw(entityCircleInner);
                            if (turret->anim_crosshair != EntityGraphics_Turret::CROSSHAIR_OFF) {
                                window.draw(entitySquare);
                            }
                        }
                        window.draw(entityLine);
                    }
                }
            }
        }
        if (playerList.size() != 0 && playerList[0] != nullptr) {
            if (useTextures) {
                sf::Sprite player(ninjaTexture);
                vec2 ninjaRadius(player.getTexture()->getSize().x/2, player.getTexture()->getSize().y/2);
                player.setOrigin(ninjaRadius.x, ninjaRadius.y);
                player.setPosition(playerList[0]->GetPos().x, playerList[0]->GetPos().y);
                EntityGraphics_Ninja* ninja = playerList[0]->GenerateGraphicComponent();
                ninja->UpdateState();
                player.setScale(ninja->facing, 1);
                window.draw(player);
            }
            else {
                double ninjaRadius = 10;
                sf::CircleShape playerCircle(ninjaRadius);
                if (playerList[0]->IsDead()) {
                    ninjaRadius -= 1;
                    playerCircle.setRadius(ninjaRadius);
                    playerCircle.setOutlineColor(sf::Color::Red);
                    playerCircle.setOutlineThickness(1);
                }
                playerCircle.setOrigin(ninjaRadius, ninjaRadius);
                playerCircle.setPosition(playerList[0]->GetPos().x, playerList[0]->GetPos().y);
                playerCircle.setFillColor(sf::Color::Black);
                window.draw(playerCircle);
            }
        }

        if (tileIDs.size() != 0) {
            for (int y = 0; y < gameHeight; ++y) {
                for (int x = 0; x < gameWidth; ++x) {
                    sf::Sprite wall(tiles.at(tileIDs.at(y * gameWidth + x)));
                    wall.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                    window.draw(wall);
                }
            }
        }

        timebarText.setString(app.stats->formattedTime);
        window.draw(timebarText);

        window.display();
    }

    return EXIT_SUCCESS;
}

void Initialize(App_MultiPurpose& app) {
    app.initialize();
    edat::Initialize();
    sim_globals::Initialize();
    Entity_Drone_Base::Initialize();
    Ninja::Initialize();
    edgedefs::Initialize();
    tiledefs::Initialize();
    tiletypes::Initialize();
}

void Inject(App_MultiPurpose& app) {
    app.soloKeys = new PlayerKeys();
    app.coopKeys = new PlayerKeys();
    app.globalKeys = new GlobalKeys();
    app.options = new Options();
    app.stats = new GameStats();
    app.account = new AccountDetails();
    StoreDefaults defaults;
    defaults.soloKeys = app.soloKeys;
    defaults.coopKeys = app.coopKeys;
    defaults.globalKeys = app.globalKeys;
    defaults.options = app.options;
    defaults.account = app.account;
    app.options->coopMode = false;
    defaults.execute();
    //app.soloKeys->bindActionKeyForPlayer(PlayerKeys::LEFT, VK_LEFT, 0);
    //app.soloKeys->bindActionKeyForPlayer(PlayerKeys::RIGHT, VK_RIGHT, 0);
}

vector<int> ImportantKeys(PlayerKeys* soloKeys, GlobalKeys* globalKeys) {
    vector<int> keys;
    keys.push_back(soloKeys->getActionKeyForPlayer(PlayerKeys::JUMP, 0));
    keys.push_back(soloKeys->getActionKeyForPlayer(PlayerKeys::LEFT, 0));
    keys.push_back(soloKeys->getActionKeyForPlayer(PlayerKeys::RIGHT, 0));
    keys.push_back(soloKeys->getActionKeyForPlayer(PlayerKeys::SUICIDE, 0));
    keys.push_back(globalKeys->back);
    keys.push_back(globalKeys->pause);
    keys.push_back(globalKeys->quit);
    return keys;
}

void CheckKeys(SimpleInput& input, vector<int>& keys) {
    for (size_t i = 0; i < keys.size(); ++i) {
        SHORT keyState = GetAsyncKeyState(keys[i]);
        if (keyState & 0x8000) {
            input.NEW_PRIVATE_EVENT_KeyDown(keys[i]);
        } else {
            input.NEW_PRIVATE_EVENT_KeyUp(keys[i]);
        }
    }
}