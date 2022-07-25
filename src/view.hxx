#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model,ge211::Mixer& mixer);

    void draw(ge211::Sprite_set& set,ge211::Dims<int>);


private:
    Model const& model_;
    ge211::Image_sprite const image;
    ge211::Image_sprite const player_image;
    ge211::Image_sprite const player2_image;
    ge211::Image_sprite const arm_image;
    ge211::Image_sprite const arm2_image;
    ge211::Rectangle_sprite body;
    ge211::Rectangle_sprite arm;
    ge211::Circle_sprite circle;
    ge211::Music_track music;
};
