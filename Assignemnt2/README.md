PA2 : Lottery Scheduler 및 2-Level Lottery Scheduler

XV6의 Round-Robin Scheduler를 참고 및 변형해 Lottery Scheduler를 구현했다. 이를 위해 추가로 필요한 tickets, uid 등의 프로세스 데이터를 추가하고, getreadcount(), settickets(), getpinfo(), fork() 등의 시스템콜을 추가/수정하고 scheduler 알고리즘을 변경했다.

Lottery Scheduler : 프로세스마다 티켓을 뽑아, 당첨자를 선정해 스케줄링하는 확률 기반 스케줄링이다. 따라서, 각 프로세스에게 특정한 티켓 갯수를 부여했을 때 스케줄링 횟수가 충분하다면 프로세스마다 의도한 비율대로 스케줄링할 수 있으며 확률 기반이기에 Starvation이 없다.

2-Level Scheduler : UID를 추가로 프로세스에 부여해 그룹을 만들고, 2번 당첨자를 뽑는다. 우선, 그룹 당첨자를 뽑고 다음으로 그 그룹 내에서의 당첨자를 뽑는다. 따라서, 그룹 단위로의 실행 비율까지도 보장할 수 있다


[1] Phase 1

  getreadcount() : 커널 부팅 이후 read() 시스템 콜이 호출된 총 횟수를 반환한다.


[2] Phase 2

  int settickets(int number) : 프로세스의 Lottery Scheduler를 위한 티켓 수를 설정한다.
  
  int getpinfo(struct pstat*) : 실행 중인 프로세스의 상태 정보를 기존의 것과 더불어 tickets, tick을 포함해 업데이트한다.
  
  int fork() : 자식 프로세스가 부모의 티켓 수를 상속받게 한다.
  
  scheduler() : 스케줄링 알고리즘을 Lottery Scheduler 알고리즘으로 변경한다. 난수 함수 srand를 사용한다.


[3] Phase 3 (*앞선 Phase들의 시스템 콜 사용/수정)

 int setuid(int uid) : 호출한 프로세스의 UID를 설정한다.
 
 int fork() : 자식이 부모의 티켓수와 UID를 상속받게 한다.
 
 int getpinfo(struct pstat*) : pstat 구조체에 기존의 것과 더불어 UID, tickets, tick을 포함해 업데이트한다.
 
 scheduler() : 2-Level Lottery Scheduler 알고리즘으로 변경한다. 프로세스의 그룹까지 포함해 티켓을 선정한다.
