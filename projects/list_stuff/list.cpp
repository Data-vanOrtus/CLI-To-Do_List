#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

#include <iostream>
#include <fstream>
#include <sstream>

#include <chrono>
#include <thread>

//#include <windows.h> //windows
//#include <unistd.h> //linux,unix

using namespace std;

const string ESC =  "\033";
const string BGR_COLOR_CODE = "48";
const string TXT_COLOR_CODE = "38";
const string TRUE_RGB_CODE = "2";
const string RESET_CODE = ESC + "[" + "m";

const int black[3] = { 0, 0, 0 };
const int grey[3] = { 130, 130,  130 };
const int white[3] = { 230, 230, 230 };
const int bright_white[3] = { 255, 255, 255 };

const int blue[3] = { 0, 0, 255 };
const int dark_blue[3] = { 0, 0, 170 }; 
const int light_blue[3] = { 51, 153, 255 };

const int red[3] = { 255, 0, 0 };
const int dark_red[3] = { 190, 0, 0 };
const int light_red[3] = { 255, 65, 65 };

const int yellow[3] = { 255, 255, 0 };
const int dark_yellow[3] = { 220, 220, 0 };
const int light_yellow[3] = { 255, 255, 130 };

const int magenta[3] = { 255, 0, 255 };
const int purple[3] = { 140, 0, 140 };
const int pink[3] = { 255, 153, 255 };

const int green[3] = { 0, 255, 0 };
const int dark_green[3] = { 0, 130, 0 };
const int light_green[3] = { 51, 255, 51 };

struct to_do_item {
    unsigned long priority;
    string name;
    string description;
    string details;
    string status;
    float completion;
};

struct command {
    string base_command;
    string name;
    unsigned long priority;
    string description;
    string details;
    string status;
    float completion;
    string filename;
    bool invalid_command = false;
};

map<string, int> base_command_ids = {
    { "/open", 1 },
    { "/create", 2 },
    { "/add", 3 },
    { "/priority", 4 },
    { "/description", 5 },
    { "/details", 6 },
    { "/status", 7 },
    { "/completion", 8 },
    { "/remove", 9 },
    { "/close", 10 },
    { "/save", 11 },
    { "/print_list", 12 },
    { "/show_item", 13 }
};

class big_list_stuff {
    public:
        //index = priority - 1
        vector<to_do_item> MAIN_LIST;

        void add_item( string name,
                       unsigned long priority,
                       string description,
                       string details,
                       string status,
                       float completion )
            {
            to_do_item* to_add = new to_do_item;
            (*to_add).name = name;
            (*to_add).priority = priority;
            if ( description != "" ) {
                (*to_add).description = description;
            }
            if ( details != "" ) {
                (*to_add).details = details;
            }
            if ( status != "" ) {
                (*to_add).status = status;
            }
            if ( completion != 0.0 ) {
                (*to_add).completion = completion;
            }
            MAIN_LIST.push_back( *to_add );
            change_prority( name,
                            priority );

            delete to_add;
        }

        void remove_item( string name )
            {
            int index;
            for ( int i = 0; i < MAIN_LIST.size(); i++ )
                {
                if ( MAIN_LIST.at( i ).name == name ) {
                    unsigned long priority;
                    index = i;
                    vector<to_do_item>::iterator iter_pos;
                    iter_pos = MAIN_LIST.begin() + i;
                    priority = MAIN_LIST.at( index ).priority;
                    for ( int prio = priority + 1; prio <= MAIN_LIST.size(); prio++ )
                        {
                        MAIN_LIST.at( prio - 1 ).priority = MAIN_LIST.at( prio - 1 ).priority - 1;
                    }
                    MAIN_LIST.erase( iter_pos );
                    sort( MAIN_LIST.begin(),
                          MAIN_LIST.end(),
                          big_list_stuff::customLess );
                    break;
                }
            }
        }

