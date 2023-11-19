#ifndef FLIGHTS_CATALOG_H
#define FLIGHTS_CATALOG_H


typedef struct flight FLIGHT;

FLIGHT *create_flight();
void free_flight(FLIGHT *flight);

// Getters
const char *get_flight_id(const FLIGHT *f);
const char *get_airline(const FLIGHT *f);
const char *get_plain_model(const FLIGHT *f);
int get_total_seats(const FLIGHT *f);
const char *get_origin(const FLIGHT *f);
const char *get_destination(const FLIGHT *f);
const char *get_schedule_departure_date(const FLIGHT *f);
const char *get_schedule_arrival_date(const FLIGHT *f);
const char *get_real_departure_date(const FLIGHT *f);
const char *get_real_arrival_date(const FLIGHT *f);
const char *get_pilot(const FLIGHT *f);
const char *get_copilot(const FLIGHT *f);
const char *get_notes(const FLIGHT *f);

// Setters
void set_flight_id(FLIGHT *f, const char *id);
void set_airline(FLIGHT *f, const char *airline);
void set_plain_model(FLIGHT *f, const char *plain_model);
void set_total_seats(FLIGHT *f, int total_seats);
void set_origin(FLIGHT *f, const char *origin);
void set_destination(FLIGHT *f, const char *destination);
void set_schedule_departure_date(FLIGHT *f, const char *schedule_departure_date);
void set_schedule_arrival_date(FLIGHT *f, const char *schedule_arrival_date);
void set_real_departure_date(FLIGHT *f, const char *real_departure_date);
void set_real_arrival_date(FLIGHT *f, const char *real_arrival_date);
void set_pilot(FLIGHT *f, const char *pilot);
void set_copilot(FLIGHT *f, const char *copilot);
void set_notes(FLIGHT *f, const char *notes);
double calc_delay(char* schedule_arrival, char* schedule_departure, char* real_arrival, char* real_departure);

#endif