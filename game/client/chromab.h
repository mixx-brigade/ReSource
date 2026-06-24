//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Screen-space chromatic aberration post-process effect
//
//===========================================================================//

#ifndef CHROMAB_H
#define CHROMAB_H

#include "screenspaceeffects.h"

class CChromAberEffect : public IScreenSpaceEffect
{
public:
    CChromAberEffect();

    void Init(void);
    void Shutdown(void);
    void SetParameters( KeyValues *params );
    void Enable( bool bEnable );
    bool IsEnabled(void);
    void Render( int x, int y, int w, int h );

private:
    bool m_bEnabled;
};

#endif // CHROMAB_H
