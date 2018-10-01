#ifndef APPT_H
#define APPT_H

#include <string>
#include <iostream>

//jared j smith
//1005002635

// This is the appointment class
// It should hold all information for the appointment

class appt
{
    private:
        int day;
        int hour;
        std::string task;
        bool complete;


    public:
        enum week_enum{
          Sunday,
          Monday,
          Tuesday,
          Wednesday,
          Thursday,
          Friday,
          Saturday
        };

        appt(int d = 0, int h = 0000, std::string item = "unset", bool done = false); // default constructor
        ~appt(); // destructor

		// set the day of the appointment
        void set_day(int d);

		// set the time of the appointment
        void set_time(int h);

		// set the task of the appointment
        void set_task(std::string item);

		// set the status of the appointment
        void set_is_done(bool done);

		// return the day of the appointment
        int get_day();

		// return the time of the appointment
        int get_time();

		// return the task of the appointment
        std::string get_task();

		// return the status of the appointment
        bool get_is_done();

		// restores appointment information to default
        void clear();

		// print all the appointment information
        void show_appt();

};  // end appt class

#endif
