#include "../inc/minishell.h"

char *split_glitch(char *cmd_all)
{
    int stock[3];
    char *cmd_tsplit;
    int pass_space_for_redir;

    cmd_tsplit = malloc(sizeof(char) * 100);
    if (!cmd_tsplit)
        return (NULL);
    if (unclosed_quotes(cmd_all))
    {
        printf("Unclosed quotes, check your inport before retrying\n");
        return (NULL);
    }
    stock[0] = 0;
    stock[1] = 0;
    while (cmd_all[stock[0]])
    {
        if (cmd_all[stock[0]] == 34 || cmd_all[stock[0]] == 39)
        {
            stock[2] = cmd_all[stock[0]];
            cmd_tsplit[stock[1]] = cmd_all[stock[0]];
            stock[0]++;
            stock[1]++;
            pass_space_for_redir = stock[0];
            while(cmd_all[pass_space_for_redir] == 32)
                pass_space_for_redir++;
            if (is_red(cmd_all[pass_space_for_redir]))
            {
                cmd_tsplit[stock[1]] = 24;
                stock[1]++;
            }
            while(cmd_all[stock[0]] != stock[2])   
            {
                if (cmd_all[stock[0]] == 32)
                    cmd_tsplit[stock[1]] = 25;
                else
                    cmd_tsplit[stock[1]] = cmd_all[stock[0]];
                stock[1]++;
                stock[0]++;
            }
            cmd_tsplit[stock[1]] = cmd_all[stock[0]];
            stock[0]++;
            stock[1]++;
        }
        else if (is_red(cmd_all[stock[0]]))
        {
            if (stock[0] >= 1 && !is_red(cmd_all[stock[0] - 1]))
            {
                cmd_tsplit[stock[1]] = 32;
                stock[1]++;
            }
            cmd_tsplit[stock[1]] = cmd_all[stock[0]];
            stock[0]++;
            stock[1]++;
             while(cmd_all[stock[0]] == 32)
                 stock[0]++;
            while (is_red(cmd_all[stock[0]] || cmd_all[stock[0] == ' ']))
            {
                cmd_tsplit[stock[1]] = cmd_all[stock[0]];
                stock[0]++;
                stock[1]++;
            }
        }
        // else if(cmd_all[stock[0]] == 32)
        //     stock[0]++;
        else
        {
            cmd_tsplit[stock[1]] = cmd_all[stock[0]];
            stock[1]++;
            stock[0]++;
        }
    }
    cmd_tsplit[stock[1]] = '\0';
    return (cmd_tsplit);
}