#include "bus_manager.h"

  void BusManager::AddBus(const string& bus, const vector<string>& stops) {
	buses_to_stops[bus] = stops;
	for (const string& stop : stops)
	{
		stops_to_buses[stop].push_back(bus);
	}
  }

  BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	BusesForStopResponse ret;
	ret.stop = stop;
	if (stops_to_buses.count(stop) != 0)
	{
		ret.buses = stops_to_buses.at(stop);
	}
	return ret;
  }

  StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
	StopsForBusResponse ret;
	ret.bus = bus;
	if (buses_to_stops.count(bus) != 0)
	{
		for (const auto& stop : buses_to_stops.at(bus))
		{
			ret.stops_to_buses.push_back(make_pair(stop, stops_to_buses.at(stop)));
		}
	}
	return ret;
  }

  AllBusesResponse BusManager::GetAllBuses() const {
	return AllBusesResponse {buses_to_stops};
  }