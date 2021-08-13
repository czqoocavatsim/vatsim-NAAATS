#pragma once
#include <map>
#include <string>
#include <vector>
#include <future>
#include <thread>
#include "InboundList.h"
#include "Structures.h"
#include "OtherList.h"
#include "ConflictList.h"
#include "RCLList.h"
#include "MenuBar.h"
#include "NotePad.h"
#include "EuroScopePlugIn.h"
#include "TrackInfoWindow.h"
#include "FlightPlanWindow.h"
#include "MessageWindow.h"

using namespace std;
using namespace EuroScopePlugIn;

// Main radar display
class CRadarDisplay : public CRadarScreen
{
	public:
		// Constructor & Destructor
		CRadarDisplay();
		virtual ~CRadarDisplay();

		// Custom methods	
		void PopulateProgramData();

		// Public properties
		CPosition RulerPoint1;
		CPosition RulerPoint2;
		double RefreshResolution = 0.2;

		// Inherited methods
		void OnRefresh(HDC hDC, int Phase);
		void OnRadarTargetPositionUpdate(CRadarTarget RadarTarget);
		void OnFlightPlanDisconnect(CFlightPlan FlightPlan);
		void OnMoveScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, bool Released);
		void OnOverScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area);
		void OnClickScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button);
		void OnButtonDownScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button);
		void OnButtonUpScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button);
		void OnFunctionCall(int FunctionId, const char* sItemString, POINT Pt, RECT Area);
		void OnDoubleClickScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button);
		void OnAsrContentToBeSaved(void);
		void OnAsrContentLoaded(bool Loaded);
		static void CursorStateUpdater(void* args); // Asynchronous loop

		inline void OnAsrContentToBeClosed(void)
		{
			// Manually call save
			OnAsrContentToBeSaved();
			appCursor->isESClosed = true;

			// Clean up
			delete appCursor;
			delete trackWindow;
			delete fltPlnWindow;
			delete msgWindow;
			delete npWindow;
			delete this;
		}

	private:
		// Cursor position structure for async
		struct CAppCursor {
			CRadarDisplay* screen;
			POINT position; // Screen coordinates
			CPosition latLonPosition; // Lat lon
			int button;
			clock_t singleClickTimer = 0; // activate on every single click to detect double click
			bool isDoubleClick = false;
			bool isESClosed = false;			
		};
		pair<int, int> screenResolution;
		CAppCursor* appCursor = new CAppCursor(); // Constantly being updated
		POINT mousePointer; // Updated on screen object actions only
		clock_t fiveSecondTimer;
		clock_t tenSecondTimer;
		bool aselDetailed;	
		map<string, int> aircraftOnScreen;
		map<int, string> menuFields;
		string asel = "";
		map<string, pair<bool, POINT>> tagStatuses;
		string aircraftSel1 = ""; // For use in conflict tools
		string aircraftSel2 = ""; // "
		CMenuBar* menuBar;
		CInboundList* inboundList;
		COtherList* otherList;
		//CRCLList* rclList;
		CConflictList* conflictList;
		CTrackInfoWindow* trackWindow = nullptr;
		CFlightPlanWindow* fltPlnWindow = nullptr;
		CMessageWindow* msgWindow = nullptr;
		CNotePad* npWindow = nullptr;
};

