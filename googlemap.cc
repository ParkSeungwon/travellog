#include<vector>
#include<string>
#include<iostream>
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
	add(vbox1);
	vbox1.pack_start(*Glib::wrap(GTK_WIDGET(webview)));
	vbox1.add(scwin);
	scwin.add(vbox2);
	for(auto& a : thumbs) {
		vbox2.pack_start(a, Gtk::PACK_SHRINK);
		auto pa = a.first_gps();
		if(pa.first != 0 || pa.second != 0) daily_gps.push_back(pa);
	}
	set_map(daily_gps);
	set_default_size(1000, 1000);
	show_all_children();
}

void Winmain::set_map(vector<pair<float, float>> pl)
{
	webkit_web_view_load_html(webview, googlemap(pl).c_str(), "");
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

