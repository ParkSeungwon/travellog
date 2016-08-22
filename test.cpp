#include"thumbnails.h"
using namespace std;

int main(int c, char** v)
{
	auto app = Gtk::Application::create(c, v);
	Gtk::Window win;
	Thumbnails th{"/home/zezeon/Dropbox/Photos/6month/2014-08-19"};
	win.add(th);
	win.show_all_children();
	app->run(win);
}
