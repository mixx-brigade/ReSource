#include "cbase.h"
#include "env_debugmessage.h"

LINK_ENTITY_TO_CLASS(env_debugmessage, CEnvDebugMessage);

BEGIN_DATADESC(CEnvDebugMessage)

DEFINE_KEYFIELD(m_Message, FIELD_STRING, "message"),

DEFINE_INPUTFUNC(FIELD_VOID, "Show", InputShow),

END_DATADESC()


CEnvDebugMessage::CEnvDebugMessage()
{
	m_Message = NULL_STRING;
}


void CEnvDebugMessage::Spawn()
{
	BaseClass::Spawn();


	SetSolid(SOLID_NONE);
	AddEffects(EF_NODRAW);
}


void CEnvDebugMessage::InputShow(inputdata_t &inputdata)
{
	const char *msg = STRING(m_Message);

	if (msg && msg[0] != '\0')
	{
		Msg("[env_debugmessage] %s\n", msg);
	}
	else
	{
		Msg("[env_debugmessage] (no message set)\n");
	}
}