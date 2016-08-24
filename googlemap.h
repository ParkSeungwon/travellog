#pragma once
#include<gtkmm.h>
#include<webkit2/webkit2.h>
#include<string>
#include<vector>
#include"thumbnails.h"
#include"interface.h"

class Winmain : public Gtk::Window, public Interface
{
public:
	Winmain(std::string photo_root_directory);
	void set_map(std::vector<std::pair<float, float>> latitude_and_longgitude);
	
protected:
	std::string googlemap(float latitude, float longitude, int zoom_lvl,
			int pixel_width, int pixel_height, std::string additional="");
	std::string googlemap(std::vector<std::pair<float, float>> latlong);
	Gtk::VBox vbox1, vbox2;
	Gtk::ScrolledWindow scwin;
	std::vector<Thumbnails> thumbs;
	WebKitWebView* webview;

private:
	std::map<std::string, int> directories;
	std::vector<std::pair<float, float>> daily_gps;
	std::vector<std::map<std::string, int>> photoes;
};
