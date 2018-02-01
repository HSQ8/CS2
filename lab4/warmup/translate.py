#     test cases
#     f(123)  -> True
#     f(321)  -> True
#     f(1000) -> False
#     f(100)  -> False
#     f(10)   -> True
#     f(1010) -> True
#     f(3010) -> False


# this algorithm works by checking whether the base case, the ends of the string, are in a format of one or two digit
# number, if it is one of the translatable number that matches to a letter, it returns true, otherwise it returns false
# if the string is bigger than 2, then it recursively checks whether the first 1 or first 2 numbers correspond to a letter
# mapping and if it does, then check the substring with those letters truncated as they have already been accepted. If we 
# reach the end and find that out of all the recursive execution paths, one path , in some combination of one or two digit
# numbers match completely to an alphabet, then we accept the string and call return True.
# #########################################################################################################################
# structure of the program:
# first it constructs a list of numbers to look for,
# then it checks for base case and either accepts or rejects,
# then it splits the string into different parse paths by assuming that one case
# the leading 1st number maps to a digit and in the second case the leading two numbers map
# to a letter
# 
# then it recursively checks the rest of the string with leading numbers removed
# 
# time complexity: on average, each function calls itself twice, and the parse path has a depths of n corresponding 
# to the length of the input, so time complexity is 
# 2^n
# 
# space complexity, not sure,if I were to guess, I would guess that each level makes a copy of the string by splicing,
# which doubles the copies of strings available in memory
# where each level adds 2^n strings. so the space complexity is 2^n (constants dropped)
# 


def Check(s, translatable):
    result = False
    resulttwo = False;
    resultone = False;
    if(len(s) == 0):
        return False
    if(len(s) == 1):
        if s in translatable:
            return True
    if(len(s) == 2):
        if s in translatable:
            return True
    if(s[:2] in translatable):
        resulttwo = Check(s[2:],translatable)
    if(s[:1] in translatable):
        resultone = Check(s[1:],translatable)
    result = resultone or resulttwo
    return result

def CheckMapping(s):
    translatable = list()
    for i in range(1,27):
        translatable.append(str(i))
    return Check(s,translatable)

# formal test-cases
print(CheckMapping("123"))
print(CheckMapping("321"))
print(CheckMapping("1000"))
print(CheckMapping("100"))
print(CheckMapping("10"))
print(CheckMapping("1010"))
print(CheckMapping("3010"))

# custom test-cases

print(CheckMapping("82621231")) # true
print(CheckMapping("111111111")) # true
print(CheckMapping("12356896693")) # true
print(CheckMapping("12356890006693")) # false
print(CheckMapping("1233006856661293")) # false
print(CheckMapping("01")) # false
print(CheckMapping("1010101010101")) # true
