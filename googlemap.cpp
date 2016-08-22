#include"googlemap.h"

int main(int c, char** v)
{
	int i=0;
	if(c<2) return 0;
	auto app = Gtk::Application::create(i, v, "");
	Winmain window(v[1]);
	extern Interface* interface;
	interface = &window;
	app->run(window);
}

