#ifndef COLLIDABLE
#define COLLIDABLE

class Collidable {
public:
    virtual int getXpoz() = 0;
    virtual int getYpoz() = 0;
    virtual int getHeight() = 0;
    virtual int getWidth() = 0;
};

#endif // COLLIDABLE

