#pragma once

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

namespace Game
{
    class ProjectileComponent : public GameEngine::CollidableComponent
    {
    public:
        ProjectileComponent();
        ~ProjectileComponent();

        virtual void Update() override;
        void SetLifeTime(float lifetime) { m_lifetime = lifetime; }

    private:
        void UpdateProjectileHit();

        float m_lifetime;
        sf::Vector2f m_velocity;
    };
} // namespace Game
