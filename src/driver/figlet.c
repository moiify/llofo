#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

void print_row(char* str, int row)
{
    char c;
    for (int i = 0; i < strlen(str); i++)
    {
        c = *(str + i);
        switch (c)
        {
            case 'A':
                switch (row)
                {
                    case 1:
                        uart_print("        ");
                        break;
                    case 2:
                        uart_print("   /\\   ");
                        break;
                    case 3:
                        uart_print("  /__\\  ");
                        break;
                    case 4:
                        uart_print(" /----\\ ");
                        break;
                    case 5:
                        uart_print("/_/  \\_\\");
                        break;
                }
                break;
            case 'B':
                switch (row)
                {
                    case 1:
                        uart_print(" ____  ");
                        break;
                    case 2:
                        uart_print("| __ ) ");
                        break;
                    case 3:
                        uart_print("|  _ \\ ");
                        break;
                    case 4:
                        uart_print("| |_) |");
                        break;
                    case 5:
                        uart_print("|____/ ");
                        break;
                }
                break;
            case 'C':
                switch (row)
                {
                    case 1:
                        uart_print("  ____ ");
                        break;
                    case 2:
                        uart_print(" / ___|");
                        break;
                    case 3:
                        uart_print("| |    ");
                        break;
                    case 4:
                        uart_print("| |___ ");
                        break;
                    case 5:
                        uart_print(" \\____|");
                        break;
                }
                break;
            case 'D':
                switch (row)
                {
                    case 1:
                        uart_print(" ____  ");
                        break;
                    case 2:
                        uart_print("|  _ \\ ");
                        break;
                    case 3:
                        uart_print("| | | |");
                        break;
                    case 4:
                        uart_print("| |_| |");
                        break;
                    case 5:
                        uart_print("|____/ ");
                        break;
                }
                break;
            case 'E':
                switch (row)
                {
                    case 1:
                        uart_print(" _____ ");
                        break;
                    case 2:
                        uart_print("| ____|");
                        break;
                    case 3:
                        uart_print("|  _|  ");
                        break;
                    case 4:
                        uart_print("| |___ ");
                        break;
                    case 5:
                        uart_print("|_____|");
                }
                break;
            case 'F':
                switch (row)
                {
                    case 1:
                        uart_print(" _____ ");
                        break;
                    case 2:
                        uart_print("|  ___|");
                        break;
                    case 3:
                        uart_print("| |_   ");
                        break;
                    case 4:
                        uart_print("|  _|  ");
                        break;
                    case 5:
                        uart_print("|_|    ");
                        break;
                }
                break;
            case 'G':
                switch (row)
                {
                    case 1:
                        uart_print("  ____ ");
                        break;
                    case 2:
                        uart_print(" / ___|");
                        break;
                    case 3:
                        uart_print("| |  _ ");
                        break;
                    case 4:
                        uart_print("| |_| |");
                        break;
                    case 5:
                        uart_print(" \\____|");
                        break;
                }
                break;
            case 'H':
                switch (row)
                {
                    case 1:
                        uart_print(" _   _ ");
                        break;
                    case 2:
                        uart_print("| | | |");
                        break;
                    case 3:
                        uart_print("| |_| |");
                        break;
                    case 4:
                        uart_print("|  _  |");
                        break;
                    case 5:
                        uart_print("|_| |_|");
                        break;
                }
                break;
            case 'I':
                switch (row)
                {
                    case 1:
                        uart_print(" ___ ");
                        break;
                    case 2:
                        uart_print("|_ _|");
                        break;
                    case 3:
                    case 4:
                        uart_print(" | | ");
                        break;
                    case 5:
                        uart_print("|___|");
                        break;
                }
                break;
            case 'J':
                switch (row)
                {
                    case 1:
                        uart_print("     _ ");
                        break;
                    case 2:
                        uart_print("    | |");
                        break;
                    case 3:
                        uart_print(" _  | |");
                        break;
                    case 4:
                        uart_print("| |_| |");
                        break;
                    case 5:
                        uart_print(" \\___/ ");
                        break;
                }
                break;
            case 'K':
                switch (row)
                {
                    case 1:
                        uart_print(" _  __");
                        break;
                    case 2:
                        uart_print("| |/ /");
                        break;
                    case 3:
                        uart_print("| ' / ");
                        break;
                    case 4:
                        uart_print("| | \\ ");
                        break;
                    case 5:
                        uart_print("|_|\\_\\");
                        break;
                }
                break;
            case 'M':
                switch (row)
                {
                    case 1:
                        uart_print(" __  __ ");
                        break;
                    case 2:
                        uart_print("|  \\/  |");
                        break;
                    case 3:
                        uart_print("| |\\/| |");
                        break;
                    case 4:
                        uart_print("| |  | |");
                        break;
                    case 5:
                        uart_print("|_|  |_|");
                        break;
                }
                break;
            case 'L':
                switch (row)
                {
                    case 1:
                        uart_print(" _     ");
                        break;
                    case 2:
                    case 3:
                        uart_print("| |    ");
                        break;
                    case 4:
                        uart_print("| |___ ");
                        break;
                    case 5:
                        uart_print("|_____|");
                        break;
                }
                break;
            case 'N':
                switch (row)
                {
                    case 1:
                        uart_print(" _   _ ");
                        break;
                    case 2:
                        uart_print("| \\ | |");
                        break;
                    case 3:
                        uart_print("|  \\| |");
                        break;
                    case 4:
                        uart_print("| |\\  |");
                        break;
                    case 5:
                        uart_print("|_| \\_|");
                        break;
                }
                break;
            case 'O':
                switch (row)
                {
                    case 1:
                        uart_print("  ___  ");
                        break;
                    case 2:
                        uart_print(" / _ \\ ");
                        break;
                    case 3:
                        uart_print("| | | |");
                        break;
                    case 4:
                        uart_print("| |_| |");
                        break;
                    case 5:
                        uart_print(" \\___/ ");
                        break;
                }
                break;
            case 'P':
                switch (row)
                {
                    case 1:
                        uart_print(" ____  ");
                        break;
                    case 2:
                        uart_print("|  _ \\ ");
                        break;
                    case 3:
                        uart_print("| |_) |");
                        break;
                    case 4:
                        uart_print("|  __/ ");
                        break;
                    case 5:
                        uart_print("|_|    ");
                        break;
                }
                break;
            case 'Q':
                switch (row)
                {
                    case 1:
                        uart_print("  ___  ");
                        break;
                    case 2:
                        uart_print(" / _ \\ ");
                        break;
                    case 3:
                        uart_print("| | | |");
                        break;
                    case 4:
                        uart_print("| |_| |");
                        break;
                    case 5:
                        uart_print(" \\__\\_\\");
                        break;
                }
                break;
            case 'R':
                switch (row)
                {
                    case 1:
                        uart_print(" ____  ");
                        break;
                    case 2:
                        uart_print("|  _ \\ ");
                        break;
                    case 3:
                        uart_print("| |_) |");
                        break;
                    case 4:
                        uart_print("|  _ < ");
                        break;
                    case 5:
                        uart_print("|_| \\_\\");
                        break;
                }
                break;
            case 'S':
                switch (row)
                {
                    case 1:
                        uart_print(" ____  ");
                        break;
                    case 2:
                        uart_print("/ ___| ");
                        break;
                    case 3:
                        uart_print("\\___ \\ ");
                        break;
                    case 4:
                        uart_print(" ___) |");
                        break;
                    case 5:
                        uart_print("|____/ ");
                        break;
                }
                break;
            case 'T':
                switch (row)
                {
                    case 1:
                        uart_print(" _____ ");
                        break;
                    case 2:
                        uart_print("|_   _|");
                        break;
                    case 3:
                    case 4:
                        uart_print("  | |  ");
                        break;
                    case 5:
                        uart_print("  |_|  ");
                        break;
                }
                break;
            case 'U':
                switch (row)
                {
                    case 1:
                        uart_print(" _   _ ");
                        break;
                    case 2:
                    case 3:
                        uart_print("| | | |");
                        break;
                    case 4:
                        uart_print("| |_| |");
                        break;
                    case 5:
                        uart_print(" \\___/ ");
                        break;
                }
                break;
            case 'V':
                switch (row)
                {
                    case 1:
                        uart_print("__     __");
                        break;
                    case 2:
                        uart_print("\\ \\   / /");
                        break;
                    case 3:
                        uart_print(" \\ \\ / / ");
                        break;
                    case 4:
                        uart_print("  \\ V /  ");
                        break;
                    case 5:
                        uart_print("   \\_/   ");
                        break;
                }
                break;
            case 'W':
                switch (row)
                {
                    case 1:
                        uart_print("__        __");
                        break;
                    case 2:
                        uart_print("\\ \\      / /");
                        break;
                    case 3:
                        uart_print(" \\ \\ /\\ / / ");
                        break;
                    case 4:
                        uart_print("  \\ V  V /  ");
                        break;
                    case 5:
                        uart_print("   \\_/\\_/   ");
                        break;
                }
                break;
            case 'X':
                switch (row)
                {
                    case 1:
                        uart_print("__  __");
                        break;
                    case 2:
                        uart_print("\\ \\/ /");
                        break;
                    case 3:
                        uart_print(" \\  / ");
                        break;
                    case 4:
                        uart_print(" /  \\ ");
                        break;
                    case 5:
                        uart_print("/_/\\_\\");
                        break;
                }
                break;
            case 'Y':
                switch (row)
                {
                    case 1:
                        uart_print("__   __");
                        break;
                    case 2:
                        uart_print("\\ \\ / /");
                        break;
                    case 3:
                        uart_print(" \\ V / ");
                        break;
                    case 4:
                        uart_print("  | |  ");
                        break;
                    case 5:
                        uart_print("  |_|  ");
                }
                break;
            case 'Z':
                switch (row)
                {
                    case 1:
                        uart_print(" _____");
                        break;
                    case 2:
                        uart_print("|__  /");
                        break;
                    case 3:
                        uart_print("  / / ");
                        break;
                    case 4:
                        uart_print(" / /_ ");
                        break;
                    case 5:
                        uart_print("/____|");
                        break;
                }
                break;
            default:
                break;
        }
        uart_print(" ");
    }
    uart_print("\n");
}


void figlet_PrintStr(char* str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (*(str + i) > 'Z' || *(str + i) < 'A')
        {
            //uart_print(stderr, "only upper case string supported\n");
            return ;
        }
    }
    for (i = 1; i <= 5; i++)
    {
        print_row(str, i);
    }
}

