#include "controller.hxx"

Controller::Controller()
        : view_(model_,mixer()),
          w_pressed(false),
          d_pressed(false),
          a_pressed(false),
          space_pressed(false),
          i_pressed(false),
          l_pressed(false),
          j_pressed(false),
          n_pressed(false)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set,initial_window_dimensions());
}

void
Controller::on_frame(double dt)
{

    if (!(model_.get_menu())) {

        if (w_pressed) {

            if (model_.get_body1().y > model_.get_floor() && model_.in_ring(model_.get_body1())) {

                model_.inc_body_v1({0,-500});

                model_.set_body_pos1({model_.get_body1().x, model_.get_body1().y -10});
            }
        }
        if (d_pressed) {

            model_.inc_body_v1({12,0});

            model_.set_right1(true);
        }
        if (a_pressed) {

            model_.inc_body_v1({-12,0});

            model_.set_right1(false);
        }
        if (space_pressed) {

            if (model_.get_right1()) {

                model_.inc_arm_rot1(-10);
            } else {

                model_.inc_arm_rot1(10);
            }

        }

        if (i_pressed) {

            if (model_.get_body2().y > model_.get_floor() && model_.in_ring(model_.get_body2())) {

                model_.inc_body_v2({0,-500});

                model_.set_body_pos2({model_.get_body2().x, model_.get_body2().y -10});

            }
        }
        if (l_pressed) {

            model_.inc_body_v2({12,0});

            model_.set_right2(true);
        }
        if (j_pressed) {

            model_.inc_body_v2({-12,0});

            model_.set_right2(false);
        }
        if (n_pressed) {

            if (model_.get_right2()) {

                model_.inc_arm_rot2(-10);
            } else {

                model_.inc_arm_rot2(10);
            }

        }
    }


    model_.on_frame(dt);
}


void
Controller::on_key_down(ge211::Key key)
{


    if (key == ge211::Key::code('w')) {
        w_pressed = true;
    }
    if (key == ge211::Key::code('d')) {
        d_pressed = true;
    }
    if (key == ge211::Key::code('a')) {
        a_pressed = true;
    }
    if (key == ge211::Key::code(' ')) {
        space_pressed = true;
    }

    if (key == ge211::Key::code('i')) {
        i_pressed = true;
    }
    if (key == ge211::Key::code('l')) {
        l_pressed = true;
    }
    if (key == ge211::Key::code('j')) {
        j_pressed = true;
    }
    if (key == ge211::Key::code('n')) {
        n_pressed = true;
    }


}

void
Controller::on_key_up(ge211::Key key)
{


    if (key == ge211::Key::code('w')) {
        w_pressed = false;
    }
    if (key == ge211::Key::code('d')) {
        d_pressed = false;
    }
    if (key == ge211::Key::code('a')) {
        a_pressed = false;
    }
    if (key == ge211::Key::code(' ')) {
        space_pressed = false;
    }

    if (key == ge211::Key::code('i')) {
        i_pressed = false;
    }
    if (key == ge211::Key::code('l')) {
        l_pressed = false;
    }
    if (key == ge211::Key::code('j')) {
        j_pressed = false;
    }
    if (key == ge211::Key::code('n')) {
        n_pressed = false;
    }


}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }

    if (key == ge211::Key::code('p')) {
        model_.set_menu(!(model_.get_menu()));
    }


}




ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return {1475,750};
}
