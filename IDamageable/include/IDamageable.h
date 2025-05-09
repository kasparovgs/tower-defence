#ifndef IDAMAGEABLE_H
#define IDAMAGEABLE_H

class IDamageable {
public:
    virtual void takeDamage(std::size_t damage) = 0;
};


#endif