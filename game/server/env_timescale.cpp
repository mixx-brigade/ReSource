#ifndef ENV_TIMESCALE_H
#define ENV_TIMESCALE_H

#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"

class CEnvTimescale : public CPointEntity
{
public:
	DECLARE_CLASS(CEnvTimescale, CPointEntity);
	DECLARE_DATADESC();

	void Spawn() OVERRIDE;

	void InputSetScale(inputdata_t &inputdata);
	void InputReset(inputdata_t &inputdata);

private:
	float m_flScale;
};

#endif