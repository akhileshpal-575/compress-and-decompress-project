#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void outputvector(vector<string> v)
{
    ofstream fout("vector.txt");

    for(int i=0;i<v.size();i++)
    {
        fout<<i<<"-->"<<v[i]<<endl;
    }
    fout.close();
}

void outputmap(map<string, int> map)
{
    ofstream fout("map.txt");

    for(auto &pr:map)
    {
        fout<<pr.first<<"-->"<<pr.second<<endl;
    }
}



void compress(string inputFileName) {
    ifstream input(inputFileName);
    ofstream compressed("compressed_"+inputFileName);
    map<string, int> wordMap;
    int wordCount = -1;
    string word;
    string line;

    streampos inputSize = input.tellg();
    input.seekg(0, ios::end);
    inputSize = input.tellg() - inputSize;
    input.seekg(0, ios::beg);

    while (getline(input, line)) {
        istringstream iss(line);
        while (iss >> word) {
            if (isdigit(word[0])) { 
                    compressed << '#' << word<<' '; 
            }
            else{
                if(word.length() < (log10(wordCount) + 1) )
                {
                    compressed<<word<<' ';
                }
                else{
                    auto it=wordMap.find(word);
                    if(it==wordMap.end())
                    {
                        compressed<<word<<' ';
                        wordCount++;
                        wordMap.insert({word,wordCount});
                    }
                    else{
                        compressed<<(*it).second<<' ';
                    }
                }
            }
        }
        compressed << '^' <<' ';

    }
    
    compressed.close();
    ifstream compressedInput("compressed_"+inputFileName);
    streampos compressedSize = compressedInput.tellg();
    compressedInput.seekg(0, ios::end);
    compressedSize = compressedInput.tellg() - compressedSize;
    cout << "\nCompression ratio: " << (double)compressedSize / (double)inputSize * 100.0 << "%" << endl<<endl;
    input.close();
    outputmap(wordMap);  // output list of map.
}

void decompress(string inputFileName) {
    ifstream input(inputFileName);
    vector<string> wordList;
    string word;

    ifstream compressedInput(inputFileName);
    ofstream decompressed("de"+inputFileName);
    int temp=1;
    while (input >> word) 
    {
        if (isdigit(word[0])) { 
            
            if(temp==1){
                decompressed << wordList[stoi(word)] ;
                temp=0;
            }
            else{
                decompressed << ' '<< wordList[stoi(word)] ;
            }
        }
        else{
            if(word[0]=='#')
            {
                if(temp==1){
                    decompressed<<word.substr(1) ;
                    temp=0;
                }
                else{
                    decompressed<< ' ' << word.substr(1);
                }
            }
            else if (word[0] == '^') {
                decompressed << '\n';
                temp=1;
            }
            else{
                if(word.length() < (log10(wordList.size()) + 1))
                {
                    if(temp==1){
                        decompressed<<word;
                        temp=0;
                    }
                    else{
                        decompressed<<' '<<word;
                    }
                }
                else{
                    wordList.push_back(word);

                    if(temp==1){
                        decompressed<<word;
                        temp=0;
                    }
                    else{
                        decompressed<<' '<<word;
                    }
                }
            }
        }
    }
    compressedInput.close();
    decompressed.close();
    outputvector(wordList);  // output list of vector.
}



int main() {
    string fileName;

    char choice;
    cout<<"1. Compress"<<endl;
    cout<<"2. Decompress"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    switch(choice){
        case '1':
            cout<<"Enter file name: ";
            cin>>fileName;
            compress(fileName);
            cout<<"File compressed successfully"<<endl<<endl;
            break;
        case '2':
            cout<<"Enter file name: ";
            cin>>fileName;
            decompress(fileName);
            cout<<"File Decompressed successfully"<<endl<<endl;
            break;
        default:
            cout<<"Invalid Choice"<<endl;
    }

    return 0;
}