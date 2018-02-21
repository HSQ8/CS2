#   ____   ____      ____     __        __                                           
#  / ___| / ___|    |___ \    \ \      / /   __ _   _ __   _ __ ___    _   _   _ __  
# | |     \___ \      __) |    \ \ /\ / /   / _` | | '__| | '_ ` _ \  | | | | | '_ \ 
# | |___   ___) |    / __/      \ V  V /   | (_| | | |    | | | | | | | |_| | | |_) |
#  \____| |____/    |_____|      \_/\_/     \__,_| |_|    |_| |_| |_|  \__,_| | .__/ 
#                                                                             |_|    
#                          
# README
# this solution takes a string and checks whether a permutation 
# of this string is a palindrome.
# It takes O(N!) space and O(N!) time
# 
# I also included an O(N) solution in both space and time,
# I accomplish this by producing a counter object in python 
# that counts the number of times each unique letter occurs
# in this case, we assume that a valid palindrome must either have
# all even counts of each unique letter or have all even counts and 
# one odd count of a unique letter.
# 
# In this case, the palindrome would be the print of all the even 
# letters half a time on one side, with the odd letters in the middle,
# and the remaining half of even letters on the other side printed
# in reverse
# 
# to run both functions, just comment / uncomment the appropriate test
# cases, I'm not going to write a user interface to switch between the 
# two. To test your own string, just follow the format of the 
# existing test cases.
# 
# The drawback of the slow implementation is that, well, its slow,
# but It can find all palindromes with slight modification
# 
# if we are only interested in one, then we can use the fast one
# which only fines one palindrome.
# 
# 

####################################################################################
#  ____    _        ___   __        __    __  __   _____   _____   _   _    ___    ____  
#/ ___|  | |      / _ \  \ \      / /   |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \ 
#\___ \  | |     | | | |  \ \ /\ / /    | |\/| | |  _|     | |   | |_| | | | | | | | | |
# ___) | | |___  | |_| |   \ V  V /     | |  | | | |___    | |   |  _  | | |_| | | |_| |
#|____/  |_____|  \___/     \_/\_/      |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/ 

def isPalindrome(_string):
    lst = list(_string)
    copylst = lst[:]
    lst.reverse()
    return lst == copylst

def producePermutation(prefix, _string):
    #print("depth" + str(len(prefix)))
    if(len(_string) == 0):
        if(isPalindrome(prefix)):
            print(prefix)
            return prefix

    else:
        for i in range(len(_string)):
            strg = producePermutation(prefix + _string[i], _string[0:i] + _string[i + 1:])
            if (not strg == None ):
                return strg
        return None

def checkAnagramSlow(_string):
    print("running test case: " + _string)
    strg = producePermutation("",_string)
    if(not strg == None):
        print("\"" + _string + "\"" + "---> " + strg)
    else:
        print("\"" + _string + "\"" + "---> " + "\"\"")

##################################################################################
#  _____      _      ____    _____     __  __   _____   _____   _   _    ___    ____  
# |  ___|    / \    / ___|  |_   _|   |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \ 
# | |_      / _ \   \___ \    | |     | |\/| | |  _|     | |   | |_| | | | | | | | | |
# |  _|    / ___ \   ___) |   | |     | |  | | | |___    | |   |  _  | | |_| | | |_| |
# |_|     /_/   \_\ |____/    |_|     |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/ 

import collections                                                                              
def checkEven(_counter):
    for i in _counter:
        if(_counter[i] % 2 == 1):
            return False
    return True

def checkOdd(_counter):
    limit = 0
    for i in _counter:
        if(_counter[i] % 2 == 1):
            if(limit > 1):
                return False
            else:
                limit += 1
    return True

def printPalindrome(_counter):
    s = ""
    for i in _counter:
        if(_counter[i] % 2 == 0):
            s+= i*int(_counter[i]/2)
    temps = list(s)
    temps.reverse()
    s_rev = "".join(temps)
    for i in _counter:
        if(_counter[i] % 2 == 1):
            s+= i*_counter[i]
    return s + s_rev

def checkAnagramFast(_string):
    c = collections.Counter(list(_string))
    hasPalindrome = False
    if (len(_string)%2 == 1):
        hasPalindrome = checkOdd(c)
    elif(len(_string)%2 == 0):
        hasPalindrome = checkEven(c)
    if(hasPalindrome):
        print("\"" + _string + "\"" + "---> " + printPalindrome(c))
    else:
        print("\"" + _string + "\"" + "---> " + "\"\"")
################################################################################




# test cases
#checkAnagramSlow("a") # should be true
#checkAnagramSlow("ab") # should be false
#checkAnagramSlow("asdfasdf")
#checkAnagramSlow("asdfasdfdfd") # should be true
#checkAnagramSlow("asdfghjkll")
#checkAnagramSlow("weatinattewsanitaryrs")


checkAnagramFast("asdfasdf")
checkAnagramFast("a") # should be true
checkAnagramFast("ab") # should be false
checkAnagramFast("asdfasdf")
checkAnagramFast("asdfasdfdfd") # should be true
checkAnagramFast("asdfghjkll")
checkAnagramFast("weatinattewsanitaryrs")
