//
// Created by Raey on 5/2/2020.
//

#include <iostream>
#include "Order.hpp"
#include "driver.hpp"
#include "time.hpp"
#include "Restaurant.hpp"
#include <string>
#include <map>
#include <sstream>

using namespace std;

Time toTime(string str){
     string h = str;
     h.resize(2);
     str.erase(0, 3);

     stringstream hour(h);
     stringstream minute(str);

     int hr, min;
     hour >> hr;
     minute  >> min;
     Time time(hr, min);
     return time;
}

static enum StringValues { evNotDefined, login, logout, order, serve, depart, deliver, arrive, status, summary};
static map<string, StringValues> commands_map;
static void initialize();

void run_program(Restaurant res)
//void test_queue(Queue<char>& testQueue)
{
    string cmd;                   // Input command
    string temp;
    string testData;              // Queue data item

    do
    {
        try {
            cout << "Command: ";                  // Read command
            getline(cin, testData);
            int x = testData.find(' ');
            if(x!=string::npos) {
                for (int i = 0; i < x; i++)
                    cmd.push_back(testData[i]);

                cmd.resize(x);
                testData.erase(0, x + 1);
            } else {
                cmd = testData;
                testData.clear();
            }

            //cout << cmd << " testdata:" << testData<< endl;

            switch(commands_map[cmd]){
                case login:{
                    //cout << "cmd login" << endl;
                    string driverName = testData;
                    cout << driverName<< endl;
                    Driver tempDriver(driverName);
                    res.addDriver(&tempDriver);
                    break;
                }

                case logout:
                    res.getDriver(testData)->logout();
                    //cout << "ji" << endl;
                    break;

                case order: {
                    string time = testData;
                    time.resize(5);
                    //cout << time << endl;

                    //time.erase(2);
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
                    //cout << testData<< endl;
                    Order tempOrder(tempTime, testData);
                    cout << tempOrder.toString() << endl;
                    res.addOrder(&tempOrder);
                    break;
                }
                case serve: {
                    res.serveNextOrder();
                    cout << endl<< "Served next order";
                    //testData????????????????????
                    break;
                }

                case depart:
                    res.departNextOrder();
                    cout << "departed next order";
                    //testData??????????????????????
                    break;

                case deliver:
                    cout << "deliver";
//                    res.deliver()
                    break;

                case arrive:
                    break;

                case status: {
                    res.status();
                    break;
                }

                case summary:
                    break;
                case evNotDefined:
                    break;
                default:
                    cout << "Please try again" << endl;
                    break;
            }
        }
        catch (logic_error e) {
            cout << "Error: " << e.what() << endl;
        }
        cmd.clear();
        testData.clear();
    }
    while ( cin && cmd != "quit"  &&  cmd != "Quit");

    if( !cin ) {
        cout << "input error" << endl;
    }

}

void print_help() {
    cout << endl << "Commands:" << endl;
    cout << "  login DRIVER             : DRIVER is logged in" << endl;
    cout << "  logout DRIVER            : DRIVER is logged out" << endl;
    cout << "  order TIME INFO          : An order INFO is created at TIME" << endl;
    cout << "  serve TIME               : An order is done cooking and is enqueued for delivery" << endl;
    cout << "  depart TIME DRIVER       : DRIVER departs at time TIME" << endl;
    cout << "  deliver TIME DRIVER TIP  : .............." << endl;
    cout << "  arrive TIME DRIVER       : Quit the test program" << endl;
    cout << "  status                   : View the current status of the restaurant" << endl;
    cout << "  summary                  : View summary statistics of restaurant" << endl;
    cout << "  quit                     : Terminates the program" << endl;
    cout << endl;
}

int main() {
    initialize();
    cout << "System is activated. Please use commands below to navigate." << endl;
    Restaurant Pizza;
    print_help();
    run_program(Pizza);

//    Driver dan("Dan");
//    Driver adam("Adam");
//
//
//    Time time1(10,00);
//    Time time2(10,15);
//    Time time3(10,30);
//    Time time4(10,45);
//    Time time5(11,00);
//
//    Order order1(time1,"2 cheese to 120 west Mango Lane");
//
//    Restaurant res1;
//    res1.addDriver(&dan);
//    res1.addDriver(&adam);
//    res1.addOrder(&order1);
//
//
//    //order1.deliver(time2);
//    cout<< order1.toString() << endl;
//    res1.status();
    return 0;

}

void initialize(){
    commands_map["login"] = login;
    commands_map["logout"] = logout;
    commands_map["order"] = order;
    commands_map["serve"] = serve;
    commands_map["depart"] = depart;
    commands_map["deliver"] = deliver;
    commands_map["arrive"] = arrive;
    commands_map["status"] = status;
    commands_map["summary"] = summary;
}
