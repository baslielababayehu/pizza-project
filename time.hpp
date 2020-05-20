//
// Created by Bas, Emerson, and Raey
// Dr. Visa
// Computer Science 120
// May 5, 2020
// Pizza Project
//

#ifndef PIZZAPROJECT_TIME_HPP
#define PIZZAPROJECT_TIME_HPP

#include <stdexcept>
#include <iostream>
#include <string>


using namespace std;

class Time {
public:
    Time();
    Time(int hour, int min) throw (logic_error);
    static int elapsedMin(Time t1, Time t2);
    string toString();

private:
    int hour;
    int min;
};

/* ---------------------------------------------------------------
 * Pre: This is a default constructor
 * Post: Creates a time with default values for data members.
 */
Time::Time() {
    hour = 0;
    min = 0;
}

/* ---------------------------------------------------------------
 * Pre: There must be times
 * Post: Returns the difference in minutes between t1 and t2. Assumes t2
 * is between 00:00 and 23:59 hours after t1.
 */
int Time::elapsedMin(Time t1, Time t2) {
    Time elapsed;
    if ( 0 > (t2.min - t1.min)) {
        elapsed.min = 60 + t2.min - t1.min;
    }
    else {
        elapsed.min = t2.min - t1.min;
    }
    return elapsed.min;
}

/* ---------------------------------------------------------------
 * Pre: 0 <= hour <= 23 and 0 <= min <= 59.
 * Post: Creates a time with the given hour and minute.
 */
Time::Time(int hour, int min) throw (logic_error) {
    if ((hour < 0) || (hour > 23)) {
        throw logic_error("Hour value must be between 0 and 24.");
    }
    else if ((min < 0) || (min > 59)){
        throw logic_error("Minute value must be between 0 and 59.");
    }
    else {
        this->hour = hour;
        this->min = min;
    }
}

/* ---------------------------------------------------------------
 * Post: Returns a string containing the hour and minute (e.g., “13:01”).
 */
string Time::toString() {
    string h = to_string(hour);
    string m;
    if(min < 10) {
        m = "0";
        m.append(to_string(min));
    } else
        m = to_string(min);
    h.append(":");
    h.append(m);
    return h;
}

#endif //PIZZAPROJECT_TIME_HPP
