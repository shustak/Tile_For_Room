#include <iostream>
#include "Simple_window.h"
#include "Graph.h"
#include <FL/fl_ask.H>
//#include <iostream>


class Room {
public:
	double length, width, square;
	std::string st_length, st_width;

	double room_data()
	{
		length = strtod(st_length.c_str(), NULL);
			if (length <= 0) 
			{
				fl_choice("You entered wrong room lenght value! Please try again!", "OK", 0, 0);
			}
		width = strtod(st_width.c_str(), NULL);
			if (width <= 0)
			{
				fl_choice("You entered wrong room width value! Please try again!","OK", 0, 0);
			}			
		return length, width;
	}
	double square_room()
	{
		square = length * width;
		return square;
	}
};

class Tile {
public:
	std::string st_tile_length, st_tile_width, st_seam, st_cost;
	double tile_length, tile_width, tile_square, seam, cost;

	double enter_tile_data()
	{
		tile_length = strtod(st_tile_length.c_str(), NULL);
			if (tile_length <= 0)
			{
				fl_choice("You entered wrong tile lenght value! Please try again!", "OK", 0, 0);
			}
		tile_width = strtod(st_tile_width.c_str(), NULL);
			if (tile_width <= 0)
			{
				fl_choice("You entered wrong tile width value! Please try again!", "OK", 0, 0);
			}
		return tile_length, tile_width;
	}
	double tile_square_m()
	{
		tile_square = tile_length * tile_width;

		return tile_square;
	}
	double tile_seam()
	{
		seam = strtod(st_seam.c_str(), NULL);
			if (seam < 0)
			{
				fl_choice("You entered wrong tile seam value! Please try again!", "OK", 0, 0);
			}
		return seam;
	}
	double tile_cost()
	{
		cost = strtod(st_cost.c_str(), NULL);
			if (cost <= 0) 
			{
				fl_choice("You entered wrong tile cost value! Please try again!", "OK", 0, 0);
			}
		return cost;
	}
};

/*int tile_amount_vertical(const Room& room, const Tile&  tile) {
	int vertical_answer;

	if (room.length < tile.tile_length || room.width < tile.tile_width || room.width < tile.tile_length || room.length < tile.tile_width) throw runtime_error(" You entered wrong value!\n");

	double tile_length_with_seam = tile.tile_length + tile.seam;
	double tile_width_with_seam = tile.tile_width + tile.seam;

	double amount_vertical = room.length / tile_length_with_seam;
	double amount_horizontal = room.width / tile_width_with_seam;

	//define a whole value
	int okr_amount_ver = int(amount_vertical + 0.5);
	int okr_amount_hor = int(amount_horizontal + 0.5);

	vertical_answer = okr_amount_ver * okr_amount_hor;
	return vertical_answer;
}

int tile_amount_horizontal(const Room& room, const Tile& tile) {
	int horizontal_answer;

	if (room.length < tile.tile_length || room.width < tile.tile_width || room.width < tile.tile_length || room.length < tile.tile_width) throw runtime_error(" You entered wrong value\n");

	double tile_length_with_seam = tile.tile_length + tile.seam;
	double tile_width_with_seam = tile.tile_width + tile.seam;

	double  amount_vertical = room.length / tile_width_with_seam;
	double amount_horizontal = room.width / tile_length_with_seam;

	//define a whole value
	int okr_amount_ver = int(amount_vertical + 0.5);
	int okr_amount_hor = int(amount_horizontal + 0.5);

	horizontal_answer = okr_amount_ver * okr_amount_hor;
	return horizontal_answer;
}*/

//Window
struct Room_with_tile_window : Window 
{	
	Room room;
	Tile tile;

	Room_with_tile_window(Point xy, int w, int h, const string& title);

	//Room in_box, out_box
	In_box room_length_box;
	In_box room_width_box;

	Out_box room_out;
	Out_box room_square_out;
	//Tile in_box, out_box
	In_box tile_length_box;
	In_box tile_width_box;
	In_box tile_seam_box;
	In_box tile_cost_box;

	Out_box tile_square_out;
	Out_box tile_cost_out;

private:
	Button room_enter_button;
	Button result_button;
	Button return_window_button;

	void go_to_tile();
	void result();

	void room_hide();
	void tile_hide();

