#include "appt.h"

//jared j smith
//1005002635

appt::appt(int d,int h,std::string item,bool done)
{
	 day = d;
	 hour = h;
	 task = item;
	 complete= done;

}

appt::~appt(){
//deletes allocated memory
}


void appt::set_day(int d){
	day = d;
}

void appt::set_time(int h){
	hour = h;
}

void appt::set_task(std::string item){
	task = item;
}

void appt::set_is_done(bool done){
	complete = done;
}

int appt::get_day(){

	return day;
}

int appt::get_time(){

	return hour;
}

std::string appt::get_task(){
	return task;
}

bool appt::get_is_done(){
	return complete;
}

void appt::clear(){
	*this = appt();
}

void appt::show_appt(){
	std::cout << "Day: ";
  switch(day){
    case 0: std::cout << "Sunday" << std::endl;
            break;
    case 1: std::cout << "Monday" << std::endl;
            break;
    case 2: std::cout << "Tuesday" << std::endl;
            break;
    case 3:std::cout << "Wednesday" << std::endl;
            break;
    case 4: std::cout << "Thursday" << std::endl;
            break;
    case 5: std::cout << "Friday" << std::endl;
            break;
    case 6: std::cout << "Saturday" << std::endl;
            break;
    default: std::cout << std::endl <<  "Enter a valid day" << std::endl <<std::endl;

  }

	std::cout << "Time: " << hour <<std::endl;
	std::cout << "Task: " << task <<std::endl;

	if(!complete){
		std::cout << "Not complete" <<std::endl;

	}else{
		std::cout << " complete " <<std::endl;

	}


}
