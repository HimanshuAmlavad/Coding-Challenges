def countLine(paragraph):
    return paragraph.count('\n') + 1

def countWord(paragraph):
    return len(paragraph.split())

def countChar(paragraph):
    return len(paragraph)


def driver():
    
    inputChoice = int(input("Enter choice:\n1)Direct input\n2)File \n:"))
    
    if (inputChoice == 1):
        paragraph = input("Please provide the paragraph:\n")

        countChoice = input("For Line(-l), For word(-w), For Character(-c), For All(*)\n:").lower()
        taskCh = countChoice.replace(" ", "").split('-')
        

        if ('*' in taskCh):
            noOfline = countLine(paragraph)
            noOfword = countWord(paragraph)
            noOfchar = countChar(paragraph)
            print(f''' Number of lines: {noOfline} \n Number of words: {noOfword} \n Number of characters: {noOfchar}''')
        elif ('l' in taskCh) or ('w' in taskCh) or ('c' in taskCh):
            if ('l' in taskCh):
                noOfline = countLine(paragraph)
                print(f'Number of lines: {noOfline}')
            
            if('w' in taskCh):
                noOfword = countWord(paragraph)
                print(f'Number of word: {noOfword}')

            if('c' in taskCh):
                noOfchar = countChar(paragraph)
                print(f'Number of character: {noOfchar}')
        else:
            print("Wrong command!!")

    elif(inputChoice == 2):
        fileName = input("provide file path : ")
        countChoice = input("For Line(-l), For word(-w), For Character(-c), For All(*)\n:").lower()
        taskCh = countChoice.replace(" ", "").split('-')
        print(taskCh)

        try:
            with open(fileName) as file:
                paragraph = file.read()
        except FileNotFoundError:
            print("File Not Found!!")

        if ('*' in taskCh):
            noOfline = countLine(paragraph)
            noOfword = countWord(paragraph)
            noOfchar = countChar(paragraph)
            print(f''' Number of lines: {noOfline} \n Number of words: {noOfword} \n Number of characters: {noOfchar}''')

        elif ('l' in taskCh) or ('w' in taskCh) or ('c' in taskCh):
            if ('l' in taskCh):
                noOfline = countLine(paragraph)
                print(f'Number of lines: {noOfline}')
            
            if('w' in taskCh):
                noOfword = countWord(paragraph)
                print(f'Number of word: {noOfword}')

            if('c' in taskCh):
                noOfchar = countChar(paragraph)
                print(f'Number of character: {noOfchar}')
        else:
            print("Wrong command!!")       

    else:
        print("Invalid Choice!!!\nThe choice must be an 'integer' or  the Number '1 or 2'")

if __name__ == "__main__":
    driver()