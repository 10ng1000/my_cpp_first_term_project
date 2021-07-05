#include "War300.h"
#include <iostream>
#include <string>
#include <exception>
#include <algorithm>


City citys[1000];

int City::totalCity=0;

City::City()
{
    redWarrior=nullptr;
    blueWarrior=nullptr;
}

void City::remove_warrior(bool color)
{
    if (color==1){
        redWarrior=nullptr;
    }
    else{
        blueWarrior=nullptr;
    }
}

void City::set_totalCity(int n)
{
    totalCity=n;
}

int City::get_totalCity()
{  
    return totalCity;
}

void City::add_warrior(Warrior* warrior)
{
    if (warrior->get_color()==1){
        redWarrior=warrior;
    }
    else{
        blueWarrior=warrior;
    }
}

bool City::judge_battle()const
{
    if(redWarrior!=nullptr && blueWarrior!= nullptr){
        return 1;
    }
    return 0;
}

Warrior *City::get_redWarrior()
{
    return redWarrior;
}

Warrior *City::get_blueWarrior()
{
    return blueWarrior;
}

int Weapon::weapon_order[3]={0,1,2};

Weapon::Weapon(Warrior* warrior)
    :owner(warrior)
{}


int Weapon::get_use_time()const
{
    return useTime;
}

void Weapon::change_onwer(Warrior *owner)
{
    this->owner = owner;
}

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

int Weapon::get_attack()const
{
    return atk;
}

void Weapon::attack(Warrior &warrior)
{
    warrior.hurt(atk);
}

int Sword::get_pos()const
{
    return 0;
}

Sword::Sword(Warrior* owner)
    :Weapon(owner)
{
    useTime=INF;
    set_attack(*owner);
}

const string Sword::get_weapon_name()const
{
    return "sword";
}

void Sword::set_attack(const Warrior& warrior)
{
    atk = warrior.get_force()*0.2;
}

Bomb::Bomb(Warrior* owner)
    :Weapon(owner)
{
    useTime=1;
    set_attack(*owner);
}

void Bomb::attack(Warrior&warrior)
{
    warrior.hurt(atk);
    if(owner->bomb_protect()==0) owner->hurt(atk/2);
    useTime--;
}

const string Bomb::get_weapon_name()const
{
    return "bomb";
}

void Bomb::set_attack(const Warrior&warrior)
{
    atk = warrior.get_force()*0.4;
}

int Bomb::get_pos()const
{
    return 1;
}

Arrow::Arrow(Warrior* owner)
    :Weapon(owner)
{
    useTime=2;
    set_attack(*owner);
}

void Arrow::attack(Warrior &warrior)
{
    warrior.hurt(atk);
    useTime--;
}

const string Arrow::get_weapon_name()const
{
    return "arrow";
}

void Arrow::set_attack(const Warrior&warrior)
{
    atk=warrior.get_force()*0.3;
}

int Arrow::get_pos()const
{
    return 2;
}

int Warrior::blue_sum=0;
int Warrior::red_sum=0;

Warrior::Warrior(int strength,Base& base)
        :strength(strength)
    {
        pos=base.get_sum();
        for (int i = 0; i < 10; i++) {
            weapons[i]=nullptr;
        }
        this->base=&base;
        nowWeapon=0;
        totalWeapon=0;
        if(base.get_color()==1){
            num=++red_sum;
            nowCity=0;
        }
        else{
            num=++blue_sum;
            nowCity=City::get_totalCity()+1;
        }
    }

void Warrior::delete_weapon()
{
    delete weapons[nowWeapon];
    weapons[nowWeapon]=nullptr;
}

int Warrior::get_now_weapon()const
{
    return nowWeapon;
}

void Warrior::weapon_robbed(int i)
{
    weapons[i] = nullptr;
}

Warrior::~Warrior()
{
    citys[nowCity].remove_warrior(base->get_color());
    base->warrior_deleted(pos);
    for(int i = 0; i < totalWeapon; i++){
        if(weapons[i]!=nullptr){
            delete weapons[i];
        }
    }
}

int Warrior::get_nowCity()const
{
    return nowCity;
}

int Warrior::get_totalweapon()const
{
    return totalWeapon;
}

