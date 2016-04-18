// region.cpp
#include "region.h"
#include <stdexcept>
using namespace std;
using namespace pokfactory;

// Region

Region::Region(int innumber,RegionFactory* infactory,const Size& inbounds)
    : number(innumber), factory(infactory), bounds(inbounds)
{

}
Region::~Region()
{
    delete factory;
}

// Gameworld

Gameworld::Gameworld()
    : curreg(1)
{

}
Gameworld::~Gameworld()
{
    for (auto thing : regions)
        delete thing;
}
void Gameworld::add_region(Region* region,Region* n,Region* s,Region* e,Region* w)
{
    int num = region->get_number();
    if (!adjlist.count(num)) {
        regions.push_back(region);
        for (int i = 0;i < 4;++i)
            adjlist[num][i] = NULL;
    }

    if (n && update_adjacency(num,north,n)) {
        add_region(n,NULL,region,
            lk(num,east,north),
            lk(num,west,north));
    }
    if (s && update_adjacency(num,south,s)) {
        add_region(s,region,NULL,
            lk(num,east,south),
            lk(num,west,south));
    }
    if (e && update_adjacency(num,east,e)) {
        add_region(e,
            lk(num,north,east),
            lk(num,south,east),
            NULL,region);
    }
    if (w && update_adjacency(num,west,w)) {
        add_region(w,
            lk(num,north,west),
            lk(num,south,west),
            region,NULL);
    }
}
Region* Gameworld::lk(int n,int d1,int d2)
{
    try {
        Region* link = adjlist.at(n)[d1];
        if (link != NULL)
            return adjlist.at(link->get_number())[d2];
    } catch (out_of_range e) {}
    return NULL;
}
bool Gameworld::update_adjacency(int i,int j,Region* r)
{
    Region* other = adjlist[i][j];
    if (other != NULL && other != r)
        throw runtime_error("Gameworld: bad adjacencies");
    adjlist[i][j] = r;
    return other == NULL;
}
