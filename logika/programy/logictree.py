# convert -> pAND(qOR(NOTpIFFr)) 
# tutorial -> https://www.geeksforgeeks.org/convert-infix-expression-to-postfix-expression

class Logic:
    operators = ["OR", "AND", "NOT", "IFF", "IF"]
    parenthesis = ["\(", "\)"]

    @staticmethod
    def InfixToPostfix(sentence: str):
        expression = ""
        while len(sentence) != 0:
            if any(sentence.startswith(i) for i in Logic.operators):
                ...
            else:
                expression += sentence[0]
                