void Warrior::claim_stat()
{
    base->show_time();
    cout<<" "<<base->show_color()<<" "<<get_type_name()<<" "<<num<<" has ";
    sort_weapon();
    int swordNum=0,arrowNum=0,bombNum = 0;
    for(int i = 0; i < totalWeapon; i++){
        switch(weapons[i]->get_pos()){
            case 0: swordNum++;break;
            case 1: bombNum++;break;
            case 2: arrowNum++;break;
        }
    }
    cout<<swordNum<<" sword "<<bombNum <<" bomb "<<arrowNum <<" arrow "<<"and "<<strength<<" elements"<<endl;
}


void Warrior::wrap_up(Warrior &other)
{
    this->sort_weapon();
    other.sort_weapon();
    for (int i = 0; i <other.totalWeapon && totalWeapon<10; i++){
        this->weapons[totalWeapon++]=other.weapons[i];
        other.weapons[i]->change_onwer(this);
        other.weapon_robbed(i);
        this->weapons[i]->set_attack(*this);
    }
}

void Warrior::yell()const
{
    return;
}

void Warrior::reduce_loyalty()
{
    return;
}

bool Warrior::bomb_protect()const
{
    return 0;
}

void Warrior::melt()
{
    return;
}

Weapon* Warrior::get_weapons(int i) const
{
    return weapons[i];
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

int Warrior::get_loyalty()const
{
    return 0;
}

int Warrior::get_force()const
{
    if(this->get_type_name()=="dragon") return Dragon::get_force();
    if(this->get_type_name()=="ninja") return Ninja::get_force();
    if (this->get_type_name() == "iceman") return Iceman::get_force();
    if (this->get_type_name() == "lion") return Lion::get_force();
    if (this->get_type_name() == "wolf") return Wolf::get_force();
    else{
        throw runtime_error("武士姓名返回时错误");
    }
}

void Warrior::rob(Warrior &other)
{
    return;
}

int Warrior::get_num()const
{
    return num;
}

bool Warrior::get_color()const
{
    return base->get_color();
}

void Warrior::hurt(int atk)
{   
    strength -= atk;
}

void Warrior::show_win()const
{
    base->show_time();
    cout<<" "<<base->show_color()<<" "<<get_type_name()<<" "<<num<<" reached blue headquarter with "<<strength<<" elements and force "<<get_force()<<endl;
}

bool Warrior::move()
{
    melt();
    reduce_loyalty();
    citys[nowCity].remove_warrior(base->get_color());
    if(base->get_color()==1) nowCity++;
    else nowCity--;
    if((base->get_color()==1&&nowCity==City::get_totalCity()+1)||(base->get_color() == 0&&nowCity==0)){
        show_win();
        base->show_win();
        return 1;
    }
    citys[nowCity].add_warrior(this);
    base->show_time();
    cout<<" "<<base->show_color()<<" "<<get_type_name()<<" "<<num<<" marched to city "<<nowCity<<" with "<<strength<<" elements and force "<<get_force()<<endl;
    return 0;
}

bool Warrior::attack(Warrior& other)
{
    int loopTime=0;
    if(totalWeapon==0){
        return 0;
    }
    while(weapons[nowWeapon]==nullptr || weapons[nowWeapon]->get_attack()==0){
        if(loopTime == totalWeapon){
            return 0;
        }
        nowWeapon++;
        loopTime++;
        if(nowWeapon >= totalWeapon) nowWeapon%=totalWeapon;
    }
    weapons[nowWeapon]->attack(other);
    if(weapons[nowWeapon]->get_use_time() == 0) delete_weapon();
    nowWeapon++;
    if(nowWeapon>=totalWeapon){
        nowWeapon-=totalWeapon;
    }
    return 1;
}

void Warrior::claim_battle_win(const Warrior &other)const
{
    base->show_time();
    cout<<" "<<base->show_color()<<" "<<get_type_name()<<" "<<num<<" killed "<<other.base->show_color()<<" "<<other.get_type_name()<<" "<<other.get_num()<<" in city "<<nowCity<<" remaining "<<strength<<" elements"<<endl;
}

void Warrior::claim_battle_draw(const Warrior &w1,const Warrior &w2)
{
    w1.base->show_time();
    cout<<" both "<<w1.base->show_color()<<" "<<w1.get_type_name()<<" "<<w1.get_num()<<" and "<<w2.base->show_color()<<" "<<w2.get_type_name()<<" "<<w2.get_num()<<" were alive in city "<<w1.nowCity<<endl;
    w1.yell();w2.yell();
}

void Warrior::claim_battle_all_die(const Warrior &w1,const Warrior &w2)
{
    w1.base->show_time();
    cout<<" both "<<w1.base->show_color()<<" "<<w1.get_type_name()<<" "<<w1.get_num()<<" and "<<w2.base->show_color()<<" "<<w2.get_type_name()<<" "<<w2.get_num()<<" died in city "<<w1.nowCity<<endl;
}

void Warrior::battle(Warrior* w1,Warrior* w2)
{
    bool firstAttackable = 1,latterAttackable = 1;
    w1->sort_weapon();
    w2->sort_weapon();
    Warrior*first,*latter;
    if(w1->nowCity%2==1){
        first=w1;latter=w2;
    }
    else {
        first=w2;latter=w1;
    }
    while(1){
        if(first->strength <= 0 && latter->strength <= 0){
            claim_battle_all_die(*w1,*w2);
            delete w1;
            delete w2;
            return;
        }
        if(first->strength <=0){
            latter->claim_battle_win(*first);
            latter->wrap_up(*first);
            delete first;
            latter->yell();
            return;
        }
        if(firstAttackable!=0){
            firstAttackable=first->attack(*latter);
        }
        if(first->strength <= 0 && latter->strength <= 0){
            claim_battle_all_die(*w1,*w2);
            delete w1;
            delete w2;
            return;
        }
        if(latter->strength<=0){
            first->claim_battle_win(*latter);
            first->wrap_up(*latter);
            delete latter;
            first->yell();
            return;
        }
        if(latterAttackable!=0){
            latterAttackable=latter->attack(*first);
        }
        /*if(first->totalWeapon==0&&latter->totalWeapon==0){
            return;
        }*/
        if(firstAttackable==0&&latterAttackable==0){
            claim_battle_draw(*w1,*w2);
            return;
        }
    }
}

void Warrior::sort_weapon()
{
    if(totalWeapon == 0) return;
    nowWeapon=0;
    int timer=0;
    while(weapons[timer]==nullptr){
        timer++;
        if(timer==totalWeapon){
            totalWeapon=0;
            return;
        }
    }
    int count = 0;
    Weapon **p= weapons,**q= weapons;
    while(p < weapons + totalWeapon){
        while(*p==nullptr){
            p++;
            if(p == weapons + totalWeapon){
                totalWeapon=count;
                sort(weapons,weapons + totalWeapon,cmp);
                return;
            }
        }
        *q = *p; q++; p++; count++;
    }
    totalWeapon=count;
    sort(weapons,weapons + totalWeapon,cmp);
}

int Dragon::force=0;

void Dragon::set_force(int force)
{
    Dragon::force=force;
}

int Dragon::get_force()
{
    return Dragon::force;
}

Dragon::Dragon(int strength,Base& base)
        :Warrior(strength,base)
{
    weapons[0]=Weapon::select_weapon(get_sum()%3,this);
    totalWeapon++;
}

void Dragon::yell()const
{
    base->show_time();
    cout<<" "<<base->show_color()<<" dragon "<<num<<" yelled in city "<<nowCity<<endl;
}

const string Dragon::get_type_name()const
{
    return "dragon";
}

int Ninja::force=0;

Ninja::Ninja(int strength,Base& base)
    :Warrior(strength,base)
{
    weapons[0]=Weapon::select_weapon(get_sum()%3,this);
    weapons[1]=Weapon::select_weapon((get_sum()+1)%3,this);
    totalWeapon+=2;
}

void Ninja::set_force(int force)
{
    Ninja::force=force;
}

int Ninja::get_force()
{
    return Ninja::force;
}

bool Ninja::bomb_protect()const
{
    return 1;
}

const string Ninja:: get_type_name()const
{
    return "ninja";
}

int Iceman::force=0;

Iceman::Iceman(int strength,Base& base)
    :Warrior(strength,base)
{
    weapons[0]=Weapon::select_weapon((get_sum())%3,this);
    totalWeapon++;
}

void Iceman::set_force(int force)
{
    Iceman::force=force;
}

int Iceman::get_force()
{
    return Iceman::force;
}

void Iceman::melt()
{
    int temp= 0.1*strength;
    strength-=temp;
}

const string Iceman::get_type_name()const
{
    return "iceman";
}

int Lion::force=0;
int Lion::loyaltyLoss=0;

Lion::Lion(int strength,Base& base)
    :Warrior(strength,base)
{
    weapons[0]=Weapon::select_weapon((get_sum())%3,this);
    totalWeapon++;
    loyalty=base.get_yuan()-strength;
}

void Lion::set_force(int force)
{
    Lion::force=force;
}

int Lion::get_force()
{
    return Lion::force;
}

const string Lion::get_type_name()const
{
    return "lion";
}

int Lion::get_loyalty()const
{
    return loyalty;
}

void Lion::set_loyaltyLoss(int k)
{
    Lion::loyaltyLoss = k;
}

void Lion::reduce_loyalty()
{
    this->loyalty-=loyaltyLoss;
}

int Wolf::force=0;

Wolf::Wolf(int strength,Base& base)
    :Warrior(strength,base)
{}

void Wolf::rob(Warrior &other)
{
    string otherColor;
    if(base->get_color()==1){
        otherColor="blue";
    }
    else {
        otherColor="red";
    }
    if(other.get_type_name()=="wolf"||other.get_totalweapon() == 0) return;
    other.sort_weapon();
    sort_weapon();
    int nowWeaponPos,count=0;
    int j=0;
    string robbedWeaponName;
    robbedWeaponName = other.get_weapons(j)->get_weapon_name();
    nowWeaponPos=other.get_weapons(j)->get_pos();
    do{
        weapons[totalWeapon]=other.get_weapons(j);
        weapons[totalWeapon]->change_onwer(this);
        weapons[totalWeapon]->set_attack(*this);
        other.weapon_robbed(j);
        totalWeapon++;j++;count++;
    }while(other.get_weapons(j)!=nullptr && other.get_weapons(j)->get_pos()==nowWeaponPos && totalWeapon< 10 && j<10);
    base->show_time();
    cout<<" "<<base->show_color()<<" wolf "<<num<<" took "<<count<<" "<<robbedWeaponName<<" from "<<otherColor<<" "<<other.get_type_name()<<" "<<other.get_num()<<" in city "<<nowCity<<endl;
}

void Wolf::set_force(int force)
{
    Wolf::force=force;
}

int Wolf::get_force()
{
    return Wolf::force;
}

const string Wolf::get_type_name()const
{
    return "wolf";
}

int Base::minute=0;
int Base::hour=0;
int Base::redEnd=0;
int Base::blueEnd=0;
int Base::red_order[5]={2,3,4,1,0};
int Base::blue_order[5]={3,0,1,2,4};

Base::~Base()
{
    for(int i=0;i<sum;i++){
        if(warriors[i]!=nullptr){
            delete warriors[i];
        }
    }
}

Base::Base(int yuan,bool color)
    :yuan(yuan),color(color)
{
    now_make_pos=0;
    sum=0;
    wolfNum[0]={0};
    wolfSum=0;
    lionNum[0]={0};
    lionSum=0;
    for( int i=0 ;i<1000 ;i++){
        warriors[i]=nullptr;   
    }
}

void Base::show_time()const
{
    if(hour<10){
        cout<<"00";
    }
    else if(hour<100){
        cout<<"0";
    }
    cout<<hour;
    cout<<":";
    if(minute<10){
        cout<<"0";
    }
    cout<<minute;
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
        case 0: ;warriors[sum]=new Dragon (cost,*this);yuan-=cost;return *(warriors[sum]);
        case 1: ;warriors[sum]=new Ninja (cost,*this);yuan-=cost;return *(warriors[sum]);
        case 2: ;warriors[sum]=new Iceman (cost,*this);yuan-=cost;return *(warriors[sum]);
        case 3: ;warriors[sum]=new Lion (cost,*this);yuan-=cost;lionNum[lionSum++]=sum;return *(warriors[sum]);
        case 4: ;warriors[sum]=new Wolf (cost,*this);yuan-=cost;wolfNum[wolfSum++]=sum;return *(warriors[sum]);
        default:throw invalid_argument("武器选择错误");
    }
}

