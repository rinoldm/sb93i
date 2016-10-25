/** Simple Befunge-93 Interpreter V1.0 -- Written by Maxime Rinoldo **/

#include "sb93i.hpp"

long int pop(std::stack<long int> &stack, bool pop)
{
    if (stack.empty())
    {
        if (pop) stack.push(0);
        return (0);
    }
    long int tmp = stack.top();
    if (pop) stack.pop();
    return (tmp);
}

char **init_program(char *progfile)
{
    char **program = (char **) calloc(PROGRAM_LINES, sizeof(char *));
    for (int i = 0; i < PROGRAM_LINES; ++i)
        program[i] = (char *) calloc(PROGRAM_COLUMNS + 1, sizeof(char));

    std::ifstream file(progfile);
    std::string str;
    for (int i = 0; i < PROGRAM_LINES && std::getline(file, str); ++i)
        strcpy(program[i], str.substr(0, PROGRAM_COLUMNS).c_str());

    return (program);
}

void exec_command(char command, char **program, PC *pc, std::stack<long int> &stack, bool *exit_program)
{
    long int t1, t2;

    switch(command)
    {
    case '0':   stack.push(0);                                                          break;
    case '1':   stack.push(1);                                                          break;
    case '2':   stack.push(2);                                                          break;
    case '3':   stack.push(3);                                                          break;
    case '4':   stack.push(4);                                                          break;
    case '5':   stack.push(5);                                                          break;
    case '6':   stack.push(6);                                                          break;
    case '7':   stack.push(7);                                                          break;
    case '8':   stack.push(8);                                                          break;
    case '9':   stack.push(9);                                                          break;
    case '+':   POP(t1, t2); stack.push(t2 + t1);                                       break;
    case '-':   POP(t1, t2); stack.push(t2 - t1);                                       break;
    case '*':   POP(t1, t2); stack.push(t2 * t1);                                       break;
    case '/':   POP(t1, t2); stack.push(t2 / t1);                                       break;
    case '%':   POP(t1, t2); stack.push(t2 % t1);                                       break;
    case '`':   POP(t1, t2); stack.push(t2 > t1);                                       break;
    case '!':   stack.top() = !pop(stack, false);                                       break;
    case '>':   pc->change_dir(pc->RIGHT);                                              break;
    case '<':   pc->change_dir(pc->LEFT);                                               break;
    case 'v':   pc->change_dir(pc->DOWN);                                               break;
    case '^':   pc->change_dir(pc->UP);                                                 break;
    case '?':   pc->change_dir(rand() % 4);                                             break;
    case '_':   pop(stack, true) ? pc->change_dir(pc->LEFT) : pc->change_dir(pc->RIGHT);break;
    case '|':   pop(stack, true) ? pc->change_dir(pc->UP)   : pc->change_dir(pc->DOWN); break;
    case '#':   pc->move();                                                             break;
    case '@':   *exit_program = true;                                                   break;
    case ':':   stack.push(pop(stack, false));                                          break;
    case '$':   pop(stack, true);                                                       break;
    case'\\':   POP(t1, t2); stack.push(t1); stack.push(t2);                            break;
    case '.':   std::cout << pop(stack, true) << " ";                                   break;
    case ',':   std::cout << (char) pop(stack, true);                                   break;
    case '&':   int     input_i; std::cin >> input_i; stack.push(input_i);              break;
    case '~':   char    input_c; std::cin >> input_c; stack.push(input_c);              break;
    case 'g':   POP(t1, t2); stack.push(IN_BOUNDS(t1, t2) ? program[t1][t2] : ' ');     break;
    case 'p':   POP(t1, t2); if (IN_BOUNDS(t1, t2)) program[t1][t2] = pop(stack, true); break;
    }
}

void exec_program(char **program)
{
    std::stack<long int> stack;
    bool stringmode = false;
    bool exit_program = false;
    char currCommand;

    for (PC *pc = new PC(); !exit_program; pc->move())
    {
        currCommand = program[pc->pos.y][pc->pos.x];
        if (currCommand == '"')
            stringmode = !stringmode;
        else if (stringmode)
            stack.push(currCommand);
        else
            exec_command(currCommand, program, pc, stack, &exit_program);
    }
}

int main(int ac, char **av)
{
    char **program = init_program(av[1]);
    exec_program(program);
    return (0);
}
