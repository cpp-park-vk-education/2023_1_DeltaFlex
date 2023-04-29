#include <DFInputSystem.hpp>

#include <SDL2/SDL_events.h>

bool DFInputSystem::keys_up[290] = { 0 };
bool DFInputSystem::keys_down[290] = { 0 };
bool DFInputSystem::keys_active[290] = { 0 };

uint32_t DFInputSystem::mouse_up = 0;
uint32_t DFInputSystem::mouse_down = 0;
uint32_t DFInputSystem::mouse_active = 0;

int DFInputSystem::mouse_x = 0;
int DFInputSystem::mouse_y = 0;

void DFInputSystem::InputSystemOnFrameStart()
{
    SDL_GetMouseState(&mouse_x, &mouse_y);
    mouse_down = 0;
    mouse_up = 0;
    for (size_t i = 0; i < sizeof(keys_down) / sizeof(bool); ++i)
    {
        keys_down[i] = false;
        keys_up[i] = false;
    }
}

void DFInputSystem::InputSystemOnKeyboardEvent(SDL_KeyboardEvent &event)
{
    size_t key_code = (size_t)event.keysym.scancode;
    // if (key_code)
    // {
    //     // KEYCODE_LSHIFT
    //     std::cout << key_code << " " << (size_t)event->keysym.mod << "\n";
    //     return;
    // }
    switch (event.type)
    {
        case SDL_KEYUP:
        {
            keys_up[key_code] = true;
            keys_active[key_code] = false;
        } break;
        case SDL_KEYDOWN:
        {
            keys_down[key_code] = !keys_active[key_code];
            keys_active[key_code] = true;
        } break;

        default:
            break;
    }
}

void DFInputSystem::InputSystemOnMouseDown(SDL_MouseButtonEvent &event)
{
    mouse_down |= (1 << event.button);
    mouse_active |= (1 << event.button);
}

void DFInputSystem::InputSystemOnMouseUp(SDL_MouseButtonEvent &event)
{
    mouse_up |= (1 << event.button);
    mouse_active &= ~(1 << event.button);
}

void DFInputSystem::InputSystemOnFrameEnd()
{

}

bool DFInputSystem::GetKey(KeyCode code)
{
    return keys_active[(size_t)code];
}

bool DFInputSystem::GetKeyDown(KeyCode code)
{
    return keys_down[(size_t)code];
}

bool DFInputSystem::GetKeyUp(KeyCode code)
{
    return keys_up[(size_t)code];
}

float DFInputSystem::GetAxis(AxisCode axis)
{
    float res;
    switch (axis)
    {
        case AXIS_HORIZONTAL:
            res = (keys_active[KEYCODE_D] | keys_active[KEYCODE_RIGHT]) - (keys_active[KEYCODE_A] | keys_active[KEYCODE_LEFT]);
            break;

        case AXIS_VERTICAL:
            res = (keys_active[KEYCODE_S] | keys_active[KEYCODE_DOWN]) - (keys_active[KEYCODE_W] | keys_active[KEYCODE_UP]);
            break;

        default:
            res = 0;
            break;
    }
    return res;
}
// float GetAxisRaw(AxisCode axis);