#include "view.hxx"

static ge211::Color const circle_color {100, 100, 100};
static ge211::Transform platform_t;
ge211::Text_sprite score1;
ge211::Text_sprite score2;
ge211::Image_sprite logo("wrassling_logo.png");
ge211::Image_sprite crown("crown.png");
ge211::Image_sprite controls1("controls1.png");
ge211::Image_sprite controls2("controls2.png");
ge211::Text_sprite menu_message;
ge211::Text_sprite quit_message;
ge211::Text_sprite win_message;



View::View(Model const& model,ge211::Mixer& mixer)
        : model_(model),
          image("ring.png"),
          player_image("player1.png"),
          player2_image("player2.png"),
          arm_image("arm1.png"),
          arm2_image("arm2.png"),
          body({20,100},{100,100,200}),
          arm(model_.get_armdims1(),{50,50,80}),
          circle(5,circle_color),
          music("music.mp3",mixer)

{
    mixer.play_music(music,true);
}

void
View::draw(ge211::Sprite_set& set,ge211::Dims<int> init_dims)
{
    ge211::Font pixel{"pixel.ttf",75};
    ge211::Font pixel_medium{"pixel.ttf",40};
    ge211::Font pixel_small{"pixel.ttf",15};

    //wrassling logo

    set.add_sprite(logo,{500,50},1);


    //menu

    if (model_.get_menu()){

        set.add_sprite(controls1,{200,100},5);
        set.add_sprite(controls2,{1100,100},5);

        ge211::Text_sprite::Builder msg_builder(pixel_medium);
        msg_builder.add_message("Press P to Start");
        msg_builder.color(ge211::Color::white());
        menu_message.reconfigure(msg_builder);
        set.add_sprite(menu_message,{550,200},1);

        msg_builder.message("Press Q to Quit");
        quit_message.reconfigure(msg_builder);
        set.add_sprite(quit_message,{560,275},1);



    }else{
        //score sprites


        ge211::Text_sprite::Builder score1_builder(pixel);
        score1_builder.add_message(model_.get_score1());
        score1_builder.color(ge211::Color::white());
        score1.reconfigure(score1_builder);
        set.add_sprite(score1,{200,100},1);

        ge211::Text_sprite::Builder score2_builder(pixel);
        score2_builder.add_message(model_.get_score2());
        score2_builder.color(ge211::Color::white());
        score2.reconfigure(score2_builder);
        set.add_sprite(score2,{init_dims.width - 275,100},1);



    }




    static ge211::Rectangle_sprite background(init_dims,ge211::Color(15,0,26));
    set.add_sprite(background,{0,0},0);


    static ge211::Transform arm_t;
    static ge211::Transform body_t;

    static ge211::Transform arm_t2;
    static ge211::Transform body_t2;





    arm_t.set_rotation(model_.get_arm_rot1());
    body_t.set_rotation(model_.get_body_rot1());
    body_t.set_flip_h(false);

    if (!(model_.get_right1())){
        body_t.set_flip_h(true);
    }


    arm_t2.set_rotation(model_.get_arm_rot2());
    body_t2.set_rotation(model_.get_body_rot2());
    body_t2.set_flip_h(false);

    if (!(model_.get_right2())){
        body_t2.set_flip_h(true);
    }

    platform_t.set_scale(2);
    platform_t.set_scale_y(1);


    set.add_sprite(image, {275,400},1,platform_t);

    set.add_sprite(player_image,{int(model_.get_body1().x),int(model_.get_body1().y)},3,body_t);
    set.add_sprite(arm_image,{int(model_.get_armrect1().top_left.width + model_.get_armdims1().width/2),int(model_.get_armrect1().top_left.height - model_.get_armdims1().height/2)},4,arm_t);

    set.add_sprite(player2_image,{int(model_.get_body2().x),int(model_.get_body2().y)},3,body_t2);
    set.add_sprite(arm2_image,{int(model_.get_armrect2().top_left.width + model_.get_armdims2().width/2),int(model_.get_armrect2().top_left.height - model_.get_armdims2().height/2)},4,arm_t2);


    if(model_.get_winner() != 0){
        set.add_sprite(background,{0,0},6);

        ge211::Text_sprite::Builder winner_builder(pixel);
        winner_builder.add_message("WINNER!");
        winner_builder.color(ge211::Color::white());
        win_message.reconfigure(winner_builder);
        set.add_sprite(win_message,{550,200},7);

        ge211::Transform crown_t;
        crown_t.set_scale(2.5);
        set.add_sprite(crown,{627,315},8,crown_t);

        if(model_.get_winner() == 1){
            body_t.set_scale(2);
            body_t.set_rotation(0);
            set.add_sprite(player_image,{660,400},7,body_t);
        }else{
            body_t2.set_scale(2);
            body_t2.set_rotation(0);
            set.add_sprite(player2_image,{660,400},7,body_t2);
        }
    }


    //These show the collisions boxes, used for previous testing

    //set.add_sprite(body, {int(model_.body_pos.x),int(model_.body_pos.y)},1,body_t);
    //set.add_sprite(arm,{int(model_.arm_pos.x),int(model_.arm_pos.y)},2,arm_t);

    //set.add_sprite(body, {int(model_.body_pos2.x),int(model_.body_pos2.y)},1,body_t2);
    //set.add_sprite(arm,{int(model_.arm_pos2.x),int(model_.arm_pos2.y)},2,arm_t2);


    //set.add_sprite(circle,{int(model_.body_rect.top_left.width),int(model_.body_rect.top_left.height)},3);
    //set.add_sprite(circle,{int(model_.body_rect.top_right.width),int(model_.body_rect.top_right.height)},3);
    //set.add_sprite(circle,{int(model_.body_rect.bottom_right.width),int(model_.body_rect.bottom_right.height)},3);
    //set.add_sprite(circle,{int(model_.body_rect.bottom_left.width),int(model_.body_rect.bottom_left.height)},3);

    //set.add_sprite(circle,{int(model_.arm_rect.top_left.width),int(model_.arm_rect.top_left.height)},3);
    //set.add_sprite(circle,{int(model_.arm_rect.top_right.width),int(model_.arm_rect.top_right.height)},3);
    //set.add_sprite(circle,{int(model_.arm_rect.bottom_right.width),int(model_.arm_rect.bottom_right.height)},3);
    //set.add_sprite(circle,{int(model_.arm_rect.bottom_left.width),int(model_.arm_rect.bottom_left.height)},3);



}

