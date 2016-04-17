// pokemon.h
#ifndef POKEMON_H
#define POKEMON_H
#include <fstream>

namespace pokfactory
{

    /*Represents an object created by the region factories*/
    class Pokemon 
    {
    public:
        void write(std::ostream& fout);
        void attack(Pokemon& enemy,int move);
    private:
        Pokemon(int species,int exp);
        Pokemon(int species,std::istream& fin);
        int species;
        int experience;
        int ivs[5];
        int evs[5];
        int moves[4];
        int pp[4];
        int curHp;
    };

} // pokfactory

#endif
