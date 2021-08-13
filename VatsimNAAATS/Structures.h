#pragma once
#include <cmath>
#include <string>
#include <vector>
#include "Constants.h"
#include <map>
#include <unordered_map>

// Describes a NAT track
struct CTrack {
	string Identifier;
	string TMI;
	vector<string> Route;
	vector<CPosition> RouteRaw;
	vector<int> FlightLevels;
	CTrackDirection Direction;
};

// Describes a point along an aircraft's route
struct CRoutePosition {
	string Fix;
	CPosition PositionRaw;
	string Estimate;
	int DistanceFromLastPoint;
	int FlightLevel;
};

// Describes a generic waypoint
struct CWaypoint {
	CWaypoint() {}; // Default constructor
	CWaypoint(string name, double lat, double lon) {
		Name = name;
		Position.m_Latitude = lat;
		Position.m_Longitude = lon;
	}
	string Name;
	CPosition Position;
};

// Describes an inbound aircraft
struct CInboundAircraft {
	CInboundAircraft(string cs, int fA, int cL, string pt, string est, string dest, bool direction) {
		Callsign = cs;
		FinalAltitude = fA;
		ClearedLevel = cL;
		Point = pt;
		Estimate = est;
		Destination = dest;
		Direction = direction;
	}
	string Callsign;
	int FinalAltitude;
	int ClearedLevel;
	string Point;
	string Estimate;
	string Destination;
	bool Direction;
};

// Describes a aircraft status
struct CAircraftStatus {
	CAircraftStatus() {}; // Default constructor
	CAircraftStatus(string cs, int alt, int gs, int hdg, CPosition pos) {
		Callsign = cs;
		Altitude = alt;
		GroundSpeed = gs;
		Heading = hdg;
		Position = pos;
	}
	string Callsign;
	int Altitude;
	int GroundSpeed;
	int Heading;
	int Estimate;
	CPosition Position;
};

// STCA status
struct CSTCAStatus {
	CSTCAStatus() {}; // Default constructor
	CSTCAStatus(string csA, string csB, CConflictStatus status, int distanceTime, int distanceNM) {
		CallsignA = csA;
		CallsignB = csB;
		ConflictStatus = status;
		DistanceAsTime = distanceTime;
		DistanceAsNM = distanceNM;
	}
	string CallsignA;
	string CallsignB;
	CConflictStatus ConflictStatus;
	int DistanceAsTime;
	int DistanceAsNM;
};

// Describes a separation status
struct CSepStatus {
	int DistanceAsTime;
	int DistanceAsNM;
	int AltDifference;
	bool IsDistanceClosing;
	CTrackStatus TrackStatus;
	CConflictStatus ConflictStatus;
	pair<CPosition, CPosition> AircraftLocations;
};

// Describes a window text input
struct CTextInput {
	CTextInput() {}; // Default constructor
	CTextInput(int id, int type, string lbl, string content, int width, CInputState state) {
		Id = id;
		Type = type;
		Label = lbl;
		Content = content;
		Width = width;
		State = state;
		Error = false;
	}
	int Id;
	int Type;
	string Label;
	string Content;
	int Width;
	CInputState State;
	bool Error;
};

// Describes a window check box
struct CCheckBox {
	CCheckBox() {}; // Default constructor
	CCheckBox(int id, int type, string lbl, bool isChecked, CInputState state) {
		Id = id;
		Type = type;
		Label = lbl;
		IsChecked = isChecked;
		State = state;
	}
	int Id;
	int Type;
	string Label;
	bool IsChecked;
	CInputState State;
};

// Describes a button
struct CWinButton {
	CWinButton() {}; // Default constructor
	CWinButton(int id, int type, string lbl, CInputState state, int width = -1, int cycle = 0) {
		Id = id;
		Type = type;
		Width = width;
		Label = lbl;
		State = state;
		Cycle = cycle;
	}
	int Id;
	int Type;
	int Width;
	int Cycle;
	string Label;
	CInputState State;
};

