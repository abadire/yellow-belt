#include "query.h"

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