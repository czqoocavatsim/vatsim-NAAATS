#pragma once
#include "pch.h"
#include <gdiplus.h>
#include <EuroScopePlugIn.h>

using namespace std;
using namespace Gdiplus;
using namespace EuroScopePlugIn;

/// Drawing aircraft targets
class CAcTargets
{
	public:
		// Render the airplane icon
		static void DrawAirplane(Graphics* g, CDC* dc, CRadarScreen* screen, CRadarTarget target, int hdg);

		// Render tags
		static void DrawTag(CDC* dc);
};