// Describes a dropdown item
struct CDropDownItem {
	CDropDownItem() {}; // Default constructor
	CDropDownItem(int id, int type, string lbl, bool hovered, bool checkItem, CInputState state) {
		Id = id;
		Type = type;
		Label = lbl;
		IsHovered = hovered;
		IsCheckItem = checkItem;
		State = state;
	}
	int Id;
	int Type;
	string Label;
	bool IsHovered;
	bool IsCheckItem;
	CInputState State;
	int Width;
};

// Describes a dropdown
struct CDropDown {
	CDropDown() {}; // Default constructor
	CDropDown(int id, int type, string value, map<string, bool>* dropDownItems, CInputState state, int width = -1) {
		Id = id;
		Type = type;
		Value = value;
		int counter = 800;
		for (auto kv : *dropDownItems) {
			Items.insert(make_pair(counter, CDropDownItem(counter, type, kv.first, false, kv.second, CInputState::INACTIVE)));
			counter++;
		}
		State = state;
		Width = width;
	}
	void MakeItems(map<string, bool>* items) {
		Items.clear();
		int counter = 800;
		for (auto kv : *items) {
			Items.insert(make_pair(counter, CDropDownItem(counter, Type, kv.first, false, kv.second, CInputState::INACTIVE)));
			counter++;
		}
	}
	int Id;
	int Type;
	string Value;
	map<int, CDropDownItem> Items;
	CInputState State;
	int Width;
};

struct CWinScrollBar {
	CWinScrollBar() {}
	CWinScrollBar(int id, int type, int cSize, int fSize, bool isX) {
		Id = id;
		Type = type;
		ContentSize = cSize;
		FrameSize = fSize;
		ContentRatio = (double)(FrameSize) / (double)ContentSize;
		IsHorizontal = isX;

		// Grip size (subtract 24 because buttons)
		// BUG: gripbox is not correct, overdraws the button, or sometimes overshoots the track
		GripSize = (FrameSize - 24) * ContentRatio;
		if (GripSize < 20) GripSize = 20; // Minimum grip size
		if (GripSize > FrameSize - 12) GripSize = FrameSize - 12; // Maximum grip size
		if (ContentRatio == 1)
			GripSize = FrameSize - (isX ? 12 : 24);
		TotalScrollableArea = ContentSize - FrameSize;
		PositionDelta = 0;
		WindowPos = 0;

	}
	int Id;
	int Type;
	int ContentSize;
	int FrameSize;
	double ContentRatio;
	double GripSize;
	double PositionDelta;
	double WindowPos;
	int TotalScrollableArea;
	bool IsHorizontal;
};

struct CMessage {
	CMessage() {}; // Default constructor
	CMessage(int id, string to, string from, string messageRaw, string createdAt, CMessageType type)
	{
		Id = id;
		To = to;
		From = from;
		MessageRaw = messageRaw;
		CreatedAt = createdAt;
		Type = type;
	}
	int Id;
	string To;
	string From;
	string MessageRaw;
	string CreatedAt;
	CMessageType Type;
};

struct CFlightRestriction {
	CFlightRestriction() {}; // Default constructor
	CRestrictionType Type;
	string Content;
	string Human;
};

struct CNetworkFlightPlan {
	string Callsign;
	int AssignedLevel;
	int AssignedMach;
	string Track;
	string Route;
	string RouteEtas;
	string Departure;
	string Arrival;
	bool IsEquipped;
	string TrackedBy;
	string LastUpdated;
};

