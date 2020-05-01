#include <iostream>
#include "Simple_window.h"
#include "Graph.h"
#include <FL/fl_ask.H>

class Room {
public:
	double length, width, square;

	double room_data(const string& st_length, const string& st_width)
	{
		length = strtod(st_length.c_str(), NULL);	
		width = strtod(st_width.c_str(), NULL);
			if (length <= 0 || width <= 0)
			{
				fl_choice("You entered wrong room value! Please try again!","OK", 0, 0);
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
	double tile_length, tile_width, tile_square, seam, cost;

	double enter_tile_data(const string& st_tile_length, const string& st_tile_width, const string& st_seam, const string& st_cost)
	{
		tile_length = strtod(st_tile_length.c_str(), NULL);			
		tile_width = strtod(st_tile_width.c_str(), NULL);			
		seam = strtod(st_seam.c_str(), NULL);			
		cost = strtod(st_cost.c_str(), NULL);
			if (tile_length <= 0 || tile_width <= 0 || seam < 0 || cost <= 0)
			{
				fl_choice("You entered wrong tile value! Please try again!", "OK", 0, 0);
			}

		tile_square = tile_length * tile_width;

		return tile_length, tile_width, seam, cost, tile_square;
	}
};

int tile_amount_vertical(const Room& room, const Tile&  tile) {
	int vertical_answer;

	if (room.length < tile.tile_length || room.width < tile.tile_width || room.width < tile.tile_length || room.length < tile.tile_width)
	{
		fl_choice("You entered wrong value! Please try again!", "OK", 0, 0);
	}
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
	
	if (room.length < tile.tile_length || room.width < tile.tile_width || room.width < tile.tile_length || room.length < tile.tile_width) 
	{
		fl_choice("You entered wrong value! Please try again!", "OK", 0, 0);
	}

	double tile_length_with_seam = tile.tile_length + tile.seam;
	double tile_width_with_seam = tile.tile_width + tile.seam;

	double  amount_vertical = room.length / tile_width_with_seam;
	double amount_horizontal = room.width / tile_length_with_seam;

	//define a whole value
	int okr_amount_ver = int(amount_vertical + 0.5);
	int okr_amount_hor = int(amount_horizontal + 0.5);

	horizontal_answer = okr_amount_ver * okr_amount_hor;
	
	return horizontal_answer;
}

//Window
struct Room_with_tile_window : Window 
{	
	Room room;
	Tile tile;
	Room_with_tile_window(Point xy, int w, int h, const string& title);

	//Room in_box, out_box
	In_box room_length_box;
	In_box room_width_box;

	Out_box room_square_out;
	//Tile in_box, out_box
	In_box tile_length_box;
	In_box tile_width_box;
	In_box tile_seam_box;
	In_box tile_cost_box;

	//Tile results
	Out_box tile_amount;
	Out_box all_tile_cost;

private:
	Button quit_button;
	Button horizontal_result_button;
	Button save_result;
	Button open_from_file;
	Button vertical_result_button;
			
	void horizontal_result_pressed() 
	{
		result();
		tile_amount.show();
		all_tile_cost.show();
	}

	void vertical_result_pressed()
	{
		result2();
		tile_amount.show();
		all_tile_cost.show();
	}

	void save_button_pressed()
	{
		fl_choice("This button haven't realised, yet!", "OK", 0, 0);
	}

	void file_button_pressed()
	{
		fl_choice("This button haven't realised, yet!", "OK", 0, 0);
	}

	void quit()
	{
		hide();
	}

	void result()
	{
		string r_length = room_length_box.get_string();
		string r_width = room_width_box.get_string();

		string t_length = tile_length_box.get_string();
		string t_width = tile_width_box.get_string();
		string t_seam = tile_seam_box.get_string();
		string t_cost = tile_cost_box.get_string();
				
		room.room_data(r_length, r_width);
		tile.enter_tile_data(t_length, t_width, t_seam, t_cost);
				
		double hor_tile_cost;
		hor_tile_cost = tile_amount_horizontal(room, tile) * tile.cost;

		ostringstream ss1;
		ss1 << room.square_room() << ';';
		room_square_out.put(ss1.str());
		
		ostringstream ss2;
		ss2 << tile_amount_horizontal(room, tile) << ';';
		tile_amount.put(ss2.str());

		ostringstream ss3;
		ss3 << hor_tile_cost << '$';
		all_tile_cost.put(ss3.str());

		redraw();
	}

	void result2()
	{
		string r_length = room_length_box.get_string();
		string r_width = room_width_box.get_string();

		string t_length = tile_length_box.get_string();
		string t_width = tile_width_box.get_string();
		string t_seam = tile_seam_box.get_string();
		string t_cost = tile_cost_box.get_string();

		room.room_data(r_length, r_width);
		tile.enter_tile_data(t_length, t_width, t_seam, t_cost);

		double ver_tile_cost;
		ver_tile_cost = tile_amount_vertical(room, tile) * tile.cost;

		ostringstream ss1;
		ss1 << room.square_room() << ';';
		room_square_out.put(ss1.str());

		ostringstream ss2;
		ss2 << tile_amount_vertical(room, tile) << ';';
		tile_amount.put(ss2.str());

		ostringstream ss3;
		ss3 << ver_tile_cost << '$';
		all_tile_cost.put(ss3.str());



		redraw();
	}
};

Room_with_tile_window::Room_with_tile_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	horizontal_result_button{ Point{x_max() - 70, 0}, 70, 20, "Hor_Result",
	[](Address, Address pw)
		{
			reference_to<Room_with_tile_window>(pw).horizontal_result_pressed();
		}
	},
	vertical_result_button{ Point{x_max() - 70, 30}, 70, 20, "Ver_Result",
	[](Address, Address pw)
		{
			reference_to<Room_with_tile_window>(pw).vertical_result_pressed();
		}
	},
	save_result{ Point{x_max() - 70, 60 }, 70, 20, "Save result",
		[](Address, Address pw)
		{
			reference_to<Room_with_tile_window>(pw).save_button_pressed();
		}
	},
	open_from_file{ Point{x_max() - 70, 90 }, 70, 20, "Open file", 
		[](Address, Address pw)
		{
			reference_to<Room_with_tile_window>(pw).file_button_pressed();
		}
	},
	quit_button{ Point{x_max() - 70, 120}, 70, 20, "Quit",
		[](Address, Address pw)
			{
				reference_to<Room_with_tile_window>(pw).quit();
			}
	},
		
		room_square_out{ Point{x_max() -550, 0}, 100, 20, "Room Square:" },
		room_length_box{ Point{x_max() - 400, 0 }, 50, 20, "Room length:" },
		room_width_box{ Point{x_max() - 200, 0}, 50, 20, "Room width:" },

		tile_length_box{ Point{100, 30}, 50, 20, "Tile lenght:" },
		tile_width_box{ Point{x_max() -550, 30}, 50, 20, "Tile width:" },
		tile_seam_box{ Point{x_max() - 400, 30}, 50, 20, "Tile seam:" },
		tile_cost_box{ Point{x_max() -200, 30}, 50, 20, "Tile cost:" },

		//tile_square_out{ Point{x_max() -70, 120}, 50, 20, "Tile square:" },		
		tile_amount{ Point{x_max() -70, 180}, 50, 20, "Tile amount:" },
		all_tile_cost{ Point{x_max() -70, 210}, 50, 20, "Tile cost:" }

		{			
				//room
				attach(room_length_box);
				attach(room_width_box);
				attach(room_square_out);
				room_square_out.put("no points");								 					
				//tile
				attach(tile_length_box);
				attach(tile_width_box);
				attach(tile_seam_box);
				attach(tile_cost_box);
				//buttons
				attach(horizontal_result_button);
				attach(vertical_result_button);
				attach(quit_button);
				attach(save_result);
				attach(open_from_file);
				//results
				attach(tile_amount);
				tile_amount.hide();
				attach(all_tile_cost);
				all_tile_cost.hide();						 
	}


int main()
{
	try {
		Room_with_tile_window win{ Point{100, 100}, 800, 600, "Room For Tile"};
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

