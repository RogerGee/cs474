// region-factory.cpp
#include "region-factory.h"
#include <cstdlib>
using namespace pokfactory;

// RegionFactory
Pokemon* RegionFactory::create_pokemon()
{
    // TODO: handle encounters

    return create_pokemon_impl();
}
RegionFactory::RegionFactory(double encounterRateIn)
    : encounterRate(encounterRateIn)
{
}
RegionFactory::~RegionFactory()
{
}
Pokemon* RegionFactory::make_pokemon(int species,int exp)
{
	return new Pokemon(species, exp);
}
/*static*/int RegionFactory::choosePoke(const int* pokes,int numPokes)
{
    int x;    
    x = pokes[(rand() % numPokes)];
    return(x);
}


// Factory subclasses
const int ForestRegionFactory::numPokes = 30;
const int ForestRegionFactory::pokes[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150};
ForestRegionFactory::ForestRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* ForestRegionFactory::create_pokemon_impl()
{

    return make_pokemon(choosePoke(pokes,numPokes),rand() % 2000+1);
}

const int SeaRegionFactory::numPokes = 30;
const int SeaRegionFactory::pokes[] = {1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71, 76, 81, 86, 91, 96, 101, 106, 111, 116, 121, 126, 131, 136, 141, 146};
SeaRegionFactory::SeaRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* SeaRegionFactory::create_pokemon_impl()
{
    return make_pokemon(choosePoke(pokes,numPokes),rand() % 2000+1);
}

const int GrasslandRegionFactory::pokes[] = {2, 7, 12, 17, 22, 27, 32, 37, 42, 47, 52, 57, 62, 67, 72, 77, 82, 87, 92, 97, 102, 107, 112, 117, 122, 127, 132, 137, 142, 147};
const int GrasslandRegionFactory::numPokes = 30;
GrasslandRegionFactory::GrasslandRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* GrasslandRegionFactory::create_pokemon_impl()
{

    return make_pokemon(choosePoke(pokes,numPokes),rand() % 2000+1);
}

const int CaveRegionFactory::numPokes = 30;
const int CaveRegionFactory::pokes[] = {3, 8, 13, 18, 23, 28, 33, 38, 43, 48, 53, 58, 63, 68, 73, 78, 83, 88, 93, 98, 103, 108, 113, 118, 123, 128, 133, 138, 143, 148};
CaveRegionFactory::CaveRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* CaveRegionFactory::create_pokemon_impl()
{

    return make_pokemon(choosePoke(pokes,numPokes),rand() % 2000+1);
}

const int UrbanRegionFactory::numPokes = 31;
const int UrbanRegionFactory::pokes[] = {4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 54, 59, 64, 69, 74, 79, 84, 89, 94, 99, 104, 109, 114, 119, 124, 129, 134, 139, 144, 149};
UrbanRegionFactory::UrbanRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* UrbanRegionFactory::create_pokemon_impl()
{

    return make_pokemon(choosePoke(pokes,numPokes),rand() % 2000+1);
}

PartyFactory::PartyFactory()
    : RegionFactory(1.0)
{
}
Pokemon* PartyFactory::create_pokemon_impl()
{
    return make_pokemon(rand() % 151 + 1,rand() % 2000 + 1);
}
