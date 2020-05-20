//
// Created by Bas, Emerson, and Raey
// Dr. Visa
// Computer Science 120
// May 5, 2020
// Pizza Project
//

#ifndef ORDERPIZZA_ORDER_HPP
#define ORDERPIZZA_ORDER_HPP

#include <iostream>
#include <string>
#include "time.hpp"
using namespace std;


class Order {
public:
    Order();
    Order(Time time, string info);
    void depart() throw (logic_error);
    void deliver(Time time) throw (logic_error);
    int getMinToDelivery() throw (logic_error);
    string toString();
    void replaceValues(Time time, string info);
    void resetValues();

private:
    Time order_time_placed;
    Time order_time_delivered;

    // string status;
    bool order_is_out_for_delivery;
    bool order_is_delivered;
    bool order_is_at_the_restaurant;
    int order_delivery_duration;

    string order_details;
    string order_info_string;
};


// ---------------------------------------------------------------------------
/*
 * Post: Creates an order with default values for data members
 */
Order::Order() {
    //time_placed = 0;
    //time_delivered = 0;
    //order = "nothing yet";
    order_is_at_the_restaurant = true;
    order_is_delivered = false;
    order_is_out_for_delivery = false;

}
// ---------------------------------------------------------------------------
/*
 * Post: Creates an order with the given order time and information
 */
Order::Order(Time time, string info) {
    order_time_placed = time;
    //order = info;
    order_details = info;
    order_is_at_the_restaurant = true;
    order_is_delivered = false;
    order_is_out_for_delivery = false;


}

// ---------------------------------------------------------------------------
/*
 * Pre: Order is at the restaurant
 * Post: Order is out for delivery
 */
void Order::depart() throw(logic_error) {
    if (!order_is_at_the_restaurant){
        //if(status != "at the restaurant") {
        throw logic_error("The order is not at the restaurant");
    }

    order_is_out_for_delivery = true;
}

// ---------------------------------------------------------------------------
/*
 * Pre: Order is out for delivery
 * Post: Order is delivered. Time to delivery is recorded.
 */
void Order::deliver(Time time) throw(logic_error) {
    if (!order_is_out_for_delivery){
        //if(status != "out for delivery") {
        throw logic_error("The order is not out for delivery");
    }
    //  status = "Delivered"
    order_is_delivered = true;
    order_time_delivered = time;

}

// ---------------------------------------------------------------------------
/*
 * Pre: Order is delivered.
 * Post: Returns the minutes until the order is delivered
 */
int Order::getMinToDelivery() throw(logic_error) {
    //if(status != "Delivered") {
    if (!order_is_delivered){
        throw logic_error("The order has not been delivered yet");
    }
    order_delivery_duration = Time::elapsedMin(order_time_placed, order_time_delivered);
    return order_delivery_duration;
}

// ---------------------------------------------------------------------------
/*
 * Post: returns a string containing the order time and info
 */
string Order::toString() {

//    order_delivery_duration_string = to_string(order_delivery_duration);
    order_info_string = order_time_placed.toString();
    order_info_string.append(" ");
    order_info_string.append(order_details);
//    order_info_string.append(". The order took a total of (in minutes):");
//    order_info_string.append(order_delivery_duration_string);

    return order_info_string;
}

/* ---------------------------------------------------------------
 * Pre: There must be a time and info implemented
 * Post: This replaces the values Order_time_placed and Order_details
 */
void Order::replaceValues(Time time, string info) {
    order_time_placed = time;
    order_details = info;
}

/* ---------------------------------------------------------------
 * Pre: none
 * Post: resets an order's private values
 */
void Order::resetValues() {
    order_is_at_the_restaurant = true;
    order_is_delivered = false;
    order_is_out_for_delivery = false;
}


#endif //ORDERPIZZA_ORDER_HPP
