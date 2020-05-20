//
// Created by Bas, Emerson, and Raey
// Dr. Visa
// Computer Science 120
// May 5, 2020
// Pizza Project
//

#ifndef PIZZAPROJECT_RESTAURANT_HPP
#define PIZZAPROJECT_RESTAURANT_HPP

#include <iostream>
#include <string>
#include <deque>
#include "Order.hpp"
#include "time.hpp"
#include "driver.hpp"

using namespace std;


class Restaurant {
public:
    Restaurant();
    void status();
    void summary();
    Driver * getDriver(string name);
    void addDriver(Driver * driver);
    void addOrder(Time time, string order) throw (logic_error);
    void serveNextOrder() throw (logic_error);
    Order * departNextOrder() throw (logic_error);
    void deliver(Driver * driver, Time time, float tip);
    void addEmptyOrder(Order* order) throw (logic_error);
    void printDrivers();

private:
    deque<Order*> cooking;
    deque<Order*> delivery;
    deque<Driver*> drivers;
    deque<Order*> orderSlots;
    int numOrders;
    int numDrivers;
    int numDeliveries;
    double totalTime;

};

//-----------------------------------------------
/* ---------------------------------------------------------------
 * Pre: This is the default constructor
 * Post: Creates a restaurant in an initial state, with no drivers or orders.
 */
Restaurant::Restaurant() {
    numDrivers = 0;
    numOrders = 0;
    numDeliveries = 0;
    totalTime = 0;
}

/* ---------------------------------------------------------------
 * Post: Prints status of orders and logged-in drivers, as specified by
 * the “status” command description.
 */
void Restaurant::status() {
    cout << "\t" << "Orders waiting to cook:" << endl;
    for(auto & i : cooking){
        cout<< "\t" << "\t" << i->toString() << endl;
    }
    cout << "\t" << "Orders waiting to depart:" << endl;
    for(auto & i : delivery){
        cout<< "\t" << "\t" << i->toString() << endl;
    }
    cout << "\t" << "Drivers:" << endl;
    for(int i = drivers.size() - 1; i >= 0; i --) {
        if (drivers[i]->isLoggedIn())
            cout << "\t" << "\t" << drivers[i]->toString() << endl;
    }
    cout << endl;
}

/* ---------------------------------------------------------------
 * Post: Prints summary statistics on orders and drivers,
 * as specified by the “summary” command description.
 */
void Restaurant::summary() {
    cout << "\t" << "Number of orders completed: " << numDeliveries << endl;
    if(numDeliveries!= 0)
        cout <<"\t" << "Average time per order: " << (totalTime / numDeliveries) << endl;
    else
        cout <<"\t" << "Average time per order: " << 0 << endl << endl;
    for(auto & driver : drivers) {
        cout << "\t" << "Driver " << driver->toString() << ":" << endl;
        cout << "\t" << "Status: " << (driver->isLoggedIn() ? "Logged in" : "Logged out");
        cout << "\t" << "\t" << "Number of deliveries completed: " << driver->getTotalDeliveries() << endl;
        cout << "\t" << "\t" << "Average time per delivery: "
             << (driver->getTotalDeliveries() != 0 ? driver->getTotalMinDelivering() / driver->getTotalDeliveries() : 0)
             << endl;
        cout << "\t" << "\t" << "Total driving time: " << driver->getTotalMinDriving()<< endl;
        cout << "\t" << "\t" << "Total Tips: " << driver->getTotalTips() << endl << endl;
    }
}

/* ---------------------------------------------------------------
 * Pre: There must be a driver logged in
 * Post: If a driver with the given name exists within the system (logged in or not),
 * returns a pointer to that driver. Otherwise, returns a null pointer.
 */
Driver *Restaurant::getDriver(string name) {
    for(auto & driver : drivers){
        if(driver->getName() == name)
            return driver;
    }
    return nullptr;
}

/* ---------------------------------------------------------------
 * Pre: there must be a driver
 * Post: Adds the given driver to the system.
 */
void Restaurant::addDriver(Driver *driver) {
    drivers.push_back(driver);
    numDrivers ++;
}

/* ---------------------------------------------------------------
 * Pre: must have an order and time
 * Post: Adds the given order to the system, enqueuing it for cooking.
 */
void Restaurant::addOrder(Time time, string order) throw (logic_error){
    //cooking.push_back(order);
    if(orderSlots.empty())
        throw logic_error("Max orders has been reached.");
    else
    {
        orderSlots.front()->replaceValues(time, order);
        cooking.push_back(orderSlots.front());
        orderSlots.pop_front();
        numOrders++;
    }
}

/* ---------------------------------------------------------------
 * Pre: The cooking queue is not empty.
 * Post: Removes the oldest order from the cooking queue and enqueues
 * it for departure.
 */
void Restaurant::serveNextOrder() throw (logic_error){
    if (!cooking.empty()) {
        delivery.push_back(cooking.front());
        cooking.pop_front();
    } else throw logic_error("There are no orders to serve.");
}

/* ---------------------------------------------------------------
 * Pre: The departure queue is not empty.
 * Post: Removes the oldest order from the departure queue and returns it.
 */
Order *Restaurant::departNextOrder() throw (logic_error) {
    if (!delivery.empty()) {
        Order* temp;
        temp = delivery.front();
        delivery.pop_front();
        temp->depart();
        return temp;
    }
    else throw logic_error("There are no orders to depart.");
}

/* ---------------------------------------------------------------
 * Pre: There must be a driver, time, and a tip.
 * Post: The order carried by the driver is delivered at the given time. The
 * driver receives the given tip.
 */
void Restaurant::deliver(Driver *driver, Time time, float tip) {
    driver->getOrder()->deliver(time);
    driver->deliver(time, tip);
    cout << "\t" << "Order has been delivered" << endl;
    numDeliveries ++;
    totalTime += driver->getOrder()->getMinToDelivery();
    //Clearing order and adding it to empty orders queue
    driver->getOrder()->resetValues();
    addEmptyOrder(driver->getOrder());
}

/* ---------------------------------------------------------------
 * Pre: There must be a driver, time, and a tip.
 * Post: The order carried by the driver is delivered at the given time. The
 * driver receives the given tip.
 */
void Restaurant::addEmptyOrder(Order *order) throw (logic_error){
    orderSlots.push_back(order);
}

/* ---------------------------------------------------------------
 * Post: This function prints the drivers names
 */
void Restaurant::printDrivers() {
    cout <<"\t" << "Drivers:" << endl;
    for(int i = drivers.size() - 1; i >= 0; i --)
        cout << "\t" << "\t" << drivers[i]->toString() << endl;
    cout << endl;
}


#endif //PIZZAPROJECT_RESTAURANT_HPP
