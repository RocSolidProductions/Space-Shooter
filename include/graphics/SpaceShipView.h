#ifndef SPACESHIPVIEW_H
#define SPACESHIPVIEW_H

#include "graphics/IDrawable.h"
#include "graphics/IAnimatible.h"

enum SpaceShipState
{
   SSS_Idle,
   SSS_Right1,
   SSS_Right2,
   SSS_Right3,
};

class SpaceShipView
      : public IAnimatible
      , public IDrawable
{
public:

   SpaceShipView();

   void animate(const Vector2 velocity, double dt);

   void draw();

private:

   SpaceShipState m_state;

   double m_duration;
};

#endif // SPACESHIPVIEW_H
