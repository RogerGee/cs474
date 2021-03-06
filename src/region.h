// region.h
#ifndef REGION_H
#define REGION_H
#include <map>
#include <array>
#include <vector>
#include <iostream>
#include "region-factory.h"

namespace pokfactory
{
    enum dir
    {
        none = -1,
		north,
        south,
        east,
        west
    };

    /* represents a 2d size */
    struct Size
    {
        int width;
        int height;
    };

    /*Represent a region in the Pokemon game world*/
    class Region
    {
    public:
        Region(int innumber,std::string n,
			RegionFactory* infactory,const Size& inbounds,bool p=false);
        ~Region();

        int get_number() const
        { return number; }
		std::string get_name() const
		{ return name; }
		bool has_pc()
		{ return pc; }
		
		Pokemon* encounter() {return factory->create_pokemon();}
    private:
        int number;
		std::string name;
        RegionFactory* factory;
        Size bounds;
		bool pc;
    };

    class Gameworld
    {
    public:
        typedef std::map<int,std::array<Region*,4> > adj_list_t;

        Gameworld(Region* a);
        ~Gameworld();

        void add_region(Region* region,Region* n = NULL,
            Region* s = NULL,Region* e = NULL,Region* w = NULL);
		
		void process(std::string input);
		
    private:
        Region* curreg;
        std::vector<Region*> regions;
        adj_list_t adjlist;
        Pokemon* party[6];

        bool battle;
        Pokemon* enemy;

        Region* lk(int,int,int);
        bool update_adjacency(int i,int j,Region* r);
        void process_idle(std::string input);
        void process_fighting(std::string input);
    };

} // pokfactory

#endif
