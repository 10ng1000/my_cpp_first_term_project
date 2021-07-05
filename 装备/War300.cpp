#include "War300.h"
#include <iostream>
#include <string>
#include <exception>

int Weapon::weapon_order[3]={0,1,2};

Weapon::Weapon(Warrior* owner)
    :owner(owner)
{}

Weapon* Weapon::select_weapon(int n,Warrior* owner)
{
    switch (n)
    {
    case 0:return new Sword(owner);break;
    case 1:return new Bomb(owner);break;
    case 2:return new Arrow(owner);break;
    default:throw invalid_argument("武器选择错误"); 
    }
}

Sword::Sword(Warrior* owner)
    :Weapon(owner)
{}

const string Sword::get_weapon_name()const
{
    return "sword";
}


Bomb::Bomb(Warrior* owner)
    :Weapon(owner)
{
    useTime=1;
}


const string Bomb::get_weapon_name()const
{
    return "bomb";
}

Arrow::Arrow(Warrior* owner)
    :Weapon(owner)
{
    useTime=2;
}

const string Arrow::get_weapon_name()const
{
    return "arrow";
}


int Warrior::blue_sum=0;
int Warrior::red_sum=0;

Warrior::Warrior(int num,int strength,Base& base,int force)
        :num(num),strength(strength),force(force)
    {
        this->base=&base;
        if(base.get_color()==1){
            red_sum++;
        }
        else{
            blue_sum++;
        }
    }

int Warrior::get_sum()
{
    {
        if(base->get_color()==1){
            return red_sum;
        }
        else{
            return blue_sum;
        }
    }
}

int Warrior::get_strength()const
    {
        return strength;
    }

double Warrior::get_morale()const
{
    return 0;
}

int Warrior::get_loyalty()const
{
    return 0;
}

Dragon::Dragon(int num,int strength,Base& base,int force)
        :Warrior(num,strength,base,force)
{
    weapons[0]=Weapon::select_weapon(get_sum()%3,this);
    morale=(base.get_yuan()-strength)/(double)strength;
}

const string Dragon::get_type_name()const
{
    return "dragon";
}

double Dragon::get_morale()const
{
    return morale;
}

Weapon& Dragon::get_weapon(int num)
{
    return *weapons[0];
}

Ninja::Ninja(int num,int strength,Base& base,int force)
    :Warrior(num,strength,base,force)
{
    weapons[0]=Weapon::select_weapon(get_sum()%3,this);
    weapons[1]=Weapon::select_weapon((get_sum()+1)%3,this);
}

const string Ninja:: get_type_name()const
{
    return "ninja";
}

Weapon& Ninja::get_weapon(int num)
{
    return *weapons[num];
}

Iceman::Iceman(int num,int strength,Base& base,int force)
    :Warrior(num,strength,base,force)
{
    weapon=Weapon::select_weapon((get_sum())%3,this);
}

Weapon& Iceman::get_weapon(int num)
{
    return *weapon;
}

const string Iceman::get_type_name()const
{
    return "iceman";
}

Lion::Lion(int num,int strength,Base& base,int force)
    :Warrior(num,strength,base,force)
{
    loyalty=base.get_yuan()-strength;
}

Weapon& Lion::get_weapon(int num)
{
    throw invalid_argument("Lion不应该有武器");
}

const string Lion::get_type_name()const
{
    return "lion";
}

int Lion::get_loyalty()const
{
    return loyalty;
}

Wolf::Wolf(int num,int strength,Base& base,int force)
    :Warrior(num,strength,base,force)
{}

const string Wolf::get_type_name()const
{
    return "wolf";
}

Weapon& Wolf::get_weapon(int num)
{
    throw invalid_argument("Wolf不应该有武器");
}

int Base::end=0;
int Base::red_order[5]={2,3,4,1,0};
int Base::blue_order[5]={3,0,1,2,4};

