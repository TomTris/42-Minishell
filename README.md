Hi everyone. Welcome to my beautiful Shell, mimic 5.2.

This is a 42-Project to get to know Bash and transform your skill, logic to real product!!
This is my first big project and because of some reasons, i did it solo. So, for me, it's very meaningfull when it's not a trash-project.

In this Minishell, there are several things that i didn't implement.

>| , <>,    2>file.txt or unset with options.
They are not worth to do in this minishell, so i don't implemment them.
But, many many many many many many other owesome things i implemented!

It works as a Bash 5.2.
Really mimic, really similar. TRy anything that you can figure out. Syntax, ambigious, redirections.
combination of expansion, << $"" or << $ or << $$ or < $"a     b"*       or echo "a      f"* or export a="b      a         f" && echo $a*.
also you call env -i ./minishell from bash. No env? i hardcore the Path =)). You can check in function make env
My Shell is very beautiful. Enjoy it.


Enjoy it !!!!

There are something, which are not similar, i will say below.
1. Expand of $ with number, with * or with $.
Such cases are not a part of

• Handle environment variables ($ followed by a sequence of characters) whichshould expand to their values.
• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

$$ expands to PID, $2 $* $1 $0 has other meaning "https://www.rackspace.com/blog/fundamentals-shell-scripting#:~:text=%24%23%20%2D%20To%20check%20count%[…]tring%20treated%20as%20separate%20arguments"
So, because we handle only $? and enviroment variables, if $bla , bla is not a valid name, it will not expand it and consider number or * just as a usual character such as . / +, but not ' or "
It's great if you can understand what you are doing!

< > << >>: handled very good. 1 case, Limiter can't not store more than (at this school) 512 bytes because i store them in pipes instead of file, so that i can store many limiters as i want,
in correct order, put them into correct place, correct part.

cd - also handle -, --. cd ~ - a volunteer bonus.
But, ~ will not expand to HOME. I just handle it only when it's in cd and we have cd ~.
If you write ~, it's just said "~: command not found" instead of "/User/qdo: Is a directory" 

export, unset multiple args, export += works.
unset - or unset -- just means that, unset, because they are not valid names and we are not supposed to handle options.

env - it will update SHLVL. If doesn't exit => new shell has shlvl = shlvl + 1. If doesn't exit or <0 -> SHLVL = 0.  It update _= in the env correctly
(expands only to the last args of the previous cmds (bash 5.2). You can check by create a test.c and a.out file, which will print the env that it gets. Then you can check this part).

My bash still works when you call env -i bash
but in Bash, env is not builtin, so, env when you call in my shell, it will be _=env. You can try when you unset PATH.
Shell and MAc...... I think it has other layor or software to store things like HOME, PWD, or PATH. Kind of.

Anyway, i did it very carefullyy in about 2.5-3 weeks with about 250 - 300 hours. Enjoy!
