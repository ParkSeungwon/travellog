#include"googlemap.h"
using namespace std;

Interface* interface;
std::map<string, int> getdir(string dir);

Winmain::Winmain(string dir) 
{
	interface = this;
	directories = getdir(dir);
	for(auto& a : directories) thumbs.push_back(Thumbnails(dir + '/' + a.first));
	webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
	auto widget_now = Glib::wrap(GTK_WIDGET(webview));
	add(vbox1);
	widget_now->set_size_request(-1, 500);
	vbox1.pack_start(hbox, Gtk::PACK_SHRINK);
	bt.set_label(vlabel(dir));
	hbox.pack_start(bt, Gtk::PACK_SHRINK);
	hbox.pack_start(*widget_now);
	vbox1.add(scwin);
	scwin.add(vbox2);
	for(auto& a : thumbs) {
		vbox2.pack_start(a, Gtk::PACK_SHRINK);
		auto pa = a.first_gps();
		if(pa.first != 0 || pa.second != 0) daily_gps.push_back(pa);
	}
	set_map(daily_gps);
	bt.signal_clicked().connect(bind(&Winmain::set_map, this, daily_gps));
	set_default_size(1000, 1000);
	show_all_children();
}

void Winmain::set_map(vector<pair<float, float>> pl)
{
	webkit_web_view_load_html(webview, googlemap(pl).c_str(), "");
}

string Winmain::vlabel(string dir) const
{
	if(dir.back() == '/') dir.pop_back();
	string s = dir.substr(dir.find_last_of('/') + 1);
	string vert;
	for(auto it = s.begin(); it != s.end();) {
		int n = multibyte(*it);
		for(int i=0; i<n; i++, it++)  vert += *it;
		vert += '\n';
	}
	vert.pop_back();
	return vert;
}

int Winmain::multibyte(char c) const
{//multibyte character check. return n byte.
	int r=1;
	if(c & 1<<7) for(int i=6; c & 1<<i && i>3; i--) r++;
	return r;
}

string Winmain::googlemap(vector<pair<float, float>> pts)
{
	string ad = "var trip = [];"
		"var marker = [];"
		"var bound = new google.maps.LatLngBounds();";
	for(auto& a : pts) {
		ad += "trip.push(new google.maps.LatLng(";
		ad += to_string(a.first) + ',' + to_string(a.second) + "));";
	}
	ad += "for(i=0; i<trip.length; i++) {"
		"marker.push(new google.maps.Marker({position:trip[i],}));"
		"bound.extend(trip[i]);"
		"marker[i].setMap(map);"
		"}"
		"var flightPath = new google.maps.Polyline({"
		"path:trip, strokeColor:'#0000FF', strokeOpacity:0.8, strokeWeight:2 });"
		"flightPath.setMap(map);"
		"map.fitBounds(bound);";
	return googlemap(0, 0, 12, 1000, 480, ad);
}

string Winmain::googlemap(float lt, float ln, int z, int w, int h, string ad)
{
	string rt = "<!DOCTYPE html> <html> <head>"
		"<script src='http://maps.googleapis.com/maps/api/js'></script>"
		"<script>function initialize() {var mapProp = {"
		"center:new google.maps.LatLng(";
	rt += to_string(lt) + ',' + to_string(ln) + "), zoom:" + to_string(z) + ',';
	rt += "mapTypeId:google.maps.MapTypeId.ROADMAP};"
		"var map=new google.maps.Map(document.getElementById('googleMap'),mapProp);";
	rt += ad + "}google.maps.event.addDomListener(window, 'load', initialize);"
		"</script> </head> <body> <div id='googleMap' style='width:100%;";
	rt += "height:" + to_string(h) + "px;'> </div></body></html>";
	return rt;
}

