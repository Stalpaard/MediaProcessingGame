#ifndef ENTITY_H
#define ENTITY_H

#include <QImage>
#include "world.h"
#include "entitystate.h"

class Entity : public QObject, public Tile
{
    Q_OBJECT
public:
    Entity(int xPosition, int yPosition, float strength, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations);
    ~Entity() override = default;
    bool isDefeated() const {return state == EntityState::DEFEATED;}
    bool isWalking() const {return state == EntityState::WALKING;}
    std::shared_ptr<QImage> getRepresentation();
    void setDefeated(bool newvalue);
    void setWalking(bool newvalue);
    void setIdleAnimations(std::shared_ptr<std::vector<std::shared_ptr<QImage>>>  newvalue) {idle_animations = newvalue;}
    void setDeathAnimations(std::shared_ptr<std::vector<std::shared_ptr<QImage>>>  newvalue) {death_animations = newvalue;}
    void setWalkingAnimations(std::shared_ptr<std::vector<std::shared_ptr<QImage>>>  newvalue) {walking_animations = newvalue;}
    virtual void deathAction()=0;
private:
    unsigned long representation_index;
    bool stopAnimation;
    EntityState state;
    std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations;
    std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations;
    std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations;
    std::shared_ptr<std::vector<std::shared_ptr<QImage>>> current_animations;
signals:
    void dead();
};

#endif // ENTITY_H
