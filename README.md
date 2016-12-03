# project1-shell
# By Arvind Mahankali, Brandon Huang and Will Ostlund

Features
- All of the critera listed on the (website)[http://www.stuycs.org/courses/mks65/dw/projects/project1gettingoutofyourshell]
    - It is important to note that out program will accept multiple pipes and can be redirected multiple times
    - We parse the user's input as to not restrict the amount of whitespace the can be add
        - We had to parse differently when the echo function is called
- Our shell prints the current path before the user enter input
- We added comment (###) to our terminal
- Typing in "cd" or "cd ~" will redirect the user to root

Attempts
- We attempted to replace fgets() with readline() as to allow autocompletion and usage of the arrow keys however, we started too late and we didn't want to risk any problems that could arise.
- We wanted to implement other forms of redirection (>>, <<, etc.) however, we had trouble implementing basic redirection and ran out of time

Functions
-In main.c
    main(): Starts by clearing the terminal and immediately 
    redirects to route. From there, it prints out the current 
    directory and asks for user input. It records this 
    information using the fgets function then uses the strsep
    function to form an array of semicolon divided sections of
    the input. The program loops through the array executing
    passing in each part of the input to the run function 
    (located in pipe.h)
        -Parameters: none
        -Returns: an integer to terminate the function
-In pipe.c
