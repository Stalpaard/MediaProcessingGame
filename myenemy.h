#ifndef MYENEMY_H
#define MYENEMY_H

#include "entity.h"

class MyEnemy :  public Entity
{
    Q_OBJECT
public:
    MyEnemy(int xPosition, int yPosition, float strength, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations);
    ~MyEnemy() override = default;
    virtual void deathAction() override{emit dead();}
    QString getTextRepresentation() override;
};

#endif // MYENEMY_H