	void room_enter_pressed() 
	{
		room_length_box.hide();
		room_width_box.hide(); 
		room_enter_button.hide();  
		result_button.show();
		return_window_button.show();
		tile_length_box.show();
		tile_width_box.show();
		tile_seam_box.show();
		tile_cost_box.show();
		tile_square_out.show();
		tile_cost_out.show();
	}
	void return_button_pressed()
	{
		room_length_box.show();
		room_width_box.show();
		room_enter_button.show();
		result_button.hide();
		return_window_button.hide();
		tile_length_box.hide();
		tile_width_box.hide();
		tile_seam_box.hide();
		tile_cost_box.hide();
		tile_square_out.hide();
		tile_cost_out.hide();
	}
};

Room_with_tile_window::Room_with_tile_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	room_enter_button{ Point{x_max() - 150, 0}, 70, 20, "Go to Tile",
	[](Address, Address pw)
		{
			reference_to<Room_with_tile_window>(pw).go_to_tile();
		}
	},
		room_length_box{ Point{x_max() - 310, 0 }, 50, 20, "Room length:" },
		room_width_box{ Point{x_max() - 210, 0}, 50, 20, "Room width:" },
		room_out{ Point{100, 0}, 100, 20, "Room:" },
		room_square_out{ Point{100, 0}, 100, 20, "Square:" }, 
	
	result_button{ Point{x_max() - 70, 0}, 70, 20, "Result",
	[](Address, Address pw)
		{
			reference_to<Room_with_tile_window>(pw).result();
		}
	},

		tile_length_box{ Point{x_max() - 310, 0}, 50, 20, "Tile lenght:" },
		tile_width_box{ Point{x_max() - 210, 0}, 50, 20, "Tile width:" },
		tile_seam_box{ Point{x_max() - 210, 0}, 50, 20, "Tile seam:" },
		tile_cost_box{ Point{x_max() - 210, 0}, 50, 20, "Tile cost:" },
		tile_square_out{ Point{x_max() - 210, 0}, 50, 20, "Tile square:" },
		tile_cost_out{ Point{100, 0}, 100, 20, "Tile cost:" },

	return_window_button{ Point{x_max() - 70, 30}, 70, 20, "Return to room data" ,
				 [](Address, Address pw)
					 {
						  reference_to<Room_with_tile_window>(pw).return_button_pressed();
					 }
		}

					 {
						 //lines.set_color(Color::black); //I've added black color for lines.

						 attach(room_length_box);
						 attach(room_width_box);
						 attach(room_out);
						 room_out.put("no points");
						 attach(room_square_out);
						 room_square_out.put("no points");
						 attach(room_enter_button);
						 					
						 attach(result_button);
						 result_button.hide();
						 attach(return_window_button);
						 return_window_button.hide();

						 attach(tile_length_box);
						 tile_length_box.hide();
						 attach(tile_width_box);
						 tile_width_box.hide();
						 attach(tile_seam_box);
						 tile_seam_box.hide();
						 attach(tile_cost_box);
						 tile_cost_box.hide();

						 attach(tile_square_out);
						 tile_square_out.hide();
						 tile_square_out.put("no points");
						 attach(tile_cost_out);
						 tile_cost_out.hide();
						 tile_cost_out.put("no points");
						 
					 }

void Room_with_tile_window::go_to_tile()
{
	string r_length = room_length_box.get_string();
	string r_width = room_width_box.get_string();
	room.st_length = r_length;
	room.st_width = r_width;

	room.room_data();
	room.square_room();

	ostringstream ss1;
	ss1 << "lenght:" << r_length << ';' << " width:" << r_width << ';';
	room_out.put(ss1.str());

	ostringstream ss2;
	ss2 << "Room square:" << room.square_room() << ';';
	room_square_out.put(ss2.str());;

	redraw();
}

void Room_with_tile_window::result()
{
	string t_length = tile_length_box.get_string();
	string t_width = tile_width_box.get_string();
	string t_seam = tile_seam_box.get_string();
	string t_cost = tile_cost_box.get_string();

	tile.st_tile_length = t_length;
	tile.st_tile_width = t_width;
	tile.st_seam = t_seam;
	tile.st_cost = t_cost;

	tile.enter_tile_data();
	tile.tile_seam();
	tile.tile_square_m();
	tile.tile_cost();

	ostringstream ss3;
	ss3 << "Tile square:" << tile.tile_square_m() << ';';
	tile_square_out.put(ss3.str());
		
	ostringstream ss4;
	ss4 << "Tile cost:" << tile.tile_cost() << ';';
	tile_cost_out.put(ss4.str());

	redraw();
}



int main()
{
	try {
		Room_with_tile_window win{ Point{100, 100}, 800, 600, "Room For Tile" };
		return gui_main();
	}
	catch (exception& e) {
		cerr << "Exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some Exception\n";
		return 2;
	}
}

