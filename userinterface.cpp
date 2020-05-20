//
// Created by Bas, Emerson, and Raey
// Dr. Visa
// Computer Science 120
// May 5, 2020
// Pizza Project
//

#include <iostream>
#include "Order.hpp"
#include "driver.hpp"
#include "time.hpp"
#include "Restaurant.hpp"
#include <string>
#include <map>
#include <sstream>

void print_instruc() {
    cout << "Commands:" << endl;
    cout << "  login DRIVER             : DRIVER is logged in" << endl;
    cout << "  logout DRIVER            : DRIVER is logged out" << endl;
    cout << "  order TIME INFO          : An order INFO is created at TIME" << endl;
    cout << "  serve TIME               : An order is done cooking and is enqueued for delivery at TIME" << endl;
    cout << "  depart TIME DRIVER       : DRIVER departs at time TIME" << endl;
    cout << "  deliver TIME DRIVER TIP  : DRIVER delivers at TIME and receives TIP" << endl;
    cout << "  arrive TIME DRIVER       : DRIVER arrives at restaurant at TIME" << endl;
    cout << "  status                   : View the current status of the restaurant" << endl;
    cout << "  summary                  : View summary statistics of restaurant" << endl;
    cout << "  drivers                  : Prints complete list of drivers" << endl;
    cout << "  help                     : Prints help instructions" << endl;
    cout << "  quit                     : Terminates the program" << endl;
    cout << endl;
}

void print_help(){
    cout << " HELP:" << endl;
    print_instruc();
    cout << "ADDITIONAL INFO: " << endl;
    cout << "Fully capitalized words--DRIVER, TIME, INFO and TIP--entail user-defined values." << endl
    << "\tThe DRIVERs in the system are pre-determined. This means that only drivers in the" << endl
    << "\tsystem can be logged in, and these drivers can be found in the “drivers” command. " << endl << endl
    << "\tThe TIME must be entered in hh:mm military time format. For example 3:45 is an incorrect" << endl
    << "\ttime entry since the appropriate 0 placeholder is missing (03:45)." << endl << endl
    << "\tThe INFO entered--the order--must describe the full order." << endl << endl
    << "\tThe TIP must be entered as any integer. " << endl<< endl;

    cout << "Note: if you are experiencing unknown errors or program crashing, please check your" << endl
    << "commands for incorrect spacing, capitalization or spelling." << endl << endl;

}