void Base::claim_make(Warrior& warrior)
{
    show_time();
    cout<<" "<<show_color()<<" "<<warrior.get_type_name()<<" "<<warrior.get_num()<<" born"<<endl;
    if(warrior.get_type_name() == "lion"){
        cout<<"its loyalty is "<<warrior.get_loyalty()<<endl;;
    }
}

bool Base::is_time_exceed(int time)
{
    if( hour*60 + minute > time){
        return 1;
    }
    return 0;
}

void Base::start(Base& red,Base &blue,int cost[],int time)
{
    int flag=0;
    while(1){
        if(is_time_exceed(time)==1) return;
        red.make_loop(cost);
        blue.make_loop(cost);
        minute+=5;
        if(is_time_exceed(time)==1) return;
        red.lion_escape();
        blue.lion_escape();
        minute +=5;
        if(is_time_exceed(time)==1) return;
        if(red.march()==1) flag=1;
        if(blue.march()==1) flag = 1;
        if(flag==1) return;   
        minute += 25;
        if(is_time_exceed(time)==1) return;
        red.wolf_rob();
        blue.wolf_rob();
        minute += 5;
        if(is_time_exceed(time)==1) return;
        start_battle(red,blue);   
        minute += 10;
        if(is_time_exceed(time)==1) return;
        red.claim_yuan();
        blue.claim_yuan();
        minute += 5;
        if(is_time_exceed(time)==1) return;
        red.all_claim_stat();
        blue.all_claim_stat();
        hour += 1;
        minute = 0;
    }
}

