#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

long length(char cstring[]) {
    long count = 0;
    while (cstring[count] != '\0')
        count++;
    return count;
}

int fill(int lineLength, istream& inf, ostream& outf)
{
    int response = 0;
    // default returns 0 if lines are valid and not exceeding the
    // max line length
    char c;
    char word[1000] = "";
    int lineCounter = 0;
    int wordCounter = 0;
    int spacing = 0;
    int ending = 0;
    int prevSpace = 0;
    int finishedWord = 0;

    // --------------------------------------------------

    char wordWithSpace[1000] = "";
    int wordCounterWithSpace = 0;

    // --------------------------------------------------

    int newPara = 1;
    char para[] = "#P#";
    int wordLength = -1;

    while (inf.get(c))
    {
        //if (c == '\n')
        //{
            //cerr << "[" << "\n" << "]";
            //cerr << spacing;
        //}

        //cerr << "space using pre, ("<< wordLength << " , " << spacing << " , " << lineCounter << endl;
        if (ending == 1 )
            // start word on new line if previous already at max
        {
            prevSpace = 0;
            lineCounter = 0;
            outf << '\n';
            cerr << "k";
            ending = 0;
        }

        if (c == ' ' || c == '\n')
        {
            // add space depending on what last character was
                // of the now completed current word
            if (prevSpace != 1)
            {
                newPara = 1;
                for (int i = 0; i < 4; i++)
                {
                    if (word[i] != para[i]) {
                        newPara = 0;
                    }
                }
                finishedWord = 1;
                // ---------------------------------------- cerr << word << ' ';
                
                if ((word[wordCounter - 1] == '.') || (word[wordCounter - 1] == '?'))
                {
                    spacing = 2;
                }
                else
                {
                    spacing = 1;
                }
                // cerr << "{" << word << " and " << word[wordCounter-1] << wordCounter-1 << "}";
                //cerr << length(word) << "," << lineCounter << c << endl;
                //cerr << lineCounter;
                if (wordCounter > 0) {
                    if (newPara == 1)
                    {
                        spacing = 0;
                        // new line added before the next word
                        ending = 1;
                        newPara = 0;
                        // new paragraph word recognized
                        // reset values for next word to be processed
                        lineCounter = 0;
                        wordCounter = 0;
                        finishedWord = 1;
                    }
                    else
                    {
                        // scenario where the special finishing characters aren't chosen
                        // but a space character is reached
                        wordLength = length(word);
                        if (wordLength >= lineLength)
                            // checks whether the extra space for the special finishing
                            // last characters can fit in the current line
                        {
                            finishedWord = 0;
                            while (finishedWord != 1)
                            {
                                if (wordLength > lineLength)
                                {
                                    cerr << "(6)";
                                    outf << endl;
                                    for (int j = wordCounter; j < wordCounter + lineLength; j++)
                                    {
                                        outf << word[j];
                                        // return max line length sized portions of the word
                                    }

                                    // make new line for word that exceeds the line length
                                    wordLength -= lineLength;
                                    wordCounter += lineLength;
                                    finishedWord = 0;
                                    // next line for the next word since current line is full
                                    lineCounter = 0;
                                    prevSpace = 0;
                                }
                                else if (wordLength == lineLength)
                                {
                                    for (int j = wordCounter; j < wordCounter + lineLength; j++)
                                    {
                                        outf << word[j];
                                        // return max line length sized portions of the word
                                    }
                                    finishedWord = 1;
                                    wordCounter = 0;
                                    wordCounterWithSpace = 0;
                                    ending = 1;
                                    prevSpace = 0;
                                }
                                else if (length(wordWithSpace) < lineLength)
                                {
                                    for (int j = wordCounter; j < length(word); j++)
                                    {
                                        cerr << "(7)";
                                        outf << word[j];
                                        lineCounter += 1;
                                    }
                                    ending = 0;
                                    if (spacing == 1)
                                    {
                                        wordWithSpace[0] = ' ';
                                    }
                                    else if (spacing == 2)
                                    {
                                        wordWithSpace[0] = ' ';
                                        wordWithSpace[1] = ' ';
                                    }
                                    // no need for new line yet since the last portion
                                    // of the word is contained within the max word length
                                    finishedWord = 1;
                                    wordCounterWithSpace = spacing;
                                    wordCounter = 0;
                                    prevSpace = 0;
                                }
                            }
                        }
                        else if (length(wordWithSpace) + lineCounter >= lineLength)
                        {
                            // returns the current word but marked down as will not fit
                            // single spacing with the next word of minimum size 1
                            cerr << "(9)";
                            outf << '\n';
                            lineCounter = 0;
                            for (int j = 0; j < length(word); j++)
                            {
                                outf << word[j];
                                lineCounter += 1;
                            }
                            // output the word and no new line since within max line length
                            finishedWord = 1;
                            wordCounter = 0;
                            wordCounterWithSpace = 0;
                        }
                        else
                        {
                            // returns the current word and marks down single spacing
                            // will be within the max line length
                            //cerr << "[";
                            cerr << "(10)";
                            for (int j = 0; j < length(wordWithSpace); j++)
                            {
                                outf << wordWithSpace[j];
                                lineCounter += 1;
                                //cerr << lineCounter;
                            }
                            //cerr << "]";
                            ending = 0;
                            if (spacing == 1)
                            {
                                wordWithSpace[0] = ' ';
                            }
                            else if (spacing == 2)
                            {
                                wordWithSpace[0] = ' ';
                                wordWithSpace[1] = ' ';
                            }
                            // output the word and no new line since within max line length
                            finishedWord = 1;
                            wordCounter = 0;
                            wordCounterWithSpace = spacing;
                        }
                    }
                }
                cerr << spacing;
                prevSpace = 1;
            }
        }
        else
        {
        // adds the next read in character to the current word
        // array given that the word isn't finished (i.e. no space)
            if (c != '\n') {
                word[wordCounter] = c;

                // --------------------------------------

                wordWithSpace[wordCounterWithSpace] = c;

                // --------------------------------------

                wordCounter += 1;
                word[wordCounter] = '\0';

                // --------------------------------------

                wordCounterWithSpace += 1;

                wordWithSpace[wordCounterWithSpace] = '\0';

                // --------------------------------------

            }
            else {
                word[wordCounter] = '\0';

                // --------------------------------------

                wordWithSpace[wordCounterWithSpace] = '\0';

                wordCounterWithSpace += 1;

                // --------------------------------------

                wordCounter += 1;
                cerr << "NEW LINE";
            }
        //cerr << c << "ye";
        ending = 0;
        //spacing = 0;
        prevSpace = 0;
        }
        
    // scenario where the special finishing characters aren't chosen
     
    }
    if (ending == 1 )
            // start word on new line if previous already at max
        {
            prevSpace = 0;
            lineCounter = 0;
            outf << '\n';
            cerr << "k";
            ending = 0;
        }
    if (prevSpace != 1)
    {
        newPara = 1;
        for (int i = 0; i < 4; i++)
        {
            if (word[i] != para[i]) {
                newPara = 0;
            }
        }
        finishedWord = 1;

        if ((word[wordCounter - 1] == '.') || (word[wordCounter - 1] == '?'))
        {
            spacing = 2;
        }
        else
        {
            spacing = 1;
        }
        if (wordCounter > 0) {
            if (newPara == 1)
            {
                spacing = 0;
                // new line added before the next word
                ending = 1;
                newPara = 0;
                // new paragraph word recognized
                // reset values for next word to be processed
                lineCounter = 0;
                wordCounter = 0;
                finishedWord = 1;
            }
            else
            {
                // scenario where the special finishing characters aren't chosen
                // but a space character is reached
                wordLength = length(word);
                if (wordLength >= lineLength)
                    // checks whether the extra space for the special finishing
                    // last characters can fit in the current line
                {
                    finishedWord = 0;
                    while (finishedWord != 1)
                    {
                        if (wordLength > lineLength)
                        {
                            cerr << "(6)";
                            outf << endl;
                            for (int j = wordCounter; j < wordCounter + lineLength; j++)
                            {
                                outf << word[j];
                                // return max line length sized portions of the word
                            }

                            // make new line for word that exceeds the line length
                            wordLength -= lineLength;
                            wordCounter += lineLength;
                            finishedWord = 0;
                            // next line for the next word since current line is full
                            lineCounter = 0;
                            prevSpace = 0;
                        }
                        else if (wordLength == lineLength)
                        {
                            for (int j = wordCounter; j < wordCounter + lineLength; j++)
                            {
                                outf << word[j];
                                // return max line length sized portions of the word
                            }
                            finishedWord = 1;
                            wordCounter = 0;
                            wordCounterWithSpace = 0;
                            ending = 1;
                            prevSpace = 0;
                        }
                        else if (length(wordWithSpace) < lineLength)
                        {
                            for (int j = wordCounter; j < length(word); j++)
                            {
                                cerr << "(7)";
                                outf << word[j];
                                lineCounter += 1;
                            }
                            ending = 0;
                            if (spacing == 1)
                            {
                                wordWithSpace[0] = ' ';
                            }
                            else if (spacing == 2)
                            {
                                wordWithSpace[0] = ' ';
                                wordWithSpace[1] = ' ';
                            }
                            // no need for new line yet since the last portion
                            // of the word is contained within the max word length
                            finishedWord = 1;
                            wordCounterWithSpace = spacing;
                            wordCounter = 0;
                            prevSpace = 0;
                        }
                    }
                }
                else if (length(wordWithSpace) + lineCounter >= lineLength)
                {
                    // returns the current word but marked down as will not fit
                    // single spacing with the next word of minimum size 1
                    cerr << "(9)";
                    outf << '\n';
                    lineCounter = 0;
                    for (int j = 0; j < length(word); j++)
                    {
                        outf << word[j];
                        lineCounter += 1;
                    }
                    // output the word and no new line since within max line length
                    finishedWord = 1;
                    wordCounter = 0;
                    wordCounterWithSpace = 0;
                }
                else
                {
                    // returns the current word and marks down single spacing
                    // will be within the max line length
                    cerr << "(10)";
                    for (int j = 0; j < length(wordWithSpace); j++)
                    {
                        outf << wordWithSpace[j];
                        lineCounter += 1;
                        //cerr << lineCounter;
                    }
                    ending = 0;
                    if (spacing == 1)
                    {
                        wordWithSpace[0] = ' ';
                    }
                    else if (spacing == 2)
                    {
                        wordWithSpace[0] = ' ';
                        wordWithSpace[1] = ' ';
                    }
                    // output the word and no new line since within max line length
                    finishedWord = 1;
                    wordCounter = 0;
                    wordCounterWithSpace = spacing;
                }
            }
        }
        cerr << spacing;
        prevSpace = 1;
    }
    outf << '\n';
    return response;
}
int main()
{
    const int MAX_FILENAME_LENGTH = 100;
    for (;;)
    {
        cout << "Enter input file name (or q to quit): ";
        char filename[MAX_FILENAME_LENGTH];
        cin.getline(filename, MAX_FILENAME_LENGTH);
        if (strcmp(filename, "q") == 0)
            break;
        ifstream infile(filename);
        if (!infile)
        {
            cerr << "Cannot open " << filename << "!" << endl;
            continue;
        }
        cout << "Enter maximum line length: ";
        int len;
        cin >> len;
        cin.ignore(10000, '\n');
        int returnCode = fill(len, infile, cout);
        cout << endl << "|" << endl << "Return code is " << returnCode << endl;
    }
}