
#include "model.hxx"

//My rectangle is used to have easy access to a rectangle's four corners and center, this is very useful for determining collisions

my_rectangle::my_rectangle(ge211::geometry::Dims<float> center, double angle,ge211::geometry::Dims<int> dims)
    : top_left(0,0),
      top_right(0,0),
      bottom_left(0,0),
      bottom_right(0,0)


{
    ge211::geometry::Dims<float> v1 (cos(angle/57.3),sin(angle/57.3));
    ge211::geometry::Dims<float> v2 (-sin(angle/57.3),cos(angle/57.3));

    v1 *= dims.width/2;
    v2 *= dims.height/2;

    top_left = center - v1 - v2;
    top_right = center + v1 - v2;
    bottom_left = center - v1 + v2;
    bottom_right = center + v1 + v2;

}

my_rectangle::my_rectangle(ge211::geometry::Dims<float> top_left, ge211::geometry::Dims<float> top_right,
                           ge211::geometry::Dims<float> bottom_left, ge211::geometry::Dims<float> bottom_right)
                           :top_left(top_left),
                           top_right(top_right),
                           bottom_left(bottom_left),
                           bottom_right(bottom_right)


{}

std::vector<ge211::geometry::Dims<float>>
my_rectangle::get_all(void)
{
    std::vector<ge211::geometry::Dims<float>> r = {top_left,top_right,bottom_left,bottom_right};
    return r;

}






Model::Model()
    :
    body_pos(400,100),
    arm_pos(100,100),
    body_pos2(1000,100),
    arm_pos2(100,100),

    arm_dims({10,150}),
    body_dims({20,100}),
    arm_dims2({10,150}),
    body_dims2({20,100}),


    body_velocity({0,0}),
    body_velocity2({0,0}),


    arm_rotation(0),
    body_rotation(0),
    arm_rotation2(0),
    body_rotation2(0),

    gravity(700),
    floor_height(450),

    score1(0),
    score2(0),

    body_rect(my_rectangle({0,0},0,{0,0})),
    body_rect2(my_rectangle({0,0},0,{0,0})),
    body_rect3(my_rectangle({0,0},0,{0,0})),
    arm_rect(my_rectangle({0,0},0,{0,0})),
    body_rect4(my_rectangle({0,0},0,{0,0})),
    arm_rect2(my_rectangle({0,0},0,{0,0})),

    left_wall(my_rectangle({295,500},0,{5,35})),
    right_wall(my_rectangle({1160,500},0,{5,35})),


    colliding(false),
    body_right(true),
    body_right2(false),
    menu(true),
    winner(0)


{}

double
Model::get_arm_rot1() const
{
    return arm_rotation;
}

double
Model::get_arm_rot2() const
{
    return arm_rotation2;
}

ge211::geometry::Dims<int>
Model::get_armdims1() const
{
    return arm_dims;
}

ge211::geometry::Dims<int>
Model::get_armdims2() const
{
    return arm_dims2;
}

struct my_rectangle
Model::get_armrect1() const
{
    return arm_rect;
}

struct my_rectangle
Model::get_armrect2() const
{
    return arm_rect2;
}

ge211::geometry::Posn<float>
Model::get_body1() const
{
    return body_pos;
}

ge211::geometry::Posn<float>
Model::get_body2() const
{
    return body_pos2;
}

double
Model::get_body_rot1() const
{
    return body_rotation;
}

double
Model::get_body_rot2() const
{
    return body_rotation2;
}

bool
Model::get_right1() const
{
    return body_right;
}

bool
Model::get_right2() const
{
    return body_right2;
}

int
Model::get_score1() const
{
    return score1;
}

int
Model::get_score2() const
{
    return score2;
}

int
Model::get_winner() const
{
    return winner;
}

bool Model::get_menu() const
{
    return menu;
}

int
Model::get_floor() const
{
    return floor_height;
}

ge211::geometry::Dims<int>
Model::get_v1() const
{
    return body_velocity;
}



void
Model::set_body_pos1(ge211::geometry::Posn<float> i)
{
    body_pos = i;
}

void
Model::set_body_pos2(ge211::geometry::Posn<float> i)
{
    body_pos2 = i;
}

void
Model::inc_body_v1(ge211::geometry::Dims<int> i)
{
    body_velocity += i;
}

void
Model::inc_body_v2(ge211::geometry::Dims<int> i)
{
    body_velocity2 += i;
}

void
Model::inc_arm_rot1(int i)
{
    arm_rotation += i;
}

void
Model::inc_arm_rot2(int i)
{
    arm_rotation2 += i;
}

void
Model::set_right1(bool b)
{
    body_right = b;
}

void
Model::set_right2(bool b)
{
    body_right2 = b;
}

void
Model::set_menu(bool b)
{
    menu = b;
}
//This helper calculates the relevant directional vectors needed for the separating axis theorem

