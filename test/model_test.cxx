#include "model.hxx"
#include <catch.hxx>


TEST_CASE("collide tests")
{
    Model m;

    //50 x 50 square centered at origin
    my_rectangle a({0,0},0,{50,50});

    //20 x 100 rectangle centered at 50,0
    my_rectangle b({50,0},0,{20,100});

    // a and b are not intersecting

    CHECK(m.collide(a,b) == false);

    //rotating by 180 degrees shouldn't change it

    b = my_rectangle({50,0},180,{20,100});

    CHECK(m.collide(a,b) == false);

    // now rotate b 90 degrees about the center and they should be intersecting

    b = my_rectangle({50,0},90,{20,100});

    CHECK(m.collide(a,b) == true);

    //at 70 degrees they should also intersect

    b = my_rectangle({50,0},70,{20,100});

    CHECK(m.collide(a,b) == true);

    //try rotating a by 45 degrees, they should still intersect

    a = my_rectangle({0,0},45,{50,50});

    CHECK(m.collide(a,b) == true);

    //test that identical squares intersect

    b = my_rectangle({0,0},45,{50,50});

    CHECK(m.collide(a,b) == true);


}

TEST_CASE("hitting a wall"){

    Model m;

    //body 1 is hitting the left most wall, it should lose 6 in the x direction from friction, then be reflected by 0.25
    //im not testing for the y direction because the reflection is done using vector by scalar multiplication, so if one is scaled, they both are
    m.inc_body_v1({-100,0});
    m.set_body_pos1({-1,100});
    m.on_frame(0.01);
    CHECK(m.get_v1().width == 23);

    //try the other wall

    m.inc_body_v1({77,0});//getting it back to 100
    m.set_body_pos1({1500,100});
    m.on_frame(0.01);
    CHECK(m.get_v1().width == -23);


}

TEST_CASE("two players colliding"){

    Model m;

    m.set_body_pos1({100,100});
    m.set_body_pos2({100,100});

    //they are currently in the same position, so they must be intersecting
    //in the actual game, they wouldn't ever intersect this much, but this is just to test
    //that the collision reflection happens properly

    m.inc_body_v1({106,0});
    m.inc_body_v2({-106,0});

    m.on_frame(0.01);

    //velocities should have both lost 6 in their respective directions, then reflected and incremented by 0.5 of the other's velocity
    //we also have to account for the arms colliding, so after the first reflection, the bodies velocity is incremented
    //by the vector normal to the arm, scaled by 100. I did the math and it should come out to around -249

    CHECK(m.get_v1().width == -249);


}

TEST_CASE("score increments & respawn"){

    //if on_frame detects a player is below 650 pixels it will increment the score of the other player
    //and respawn the player above the ring

    Model m;

    m.set_body_pos1({100,700});

    m.on_frame(0.01);

    CHECK(m.get_score2() == 1);
    CHECK(m.get_body1().x == 400);
    CHECK(m.get_body1().y == -200);

    //try for player 2

    m.set_body_pos2({100,700});

    m.on_frame(0.01);

    CHECK(m.get_score1() == 1);
    CHECK(m.get_body2().x == 1000);
    CHECK(m.get_body2().y == -200);


}

TEST_CASE("game end conditions are met"){

    Model m;

    //lets give player 1 a score of 5, and see if it ends the game and assigns a winner

    for (int i = 0;i<5;i++){
        m.set_body_pos2({100,700});
        m.on_frame(0.01);
    }

    CHECK(m.get_score1() == 5);
    CHECK(m.get_winner() == 1);

    //try for the second player

    Model t;

    for (int i = 0;i<5;i++){
        t.set_body_pos1({100,700});
        t.on_frame(0.01);
    }

    CHECK(t.get_score2() == 5);
    CHECK(t.get_winner() == 2);


}