void Base::make_loop(int cost[])
{
    if(color==1){
        if(redEnd==1) return;
        if(yuan-cost[red_order[now_make_pos%5]]>=0){
            claim_make(make_worrior(cost[red_order[now_make_pos%5]],red_order[now_make_pos%5]));
        }
        else {
            redEnd++;
        }
    }
    else{
        if(blueEnd==1) return;
        if(yuan-cost[blue_order[now_make_pos%5]]>=0){
            claim_make(make_worrior(cost[blue_order[now_make_pos%5]],blue_order[now_make_pos%5]));
        }
        else {
            blueEnd++;
        }
    }
    sum++;
    now_make_pos++;
}

bool Base::march()
{
    int flag=0;
    for(int i = 0; i <sum; i++){
        if(warriors[i]!=nullptr){
            if(warriors[i]->move()==1) flag=1;
        }
    }
    return flag;
}

void Base::wolf_rob()
{
    for(int i = 0; i < wolfSum; i++){
        if(warriors[wolfNum[i]]!=nullptr && citys[warriors[wolfNum[i]]->get_nowCity()].judge_battle()){
            if(color==1){
                warriors[wolfNum[i]]->rob(*citys[warriors[wolfNum[i]]->get_nowCity()].get_blueWarrior());
            }
            else{
                warriors[wolfNum[i]]->rob(*citys[warriors[wolfNum[i]]->get_nowCity()].get_redWarrior());
            }
        }                                                                                                                                            
    }
}

