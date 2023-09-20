# Pipex

Pipex is a C programming project that simulates the behavior of shell pipes, allowing you to redirect and process data between specified shell commands. It aims to deepen your understanding of UNIX mechanisms by implementing them within your own program.

## Score

-  125%

## Project Highlight
- Pipex replicates the functionality of the shell command `< file1 cmd1 | cmd2 > file2`, enabling seamless data transfer and manipulation between two specified shell commands through your program.
- The bonus part handles multiple pipes `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`
- The bonus part support << and >> in order to replicates a heredoc `cmd << LIMITER | cmd1 >> file`
  
## Usage
1. Clone the repository.
2. Compile the library using the provided Makefile.
3. Run Pipex, using the following command format:  
- `$> ./pipex infile "ls -l" "wc -l" outfile` should behave as `< infile ls -l | wc -l > outfile`  
- `$>./pipex infile "grep a1" "wc -w" outfile` should behave as `< infile grep a1 | wc -w > outfile`  
- `$> ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2` should behave as `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`  
- `$> ./pipex_bonus here_doc LIMITER cmd cmd1 file` should behave as `cmd << LIMITER | cmd1 >> file`

## Author

[Archibald Thirion](https://github.com/Archips)
