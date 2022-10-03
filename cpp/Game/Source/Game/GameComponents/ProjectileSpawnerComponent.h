#pragma once

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Component.h"

namespace Game
{
    class ProjectileSpawnerComponent : public GameEngine::Component
    {
    public:
        ProjectileSpawnerComponent();
        ~ProjectileSpawnerComponent();

        virtual void Update() override;
        void SpawnProjectile();
        void SetFire(bool newFire);

    private:
        bool m_fire;
        float m_duration;
    };
} // namespace Game