void Base::lion_escape()
{
    for(int i=0; i<lionSum; i++){
        if(warriors[lionNum[i]]!=nullptr && warriors[lionNum[i]]->get_loyalty()<=0){
            show_time();
            cout<<" "<<show_color()<<" lion "<<warriors[lionNum[i]]->get_num()<<" ran away"<<endl;
            delete warriors[lionNum[i]];warriors[lionNum[i]]=nullptr;
        }
    }
}

void Base::claim_yuan()
{
    show_time();
    cout<<" "<<yuan<<" elements in "<<show_color()<<" headquarter"<<endl;
}

void Base::all_claim_stat()
{
    for(int i =0 ; i < sum; i++){
        if(warriors[i] != nullptr){
            warriors[i]->claim_stat();
        }
    }
}

bool Base::get_color()const
{
    return color;
}

int Base::get_yuan()const
{
    return yuan;
}

void Base::show_win()const 
{
    string otherColor;
    if(color==1){
        otherColor="blue";
    }
    else {
        otherColor="red";
    }
    show_time();
    cout<<" "<<otherColor<<" headquarter was taken"<<endl;
}

void Base::start_battle(Base &b1, Base&b2)
{
    for(int i = 1; i <= City::get_totalCity() ; i++){
        if(citys[i].judge_battle()){
            Warrior::battle(citys[i].get_redWarrior(),citys[i].get_blueWarrior());
        }
    }
}

void Base::warrior_deleted(int i)
{
    warriors[i]=nullptr;
}

int Base::get_sum()const
{
    return sum;
}

void Init()
{
    Base::redEnd=0;Base::blueEnd=0;Base::hour=0;Base::minute=0;
    Warrior::blue_sum=0;Warrior::red_sum = 0;
}

bool cmp(const Weapon *w1,const Weapon *w2)
{
    if(w1->get_pos() ==2 && w2->get_pos()==2){
         return w1->get_use_time()<w2->get_use_time();
    }
    return w1->get_pos()<w2->get_pos();
}