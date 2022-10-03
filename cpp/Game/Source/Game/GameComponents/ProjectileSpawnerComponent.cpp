#include "ProjectileSpawnerComponent.h"
#include "ProjectileComponent.h"

#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

using namespace Game;

ProjectileSpawnerComponent::ProjectileSpawnerComponent() : m_fire(false), m_duration(5.f) {}

ProjectileSpawnerComponent::~ProjectileSpawnerComponent() {}

void ProjectileSpawnerComponent::SetFire(bool newFire)
{
    m_fire = newFire;
}

void ProjectileSpawnerComponent::Update()
{
    __super::Update();

    // float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
    // m_duration -= 5 * dt;

    // if (m_fire && m_duration > 0.f)
    // {
    //     SpawnProjectile();
    // }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    // {
    //     m_fire = true;
    // }
    // else
    // {
    //     if (m_fire)
    //     {
    //         float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
    //         m_duration -= 3 * dt;

    //         if (m_duration > 0.f)
    //         {
    //             SpawnProjectile();
    //         }
    //     }

    //     m_fire = false;
    //     m_duration = 5.f;
    // }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_fire = true;
    }
    else
    {
        if (m_fire)
        {
            SpawnProjectile();
        }

        m_fire = false;
    }
}

void ProjectileSpawnerComponent::SpawnProjectile()
{
    GameEngine::Entity *projectile = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(projectile);

    projectile->SetPos(GetEntity()->GetPos() + sf::Vector2f(20.f, 0.f));
    projectile->SetSize(sf::Vector2f(20.f, 20.f));

    GameEngine::SpriteRenderComponent *render = static_cast<GameEngine::SpriteRenderComponent *>(projectile->AddComponent<GameEngine::SpriteRenderComponent>());

    render->SetTexture(GameEngine::eTexture::Fireball);
    render->SetFillColor(sf::Color::Transparent);
    render->SetZLevel(2);

    ProjectileComponent *projectileComponent = static_cast<ProjectileComponent *>(projectile->AddComponent<ProjectileComponent>());
}