int toNum(string str){
    if(str == "login")
        return 1;
    if(str == "logout")
        return 2;
    if(str == "order")
        return 3;
    if(str == "serve")
        return 4;
    if(str == "depart")
        return 5;
    if(str == "deliver")
        return 6;
    if(str == "arrive")
        return 7;
    if(str == "status")
        return 8;
    if(str == "summary")
        return 9;
    if(str == "drivers")
        return 10;
    if(str == "help")
        return 11;
}
void run_program(Restaurant res)
{
    string cmd;                   // Input command
    string testData;              // Queue data item

    do
    {
        try {
            //clearing strings after every loop
            cmd.clear();
            testData.clear();

            cout << "Command: ";                  // Read command
            getline(cin, testData);

            //separating the input into commands and data
            int x = testData.find(' ');
            if(x!=-1) {
                for (int i = 0; i < x; i++)
                    cmd.push_back(testData[i]);
                cmd.resize(x);
                testData.erase(0, x + 1);
            } else {
                cmd = testData;
                testData.clear();
            }

            switch(toNum(cmd)){
                case 1: {    // login
                    // displaying error message if no driver is given
                    if(x==-1) {
                        cout << "\t" << "Please enter values after command" << endl;
                        break;
                    }
                    //check if driver exists
                    if(res.getDriver(testData) == 0) {
                        cout << "\t" << "Error: Driver does not exist. Use command 'Drivers' to see available drivers" << endl; //error message if driver does not exist
                        break;
                    } else {
                        res.getDriver(testData)->login();
                        cout << "\t" << testData << " has logged in." << endl;  //confirmation message
                    }
                    break;
                } //login

                case 2: {    // logout
                    // displaying error message if no driver is given
                    if (x == -1) {
                        cout << "\t" << "Please enter values after command" << endl;
                        break;
                    }
                    //check if driver exists
                    if(res.getDriver(testData) == 0) {
                        cout << "\t" << "Error: Driver does not exist. Use command 'Drivers' to see available drivers" << endl; //error message if driver does not exist
                        break;
                    } else {
                        res.getDriver(testData)->logout();
                        cout << "\t" << testData << " has logged out." << endl; //confirmation message
                    }
                    break;
                } //logout

                case 3: {   // order
                    if(x==-1) {
                        cout << "\t" << "Please enter values after command" << endl;
                        break;
                    }

                    //processing testData into TIME and INFO
                    string displayOrder = testData;
                    string time = testData;
                    int y = testData.find(' ');
                    if(y!=5) { // making sure the time is in correct format
                        cout << "\t" << "Error: time must be in format hh:mm (eg. 05:45)" << endl << "\t" << "Else, info is missing" << endl;
                        break;
                    }
                    time.resize(5);

                    string h = time;
                    h.resize(2);
                    time.erase(0, 3);

                    stringstream hour(h);
                    stringstream minute(time);

                    int hr, min;
                    hour >> hr;
                    minute  >> min;
                    Time tempTime(hr, min);

                    testData.erase(0, 6);
                    res.addOrder(tempTime, testData);

                    //order notification
                    cout << "\t" << "The following order has been placed: " << endl <<"\t" << displayOrder<< endl;
                    break;
                } //order

                case 4: {   //serve
                    if(x==-1) {
                        cout << "\t" << "Please enter values after command" << endl;
                        break;
                    }
                    res.serveNextOrder();
                    break;
                } //serve

                case 5: {   //depart
                    if(x==-1) {
                        cout << "\t" << "Please enter values after command" << endl;
                        break;
                    }

                    //processing testData into TIME and DRIVER
                    string time = testData;
                    time.resize(5);
                    //cout << time << endl;     //debugging
                    string h = time;
                    h.resize(2);
                    time.erase(0, 3);

                    stringstream hour(h);
                    stringstream minute(time);

                    int hr, min;
                    hour >> hr;
                    minute >> min;
                    Time tempTime(hr, min);
                    testData.erase(0, 6);

                    res.getDriver(testData)->depart(tempTime, *res.departNextOrder());
                    break;
                } //depart

                case 6: {   //deliver
                    if (x == -1) {
                        cout << "\t" << "Please enter values after command" << endl;
                        break;
                    }

                    // processing testData into separate values
                    string time = testData;
                    time.resize(5);
                    string h = time;
                    h.resize(2);
                    time.erase(0, 3);

                    stringstream hour(h);
                    stringstream minute(time);

                    int hr, min;
                    hour >> hr;
                    minute >> min;
                    Time tempTime(hr, min);
                    testData.erase(0, 6);

                    int i = testData.find_first_of(" ");
                    string driver;
                    for (int j = 0; j < i; j++)
                        driver.push_back(testData[j]);
                    testData.erase(0, i + 1);
                    float tip = stof(testData);

                    // delivering
                    res.deliver(res.getDriver(driver), tempTime, tip);
                    break;
                } //deliver

                case 7: {   //arrive
                    if(x==-1) {
                        cout << "\t" << "Please enter values after command" << endl;
                        break;
                    }

                    // processing testData into separate values
                    string time = testData;
                    time.resize(5);
                    //cout << time << endl;     //debugging
                    string h = time;
                    h.resize(2);
                    time.erase(0, 3);

                    stringstream hour(h);
                    stringstream minute(time);

                    int hr, min;
                    hour >> hr;
                    minute >> min;
                    Time tempTime(hr, min);
                    testData.erase(0, 6);

                    //arriving
                    res.getDriver(testData)->arrive(tempTime);
                    break;
                } //arrive

                case 8: {   // status
                    res.status();
                    break;
                } //status

                case 9: {   //summary
                    res.summary();
                    break;
                } //summary

                case 10:{  //drivers
                    res.printDrivers();
                    break;
                } //drivers

                case 11:{  //help
                    print_help();
                    break;
                } //help

                default:
                    if(cmd != "quit")
                        cout << "\t" << "Please try again" << endl;
                    break;
            }
        }
        catch (logic_error e) {
            cout << "\t" << "Error: " << e.what() << endl << endl;
        }
    }
    while (cmd != "quit"); //implementing quit command

    if( !cin ) {
        cout << "input error" << endl;
    }
}

int main(){
    cout << "System is activated. Please use commands below to navigate." << endl;
    print_instruc();   //print command instructions
    cout << "Note: If you are experiencing trouble, please use the command 'help'"<< endl << endl;
    Restaurant Pizza;

    //Creating drivers
    Driver one("Pam");
    Driver two("Abe");
    Driver three("Bob");

    //Creating orders
    Order order1;
    Order order2;
    Order order3;
    Order order4;
    Order order5;
    Order order6;
    Order order7;
    Order order8;
    Order order9;
    Order order10;

    //Adding orders and drivers to restaurant
    Pizza.addDriver(&one);
    Pizza.addDriver(&two);
    Pizza.addDriver(&three);

    Pizza.addEmptyOrder(&order1);
    Pizza.addEmptyOrder(&order2);
    Pizza.addEmptyOrder(&order3);
    Pizza.addEmptyOrder(&order4);
    Pizza.addEmptyOrder(&order5);
    Pizza.addEmptyOrder(&order6);
    Pizza.addEmptyOrder(&order7);
    Pizza.addEmptyOrder(&order8);
    Pizza.addEmptyOrder(&order9);
    Pizza.addEmptyOrder(&order10);

    //run user interface
    run_program(Pizza);
    return 0;
}
