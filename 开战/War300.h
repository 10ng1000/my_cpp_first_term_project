#include <iostream>
#include <string>
class Warrior;

using namespace std;

const int INF=0x3f3f3f3f;

class Base;
class Weapon;
class Warrior;

class City
{
    private:
    static int totalCity;
    Warrior* redWarrior=nullptr;
    Warrior* blueWarrior=nullptr;
    public:
    City();
    static void set_totalCity(int n);
    static int get_totalCity();
    void add_warrior(Warrior* warrior);
    bool judge_battle() const;
    Warrior* get_blueWarrior();
    Warrior* get_redWarrior();
    void remove_warrior(bool color);
};

class Warrior
{
    protected:
    static int blue_sum;
    static int red_sum;
    Base* base;
    int num;
    int pos;
    int strength;
    int nowCity;
    int nowWeapon;
    int totalWeapon;
    Weapon* weapons[10];
    public:
    Warrior(int strength,Base& base);
    virtual ~Warrior();
    virtual const string get_type_name() const=0;
    int get_sum();
    int get_strength()const;
    virtual int get_loyalty()const;
    friend void Init();
    void hurt(int atk);
    int get_force() const;
    bool move();
    bool attack(Warrior& other);
    void sort_weapon();
    static void battle(Warrior* w1,Warrior* w2);
    void wrap_up(Warrior &other);
    inline virtual void yell()const;
    inline virtual bool bomb_protect()const;
    inline virtual void melt();
    inline virtual void reduce_loyalty();
    inline int get_totalweapon()const;
    inline Weapon* get_weapons(int i) const;
    void weapon_robbed(int i);
    int get_num()const;
    inline int get_nowCity()const;
    virtual void rob(Warrior &other);
    void claim_battle_win(const Warrior &other)const;
    static void claim_battle_draw(const Warrior &w1,const Warrior &w2);
    static void claim_battle_all_die(const Warrior &w1,const Warrior &w2);
    void claim_stat();
    bool get_color()const;
    int get_now_weapon()const;
    void delete_weapon();
    void show_win()const;
};

class Base
{
    private:
    int sum;
    int yuan;
    bool color;//红1蓝0
    int wolfNum[1000],wolfSum;
    int lionNum[1000],lionSum;
    Warrior *warriors[1000];
    static int hour,minute;
    static int redEnd,blueEnd;
    static int red_order[];
    static int blue_order[];
    int now_make_pos;
    void make_loop(int cost[]);
    public:
    ~Base();
    Base(int yuan,bool color);
    Warrior& make_worrior(int cost,int type);
    void claim_make(Warrior& warrior);
    const string show_color()const;
    void show_time()const;
    static void start(Base &red,Base &blue,int cost[],int time);
    bool get_color()const;
    int get_yuan()const;
    void show_win()const;
    friend void Init();
    bool march();
    void wolf_rob();
    static void start_battle(Base &b1, Base&b2);
    void lion_escape();
    void claim_yuan();
    void all_claim_stat();
    void warrior_deleted(int i);
    int get_sum()const;
    static bool is_time_exceed(int time);
};

class Weapon
{
    protected:
    static int weapon_order[3];
    int atk;
    Warrior* owner;
    int useTime;
    public:
    static Weapon* select_weapon(int n, Warrior* warrior);
    Weapon( Warrior* owner);
    virtual const string get_weapon_name()const=0;
    virtual ~Weapon(){}
    friend void Init();
    virtual void set_attack(const Warrior& warrior)=0;
    virtual void attack(Warrior &warrior);
    virtual int get_pos()const= 0;
    int get_attack() const;
    void change_onwer(Warrior *owner);
    int get_use_time()const;
};

class Sword : public Weapon
{
    public:
    Sword( Warrior* owner);
    const string get_weapon_name()const;
    void set_attack(const Warrior& warrior);
    int get_pos()const;
};

class Bomb : public Weapon
{
    public:
    Bomb( Warrior* owner);
    const string get_weapon_name()const;
    void set_attack(const Warrior& warrior);
    void attack(Warrior &warrior);
    int get_pos()const;
};

class Arrow : public Weapon
{
    public:
    Arrow( Warrior* owner);
    const string get_weapon_name()const;
    void set_attack(const Warrior& warrior);
    void attack(Warrior &warrior);
    int get_pos()const;
};

class Dragon : public Warrior
{
    private:
    static int force;
    public:
    Dragon(int strength,Base& base);
    const string get_type_name()const;
    void yell()const;
    static void set_force(int force);
    static inline int get_force();
};

class Ninja : public Warrior
{
    private:
    static int force;
    public:
    Ninja(int strength,Base& base);
    const string get_type_name()const;
    bool bomb_protect()const;
    static void set_force(int force);
    static inline int get_force();
};

class Iceman : public Warrior
{
    private:
    static int force;
    Weapon* weapon;
    public:
    Iceman(int strength,Base& base);
    const string get_type_name()const;
    void melt();
    static void set_force(int force);
    static inline int get_force();
};

class Lion : public Warrior
{
    private:
    static int force;
    static int loyaltyLoss;
    int loyalty;
    public:
    Lion(int strength,Base& base);
    const string get_type_name()const;
    int get_loyalty()const;
    void reduce_loyalty();
    static void set_force(int force);
    static inline int get_force();
    static void set_loyaltyLoss(int k);
};

class Wolf : public Warrior
{
    public:
    static int force;
    Wolf(int strength,Base& base);
    const string get_type_name()const;
    static void set_force(int force);
    static inline int get_force();
    void rob(Warrior &other);
};

void Init();

bool cmp(const Weapon *w1, const Weapon *w2);