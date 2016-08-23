#pragma once
#include<gtkmm.h>
#include<webkit2/webkit2.h>
#include"thumbnails.h"
#include"interface.h"

class Winmain : public Gtk::Window, public Interface
{
public:
	Winmain(std::string directory);
	virtual void set_map(std::vector<std::pair<float, float>> places);
	
protected:
	std::string googlemap(float latitude, float longitude, int zoom_lvl,
			int width_pixel, int height_pixel, std::string additional="");
	std::string googlemap(std::vector<std::pair<float, float>> places);
	Gtk::VBox vbox1, vbox2;
	Gtk::ScrolledWindow scwin;
	std::vector<Thumbnails> thumbs;
	WebKitWebView* webview;

private:
	std::map<std::string, int> directories;
	std::vector<std::pair<float, float>> daily_gps;
	std::vector<std::map<std::string, int>> photoes;
};
