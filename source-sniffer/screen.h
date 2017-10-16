#include <assert.h>
#include <stdio.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>

class GetScreen
{
	public:
	Display *disp;
	Window root;
	cairo_surface_t *surface;
	int scr;
	bool no_cap;

	void setup(char * _display)
	{
		no_cap = true;
   		disp = XOpenDisplay( _display );
		if( disp == NULL )
		{
			cerr << "Display: " << _display << " not found!" << endl;
			no_cap = false;
		}
    		scr = DefaultScreen(disp);
		root = DefaultRootWindow(disp);
	}

	void capture()
	{
		while(no_cap)
		{
			//cout << "capture screen" << endl;
			milliseconds ms = duration_cast< milliseconds >( system_clock::now().time_since_epoch() );
		        time_t t = ms.count();
		        string path = LOG;
			path+="image_"+to_string(t)+".png";
			surface = cairo_xlib_surface_create(disp, root, DefaultVisual(disp, scr),
                                                    DisplayWidth(disp, scr), 
                                                    DisplayHeight(disp, scr));
			cairo_surface_write_to_png( surface, path.c_str() );
			sleep(1);
		}
	}

	void exit()
	{
		cairo_surface_destroy(surface);
	}
};
