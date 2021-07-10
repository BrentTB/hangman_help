#include <bits/stdc++.h>
using namespace std;

#define elif else if
#define fo(i, a, b) for (int i = a; i < (int)b; i++)
#define vstr vector<string>
#define print(x) cout << x << "\n"
#define println cout << endl
#define usrT cout << endl \
                  << " >> "

// returns a string of all the letters that are not in the word being guessed
string getWrong(set<char> wrong)
{
    string wrd = "";
    for (auto x : wrong)
        wrd.push_back(x);
    return wrd;
}

// returns a string representing the word to be guessed
string getWrd(int length, map<int, char> letters)
{
    string wrd = "";
    fo(i, 0, length)
        wrd.push_back(letters[i + 1]);
    return wrd;
}

// returns the lowercase of a string
string lowerCase(string wrd)
{
    string nW = "";
    for (auto x : wrd)
        nW.push_back(tolower(x));
    return nW;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // long:
    // happy 11
    // hungry 5

    // medium:
    // happy 6
    // hungry 5

    // short:
    // happy 6
    // hungry 4

    // Full:
    // happy 13
    // hungry 5

    int count[26];

    vstr words;             // array of all words
    vstr tmp;               // array used to help fill poswords
    set<char> notIn;        // all of the letters not in the word;
    string x;               // temp string used to read from txt file
    string input;           // the string used when the user enters information
    int numL = 0;           // the number of letters in the word
    map<int, char> letters; // maps an index to teh letter at said index

    words.reserve(500000);

    int txtChoose = 1;  // selects which txt file to use
    string inputF = ""; // the name of the txt file used

    switch (txtChoose)
    {
    case 1:

        inputF = "wordsShort.txt"; // very short list, most accurate most of the time ± 10k words

        break;
    case 2:

        inputF = "wordsMedium.txt"; // shorter list but more useful ± 58K words
        break;

    case 3:

        inputF = "wordsFull.txt"; // The word list supplied by apple based on the Merriam-Webster dictionary ± 230k words

        break;

    case 4:

        inputF = "wordsLong.txt"; // more entensive list, but less useful in most games ± 370k words
        break;
    case 5:

        inputF = "wordsSpecial.txt"; //Long list containing special characters - DOES NOT WORK CURRENTLY ± 460k
        break;

    default:
        inputF = "wordsShort.txt";

        break;
    }

    {
        ifstream cin(inputF); // 370000
        while (cin >> x)
        {
            x = lowerCase(x);
            words.push_back(x);
        }
    }

start:
    println;
    println;
    print("I am a hangman bot. Please enter the number of letters in the word to be guessed");
    usrT;

    cin >> x;

    try
    {
        numL = stoi(x);

        if (numL < 1 || numL > 25)
        {
            throw "wrong word length";
        }
    }
    catch (invalid_argument e)
    {

        print("The program will now terminate");
        return 0;
    }
    catch (...)
    {

        print("Please enter a number between 1 and 25 inclusive");
        goto start;
    }

    letters.clear();
    notIn.clear();

    fo(i, 0, numL)
    {
        letters[i + 1] = '_';
    }

    print("I will suggest a word for you to guess. You can guess this, or any other letter. If the letter you guessed was not in the word, type .[letter1][letter2][...]   eg, if you guessed an 'e' and a 'j':");
    print("'.ej'");
    print("If the letter was in the word, type the letter in the place it would fit, surrounded by _'s. eg: if the word is 5 letters with a b in the first spot and your guess of a is in the second and fifth place:");
    print("'_a__a' or 'ba__a'");
    println;

inLoop:
    print("     COMMANDS:");
    print("     type '/exit' to quit the program");
    print("     type '/restart' to choose a new word");
    print("     type '/help' to see this menu again");

    while (true)
    {
        string curWrd = getWrd(numL, letters);
        println;
        print("Current word:       " << curWrd);

        if (curWrd.find('_') == -1)
        {
            print("The word has been guessed. I will now reset.");
            goto start;
        }

        print("Incorrect letters:  " << getWrong(notIn));

        set<char> dontCount;
        vstr posWords;

        fo(i, 0, numL)
        {
            if (letters[i + 1] != '_')
            {
                dontCount.insert(letters[i + 1]);
            }
        }
        for (auto x : notIn)
        {
            dontCount.insert(x);
        }

        //this is wrong, right now, if hap__ it shows happy which is wrong
        fo(i, 0, 26)
            count[i] = 0;

        for (auto wrd : words)
        {
            if (wrd.length() == numL)
            {
                bool works = true;

                fo(i, 0, numL)
                {
                    if (letters[i + 1] != '_')
                    {
                        if (letters[i + 1] != wrd[i])
                        {
                            works = false;
                            break;
                        }
                    }
                    else
                    {
                        if (dontCount.count(wrd[i]) != 0)
                        {

                            works = false;
                            break;
                        }
                    }
                }

                if (!works)
                {
                    continue;
                }

                posWords.push_back(wrd);
                set<char> uniqueLet; // stores every unique letter in this possible word

                for (auto let : wrd)
                {
                    uniqueLet.insert(let);
                }
                for (auto let : uniqueLet)
                {
                    count[let - 'a']++;
                }
            }
        }

        int maxC = -1;
        char guess = 'a';

        fo(i, 0, 26)
        {
            if (count[i] > maxC && dontCount.count(i + 'a') == 0)
            {
                maxC = count[i];
                guess = i + 'a';
            }
        }

        // correspondence - 14
        //hungry
        //happy

        print("you should guess:   " << guess);

        if (posWords.size() == 0)
        {
            print("That word is not in my selected dictionary");
        }
        elif (posWords.size() <= 5)
        {
            print("Here are the words I think it could be:");
            for (auto wrd : posWords)
            {
                print("-> " << wrd);
            }
        }

        usrT;
        cin >> input;
        input = lowerCase(input);

        if (input.compare("/exit") == 0)
        {
            return 0;
        }
        elif (input.compare("/restart") == 0)
        {
            goto start;
        }
        elif (input.compare("/help") == 0)
        {
            goto inLoop;
        }

        if (input[0] == '.')
        {
            fo(i, 1, input.size())
            {
                notIn.insert(input[i]);
            }

            fo(i, 0, numL)
            {
                if (notIn.count(letters[i + 1]) != 0)
                {
                    letters[i + 1] = '_';
                }
            }
        }
        else
        {
            fo(i, 0, input.length())
            {
                if (input[i] != '_')
                {

                    letters[i + 1] = input[i];

                    if (notIn.count(input[i]) != 0)
                    {
                        notIn.erase(input[i]);
                    }
                }
            }
        }
    }
    return 0;
}

/*

The action being done is favoured. So if an incorrect letter was typed eg: qw__ instead of _w__
this can be corrected with .q, which will result in _w__

similarly, you can get rid of a letter being ignored by putting it in your guess
if .ab is gollowed by __a__d
a will be deleted from the ignore list



This program only works with 1 word (no spaces) and no special characters (only the 26 letters in the latin alphabet allowed)

The 'wordsShort.txt' is best to use most of the time, but for words that are short (4 letters or less), rather use 'wordsMedium'

'wordsMedium' is more consistent, wordsShort sometimes cannot find the word at all (it only has 10k words - such as 'yearn') so you end up with ± 20 guesses

The program can be made faster by reusing the possible words from the previosu round, but to account for humanerrors, the list is regenerated each time
*/