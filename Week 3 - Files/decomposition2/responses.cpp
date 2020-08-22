#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r)
{
  if (r.buses.empty())
  {
	  os << "No stop";
  }
  else
  {
	  for (const string& bus : r.buses)
	  {
		  os << bus << ' ';
	  }
  }
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r)
{
  if (r.stops_to_buses.empty())
  {
	  os << "No bus";
  }
  else
  {
	  for (auto el : r.stops_to_buses)
	  {
		  os << "Stop " << el.first << ": ";
		  if (el.second.size() == 1)
		  {
			  os << "no interchange";
		  }
		  for (const string& bus : el.second)
		  {
			 if (bus != r.bus)
			 {
			 	os << bus << " ";
			 }
		  }
		  os << endl;
	  }
  }
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r)
{
  if (r.buses_to_stops.empty())
  {
	  os << "No buses";
  }
  else
  {
	  for (const auto& bus_to_stops : r.buses_to_stops)
	  {
		  os << "Bus " << bus_to_stops.first << ": ";
		  for (const string& stop : bus_to_stops.second)
		  {
			  os << stop << " ";
		  }
	  os << endl;
	  }
  }
  return os;
}
