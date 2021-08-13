#pragma once
#include "pch.h"
#include "EuroScopePlugIn.h"
#include "Structures.h"
#include "RoutesHelper.h"
#include "DataHandler.h"
#include "MenuBar.h"
#include <string>
#include <gdiplus.h>

using namespace std;
using namespace Gdiplus;
using namespace EuroScopePlugIn;

class CCommonRenders // Commonly rendered items, here for ease of access
{
	public: 
		static CRect RenderButton(CDC* dc, CRadarScreen* screen, POINT topLeft, int width, int height, CWinButton* obj, int vtcAlign = -1);
		static void RenderTextInput(CDC* dc, CRadarScreen* screen, POINT topLeft, int width, int height, CTextInput* obj);
		static CRect RenderCheckBox(CDC* dc, Graphics* g, CRadarScreen* screen, POINT topLeft, int height, CCheckBox* obj);
		static void RenderDropDown(CDC* dc, Graphics* g, CRadarScreen* screen, POINT topLeft, int width, int height, CDropDown* obj);
		static void RenderScrollBar(CDC* dc, Graphics* g, CRadarScreen* screen, POINT topLeft, CWinScrollBar* scrollView);

		// Screen actions
		static void RenderTracks(CDC* dc, Graphics* g, CRadarScreen* screen, COverlayType type, CMenuBar* menubar);
		static void RenderRoutes(CDC* dc, Graphics* g, CRadarScreen* screen);
		static void RenderQDM(CDC* dc, Graphics* g, CRadarScreen* screen, CPosition* position1, CPosition* position2, POINT cursorPosition, CPosition* cursorLatlon);
};

