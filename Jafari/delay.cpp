#include <iostream>
#include <string>

using namespace std;

void delay(int);

int main()
{
    string name;

    cout << "Enter your name: ";
    getline(cin, name);

    for (int index = 0; index < name.length(); index++)
    {
        cout << name[index];
        delay(20);
    }
}
void delay(int delay)
{
    for (int index = 0; index < (9000000 * delay); index++);
}