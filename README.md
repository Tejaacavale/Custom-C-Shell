# Custom C Shell - OSN Sem 3 IIIT

# Part A: Basic System Calls

## Specification 1: Display Requirement [5]
Shell prompt display with username, system name, and current directory.

## Specification 2: Input Requirements [5]
Support for ';' or '&' separated commands with random spaces or tabs in input.

## Specification 3: warp [5]
Command to change the shell directory and display the full path after changing.

## Specification 4: peek [8]
Command to list files/directories with support for flags, color coding, and specific output formats.

## Specification 5: pastevents commands [8]
History command storing 15 most recent command statements, excluding specific commands, and executing past events.

## Specification 6: System commands [12]
Execution of system commands in foreground and background, displaying process ID and time taken if > 2 seconds.

## Specification 7: proclore [5]
Command to obtain process-related information such as pid, process status, virtual memory, and executable path.

## Specification 8: seek [8]
Command to search for files/directories with flags for specific searches and path symbols.

# Part B: Processes, Files and Misc.

## Specification 9: I/O Redirection [8]
Support for redirection ('>', '>>', '<') for output and input files, handling file existence and permissions.

## Specification 10: Pipes [8]
Support for piping ('|') commands to pass output as input for subsequent commands.

## Specification 11: Redirection along with pipes [5]
Integration of I/O redirection and pipes for combined functionality.

## Specification 12: activities [5]
Display a list of running processes with command name, pid, and state.

## Specification 13: Signals [12]
Sending signals to processes, handling process termination, and signal number translation.

## Specification 14: fg and bg [8]
Foreground and background commands to manage process state by bringing processes to the foreground or background.

## Specification 15: Neonate [8]
Command to print the PID of the most recently created process at intervals until 'x' key is pressed.

# Part C: Networking

## Specification 16: iMan [12]
Fetching man pages from a website using sockets, extracting information for specified commands.
