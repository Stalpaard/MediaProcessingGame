#ifndef MYXENEMY_H
#define MYXENEMY_H

#include "entity.h"


class MyXEnemy : public Entity
{
    Q_OBJECT
public:
    MyXEnemy(int xPosition, int yPosition, float strength, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations);
    ~MyXEnemy() override = default;
    virtual void deathAction() override;
private:
    bool respawned;

signals:
    void respawn(int Xpos, int Ypos);
};

#endif // MYXENEMY_H
