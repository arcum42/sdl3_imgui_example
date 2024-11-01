#include <SDL3/SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <cstdio>
#include <format>
#include <string>

import imgui_wrap;
import imgui_sdl3_wrap;
import log;

bool quit = false;

SDL_Window *main_window = nullptr;
SDL_Renderer *main_renderer = nullptr;

void draw_content()
{
    static bool show_demo = true;
    static bool show_log = true;

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Windows"))
        {
            if (ImGui::MenuItem("Demo", "", &show_demo))
            {
                if (!show_demo)
                    log::writeln("Hiding Demo Window");
                else
                    log::writeln("Showing Demo Window");
            }
            if (ImGui::MenuItem("Log", "", &show_log))
            {
                if (!show_log)
                    log::writeln("Hiding Log Window");
                else
                    log::writeln("Showing Log Window");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Just for testing.
    if (show_demo)
        ImGui::ShowDemoWindow(&show_demo);

    if (show_log)
        log::draw();
}

bool init_sdl()
{
    // Initialize SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    // Create a window.
    main_window = SDL_CreateWindow("SDL 3 ImGui Example", 1280, 720, 0);
    if (!main_window)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    // Create a renderer
    main_renderer = SDL_CreateRenderer(main_window, NULL);
    if (!main_renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void init_imgui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_Wrap::Init(main_window, main_renderer);
}

int main(int argc, char *argv[])
{
    // Initialize SDL 3.
    if (!init_sdl())
        return 1;

    init_imgui();

    // Update the screen
    SDL_UpdateWindowSurface(main_window);

    log::writeln("Hello, World!");
    log::writeln("Text.");

    // Begin ImGui main loop
    while (!quit)
    {
        // Process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Handle SDL events
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                quit = true;

            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(main_window))
                quit = true;
        }

        // Start the Dear ImGui frame
        ImGui_Wrap::NewFrame();

        draw_content();

        // Clear the window with a grey fill
        SDL_SetRenderDrawColor(main_renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(main_renderer);

        // Rendering
        ImGui_Wrap::Render(main_renderer);
        SDL_RenderPresent(main_renderer);

        SDL_UpdateWindowSurface(main_window);

        // Wait for a key press before exiting
        SDL_Delay(1000 / 60);
    }

    // Cleanup
    ImGui_Wrap::Shutdown();

    // Quit SDL subsystems
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();

    return 0;
}
