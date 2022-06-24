#include <iostream>
#include <fstream>   // for file
#include <time.h>    //for random time
#include <Windows.h> // for colores
using namespace std;
HANDLE takecolor = GetStdHandle(STD_OUTPUT_HANDLE);
class player
{
protected:
    string name1, name2;
    char mark_player1, mark_player2;

public:
    void start_player()
    {
        int no1, no2;
        char shapes[5] = {5, 6, 127, 747, 4};
        SetConsoleTextAttribute(takecolor, 10); // for color grean
        cout << "\t\t******************************\n";
        cout << "\t\t WELLCOME THE DICE GAME \n";
        cout << "\t\t******************************\n";
        SetConsoleTextAttribute(takecolor, 7);  // for color white
        SetConsoleTextAttribute(takecolor, 11); // for color light blue
        cout << "******************************\n";
        cout << "player 1 enter your name :";
        cin >> name1;
        cout << "******************************\n";
        cout << "player 2 enter your name :";
        cin >> name2;
        cout << "******************************\n";
        SetConsoleTextAttribute(takecolor, 7);
        system("cls");
        SetConsoleTextAttribute(takecolor, 10);
        cout << "\t\t-------------------------------\n";
        cout << "\t\t <<<< SHAPE SELECTION >>>>\n";
        cout << "\t\t-------------------------------\n";
        SetConsoleTextAttribute(takecolor, 7);
        SetConsoleTextAttribute(takecolor, 4); // for color red
        for (int i = 0; i < 5; i++)
        {
            cout << "-------" << endl;
            cout << i + 1 << "-" << shapes[i] << endl;
        }
        SetConsoleTextAttribute(takecolor, 7);
        cout << "-------------------------------------------\n";
        cout << name1 << " choose number of shape you want to play :";
        cin >> no1;
        cout << "-------------------------------------------\n";
        cout << name2 << " choose number of shape you want to play :";
        cin >> no2;
        cout << "-------------------------------------------\n";
        mark_player1 = shapes[no1 - 1];
        mark_player2 = shapes[no2 - 1];
        SetConsoleTextAttribute(takecolor, 10);
        cout << "--------------------\n";
        cout << name1 << " :" << mark_player1 << endl;
        cout << "--------------------\n";
        cout << name2 << " :" << mark_player2 << endl;
        cout << "--------------------\n";
        SetConsoleTextAttribute(takecolor, 7);
    }
};
class game : public player
{
    char board[5][5];
    int num2[5][5], num1[5][5];
    int size, dice1, dice2, row1, col1, rowp2, colp2, sr1, sc1, sr2, sc2;
    bool checkwinner; // check winner for file
public:
    game()
    {
        size = 5;
        int p1 = 0;
        int p2 = 0;
        checkwinner = true;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
            {
                num1[i][j] = 0;
                num2[i][j] = 0;
            }
        /**************matrix numbers for player 1 **********************/
        for (int i = 0; i < 5; i++)
        {
            num1[0][i] = p1;
            p1++;
        }
        p1 = 5;
        for (int i = 1; i < 4; i++)
        {
            num1[i][4] = p1;
            p1++;
        }
        p1 = 8;
        for (int i = 3; i > 0; i--)
        {
            num1[3][i] = p1;
            p1++;
        }
        p1 = 11;
        for (int i = 1; i < 3; i++)
        {
            num1[2][i] = p1;
            p1++;
        }
        /**************matrix numbers for player 2 **********************/
        for (int i = 4; i >= 0; i--)
        {
            num2[4][i] = p2;
            p2++;
        }
        for (int i = 4; i >= 0; i--)
        {
            if (i > 0)
            {
                num2[i][0] = p2 - 1;
                p2++;
            }
        }
        p2 = 8;
        for (int i = 0; i < 4; i++)
        {
            if (i > 0)
            {
                num2[1][i] = p2;
                p2++;
            }
        }
        p2 = 12;
        for (int i = 0; i < 4; i++)
        {
            if (i > 1)
            {
                num2[2][i] = p2;
                p2--;
            }
        }
        /**************matrix space **********************/
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                board[i][j] = ' ';
        sr1 = 0;
        sc1 = 0;
        sr1 = 4;
        sc1 = 4;
        board[0][0] = mark_player1;
        board[4][4] = mark_player2;
    }
    void movemark()
    {
        bool continue1 = true;
        int s1 = 0, s2 = 0, index1 = 0, index2 = 0, n2 = 0, n1 = 0, x, saverand = 0;
        genralpoard(board);
        sr1 = 0;
        sc1 = 0;
        sr2 = 4;
        sc2 = 4;
        int again = 0;
        while (continue1 == true)
        {
            if (again % 2 == 0)
            {
                SetConsoleTextAttribute(takecolor, 6);
                cout << name1;
                SetConsoleTextAttribute(takecolor, 7);
                cout << " Plases Enter ( 0 ) for throw the dice : ";
                cin >> dice1;
                srand(time(NULL));
                if (dice1 == 0)
                {
                    saverand = rand() % 5;
                    dice1 = saverand + 1; // that i want from 1 to 6
                    cout << "THE DICE IS : " << dice1 << endl;
                    row1 = sr1;           // 4 3
                    col1 = sc1;           // 3 3
                    index1 = row1 + col1; // 7 6
                    index1 += dice1;      // 3 9
                    x = 12 - s1;
                    if (row1 == 3 && col1 == 3)
                    {
                        if (index1 > 10)
                            check(index1);
                        index1 += 2;
                    } // for index 8
                    else if (row1 == 3 && col1 == 2)
                    {
                        if (index1 > 4)
                            index1 += 4;
                    } // for index 9
                    else if (row1 == 3 && col1 == 1)
                    {
                        if (index1 > 6)
                            check(index1);
                        index1 += 6;
                    } // for index 10
                    else if (row1 == 2 && col1 == 1)
                    {
                        if (index1 > 4)
                            check(index1);
                        index1 += 8;
                    } // for index 11
                    if ((index1 <= x) || (index1 >= x))
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            for (int j = 0; j < 5; j++)
                            {
                                if (index1 == num1[i][j])
                                {
                                    if ((index1 != 12) && (index1 != 1) && (index1 != 4) && (index1 != 6) && (index1 != 9))
                                    {
                                        board[i][j] = mark_player1;
                                        allbourd(board);
                                        s1 = index1;
                                        sr1 = i;
                                        sc1 = j;
                                        continue1 = true;
                                    }
                                    else
                                    {
                                        switch (index1)
                                        {
                                        case 1:
                                        {
                                            SetConsoleTextAttribute(takecolor, 4);
                                            cout << "YOU GET TRAP AT NUMBER 1 NO CHANGE " << endl;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            allbourd(board);
                                        }
                                        break;
                                        case 4:
                                        {
                                            SetConsoleTextAttribute(takecolor, 4);
                                            cout << "YOU GET TRAP AT NUMBER 4 YOU GET BACK STEP " << endl;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            board[0][3] = mark_player1;
                                            s1 = index1 - 1;
                                            sr1 = 0;
                                            sc1 = 3;
                                            continue1 = true;
                                            allbourd(board);
                                        }
                                        break;
                                        case 6:
                                        {
                                            SetConsoleTextAttribute(takecolor, 7);
                                            cout << "YOU GET TRAP AT NUMBER 6 YOU GET OVER STEP " << endl;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            board[3][4] = mark_player1;
                                            index1 = s1 + 1;
                                            s1 = index1;
                                            sr1 = 3;
                                            sc1 = 4;
                                            continue1 = true;
                                            allbourd(board);
                                        }
                                        break;
                                        case 9:
                                        {
                                            SetConsoleTextAttribute(takecolor, 4);
                                            cout << "YOU GET TRAP AT NUMBER 9 YOU die " << endl;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            board[3][2] = mark_player1;
                                            index1 = 9;
                                            sr1 = 3;
                                            sc1 = 2;
                                            cout << " THE WINNER IS << " << name2 << " >>" << endl;
                                            continue1 = false;
                                            checkwinner = false;
                                        }
                                        break;
                                        case 12:
                                        {
                                            SetConsoleTextAttribute(takecolor, 10);
                                            cout << " THE WINNER IS " << name1 << endl;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            continue1 = false;
                                            checkwinner = true;
                                        }
                                        break;
                                        } // end switch
                                    }     // end else
                                }
                            }
                        }
                    }
                }
            } // end if
            else
            {
                SetConsoleTextAttribute(takecolor, 1);
                cout << name2;
                SetConsoleTextAttribute(takecolor, 7);
                cout << " Plases Enter ( 0 ) for throw the dice : ";
                cin >> dice2;
                srand(time(NULL));
                if (dice2 == 0)
                {
                    saverand = rand() % 5;
                    dice2 = saverand + 1;
                    cout << "THE DICE IS :" << dice2 << endl;
                    rowp2 = sr2;
                    colp2 = sc2;
                    index2 = rowp2 - colp2;
                    try
                    {
                        if (rowp2 == 4)
                        {
                            index2 += dice2;
                            throw index2;
                        }
                        if (colp2 == 0)
                        {
                            index2 = s2;
                            index2 += dice2;
                            if (index2 <= 12)
                                throw index2;
                            else
                                check(index2);
                        } // here i save the index and sum withe new dice
                        if (index2 <= 0 && rowp2 == 1)
                        {
                            index2 = s2;
                            index2 += dice2;
                            if (index2 <= 12)
                                throw index2;
                            else
                                check(index2);
                        } // here i save the index and sum withe new dice
                        if (index2 <= 0 && rowp2 == 2)
                        {
                            if (index2 <= 12)
                                throw index2;
                            else
                                check(index2);
                        }
                    } // end try
                    catch (int n)
                    {
                        for (int i = 0; i < 5; i++)
                            for (int j = 0; j < 5; j++)
                            {
                                if (n == num2[i][j])
                                {
                                    if (n != 1 && n != 4 && n != 6 && n != 9 && n != 12)
                                    {
                                        sr2 = i;
                                        sc2 = j;
                                        s2 = n;
                                        board[i][j] = mark_player2;
                                        allbourd(board);
                                    }
                                    else
                                    {
                                        switch (n)
                                        {
                                        case 1:
                                        {
                                            SetConsoleTextAttribute(takecolor, 4);
                                            cout << "YOU GET TRAP AT NUMBER 1 NO CHANGE " << endl;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            allbourd(board);
                                        }
                                        break;
                                        case 4:
                                        {
                                            SetConsoleTextAttribute(takecolor, 4);
                                            cout << "YOU GET TRAP AT NUMBER 4 YOU GET BACK STEP " << endl;
                                            board[4][1] = mark_player2;
                                            s2 = n;
                                            sr2 = 4;
                                            sc2 = 1;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            allbourd(board);
                                        }
                                        break;
                                        case 6:
                                        {
                                            SetConsoleTextAttribute(takecolor, 4);
                                            cout << "YOU GET TRAP AT NUMBER 6 YOU GET OVER STEP " << endl;
                                            board[1][0] = mark_player2;
                                            s2 = n + 1;
                                            sr2 = 1;
                                            sc2 = 0;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            allbourd(board);
                                        }
                                        break;
                                        case 9:
                                        {
                                            SetConsoleTextAttribute(takecolor, 4);
                                            cout << "YOU GET TRAP AT NUMBER 9 YOU die " << endl;
                                            sr2 = 1;
                                            sc2 = 2;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            cout << " THE WINNER IS << " << name1 << " >>" << endl;
                                            continue1 = false;
                                            checkwinner = true;
                                        }
                                        break;
                                        case 12:
                                        {
                                            SetConsoleTextAttribute(takecolor, 10);
                                            cout << " THE WINNER IS << " << name2 << " >> " << endl;
                                            SetConsoleTextAttribute(takecolor, 7);
                                            continue1 = false;
                                            checkwinner = false;
                                        }
                                        break;
                                        }
                                    }
                                }
                            } /* end loop */
                    }         // end catch
                }
            } // end else player2
            again++;
        } // end while
    }     // end function
    void genralpoard(char a[][5])
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                cout << "**********";
            cout << endl;
            fullcube(i);                   // function for fall cube mean for (Trap)
            for (int j = 0; j < size; j++) // for row medium (mean second)
            {
                if (i == 0 && j == 0)
                {
                    cout << "*";
                    SetConsoleTextAttribute(takecolor, 6);
                    cout << " SP"
                         << "1 "; // start player 1
                    SetConsoleTextAttribute(takecolor, 7);
                    cout << "*";
                }
                else if (i == 4 && j == 4)
                {
                    cout << "*";
                    SetConsoleTextAttribute(takecolor, 1);
                    cout << " SP"
                         << "2 "; // start player 1
                    SetConsoleTextAttribute(takecolor, 7);
                    cout << "*";
                }
                else if (i == 2 && j == 2)
                {
                    cout << "*";
                    SetConsoleTextAttribute(takecolor, 10);
                    cout << "*W"
                         << "INNER*";
                    SetConsoleTextAttribute(takecolor, 7);
                    cout << "*";
                }
                else if ((i == 0 && j == 1) || (i == 0 && j == 4) || (i == 2 && j == 4) || (i == 3 && j == 2)) // for player 1
                {
                    cout << "*";
                    SetConsoleTextAttribute(takecolor, 6);
                    cout << "***"
                         << "*****";
                    SetConsoleTextAttribute(takecolor, 7);
                    cout << "*";
                }
                else if ((i == 1 && j == 2) || (i == 2 && j == 0) || (i == 4 && j == 0) || (i == 4 && j == 3)) // for player 2
                {
                    cout << "*";
                    SetConsoleTextAttribute(takecolor, 1);
                    cout << "***"
                         << "*****";
                    SetConsoleTextAttribute(takecolor, 7);
                    cout << "*";
                }
                else
                    cout << "* " << a[i][j] << " *";
            }
            cout << endl;
            fullcube(i); // function for fall cube mean for (Trap)
            for (int j = 0; j < size; j++)
                cout << "**********";
            cout << endl;
        } // end loop
    }
    void allbourd(char a[][5])
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                cout << "**********";
            cout << endl;
            fullcube(i); // here is function
            detals(i, a);
            cout << endl;
            fullcube(i);
            for (int j = 0; j < size; j++)
                cout << "**********";
            cout << endl;
        } // end loop
    }
    void detals(int b, char c[][5])
    {
        for (int j = 0; j < size; j++)
        {
            if (b == 0 && j == 0)
            {
                cout << "*";
                SetConsoleTextAttribute(takecolor, 6);
                cout << " SP"
                     << "1 "; // start player 1
                SetConsoleTextAttribute(takecolor, 7);
                cout << "*";
            }
            else if (b == 4 && j == 4)
            {
                cout << "*";
                SetConsoleTextAttribute(takecolor, 1);
                cout << " SP"
                     << "2 "; // start player 1
                SetConsoleTextAttribute(takecolor, 7);
                cout << "*";
            }
            else if (b == 2 && j == 2)
            {
                cout << "*";
                SetConsoleTextAttribute(takecolor, 10);
                cout << "*W"
                     << "INNER*";
                SetConsoleTextAttribute(takecolor, 7);
                cout << "*";
            }
            else if ((b == 0 && j == 1) || (b == 0 && j == 4) || (b == 2 && j == 4) || (b == 3 && j == 2)) // for player 1
            {
                cout << "*";
                SetConsoleTextAttribute(takecolor, 6);
                cout << "***"
                     << "*****";
                SetConsoleTextAttribute(takecolor, 7);
                cout << "*";
            }
            else if ((b == 1 && j == 2) || (b == 2 && j == 0) || (b == 4 && j == 0) || (b == 4 && j == 3)) // for player 2
            {
                cout << "*";
                SetConsoleTextAttribute(takecolor, 1);
                cout << "***"
                     << "*****";
                SetConsoleTextAttribute(takecolor, 7);
                cout << "*";
            }
            else
            {
                if ((b != 0 && j != 0) || (b != 4 && j != 4))
                {
                    cout << "* ";
                    SetConsoleTextAttribute(takecolor, 4);
                    cout << c[b][j];
                    SetConsoleTextAttribute(takecolor, 7);
                    cout << " *";
                }
                else
                    cout << "* " << c[b][j] << " *";
            }
        }
    }
    void fullcube(int b)
    {
        for (int j = 0; j < size; j++) // for row up (mean first)
        {
            if ((b == 0 && j == 1) || (b == 0 && j == 4) || (b == 2 && j == 4) || (b == 3 && j == 2)) // for player 1
                                                                                                      //  that to take color row of player 1
            {
                cout << "*";
                SetConsoleTextAttribute(takecolor, 6);
                cout << "***"
                     << "*****";
                SetConsoleTextAttribute(takecolor, 7);
                cout << "*";
            }
            else if ((b == 1 && j == 2) || (b == 2 && j == 0) || (b == 4 && j == 0) || (b == 4 && j == 3))
            // that to take color row of player 2
            {
                cout << "*";
                SetConsoleTextAttribute(takecolor, 1);
                cout << "***"
                     << "*****";
                SetConsoleTextAttribute(takecolor, 7);
                cout << "*";
            }
            else if (b == 2 && j == 2)
            {
                cout << "*";
                SetConsoleTextAttribute(takecolor, 10);
                cout << "***"
                     << "*****";
                SetConsoleTextAttribute(takecolor, 7);
                cout << "*";
            }
            else
                cout << "* *";
        } // end loop
        cout << endl;
    } // end function
    void check(int m) { cout << "SORRY YOU CAN NOT WITH THIS DICE " << endl; }
    friend void testfile1(game p); // friend function
};
void testfile1(game p)
{
    ofstream prj1("check.txt");
    string c;
    if (p.checkwinner == true)
    {
        prj1 << "THE WINNER IS : " << p.name1;
    }
    else
    {
        prj1 << "THE WINNER IS : " << p.name2;
    }
}

int main()
{
    game s1;
    s1.start_player();
    s1.movemark();
    testfile1(s1);
}
