#include "doctest.h"
#include "sources/Team.hpp"
#include "sources/L_team.hpp"
#include "sources/Team2.hpp"
#include <stdexcept>
#include "iostream"
#include <string>


using namespace std;
namespace ariel {
    class Player : public Character {
        public:
            Player( std::string name, Point place, int life) : Character(name, place, life) {}

            std::string print(){
                return "player: " + getName();
            }
        };
    }

using namespace ariel;

TEST_CASE("1) Test print function:")
{
        ariel::Point pla(1.0, 1.0);
        int life = 100;
        string name = "char";
        ariel::Player Player(name, pla, life);
        string expected = "Name: char\nlife: 100\nplace: (1.0, 1.0)";
        CHECK(Player.print() == expected);
}

TEST_CASE("2)Test Point distance") 
    {
        ariel::Point p1(0, 0);
        ariel::Point p2(140.0, 2.0);
        CHECK(p1.distance(p2) == 12);
        CHECK(p2.distance(p1) == 12);
    }

TEST_CASE("3)Test the player ain't shooting with empty bullets")
{
    Cowboy *ron = new Cowboy("ron", Point(0,0));
    Cowboy *john = new Cowboy("john", Point(10.0, 10.0));
    ron->shoot(john);
    ron->shoot(john);
    ron->shoot(john);
    ron->shoot(john);
    ron->shoot(john);
    ron->shoot(john);
    CHECK_THROWS(ron->shoot(john));
    //john still alive because only 60 points were reduced from his life
    CHECK_NOTHROW(john->isAlive());
}

TEST_CASE("Test case 4: Assignment operator")
{
    Cowboy *alex = new Cowboy("Tom", Point(1.0, 1.0));
    Team t_A(alex);
    t_A.add(new YoungNinja("Yogi", Point(2.0, 2.0)));
    t_A.add(new TrainedNinja("Hikari", Point(3.0, 3.0)));

    Team t_B(new Cowboy("Jerry", Point(4.0, 4.0)));
    t_B.add(new OldNinja("Sushi", Point(5.0, 5.0)));

    t_B = t_A;

    CHECK(t_B.stillAlive() == 3);
}
TEST_CASE("5)Test the size of team aint more then 10 members")
{
    OldNinja *suaa = new OldNinja("suaa", Point(30.0, 30.0));
    Team ninja_T(suaa);
    ninja_T.add(new YoungNinja("aaa", Point(32,12)));
    ninja_T.add(new YoungNinja("bbb", Point(22,22)));
    ninja_T.add(new YoungNinja("ccc", Point(42,42)));
    ninja_T.add(new YoungNinja("ddd", Point(20,31)));
    ninja_T.add(new YoungNinja("eee", Point(11,35)));
    ninja_T.add(new YoungNinja("fff", Point(14,30)));
    ninja_T.add(new YoungNinja("ggg", Point(9,13)));
    ninja_T.add(new YoungNinja("iii", Point(2,22)));
    ninja_T.add(new YoungNinja("jjj", Point(25,4)));
    CHECK_NOTHROW(ninja_T.add(new YoungNinja("kkk", Point(19,30))));
    CHECK_THROWS(ninja_T.add(new YoungNinja("lll", Point(1,1))));
}
    Cowboy *smith = new Cowboy("smith", Point(6,6));
    Cowboy *john = new Cowboy("john", Point(11, 11));
    Cowboy *shon = new Cowboy("shon", Point(14, 16));
    Cowboy *petrik = new Cowboy("petrik", Point(1, 5));
TEST_CASE("6)Test Character can't be hit even more after is life gotten to 0")
{
    smith->shoot(john);
    smith->shoot(john);
    john->shoot(smith);
    smith->shoot(john);
    smith->shoot(john);
    smith->shoot(john);
    smith->shoot(john);
    //smith reload after 6 shots.
    smith->reload();
    smith->shoot(john);
    john->shoot(smith);
    smith->shoot(john);
    smith->shoot(john);
    //john can still shoot smith, because he shot smith less then 10 shots
    CHECK_NOTHROW(john->shoot(smith));
    smith->shoot(john);
    //smith cant shoot anymore john because his life points gotten to 0 after 10 shots.
    CHECK_THROWS(smith->shoot(john));
}

TEST_CASE("7)Test Attacking an empty team")
{
    Cowboy* tommy = new Cowboy("Tommmy", Point(2.0, 1.0));
    Team team_A(tommy);
    Team team_B(new OldNinja("Sushi", Point(2.0, 4.0)));
    team_A.attack(&team_B);
    CHECK(team_A.stillAlive() >= 1);
    CHECK(team_B.stillAlive() == 1);
}   


TEST_CASE("8)Test cowboy cant shoot without bullets")
{
    for (int i = 0; i < 6; i++)
    {
    shon->shoot(petrik);
    }
    
    CHECK_THROWS(shon->shoot(petrik));
    CHECK_EQ(shon->hasboolets(), false);
    shon->reload();
    CHECK_EQ(shon->hasboolets(), true);
    CHECK_NOTHROW(shon->shoot(petrik));
}


