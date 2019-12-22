#ifndef MYPROTAGONIST_H
#define MYPROTAGONIST_H

#include "world.h"

class MyProtagonist : public Protagonist
{
public:
    MyProtagonist(QImage* representation);
    QImage* getRepresentation() const{
        return representation;
    }
private:
    QImage* representation;
};

#endif // MYPROTAGONIST_H
