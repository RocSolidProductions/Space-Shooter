#include "EntityCreator.h"
#include "components/PlayerControl.h"
#include "components/Motion.h"
#include "components/Position.h"
#include "components/State.h"
#include "components/Display.h"
#include "components/Gun.h"
#include "components/Bullet.h"
#include "components/Volume.h"
#include "components/SpaceShip.h"
#include "components/Obstacle.h"
#include "components/Health.h"
#include "components/Menu.h"
#include "components/AiControl.h"
#include "components/Enemy.h"
#include "graphics/SpaceShipView.h"
#include "graphics/BulletView.h"
#include "graphics/BackgroundView.h"
#include "graphics/AsteroidView.h"
#include "graphics/AsteroidBossView.h"
#include "graphics/StartMenuView.h"
#include "graphics/GameOverMenuView.h"
#include "graphics/LevelCompMenuView.h"
#include "ai/FirstBossAi.h"
#include "SpriteSheet.h"
#include "ScreenSize.h"

using namespace entityx;

StartMenuCreator::StartMenuCreator()
{
}

void StartMenuCreator::create(Entity entity)
{
   auto pSmv = std::make_shared<StartMenuView>();
   entity.assign<Menu>(IMenuSP(pSmv));
   entity.assign<Position>(Vector2(ScreenSize::width()/2.0, ScreenSize::height()*0.33));
   entity.assign<Display>(IDrawableSP(pSmv));
}

GameOverMenuCreator::GameOverMenuCreator()
{
}

void GameOverMenuCreator::create(Entity entity)
{
   auto pSmv = std::make_shared<GameOverMenuView>();
   entity.assign<Menu>(IMenuSP(pSmv));
   entity.assign<Position>(Vector2(ScreenSize::width()/2.0, ScreenSize::height()*0.33));
   entity.assign<Display>(IDrawableSP(pSmv));
}

LevelCompMenuCreator::LevelCompMenuCreator()
{
}

void LevelCompMenuCreator::create(Entity entity)
{
   auto pSmv = std::make_shared<LevelCompMenuView>();
   entity.assign<Menu>(IMenuSP(pSmv));
   entity.assign<Position>(Vector2(ScreenSize::width()/2.0, ScreenSize::height()*0.33));
   entity.assign<Display>(IDrawableSP(pSmv));
}

BackgroundCreator::BackgroundCreator(double scrollSpeed)
: m_scrollSpeed(scrollSpeed)
{
}

void BackgroundCreator::create(Entity entity)
{
   entity.assign<Motion>(Vector2(0.0, m_scrollSpeed));
   entity.assign<Position>();
   entity.assign<Display>(IDrawableSP(new BackgroundView()));
}


SpaceShipCreator::SpaceShipCreator()
{
}

void SpaceShipCreator::create(Entity entity)
{
   auto volume = Volume();
   volume.m_boxes.push_back(CollisionBox(32, 32));
   auto pSpriteSheet = new SpriteSheet("../images/SpriteSheet.png", 32);
   auto pSsv = std::make_shared<SpaceShipView>( pSpriteSheet );
   entity.assign<SpaceShip>();
   entity.assign<PlayerControl>();
   entity.assign<Motion>();
   entity.assign<Position>(Vector2(400.0, 300.0));
   entity.assign<Gun>(Vector2(0.0, -1.0));
   entity.assign<Volume>(volume);
   entity.assign<State>(IAnimatibleSP(pSsv));
   entity.assign<Display>(IDrawableSP(pSsv));
}


AsteroidCreator::AsteroidCreator(const Vector2 &position,
                                 const Vector2 &velocity)
: m_position(position)
, m_velocity(velocity)
{
}

void AsteroidCreator::create(Entity entity)
{
   auto volume = Volume();
   volume.m_boxes.push_back(CollisionBox(32, 32));
   auto pSpriteSheet = new SpriteSheet("../images/SpriteSheet.png", 32);
   auto pAv = new AsteroidView( pSpriteSheet );
   entity.assign<Enemy>(ET_Asteroid);
   entity.assign<Health>(5);
   entity.assign<Motion>(m_velocity);
   entity.assign<Position>(m_position);
   entity.assign<Volume>(volume);
   entity.assign<Display>(IDrawableSP(pAv));
}

BulletCreator::BulletCreator(Entity::Id ownerId,
                             const Vector2 &position,
                             const Vector2 &velocity,
                             BulletType bulletType)
: m_ownerId(ownerId)
, m_position(position)
, m_velocity(velocity)
, m_bulletType(bulletType)
{
}

void BulletCreator::create(Entity entity)
{
   auto damage = BulletDamageTable::lookup(m_bulletType);
   auto volume = Volume();
   volume.m_boxes.push_back(CollisionBox(4, 8));
   auto pBv = new BulletView();
   entity.assign<Motion>(m_velocity);
   entity.assign<Position>(m_position);
   entity.assign<Bullet>(m_ownerId, 10000.0, damage);
   entity.assign<Volume>(volume);
   entity.assign<Display>(IDrawableSP(pBv));
}

FirstBossCreator::FirstBossCreator(Entity::Id enemyId,
                                   const Vector2& position,
                                   double scrollSpeed)
: m_enemyId(enemyId)
, m_position(position)
, m_scrollSpeed(scrollSpeed)
{
}

void FirstBossCreator::create(Entity entity)
{
   auto volume = Volume();
   volume.m_boxes.push_back(CollisionBox(96, 96));
   auto pSpriteSheet = new SpriteSheet("../images/SpriteSheet.png", 32);
   auto pAv = new AsteroidBossView( pSpriteSheet );
   entity.assign<AiControl>(IAiSP(new FirstBossAi(entity.id(), m_enemyId, m_scrollSpeed)));
   entity.assign<Enemy>(ET_Boss);
   entity.assign<Health>(10);
   entity.assign<Motion>();
   entity.assign<Position>(m_position);
   entity.assign<Gun>(Vector2(0.0, 1.0));
   entity.assign<Volume>(volume);
   entity.assign<Display>(IDrawableSP(pAv));
}
