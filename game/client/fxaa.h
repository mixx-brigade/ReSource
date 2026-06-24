#ifndef FXAA_H
#define FXAA_H
#ifdef _WIN32
#pragma once
#endif

#include "ScreenSpaceEffects.h"

class CFXAAEffect : public IScreenSpaceEffect
{
public:
	CFXAAEffect();

	// IScreenSpaceEffect implementation
	virtual void Init(void);
	virtual void Shutdown(void);

	virtual void SetParameters(KeyValues* params);

	virtual void Enable(bool bEnable);
	virtual bool IsEnabled(void);

	virtual void Render(int x, int y, int w, int h);

private:
	bool m_bEnabled;
};

#endif // FXAA_H