bool
Model::collide_helper(my_rectangle box1,my_rectangle box2,ge211::geometry::Dims<float> axis1)
{

    std::vector<ge211::geometry::Dims<float>> corners1 = box1.get_all();
    std::vector<ge211::geometry::Dims<float>> corners2 = box2.get_all();
    std::vector<float> proj1;
    std::vector<float> proj2;

    for(int i = 0; i < 3; i++){
        proj1.push_back(dot(corners1[i],axis1));
        proj2.push_back(dot(corners2[i],axis1));
    }

    float min1 = proj1[0];
    float max1 = proj1[0];
    float min2 = proj2[0];
    float max2 = proj2[0];

    for(int i = 0; i < 3; i++){
        if(proj1[i] < min1){
            min1 = proj1[i];
        }

        if(proj1[i] > max1){
            max1 = proj1[i];
        }

        if(proj2[i] < min2){
            min2 = proj2[i];
        }

        if(proj2[i] > max2){
            max2 = proj2[i];
        }
    }

    if ((min1 <= max2 && min1 >= min2)||(min2 <= max1 && min2 >= min1)){
        return true;
    }

    return false;
}

//Combined with its helper, collide will determine whether two rectangles are intersecting using the separating axis theorem

bool
Model::collide(my_rectangle box1, my_rectangle box2)
{


    std::vector<ge211::geometry::Dims<float>> axes = {(box1.top_right - box1.top_left),(box1.top_right - box1.bottom_right),(box2.top_left - box2.bottom_left),
                                                   (box2.top_left - box2.top_right)};

    bool condition = true;

    for(int i = 0;i<3;i++){
        condition = collide_helper(box1,box2,axes[i]);
        if(!condition){
            return condition;
        }
    }

    return condition;

}

//Dot product function, useful for geometry

float
Model::dot(ge211::geometry::Dims<float> v1, ge211::geometry::Dims<float> v2) //projects v1 onto v2
{
    return ((v1.width*v2.width + v1.height*v2.height));
}

bool
Model::in_ring(ge211::geometry::Posn<float> pos)
{
    if (pos.x >= 295 && pos.x <= 1140){
        return true;
    }

    return false;
}

void
Model::end()
{
    if(score1 == 5 && score2 < 5){
        winner = 1;
    }
    else if(score1 < 5 && score2 == 5){
        winner = 2;
    }


}

