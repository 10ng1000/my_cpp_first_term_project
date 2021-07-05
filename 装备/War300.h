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
    Weapon* weapons[10];
    public:
    Warrior(int num,int strength,Base& base,int force=0);
    virtual ~Warrior(){};
    virtual const string get_type_name() const=0;
    int get_sum();
    int get_strength()const;
    virtual double get_morale()const;
    virtual Weapon& get_weapon(int num=0)=0;
    virtual int get_loyalty()const;
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

class Weapon
{
    protected:
    static int weapon_order[3];
    int atk;
    int num;
    Warrior* owner;
    public:
    static Weapon* select_weapon(int n, Warrior* owner);
    Weapon( Warrior* owner);
    virtual const string get_weapon_name()const=0;
    virtual ~Weapon(){}
    friend void Init();
};

class Sword : public Weapon
{
    public:
    Sword( Warrior* owner);
    const string get_weapon_name()const;
    void set_attack(const Warrior& warrior);
};

class Bomb : public Weapon
{
    private:
    int useTime;
    public:
    Bomb( Warrior* owner);
    const string get_weapon_name()const;
    void set_attack(const Warrior& warrior);
    void attack(Warrior &warrior);
};

class Arrow : public Weapon
{
    private:
    int useTime;
    public:
    Arrow( Warrior* owner);
    const string get_weapon_name()const;
    void set_attack(const Warrior& warrior);
    void attack(Warrior &warrior);
};

class Dragon : public Warrior
{
    private:
    double morale;
    public:
    Dragon(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
    double get_morale()const;
    Weapon& get_weapon(int num=0);
};

class Ninja : public Warrior
{
    private:
    public:
    Ninja(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
    Weapon& get_weapon(int num=0);
};

class Iceman : public Warrior
{
    private:
    Weapon* weapon;
    public:
    Iceman(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
    Weapon& get_weapon(int num=0);
};

class Lion : public Warrior
{
    private:
    int loyalty;
    public:
    Lion(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
    int get_loyalty()const;
    Weapon& get_weapon(int num=0);
};

class Wolf : public Warrior
{
    public:
    Wolf(int num,int strength,Base& base,int force=0);
    const string get_type_name()const;
    Weapon& get_weapon(int num=0);
};

void Init();
