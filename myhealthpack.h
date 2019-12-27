#ifndef MYHEALTHPACK_H
#define MYHEALTHPACK_H

#include "entity.h"

class MyHealthpack : public Entity
{
public:
    MyHealthpack(int xPosition, int yPosition, float health, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations);
    virtual void deathAction() override{}
    virtual QString getTextRepresentation() override;
};

#endif // MYHEALTHPACK_H
