/* Factory subclasses
const int ForestRegionFactory::numPokes = 30;
const int ForestRegionFactory::pokes[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150};
ForestRegionFactory::ForestRegionFactory()
    : RegionFactory(0.25)
{
}
Pokemon* ForestRegionFactory::create_pokemon_impl()
{

    return make_pokemon(choosePoke(pokes,numPokes),rand() % 2000+1);
}*/

//There's only one type of pokemon in each region,
//enter the region type and the new pokemon pointer you want to be populated
Pokemon* ugly(string region_type, Pokemon* new_pokemon)
{
	if (region_type == "ForestRegion")
	{
		new_pokemon.species = 1;
		new_pokemon.curHP = 45;
		//new_pokemon.stats = 
	}
	else if (region_type == "SeaRegion")
	{
		new_pokemon.species = 7;
		new_pokemon.curHP = 44;
		//new_pokemon.stats = 
	}
	else if (region_type == "GrasslandRegion")
	{
		new_pokemon.species = 16;
		new_pokemon.curHP = 83;
		//new_pokemon.stats = 
	}
	else if (region_type == "CaveRegion")
	{
		new_pokemon.species = 41;
		new_pokemon.curHP = 40;
		//new_pokemon.stats = 
	}
	else if (region_type == "UrbanRegion")
	{
		new_pokemon.species = 150;
		new_pokemon.curHP = 106;
		//new_pokemon.stats = 
	}
	
	new_pokemon.experience = 0;
	new_pokemon.level = 1;
	
	return new_pokemon;
}