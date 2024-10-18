#include <SDL3/SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <cstdio>

int main(int argc, char *argv[])
{
    // Initialize SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window with title "Hello World"
    SDL_Window *win = SDL_CreateWindow("SDL 3 ImGUI Example", 1280, 720, 0);
    if (!win)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    // Setup SDL rendering context for ImGui
    int screenW, screenH;
    SDL_GetWindowSize(win, &screenW, &screenH);

    // Create a renderer
    SDL_Renderer *rend = SDL_CreateRenderer(win, NULL);
    if (!rend)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

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
    ImGui_ImplSDL3_InitForSDLRenderer(win, rend);
    ImGui_ImplSDLRenderer3_Init(rend);

    // Update the screen
    SDL_UpdateWindowSurface(win);

    // Begin ImGui main loop
    bool quit = false;
    bool demo = true;
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

            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(win))
                quit = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        if (demo)
            ImGui::ShowDemoWindow(&demo);

        // Create context for ImGui widgets
        static float globalCount = 0.0f;
        ImGui::Begin("Hello World");
        ImGui::Text("This is some useful text.");
        ImGui::SliderFloat("My Slider", &globalCount, 0.0f, 10.0f);
        if (ImGui::Button("Quit"))
        {
            quit = true;
        }
        ImGui::End();

        // Clear the window with a grey fill
        SDL_SetRenderDrawColor(rend, 128, 128, 128, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rend);

        // Rendering
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), rend);
        SDL_RenderPresent(rend);

        SDL_UpdateWindowSurface(win);

        // Wait for a key press before exiting
        SDL_Delay(1000 / 60);
    }

    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    // Quit SDL subsystems
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
