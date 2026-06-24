//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Screen-space vignette post-process effect.
//          Darkens screen corners with a smooth elliptical radial falloff.
//
//===========================================================================//

#include "cbase.h"
#include "vignette.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialsystem.h"
#include "tier0/memdbgon.h"

ConVar mat_vignette( "mat_vignette", "1", FCVAR_ARCHIVE, "Enable/disable screen vignette effect" );
ConVar mat_vignette_strength( "mat_vignette_strength", "0.70", FCVAR_ARCHIVE, "Vignette darkening strength (0=none, 1=full)" );
ConVar mat_vignette_radius( "mat_vignette_radius", "0.30", FCVAR_ARCHIVE, "Vignette inner radius (0=center, 0.5=edge)" );

static IMaterial*    g_pVignetteMaterial = nullptr;
static IMaterialVar* g_pVignetteStrength = nullptr;
static IMaterialVar* g_pVignetteRadius   = nullptr;

CVignetteEffect::CVignetteEffect()
{
    m_bEnabled = true;
}

void CVignetteEffect::Init( void )
{
    g_pVignetteMaterial = materials->FindMaterial( "effects/vignette", TEXTURE_GROUP_OTHER, true );
    if ( g_pVignetteMaterial )
    {
        bool bFound = false;
        g_pVignetteStrength = g_pVignetteMaterial->FindVar( "$c0_x", &bFound, false );
        g_pVignetteRadius   = g_pVignetteMaterial->FindVar( "$c0_y", &bFound, false );
    }
}

void CVignetteEffect::Shutdown( void )
{
}

void CVignetteEffect::SetParameters( KeyValues *params )
{
}

void CVignetteEffect::Enable( bool bEnable )
{
    m_bEnabled = bEnable;
}

bool CVignetteEffect::IsEnabled( void )
{
    return m_bEnabled && mat_vignette.GetBool();
}

void CVignetteEffect::Render( int x, int y, int w, int h )
{
    if ( !IsEnabled() || !g_pVignetteMaterial )
        return;

    if ( g_pVignetteStrength )
        g_pVignetteStrength->SetFloatValue( mat_vignette_strength.GetFloat() );
    if ( g_pVignetteRadius )
        g_pVignetteRadius->SetFloatValue( mat_vignette_radius.GetFloat() );

    IMatRenderContext *pRenderContext = materials->GetRenderContext();

    pRenderContext->PushRenderTargetAndViewport();
    pRenderContext->Bind( g_pVignetteMaterial );

    CMatRenderContextPtr pRC( materials );
    pRC->DrawScreenSpaceQuad( g_pVignetteMaterial );

    pRenderContext->PopRenderTargetAndViewport();
}

// Register as a screen-space effect
ADD_SCREENSPACE_EFFECT( CVignetteEffect, vignette );
