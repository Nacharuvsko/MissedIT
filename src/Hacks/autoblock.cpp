#include "autoblock.h"

#include "../Utils/math.h"
#include "../settings.h"
#include "../interfaces.h"

void Autoblock::CreateMove(CUserCmd *cmd)
{
	if (!inputSystem->IsButtonDown(Settings::Autoblock::key)) {
		return;
	}

	C_BasePlayer *localplayer = (C_BasePlayer *) entityList->GetClientEntity(engine->GetLocalPlayer());
	float bestdist = 250.f;
	int index = -1;

	for (int i = 1; i < engine->GetMaxClients(); i++) {
		C_BasePlayer *entity = (C_BasePlayer *) entityList->GetClientEntity(i);

		if (!entity) {
			continue;
		}

		if (!entity->IsAlive() || entity->GetDormant() || entity == localplayer) {
			continue;
		}

		float dist = localplayer->GetVecOrigin().DistTo(entity->GetVecOrigin());

		if (dist < bestdist) {
			bestdist = dist;
			index = i;
		}
	}

	if (index == -1) {
		return;
	}

	C_BasePlayer *target = (C_BasePlayer *) entityList->GetClientEntity(index);

	if (!target) {
		return;
	}

	QAngle angles = Math::CalcAngle(localplayer->GetVecOrigin(), target->GetVecOrigin());

	angles.y -= localplayer->GetEyeAngles()->y;
	Math::NormalizeAngles(angles);

	if (angles.y < 0.0f) {
		cmd->sidemove = 250.f;
	} else if (angles.y > 0.0f) {
		cmd->sidemove = -250.f;
	}
}
