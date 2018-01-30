//
//  align.cpp
//  dna_alignment
//
//  Created by Erika DeBenedictis on 1/27/13.
//  Copyright (c) 2014 California Institute of Technology. All rights reserved.
//
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// scoring values
#define GAP_SCORE -5
#define MISMATCH -1
#define MATCHING 2


struct align_test{
    string fowl = "GAGAGAGTGGTCGTGAGTATTGACCGTTTCTTAAGGGTTCGAGATCAACGTGGGAATGTGCTATTGTCTCCCGAAGAGGTTAGCGAAACGCAGGGAACAG";
    string chicken = "GAGAGAGTGGTCGTGAGTATTGACCGTTTCTTAAGAGTTCGAGATCAGCGTGGAAATGTAATCCTGTCTCCTGAAGAGGTTAGCGAAACGCAGGGAACAG";
    string A_swine_nigeria = "TATGAGTCTTTTAACCGAGGTCGAAACGTACGTTCTTTCTATCATTCCGTCAGGCCCCCTCAAAGCCGAGATCGCGCAGAGACTGGAAAGTGTATTTGCAGGAAAGAACACAGATCTTGAGGCTCTCATGGAATGGCTAAAGACAAGACCAATCTTGTCACCTCTGACTAAGGGAATTTTAGGATTTGTGTTCACGCTCACCGTGCCCAGTGAGCGAGGACTGCAGCGTAGACGTTTTGTCCAG";
    string A_Ghana = "TATATGAGTCTTCTAACCGAGGTCGAAACGTTCGTTCTTTCTATCATACCGTCAGGCCCCCTCAAAGCCGAGATCGCGCAGAGACTGGAAAGTGTCTTTGCAGGAAAGAACACAGATCTTGAGGCTCTCATGGAATGGCTAAAGACAAGACCAATCTTGTCACCTCTGACTAAGGGAATTTTAGGATTTGTGTTCCCGCTCACCGTGCCCAGTGAACGAGGACTGCAGCGTAGACGTTTTGTCCAAAA";
    align_test(){}
};

/**
 * @brief Packages the score and instruction string the align function returns
 */
struct align_result {
    int score;      // score of this alignment
    string inst;    // instruction on how to align the inputs

    align_result(int s, string i) {
        this->score = s;
        this->inst = i;                              
    }
    align_result() {
        this->score = 0;
        this->inst = "";
    }
};

// memo_type will allow us to hash the string input to align
// with its output for memoization
typedef unordered_map<string, align_result> memo_type;                  

int computeScore(string s, string t){
    int score = 0;
    int length = s.length();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    int longerlength = t.length();
    if(s.length() > t.length()){
        length = t.length();
        longerlength = s.length();
    }
    for(int i = 0; i < length; ++i){
        if(s.substr(i,1).compare(t.substr(i,1)) == 0){
            score += MATCHING;
        }else if (s.substr(i,1) != "-" && t.substr(i,1) != "-"){
            score += MISMATCH;
        }
    }
    score += GAP_SCORE*(longerlength - length);
    return score;
}
/**
 * @brief Function takes two strings, s and t, and produces an align_result
 * of the highest alignment score and its corresponding instruction str.
 */
align_result align(string s, string t, memo_type &memo) {
    // if this result is memoized, use recorded result
    string key = s + "," + t;
    if (memo.count(key) > 0){
      return memo[key];
    }

    /*
      TODO: calculate the highest score for an alignment of s and t
      - Base cases: s or t is empty
      - Recursive calls                                                                        
     */
    if(s.length() == 0 &&  t.length() != 0){
        return align_result(computeScore(s,t), std::string((t.length() - s.length()), 't'));
    }else if(s.length() != 0 &&  t.length() == 0){
        return align_result(computeScore(s,t), std::string((s.length() - t.length()),'s'));
    } else if(s.length() == 0 &&  t.length() == 0){
        return align_result(computeScore(s,t),"");
    }
    align_result answer;
//gap on S
    align_result gapOnSResult = align_result(GAP_SCORE, "t");
    align_result gaponSRecursive = align(s,t.substr(1),memo);
    gapOnSResult.score += gaponSRecursive.score;
    gapOnSResult.inst += gaponSRecursive.inst;
    answer = gapOnSResult;
//gap on T
    align_result gapOnTResult = align_result(GAP_SCORE, "s");
    align_result gaponTRecursive = align(t,s.substr(1), memo);
    gapOnTResult.score += gaponTRecursive.score;
    gapOnTResult.inst += gaponTRecursive.inst;
    if(answer.score < gapOnTResult.score){
        answer = gapOnTResult;
    }
//gap on neither
    int tempscore = computeScore(s.substr(0,1), t.substr(0,1));
    string tempinst = "s";
    if(tempscore == MISMATCH){
        tempinst = "*";
    }else if (tempscore == MATCHING){
        tempinst = "|";
    }
    align_result gapNeitherResult = align_result(tempscore, tempinst);
    align_result gapNeitherRecursive = align(s.substr(1),t.substr(1),memo);
    gapNeitherResult.score += gapNeitherRecursive.score;
    gapNeitherResult.inst += gapNeitherRecursive.inst;
    if(answer.score < gapNeitherResult.score){
        answer = gapNeitherResult;
    }

    /* Before you return your calculated  align_result object,
       memoize it like so:*/
    
    memo[key] = answer;
    return answer;
}

/**
 * @brief Wrapper function to print the results of align
 */
void DNA_align(string s, string t) {
    cout << endl << "Calling DNA align on strings " << s << ", " << t << endl;

    // create the memoization system
    memo_type memo;

    align_result answer = align(s, t, memo);
    string ans = answer.inst;
    int score = answer.score;

    // Printing section
    // line where string s will be printed, spaces inserted
    string line1 = "";
    // line where string t will be printed, spaces inserted
    string line2 = "";
    // description of the relationship between s and t here (* | s t)
    string line3 = "";

    int j = 0;      // running index in s
    int k = 0;      // running index in t

    for (unsigned int m = 0; m < ans.length(); m++) {
        // i is the next element in our instruction string ans
        string i = ans.substr(m, 1);

        // only in s
        if(i.compare("s") == 0){
            line1 += s[j]; j++;
            line2 += " ";
            line3 += "s";
        }

        // only in t
        else if (i.compare("t") == 0){
            line1 += " ";
            line2 += t[k]; k++;
            line3 += "t";
        }

        // mismatch
        else if (i.compare("*") == 0){
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "*";
        }

        // match
        else {
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "|";
        }
    }
    cout << line1 << endl << line2 << endl << line3 << endl;
    cout << "Score for this alignment: " << score << endl;
}

int main(){
    //custom test cases
    align_test mytests = align_test();
    // some test cases to begin with
    DNA_align("",   "a");
    DNA_align("b",  "");
    DNA_align("a", "a");
    DNA_align("b",  "a");
    DNA_align("b",  "ba");
    DNA_align("ab", "ba");
    DNA_align("ab", "b");
    DNA_align(mytests.fowl, mytests.chicken);
    DNA_align(mytests.A_swine_nigeria, mytests.A_Ghana);
    return 0;
}