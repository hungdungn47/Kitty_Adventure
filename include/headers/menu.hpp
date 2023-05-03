#pragma once
#include "utils.hpp"
#include "constants.hpp"

class Textbox {
private:
    TTF_Font* font;
    SDL_Rect background_rect, text_rect;
    SDL_Color text_color;
    std::string text_string;
    LTexture text_texture;
public:
    Textbox(SDL_Color _text_color, std::string _text_string, SDL_Rect _text_rect, int font_size, std::string _font_path);
    ~Textbox();
    void update_text(std::string new_text);
    void load_text_texture();
    void render_text_box();
    SDL_Rect get_rect() {return text_rect;};
    std::string get_text() {return text_string;};
    SDL_Color get_color() {return text_color;};
};

class Button {
private:
    Textbox* button_textbox;
    SDL_Rect src_rect, button_rect;
    std::string button_name;
    LTexture button_texture;
public:
    Button() {}
    Button(std::string button_name, SDL_Rect _button_rect);
    void load_texture();
    bool is_pressed(int mouse_x, int mouse_y);
    void render();
};

// class Menu {
// private:
//     vector<Button*> buttons;
// public:
//     Menu() {}
//     Menu();
//     std::string get_pressed_button();
//     void render();
// }