#factorization
def fermatfactorization(N):
   
    a = ceil(sqrt(N))
   
    while not is_square(a^2 - N):
        a = a + 2
       
    b = sqrt(a^2 - N)
   
    return [a-b, a+b]
m = "이현호"
m1= int.from_bytes(m.encode('utf-8'), "big")

e = 65537
n = 179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430652885096550381956977355009744407642308411545070379136134645709973060633048727107215362312651042098054062317216389604359801702614666769905641776363676873830995947


p = fermatfactorization(n)[0]
q = fermatfactorization(n)[1]
#오일러 파이함수
phi = (p-1)*(q-1)
#개인키 생성
d = (e.xgcd(phi)[1])%phi

#전자서명
s = pow(m1,d,n)

#서명 검증
mprime = pow(s,e,n)
j = bytes.fromhex(hex(mprime)[2:]).decode('utf-8')
print(mprime == m1)
print("복호문 = ",j)
"""
Bob의 RSA 공개키 (e,n)은 다음과 같은 성분을 가진다.
e=65537
n=179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430652885096550381956977355009744407642308411545070379136134645709973060633048727107215362312651042098054062317216389604359801702614666769905641776363676873830995947

위 정보만을 이용하여 Bob의 공개키로 검증에 성공하도록 자신의 이름에 대한 서명 s를 생성하라.
즉, Sagecell (https://sagecell.sagemath.org/)을 이용하여 검증 시 자신의 이름이 나와야 한다
Tip. n에 사용된 두 소수는 p = q + ε 만큼 차이가 난다는 취약점이 있다 이를 이용하여 n을 인수분해한다 -> 즉 n 은 p^2 과 거의 유사한 값을 가질 것 이다 
"""
