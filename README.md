# BASHFUL

a shell except it's shelldon from big bang theory (bazinga)

# FEATURES

Arbitrary command execution, plus cd and exit.

Semicolons to sequentially execute a number of commands from a single input line.

Redirection (>,<) and piping (|). Also added: >> to redirect stdout to append to a file, and 2> or 2>> to redirect stderr.

Ampersands at the end of a line will allow the command to run in the background.

Double quotes allow you to treat the enclosed text as one argument, including spaces.

Left and right arrow allow you to navigate backwards and forwards within the text that you have in order to insert text in the middle of what you've already typed.

Up and down arrow allow you to navigate backwards and forwards through the command history, stored in /home/USER/.shellhistory

Tab autocompletes commands for the first argument, and file/directory for all subsequent arguments.

# ALMOST FEATURES

We tried to add better tab autocompletion.

We were going to add ampersand redirects but we decided against it.

# WE PRETEND THESE ARE FEATURES

Holding the horizontal arrow keys for long enough can mess up the position in which the cursor appears (although this has no effect on the way text is inserted). The visual bug should go away after a backspace is pressed.

When the input reaches at least 2 lines long, on any new keyboard input, all but the last line of the input will stay and a new copy of the prompt and the whole input will be printed starting from the bottom line. 

Various other visual glitches (that also glitch bash so we feel no need to list them here).

All of the bugs that we listed above are simply aesthetic bugs, and don't modify at all the actual input.

# CONJUNCTION JUNCTION?

What in truth is your function?

Dost thou hooketh up yon words, yon phrases and clauses?
