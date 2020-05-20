# pizza-project
This project uses a user interface on the command line. When the program is run, the available commands are displayed in a notice that describes how to run the commands.
     Commands:   
     
       login DRIVER             : DRIVER is logged in      
       logout DRIVER            : DRIVER is logged out      
       order TIME INFO          : An order INFO is created at TIME      
       serve TIME               : An order is done cooking and is enqueued for delivery at TIME      
       depart TIME DRIVER       : DRIVER departs at time TIME      
       deliver TIME DRIVER TIP  : DRIVER delivers at TIME and receives TIP      
       arrive TIME DRIVER       : DRIVER arrives at restaurant at TIME      
       status                   : View the current status of the restaurant      
       summary                  : View summary statistics of restaurant      
       drivers                  : Prints complete list of drivers      
       help                     : Prints help instructions      
       quit                     : Terminates the program      

Fully capitalized words--DRIVER, TIME, INFO and TIP--entail user-defined values. 
The DRIVERs in the system are pre-determined. This means that only drivers in the system can be logged in, and these drivers can be found in the “drivers” command. The available drivers in this restaurant are Pam, Abe and Bob. 
	The TIME must be entered in hh:mm military time format. For example 3:45 is an incorrect time entry since the appropriate 0 placeholder is missing (03:45). 
	The INFO entered--the order--must describe the full order. 
	The TIP must be entered as any integer. 
