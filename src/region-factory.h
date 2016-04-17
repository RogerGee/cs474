// region-factory.h
#ifndef REGION_FACTORY_H
#define REGION_FACTORY_H
#include "pokemon.h"

namespace pokfactory
{

    /*Represents the interface for a region factory*/
    class RegionFactory 
    {
    public:
        Pokemon* create_pokemon();
    protected:
        RegionFactory(double encounterRate);
        double flip_coin();
    private:
        virtual Pokemon* create_pokemon_impl() = 0;
        double encounterRate;
    };

    /*Factory for forest regions*/
    class ForestRegionFactory : RegionFactory 
    {
    private:
        virtual Pokemon* create_pokemon_impl();
    };

    /*Factory for sea Factory for sea regions*/
    class SeaRegionFactory : RegionFactory 
    {
    private:
        virtual Pokemon* create_pokemon_impl();
    };

    /*Region for grassland regions*/
    class GrasslandRegionFactory : RegionFactory 
    {
    private:
        virtual Pokemon* create_pokemon_impl();
    };

    /*Factory for cave regions*/
    class CaveRegionFactory : RegionFactory 
    {
    private:
        virtual Pokemon* create_pokemon_impl();
    };

    /*Factory for urban regions*/
    class UrbanRegionFactory : RegionFactory 
    {
    private:
        virtual Pokemon* create_pokemon_impl();
    };

} // pokfactory

#endif
