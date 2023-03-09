#include "../../INCLUDE/ComponentsLibrary.hpp"

ComponentsLibrary::ComponentsLibrary()
{
    std::vector<iComponent *> player;
    cGraphical *pGraph = new cGraphical("assets/isaac.png", sf::IntRect(0, 0, 30, 30));
    pGraph->getSprite().scale(3, 3);
    pGraph->addAnimationLoop("stage1R", 2, 150, sf::IntRect(64, 0, 32, 26));
    pGraph->changeAnimationLoop("stage1R");
    player.emplace_back(pGraph);
    player.emplace_back(new cStats());
    player.emplace_back(new cWeapon(10, 1.5));
    player.emplace_back(new cControllable);
    player.emplace_back(new cSpeed(0, 0, 5));
    player.emplace_back(new cCollision(collision1, 0.5, 5, 3));
    player.emplace_back(new cScene(eGameScene::GAME_SCENE));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(1, player));

    std::vector<iComponent *> tear;
    tear.emplace_back(new cGraphical("assets/tear.png", sf::IntRect(0, 0, 16, 16)));
    tear.emplace_back(new cSpeed(20, 0, 250));
    tear.emplace_back(new cCollision(collision2, 0, 1, 1));
    tear.emplace_back(new cScene(eGameScene::GAME_SCENE));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(2, tear));
    
    std::vector<iComponent *> redtear;
    redtear.emplace_back(new cGraphical("assets/tear.png", sf::IntRect(16, 16, 16, 16)));
    redtear.emplace_back(new cSpeed(20, 0));
    redtear.emplace_back(new cCollision(collision3, 0, 1, 1));
    redtear.emplace_back(new cScene(eGameScene::GAME_SCENE));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(10, redtear));

    std::vector<iComponent *> background;
    cGraphical *bgGraph = new cGraphical("assets/tileset.png", sf::IntRect(0, 0, 100000, 100000));
    bgGraph->getSprite().setScale(5, 5);
    bgGraph->getSprite().setTexture(bgGraph->getTexture());
    background.emplace_back(bgGraph);
    background.emplace_back(new cSpeed(-10, 0));
    background.emplace_back(new cScene(eGameScene::GAME_SCENE));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(3, background));

    std::vector<iComponent *> fog;
    cGraphical *fogGraph = new cGraphical("assets/fog.png", sf::IntRect(5, 5, 100000, 100000));
    fogGraph->getSprite().setScale(5, 5);
    fogGraph->getSprite().setTexture(fogGraph->getTexture());
    fog.emplace_back(fogGraph);
    fog.emplace_back(new cSpeed(-15, 0));
    fog.emplace_back(new cScene(eGameScene::GAME_SCENE));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(4, fog));

    std::vector<iComponent *> menu;
    cGraphical *mGraph = new cGraphical("assets/menu.png", sf::IntRect(0, 0, 480, 256));
    mGraph->getSprite().setScale({8, 8});
    menu.emplace_back(mGraph);
    menu.emplace_back(new cText("assets/font1.ttf", 80, sf::Color::Black, "TEST"));
    menu.emplace_back(new cScene(eGameScene::MENU_SCENE));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(5, menu));

    std::vector<iComponent*> charger;
    cGraphical *mCharger = new cGraphical("assets/charger.png", sf::IntRect(0, 0, 32, 32), 100, 4, LEFT_TO_RIGHT, "walk");
    mCharger->addAnimationLoop("attack", 1, 100, sf::IntRect(32 * 4, 0, 32, 32));
    mCharger->getSprite().setScale(4, 4);
    mCharger->getSprite().setPosition(2000, 500);
    charger.emplace_back(mCharger);
    charger.emplace_back(new cScene(eGameScene::GAME_SCENE));
    charger.emplace_back(new cBehaviour(CHARGER));
    charger.emplace_back(new cCollision(eCollisionType::collision3, 0.2, 3, 1));
    charger.emplace_back(new cSpeed(-10, 0));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(6, charger));

    std::vector<iComponent*> spidey;
    cGraphical *mSpidey = new cGraphical("assets/spidey.png", sf::IntRect(0, 0, 48, 48), 45, 12, LEFT_TO_RIGHT, "attack");
    mSpidey->getSprite().setScale(4, 4);
    mSpidey->getSprite().setPosition(1000, 500);
    spidey.emplace_back(mSpidey);
    spidey.emplace_back(new cScene(eGameScene::GAME_SCENE));
    spidey.emplace_back(new cBehaviour(SPIDER));
    spidey.emplace_back(new cCollision(eCollisionType::collision3, 0.2, 4, 1));
    spidey.emplace_back(new cSpeed(0, 0, 20));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(8, spidey));

    std::vector<iComponent*> exfly;
    cGraphical *mExfly = new cGraphical("assets/exfly.png", sf::IntRect(0, 0, 32, 32), 30, 2, LEFT_TO_RIGHT, "idle");
    mExfly->getSprite().setScale(3, 3);
    mExfly->getSprite().setPosition(1000, 500);
    exfly.emplace_back(mExfly);
    exfly.emplace_back(new cScene(eGameScene::GAME_SCENE));
    exfly.emplace_back(new cBehaviour(EXFLY));
    exfly.emplace_back(new cCollision(eCollisionType::collision3, 0.2, 4, 1));
    exfly.emplace_back(new cSpeed(0, 0, 0));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(9, exfly));

    std::vector<iComponent*> bpoo;
    cGraphical *mBpoo = new cGraphical("assets/bpoo.png", sf::IntRect(0, 64, 64, 64), 500, 3, LEFT_TO_RIGHT, "walk");
    mBpoo->addAnimationLoop("charge", 3, 500, sf::IntRect(0, 64, 64, 64));
    mBpoo->addAnimationLoop("runL", 3, 400, sf::IntRect(128, 0, 64, 64));
    mBpoo->addAnimationLoop("runR", 3, 400, sf::IntRect(128, 64, 64, 64));
    mBpoo->getSprite().setScale(4, 4);
    mBpoo->getSprite().setPosition(1800, 500);
    bpoo.emplace_back(mBpoo);
    bpoo.emplace_back(new cScene(eGameScene::GAME_SCENE));
    bpoo.emplace_back(new cBehaviour(BPOO));
    bpoo.emplace_back(new cCollision(eCollisionType::collision3, 0.2, 1, 1));
    bpoo.emplace_back(new cSpeed(-3, 0, 0));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(11, bpoo));

    std::vector<iComponent*> spoo;
    cGraphical *mSpoo = new cGraphical("assets/spoo.png", sf::IntRect(0, 0, 32, 32), 100, 3, LEFT_TO_RIGHT, "walkL");
    mSpoo->addAnimationLoop("walkR", 3, 100, sf::IntRect(0, 32, 32, 32));
    mSpoo->getSprite().setScale(2, 2);
    spoo.emplace_back(mSpoo);
    spoo.emplace_back(new cScene(eGameScene::GAME_SCENE));
    spoo.emplace_back(new cBehaviour(SPOO));
    spoo.emplace_back(new cCollision(eCollisionType::collision3, 0.2, 2, 1));
    spoo.emplace_back(new cSpeed(0, 0, 15));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(12, spoo));

    std::vector<iComponent *> wave;
    cText *twave1 = new cText("assets/font1.ttf", 100, sf::Color::Red, "Round ");
    twave1->getText().setPosition(sf::Vector2f(800, 400));
    wave.emplace_back(twave1);
    wave.emplace_back(new cScene(eGameScene::GAME_SCENE));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(7, wave));

    std::vector<iComponent *> upg;
    cText *tUpg = new cText("assets/font1.ttf", 100, sf::Color::Red, "Round ");
    tUpg->getText().setPosition(sf::Vector2f(800, 400));
    upg.emplace_back(new cScene(eGameScene::GAME_SCENE));
    upg.emplace_back(twave1);
    upg.emplace_back(new cScene(eGameScene::GAME_SCENE));
    _library.insert(std::pair<size_t, std::vector<iComponent *>>(7, upg));

}

ComponentsLibrary::~ComponentsLibrary()
{
    
}

std::vector<iComponent *> ComponentsLibrary::getVectorComponents(size_t entity)
{
    std::vector<iComponent *> cpy;
    for (size_t i = 0; i != _library.at(entity).size(); i++) {
        cpy.push_back(_library.at(entity)[i]->clone());
    }
    return (cpy);
}