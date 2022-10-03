#include "PowerUpEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/ButtonComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

PowerUpEntity::PowerUpEntity()
{
    m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
    m_renderComponent->SetFillColor(sf::Color::Red);
    m_renderComponent->SetTexture(GameEngine::eTexture::PowerUp);
    m_renderComponent->SetZLevel(2);
    m_renderComponent->SetTileIndex(0, 0);

    AddComponent<GameEngine::CollidableComponent>();
    AddComponent<GameEngine::ButtonComponent>();

    SetEntityTag("PowerUp");
}

PowerUpEntity::~PowerUpEntity()
{
}

void PowerUpEntity::OnAddToWorld()
{
    Entity::OnAddToWorld();
}

void PowerUpEntity::OnRemoveFromWorld()
{
    Entity::OnRemoveFromWorld();
}
