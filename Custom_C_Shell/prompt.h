#ifndef __PROMPT_H
#define __PROMPT_H

void prompt(char* homedir);
bool is_starting_part(const char *str1, const char *str2);
void find_relative_path(const char *from_path, const char *to_path,char relative_path[4096]);
#endif