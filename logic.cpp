#include<iostream>
#include<string>
#include<vector>
#include<limits>
using namespace std;

const int wolf=1;
const int villager=2;
const int witch=3;
const int guard=4;

struct Player
{
	string name;
	int role;
	bool alive;
};

void Playerinput(vector<Player>& pl)	//pl is the name of the vector, the list
{
	int n;
	cout<<"Number of players : ";
	cin>>n;
	cin.ignore();
	for(int i=0;i<n;i++)
	{
		Player p;	// Player is the data type, p is the variable's name (in the pl)
		cout<<"Name of Player "<<i+1<<": ";
		getline(cin,p.name);
		p.alive=true;
		pl.push_back(p);
	}
	cout<<"//wolf press 1\n"<<"villager press 2\n"<<"witch press 3\n"<<"guard press 4//\n\n";
	for(int i=0;i<n;i++)
	{
		Player p;
		cout<<"role of the player "<<i+1<<" is: ";
		cin>>pl[i].role;
	}
}

void PrintPlayer(const vector<Player>& pl)	//const for read only
{
	string rolename;
	for(int i=0;i<pl.size();i++)
	{
		switch(pl[i].role)
		{
			default: rolename="none";break;
			case 1: rolename="wolf";break;
			case 2: rolename="villager";break;
			case 3: rolename="witch";break;
			case 4: rolename="guard";break;
		}
		if(pl[i].alive==true)
		{
			cout<<"Player "<<pl[i].name<<" "<<" with the role "<<rolename<<" is still alive"<<endl;
		}
		else
		{
			cout<<"Player "<<pl[i].name<<" "<<" with the role "<<rolename<<" is dead "<<endl;
		}
	}
}

string Checkwin(const vector<Player>& pl)
{
	int a=0;
	int b=0;
	for(int i=0;i<(int)pl.size();i++)
	{
		if(pl[i].role==1 && pl[i].alive==true) a++;
		if(pl[i].role!=1 && pl[i].alive==true) b++;
	}
	if (a==0)
	{
		return "danlangthang";
	}
	else
	{
		if(a>b||a==b)
		{
			return "soithang";
		}
		else
		{
			return "danlangthang";
		}
	}
}

struct Rolesum
{
	int wolf=0;
	int villager=0;
	int witch=0;
	int guard=0;
};

Rolesum count(const vector<Player>& pl)
{
	Rolesum s;
	for(int i=0;i<(int)pl.size();i++)
	{
		switch(pl[i].role)
		{
			case wolf: s.wolf ++; break;
			case villager: s.villager ++; break;
			case witch: s.witch ++; break;
			case guard: s.guard ++; break;
		}
	}
	return s;
}

vector<int> listalive(const vector<Player>& pl, int roleCode)
{
	vector<int> idx;
	for(int i=0;i<(int)pl.size();i++)
	{
		if(pl[i].alive && pl[i].role == roleCode)
		{
			idx.push_back(i);
		}
	}
	return idx;
}

bool checkalive(const vector<Player>& pl, int roleCode)
{
	return !listalive(pl,roleCode).empty();
}

struct Nightstate
{
	int wolfTarget=-1;
	int guardTarget=-1;
	bool witchSave= false;
};

int choosealive(const vector<Player>& pl, const string& prompt)
{
	while(true)
	{
		cout<<endl<<prompt<<endl;
		for(int i=0;i<(int)pl.size();i++)
		{
			if(pl[i].alive)
			{
				cout<<i+1<<". "<<pl[i].name<<endl;
			}
		}
		cout<<"choose number :";
		int pick;
		cin>>pick;
		int idx= pick-1;
		if( idx>=0 && idx<(int)pl.size() && pl[idx].alive)
		{
			return idx;
		}
		"invalid choice, try again";
	}
}

Nightstate Nightphase(const vector<Player>& pl)
{
	Nightstate st;
	if(checkalive(pl,wolf))
	{
		do
    	{
       		st.wolfTarget=choosealive(pl, "Wolf: choose someone to kill");
    		if(pl[st.wolfTarget].role==wolf)
            cout<<"Invalid: wolf cannot kill wolf. Choose again.\n";
   		}
    	while (pl[st.wolfTarget].role == wolf);
	}
	return st;
}

void NightResult(vector<Player>& pl, const Nightstate& st)
{
    if(st.wolfTarget!=-1)
    {
        pl[st.wolfTarget].alive=false;
    }
}

int main()
{
	vector<Player> pl;
	Playerinput(pl);
	Nightstate st = Nightphase(pl);
	cout << "\nWolf target index: " << st.wolfTarget << "\n";
	if(st.wolfTarget != -1) cout << "Wolf chose: " << pl[st.wolfTarget].name << "\n";

	NightResult(pl, st);
	cout << "\nSo wolf con song: " << listalive(pl, wolf).size()<<endl;
 	
	PrintPlayer(pl);
	cout<<"tinh huong win la "<<Checkwin(pl);

}



 