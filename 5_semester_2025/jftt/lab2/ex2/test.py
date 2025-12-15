# BAD hello this is a comment
#BAD pep comment, but still a comment
print("# OK this is not a comment")
print('# OK this is also not a comment')
### BAD triple comment start
###BAD triple comment start
print("""# OK try triple brackets""")
print('''# OK and again''')
#BAD pep comment, but still a comment
print("""
    # how about multiline strings  
    # OK
    # this should be printed as is
      """)
#BAD pep comment, but still a comment
print('''"# OK this should print"''')
print('''"""# OK this should print"""''')
print('''""# OK this should print''')
"""# OK this should print "" # OK print """
"""
"
# OK this should print
"""
### BAD hasn't left the environment
# dont kill the docstring
def func():
    """
    the very real part of a program
    """

print(func.__doc__)