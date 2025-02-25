import re

def valid_json(input_string):
    
    pattern =r'(\{|\}|\[|\]|\(|\)|:|,|True|False|null|\d+|"(?:\\.|[^"\\])*")'
    parts = re.findall(pattern , input_string)
    stack = []
    previous_token = None

    for token in parts:
        if token in '{[(':
            stack.append(token)
        elif token in '}])':
            if not stack:
                print("Inalid JSON : Unmatch closing braces and bracket or parenthesis.")
                return false
            top = stack.pop()
            if( (top == '{' and token != '}') or (top == '[' and token != ']') or (top == '(' and token != ')' ) ):
                print("Inalid JSON : Unmatch closing braces and bracket or parenthesis.")
                return False
        elif (token in ':'):
            if(not previous_token or not re.match(r'^".*"$', previous_token)):
                print("Invalid JSON: Colon must follow a string key.")
                return False
        elif(token == ','):
            if(not previous_token or  previous_token in '{[(:,'):
                print("Invalid JSON: Comma is misplaced.")
                return False
        else:
            if( previous_token in ')]}'):
                print("Invalid JSON: Value must be followed by a comma or closing brace/bracket.")
                return False

        previous_token = token 

    if(stack):
        print("Invalid JSON: Unmatched opening brace or bracket.")
        return False
    print("Valid Json")
    return True

def driver_code():
    userInput = input("Please provide your choice\n1)Create a JSON in terminal\n2)Provide name of JSON file\n:")
    
    if( userInput == '1'):
        input_string = input("Insert your data into JSON formate :\n")
        decision = valid_json(input_string)
        return decision

    elif(userInput == '2'):
        json_name = input("Enter the path of json file :\n")

        try:
            with open(json_name) as file:
                input_string = file.read()
        except FileNotFoundError:
            print("File Not Found!!")
        
        decision = valid_json(input_string)
        return decision

    else:
        print("Invalid choice : The choice must be 1 or 2 .")    
if __name__ == '__main__':
    decision = driver_code()
    if not decision :
        exit(1)
    else :
        exit(0)    