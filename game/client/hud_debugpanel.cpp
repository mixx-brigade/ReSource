#include "cbase.h"
#include "hud_debugpanel.h"

#include "iclientmode.h"
#include "hud_macros.h"
#include "c_baseplayer.h"

DECLARE_HUDELEMENT(CHudDebugPanel);

ConVar cl_debug_panel("cl_debug_panel", "0");

using namespace vgui;

CHudDebugPanel::CHudDebugPanel(const char *pElementName)
	: CHudElement(pElementName),
	BaseClass(NULL, "DebugPanel")
{
	SetParent(g_pClientMode->GetViewport());

	SetTitle("Debug Panel", true);

	SetPos(50, 50);
	SetSize(250, 150);

	SetMoveable(true);
	SetSizeable(false);
	SetCloseButtonVisible(false);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);

	m_pSpeedLabel = new Label(this, "SpeedLabel", "");
	m_pSpeedLabel->SetPos(10, 30);
	m_pSpeedLabel->SetSize(200, 20);

	m_pFPSLabel = new Label(this, "FPSLabel", "");
	m_pFPSLabel->SetPos(10, 50);
	m_pFPSLabel->SetSize(200, 20);

	SetVisible(false);
}

void CHudDebugPanel::Init()
{
}

void CHudDebugPanel::VidInit()
{
}

void CHudDebugPanel::OnThink()
{
	SetVisible(cl_debug_panel.GetBool());

	C_BasePlayer *player = C_BasePlayer::GetLocalPlayer();

	if (!player)
		return;

	float speed = player->GetAbsVelocity().Length2D();
	float fps = 1.0f / gpGlobals->frametime;

	wchar_t buffer[64];

	swprintf(buffer, ARRAYSIZE(buffer), L"Speed: %.0f", speed);
	m_pSpeedLabel->SetText(buffer);

	swprintf(buffer, ARRAYSIZE(buffer), L"FPS: %.0f", fps);
	m_pFPSLabel->SetText(buffer);
}