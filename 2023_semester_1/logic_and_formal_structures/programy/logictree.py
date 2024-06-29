class Logic:
    def __init__(self, size):
        self.top = -1
        self.size = size

        self.stack = []
        self.output = []

        # polish notation one-letter standard, at: https://en.wikipedia.org/wiki/Polish_notation#Polish_notation_for_logic
        self.translation = {'/neg': 'N', '/and': 'K',
                            '/or': 'A', '/implies': 'C', '/iff': 'E'}
        self.precedence = {'N': 5, 'K': 4, 'A': 3, 'C': 2, 'E': 1}

    def latexToPolish(self, expression):
        for key, value in self.translation.items():
            expression = expression.replace(key, value)
        return expression

    def polishTolatex(self, expression):
        for key, value in self.translation.items():
            expression = expression.replace(value, key)
        return expression.replace('/',' ')

    def isStackEmpty(self):
        return True if self.top == -1 else False

    def topStackItem(self):
        return self.stack[-1]

    def popStackItem(self):
        if not self.isStackEmpty():
            self.top -= 1
            return self.stack.pop()
        else:
            return "$"

    def pushToStack(self, op):
        self.top += 1
        self.stack.append(op)

    def isOperand(self, ch):
        return ch.islower()

    def notGreater(self, i):
        try:
            a = self.precedence[i]
            b = self.precedence[self.topStackItem()]
            return True if a <= b else False
        except KeyError:
            return False

    def InfixToPostfix(self, expression):
        for i in expression:
            if self.isOperand(i):
                self.output.append(i)

            elif i == '(':
                self.pushToStack(i)

            elif i == ')':
                while ((not self.isStackEmpty()) and
                       self.topStackItem() != '('):
                    a = self.popStackItem()
                    self.output.append(a)
                if (not self.isStackEmpty() and self.topStackItem() != '('):
                    return -1
                else:
                    self.popStackItem()

            else:
                while (not self.isStackEmpty() and self.notGreater(i)):
                    self.output.append(self.popStackItem())
                self.pushToStack(i)

        while not self.isStackEmpty():
            self.output.append(self.popStackItem())

        return ''.join(self.output)


testing_expressions = [
    "a/orb/and(c/ord)/ore)/and(f/impliesg)/orh)/andi",
    "(a/orb)",
    "p/and(q/or(/negp/iffr))"
]

if __name__ == '__main__':
    for i, expression in enumerate(testing_expressions):
        print(f"Element {i+1}:")
        logical_object = Logic(len(expression))
        polish_operators = logical_object.latexToPolish(expression)
        print(f"Polish operators: {polish_operators}")
        print(f"Reverse polish notation {(res:=logical_object.InfixToPostfix(polish_operators))}")
        print(f"Latex Equivalent: {logical_object.polishTolatex(res)}")