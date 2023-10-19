# Dragon Shell - drash

This is an embeddable command line interpreter.  It follows the basic rules of a POSIX shell but lets you define multiple "programs" within a single executable by defining them as functions in a list.  This is a pattern I've used several times in embedded products which run a large microcontroller with no high level operating system.  A shell like this hooked up to a UART makes a powerful way to configure and test your system.

# Including it in a project

There's not a lot of code in this project, just include the C files in your build and include the `inc` directory to allow you to integrate the shell.  If you're using CMake there's a package file, you need to specify the variable `${PROJ_NAME}` with the name of your executable and the C files and include paths will be added when you call `find_package`.  Take a look at the example project.

# Extending it

You can extend the list of commands without altering this library by defining the commands you want to call as functions with a standard C main function signature and then adding them to the `application_commands` array with a string which when matched as the first argument on the command line will cause the function to be called.  Take a look at the example project which adds a command "extend" to the shell.

# Example project

In the `example` folder there is an example CMake project that will make a program "drash\_demo" on a Linux machine that you can run as an interactive shell.  Once you've cloned this repo you can build and run the demo by following the steps

    cd example
    mkdir build
    cd build
    cmake ..
    make -j5

Most of the code in the demo main function is setting up the Stdin file to be in non-canonical mode which means the code gets every keypress including backspace and cursor keys.  If you're using this code in an embedded system that has a hardware UART then you're probably already in non-canonical mode.
