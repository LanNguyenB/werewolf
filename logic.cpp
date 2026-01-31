#include<iostream>
#include<string>
#include<vector>
#include<limits>
using namespace std;

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
	cout<<"//wolf press 1\n"<<"villager press 2\n"<<"witch press 3\n"<<"guard press 4//\n";
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
	for(int i=0;i<pl.size();i++)
	{
		if(pl[i].role==1 && pl[i+1].alive==true) a++;
		if(pl[i].role!=1 && pl[i+1].alive==true) b++;
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
int main()
{
	vector<Player> pl;
	Playerinput(pl);
	PrintPlayer(pl);
	cout<<"tinh huong win la "<<Checkwin(pl);
	//While(Checkwin(pl)==0)
	{
		//Using for coding the Night and Day
	};
}



 