# the test cases given to me on the webpage that I use to simplify testing and debugging
test1 = [['E', 'E', 'E', 'E', 'E'], ['E', 'E', 'M', 'E', 'E'], ['E', 'E', 'E', 'E', 'E'], ['E', 'E', 'E', 'E', 'E']]
test1loc = [3,0]
test1result = [['B', '1', 'E', '1', 'B'], ['B', '1', 'M', '1', 'B'], ['B', '1', '1', '1', 'B'], ['B', 'B', 'B', 'B', 'B']]
test2 = [['B', '1', 'E', '1', 'B'], ['B', '1', 'M', '1', 'B'], ['B', '1', '1', '1', 'B'], ['B', 'B', 'B', 'B', 'B']]
test2loc = [1,2]
test2result = [['B', '1', 'E', '1', 'B'], ['B', '1', 'X', '1', 'B'], ['B', '1', '1', '1', 'B'], ['B', 'B', 'B', 'B', 'B']]

# simple function that counts the number of neighboring mines in relation to one cell
def NeighborMineCount(board,x,y):
    count = 0
    if(board[x+1][y+1] == 'M'):
        count += 1
    if(board[x+1][y-1] == 'M'):
        count += 1
    if(board[x+1][y] == 'M'):
        count += 1
    if(board[x-1][y+1] == 'M'):
        count += 1
    if(board[x-1][y-1] == 'M'):
        count += 1
    if(board[x-1][y] == 'M'):
        count += 1
    if(board[x][y-1] == 'M'):
        count += 1
    if(board[x][y+1] == 'M'):
        count += 1
    return count

# reveal
#recursive function that reveals the cell and then reveals
#neighboring cells if there is no
#mine in the current cell and no mine in the nearby cells
#if there are nearby mines, then place the the number 
#of nearby mines into the current cell
def reveal(board, x,y):
    if(board[x][y] == 'E'):
        minecount = NeighborMineCount(board,x,y)
        if(0 == minecount):
            board[x][y] = 'B'
            reveal(board,x+1,y + 1)
            reveal(board,x+1,y)
            reveal(board,x+1,y - 1)
            reveal(board,x-1,y + 1)
            reveal(board,x-1,y)
            reveal(board,x-1,y - 1)
            reveal(board,x,y + 1)
            reveal(board,x,y - 1)
        elif (minecount > 0):
            board[x][y] = str(minecount)

# for debugging
# this prints out a board
def printboard(board):
    for i in board:
        print(i)

#this function outlines the principle that I use to adjust the 
#board for easy processing
#it adds a padding layer of a meaningleses values around the board so that
#when i compute the neighboring cells, I don't have to account for every edge case
#in this instance, the padding value is 'K'
def getDummyBoard(board):
    newboard = [['K' for y in range(len(board[0]) + 2)] for x in range(len(board) + 2)]
    for i in range(len(board)):
        for j in range(len(board[0])):
            newboard[1 + i][1 + j] = board[i][j]
    return newboard

#this function is the finailizing function that comverts a padded board back 
#into the original board dimension, stripping the padded characters
#and only returning the actual board itself
def getRealBoardfromDummy(board):
    newboard = []
    for i in range(1,len(board) - 1):
        newboard.append(board[i][1:-1])
    return newboard

# this is the main function of the program, it
# first checks for whether the current click location is a 
# mine, if it is, then it replaces the current location with a 
# 'X' and returns the board
# if not, then it adjusts the boarder of the board
# by applying a layer of padding and 
# then recursively revealing the rest of the board until
# the conditions underwhich we can reveal a location have been
# exhausted
def adjustboard(board, clicklocation):
    x = clicklocation[0]
    y = clicklocation[1]
    if board[x][y] == 'M':
        board[x][y] = 'X'
        return board

    newboard = getDummyBoard(board)
    reveal(newboard, x + 1, y + 1)
    finalboard = getRealBoardfromDummy(newboard)
    return finalboard

print("if there's no output, then the assertion was a success and the \n test cases passed")
assert test1result == adjustboard(test1,test1loc)
assert test2result == adjustboard(test2,test2loc)
