# BoB 11기

## openssl 라이브러리 사용법 (ubuntu)   
```
$ sudo apt-get install libssl-dev
```
윈도우에서는 openssl 사용하는 방법이 까다로우니 구글링 또는 openssl github 홈페이지에서 다운로드 가이드 통해 설치하여 사용한다.   
이 모든게 귀찮다면 - https://slproweb.com/products/Win32OpenSSL.html  
컴파일시 gcc 옵션 -lcrypto (libcrypto 라이브러리를 연결시켜야함)   

### sagemath 사용법 - python 기반의 오픈소스
Tip. sage는 새로운 프로그래밍 언어가 아니라 python 문법에 수학적으로 다룰 수 있는 함수 및 기능이 추가된 것이라고 보면 된다.   

1. 사이트에서 돌려보기 - https://sagecell.sagemath.org/
2. sagemath 설치 - https://doc.sagemath.org/html/en/installation/index.html

## In ubuntu linux   
 ```bash
$ sudo apt install python3
$ sudo apt install sagemath
```  
 실행시 `$ sage <filename>.sage` 해주면 알아서 python파일로도 변환시켜줌. `<filename>` 대신 실행할 파이썬 파일 이름을 넣어야함!
 
In windows (without wsl)   
 https://www.sagemath.org/download-source.html -> Download Windows binaries ->    
 https://github.com/sagemath/sage-windows/releases -> SageMath-9.3-Installer-v0.6.3.exe -> Download!   
 
 사용법은 linux와 비슷하다. windows는 설치된 sage 프로그램을 클릭하면 terminal이 실행 됨.   
 
### ARIA test vector

한국인터넷진흥원(KISA) ARIA.zip 참고   
https://seed.kisa.or.kr/kisa/Board/19/detailView.do   
https://www.rfc-editor.org/rfc/rfc8269.html   