void
Model::on_frame(double dt)
{

    //Gravity affects player only if they are not on the floor or not colliding

    if (body_pos.y > floor_height && in_ring(body_pos)) {
        body_velocity.height = -gravity*dt;
        body_pos.y = floor_height;
    }

    if (body_pos2.y > floor_height && in_ring(body_pos2)) {
        body_velocity2.height = -gravity*dt;
        body_pos2.y = floor_height;
    }

    if(!(colliding)) {
        body_velocity.height += dt * gravity;
        body_velocity2.height += dt * gravity;
    }

    //Ground/air Friction

    if (body_velocity.width > 0){
        body_velocity.width -= 6;
    }
    if (body_velocity.width < 0){
        body_velocity.width += 6;
    }

    if (body_velocity2.width > 0){
        body_velocity2.width -= 6;
    }
    if (body_velocity2.width < 0){
        body_velocity2.width += 6;
    }


    //Setting body rotation to be a fraction of velocity

    body_rotation = body_velocity.width/10;
    body_rotation2 = body_velocity2.width/10;

    //Limiting rotation when on the ground, so they aren't able to spin around on the ground

    if(body_rotation > 89 && body_pos.y >= floor_height){
        body_rotation = 89;
    }

    if(body_rotation < -89 && body_pos.y >= floor_height){
        body_rotation = -89;
    }

    if(body_rotation2 > 89 && body_pos2.y >= floor_height){
        body_rotation2 = 89;
    }

    if(body_rotation2 < -89 && body_pos2.y >= floor_height){
        body_rotation2 = -89;
    }

    //Setting up boundaries

    if(body_pos.x <= 0){
        body_pos.x += 5;
        body_velocity.width = -0.25*body_velocity.width;
    }

    if(body_pos.x >= 1500-body_dims.width){
        body_pos.x -= 5;
        body_velocity.width = -0.25*body_velocity.width;
    }

    if(body_pos2.x <= 0){
        body_pos2.x += 5;
        body_velocity2.width = -0.25*body_velocity2.width;
    }

    if(body_pos2.x >= 1500-body_dims2.width){
        body_pos2.x -= 5;
        body_velocity2.width = -0.25*body_velocity2.width;
    }




    //Initializing body rects for the players and their arms, this allows collides to check id they will collide in the next frame
    //naming scheme is the same as rest of code, the first player is odd numbers, and the second player is even numbers
    //3 and 4 used to create the arm rects

    body_rect = my_rectangle({float((body_pos.x + body_velocity.width*dt) + (body_dims.width+2)/2),float((body_pos.y + body_velocity.height*dt) + (body_dims.height+2)/2)},
                             body_rotation,body_dims);

    body_rect2 = my_rectangle({float((body_pos2.x + body_velocity2.width*dt) + (body_dims2.width+2)/2),float((body_pos2.y + body_velocity2.height*dt) +(body_dims2.height+2)/2)},
                              body_rotation2,body_dims2);

    body_rect3 = my_rectangle({float((arm_pos.x + body_velocity.width*dt) + (arm_dims.width+2)/2),float((arm_pos.y + body_velocity.height*dt) + (arm_dims.height+2)/2)},
                             arm_rotation,arm_dims);

    arm_rect = my_rectangle({body_rect.top_left.width,body_rect.top_left.height + 25},
                            {body_rect.top_right.width,body_rect.top_right.height + 25},
                            body_rect3.bottom_left,
                            body_rect3.bottom_right);

    body_rect4 = my_rectangle({float((arm_pos2.x + body_velocity2.width*dt) + (arm_dims2.width+2)/2),float((arm_pos2.y + body_velocity2.height*dt) + (arm_dims2.height+2)/2)},
                              arm_rotation2,arm_dims2);

    arm_rect2 = my_rectangle({body_rect2.top_left.width,body_rect2.top_left.height + 25},
                             {body_rect2.top_right.width,body_rect2.top_right.height + 25},
                            body_rect4.bottom_left,
                            body_rect4.bottom_right);


    //Checking for collisions between two bodies, and their arms with the opponent's body

    if (collide(body_rect,body_rect2)){



        ge211::geometry::Dims<int> temp = body_velocity2;

        body_velocity2 = -1 * body_velocity2 + 0.5*body_velocity;
        body_velocity = -1 * body_velocity + 0.5*temp;



        colliding = true;
    }
    else {
        colliding = false;
    }

    if (collide(body_rect2,arm_rect)){


        ge211::geometry::Dims<float> dir = arm_rect.top_right - arm_rect.bottom_right;
        ge211::geometry::Dims<float> norm = {dir.height,-1*dir.width};
        norm = norm/sqrtf(norm.width*norm.width + norm.height*norm.height);

        int n = 1;

        if(body_right){
            n = -1;
        }

        body_velocity2 += {int(norm.width * 150),int(norm.height * 75 * n)};



        colliding = true;


    }
    else {
        colliding = false;
    }

    if (collide(body_rect,arm_rect2)){


        ge211::geometry::Dims<float> dir = arm_rect2.top_right - arm_rect2.bottom_right;
        ge211::geometry::Dims<float> norm = {dir.height,-1*dir.width};
        norm = norm/sqrtf(norm.width*norm.width + norm.height*norm.height);

        int n = 1;

        if(body_right2){
            n = -1;
        }

        body_velocity += {int(norm.width * 150),int(norm.height * 75 * n)};



        colliding = true;


    }
    else {
        colliding = false;
    }

    //Checking for collisions with ring walls

    if (collide(body_rect,left_wall) || collide(body_rect,right_wall)) {

        body_velocity = -0.25 * body_velocity;

        if (body_pos.y < floor_height){
            body_velocity += {0,-50};
        }

        body_pos = {float(body_pos.x + body_velocity.width * 0.1),float(body_pos.y + body_velocity.height * 0.1)};


    }

    if (collide(body_rect2,left_wall) || collide(body_rect2,right_wall)) {

        body_velocity2 = -0.25 * body_velocity2;

        if (body_pos2.y < floor_height){
            body_velocity2 += {0,-50};
        }
        body_pos2 = {float(body_pos2.x + body_velocity2.width * 0.1),float(body_pos2.y + body_velocity2.height * 0.1)};

    }





    // Updating Positions


    body_pos.x += dt*body_velocity.width;
    body_pos2.x += dt*body_velocity2.width;

    body_pos.y += dt * body_velocity.height;
    body_pos2.y += dt * body_velocity2.height;

    arm_pos.x = body_pos.x + arm_dims.width/2;
    arm_pos.y = body_pos.y - arm_dims.height/2;

    arm_pos2.x = body_pos2.x + arm_dims2.width/2;
    arm_pos2.y = body_pos2.y - arm_dims2.height/2;


    //Cleaning up velocities, sometimes they start drifting

    if (body_velocity.width < 6 && body_velocity.width > -6){
        body_velocity.width = 0;
    }

    if (body_velocity2.width < 6 && body_velocity2.width > -6){
        body_velocity2.width = 0;
    }

    //Check if player falls into void, if so respawn them and increment scores

    if (body_pos.y > 650){
        score2 += 1;
        body_velocity = {0,0};
        body_pos = {400,-200};
    }

    if (body_pos2.y > 650){
        score1 += 1;
        body_velocity2 = {0,0};
        body_pos2 = {1000,-200};
    }

    end();

}



