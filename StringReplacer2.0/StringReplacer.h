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
    typedef function<void(vector<string>)> OnFileProcessedCallback;
    StringReplacer() = delete;
public:
    static void ProcessFile(string path, OnNewMatchCallback, OnFileProcessedCallback);
    static void SaveStringsToFile(string path, vector<string> strings);
private:
    static string ReadFileContent(string path);
    static vector<string> DivideString(string str);
    static string DeleteWordFromString(string str, string word, OnNewMatchCallback);
};
