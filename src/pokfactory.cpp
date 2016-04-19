// pokfactory.cpp
#include <iostream>
#include <ctime>
#include "region.h"
using namespace std;
using namespace pokfactory;

int main(int argc,const char* argv[])
{
    srand(time(0));

    Size sz = {20,20};
    Region* a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
    a = new Region(1,"Floating Forest",new ForestRegionFactory,sz);
    b = new Region(2,"Soaked Sea",new SeaRegionFactory,sz);
    c = new Region(3,"Green Grassland",new GrasslandRegionFactory,sz);
    d = new Region(4,"Cruel Cavern",new CaveRegionFactory,sz);
    e = new Region(5,"Cirridale City",new UrbanRegionFactory,sz);
    f = new Region(6,"Frozen Forest",new ForestRegionFactory,sz);
    g = new Region(7,"Ghastly Grassland",new GrasslandRegionFactory,sz);
    h = new Region(8,"Template Town",new UrbanRegionFactory,sz);
    i = new Region(9,"Treacherous Tunnel",new CaveRegionFactory,sz);
    j = new Region(10,"Orca Ocean",new SeaRegionFactory,sz);
	
	Gameworld world(a);

    world.add_region(a,b,c,d,e);
    world.add_region(c,NULL,f,g,NULL);
    world.add_region(f,NULL,h,i,NULL);
    world.add_region(b,NULL,NULL,NULL,j);
	
	//process input in loop
	string input;
	while(true)
	{
		getline(cin, input);
		if (input == "quit")
			break;
		world.process(input);
	}
}
