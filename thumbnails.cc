#include<gtkmm.h>
#include<string>
#include<vector>
#include<functional>
#include"thumbnails.h"
#include"interface.h"
using namespace std;

std::map<std::string, int> getdir(string dir);
extern Interface* interface;

void Thumbnails::on_bt_click(vector<pair<float, float>> g)
{
	interface->set_map(g);//cannot use member variable as g
}

Thumbnails::Thumbnails(string dir) 
{
	bt.set_label(vlabel(dir));
	auto files = getdir(dir);
	files.erase("thumbnails");
	int i=0;
	for(auto& a : files) {
		string s = psstm("exiv2 -pc " + dir + '/' + a.first); 
		auto gp = gps_coordinate(s);
		if(gp.first != 0 && gp.second != 0) gps.push_back(gp);
		s = a.first.substr(0, a.first.find_last_of('.'));
		ims.push_back(Gtk::Image{dir + "/thumbnails/" + s + "-thumb.jpg"});
		bts.push_back(Gtk::Button());
		bts.back().set_image(ims.back());
		bts.back().signal_clicked().connect(bind(&Thumbnails::sstm, this, 
					"shotwell " + dir + '/' + a.first +'&'));
	}
	bt.signal_clicked().connect(bind(&Thumbnails::on_bt_click, this, gps));
	pack_all();
}

void Thumbnails::pack_all()
{
	set_size_request(900, 140);
	add(hbox1);
	hbox1.pack_start(bt, Gtk::PACK_SHRINK);
	hbox1.pack_start(scwin);
	scwin.add(hbox2);
	for(auto& a : bts) hbox2.pack_start(a, Gtk::PACK_SHRINK);
}

void Thumbnails::sstm(string command) const
{
	system(command.data());
}

string Thumbnails::psstm(string command) const
{
	char buf[100];
	FILE* f = popen(command.c_str(), "r");
	fgets(buf, sizeof(buf), f);
	pclose(f);
	return buf;
}

string Thumbnails::vlabel(string dir) const
{
	string s = dir.substr(dir.find_last_of('/') + 1);
	s.erase(0, 2);
	string vert;
	for(auto& a : s) {
		if(a != '-') {
			vert += a; 
			vert += '\n';
		}
	}
	vert.pop_back();
	return vert;
}

pair<float, float> Thumbnails::gps_coordinate(string s) const
{
	int sp = s.find(' ');
	float lat=0, lng=0;
	try {
		lat = stof(s.substr(0, sp));
		lng = stof(s.substr(sp+1));
	} catch(...) {
		//cout << "no gps data in " << s;
	}
	return {lat, lng};
}

pair<float, float> Thumbnails::first_gps()
{
	return gps.empty() ? pair<float, float>{0,0} : gps[0];
}
