// region.h
#ifndef REGION_H
#define REGION_H

namespace pokfactory
{

    /*Represent a region in the Pokemon game world*/
    class Region 
    {
    public:
        Region(int number,RegionFactory* factory);
        void bind_adjacencies(const std::map<int,std::map<int,Region*> >& adjmap);
    private:
        RegionFactory* factory;
        Size bounds;
        Region* adjacencies[4];
        int number;
    };

} // pokfactory

#endif
