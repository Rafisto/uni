n = 5
s1 = "hello"
s2 = "hello # not a comment"
s3 = 'hi # not a comment'
s4 = """text # not a comment
# also not a comment
"""
s5 = '''text # not a comment
# also not a comment
'''
s6 = "hello"
s7 = "hello \" # not a comment"
s8 = 'hi \' # not a comment'
s9 = "\\"
s10 = "\\\" # this isn't"
s11 = "\\\\"
s12 = "\\\\\" # odd number means it won't"
s13 = '\\\' # not a comment'
s14 = '\\'
s15 = """ \""" a
" ""
\""" # not a comment
""\\\""" "" # weird things happens with multiline strings"""
s16 = ''' \''' text
\''' # not a comment
''\\\''' '' # also not a comment'''
s17 = "'text' # not a comment"
s18 = '"text" # not a comment'
s19 = ""
s20 = ''
s21 = """" # so yeah, it's NOT a comment """
s22 = '''' # neither is this one '''
s23 = "" ""
