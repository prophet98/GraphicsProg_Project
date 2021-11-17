//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

extern void ExitGame() noexcept;

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	m_deviceResources->SetWindow(window, width, height);

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);
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

	// TODO: Add your game logic here.

	auto kb = m_keyboard->GetState();
	if (kb.Escape)
	{
		ExitGame();
	}

	auto mouse = m_mouse->GetState();


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

	const wchar_t* output = L"Hello World";

	m_spriteBatch->Draw(m_background.Get(), m_fullscreenRect);

	Vector2 origin = m_font->MeasureString(output) / 2.f;

	m_font->DrawString(m_spriteBatch.get(), output,
		m_fontPos, Colors::White, 0.f, origin);

	m_spriteBatch->End();

	context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(m_states->DepthNone(), 0);
	context->RSSetState(m_states->CullNone());

	m_effect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_batch->Begin();
	
	RECT test;
	test.left = 0.0f;
	test.top = 0.0f;
	test.right = 200.0f;
	test.bottom = 100.0f;


	VertexPositionColor v1(Vector2(test.left, test.top), Colors::Yellow);
	VertexPositionColor v2(Vector2((test.left + test.right), test.top), Colors::Yellow);
	VertexPositionColor v3(Vector2(test.right, test.bottom), Colors::Yellow);
	VertexPositionColor v4(Vector2(test.left, test.top + test.bottom), Colors::Yellow);

	m_batch->DrawQuad(v1, v2, v3, v4);

	m_batch->End();


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
	// TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).
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
			m_inputLayout.ReleaseAndGetAddressOf())
	);

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
}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion
