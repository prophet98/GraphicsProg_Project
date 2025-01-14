//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "AnimatedTexture.h"
#include "BrickManager.h"
#include <Paddle.h>

class Ball;
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

	Game() noexcept(false);
	~Game();

	Game(Game&&) = default;
	Game& operator= (Game&&) = default;

	Game(Game const&) = delete;
	Game& operator= (Game const&) = delete;

	// Initialization and management
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	void Tick();

	// IDeviceNotify
	void OnDeviceLost() override;
	void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const noexcept;
	void OnNewAudioDevice() noexcept { m_retryAudio = true; }

private:

	void Update(DX::StepTimer const& timer);
	void Render();

	void Clear();

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	// Device resources.
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	// Rendering loop timer.
	DX::StepTimer                           m_timer;

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;
	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::BasicEffect> m_effect;

	RECT m_tileRect;
	RECT m_stretchRect;
	RECT m_fullscreenRect;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_BallTexture;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	using VertexType = DirectX::VertexPositionColor;
	std::unique_ptr<DirectX::PrimitiveBatch<VertexType>> m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	std::unique_ptr<DirectX::SpriteFont> m_font;
	DirectX::SimpleMath::Vector2 m_fontPos;

	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	Ball* ball;
	BrickManager* Manager;
	Paddle* paddle;
	RECT walls;

	//game settings parameters
	static constexpr int brickWidth = 40;
	static constexpr int brickHeigth = 40;
	static constexpr int nBricksAcross = 10;
	static constexpr int nBricksDown = 3;

	bool GameOver = false;

	std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	bool m_retryAudio;

	std::unique_ptr<DirectX::SoundEffect> m_PaddleHitSound;
	std::unique_ptr<DirectX::SoundEffect> m_GameOverSound;
	std::unique_ptr<DirectX::SoundEffect> m_BrickExplSound;
};
