#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own
	 function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */

char** allocate_2D_array(int rows, int columns) {
	char** m = new char* [rows];
	assert(m);
	for(int r=0; r<rows; r++) {
		m[r] = new char[columns];
		assert(m[r]);
	}
	return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char** m, int rows) {
	for(int r=0; r<rows; r++)
		delete [] m[r];
	delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char* filename, int& height, int& width) {
	char line[512];

	ifstream input(filename);

	height = width = 0;

	input.getline(line, 512);
	while(input) {
		if( (int) strlen(line) > width)
			width = strlen(line);
		height++;
		input.getline(line, 512);
	}

	if(height > 0)
		return true;
	return false;
}

/* pre-supplied function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width) {

	bool success = get_map_dimensions(filename, height, width);

	if(!success) return NULL;

	char** m = allocate_2D_array(height, width);

	ifstream input(filename);

	char line[512];
	char space[] = " ";

	for(int r = 0; r<height; r++) {
		input.getline(line, 512);
		strcpy(m[r], line);
		while( (int) strlen(m[r]) < width ) {
			strcat(m[r], space);
		}
	}
	return m;
}

/* pre-supplied function to print the tube map */
void print_map(char** m, int height, int width) {
	cout << setw(2) << " " << " ";
	for(int c=0; c<width; c++) {
		if(c && (c % 10) == 0) {
			cout << c/10;
		} else {
			cout << " ";
		}
	}

	cout << endl;
	cout << setw(2) << " " << " ";

	for(int c=0; c<width; c++) cout << (c % 10);

	cout << endl;

	for(int r=0; r<height; r++) {
		cout << setw(2) << r << " ";
		for(int c=0; c<width; c++) cout << m[r][c];
		cout << endl;
	}
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char* error_description(int code) {
	switch(code) {
	case ERROR_START_STATION_INVALID:
		return "Start station invalid";
	case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
		return "Route endpoint is not a station";
	case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
		return "Line hopping between stations not possible";
	case ERROR_BACKTRACKING_BETWEEN_STATIONS:
		return "Backtracking along line between stations not possible";
	case ERROR_INVALID_DIRECTION:
		return "Invalid direction";
	case ERROR_OFF_TRACK:
		return "Route goes off track";
	case ERROR_OUT_OF_BOUNDS:
		return "Route goes off map";
	}
	return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char* token) {
	const char* strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
	for(int n=0; n<8; n++) {
		if(!strcmp(token, strings[n])) return (Direction) n;
	}
	return INVALID_DIRECTION;
}


// pre-supplied function to print the tube map 
bool get_symbol_position(char** map,int height,int width,char symbol ,int& r,int& c){

  
	for(int r2=0; r2<height; r2++) {
	  for(int c2=0; c2<width; c2++) {
	     if(map[r2][c2] == symbol){
	       r = r2;
	       c = c2;
	       return true;
	     }
	   }  
	}
	r = -1; c = -1;
	return false;
}

// function that takes argument of station cstring and returns the corresponding line/station character symbol.
char get_symbol_for_station_or_line(const char station[]){
  ifstream fin;
  char symbol = ' ';

  fin.open("stations.txt");
  symbol = check_file(fin,station);
  fin.close();

  if (symbol == ' '){
    fin.open("lines.txt");
    symbol =  check_file(fin,station);
    fin.close();
  }

  return symbol;
}

//helper function that takes instream and cstring input, compares fstream line input to cstring station[] input.
//returns symbol of matching station
char check_file(ifstream& fin,const char station[]){

  char station_name[512];
  char symbol;
  bool checkln = false;

  do{
    get_line(fin,station_name,symbol);
    checkln = check_line(station,station_name);
  }while(!checkln && !fin.eof());

  if(checkln){
    return symbol;
  }
  return ' ';
}

// helper function - get one line of input file - split into symbol and station name
void get_line(ifstream& fin, char station_name[],char& symbol){
  char next;
  int index = 0;
  fin.unsetf(ios::skipws);
  fin >> symbol;
  fin >> next;
  fin >> next;
    
  while(fin.good() && next != '\n'){
    station_name[index] = next;
    fin >> next;
    index ++;
  }
  station_name[index] = '\0';
}

// helper function - takes cstring inputs and compares them to determine if they are the same, returns true if same
bool check_line(const char station[],char station_name[]){


  if(strlen(station_name) == strlen(station) && strlen(station) > 0){
    for(unsigned int i=0;i<=strlen(station_name) &&  i<strlen(station); i++){
      if(station_name[i] != station[i]) return false;
    }
    return true;
  }
  
  return false;
}

// function to iterate through supplied route string and return integer number of changes on tube map and destination of journey.
int validate_route(char ** map,const int height,const int width,const char station[],char route[],char destination[]){
  char current_symbol,old_line;
  bool station_exists = true,hop_line = false,in_station = true;
  Direction dir, old_dir;
  int changes = -1,r,c,step = 0;
  
  cout.setf(ios::boolalpha);
  
  current_symbol = get_symbol_for_station_or_line(station);
  station_exists = get_symbol_position(map,height,width,current_symbol,r,c);
  
  if(!isalnum(current_symbol) || !station_exists){
    station_exists = false;
    return -1;
  }
  if(!valid_route(route)) return -5;
  
  if(strlen(route) != 0){
    
    char* token = strtok(route,",");
    while(token != NULL){
      dir = string_to_direction(token);
      if(static_cast<int>(dir) == 8) return -5;
      if(!get_new_position(map,width,height,r,c,dir)) return -7;
    
      current_symbol = map[r][c];

      if(current_symbol == ' ') return -6;
      if(reverse_dir(dir, old_dir,step,current_symbol,changes,in_station)) return -4;
      old_dir = dir;
    
      check_line_hop(current_symbol,old_line,in_station,hop_line,changes);
      if(hop_line) return -3;
      step++;
      token = strtok(NULL,",");
    }
    
  }else changes ++;

  if(!isalnum(current_symbol)) return -2;
  
  get_station_for_symbol(current_symbol,destination);
  
  return changes;
}


//helper function to determine if train has reversed direction between stations
bool reverse_dir(const Direction dir, Direction& old_dir,const int step,char current_symbol, int& changes,const bool in_station){
  int redo_enum[8] = {0,4,6,2,1,7,3,5}, difference;

  if(step == 0){
    old_dir = dir;
    return false;
  }
  
  difference = abs(redo_enum[static_cast<int>(dir)] - redo_enum[static_cast<int>(old_dir)]);
  if(difference == 4 && !in_station) return true;
  if (difference == 4 && in_station) changes ++;
  return false;
}

// Checks the route input before tokenising if it is a valid route returns true
bool valid_route(char route[]){
  
  for(unsigned int i=0; i<strlen(route);i++){
    if(islower(route[i])) return false;
    if((i == strlen(route)-1 || i == 0) && route[i] == ',') return false;
    if(i<strlen(route)-1 && route[i+1] == ',' && route[i] == ',') return false;
  };
  return true;
}

// function to check whether the train has changed line between stations
void check_line_hop(const char current_symbol,char& old_line,bool& in_station,bool& hop_line,int& changes){
  if(!in_station){
    if(isalnum(current_symbol)) in_station = true;
    if(!isalnum(current_symbol) && old_line != current_symbol) hop_line = true;
  }else{
    if(old_line != current_symbol) changes++;
    if(!isalnum(current_symbol)) in_station = false;
    old_line = current_symbol;
  }
}



/*function that takes Direction input and returns bool = false if train is off map plus alters train
r and c position */
bool get_new_position(char** map,const int width,const int height,int& r,int& c,const Direction dir){

  int ch_r[8] = {-1,1,0,0,-1,-1,1,1};
  int ch_c[8] = {0,0,-1,1,1,-1,1,-1};

  r = r + ch_r[static_cast<int>(dir)];
  c = c + ch_c[static_cast<int>(dir)];

  if(r>height || r<0 ||c > width || c<0)
    return false;

  return true;
}

// Returns station name cstring corresponding to the supplied symbol.
void get_station_for_symbol(char current_symbol,char destination[]){
  ifstream fin;
  char station_name[512];
  char symbol;

  fin.open("stations.txt");
  
  do{
    get_line(fin,station_name,symbol);
  }while(current_symbol != symbol && !fin.eof());
  
  for(unsigned int i=0; i<= strlen(station_name); i++){
    destination[i] = station_name[i];
  }

}
