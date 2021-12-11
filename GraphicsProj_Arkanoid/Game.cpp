//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <BrickManager.h>
#include "Ball.h"
extern void ExitGame() noexcept;

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false) :
	m_retryAudio(false)
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
	if (m_audEngine)
	{
		m_audEngine->Suspend();
	}
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	m_deviceResources->SetWindow(window, width, height);
	GameOver = true;
	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);

	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags |= AudioEngine_Debug;
#endif
	m_audEngine = std::make_unique<AudioEngine>(eflags);

	m_BrickExplSound = std::make_unique<SoundEffect>(m_audEngine.get(),
		L"BrickExpl.wav");
	m_GameOverSound = std::make_unique<SoundEffect>(m_audEngine.get(),
		L"GameOver.wav");
	m_PaddleHitSound = std::make_unique<SoundEffect>(m_audEngine.get(),
		L"PaddleHit.wav");



	ball = new Ball(Vector2(500.0f, 500.0f), Vector2(-1.0f, -1.0f));
	Manager = new BrickManager(std::move(m_BrickExplSound));
	paddle = new Paddle(Vector2(550.0f, 550.0f), 60.0, 10.0f);
	//Manager->CreateBricks(nBricksAcross, nBricksDown, brickWidth, brickHeigth);
	walls.left = 0.0f;
	walls.top = 0.0f;
	walls.right = width;
	walls.bottom = height;


	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
	m_timer.Tick([&]()
		{
			Update(m_timer);
		});

	Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	if (m_retryAudio)
	{
		m_retryAudio = false;
		if (m_audEngine->Reset())
		{
			// TODO: restart any looped sounds here
		}
	}
	else if (!m_audEngine->Update())
	{
		if (m_audEngine->IsCriticalError())
		{
			m_retryAudio = true;
		}
	}

	// TODO: Add your game logic here.

	auto kb = m_keyboard->GetState();
	if (kb.Escape)
	{
		ExitGame();
	}
	if (kb.Space && GameOver)
	{
		GameOver = false;
		Manager->RemoveAllBricks();
		Manager->CreateBricks(nBricksAcross, nBricksDown, brickWidth, brickHeigth);
	}
	//paddle inputs
	paddle->Update(kb, elapsedTime);

	auto mouse = m_mouse->GetState();
	if (!GameOver)
	{
		ball->Update(elapsedTime);
	}
	if (ball->DoWallCollision(walls) == 2)
	{
		GameOver = true;
		m_GameOverSound->Play();
	}

	if (!GameOver)
	{
		ball->DoWallCollision(walls);
		paddle->DoWallCollision(walls);
		if (paddle->DoBallCollision(*ball))
		{
			if (!m_PaddleHitSound->IsInUse())
			{
				m_PaddleHitSound->Play();
			}
		}

	}

	elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	// TODO: Add your rendering code here.
	float time = float(m_timer.GetTotalSeconds());

	m_spriteBatch->Begin();

	const wchar_t* output = L"Level 0-1";

	if (GameOver)
	{
		output = L"Press Space To Start";
	}

	m_spriteBatch->Draw(m_background.Get(), m_fullscreenRect);

	Vector2 origin = m_font->MeasureString(output) / 2.f;
	m_font->DrawString(m_spriteBatch.get(), output,
		m_fontPos, Colors::White, 0.f, origin);

	m_spriteBatch->Draw(m_BallTexture.Get(), ball->GetPosition(), nullptr,
		Colors::White, 0.f, m_origin, .03f);

	m_spriteBatch->End();

	if (!GameOver)
	{
		context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
		context->OMSetDepthStencilState(m_states->DepthNone(), 0);
		context->RSSetState(m_states->CullNone());

		m_effect->Apply(context);

		context->IASetInputLayout(m_inputLayout.Get());

		m_batch->Begin();
		paddle->Draw(m_batch);
		Manager->UpdateBrickState(Manager->brickList, *ball, m_batch);

		m_batch->End();
	}


	context;

	m_deviceResources->PIXEndEvent();

	// Show the new frame.
	m_deviceResources->Present();

}

// Helper method to clear the back buffers.
void Game::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
	m_audEngine->Suspend();
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	m_audEngine->Resume();
}

void Game::OnWindowMoved()
{
	auto r = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

	// TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 800;
	height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();
	m_states = std::make_unique<CommonStates>(device);
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
	m_font = std::make_unique<SpriteFont>(device, L"myfile.spritefont");
	m_effect = std::make_unique<BasicEffect>(device);
	m_effect->SetVertexColorEnabled(true);

	ComPtr<ID3D11Resource> resource;
	// TODO: Initialize device dependent objects here (independent of window size).
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(device, L"Background.png", nullptr,
			m_background.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexType>(device, m_effect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(device, L"ball.png",
			resource.GetAddressOf(),
			m_BallTexture.ReleaseAndGetAddressOf()));
	ComPtr<ID3D11Texture2D> ballTex;
	DX::ThrowIfFailed(resource.As(&ballTex));
	CD3D11_TEXTURE2D_DESC ballDesc;
	ballTex->GetDesc(&ballDesc);

	m_origin.x = float(ballDesc.Width / 2);
	m_origin.y = float(ballDesc.Height / 2);

	m_batch = std::make_unique<PrimitiveBatch<VertexType>>(context);

	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.
	auto size = m_deviceResources->GetOutputSize();
	Matrix proj = Matrix::CreateScale(2.f / float(size.right),
		-2.f / float(size.bottom), 1.f)
		* Matrix::CreateTranslation(-1.f, 1.f, 0.f);
	m_effect->SetProjection(proj);
	m_screenPos.x = float(size.right) / 2.f;
	m_screenPos.y = float(size.bottom) / 10.f;

	m_stretchRect.left = size.right / 4;
	m_stretchRect.top = size.bottom / 4;
	m_stretchRect.right = m_stretchRect.left + size.right / 2;
	m_stretchRect.bottom = m_stretchRect.top + size.bottom / 2;

	m_fullscreenRect = m_deviceResources->GetOutputSize();

	m_fontPos.x = float(size.right) / 2.f;
	m_fontPos.y = float(size.bottom) / 2.f;
}

void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
	//m_texture.Reset();
	m_spriteBatch.reset();
	m_states.reset();
	m_background.Reset();
	m_font.reset();
	m_effect.reset();
	m_batch.reset();
	m_inputLayout.Reset();
	m_BallTexture.Reset();

}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion
