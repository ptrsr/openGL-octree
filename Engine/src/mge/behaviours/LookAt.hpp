#ifndef LookAt_H
#define LookAt_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Keeps the owner looking at the given target.
 */
class LookAt : public AbstractBehaviour
{
    public:
        LookAt (GameObject * pTarget);
        virtual ~LookAt();

        virtual void update(float pStep);
		void message(sendMsg::Message) { };

    private:
        GameObject * _target;   //what are we looking at?

        LookAt(const LookAt&);
        LookAt& operator=(const LookAt&);

};

#endif // LookAt_H