struct CAircraftFlightPlan {
	CAircraftFlightPlan() {}; // Default constructor
	CAircraftFlightPlan(
		string PassedRoute,
		string PassedCallsign,
		string PassedType,
		string PassedDepart,
		string PassedDest,
		string PassedEtd,
		string PassedSELCAL,
		string PassedDLStatus,
		string PassedCommunications,
		string PassedSector,
		string PassedFlightLevel,
		string PassedMach,
		string PassedTrack,
		string PassedState,
		int PassedExitTime,
		bool PassedIsCleared,
		bool PassedIsValid
	)
	{
		Callsign = PassedCallsign;
		Type = PassedType;
		Depart = PassedDepart;
		Dest = PassedDest;
		Etd = PassedEtd;
		SELCAL = PassedSELCAL;
		DLStatus = PassedDLStatus;
		Communications = PassedCommunications;
		Sector = PassedSector;
		FlightLevel = PassedFlightLevel;
		Mach = PassedMach;
		Track = PassedTrack;
		State = PassedState;
		ExitTime = PassedExitTime;
		IsCleared = PassedIsCleared;
		IsValid = PassedIsValid;
		CurrentMessage = nullptr;

		auto is_track = true;
		if (Track == "RR")
		{
			is_track = false;
		}
		else
		{
			PassedRoute = "NULL";
		}
	}
	string Callsign;
	string Type;
	string Depart;
	string Dest;
	string Etd;
	string SELCAL;
	string DLStatus;
	string Communications;
	string Sector;
	string FlightLevel;
	string Mach;
	string Track;
	string State;
	CMessage* CurrentMessage;
	vector<string> FlightHistory;
	vector<string> RouteRaw;
	vector<CWaypoint> Route;
	vector<CFlightRestriction> Restrictions;
	int ExitTime;
	bool IsEquipped;
	bool IsValid = false;
	bool IsFirstUpdate = false; // So that we can disable flight plan window until the plan has been fetched from server at least once
	CRadarTargetMode TargetMode = CRadarTargetMode::ADS_B;
	bool IsCleared = false;
};


// These gotta go in here because Constants.h doesn't like it?
const vector<CWaypoint> NatSM = {
	CWaypoint("SM15W", 50.683, -15.0),
	CWaypoint("SM20W", 50.833, -20.0),
	CWaypoint("SM30W", 50.5, -30.0),
	CWaypoint("SM40W", 49.266, -40.0),
	CWaypoint("SM50W", 47.05, -50.0),
	CWaypoint("SM53W", 46.166, -53.0),
	CWaypoint("SM60W", 44.233, -60.0),
	CWaypoint("SM65W", 42.766, -65.0),
	CWaypoint("SM67W", 42.0, -67.0)
};
const vector<CWaypoint> NatSN = {
	CWaypoint("SN67W", 40.416667, -67.0),
	CWaypoint("SN65W", 41.666667, -65.0),
	CWaypoint("SN60W", 43.116667, -60.0),
	CWaypoint("SN525W", 45.166667, -52.5),
	CWaypoint("SN50W", 45.9, -50.0),
	CWaypoint("SN40W", 48.166667, -40.0),
	CWaypoint("SN30W", 49.433333, -30.0),
	CWaypoint("SN20W", 49.816667, -20.0),
	CWaypoint("SN15W", 49.683333, -15.0)
};
const vector<CWaypoint> NatSO = {
	CWaypoint("SO15W", 48.666667, -15.0),
	CWaypoint("SO20W", 48.8, -20.0),
	CWaypoint("SO30W", 48.366667, -30.0),
	CWaypoint("SO40W", 47.066667, -40.0),
	CWaypoint("SO50W", 44.75, -50.0),
	CWaypoint("SO52W", 44.166667, -52.0),
	CWaypoint("SO60W", 42.0, -60.0)
};
const vector<CWaypoint> NatSL = {
	CWaypoint("SL50W", 57.0, -50.0),
	CWaypoint("SL40W", 57.0, -40.0),
	CWaypoint("SL30W", 56.0, -30.0),
	CWaypoint("SL20W", 54.0, -20.0),
	CWaypoint("SL15W", 52.0, -15.0)
};
const vector<CWaypoint> NatSP = {
	CWaypoint("SP20W", 46.816667, -20.0),
	CWaypoint("SP238W", 45.0, -23.883333),
	CWaypoint("SP30W", 41.6, -30.0),
	CWaypoint("SP40W", 34.366667, -40.0),
	CWaypoint("SP477W", 27.0, -47.783333),
	CWaypoint("SP50W", 24.633333, -50.0),
	CWaypoint("SP556W", 18.0, -55.65)
};