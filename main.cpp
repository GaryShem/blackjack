#include <iostream>
#include "Table.h"
#include "ConsolePlayer.h"

int main()
{
    Table table(4);
    table.AddPlayer(new ConsolePlayer());
    table.PlayGame();
    return 0;
}
