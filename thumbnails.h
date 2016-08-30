#pragma once
#include<gtkmm.h>
#include<string>
#include<vector>

class Thumbnails : public Gtk::HBox
{
public:
	Thumbnails(std::string directory);
	std::pair<float, float> first_gps();
	static std::string psstm(std::string command);

protected:
	Gtk::HBox hbox1, hbox2;
	Gtk::ScrolledWindow scwin;
	std::vector<Gtk::Button> bts;
	std::vector<Gtk::Image> ims;
	Gtk::Button bt;
	std::vector<std::pair<float, float>> gps;
	
	void on_bt_click(std::vector<std::pair<float, float>> places);

private:
	void sstm(std::string command) const;
	std::string vlabel(std::string dir) const;
	std::pair<float, float> gps_coordinate(std::string gps_string) const;
	void pack_all();
};
