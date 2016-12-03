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

Bugs
-After thorough testing, none that we know of

Functions

In main.c
    main(): 
    Starts by clearing the terminal and immediately 
    redirects to route. From there, it prints out the current 
    directory and asks for user input. It records this 
    information using the fgets function then uses the strsep
    function to form an array of semicolon divided sections of
    the input. The program loops through the array executing
    passing in each part of the input to the run function 
    (located in pipe.h)
        -Parameters: none
        -Returns: an integer to terminate the function

noAdjSymbol(char* command): 
    The goal of this function is to
    catch syntax errors that arise from redirection and piping. If
    there is a "|" character at the beginning of the string provided
    in the command line, or if there is a ">" or "<" character directly
    before a "|" character in the provided string, this function will
    return -1. This is done by splitting the given command by spaces.
    main() then uses this function to determine if the given command
    string has a syntax error of this type.
        -Parameters: char* command
        -Returns: an integer: returns -1 if the given string contains
        a syntax error of the form above, and 0 otherwise.
        
-In pipe.c
    
void print(char* a[], int length): 
    prints out the contents 
    of a given array
        - Parameters:
            - a is the array
            - length is the number of elements in a
        - Returns:
            - nothing
    
int piper(char *a): 
    Parses the given string by the '|'
    character and proceeds to check for notable exceptions. 
    If there are none then the program forks, redirects in the
    child process and reverts back in the parent process.
        - Parameters:
            - a, a string to parse
        - Returns:
            - An integer to terminate the function

int run(char *a):
    
    We implemented redirection by separating the command string by spaces, then
    scanning through the string. Each time we encountered a ">", we used dup2 to
    make the file descriptor 1 point to the file descriptor of the following token,
    which was the name of a file. Similarly, each time we encountered a "<", we used
    dup2 to make the file descriptor 0 point to the file descriptor of the following
    token. At the end of the scan, the files that the file descriptors 0 and 1 point
    to will be decided. Finally, we used execvp to execute the given commands after
    accounting for the ">" and "<" symbols.
        - Parameters: 
            - char* a, the command
        - Returns:
            - An integer, terminating the function.

