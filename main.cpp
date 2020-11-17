#include <iostream>
#include "Table.h"
#include "ConsolePlayer.h"

int main()
{
    Table table(10);
    table.AddPlayer(new ConsolePlayer());
    table.PlayGame();
    std::cout << "No more players left, finishing game" << std::endl;
    return 0;
}
