#ifndef PASSANGERS_H
#define PASSANGERS_H

typedef struct passenger *PASSENGER;

PASSENGER *create_passenger();
void free_passenger(PASSENGER *p);

//setters
void set_flight_id(PASSENGER *p, int flight_id);
void set_airline(PASSENGER *p, const char *user_id);
//getters
int get_id(const PASSENGER *p);
const char *get_airline(const PASSENGER *p);


#endif //PASSANGERS_H
