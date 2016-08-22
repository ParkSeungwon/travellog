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
	Gtk::Button bt;

private:
	void sstm(std::string command);
};
