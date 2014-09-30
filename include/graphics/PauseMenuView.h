#ifndef PAUSEMENUVIEW_H
#define PAUSEMENUVIEW_H

#include "graphics/IDrawable.h"
#include "components/IMenu.h"

class PauseMenuView
      : public IDrawable
      , public IMenu
{
public:

    PauseMenuView();

    void update(const KeyHandler &keyHandler,
                entityx::EventManager& eventManager);

    void draw(const Position& pos);

 private:

    GLuint m_texture;

    float m_halfLogoWidth;

    float m_halfLogoHeight;
 };
#endif // PAUSEMENUVIEW_H