        void change_prority( string name,
                             unsigned long new_priority )
            {
            int index;
            unsigned long current_priority;
            //check for out of bounds error
            //check if name match
            for ( int i = 0; i < MAIN_LIST.size(); i++ )
                {
                if ( MAIN_LIST.at( i ).name == name ) {
                    index = i;
                    current_priority = MAIN_LIST.at( index ).priority;
                    if ( current_priority < new_priority ) {
                        for ( int prio = current_priority + 1; prio <= new_priority; prio++ ) {
                            MAIN_LIST.at( prio - 1 ).priority = MAIN_LIST.at( prio - 1 ).priority - 1;
                        }
                    } else if ( current_priority > new_priority ) {
                        for ( int prio = new_priority; prio < current_priority; prio++ )
                            {
                            MAIN_LIST.at( prio - 1 ).priority = MAIN_LIST.at( prio - 1 ).priority + 1;
                        }
                    } else if ( new_priority = current_priority ) {
                        break;
                    } else {
                        //error
                    }
                    MAIN_LIST.at( index ).priority = new_priority;
                    //sort
                    //safe to file
                    //vector<to_do_item>::iterator iter_MAIN_LIST;
                    sort( MAIN_LIST.begin(),
                          MAIN_LIST.end(),
                          big_list_stuff::customLess );
                    break;
                }
            }
        }

        void change_description( string name,
                                 string new_description )
            {
            int index;
            //check for out of bounds error
            //check if name match
            for ( int i = 0; i < MAIN_LIST.size(); i++ )
                {
                if ( MAIN_LIST.at( i ).name == name ) {
                    index = i;
                    MAIN_LIST.at( index ).description = new_description;
                    break;
                }
            }
        }

        void change_details( string name,
                             string new_details )
            {
            int index;
            //check for out of bounds error
            //check if name match
            for ( int i = 0; i < MAIN_LIST.size(); i++ )
                {
                if ( MAIN_LIST.at( i ).name == name ) {
                    index = i;
                    MAIN_LIST.at( index ).details = new_details;
                    break;
                }
            }
        }

        void change_status( string name,
                            string new_status )
            {
            int index;
            //check for out of bounds error
            //check if name match
            for ( int i = 0; i < MAIN_LIST.size(); i++ )
                {
                if ( MAIN_LIST.at( i ).name == name ) {
                    index = i;
                    MAIN_LIST.at( index ).status = new_status;
                    break;
                }
            }
        }

        void change_completion( string name,
                                float new_completion )
            {
            int index;
            //check for out of bounds error
            //check if name match
            for ( int i = 0; i < MAIN_LIST.size(); i++ )
                {
                if ( MAIN_LIST.at( i ).name == name ) {
                    index = i;
                    MAIN_LIST.at( index ).completion = new_completion;
                    break;
                }
            }
        }

    private:
        struct
            {
            bool operator()(to_do_item a, to_do_item b) const { return a.priority < b.priority; }
        } customLess;
};

class File_handler {
    public:
        void create_or_open( fstream& file,
                             string filename )
            {
            file.open( filename,
                       ios::out | ios::in | ios::app );
        }

        void close_file( fstream& file,
                         string filename )
            {
            file.close();
        }

        void read_file_to_list( fstream& file,
                                vector<to_do_item> &List )
            {
            string line;
            while ( getline( file, line ) )
                { //read all lines, seperated by newline
                stringstream sstream( line );
                string field;
                vector<string> row;
                to_do_item item_line;

                while ( getline( sstream, field, ',' ) )
                    { //seperate comma seperated values
                    row.push_back( field );
                }

                //add values to item
                item_line.priority = stoul( row[0] );
                item_line.name = row[1];
                item_line.description = row[2];
                item_line.details = row[3];
                item_line.status = row[4];
                item_line.completion = stof( row[5] );
                
                //add item to list
                List.push_back( item_line );
            }
        }

        void write_list_to_file( fstream& file,
                                 string file_name,
                                 vector<to_do_item> list )
            {
            fstream list_new;
            list_new.open( "temp_list",
                           ios::out | ios::in | ios::app | ios::trunc );
            for ( to_do_item row : list )
                {
                list_new << to_string( row.priority ) << ",";
                list_new << row.name << ",";
                list_new << row.description << ",";
                list_new << row.details << "<";
                list_new << row.status << ",";
                list_new << to_string( row.completion ) << "\n";
            }

            file.close();
            file.open( file_name,
                       ios::out | ios::in | ios::app | ios::trunc ); //this clears the file
            file << list_new.rdbuf();
            list_new.close();
        }

        void remove_file( string filename )
            {
            remove( filename.c_str() );
        }

        void rename_file( string filename,
                          string new_name )
            {
            rename( filename.c_str(),
                    new_name.c_str() );
        }

