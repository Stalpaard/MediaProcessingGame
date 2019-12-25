#ifndef MYPENEMY_H
#define MYPENEMY_H

#include "entity.h"
#include <iostream>

class MyPEnemy : public Entity
{
    Q_OBJECT
public:
    MyPEnemy(int xPosition, int yPosition, float strength, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations);
    ~MyPEnemy() override = default;
    float getPoisonLevel() const;
    void setPoisonLevel(float value);
    virtual void deathAction() override{poison();}
    QString getTextRepresentation() override;


public slots:
    bool poison();

signals:
    void poisonLevelUpdated(float value, int x, int y);

private:
    float poisonLevel;
};

#endif // MYPENEMY_H
