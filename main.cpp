// written by <Rzye>
// contact: <rzyekarami@gmail.com>

#include <iostream>
#include <string>
#include <unistd.h>
#include "utils//functions.hpp"
using namespace std;

// system "cls" & "clear"
#ifdef _WIN32
#define CLEAR "cls"
#else // In any other OS
#define CLEAR "clear"
#endif

// int todigit(string);
void inmainmenu(string);
string menu();
string mainmenu();
void info();

int main()
{
    string ch, co;
    // int choice, command;

    while (true)
    {
        ch = menu();
        // choice = todigit(ch);
        system(CLEAR);

        // if(choice == 1)
        if (ch == "1")
        {
            while (true)
            {
                co = mainmenu();
                // command = todigit(co);
                system(CLEAR);
                // if(command== 1 || ...)
                if (co == "1" || co == "2" || co == "3")
                    inmainmenu(co);

                else if (co == "4")
                    break;

                else
                {
                    cout << "invalid input!" << endl
                         << "Choose between: (1/2/3/4)" << endl;
                    sleep(2);
                    system(CLEAR);
                }
            }
        }
        else if (ch == "2")
        {
            info();
        }
        else if (ch == "3")
        {
            string answer;
            while (true)
            {
                system(CLEAR);
                cout << "Are sure you wanna exit?" << endl
                     << "Y or N? ";
                cin >> answer;
                system(CLEAR);
                if (answer == "y" || answer == "Y")
                {
                    cout << "See you soon:)" << endl;
                    sleep(1.5);
                    system(CLEAR);
                    return 0;
                }
                else if (answer == "n" || answer == "N")
                {
                    system(CLEAR);
                    break;
                }
                else
                {
                    cout << "invalid input!" << endl
                         << "choose Y/N" << endl;
                    sleep(2);
                    system(CLEAR);
                }
            }
        }
        else
        {
            cout << "invalid input" << endl
                 << "Choose between: (1/2/3)" << endl;
            sleep(2);
            system(CLEAR);
        }
    }
    return 0;
}
// int todigit(string str)
// {
//     int n;
//     if (isdigit(str[0]))
//     {
//         n = str[0];
//         n -= 48;
//     }
//     return n;
// }

string menu()
{
    system(CLEAR);
    cout << "Image Classifier Menu:\n\n"
         << "   1) Main Menu\n"
         << "   2) Info\n"
         << "   3) Exit\n"
         << "Your command: ";
    string ch;
    cin >> ch;
    return ch;
}
string mainmenu()
{
    cout << "Main Menu:\n\n"
         << "Make sure you had done the training once before testing...\n\n"
         << "   1) Explore images from dataset\n"
         << "   2) Train\n"
         << "   3) Test\n"
         << "   4) Return\n"
         << "Your command: ";
    string co;
    cin >> co;
    return co;
}

void inmainmenu(string co)
{
    float matrix[to][ti];
    int label[to];
    if (co == "1")
    {
        exploring_images();
        cout << "Press enter to continue..." << endl;
        cin.get();
        cin.get();
        system(CLEAR);
    }
    else if (co == "2")
    {
        cout << "It's training...";
        train(matrix, label);
        system(CLEAR);
        cout << "Training's Done Successfully!" << endl;
        cout << "You wanna check the accuracy?(y/n) ";
        char answer;
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            test_algorithem(matrix, label);
        cout << "Press enter to continue..." << endl;
        cin.get();
        cin.get();
        system(CLEAR);
    }
    else if (co == "3")
    {
        test(matrix, label);
        cin.get();
        cout << "Press enter to continue..." << endl;
        cin.get();
        cin.get();
        system(CLEAR);
    }
}

void info()
{
    cout << "Info:\n\n"
         << "Author:\n"
         << "Raziye Karami\n"
         << "Gmail:\n"
         << "rzyekarami@gmail.com\n"
         << endl
         << "Press enter to continue..."
         << endl;
    cin.get();
    cin.get();
    system(CLEAR);
}
