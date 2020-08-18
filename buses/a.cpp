#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  // реализуйте эту функцию
  string type;
  is >> type;
  if ("NEW_BUS" == type)
  {
	  q.type = QueryType::NewBus;
      is >> q.bus;
      int stop_count;
      is >> stop_count;
      q.stops.resize(stop_count);
      for (string& stop : q.stops) {
        is >> stop;
      }
  }
  else if ("BUSES_FOR_STOP" == type)
  {
	  q.type = QueryType::BusesForStop;
      is >> q.stop;
  }
  else if ("STOPS_FOR_BUS" == type)
  {
	  q.type = QueryType::StopsForBus;
	  is >> q.bus;
  }
  else if ("ALL_BUSES" == type)
  {
	  q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  // Наполните полями эту структуру
  string stop;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // реализуйте эту функцию
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

struct StopsForBusResponse {
  // Наполните полями эту структуру
  string bus;
  vector<pair<string, vector<string>>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // реализуйте эту функцию
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

struct AllBusesResponse {
  // Наполните полями эту структуру
  map<string, vector<string>> buses_to_stops; 
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // реализуйте эту функцию
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

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    //еализуйте этот метод
	buses_to_stops[bus] = stops;
	for (const string& stop : stops)
	{
		stops_to_buses[stop].push_back(bus);
	}
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    //еализуйте этот метод
	BusesForStopResponse ret;
	ret.stop = stop;
	if (stops_to_buses.count(stop) != 0)
	{
		ret.buses = stops_to_buses.at(stop);
	}
	return ret;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    //еализуйте этот метод
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

  AllBusesResponse GetAllBuses() const {
    //еализуйте этот метод
	return AllBusesResponse {buses_to_stops};
  }

private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	#ifdef LOCAL
  	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}