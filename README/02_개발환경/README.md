# 2. 개발 환경 구성

✅ **개발 환경**   
LINUX (`linuxmint-22.1-cinnamon-64bit`)   
-> Linux Debian 참고

✅ **아카이브 참고**: https://github.com/navilera/Navilos/commits/master

✅ **컴파일러 설치**  
-> ARM에서 동작하는 펌웨어를 만드는 것이 목표  
`$ sudo apt install gcc-arm-none-eabi`  
: ARM용 컴파일러 설치 (gcc 사용)    
: none (운영체제 없이 동작), eabi(Embedded Application Binary Interface) -> HW와 SW의 호환성 보장하는 규약 

-> `크로스 컴파일러` : 컴파일을 실행하는 환경과 컴파일의 결과물이 실행될 환경이 다른 경우에 사용하는 컴파일러  
`$ arm-none-eabi-gcc -v` : 위와 같은 컴파일러 버전 확인  

✅ **QEMU 설치**
* `QEMU`란?  
실제 보드 없이 가상으로 개발가능한 에뮬레이터  

`$sudo apt install qemu-system-arm`  
: qemu 에뮬레이터 설치

`$qemu-system-arm --version` : 버전확인  
`$qemu-system-arm -M ? `: qemu가 지원하는 머신 목록   
-> 프로젝트에서는 `realview-pb-a8` 사용  
-> ARM Cortex A8 프로세서용 HW 개발 보드!  
-> 32bit 프로세서 




