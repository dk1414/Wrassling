#pragma once

#include <ge211.hxx>


struct my_rectangle {

    ge211::geometry::Dims<float> top_left;
    ge211::geometry::Dims<float> top_right;
    ge211::geometry::Dims<float> bottom_left;
    ge211::geometry::Dims<float> bottom_right;


    my_rectangle(ge211::geometry::Dims<float> center, double angle,ge211::geometry::Dims<int> dims);
    my_rectangle(ge211::geometry::Dims<float> top_left,ge211::geometry::Dims<float> top_right,ge211::geometry::Dims<float> bottom_left,
                 ge211::geometry::Dims<float> bottom_right);

    std::vector<ge211::geometry::Dims<float>> get_all(void);




};


class Model
{

private:
    ge211::geometry::Posn<float> body_pos;
    ge211::geometry::Posn<float> arm_pos;
    ge211::geometry::Posn<float> body_pos2;
    ge211::geometry::Posn<float> arm_pos2;
    ge211::geometry::Dims<int> arm_dims;
    ge211::geometry::Dims<int> body_dims;
    ge211::geometry::Dims<int> arm_dims2;
    ge211::geometry::Dims<int> body_dims2;

    ge211::geometry::Dims<int> body_velocity;
    ge211::geometry::Dims<int> body_velocity2;


    double arm_rotation;
    double body_rotation;
    double arm_rotation2;
    double body_rotation2;

    int gravity;
    int floor_height;

    int score1;
    int score2;

    struct my_rectangle body_rect;
    struct my_rectangle body_rect2;
    struct my_rectangle body_rect3;
    struct my_rectangle arm_rect;
    struct my_rectangle body_rect4;
    struct my_rectangle arm_rect2;

    struct my_rectangle left_wall;
    struct my_rectangle right_wall;

    bool colliding;
    bool body_right;
    bool body_right2;

    bool menu;
    int winner;




public:

    Model();

    void on_frame(double dt);

    bool collide(my_rectangle box1, my_rectangle box2);
    bool collide_helper(my_rectangle box1,my_rectangle box2,ge211::geometry::Dims<float> axis);

    float dot(ge211::geometry::Dims<float> v1,ge211::geometry::Dims<float> v2);

    bool in_ring(ge211::geometry::Posn<float> pos);

    void end(void);

    ge211::geometry::Posn<float> get_body1(void) const;
    ge211::geometry::Posn<float> get_body2(void) const;
    ge211::geometry::Dims<int> get_armdims1(void) const;
    ge211::geometry::Dims<int> get_armdims2(void) const;

    struct my_rectangle get_armrect1(void) const;
    struct my_rectangle get_armrect2(void) const;

    double get_body_rot1(void) const;
    double get_body_rot2(void) const;
    double get_arm_rot1(void) const;
    double get_arm_rot2(void) const;

    bool get_right1(void) const;
    bool get_right2(void) const;

    int get_score1(void) const;
    int get_score2(void) const;

    int get_winner(void) const;

    bool get_menu(void) const;
    int get_floor(void) const;

    ge211::geometry::Dims<int> get_v1(void) const;


    void inc_body_v1(ge211::geometry::Dims<int> i);
    void inc_body_v2(ge211::geometry::Dims<int> i);
    void set_body_pos1(ge211::geometry::Posn<float> i);
    void set_body_pos2(ge211::geometry::Posn<float> i);
    void inc_arm_rot1(int i);
    void inc_arm_rot2(int i);
    void set_right1(bool b);
    void set_right2(bool b);
    void set_menu(bool b);










};




