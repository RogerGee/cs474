// region.cpp
#include "region.h"
#include <stdexcept>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;
using namespace pokfactory;

//helper
string tolower(string input)
{
	string output = "";
	for (size_t i = 0;i < input.size();++i)
        output += tolower(input[i]);
	return output;
}

// Region

Region::Region(int innumber,string n,
	RegionFactory* infactory,const Size& inbounds,bool p)
    : number(innumber), name(n), factory(infactory), bounds(inbounds), pc(p)
{

}
Region::~Region()
{
    delete factory;
}

// Gameworld

Gameworld::Gameworld(Region* a)
    : curreg(a), battle(false)
{
    PartyFactory factory;
	add_region(a, NULL, NULL, NULL, NULL);
    for (int i = 0;i < 6;++i) {
        party[i] = factory.create_pokemon();
    }
}
Gameworld::~Gameworld()
{
    for (auto thing : regions)
        delete thing;
    for (auto pok : party)
        delete pok;
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
void Gameworld::process(string input)
{
	input = tolower(input);
    if (battle)
        process_fighting(input);
    else
        process_idle(input);
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
void Gameworld::process_idle(string input)
{
	stringstream ss(input);
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
					cout << "There is nothing to the " << input << '\n';
				else
					cout << "To the " << input << " is " << 
						adjlist[curreg->get_number()][d]->get_name() << '\n';
				return;
			}
		}
		else
		{
			cout << "You are in " << curreg->get_name() << '\n';
			if (curreg->has_pc())
				cout << "There is a pokemon center here\n";
			return;
		}
	}
	else if (input == "walk")
	{
		cout << "You walk around aimlessly, ";
		Pokemon* p = curreg->encounter();
		if (p) {
			cout << "and encounter a wild " << p->get_name() << " (level "
				<< p->get_level() << ")!!!\n";
            battle = true;
            enemy = p;
        }
		else
			cout << "but end up right back where you started...\n";
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
				cout << "There is nothing to the " << input << '\n';
			else
			{
				curreg = adjlist[curreg->get_number()][d];
				cout << "You travel " << input << " to "
					<< curreg->get_name() << '\n';
			}
			return;
		}
	}
    else if (input == "party")
	{
        int index;
        ss >> index;
        index -= 1;
        if (!ss.fail())
		{
            if (index >= 6 || index < 0)
                cout << "bad party slot number, fool!\n";
            else
                cout << *party[index] << endl;
        }
        else
		{
            for (auto p : party)
                cout << p->get_name() << " level " << p->get_level() << endl;
        }
        return;
    }
	else if (input == "visit")
	{
		if (curreg->has_pc())
		{
			cout << "Let me take your pokemon for a moment...\n";
			this_thread::sleep_for(chrono::seconds(2));
			for (auto p : party)
				p->heal();
			cout << "All healed! Please come again soon!\n";
		}
		else
		{
			cout << "There is no pokemon center here.\n";
		}
		return;
	}
	else if (input == "switch")
	{
		ss >> input;
		if (!ss.fail()) {
			Pokemon** switchto = NULL;
			for (auto& p : party)
				if (tolower(p->get_name()) == input)
					switchto = &p;
			if (switchto)
			{
				if ((*switchto)->fainted())
				{
					cout << (*switchto)->get_name() << " is fainted\n";
					return;
				}
				Pokemon* p = party[0];
				party[0] = *switchto;
				*switchto = p;
				cout << "Switched to " << party[0]->get_name() << '\n';
			}
			else
				cout << "No " << input << " in party\n";
		}
		else
			cout << "Please specify a party member\n";
		return;
	}
	cout << "I don't know what that means cuz me am no smrt.\n"
		<< "Please try again.\n";
}
void Gameworld::process_fighting(string input)
{
    Pokemon* fighter = party[0];
	stringstream ss(input);
	ss >> input;
	if (input == "look")
	{
		cout << *enemy << '\n';
		return;
	}
    else if (input == "use")
	{
		if (fighter->fainted())
		{
			cout << fighter->get_name() << " has fainted, switch pokemon\n";
			return;
		}
		string mv;
        ss >> mv;
        if (ss.fail()) {
            cout << "please specify a move\n";
            return;
        }

        int mno = fighter->select_move(mv);
        if (mno == -1) {
            cout << "bad move!\n";
            return;
        }

        if (enemy->attacked(*fighter,mno,cout))
		{
            cout << "The battle is over.\n";
            battle = false;
            delete enemy;
        }
		else if (fighter->attacked(*enemy,enemy->random_move(),cout))
		{
			cout << fighter->get_name() << " has fainted!\n";
			bool alive = false;
			for (auto p : party)
				alive |= !p->fainted();
			if (!alive)
				cout << "You blacked out!\nPlease play again\n";
		}
        return;
    }
	else if (input == "party")
	{
		int index;
        ss >> index;
        index -= 1;
        if (!ss.fail())
		{
            if (index >= 6 || index < 0)
                cout << "bad party slot number, fool!\n";
            else
                cout << *party[index] << endl;
        }
        else
		{
            for (auto p : party)
                cout << p->get_name() << " level " << p->get_level() << endl;
        }
        return;
	}
	else if (input == "switch")
	{
		ss >> input;
		if (!ss.fail()) {
			Pokemon** switchto = NULL;
			for (auto& p : party)
				if (tolower(p->get_name()) == input)
					switchto = &p;
			if (switchto)
			{
				if ((*switchto)->fainted())
				{
					cout << (*switchto)->get_name() << " is fainted\n";
					return;
				}
				party[0] = *switchto;
				*switchto = fighter;
				cout << "Switched to " << party[0]->get_name() << '\n';
				if (party[0]->attacked(*enemy,0,cout))
				{
					cout << fighter->get_name() << " has fainted!\n";
					bool alive = false;
					for (auto p : party)
						alive |= !p->fainted();
					if (!alive)
						cout << "You blacked out!\nPlease play again\n";
				}
			}
			else
				cout << "No " << input << " in party\n";
		}
		else
			cout << "Please specify a party member\n";
		return;
	}
	cout << "I don't know what that means cuz me am no smrt.\n"
		<< "Please try again.\n";
}
