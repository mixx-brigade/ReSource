#include "cbase.h"
#include "fxaa.h"

#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialsystem.h"
#include "materialsystem/imaterialvar.h"
#include "tier0/memdbgon.h"

ConVar mat_fxaa("mat_fxaa", "1", FCVAR_ARCHIVE, "Enable FXAA post-processing");

CFXAAEffect::CFXAAEffect()	
{
	m_bEnabled = true;
}

void CFXAAEffect::Init()
{
}

void CFXAAEffect::Shutdown()
{
	g_pFXAAMaterial = nullptr;
}

void CFXAAEffect::SetParameters(KeyValues* params)
{
}

void CFXAAEffect::Enable(bool bEnable)
{
	m_bEnabled = bEnable;
}

bool CFXAAEffect::IsEnabled()
{
	return m_bEnabled && mat_fxaa.GetBool();
}

void CFXAAEffect::Render(int x, int y, int w, int h)
{
	if (!IsEnabled())
		return;

	IMatRenderContext* pRenderContext = materials->GetRenderContext();

	pRenderContext->PushRenderTargetAndViewport();

	pRenderContext->Bind(g_pFXAAMaterial);

	// Fullscreen quad
	CMatRenderContextPtr pRC(materials);
	pRC->DrawScreenSpaceQuad(g_pFXAAMaterial);

	pRenderContext->PopRenderTargetAndViewport();
}

// Register effect
ADD_SCREENSPACE_EFFECT(CFXAAEffect, fxaa);