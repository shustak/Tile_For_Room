#include <iostream>
#include "Simple_window.h"
#include "Graph.h"
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>
#include <math.h>

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
//fuctions to define amount horizontal and vertical tiles
int hor_okr_lenght(const Room& room, const Tile& tile) {

	double tile_length_with_seam = tile.tile_length + tile.seam;
	double amount_horizontal = room.length / tile_length_with_seam;
	
	int okr_amount_hor_length = int(ceil(amount_horizontal));

	return okr_amount_hor_length;
}

int hor_okr_width(const Room& room, const Tile& tile) {

	double tile_width_with_seam = tile.tile_width + tile.seam;
	double amount_horizontal = room.width / tile_width_with_seam;

	int okr_amount_hor_width = int(ceil(amount_horizontal));

	return okr_amount_hor_width;
}

int ver_okr_lenght(const Room& room, const Tile& tile) {

	double tile_length_with_seam = tile.tile_width + tile.seam;
	double amount_horizontal = room.length / tile_length_with_seam;

	int okr_amount_ver_length = int(ceil(amount_horizontal));

	return okr_amount_ver_length;
}

int ver_okr_width(const Room& room, const Tile& tile) {

	double tile_length_with_seam = tile.tile_length + tile.seam;
	double amount_horizontal = room.width / tile_length_with_seam;

	int okr_amount_ver_width = int(ceil(amount_horizontal));

	return okr_amount_ver_width;
}
//define all horizontal amount tile in the room 
int tile_amount_horizontal(const Room& room, const Tile& tile) {
	if (room.length < tile.tile_length || room.width < tile.tile_width || room.width < tile.tile_length || room.length < tile.tile_width)
	{
		fl_choice("You entered wrong value! Please try again!", "OK", 0, 0);
	}
	int horizontal_answer = hor_okr_lenght(room, tile) * hor_okr_width(room, tile);

	return horizontal_answer;
}

//define all vertical amount tile in the room 
int tile_amount_vertical(const Room& room, const Tile&  tile) {
	if (room.length < tile.tile_length || room.width < tile.tile_width || room.width < tile.tile_length || room.length < tile.tile_width)
	{
		fl_choice("You entered wrong value! Please try again!", "OK", 0, 0);
	}
	int vertical_answer = ver_okr_lenght(room, tile) * ver_okr_width(room, tile);
	return vertical_answer;
}
//Window class
struct Room_with_tile_window : Window
{
	Room room;
	Tile tile;
	Room_with_tile_window(Point xy, int w, int h, const string& title);

	int x_orig = 400; //Window center
	int y_orig = 300;

	Point orig{ x_orig, y_orig };

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
	
	void draw(int par)
	{
		int tlx2 = 10;
		int tly2 = 60;
		//drawing for horizontal tile orientation
		if (par == 1) 
		{
			int numOfColumns = hor_okr_lenght(room, tile);
			int numOfRows = hor_okr_width(room, tile);

			int numOfSquares = numOfColumns * numOfRows;

			int tileL2 = int(tile.tile_length * 100);
			int tileW2 = int(tile.tile_width * 100);

			vector<Graph_lib::Rectangle*> vr;
			vr.clear();
			vr.reserve(numOfSquares);
			for (int i = 0; i < numOfColumns; ++i)
			{
				for (int j = 0; j < numOfRows; ++j)
				{
					Graph_lib::Rectangle* r = new Graph_lib::Rectangle(Point(10 + tileL2 * i, 60 + tileW2 * j), tileL2, tileW2);
					// fill the consequtive squares with white or green color
					if ((i + j) % 2 == 0)
					{
						r->set_fill_color(Color::dark_green);
					}
					else r->set_color(Color::white);
					vr.push_back(r);
				}
			}
			for (size_t k = 0; k < vr.size(); ++k) attach(*vr[k]);
		}
		//drawing for vertical tile orientation
		if(par==2)
		{
			int numOfColumns = ver_okr_lenght(room, tile);
			int numOfRows = ver_okr_width(room, tile);

			int numOfSquares = numOfColumns * numOfRows;

			int tileL2 = int(tile.tile_width * 100);
			int tileW2 = int(tile.tile_length * 100);

			vector<Graph_lib::Rectangle*> vr;
			vr.clear();
			vr.reserve(numOfSquares);
			for (int i = 0; i < numOfColumns; ++i)
			{
				for (int j = 0; j < numOfRows; ++j)
				{
					Graph_lib::Rectangle* r = new Graph_lib::Rectangle(Point(10 + tileL2 * i, 60 + tileW2 * j), tileL2, tileW2);
					// fill the consequtive squares with white or green color
					if ((i + j) % 2 == 0) 
					{ 
						r->set_fill_color(Color::dark_green);
					}
					else r->set_color(Color::white);
					vr.push_back(r);
				}
			}
			for (size_t k = 0; k < vr.size(); ++k) attach(*vr[k]);
		}				
	}
	//after click horizontal button
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
		ss1 << room.square_room() << "m2;";
		room_square_out.put(ss1.str());
		
		ostringstream ss2;
		ss2 << tile_amount_horizontal(room, tile) << ';';
		tile_amount.put(ss2.str());

		ostringstream ss3;
		ss3 << hor_tile_cost << '$';
		all_tile_cost.put(ss3.str());
		draw(1);

		redraw();
	}
	//after click vertical button
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
		ss1 << room.square_room() << "m2;";
		room_square_out.put(ss1.str());

		ostringstream ss2;
		ss2 << tile_amount_vertical(room, tile) << ';';
		tile_amount.put(ss2.str());

		ostringstream ss3;
		ss3 << ver_tile_cost << '$';
		all_tile_cost.put(ss3.str());
		draw(2);

		redraw();
	}
};

Room_with_tile_window::Room_with_tile_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	horizontal_result_button{ Point{x_max() - 70, 0}, 70, 20, "Horizontal",
	[](Address, Address pw)
		{
			reference_to<Room_with_tile_window>(pw).horizontal_result_pressed();
		}
	},
	vertical_result_button{ Point{x_max() - 70, 30}, 70, 20, "Vertical",
	[](Address, Address pw)
		{
			reference_to<Room_with_tile_window>(pw).vertical_result_pressed();
		}
	},
	save_result{ Point{x_max() - 70, 60 }, 70, 20, "Save",
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
		room_square_out{ Point{x_max() -550, 0}, 80, 20, "Room Square:" },
		room_length_box{ Point{x_max() -350, 0 }, 50, 20, "Room length, m:" },
		room_width_box{ Point{x_max() - 200, 0}, 50, 20, "Room width, m:" },

		tile_length_box{ Point{100, 30}, 50, 20, "Tile lenght, m:" },
		tile_width_box{ Point{x_max() -550, 30}, 50, 20, "Tile width, m:" },
		tile_seam_box{ Point{x_max() - 350, 30}, 50, 20, "Tile seam, m:" },
		tile_cost_box{ Point{x_max() -200, 30}, 50, 20, "Tile cost, $:" },
	
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

