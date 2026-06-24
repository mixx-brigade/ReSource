//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Screen-space vignette post-process effect
//
//===========================================================================//

#ifndef VIGNETTE_H
#define VIGNETTE_H

#include "screenspaceeffects.h"

class CVignetteEffect : public IScreenSpaceEffect
{
public:
    CVignetteEffect();

    void Init(void);
    void Shutdown(void);
    void SetParameters( KeyValues *params );
    void Enable( bool bEnable );
    bool IsEnabled(void);
    void Render( int x, int y, int w, int h );

private:
    bool m_bEnabled;
};

#endif // VIGNETTE_H