        void move_pointer( fstream& file,
                           int line,
                           //int col,
                           bool write_poiter= false ) 
            {
            if ( write_poiter ) {
                file.seekp( line,
                            fstream::beg );
            } else {
                file.seekg( line,
                            fstream::beg );
            }
        }
};

class TUI {
    public:
        TUI() {
            print_commands();
        }

        command read_and_format()
            {
            command user_command;
            string input = read_user_input();
            user_command = format_user_input( input );
            return user_command;
        }

        void print_c_tui( string text,
                          int text_color[3],
                          int bgr_color[3] )
            {
            print_c( text,
                     text_color,
                     bgr_color );
        }

        void open_list()
            {
        }

        void create_list()
            {
        }

    private:
        string read_user_input()
            {
            string user_command;
            int len_input = 1000;
            char input[len_input];
            cin.getline( input,
                        len_input );
            for ( char symbol : input )
                {
                user_command += symbol;
            }
            return user_command;
        }

        command format_user_input( string input )
            {
            vector<string> tokens;
            string delimiter = " ";
            size_t pos = 0;
            int input_length = input.length();
            string token;

            string base_command;
            string name ="";
            string priority = "";
            string description = "";
            string details = "";
            string status = "";
            string completion = "";
            string filename = "";

            command user_command_formatted;

            if ( input[0] == '/' ) {
                while(( pos = input.find(delimiter)) != string::npos )
                    {
                    token = input.substr( 0,
                                          pos );
                    tokens.push_back(token);
                    input.erase( 0,
                                 pos + delimiter.length() );
                }
                tokens.push_back( input );
            } else {
                print_c( "This isn't a command. Please enter a command.\n",
                         purple,
                         light_green );
                print_commands();
            }
            int command_id;
            try {
                command_id = base_command_ids.at( tokens[0] );
                switch(command_id) {
                    case 1:
                        base_command = tokens[0];
                        filename = tokens[1];
                        break;
                    case 2:
                        base_command = tokens[0];
                        filename = tokens[1];
                        break;
                    case 3:
                        base_command = tokens[0];
                        name = tokens[1];
                        priority = tokens[2];
                        description = tokens[3];
                        details = tokens[4];
                        status = tokens[5];
                        completion = tokens[6];
                        break;
                    case 4:
                        base_command = tokens[0];
                        name = tokens[1];
                        priority = tokens[2];
                        break;
                    case 5:
                        base_command = tokens[0];
                        name = tokens[1];
                        description = tokens[2];
                        break;
                    case 6:
                        base_command = tokens[0];
                        name = tokens[1];
                        details = tokens[2];
                        break;
                    case 7:
                        base_command = tokens[0];
                        name = tokens[1];
                        status = tokens[2];
                        break;
                    case 8:
                        base_command = tokens[0];
                        name = tokens[1];
                        completion = tokens[2];
                        break;
                    case 9:
                        base_command = tokens[0];
                        name = tokens[1];
                        break;
                    case 10:
                        base_command = tokens[0];
                        break;
                    case 11:
                        base_command = tokens[0];
                }

                user_command_formatted.base_command = base_command;
                user_command_formatted.name = name;
                user_command_formatted.description = description;
                user_command_formatted.details = details;
                user_command_formatted.status = status;
                user_command_formatted.filename = filename;
                user_command_formatted.priority = stoul( priority );
                user_command_formatted.completion = stof( completion );
            }
            catch ( std::out_of_range ) {
                user_command_formatted.invalid_command = true;
                print_c( "Command not found.\n",
                         purple,
                         light_green );
                print_commands();
                return user_command_formatted;
            }
            return user_command_formatted;
        }

        string assemble_color_indic( int red,
                                     int green,
                                     int blue,
                                     bool bgr= false )
            {
            string out;
            out = out + ESC + "[";
            out = bgr ? out + BGR_COLOR_CODE : out + TXT_COLOR_CODE;
            out = out + ";";
            out = out + to_string( red ) + ";";
            out = out + to_string( green ) + ";";
            out = out + to_string( blue );
            out = out + "m";

            return out;
        }

        void print_c( string text,
                      const int bgr_color[3]= black,
                      const int txt_color[3]= white )
            {
            string txt_color_code = assemble_color_indic( txt_color[0],
                                                          txt_color[1],
                                                          txt_color[2] );
            string bgr_color_code = assemble_color_indic( bgr_color[0],
                                                          bgr_color[1],
                                                          bgr_color[2] );
            cout << txt_color_code << bgr_color_code << text << RESET_CODE;
        }

