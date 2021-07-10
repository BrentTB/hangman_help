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
    println;

    // vstr wordChoices = {"oh", "an", "be", "is", "by", "on"};
    // vstr wordChoices = {"oil", "log", "bin", "dog", "win", "aid"};
    // vstr wordChoices = {"spit", "cast", "curl", "sofa", "hole", "tell"};
    // vstr wordChoices = {"shine", "sound", "fibre", "scene", "model", "drama"};
    // vstr wordChoices = {"common", "module", "fossil", "dollar", "mutual", "rotate"};
    vstr wordChoices = {"cfvghbjn", "yearn", "remix", "overtake", "liquid", "devil"};
    


    fo(txtChoose, 1, 6)
    {

        int sumWrong=0;

        int count[26];
        vstr words;             // array of all words
        vstr tmp;               // array used to help fill poswords
        set<char> notIn;        // all of the letters not in the word;
        string x;               // temp string used to read from txt file
        string input;           // the string used when the user enters information
        int numL = 0;           // the number of letters in the word
        map<int, char> letters; // maps an index to teh letter at said index

        words.reserve(500000);

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
        print("Source: " << inputF);

        {
            ifstream cin(inputF); // 370000
            while (cin >> x)
            {
                x = lowerCase(x);
                words.push_back(x);
            }
        }

        for (auto wordChoice : wordChoices)
        {

        start:
            numL = wordChoice.length();

            letters.clear();
            notIn.clear();

            fo(i, 0, numL)
            {
                letters[i + 1] = '_';
            }

        inLoop:

            while (true)
            {
                string curWrd = getWrd(numL, letters);
                // print(curWrd);

                if (curWrd.find('_') == -1)
                {
                    // print("Correct!");
                    break;
                }

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

                input = "";
                bool in = false;

                fo(i, 0, numL)
                {
                    if (wordChoice[i] == guess)
                    {
                        input.push_back(guess);
                        in = true;
                    }
                    else
                    {
                        input.push_back('_');
                    }
                }
                if (!in)
                {
                    input = "";
                    input.push_back('.');
                    input.push_back(guess);
                }

                input = lowerCase(input);

                // print("Result: " << input);

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
            print("word: "<< wordChoice <<"\tcount: " << notIn.size());
            sumWrong+=notIn.size();
        }
        print("total wrong:\t"<<sumWrong);
            println;
    }
    return 0;
}
