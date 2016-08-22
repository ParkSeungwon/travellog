#include<gtkmm.h>
class Winmain : public Gtk::Window
{
public:
	Winmain(std::string directory);
	
protected:
	std::string googlemap(float latitude, float longitude, int zoom_lvl,
			int width_pixel, int height_pixel, std::string additional="");
	std::string googlemap(std::initializer_list<std::pair<float, float>> places);

private:
	std::map<std::string, int> directories;
	std::vector<std::map<std::string, int>> photoes;
};