        void print_commands()
            {
            print_c( "TUI commands\n",
                     light_blue );
            print_c( "/open <filename>\n",
                     light_blue );
            print_c( "/create <filename>\n",
                     light_blue );
            print_c( "/add <name> <priority> <description> <details> <status> <completion>\n",
                     light_blue );
            print_c( "/priority <name> <new priority>\n",
                     light_blue );
            print_c( "/description <name> <new description>\n",
                     light_blue );
            print_c( "/details <name> <new details>\n",
                     light_blue );
            print_c( "/status <name> <new status>\n",
                     light_blue );
            print_c( "/completion <name> <completion>\n",
                     light_blue );
            print_c( "/remove <name>\n",
                     light_blue );
            print_c( "/close\n",
                     light_blue );
            print_c( "/save\n",
                     light_blue );
            print_c( "/print_list\n",
                     light_blue );
            print_c( "/show_item <name>\n",
                     light_blue );
        }
};

int main() {
    big_list_stuff LIST;
    TUI Tui;
    command input_command;
    File_handler file_handler;

    fstream current_list;
    string current_list_name;

    volatile bool run = true;
    while( run ) {
        while ( !cin.peek() )
            {
            //do nothing, this_thread is the correct one lol
            this_thread::sleep_for( chrono::milliseconds( 500 ) );
        }
        input_command = Tui.read_and_format();
        if ( input_command.invalid_command ) {
            continue;
        } else {
            switch( base_command_ids.at( input_command.base_command )) {
                case 1:
                    //open a file
                    if ( !current_list.is_open() ) {
                        file_handler.create_or_open( current_list,
                                                     input_command.filename );
                        current_list_name = input_command.filename;
                    }
                case 2:
                    //create a file
                    file_handler.create_or_open( current_list,
                                                 input_command.filename );
                    current_list_name = input_command.filename;
                case 3:
                    LIST.add_item( input_command.name,
                                   input_command.priority,
                                   input_command.description,
                                   input_command.details,
                                   input_command.status,
                                   input_command.completion );
                case 4:
                    LIST.change_prority( input_command.name,
                                         input_command.priority );
                case 5:
                    LIST.change_description( input_command.name,
                                             input_command.description );
                case 6:
                    LIST.change_details( input_command.name,
                                         input_command.details );
                case 7:
                    LIST.change_status( input_command.name,
                                        input_command.status );
                case 8:
                    LIST.change_completion( input_command.name,
                                            input_command.completion );
                case 9:
                    LIST.remove_item( input_command.name );
                case 10:
                    //close file safly
                    if ( current_list.is_open() ) {
                        file_handler.write_list_to_file( current_list,
                                                         current_list_name,
                                                         LIST.MAIN_LIST );
                        file_handler.close_file( current_list,
                                                 input_command.filename );
                    }
                    run = false;
                case 11:
                    // save list to file
                    file_handler.write_list_to_file( current_list,
                                                     current_list_name,
                                                     LIST.MAIN_LIST );
                case 12:
                    //print the list
                    for ( to_do_item row : LIST.MAIN_LIST )
                        {
                        cout << "priority: " << to_string( row.priority ) << " ";
                        cout << "name: " << row.name << " ";
                        cout << "completion: " << to_string( row.completion ) << " ";
                        cout << "description: " << row.description << "\n";
                    }
                case 13:
                    //print specific element of the list
                    int index;
                    for ( int i = 0; i < LIST.MAIN_LIST.size(); i++ )
                        {
                        if ( LIST.MAIN_LIST.at( i ).name == input_command.name ) {
                            index = i;
                            break;
                        }
                    }
                    cout << "priority: " << to_string( LIST.MAIN_LIST[index].priority ) << " ";
                    cout << "name: " << LIST.MAIN_LIST[index].name << " ";
                    cout << "completion: " << to_string( LIST.MAIN_LIST[index].completion ) << "\n";
                    cout << "description: " << LIST.MAIN_LIST[index].description << "\n";
                    cout << "details: " << LIST.MAIN_LIST[index].details << "\n";
                    cout << "status: " << LIST.MAIN_LIST[index].status << "\n";
            }
        }
    }
    return 0;
}