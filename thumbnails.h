#include<gtkmm.h>

class MyImage : public Gtk::Image
{
public:
};

class Thumbnails : public Gtk::HBox
{
public:
	Thumbnails(std::string directory);

protected:
	Gtk::HBox hbox1, hbox2;
	Gtk::ScrolledWindow scwin;
	std::vector<Gtk::Image> images;
	Gtk::Button bt;

private:
	void sstm(std::string command);
};
