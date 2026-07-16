#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <sstream>

using namespace std;

/*
const string ESC =  "\033";
const string BGR_COLOR_CODE = "48";
const string TXT_COLOR_CODE = "38";
const string TRUE_RGB_CODE = "2";
const string RESET_CODE = ESC + "[" + "m";

const int black[3] = {0, 0, 0};
const int grey[3] = {130, 130,  130};
const int white[3] = {230, 230, 230};
const int bright_white[3] = {255, 255, 255};

const int blue[3] = {0, 0, 255};
const int dark_blue[3] = {0, 0, 170}; 
const int light_blue[3] = {51, 153, 255};

const int red[3] = {255, 0, 0};
const int dark_red[3] = {190, 0, 0};
const int light_red[3] = {255, 65, 65};

const int yellow[3] = {255, 255, 0};
const int dark_yellow[3] = {220, 220, 0};
const int light_yellow[3] = {255, 255, 130};

const int magenta[3] = {255, 0, 255};
const int purple[3] = {140, 0, 140};
const int pink[3] = {255, 153, 255};

const int green[3] = {0, 255, 0};
const int dark_green[3] = {0, 130, 0};
const int light_green[3] = {51, 255, 51};

struct color {
    int red;
    int green;
    int blue;
};

map<string, const int[3]> colors = {
    {"blue", {230, 230, 230}},
    {"green", {230, 230, 230}},
    {"aqua", {230, 230, 230}},
    {"red", {230, 230, 230}},
    {"purple", {230, 230, 230}},
    {"yellow", {230, 230, 230}},
    {"white", {230, 230, 230}},
    {"grey", {230, 230, 230}},
    {"light_blue", {230, 230, 230}},
    {"black", {230, 230, 230}},
    {"light_green", {230, 230, 230}},
    {"light_aqua", {230, 230, 230}},
    {"light_red", {230, 230, 230}},
    {"light_purple", {230, 230, 230}},
    {"light_yellow", {230, 230, 230}},
    {"bright_white", {230, 230, 230}}
};

string assemble_color_indic(int red, int green, int blue, bool bgr= false) {
    string out;
    out = out + ESC + "[";
    out = bgr ? out + BGR_COLOR_CODE : out + TXT_COLOR_CODE;
    out = out + ";";
    out = out + to_string(red) + ";";
    out = out + to_string(green) + ";";
    out = out + to_string(blue);
    out = out + "m";
}

void print_c( string text, const int bgr_color[3]= black, const int txt_color[3]= white ) {
    string txt_color_code = assemble_color_indic(txt_color[0], txt_color[1], txt_color[2]);
    string bgr_color_code = assemble_color_indic(bgr_color[0], bgr_color[1], bgr_color[2]);
    cout << txt_color_code << bgr_color_code << text << RESET_CODE;
}

class File_handeler {
    public:
        void create_or_open( fstream& file, string filename ) {
            file.open(filename, ios::out | ios::in | ios::app);
        }

        void close_file( fstream& file, string filename ) {
            file.close();
        }

        int write_line_to_file(fstream& file, string input, int start_pos= 0) {
            if (file.is_open()) {
                file << input;
                return 0;
            } else {
                return 1;
            }
        }

        string read_line_from_file(fstream& file, int start_pos= 0) {
            string out;
            if (file.is_open()) {
                file.seekg(start_pos, fstream::beg);
                getline(file, out);
                return out;
            } else {
                return "file closed";
            }
        }

        void remove_file(string filename) {
            remove(filename.c_str());
        }

        void rename_file(string filename, string new_name) {
            rename(filename.c_str(), new_name.c_str());
        }
};

void print_commands() {
    print_c("TUI commands\n", light_blue);
    print_c("/open <filename>\n", light_blue);
    print_c("/create <filename>\n", light_blue);
    print_c("/add <name> <priority> <description> <details> <status> <completion>\n", light_blue);
    print_c("/priority <name> <new priority>\n", light_blue);
    print_c("/description <name> <new description>\n", light_blue);
    print_c("/details <name> <new details>\n", light_blue);
    print_c("/status <name> <new status>\n", light_blue);
    print_c("/completion <name> <completion>\n", light_blue);
    print_c("/remove <name>\n", light_blue);
    print_c("/close\n", light_blue);
}

*/

//int main() {
    string thing = "stuff";
    //to_do_list.open("To_Do.csv", ios::out | ios::in | ios::app);
    //to_do_list << "many things\n";
    //to_do_list << "many things\n";
    //print_c(thing, "aqua", "light_green");
/*
    fstream MyFile;
    MyFile.open("filename.txt", ios::out | ios::in | ios::app);
    MyFile << "&";
    MyFile.seekp(6, fstream::beg);
    cout << MyFile.tellp() << "\n";
    MyFile << "\n";
    MyFile.seekp(-3, fstream::cur);
    string out;
    getline( MyFile, out ); 
    cout << out << "\n";
    MyFile.write("&", 2);
    MyFile.seekp(-4, fstream::end);
    cout << MyFile.tellp() << "\n";
    MyFile.write("&", 2);
    MyFile.close();

    return 0;
}
*/

struct to_do_item {
    unsigned long priority;
    string name;
    string description;
    string details;
    string status;
    float completion;
};

int main() {
    fstream test_file( "test.csv" );
    string line;
    vector<to_do_item> table;

    if ( !test_file.is_open() ) {
        cerr << "error when opening to read!" << endl;
        return;
    }

    while ( getline( test_file, line ) ) { //read all lines, seperated by newline
        stringstream sstream( line );
        string field;
        vector<string> row;
        to_do_item item_line;

        while ( getline( sstream, field, ',' ) ) { //seperate comma seperated values
            row.push_back( field );
        }

        //add values to item
        item_line.priority = stoul( row[ 0 ] );
        item_line.name = row[ 1 ];
        item_line.description = row[ 2 ];
        item_line.details = row[ 3 ];
        item_line.status = row[ 4 ];
        item_line.completion = stof( row[ 5 ] );
        //add item to list

        table.push_back( item_line );
    }

    
    for ( to_do_item row : table )
        {
        test_file << to_string( row.priority ) << ",";
        test_file << row.name << ",";
        test_file << row.description << ",";
        test_file << row.details << "<";
        test_file << row.status << ",";
        test_file << to_string( row.completion ) << "\n";
    }

    return 0;
}