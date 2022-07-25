#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    ge211::Dims<int> initial_window_dimensions() const override;
    void on_frame(double dt) override;
    void on_key(ge211::Key) override;
    void on_key_down(ge211::Key) override;
    void on_key_up(ge211::Key) override;

private:
    Model model_;
    View view_;
    bool w_pressed;
    bool d_pressed;
    bool a_pressed;
    bool space_pressed;

    bool i_pressed;
    bool l_pressed;
    bool j_pressed;
    bool n_pressed;
};
