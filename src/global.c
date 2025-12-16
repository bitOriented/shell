#include"shell.h"

char *current_dir = NULL;

void init_current_dir(void)
{
    current_dir = getcwd(NULL, 0);
}