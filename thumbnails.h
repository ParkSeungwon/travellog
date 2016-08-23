#pragma once
#include<gtkmm.h>

class Thumbnails : public Gtk::HBox
{
public:
	Thumbnails(std::string directory);

protected:
	Gtk::HBox hbox1, hbox2;
	Gtk::ScrolledWindow scwin;
	std::vector<Gtk::Button> bts;
	std::vector<Gtk::Image> ims;
	std::vector<std::pair<float, float>> gps;
	Gtk::Button bt;
	
	void on_bt_click();

private:
	void sstm(std::string command) const;
	std::string psstm(std::string command) const;
	std::string vlabel(std::string dir) const;
	std::pair<float, float> gps_coordinate(std::string gps_string) const;
	void pack_all();
};
