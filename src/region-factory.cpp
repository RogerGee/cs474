// region-factory.cpp
#include "region-factory.h"
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
double RegionFactory::flip_coin()
{
    return 0.5;
}

// Factory subclasses

ForestRegionFactory::ForestRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* ForestRegionFactory::create_pokemon_impl()
{

    return NULL;
}

SeaRegionFactory::SeaRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* SeaRegionFactory::create_pokemon_impl()
{
    return NULL;
}

GrasslandRegionFactory::GrasslandRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* GrasslandRegionFactory::create_pokemon_impl()
{
    return NULL;
}

CaveRegionFactory::CaveRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* CaveRegionFactory::create_pokemon_impl()
{
    return NULL;
}

UrbanRegionFactory::UrbanRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* UrbanRegionFactory::create_pokemon_impl()
{
    return NULL;
}