#include<gtkmm.h>
using namespace std;

int main(int c, char** v)
{
	auto app = Gtk::Application::create(c, v);
	Gtk::Window win;
	Gtk::Image im("/home/zezeon/Dropbox/Photos/6month/2014-08-19/thumbnails/06-26-52-thumb.jpg");
	Gtk::Button bt;
	bt.set_image(im);
	win.add(bt);
	win.show_all_children();
	app->run(win);
}
