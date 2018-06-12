#include <iostream>
#include <cassert>
#include <cstring>


using namespace std;

#include "tube.h"

int main() {

	/* This code illustrates the use of the pre-supplied helper functions and the
	 * functions that you are supposed to write. */

	cout << "============== Pre-supplied functions ==============" << endl << endl;

	char** map;
	int height, width;

	cout << "Loading tube map with load_map():";

	/* loads the map from the file "map.txt" and sets height and width */
	map = load_map("map.txt", height, width);
	assert(map);
	cout << " done (height = " << height << ", width = " << width
			 << ")." << endl << endl;
	cout << "Printing map with print_map():" << endl;

	/* prints the map with row and column numbers */
	print_map(map,height,width);
	cout << endl;

	
	cout << "====================== Question 1 ==================" << endl << endl;

	int r, c;
	bool success = get_symbol_position(map, height, width, 'T', r, c);
	
	cout << "The symbol 'T' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	success = get_symbol_position(map, height, width, '4', r, c);
	cout << "The symbol '4' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	success = get_symbol_position(map, height, width, 'z', r, c);
	cout << "The symbol 'z' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	cout << "====================== Question 2 ==================" << endl << endl;

	cout << "The symbol for Victoria station is '" <<
		get_symbol_for_station_or_line("Victoria") << "'" << endl << endl;

	
	cout << "The symbol for Oxford Circus station is '" <<
		get_symbol_for_station_or_line("Oxford Circus") << "'" << endl << endl;

	cout << "The symbol for the District Line is '" <<
		get_symbol_for_station_or_line("District Line") << "'" << endl << endl;

	// Birmingham station is not on the Tube map, so this should return ' '
	cout << "The symbol for Birmingham station is '" <<
		get_symbol_for_station_or_line("Birmingham") << "'" << endl << endl;

	cout << "====================== Question 3 ==================" << endl << endl;
        
	char route[512];
	char destination[512] = "nowhere";

	// valid route to Leicester Square with 1 line change 
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	int result = validate_route(map,height, width, "Oxford Circus", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;
	/*
	// invalid route because of backtracking between stations
	strcpy(route, "W,W,E,W,W,W");
	cout << "Starting at Sloane Square and backtracking:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Sloane Square", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result
			<< " line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	// invalid route because route goes outside of map bounds 
	strcpy(route, "E,NE,SE,SE,SE");
	cout << "Starting at Marylebone and going out of map bounds:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Marylebone", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	// Add more of your own tests here. 

	
	// invalid route to Leicester Square off track 
	strcpy(route, "S,SE,S,S,E,E,E,N,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and going off track:" << endl;
	cout << route << endl;
	result = validate_route(map,height, width, "Oxford Circus", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;


	// invalid direction entry 
	strcpy(route, "S,SE,S,S,E,E,E,UP,UP,E,E,E,E,E,E");
	cout << "Willy Wonka lift:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "Oxford Circus", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;


	

	// valid route ending at Bank reverse back therefore 1 change
	strcpy(route, "E,E,SE,E,E,W,W,NW,W,W");
	cout << "Starting at St Pauls to Bank then to St Pauls:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "St Pauls", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;



	// invalid route line hop
	strcpy(route, "E,E,N,E,E");
	cout << "Starting at Temple line hop:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "Temple", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;


	// invalid route to Leicester Square start "Oxford Circusn" extra letter
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circusn and taking the steps:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "Oxford Circusn", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	// valid route to Leicester Square with 1 line change - lowercase station entry
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at oxford circus and taking the steps:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "oxford circus", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;



	// invalid route with start station as line name
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at District Line:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "District Line", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	
	// valid route ending at Bank < character length than "nowhere" destination "bankere"?
	strcpy(route, "E,E,SE,E,E");
	cout << "Valid route starting at St Pauls to Bank:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "St Pauls", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;


	//invalid route ending out of station
	strcpy(route, "E,E,SE,E");
	cout << "Invalid route St Pauls to nowhere:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "St Pauls", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;


	// invalid route starting at ""
	
	strcpy(route, "E,E,SE,E,E");
	cout << "Starting at '' to Bank:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;
	

	//invalid route two commas
	strcpy(route, "E,E,SE,,E,E");
	cout << "Invalid double commas:" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "St Pauls", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	//invalid starting comma
	strcpy(route, ",E,E,SE,E,E");
	cout << "Starting comma error" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "St Pauls", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	// ending comma error
	strcpy(route, "E,E,SE,E,E,");
	cout << "Ending Comma error" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "St Pauls", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	// ending small letter
	strcpy(route, "E,E,SE,E,e");
	cout << "Ending small letter" << endl;
	cout << route << endl;
        result = validate_route(map,height, width, "St Pauls", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;



	// invalid route Start station "Oxford Circus \n5" newline + symbol line after 
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus\\n5 and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map,height, width, "Oxford Circus\n5", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;*/


	//invalid '' 
	strcpy(route, "");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map,height, width, "Oxford Circus", route, destination);
	
	
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;
}
