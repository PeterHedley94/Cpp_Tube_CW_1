enum Direction {N, S, W, E, NE, NW, SE, SW, INVALID_DIRECTION};

/* error codes for Question 3 */
#define ERROR_START_STATION_INVALID -1
#define ERROR_ROUTE_ENDPOINT_IS_NOT_STATION -2
#define ERROR_LINE_HOPPING_BETWEEN_STATIONS -3
#define ERROR_BACKTRACKING_BETWEEN_STATIONS -4
#define ERROR_INVALID_DIRECTION -5
#define ERROR_OFF_TRACK -6
#define ERROR_OUT_OF_BOUNDS -7

/* pre-supplied function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width);

/* pre-supplied function to print the tube map */
void print_map(char** m, int height, int width);

/* pre-supplied helper function to describe errors for Question 3 */
const char* error_description(int code);

/* presupplied helper function for converting string to Direction enum */
Direction string_to_direction(const char* token);

/*function for finding a symbol in the map*/
bool get_symbol_position(char** map,int height,int width,char symbol ,int& r,int& c);

// function that takes argument of station cstring and returns the corresponding line/station character symbol.
char get_symbol_for_station_or_line(const char station[]);

//helper function that takes instream and cstring input, compares fstream line input to cstring station[] input. Returns symbol of matching station
char check_file(ifstream& fin,const char station[]);

// helper function - get one line of input file - split into symbol and station name
void get_line(ifstream& fin, char station_name[],char& symbol);

// helper function - takes cstring inputs and compares them to determine if they are the same, returns true if same
bool check_line(const char station[],char station_name[]);

// function to iterate through supplied route string and return integer number of changes on tube map and destination of journey.
int validate_route(char ** map,const int height,const int width,const char station[],char route[],char destination[]);

// Checks the route input before tokenising if it is a valid route returns true
bool valid_route(char route[]);


/*function that takes Direction input and returns bool = false if train is off map plus alters train r and c position */
bool get_new_position(char** map,const int height,const int width,int &r,int &c,const Direction dir);


//helper function to determine if train has reversed direction between stations if at station changes ++
bool reverse_dir(const Direction dir, Direction& old_dir,const int step,const char current_symbol,int& changes, const bool in_station);


// function to check whether the train has changed line between stations
void check_line_hop(const char current_symbol,char& old_line,bool& in_station,bool& hop_line,int& changes);

// Returns station name cstring corresponding to the supplied symbol.
void get_station_for_symbol(const char current_symbol,char destination[]);
