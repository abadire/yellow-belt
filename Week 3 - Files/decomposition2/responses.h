#pragma once

#include <string>
#include <vector>
#include <map>
#include <ostream>

using namespace std;

struct BusesForStopResponse {
  string stop;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  // Наполните полями эту структуру
  string bus;
  vector<pair<string, vector<string>>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  // Наполните полями эту структуру
  map<string, vector<string>> buses_to_stops; 
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
