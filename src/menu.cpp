#include "menu.hpp"
#include "SDL_mixer_functions.hpp"
#include <iostream>

Textbox::Textbox(SDL_Color _text_color, std::string _text_string, int x, int y, int font_size, std::string _font_path)
{   
    font = TTF_OpenFont(_font_path.c_str(), font_size);
    text_color = _text_color;
    text_string = _text_string;
    load_text_texture();
    text_rect = {x, y, text_texture.getWidth(), text_texture.getHeight()};
    std::cout << text_string << ": " << text_rect.x << " " << text_rect.y << " " << text_rect.w << " " << text_rect.h << std::endl;
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
    text_texture.render(gRenderer, text_rect.x, text_rect.y);
}

void Textbox::render_center() {
    text_texture.render(gRenderer, SCREEN_WIDTH / 2 - text_rect.w / 2, text_rect.y);
}

Button::Button(std::string _button_name, int x, int y) { 
    button_name = _button_name;

    //The text rect is a bit smaller than the button rect so that the text is inside the button
    //SDL_Rect text_rect = {button_rect.x + 20, button_rect.y + 20, button_rect.w - 40, button_rect.h - 40};
    button_textbox = new Textbox(WHITE_COLOR, button_name, x, y, 50, southern_font);
    hovering_textbox = new Textbox(GREEN_COLOR, button_name, x, y, 50, southern_font);

    text_rect = button_textbox->get_rect();
    button_rect = {text_rect.x - 20, text_rect.y - 20, text_rect.w + 40, text_rect.h + 40};
    load_texture();
}

bool Button::is_pressed(int mouse_x, int mouse_y) {
    if(is_mouse_over(mouse_x, mouse_y)) {
            Mix_PlayChannel(-1, button_select_sound, 0);
            return true;
        }
    return false;
}

bool Button::is_mouse_over(int mouse_x, int mouse_y) {
    return mouse_x >= button_rect.x && mouse_x <= button_rect.x + button_rect.w
        && mouse_y >= button_rect.y && mouse_y <= button_rect.y + button_rect.h;
}

void Button::load_texture() {
    button_texture.loadFromFile(gRenderer, "res/images/button_0.png");
}

void Button::render(int mouseX, int mouseY) {
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
    SDL_RenderDrawRect(gRenderer, &button_rect);

    if(is_mouse_over(mouseX, mouseY)) {
        button_texture.render(gRenderer, button_rect.x, button_rect.y, NULL, &button_rect);
        hovering_textbox->render_text_box();
    } else {
        button_texture.render(gRenderer, button_rect.x, button_rect.y, NULL, &button_rect);
        button_textbox->render_text_box();
    }
}