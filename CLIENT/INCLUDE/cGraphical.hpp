// This belongs to mathias.blanchard01@gmail.com
// Notify me if you are using it, if your nice 


#ifndef cGraphical_HPP_
#define cGraphical_HPP_
#include "SFML/Graphics.hpp"
#include <memory>
#include <iostream>
#include "iComponent.hpp"

enum direction_e {
    LEFT_TO_RIGHT = 0,
    TOP_TO_BOTTOM,
};

class cGraphicalAnimation {
    public:
        cGraphicalAnimation(std::string _name, int nbFrame, int64_t milli, sf::IntRect rect);
        ~cGraphicalAnimation();
        std::string name();
        int nbFrame();
        int64_t milliseconds();
        sf::IntRect rect();

    private:
        std::string _name;
        int _nbFrame;
        int64_t _milliseconds;
        sf::IntRect _rect;
};


class cGraphical  final: public iComponent {
    public:
    // Create a cGraphical from a path
    cGraphical(sf::String path, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir = LEFT_TO_RIGHT, std::string NAME = "");

    // Create a cGraphical from a already loaded sf::Texture
    cGraphical(sf::Texture texture, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir = LEFT_TO_RIGHT, std::string NAME = "");

    // Create a small cGraphical from a path, no animation.
    cGraphical(sf::String path, sf::IntRect rect);

    // Create a small cGraphical from a already loaded texture, no animation.
    cGraphical(sf::Texture texture, sf::IntRect rect);

    /// Change animation loop, if name keep to default it doesn't save
    void changeAnimationLoop(sf::IntRect rect, int64_t milliseconds, int nbFrame, std::string name = "DEFAULT");

    /// Change animation loop to a pre register one
    void changeAnimationLoop(std::string name);

    /// Return the current frame
    int update();

    /// Add a loop to _saved
    void addAnimationLoop(std::string name, int nbFrame, int64_t milli, sf::IntRect rect);

    /// Display sprite on window
    void display(sf::RenderWindow &window);

    /// Check if point is in hitbox, don't handle rotation
    bool intersect(sf::Vector2f point);
    bool intersect(sf::Vector2i point);
    bool intersect(sf::Vector2u point);
    bool intersect(sf::IntRect rect);


    /// Add preregister animation in the wait list
    void addToQueue(std::string animation);

    /// Return hitbox, useful for debugging
    sf::IntRect getHitbox();

    /// Return reference to a sprite
    sf::Sprite &getSprite();

    /// Return name of the playing animation
    std::string getName();

    /// Get number of frame
    int getNbFrame();

    /// Get Milliseconds
    int64_t getMilliseconds();

    /// Get clock
    sf::Clock getClock();

    /// GetTexture
    sf::Texture getTexture();

    /// Synchronize two animation
    void synchronize(cGraphical toSynchronize);

    void setTimingMilliseconds(int64_t milli);
    bool isActualFrame(int _frame);

    eComponentList getComponentType() override;
    iComponent *clone() override;
    void Destroy() { delete this; }
    ~cGraphical();
private:
    std::vector<std::string> _queue;
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Clock _clock;
    direction_e _dir;
    int _checkedFrame;

    int64_t _timingMilliseconds;
    sf::IntRect _rect;
    int _nbFrame;
    std::string _name;
    std::vector<cGraphicalAnimation> _saved;
};


#endif /* !PARALLAX_HPP_ */
