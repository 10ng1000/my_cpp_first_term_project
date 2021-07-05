#include <iostream>
#include <string>

using namespace std;

class Base;
class Weapon;

class Warrior
{
    protected:
    static int blue_sum;
    static int red_sum;
    Base* base;
    int num;
    int strength;
    int force;
    public:
    Warrior(int num,int strength,Base& base,int force=0);
    virtual ~Warrior(){};
    virtual const string get_type_name() const=0;
    int get_sum();
    int get_strength()const;
    friend void Init();
    
};

class Base
{
    private:
    int sum;
    int yuan;
    bool color;//红1蓝0
    int time;
    Warrior *warriors[1000];int dragon_count,ninja_count,iceman_count,lion_count,wolf_count;
    Warrior *garbage;
    static int end;
    static int red_order[];
    static int blue_order[];
    int chance;
    int now_make_pos;
    void make_loop(int cost[]);
    public:
    ~Base();
    Base(int yuan,bool color);
    Warrior& make_worrior(int cost,int type);
    void claim_make(Warrior& warrior);
    const string show_color()const;
    void show_time()const;
    static void start(Base &red,Base &blue,int cost[]);
    bool get_color()const;
    int get_yuan()const;
    friend void Init();
};

class Dragon : public Warrior
{
    public:
    Dragon(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
};

class Ninja : public Warrior
{
    public:
    Ninja(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
};

class Iceman : public Warrior
{
    public:
    Iceman(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
};

class Lion : public Warrior
{
    public:
    Lion(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
};

class Wolf : public Warrior
{
    public:
    Wolf(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
};

void Init();
