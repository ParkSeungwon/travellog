#include<gtkmm.h>
#include"thumbnails.h"

class Winmain : public Gtk::Window
{
public:
	Winmain(std::string directory);
	
protected:
	std::string googlemap(float latitude, float longitude, int zoom_lvl,
			int width_pixel, int height_pixel, std::string additional="");
	std::string googlemap(std::initializer_list<std::pair<float, float>> places);
	Gtk::VBox vbox1, vbox2;
	Gtk::ScrolledWindow scwin;
	std::vector<Thumbnails> thumbs;

private:
	std::map<std::string, int> directories;
	std::vector<std::map<std::string, int>> photoes;
};
