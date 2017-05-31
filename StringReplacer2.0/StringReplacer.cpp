#include "stdafx.h"
#include "StringReplacer.h"


template<class T>
static void SortVector(vector<T> &v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                T temp = v[j + 1];
                v[j + 1] = v[j];
                v[j] = temp;
            }
        }
    }
}


void StringReplacer::ProcessFile(const string &path, const string &word, OnNewMatchCallback onNewMatch, OnFileProcessedCallback onFileProcessed)
{
    string str = ReadFileContent(path);
    vector<string> strs = DivideString(str);
    for (int i = 0; i < strs.size(); i++)
    {
        strs[i] = DeleteWordFromString(strs[i], word, onNewMatch);
    }
    SortVector<string>(strs);
    onFileProcessed(strs);
    return;
}


string StringReplacer::DeleteWordFromString(string &str, const string &word, OnNewMatchCallback onNewMatch)
{
    int pos;
    while (str.npos != (pos = str.find(word, 0)))
    {
        int secPartOffset = pos + word.length();
        string firstPart = str.substr(0, pos);
        string secPart = str.substr(secPartOffset, str.length() - secPartOffset);
        str = firstPart + secPart;
        onNewMatch();
    }
    return str;
}


vector<string> StringReplacer::DivideString(const string &str)
{
    vector<string> strs;
    string::const_iterator prevIt = str.begin();
    string::const_iterator it;
    while (str.end() != (it = find(prevIt, str.end(), '\n')))
    {
        string newStr = str.substr(prevIt - str.begin(), it - prevIt);
        it++;
        prevIt = it;
        strs.push_back(newStr);
    }
    if (str.end() != prevIt && *prevIt)
    {
        string newStr = str.substr(prevIt - str.begin(), str.end() - prevIt);
        strs.push_back(newStr);
    }
    return strs;
}


void StringReplacer::SaveStringsToFile(const string &path, const vector<string> &strs)
{
    ofstream fileStream;
    fileStream.open(path);
    vector<string>::iterator it;
    for (int i = 0; i < strs.size(); i++)
    {
        fileStream << strs[i];
        if (strs.size() - 1 != i)
        {
            fileStream << '\n';
        }
    }
}


string StringReplacer::ReadFileContent(const string &path)
{
    ifstream t(path);
    return string(
        istreambuf_iterator<char>(t),
        istreambuf_iterator<char>()
    );
}
