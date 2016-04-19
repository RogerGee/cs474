// region.cpp
#include "region.h"
#include <stdexcept>
#include <sstream>
using namespace std;
using namespace pokfactory;

// Region

Region::Region(int innumber,std::string n,
	RegionFactory* infactory,const Size& inbounds)
    : number(innumber), name(n), factory(infactory), bounds(inbounds)
{

}
Region::~Region()
{
    delete factory;
}

// Gameworld

Gameworld::Gameworld(Region* a)
    : curreg(a)
{
	add_region(a, NULL, NULL, NULL, NULL);
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
void Gameworld::process(std::string input)
{
	std::stringstream ss(input);
	ss >> input;
	if (input == "look")
	{
		ss >> input;
		if (!ss.fail())
		{
			if (input == "everywhere")
			{
				process("look");
				process("look north");
				process("look east");
				process("look south");
				process("look west");
				return;
			}
			dir d = none;
			if (input == "north")
				d = north;
			else if (input == "east")
				d = east;
			else if (input == "south")
				d = south;
			else if (input == "west")
				d = west;
			if (d != none)
			{
				if (!adjlist[curreg->get_number()][d])
					std::cout << "There is nothing to the " << input << '\n';
				else
					std::cout << "To the " << input << " is " << 
						adjlist[curreg->get_number()][d]->get_name() << '\n';
				return;
			}
		}
		else
		{
			std::cout << "You are in " << curreg->get_name() << '\n';
			return;
		}
	}
	else if (input == "walk")
	{
		std::cout << "You walk around aimlessly, ";
		Pokemon* p = curreg->encounter();
		if (p)
			std::cout << "and encounter a wild " << *p << "!!!\n";
		else
			std::cout << "but end up right back where you started...\n";
		return;
	}
	else if (input == "go")
	{
		ss >> input;
		dir d = none;
		if (input == "north")
			d = north;
		else if (input == "east")
			d = east;
		else if (input == "south")
			d = south;
		else if (input == "west")
			d = west;
		if (d != none)
		{
			if (!adjlist[curreg->get_number()][d])
				std::cout << "There is nothing to the " << input << '\n';
			else
			{
				curreg = adjlist[curreg->get_number()][d];
				std::cout << "You travel " << input << " to "
					<< curreg->get_name() << '\n';
			}
			return;
		}
	}
	std::cout << "I don't know what that means cuz me am no smrt.\n"
		<< "Please try again.\n";
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
