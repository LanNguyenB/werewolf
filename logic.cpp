#include<iostream>
#include<string>
#include<vector>
#include<limits>
using namespace std;

const int wolf=1;	
const int villager=2;
const int witch=3;
const int guard=4;
const int seer=5;	//tien tri
const int cupid=6;
const int hunter=7;
const int idiot=8; 	//thằng đần

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
	cout<<"//wolf press 1\n"<<"villager press 2\n"<<"witch press 3\n"<<"guard press 4\n"<<"seer press 5\n"
	<<"cupid press 6\n"<<"hunter press 7\n"<<"idiot press 8//\n\n";
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
			case 5: rolename="seer";break;
			case 6: rolename="cupid";break;
			case 7: rolename="hunter";break;
			case 8: rolename="idiot";break;
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
		return "Villager win";
	}
	else
	{
		if(a>b||a==b)
		{
			return "Wolf win";
		}
		else
		{
			return "Villager win";
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
    bool witchSave=false;        // đêm nay có cứu không
    int witchPoisonTarget=-1;    // đêm nay có đầu độc ai không
};

struct Gamestate
{
    bool witchHasSave=true;   
    bool witchHasPoison=true;  
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
		cout<<"invalid choice, try again";
	}
}

bool hasNonWolfAlive(const vector<Player>& pl)
{
    for(int i=0;i<(int)pl.size();i++)
        if(pl[i].alive && pl[i].role!=wolf)
            return true;
    return false;
}

Nightstate Nightphase(const vector<Player>& pl, Gamestate& gs)
{
	Nightstate st;
	if(checkalive(pl,wolf) && hasNonWolfAlive(pl))
	{
		do
    	{
       		st.wolfTarget=choosealive(pl, "Wolf: choose someone to kill");
    		if(pl[st.wolfTarget].role==wolf)
            cout<<"Invalid: wolf cannot kill wolf. Choose again.\n";
   		}
    	while (pl[st.wolfTarget].role == wolf);
	}
	if(checkalive(pl, guard))
	{
    	int guardIndex=listalive(pl, guard)[0]; // v1 assume only 1 guard
        while (true)
        {
            st.guardTarget=choosealive(pl, "Guard: choose someone to protect");

            if(st.guardTarget==guardIndex)
            {
                cout<<"Invalid: guard cannot protect self. Choose again.\n";
                continue;
            }
            break;
        }
	}
	if(checkalive(pl, witch) && st.wolfTarget!=-1 && gs.witchHasSave)
    {
        cout << "\nWitch: victim is " << pl[st.wolfTarget].name << "\n";
        cout << "Save them? (1=yes 0=no): ";
        int x; cin >> x;
        st.witchSave = (x == 1);
    }
    if(checkalive(pl, witch) && gs.witchHasPoison)
    {
        cout<<"\nWitch: use poison tonight? (1=yes 0=no): ";
        int use;cin>>use;

        if(use==1)
        {
            int witchIndex=listalive(pl, witch)[0];
            while(true)
            {
                st.witchPoisonTarget=choosealive(pl, "Witch: choose someone to poison");
                if(st.witchPoisonTarget==witchIndex)
                {
                    cout<<"Invalid: witch cannot poison self. Choose again.\n";
                    continue;
                }
                break;
            }
        }
    }
    return st;
}

vector<int> NightResult(vector<Player>& pl,const Nightstate& st,Gamestate& gs)
{
    vector<int> died;
    if (st.wolfTarget!=-1)	//resolve wolf kill
    {
        bool protectedByGuard=(st.guardTarget==st.wolfTarget);
        bool savedByWitch=st.witchSave;
        if(st.witchSave)
            gs.witchHasSave=false;	//if witch choose to save, loss the save
        if(!protectedByGuard && !savedByWitch)
        {
            if (pl[st.wolfTarget].alive)
            {
                pl[st.wolfTarget].alive=false;
                died.push_back(st.wolfTarget);
            }
        }
    }
    if (st.witchPoisonTarget != -1)	//resolve witch poison
    {
        gs.witchHasPoison=false; // can use poison once
        if (pl[st.witchPoisonTarget].alive)
        {
            pl[st.witchPoisonTarget].alive=false;
            died.push_back(st.witchPoisonTarget);
        }
    }
    return died;
}

void printNightReport(const vector<Player>& pl,const vector<int>& died)
{
    cout<<"\n=== NIGHT RESULT ===\n";
    if(died.empty())
    {
        cout<<"No one died tonight.\n";
        return;
    }
    cout<<"Died tonight: ";
    for(int i=0;i<(int)died.size(); i++)
    {
        if(i) cout<<", ";
        cout<<pl[died[i]].name;
    }
    cout<<"\n";
}

int main()
{
    vector<Player> pl;  // Player list
    Playerinput(pl);    // Name and role input

	Gamestate gs;

    //cout<<"\n=== BEFORE NIGHT ===\n";
    //PrintPlayer(pl);   // in trạng thái trước đêm (test)

    Nightstate st=Nightphase(pl,gs);  // asking for action in night
    vector<int> died=NightResult(pl,st,gs);  // showing result after night

    printNightReport(pl,died);      // print out who died last night

    cout<<"\n=== AFTER NIGHT ===\n";
    PrintPlayer(pl);     // print the players status after night

    cout<<"\nAlive wolves: "<<listalive(pl,wolf).size()<<endl; // debug nhanh
    cout<<"Win status: "<<Checkwin(pl)<<endl;                   // check win tạm thời

    return 0;                          // kết thúc chương trình
}


 