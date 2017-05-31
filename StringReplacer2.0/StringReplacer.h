#pragma once
#include <string>
#include <functional>
#include <atomic>
#include <iostream>
#include <fstream>
using namespace std;


class StringReplacer
{
public:
    typedef function<void()> OnNewMatchCallback;
    typedef function<void(const vector<string>&)> OnFileProcessedCallback;
    StringReplacer() = delete;
public:
    static void ProcessFile(const string &path, const string &word, OnNewMatchCallback, OnFileProcessedCallback);
    static void SaveStringsToFile(const string &path, const vector<string> &strings);
private:
    static string ReadFileContent(const string &path);
    static vector<string> DivideString(const string& str);
    static string DeleteWordFromString(string &str, const string &word, OnNewMatchCallback);
};
