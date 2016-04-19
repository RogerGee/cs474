// pokemon.h
#ifndef POKEMON_H
#define POKEMON_H
#include <ostream>
#include <fstream>

namespace pokfactory
{

    /* represents the base Pokemon info per species */
    struct PokemonEntry
    {
        const char* name;
        int baseStats[6];
    };

    /* represents a move; we keep things simple and just let the move have a
       base power */
    struct PokemonMove
    {
        const char* name;
        int basePower;
        bool special;
    };

    /* enumerate the pokemon stat kinds */
    enum PokemonStat
    {
        HP,
        Attack,
        Defense,
        SpcAttack,
        SpcDefense,
        Speed
    };

    /*Represents an object created by the region factories*/
    class Pokemon
    {
        friend class RegionFactory;
        friend std::ostream& operator <<(std::ostream&,const Pokemon&);
    public:
        const char* get_name() const;

        void write(std::ostream& fout);
        bool attacked(Pokemon& enemy,int move,std::ostream& output); // enemy uses move on us
        int select_move(std::string name);
		void heal() {curHP = stats[HP];}
    private:
        Pokemon(int index,int exp);
        Pokemon(int index,std::istream& fin);

        int species;
        int experience;
        int ivs[6];
        int evs[6];
        int moves[4];
        int pp[4];
        int curHP;
        int level;
        int stats[6];

        void calc_stats();
    };

    std::ostream& operator <<(std::ostream&,const Pokemon&);

} // pokfactory

#endif
