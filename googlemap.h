#pragma once
#include<gtkmm.h>
#include<webkit2/webkit2.h>
#include"thumbnails.h"

class Interface
{
public:
	virtual void set_map(std::vector<std::pair<float, float>> places) = 0;
};

class Winmain : public Gtk::Window, public Interface
{
public:
	Winmain(std::string directory);
	void set_map(std::vector<std::pair<float, float>> places);
	
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
	std::vector<std::map<std::string, int>> photoes;
};
