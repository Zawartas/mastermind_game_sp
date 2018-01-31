#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

#define max_array_size 8000

using namespace std;

struct pattern
{
    string value;
    bool possible_solution;
};

int guess (pattern from_solutions[], int n)
{
    int k;
    pattern number;

    do
    {
        k = rand() % n;
        if (from_solutions[k].possible_solution)
            return k;
    }
    while (from_solutions[k].possible_solution == false);
}

bool all_x (string s, int n)
{
    for (int i = 0; i < n; i++)
        if (s[i] != 'x')
            return false;
    return true;
}

int how_many_x (string s, int n)
{
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'x')
            counter++;
    }
    return counter;
}

int how_many_o (string s, int n)
{
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'o')
            counter++;
    }
    return counter;
}

int compare_numbers (string liczba1, string liczba2, int n)    //ile wspolnych cyfr na tych samych miejscach
{
    int k = 0;
    string temp = liczba2;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (liczba1[i] == liczba2[j])
            {
                k++;
                liczba2[j] = 'z';
            }
        }
    }
    liczba2 = temp;
    return k;
}

void remove_from_S (pattern *x, string liczba, int index, int n, int O)
{
    for (int i = 0; i < index; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (x[i].value[j] == liczba[j] || compare_numbers(x[i].value, liczba, n) < O)
            {
                x[i].possible_solution = false;
            }
        }
    }
}

int solutions_count (pattern x[], int index)
{
    int counter = 0;
    for (int i = 0; i < index; i++)
        if (x[i].possible_solution == true)
        {
            counter++;
        }
    return counter;
}

int compare_numbers_and_places (string liczba1, string liczba2, int n)    //ile wspolnych cyfr na tych samych miejscach
{
    int k = 0;
    string temp = liczba2;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (liczba1[i] == liczba2[j] && i == j)
            {
                k++;
                liczba2[j] = 'z';
            }
        }
    }
    liczba2 = temp;
    return k;
}

void remove_from_S_x (pattern *some, string liczba2, int index, int n, int X)
{
    for (int i = 0; i < index; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int z = compare_numbers_and_places(some[i].value, liczba2, n);
            if (z != X)
            {
                some[i].possible_solution = false;
            }
        }
    }
}

int main ()
{
    srand(time(nullptr));

    int n, k;
    cout << "How many numbers (n) and max number (k): ";
    cin >> n >> k;

    //number of solutions
    unsigned int S = 1;
    for (int i = 1; i <= n; i++)
        S = S*k;

    //creating soultion base
    pattern solution[max_array_size];

    for (int p = 0; p < S; p++)
    {
        solution[p].possible_solution = true;
        int i, x = 1;
        do
        {
            for (i = 0; i < n; i++)
            {
                solution[p].value += (p / x) % k + 49;
                x = x * k;
            }
        }
        while (i < n);
    }
    //done

    //petla wykonujaca gre do momentu samych "xxxxx" n-razy
    string answear;
    do
    {
        cout << "Possible solutions: " << solutions_count(solution, S) << endl;

        int z = guess(solution, S);

        string comp_guess;
        for (int i = 0; i < n; i++)
        {
            comp_guess += solution[z].value[i];
        };

        cin.sync();
        cout << "'x' for correct place and number.\n";
        cout << "'o' for correct number but wrong place. Do not include if 'x' already.\n";
        cout << "Computer guess: " << comp_guess << endl;
        getline(cin, answear);

        if (how_many_x(answear, n) == 0)
        {
            solution[z].possible_solution = false;
            remove_from_S(solution, comp_guess, S, n, how_many_o(answear, n));
        }

        if (how_many_x(answear, n) > 0 && how_many_x(answear, n) < n)
        {
            solution[z].possible_solution = false;
            remove_from_S_x(solution, comp_guess, S, n, how_many_x(answear, n));
        }
        cout << endl;
    }
    while (!all_x(answear, n));
    //koniec petli

    return 0;
}
