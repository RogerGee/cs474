// pokfactory.cpp
#include <iostream>
#include "region.h"
using namespace std;
using namespace pokfactory;

int main(int argc,const char* argv[])
{
    Gameworld world;

    Size sz = {20,20};
    Region* a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
    a = new Region(1,new ForestRegionFactory,sz);
    b = new Region(2,new SeaRegionFactory,sz);
    c = new Region(3,new GrasslandRegionFactory,sz);
    d = new Region(4,new CaveRegionFactory,sz);
    e = new Region(5,new UrbanRegionFactory,sz);
    f = new Region(6,new ForestRegionFactory,sz);
    g = new Region(7,new GrasslandRegionFactory,sz);
    h = new Region(8,new UrbanRegionFactory,sz);
    i = new Region(9,new CaveRegionFactory,sz);
    j = new Region(10,new SeaRegionFactory,sz);

    world.add_region(a,b,c,d,e);
    world.add_region(c,NULL,f,g,NULL);
    world.add_region(f,NULL,h,i,NULL);
    world.add_region(b,NULL,NULL,NULL,j);
}
