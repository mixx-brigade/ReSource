#include "cbase.h"
#include "fxaa.h"

#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialsystem.h"
#include "materialsystem/imaterialvar.h"
#include "tier0/memdbgon.h"

ConVar mat_fxaa("mat_fxaa", "1", FCVAR_ARCHIVE, "Enable FXAA post-processing");

IMaterial* g_pFXAAMaterial = nullptr;

CFXAAEffect::CFXAAEffect()
{
	m_bEnabled = true;
}

void CFXAAEffect::Init()
{
	g_pFXAAMaterial = materials->FindMaterial("effects/fxaa", TEXTURE_GROUP_OTHER, true);
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

	pRC->PushRenderTargetAndViewport();

	// This is the correct Source-style fullscreen draw
	pRC->DrawScreenSpaceRectangle(
		g_pFXAAMaterial,
		0, 0, w, h,     // dest rect
		0, 0, 1, 1,     // UVs
		w, h            // texture size
	);

	pRC->PopRenderTargetAndViewport();
}

// Register effect
ADD_SCREENSPACE_EFFECT(CFXAAEffect, fxaa);