#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"
#include "Game/GameComponents/ProjectileComponent.h"
#include "GameEngine/Util/CameraManager.h"
#include "Game/GameEntities/PlayerEntity.h"
#include "Game/GameEntities/ObstacleEntity.h"
#include "Game/GameEntities/PowerUpEntity.h"

using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr), m_backGround(nullptr), m_lastObstacleSpawnTimer(0.f), m_isGameOver(false)
{
	m_player = new PlayerEntity();

	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(50.f, 50.f));
	m_player->SetSize(sf::Vector2f(40.f, 40.f));

	// m_text = new GameEngine::Entity();
	// GameEngine::GameEngineMain::GetInstance()->AddEntity(m_text);
	// m_text->SetParent(m_player);
	// GameEngine::TextRenderComponent* textRenderComponent = m_text->AddComponent<GameEngine::TextRenderComponent>();
	// textRenderComponent->SetFont("arial.ttf");
	// textRenderComponent->SetString("Player!");
	// textRenderComponent->SetZLevel(3);
	// m_text->SetLocalPosOffset(sf::Vector2f(1.f, 1.f));
	// m_text->SetLocalRotOffset(90.f);

	CreateBackGround();
	// Debug
	for (int a = 0; a < 3; ++a)
	{
		// SpawnNewRandomObstacles();
	}
}

GameBoard::~GameBoard()
{
}

void GameBoard::Update()
{
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		if (m_lastObstacleSpawnTimer <= 0.f)
		{
			// SpawnNewRandomObstacles();
			// SpawnNewRandomTiledObstacles();
			// SpawnNewRandomPowerUps();
		}

		// UpdateObstacles(dt);
		// UpdatePowerUps(dt);
		UpdateBackGround();
		UpdatePlayerDying();
	}
}

void GameBoard::UpdateObstacles(float dt)
{
	static float obstacleSpeed = 100.f;

	std::vector<GameEngine::Entity *> obstacles = GameEngine::GameEngineMain::GetInstance()->GetEntitiesByTag("Obstacle");

	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		GameEngine::Entity *obstacle = (*it);
		sf::Vector2f currPos = obstacle->GetPos();
		currPos.x -= obstacleSpeed * dt;
		obstacle->SetPos(currPos);
		// If we are to remove ourselves
		if (currPos.x < -50.f)
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
	}
}

void GameBoard::UpdatePowerUps(float dt)
{
	static float powerUpSpeed = 100.f;

	std::vector<GameEngine::Entity *> powerups = GameEngine::GameEngineMain::GetInstance()->GetEntitiesByTag("PowerUp");

	for (auto it = powerups.begin(); it != powerups.end(); ++it)
	{
		GameEngine::Entity *powerup = (*it);
		sf::Vector2f currPos = powerup->GetPos();
		currPos.x -= powerUpSpeed * dt;
		powerup->SetPos(currPos);
		// If we are to remove ourselves
		if (currPos.x < -50.f)
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(powerup);
	}
}

void GameBoard::UpdatePlayerDying()
{
	bool noGameOver = GameEngine::CameraManager::IsFollowCameraEnabled();

	if (noGameOver)
		return;

	static float xToPlayerDie = 0.f;
	if (m_player->GetPos().x < xToPlayerDie)
	{
		m_isGameOver = true;
	}
}

void GameBoard::SpawnNewRandomObstacles()
{
	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 50.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;

	static float minObstacleHeight = 50.f;
	static float maxObstacleHeight = 170.f;
	static float minObstacleWidth = 20.f;
	static float maxObstacleWidth = 40.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(RandomFloatRange(minObstacleWidth, maxObstacleWidth), RandomFloatRange(minObstacleHeight, maxObstacleHeight));

	SpawnNewObstacle(pos, size);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}

void GameBoard::SpawnNewRandomTiledObstacles()
{
	static int minObstacleCount = 2;
	static int maxObstacleCount = 7;

	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 350.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 80.f;
	static float maxObstacleYPos = 350.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(32.f, 32.f);

	int obstacleCount = (int)RandomFloatRange((float)minObstacleCount, (float)maxObstacleCount);
	for (int a = 0; a < obstacleCount; ++a)
	{
		SpawnNewObstacle(pos, size);
		pos.y += size.y;
	}

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}

void GameBoard::SpawnNewObstacle(const sf::Vector2f &pos, const sf::Vector2f &size)
{
	ObstacleEntity *obstacle = new ObstacleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));
}

void GameBoard::SpawnNewRandomPowerUps()
{
	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minPowerUpXPos = 50.f;
	static float maxPowerUpXPos = 450.f;
	static float minPowerUpYPos = 20.f;
	static float maxPowerUpYPos = 450.f;

	// static float minPowerUpHeight = 50.f;
	// static float maxPowerUpHeight = 170.f;
	// static float minPowerUpWidth = 20.f;
	// static float maxPowerUpWidth = 40.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minPowerUpXPos, maxPowerUpXPos), RandomFloatRange(minPowerUpYPos, maxPowerUpYPos));
	// sf::Vector2f size = sf::Vector2f(RandomFloatRange(minPowerUpWidth, maxPowerUpWidth), RandomFloatRange(minPowerUpHeight, maxPowerUpHeight));
	sf::Vector2f size = sf::Vector2f(20.f, 20.f);

	SpawnNewPowerUp(pos, size);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}

void GameBoard::SpawnNewPowerUp(const sf::Vector2f &pos, const sf::Vector2f &size)
{
	// ObstacleEntity *powerup = new ObstacleEntity();
	// Game::PowerUpEntity *powerup = new Game::PowerUpEntity::PowerUpEntity();
	Game::PowerUpEntity *pu = new PowerUpEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(pu);
	pu->SetPos(pos);
	pu->SetSize(sf::Vector2f(size.x, size.y));
}

void GameBoard::SpawnFireball()
{
	GameEngine::Entity *projectile = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(projectile);

	projectile->SetPos(sf::Vector2f(m_player->GetPos().x + 20, m_player->GetPos().y));
	projectile->SetSize(sf::Vector2f(20.f, 20.f));

	GameEngine::SpriteRenderComponent *render = static_cast<GameEngine::SpriteRenderComponent *>(projectile->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetTexture(GameEngine::eTexture::Fireball);
	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(2);

	ProjectileComponent *projectileComponent = static_cast<ProjectileComponent *>(projectile->AddComponent<ProjectileComponent>());
}
 
void GameBoard::CreateBackGround()
{
	GameEngine::Entity *bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent *render = bgEntity->AddComponent<GameEngine::SpriteRenderComponent>();
	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(0);
	bgEntity->SetPos(sf::Vector2f(250.f, 250.f));
	bgEntity->SetSize(sf::Vector2f(500.f, 500.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
}

void GameBoard::UpdateBackGround()
{
	if (!m_backGround || !m_player)
		return;

	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	m_backGround->SetPos(m_player->GetPos());
}