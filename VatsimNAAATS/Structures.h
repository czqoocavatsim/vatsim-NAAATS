#pragma once
#include <string>
#include <vector>
#include "Constants.h"

// Describes a NAT track
struct CTrack {
	char Identifier;
	int TMI;
	vector<string> Route;
	vector<int> FlightLevels;
	CTrackDirection Direction;
};

// Describes a point along an aircraft's route
struct CRoutePosition {
	string Fix;
	CPosition PositionRaw;
	string Estimate;
	int FlightLevel;
};