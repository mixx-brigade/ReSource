//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Screen-space chromatic aberration post-process effect.
//          Separates RGB channels toward screen edges for a subtle lens effect.
//
//===========================================================================//

#include "cbase.h"
#include "chromab.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialsystem.h"
#include "tier0/memdbgon.h"

ConVar mat_chromatic_aberration( "mat_chromatic_aberration", "1", FCVAR_ARCHIVE, "Enable/disable chromatic aberration effect" );
ConVar mat_chromatic_aberration_strength( "mat_chromatic_aberration_strength", "0.003", FCVAR_ARCHIVE, "Chromatic aberration strength (0=none, 0.01=strong)" );

static IMaterial*    g_pChromabMaterial = nullptr;
static IMaterialVar* g_pChromabStrength = nullptr;

CChromAberEffect::CChromAberEffect()
{
    m_bEnabled = true;
}

void CChromAberEffect::Init( void )
{
    g_pChromabMaterial = materials->FindMaterial( "effects/chromab", TEXTURE_GROUP_OTHER, true );
    if ( g_pChromabMaterial )
    {
        bool bFound = false;
        g_pChromabStrength = g_pChromabMaterial->FindVar( "$c0_x", &bFound, false );
    }
}

void CChromAberEffect::Shutdown( void )
{
}

void CChromAberEffect::SetParameters( KeyValues *params )
{
}

void CChromAberEffect::Enable( bool bEnable )
{
    m_bEnabled = bEnable;
}

bool CChromAberEffect::IsEnabled( void )
{
    return m_bEnabled && mat_chromatic_aberration.GetBool();
}

void CChromAberEffect::Render( int x, int y, int w, int h )
{
    if ( !IsEnabled() || !g_pChromabMaterial )
        return;

    if ( g_pChromabStrength )
        g_pChromabStrength->SetFloatValue( mat_chromatic_aberration_strength.GetFloat() );

    IMatRenderContext *pRenderContext = materials->GetRenderContext();

    pRenderContext->PushRenderTargetAndViewport();
    pRenderContext->Bind( g_pChromabMaterial );

    CMatRenderContextPtr pRC( materials );
    pRC->DrawScreenSpaceQuad( g_pChromabMaterial );

    pRenderContext->PopRenderTargetAndViewport();
}

// Register as a screen-space effect
ADD_SCREENSPACE_EFFECT( CChromAberEffect, chromatic_aberration );
