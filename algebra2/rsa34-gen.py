cipher = """03f824fd:033c7a71:050a6706:050a6706:03ffab5e:03f824fd:0189a78d:
            005bca7d:00734305:04046ca6:017698b6:005bca7d:03f824fd:03d10ac0:
            003622e4:011c1c7e:030cf03c:011c1c7e:03d10ac0:01b60e5d:03f824fd:
            00734305:007a18e6:03ffab5e:00734305:0179f797:037906bb:050a6706:
            007a18e6:015d897d:03f824fd:037906bb:03f824fd:0451f198:059ff1e0:
            03d10ac0:02e6b154:037906bb:03f824fd:00734305:003622e4:011c1c7e:
            0414fa45:03f824fd:00a6891a:042edbee"""

N = 101080891
p = 2062465
q = 101080891


e = 49
msg = " Deep Though znalazł odpowiedź i brzmi ona: 42"
new_cipher = []

for c in msg:
    char_val = pow(ord(c), e, N)
    new_cipher.append(hex(char_val)[2:].zfill(8))

old_format = cipher.replace(' ','').replace('\n','')
new_format = ':'.join(new_cipher)

assert old_format == new_format