Base::~Base()
{
    for(int i=0;i<sum;i++){
        delete warriors[i];
    }
}

Base::Base(int yuan,bool color)
    :yuan(yuan),color(color)
{
    now_make_pos=0;
    chance=5;
    sum=0;
    end=0;
    time=0;
    dragon_count=0;
    ninja_count=0;
    iceman_count=0;
    lion_count=0;
    wolf_count=0;
}

void Base::show_time()const
{
    if(time<10){
        cout<<"00";
    }
    else if(time<100){
        cout<<"0";
    }
    cout<<time;
}

const string Base::show_color()const
{
    if(color==1){
        return "red";
    }
    return "blue";
}

Warrior& Base::make_worrior(int cost,int type)
{
    switch(type){
        case 0: ;warriors[sum]=new Dragon (++dragon_count,cost,*this);yuan-=cost;return *(warriors[sum]);break;
        case 1: ;warriors[sum]=new Ninja (++ninja_count,cost,*this);yuan-=cost;return *(warriors[sum]);break;
        case 2: ;warriors[sum]=new Iceman (++iceman_count,cost,*this);yuan-=cost;return *(warriors[sum]);break;
        case 3: ;warriors[sum]=new Lion (++lion_count,cost,*this);yuan-=cost;return *(warriors[sum]);break;
        case 4: ;warriors[sum]=new Wolf (++wolf_count,cost,*this);yuan-=cost;return *(warriors[sum]);break;
        default:throw invalid_argument("武器选择错误");
    }
}

void Base::claim_make(Warrior& warrior)
{
    show_time();time++;
    cout<<' '<<show_color();//输出颜色
    cout<<' '<<warrior.get_type_name()<<' '<<warrior.get_sum()<<" born with strength "<<warrior.get_strength()<<","<<warrior.get_sum()<<' '<<warrior.get_type_name()<<" in";
    cout<<' '<<show_color();//输出颜色
    cout<<" headquarter"<<endl;
    if(warrior.get_type_name()=="dragon"){
        cout<<"It has a "<<warrior.get_weapon().get_weapon_name()<<" and its morale is "<<warrior.get_morale()<<endl;
    }
    if(warrior.get_type_name()=="ninja"){
        cout<<"It has a "<<warrior.get_weapon(0).get_weapon_name()<<" and a "<<warrior.get_weapon(1).get_weapon_name()<<endl;
    }
    if(warrior.get_type_name()=="iceman"){
        cout<<"It has a "<<warrior.get_weapon().get_weapon_name()<<endl;
    }
    if(warrior.get_type_name()=="lion"){
        cout<<"Its loyalty is "<<warrior.get_loyalty()<<endl;
    }
    return;
}

void Base::start(Base& red,Base &blue,int cost[])
{
    while(end<2){
        red.make_loop(cost);
        blue.make_loop(cost);
    }
}

void Base::make_loop(int cost[])
{
    if(chance==0){
        end++;
        show_time();time++;
        cout<<' '<<show_color()<<" headquarter stops making warriors"<<endl;
        chance--;
        return;
    }
    if(chance==-1){
        return;
    }
    if(color==1){
        if(yuan-cost[red_order[now_make_pos%5]]>=0){
            claim_make(make_worrior(cost[red_order[now_make_pos%5]],red_order[now_make_pos%5]));
            chance=5;
        }
        else{
            chance--;
            make_loop(cost);
        }
    }
    else{
        if(yuan-cost[blue_order[now_make_pos%5]]>=0){
            claim_make(make_worrior(cost[blue_order[now_make_pos%5]],blue_order[now_make_pos%5]));
            chance=5;
        }
        else{
            chance--;
            make_loop(cost);
        }
    }
    now_make_pos++;
}

bool Base::get_color()const
{
    return color;
}

int Base::get_yuan()const
{
    return yuan;
}

void Init()
{
    Base::end=0;
    Warrior::blue_sum=0;Warrior::red_sum = 0;
}