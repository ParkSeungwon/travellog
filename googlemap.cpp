#include"googlemap.h"
using namespace std;

int main(int c, char** v)
{
	int i=0;
	const char* p;
	string s = Thumbnails::psstm("pwd");
	s.pop_back();//remove new line character
	if(c<2) p = s.c_str();
	else p = v[1];
	auto app = Gtk::Application::create(i, v, "");
	Winmain window(p);
	app->run(window);
}

