#include "menu.hpp"
#include <iostream>

Textbox::Textbox(SDL_Color _text_color, std::string _text_string, SDL_Rect _text_rect, int font_size, std::string _font_path)
{   
    font = TTF_OpenFont(_font_path.c_str(), font_size);
    background_rect = {0, 0, 100, 100};
    text_rect = _text_rect;
    text_color = _text_color;
    text_string = _text_string;
    load_text_texture();
}

Textbox::~Textbox() {
    text_texture.free();
}

void Textbox::update_text(std::string new_text)
{
    text_string = new_text;
    load_text_texture();
}

void Textbox::load_text_texture()
{
    if(font == NULL) {
        std::cout << "Error loading font";
    }
    text_texture.loadFromRenderedText(gRenderer, font, text_string, text_color);
}

void Textbox::render_text_box()
{
    text_texture.render(gRenderer, text_rect.x, text_rect.y, NULL, &text_rect);
}

Button::Button(std::string _button_name, SDL_Rect _button_rect) {
    button_name = _button_name;
    button_rect = _button_rect;

    //The text rect is smaller than the button rect so that the text is inside the button
    SDL_Rect text_rect = {button_rect.x + 10, button_rect.y + 10, button_rect.w - 20, button_rect.h - 20};
    button_textbox = new Textbox(WHITE_COLOR, button_name, text_rect, 25, "res/fonts/Southern.ttf");
    load_texture();
}

bool Button::is_pressed(int mouse_x, int mouse_y) {
    return mouse_x >= button_rect.x && mouse_x <= button_rect.x + button_rect.w
        && mouse_y >= button_rect.y && mouse_y <= button_rect.y + button_rect.h;
}

void Button::load_texture() {
    button_texture.loadFromFile(gRenderer, "res/images/button_0.png");
    std::cout << "Button texture loaded" << std::endl;
}

void Button::render() {
    button_texture.render(gRenderer, button_rect.x, button_rect.y, NULL, &button_rect);
    button_textbox->render_text_box();
}