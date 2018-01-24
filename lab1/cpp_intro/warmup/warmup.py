# personally I would use a hashmap, but since the problem 
# asked for it to return an array
# here is the array version
# for instance, this program will  take [11223], and return 
# [22221], since each position which the frequency value occupies will 
# reflect the frequency of the letter at that position in the original array
def CharFrequency(_ar):
    charlist = list(_ar)
    numlist = charlist[:]
    for i in range(len(charlist)):
        count = 0
        for j in range(len(charlist)):
            if charlist[i] == charlist[j]:
                count += 1
        numlist[i] = count
    return numlist

# the time complexity is (O)n^2
# the space complexity is (O)n

# but I really dislike that implementation, so here's what I would do

def charFrequencyBetter(_ar):
    dic = dict()
    for i in _ar:
        if i in dic:
            dic[i] += 1
        else:
            dic[i] = 1
    return dic

    # time complexity is O(n)
    # space complexity is O(n) .. i think.
