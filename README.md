# BASHFUL

a shell except it's shelldon from big bang theory (bazinga)

# FEATURES

Arbitrary command execution, plus cd and exit.

Semicolons to sequentially execute a number of commands from a single input line.

Redirection (< or > [or rather (uwu) (>o<) (owo)]) and piping (|).

Ampersands at the end of a line will allow the command to run in the background.

Double quotes allow you to include spaces within arguments passed into.

Left and right arrow allow you to navigate backwards and forwards within the text that you have in order to insert text in the middle of what you've already typed.

Up and down arrow allow you to navigate backwards and forwards through what has been previously entered.

# ALMOST FEATURES



# WE PRETEND THESE ARE FEATURES

Holding the horizontal arrow keys for long enough can mess up the position in which the cursor appears (although this has no effect on the way text is inserted). Sometimes holding the horizontal arrow keys causes a character that is supposed to be escaped to be printed, although I don't think the root cause of this is really in our program, and this should be rectified upon any new keyboard input.

When the input reaches at least 2 lines long, on any new keyboard input, all but the last line of the input will stay and a new copy of the prompt and the whole input will be printed starting from the bottom line. 

Various other visual glitches (that also glitch bash so we feel no need to list them here).

All of the bugs that we listed above are simply aesthetic bugs, and don't modify at all the actual input.

One strange bug is that after pressing the down arrow once, you have to press the up arrow twice to go up once. But after the up arrow is pressed twice, it goes back to normal where one up = one navigation.

Also having to do with vertical arrrows, a blank line with nothing on it prevents our shell from being able to continue using the down arrow through it, but the up arrow works fine. This can cause you to get "stuck" above a certain blank lines, and you'd have to press enter to reset it.

# CONJUNCTION JUNCTION?

What in truth is your function?

Dost thou hooketh up yon words, yon phrases and clauses?
