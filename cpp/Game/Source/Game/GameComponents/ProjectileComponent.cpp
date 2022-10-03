#include "ProjectileComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/Util/CollisionManager.h"

using namespace Game;

ProjectileComponent::ProjectileComponent() : m_velocity(sf::Vector2f(200.f, 0.f)), m_lifetime(5.f)
{
}

ProjectileComponent::~ProjectileComponent() {}

void ProjectileComponent::Update()
{
    __super::Update();

    float dt = GameEngine::GameEngineMain::GetTimeDelta();

    // Reduce lifetime every frame
    m_lifetime -= dt;

    // Move projectile according to its wanted velocity
    sf::Vector2f wantedVel = m_velocity * dt;
    GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);

    // If below 0, the projectile is dead, hence remove it
    if (m_lifetime < 0.f)
        GameEngine::GameEngineMain::GetInstance()->RemoveEntity(GetEntity());
}