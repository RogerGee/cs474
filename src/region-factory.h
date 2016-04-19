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
        virtual ~RegionFactory();
    protected:
        RegionFactory(double encounterRateIn);
		Pokemon* make_pokemon(int species,int exp);
        static int choosePoke(const int* pokes,int numPokes);
    private:
        virtual Pokemon* create_pokemon_impl() = 0;
        double encounterRate;
    };

    /*Factory for forest regions*/
    class ForestRegionFactory : public RegionFactory 
    {
    public:
        ForestRegionFactory();
    private:
        virtual Pokemon* create_pokemon_impl();
        static const int pokes[];
        static const int numPokes;

    };

    /*Factory for sea Factory for sea regions*/
    class SeaRegionFactory : public RegionFactory 
    {
    public:
        SeaRegionFactory();
    private:
        virtual Pokemon* create_pokemon_impl();
        static const int pokes[];
        static const int numPokes;
    };

    /*Region for grassland regions*/
    class GrasslandRegionFactory : public RegionFactory 
    {
    public:
        GrasslandRegionFactory();
    private:
        virtual Pokemon* create_pokemon_impl();
        static const int pokes[];
        static const int numPokes;
    };

    /*Factory for cave regions*/
    class CaveRegionFactory : public RegionFactory 
    {
    public:
        CaveRegionFactory();
    private:
        virtual Pokemon* create_pokemon_impl();
        static const int pokes[];
        static const int numPokes;
    };

    /*Factory for urban regions*/
    class UrbanRegionFactory : public RegionFactory 
    {
    public:
        UrbanRegionFactory();
    private:
        virtual Pokemon* create_pokemon_impl();
        static const int pokes[];
        static const int numPokes;
    };

    class PartyFactory : public RegionFactory
    {
    public:
        PartyFactory();
    private:
        virtual Pokemon* create_pokemon_impl();
    };

} // pokfactory

#endif
