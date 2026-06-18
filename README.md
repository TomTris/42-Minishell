# minishell

A small reimplementation of **bash 5.2** in pure C — a 42 project. Done solo over ~2.5–3 weeks. Mandatory and bonus parts both implemented. Score: 125/125.

The goal is fidelity: the prompt loop, parsing, expansion, redirections, pipes, signals and built-ins are meant to match bash 5.2 behavior as closely as the subject allows. Most syntax, ambiguity, quoting and combination cases behave like the real thing.

---

## Build

```sh
make        # build the minishell binary
make clean  # remove object files
make fclean # remove objects + binary
make re     # fclean + build
```

Run interactively:

```sh
./minishell
```

Or non-interactively from another shell:

```sh
env -i ./minishell    # works with a clean environment; PATH falls back to a hardcoded default
```

---

## Features

### Core
- Interactive prompt with line editing and history (`readline`).
- Executable resolution via `PATH`, or via relative/absolute path.
- Single global variable for signal handling — stores only the signal number, never touches main data structures.

### Quoting
- `'single quotes'` — no metacharacter interpretation inside.
- `"double quotes"` — no interpretation except `$` expansion.

### Redirections
- `<` input
- `>` output (truncate)
- `>>` output (append)
- `<<` heredoc with a delimiter; reads until a line matching the delimiter.

### Pipes
- Full `|` pipelines; each command's stdout connects to the next command's stdin.

### Expansion
- `$VAR` → environment variable value.
- `$?` → exit status of the last foreground pipeline.
- `$$` → PID.
- Combined and edge cases: `export a="b    a          f" && echo $a && echo $a*`, `<< $""`, `<< $`, `<< $$`, `< $"a b"*`, `echo "a f"*`, etc.

### Signals (interactive mode)
- `ctrl-C` → new prompt on a new line.
- `ctrl-D` → exits the shell.
- `ctrl-\` → does nothing.

### Built-ins
- `echo` (with `-n`)
- `cd` (relative/absolute path; also handles `-`, `--`, and `~` as an extra)
- `pwd`
- `export` (with `+=`, multiple arguments)
- `unset` (multiple arguments)
- `env`
- `exit`

### Bonus
- `&&` and `||` with parentheses for priority.
- Wildcards `*` for the current working directory.

---

## Behavior notes (deliberate deviations from bash)

These are intentional and documented, not bugs. Where the subject does not require a behavior, this shell follows the subject rather than bash, and stays internally consistent.

**Expansion of `$` followed by digit, `*` or `$`.**
The subject only requires expanding environment variables (`$NAME`) and `$?`. `$1`, `$2`, `$0`, `$*` etc. have shell-scripting meanings that are out of scope, so they are not expanded. For an invalid name (e.g. `$bla` where `bla` is not a valid variable), the trailing characters like a digit or `*` are treated as ordinary characters (the same as `.`, `/`, `+`), **not** as quote or expansion metacharacters. `$$` is handled and expands to the PID.

**Heredoc delimiter size.**
Heredocs are stored in pipes rather than temporary files, which allows arbitrarily many delimiters in the correct order and placement. The tradeoff: a single delimiter cannot exceed the pipe buffer (~512 bytes on this system).

**`cd ~`.**
`~` is only handled inside `cd` (`cd ~` → HOME). It is not expanded generally. `~~` is treated as a command, so `~~` reports `~~: command not found` rather than a directory error.

**`export` / `unset` options.**
Options are not part of the subject. `unset -` / `unset --` are treated as `unset` with no valid name, since `-` and `--` are not valid variable names.

**`env` and `SHLVL` / `_`.**
`env` updates `SHLVL`: a new shell gets `SHLVL + 1`; if unset or `< 0`, `SHLVL` resets to 0. `_=` is updated to the last argument of the previous command, matching bash 5.2. `env -i ./minishell` works; with no `PATH`, a hardcoded default path is used. Note `env` is not a real built-in in bash, so calling `env` here resolves through `PATH` (visible when you `unset PATH`).

---

## Not implemented (out of scope)

The following were judged not worth implementing for this minishell and are intentionally absent:

- `|&`
- `<>`
- `2>file.txt` (stderr redirection)
- `unset` / `export` with options

The subject only requires what is listed in the mandatory part; anything beyond it is optional. Where there was doubt, bash 5.2 was used as the reference.

---

## Code quality disclaimer

This project was built under time pressure with correctness as the priority. **Clean code and style were not a focus.** The code works well and passes evaluation, but it is not organized or formatted to a standard I would call clean. Treat the source as functional reference, not a style example.

---

## Project files

Parsing/tokenizing (`break_input*.c`, `syntax_*.c`), expansion (`expansion_*.c`, including wildcard handling), execution and subshells (`execute_*.c`, `mini_*.c`), built-ins (`ft_builtin_*.c`), cleanup/memory (`ft_clean*.c`, `ft_free.c`), signals (`signal.c`), and a vendored `libft`.