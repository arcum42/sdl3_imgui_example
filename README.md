This is a simple example project using imgui with SDL 3. At the time of writing, SDL 3 is a preview release, so if it has officially released and this isn't compiling, something may have changed. I'll try to remember to go back and fix this if that happens.

A fair amount was copied from the example in imgui's examples, but it's more useful for me to have an actual project set up that uses it with cmake that I can copy and base new projects on, and I'm making it public so other people can use it as well.

I've gone and made this C++20 with modules, simply because it's getting more feasible to do so, and I'd like some experience using them. Everything I've got in modules at the moment should be fairly trivial to change over to non modules (or reimplemented, really).