TEST_CASE("9)Test Ninja can't make damge with slash if he the distance mora then 1 meter ")
{
    TrainedNinja *tobi = new TrainedNinja("tobi", Point(2, 2));
    YoungNinja *obit = new YoungNinja("obit", Point(5, 5));
    CHECK_THROWS(tobi->slash(obit));
    tobi->move(obit);
    CHECK_NOTHROW(tobi->slash(obit));   
}

TEST_CASE("10)Test traine ninja dies after 3 slash from another trained ninja")
{
    TrainedNinja *a = new TrainedNinja("a", Point(2, 2));
    TrainedNinja *b = new TrainedNinja("b", Point(2.5, 2.5));   
    for (int i = 0; i < 2; i++)
    {
        a->slash(b);
    }
    CHECK_EQ(b->isAlive(), true);
    a->slash(b);
    CHECK_EQ(b->isAlive(), false);

}

TEST_CASE("11)Test Attack while no player is alive")
{
    Team t_A(nullptr);
    
    Team t_B(new Cowboy("James", Point(3.0, 3.0)));
    t_B.add(new YoungNinja("son", Point(12.0, 9.0)));

    CHECK_NOTHROW(t_B.attack(&t_A));
    CHECK(t_B.stillAlive() == 2);
}

TEST_CASE("12) Test distance function")
{
        Point p1(0, 0);
        Point p2(3, 4);
        int life = 100;
        string name = "char";
        Player c1(name, p1, life);
        Player c2(name, p2, life);
        CHECK(c1.distance(c2) == doctest::Approx(5.0));
}
TEST_CASE("13) Test adding teamats ")
{
    Cowboy *yaron = new Cowboy("Yaron", Point(0,0)); 
    Team t1(yaron);
    t1.add(new YoungNinja("john2", Point(10.0, 10.0)));
    CHECK(t1.stillAlive() == 2);
}
TEST_CASE("14) Test damge from hit function")
{
  YoungNinja *ron2 = new YoungNinja("ron2", Point(0,0));
  YoungNinja *john2 = new YoungNinja("john2", Point(10.0, 10.0)); 
  ron2->hit(100);
  john2->hit(100);
  CHECK(ron2->isAlive() == false);
  CHECK(john2->isAlive() == false);
}

TEST_CASE("15) stillalive function")
{
    OldNinja *san = new OldNinja("sanin", Point(0,0));
    san->hit(100);
    CHECK(san->isAlive() == 0);
} 
Cowboy *cow = new Cowboy("Cow", Point(0, 0));
Cowboy *chan = new Cowboy("nemesis", Point(2.2, 2.4));
TEST_CASE("16) Test Cowboy constructor")
{
CHECK(cow->getName() == "Cow");
CHECK(cow->isAlive());
CHECK(cow->hasboolets());
}
TEST_CASE("17) Test shots and hasboolets ")
{
 for (int i = 0; i < 6; i++)
 {
    cow->shoot(chan);
 }
CHECK(cow->isAlive());
CHECK_NOTHROW(cow->reload());
}

TEST_CASE("18) Test of diffrent of speed for ninjas")
{
    OldNinja *Oldi = new OldNinja("O", Point(0, 0));
    YoungNinja *Youngi = new YoungNinja("Y", Point(5.0, 5.0));
    TrainedNinja *trained = new TrainedNinja("T", Point(10.0,10.0));
    CHECK(Youngi->g_Speed() == 14);
    CHECK(Oldi->g_Speed() == 12);
    CHECK(trained->g_Speed() == 8);
}
TEST_CASE("19) Attacking your own team")
{
    Cowboy* tomi = new Cowboy("Tomi", Point(1, 1));
    //tea leader tomi
    Team t(tomi);

    t.add(new YoungNinja("Yogi", Point(2, 2)));
    t.add(new TrainedNinja("Hikari", Point(3, 3)));

    CHECK_NOTHROW(t.attack(&t));
    CHECK(t.stillAlive() == 3);
}
// teams can attack another type of team
TEST_CASE("20) Test  of Team2 VS Team2")
{
        Cowboy *Sherif = new Cowboy("Sherif",Point(101,150));
        OldNinja *Outlows = new OldNinja("Enemies",Point(0,0));
        Team2* t_S = new Team2(Sherif);
        Team2* t_O = new Team2(Outlows);
        CHECK_NOTHROW(t_O->attack(t_S));
        CHECK_NOTHROW(t_S->attack(t_O));
        while(t_S->stillAlive() && t_O->stillAlive()){
            t_S->attack(t_O);
            t_O->attack(t_S);
        }
        CHECK(t_S->stillAlive());
        CHECK(t_O->stillAlive());
}