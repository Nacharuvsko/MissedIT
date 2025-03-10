#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"

#include "../Hacks/fovchanger.h"
#include "../Hacks/thirdperson.h"
#include "../Hacks/grenadeprediction.h"
#include "../Hacks/AntiAim/fakeduck.h"
#include "../Hacks/AntiAim/antiaim.h"

float OverrideView::currentFOV = 90.0f;

typedef void (*OverrideViewFn)(void *, CViewSetup *);

void Hooks::OverrideView(void *thisptr, CViewSetup *pSetup)
{
	if (!engine->IsTakingScreenshot()) {
		GrenadePrediction::OverrideView(pSetup);
		FOVChanger::OverrideView(pSetup);
		ThirdPerson::OverrideView(pSetup);
		FakeDuck::OverrideView(pSetup);
		AntiAim::OverrideView(pSetup);
	}

	OverrideView::currentFOV = pSetup->fov;

	clientModeVMT->GetOriginalMethod<OverrideViewFn>(19)(thisptr, pSetup);
}
