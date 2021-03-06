#include "graphics/LevelCompMenuView.h"
#include "graphics/FontRepository.h"
#include "systems/Events.h"
#include "KeyHandler.h"
#include "ScreenSize.h"

using namespace entityx;

LevelCompMenuView::LevelCompMenuView()
: m_text()
{
   m_text.setFont(FontRepository::getMenuFont());
   m_text.setCharacterSize(40);
   m_text.setString("Level Completed");

   sf::FloatRect bounds(m_text.getLocalBounds());
   m_text.setOrigin(bounds.width/2.0, bounds.height/2.0);
}

void LevelCompMenuView::update(EventManager &events, double dt)
{
}

void LevelCompMenuView::draw(sf::RenderWindow& window)
{
   m_text.setPosition(ScreenSize::width()*0.5,
                      ScreenSize::height()*0.33);

   window.draw(m_text);
}

void LevelCompMenuView::onConfirm(entityx::EventManager& eventManager)
{
    eventManager.emit<EvStartGame>();
}

