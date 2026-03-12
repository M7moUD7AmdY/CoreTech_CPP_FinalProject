// /*
// sequance find the long sequance                                         
// //    1 2 3 4 9 10 11 13 14 15 20 21 22 23 24 30 31 32 33 */

// #include <iostream>
// using namespace std;
// //1 3 5  6 7 9 11 13 18 23 28 33 
// int max_arr(int *arr , int size)
// {
//     int count=0;
//     int max_count=0;
    
//     for(int i=0;i<size-1;i++)
//     {
//         if(arr[i]==(arr[i+1]-1))
//         {
//             cout<<"in IF "<<endl;
//             count++;
//             cout<<count<<endl;
//              if(max_count < count)
//             {
//                 max_count=count;
                
//             }

//         }
//         else
//         {
           
//             count=1;

//         }

        

//     }
//     return max_count;


// }

// #include <string>
// #include <algorithm>

// bool IsAnagram2(string s1, string s2)
// {
//     if(s1.size() != s2.size())
//         return false;

//     sort(s1.begin(), s1.end());
//     sort(s2.begin(), s2.end());

//     return s1 == s2;
// }

// // bool IsAngram(S1,S2);
// // S1 = cat , s2 = hat -> false
// // S1 = cat , s2 = act  -> true


// bool IsAngram(string S1,string S2)
// {
//     int count=0;
//     for(int i=0;i<S2.size();i++)
//     {
        

//         if(S1.find_first_of(S2[i])!=string::npos)
//         {
//             cout<<"Test: "<<S1.find_first_of(S2[i])<<endl;
//             cout<<"Find: "<<S2[i]<<endl;
//             count++;
//         }
    
//     }
//     if(count == S1.size())
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
    



// }

// char MostRepeted(string arr)
// {
//     char most;
//     int count=0;
//     int max_count=0;
//     for(int i=0;i<arr.size();i++)
//     {
//         for(int j=0;j<arr.size();j++)
//         {
//             if(arr[i] == arr[j])
//             {
//                 count++;
//             }

//         }
//         if(count > max_count)
//         {
//             most=arr[i];
//             cout<<"Most:"<<most<<count<<endl;
//             max_count=count;
//             count=0;
//         }
//         count=0;

//     }
//     return most;

// }


// string longestPalindrome(string s) {
//         if (s.empty()) return "";

//         int start = 0;
//         int maxLen = 1;

//         for (int i = 0; i < s.size(); i++) {
//             // odd length
//             int left = i, right = i;
//             while (left >= 0 && right < s.size() && s[left] == s[right]) {
//                 if (right - left + 1 > maxLen) {
//                     start = left;
//                     maxLen = right - left + 1;
//                 }
//                 left--;
//                 right++;
//             }

//             // even length
//             left = i;
//             right = i + 1;
//             while (left >= 0 && right < s.size() && s[left] == s[right]) {
//                 if (right - left + 1 > maxLen) {
//                     start = left;
//                     maxLen = right - left + 1;
//                 }
//                 left--;
//                 right++;
//             }
//         }

//         return s.substr(start, maxLen);
//     }

// int main()
// {
//  string s = longestPalindrome("babad") ; 
// cout<<s<<endl;
//  return 0 ; 
// }

#include <iostream>
#include "image/Image.hpp"
#include "turtle/Turtle.hpp"
#include "parser/ScriptParser.hpp"

// int main()
// {
//     cImage image(5, 5);
//     cTurtle turtle;
//     turtle.SetImage(&image);
//     turtle.PenColor("red");

//  LineParsing("move forward 2", turtle,image);





//     // for(int i=0;i<200;i++)
//     // {
//     //     for(int j=0;j<200;j++)
//     //     {     
//     //         image.SetPixel(i,j,"red");

//     //     }

//     // }

  
   

// if (image.SavePPM("test.ppm"))
// {
//     std::cout << "Saved successfully\n";
//     system("FoxViewPPM.exe test.ppm");
// }
// else
// {
//     std::cout << "Failed to save image\n";
// }
//     return 0;
// }

#include <iostream>
#include "image/Image.hpp"

int main()
{
    int width = 512;
    int height = 512;

    cImage image(width, height);

    image.Fill("white");

    if (image.SavePPM("white.ppm"))
    {
        std::cout << "Image generated successfully\n";
    }
    else
    {
        std::cout << "Failed to save image\n";
        return 1;
    }

    return 0;
}