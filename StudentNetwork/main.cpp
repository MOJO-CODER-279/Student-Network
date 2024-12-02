#include <iostream>
using namespace std;

int main()
{
    string uniArr[5]={"a","b","c","d","e"};
    int uniAdr[5] = {0};
    int indx = -1;
    string FriArr[15] = {
                            "b","d","e","c","a",
                            "a","d","e","a","b",
                            "c","e","a","b","d"
                        };

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<15; j++)
        {
            if(uniArr[i]==FriArr[j])
            {
                uniAdr[i]++;
            }
        }

        if((indx==-1) || (uniAdr[indx]<uniAdr[i]))
        {
            indx = i;
        }
    }

    cout << uniArr[indx] << " is the most Famous Student of Class.";
    cout << " Having Max Friendships: " << uniAdr[indx] << endl;

    return 0;
}
