//
// Created by Bas, Emerson, and Raey
// Dr. Visa
// Computer Science 120
// May 5, 2020
// Pizza Project
//

#ifndef PIZZAPROJECT_DRIVER_HPP
#define PIZZAPROJECT_DRIVER_HPP

#include <string>
#include "time.hpp"
#include "Order.hpp"

using namespace std;

class Driver {
public:
    Driver(string name);
    void login() throw (logic_error);
    void logout() throw (logic_error);
    void depart(Time time, Order o) throw (logic_error);
    void deliver(Time time, float tip) throw (logic_error);
    void arrive(Time time) throw (logic_error);
    string getName();
    bool isLoggedIn();
    int getTotalDeliveries();
    int getTotalMinDelivering();
    int getTotalMinDriving();
    float getTotalTips();
    Order *getOrder() throw (logic_error);
    string toString();
private:
    string driver_name;
    bool driver_departed;
    bool driver_arrived;
    bool driver_loggedIn;
    bool driver_atRestaurant;
    bool driver_delivered;
    float total_tips;
    Time depart_time;
    Time deliver_time;
    Time arrive_time;
    int total_deliveries;
    int total_min_delivering;
    int total_min_driving;
    Order order_current;
};


/* ---------------------------------------------------------------
 * Pre: This is the default constructor
 * Post: Creates a logged-in driver with the given name.
 */
Driver::Driver(string name) {
    driver_name = name;
    driver_arrived = false;
    driver_delivered = false;
    driver_departed = false;
    driver_loggedIn = false;
    driver_atRestaurant = true;
    total_tips = 0;
    total_min_delivering = 0;
    total_min_driving = 0;
    total_deliveries = 0;
}

/* ---------------------------------------------------------------
 * Pre: Driver is not logged in.
 * Post: Logs the driver in.
 */
void Driver::login() throw (logic_error){
    if (driver_loggedIn){
        throw logic_error("This driver has already been logged in");
    }
    else {
        driver_loggedIn = true;
        driver_arrived = true;
        driver_delivered = false;
        driver_departed = false;

    }
}

/* ---------------------------------------------------------------
 * Pre: Driver is logged in and at the restaurant.
 * Post: Logs the driver out.
 */
void Driver::logout() throw (logic_error){
    if (!driver_loggedIn) {
        throw logic_error("This driver has already been logged out");
    }
    else if (!driver_atRestaurant){
        throw logic_error("Unable to log out: driver is not at restaurant");
    }
    else {
        driver_loggedIn = false;
    }
}

/* ---------------------------------------------------------------
 * Pre: Driver is logged in and at the restaurant.
 * Post: Driver is delivering. Departure time is recorded
 */
void Driver::depart(Time time, Order o) throw (logic_error){
    if (!driver_atRestaurant || !driver_loggedIn){
        throw logic_error("The driver is not logged in or not at the restaurant");
    }
    depart_time = time;
    driver_departed = true;
    driver_arrived = false;
    driver_delivered = false;
    driver_atRestaurant = false;

    order_current = o;
}

/* ---------------------------------------------------------------
 * Pre: Driver is delivering. The tip must be greater than or equal to 0
 * Post: Driver not delivering. Drivers stats are updated
 */
void Driver::deliver(Time time, float tip) throw (logic_error){
    if (!driver_loggedIn){
        throw logic_error ("driver is not logged in");
    }
    else if (tip < 0 || !driver_departed){
        throw logic_error("Tip must be greater than zero and the driver must have departed from the restaurant");
    }
    deliver_time = time;
    driver_delivered = true;
    driver_arrived = false;
    total_min_delivering += Time::elapsedMin(depart_time, deliver_time);
    total_deliveries ++;
    total_tips = total_tips + tip;
}

/* ---------------------------------------------------------------
 * Pre: Driver is driving but not delivering.
 * Post: Driver is at the restaurant. Driver’s stats are updated.
 */
void Driver::arrive(Time time) throw (logic_error){
    if (!driver_loggedIn){
        throw logic_error ("driver is not logged in");
    }
    else if (!driver_delivered || driver_arrived){
        throw logic_error("unknown");
    }
    arrive_time = time;
    total_min_driving += Time::elapsedMin(depart_time, arrive_time );
    driver_arrived = true;
    driver_atRestaurant = true;
    driver_departed = false;
    driver_delivered = false;
    driver_atRestaurant = true;
}

/* ---------------------------------------------------------------
 * Pre: There must be a drivers name. This is a getter.
 * Post: Returns the driver’s name.
 */
string Driver::getName() {
    return driver_name;
}

/* ---------------------------------------------------------------
 * Post: Returns true if and only if the driver is logged in.
 */
bool Driver::isLoggedIn() {
    return driver_loggedIn;
}

/* ---------------------------------------------------------------
 * Post: Returns the total number of completed deliveries.
 */
int Driver::getTotalDeliveries() {
    return total_deliveries;
}

/* ---------------------------------------------------------------
 * Post: Returns the total minutes spent delivering
 */
int Driver::getTotalMinDelivering() {
    return total_min_delivering;
}

/* ---------------------------------------------------------------
 * Post: Returns the total minutes spent driving
 */
int Driver::getTotalMinDriving() {
    return total_min_driving;
}

/* ---------------------------------------------------------------
 * Post: Returns the total tips received, in dollars.
 */
float Driver::getTotalTips() {
    return total_tips;
}

/* ---------------------------------------------------------------
 * Pre: Driver is delivering.
 * Post: Returns the order being delivered.
 */
Order* Driver::getOrder() throw (logic_error){
    if (!driver_departed) {
        throw logic_error("The driver is not delivering yet");
    }
    return &order_current;

}

/* ---------------------------------------------------------------
 * Post: Returns a string containing the driver’s name, state (e.g., not logged in),
 * and, if the driver is delivering an order, the departure time and toString of the
 * order being delivered.
 */
string Driver::toString() {
    string driver_status = "";
    driver_status.append(driver_name);
    return driver_status;
}


#endif //PIZZAPROJECT_DRIVER_HPP
