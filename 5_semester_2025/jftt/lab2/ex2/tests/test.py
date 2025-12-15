n = 5 # this is a comment
s1 = "hello" # comment
s2 = "hello # not a comment"
s3 = 'hi # not a comment'
s4 = """text # not a comment
# also not a comment
""" # comment
s5 = '''text # not a comment
# also not a comment
''' # a comment
s6 = "hello" # this is a comment " <- shouldn't be part of string
s7 = "hello \" # not a comment"
s8 = 'hi \' # not a comment'
s9 = "\\" # this is a comment
s10 = "\\\" # this isn't"
s11 = "\\\\" # even number of backslashes before closing " mean it's gonna end the string
s12 = "\\\\\" # odd number means it won't"
s13 = '\\\' # not a comment'
s14 = '\\' # comment
s15 = """ \""" a
" ""
\""" # not a comment
""\\\""" "" # weird things happens with multiline strings"""
s16 = ''' \''' text
\''' # not a comment
''\\\''' '' # also not a comment''' # while this is ''' a comment
s17 = "'text' # not a comment" # a comment
s18 = '"text" # not a comment' # a comment
s19 = "" # a comment
s20 = '' # a comment
s21 = """" # so yeah, it's NOT a comment """ # this one is
s22 = '''' # neither is this one ''' # this one also it
s23 = "" "" # this IS a comment """
