#ifndef PASSANGERS_H
#define PASSANGERS_H


typedef struct passenger PASSENGER;

PASSENGER *create_passenger();
void free_passenger(PASSENGER *p);

//setters
void set_flight_id2(PASSENGER *p, int flight_id);
void set_user_id2(PASSENGER *p, const char *user_id);
//getters
const char * get_user_id2(const PASSENGER *p);
int get_flight_id2(const PASSENGER *p);


#endif //PASSANGERS_H
