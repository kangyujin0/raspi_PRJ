pthread 라이브러리를 활용 멀티스레딩 구현
두 스레드를 사용 각 범위 내에서 
숫자를 더한 후 전역 변수 sum에 결과를 누적하는 예제

/*pthread3.c*/
#include <stdio.h>
#include <pthread.h>

int sum = 0;
void* thread_summation(void*);
int main()
{
        pthread_t t_id1, t_id2;
        int range1[] = {1, 5};
        int range2[] = {6, 10};

        pthread_create(&t_id1, NULL, thread_summation, (void*)range1);
        pthread_create(&t_id2, NULL, thread_summation, (void*)range2);

        pthread_join(t_id1, NULL);
        pthread_join(t_id2, NULL);
        printf("result: %d\n", sum);

        return 0;
        
}
void* thread_summation(void* arg)
{
        int start = ((int*)arg)[0];
        int end = ((int*)arg)[1];
        while(start <= end){
                sum += start;
                start++;
        }
        return NULL;
}

구현
main 함수는 두 개의 스레드를 생성
각 스레드가 thread_summation 함수를 실행
두 스레드의 실행이 끝날 때까지 기다린 후
sum의 최종 값을 출력

결과
첫 번째 스레드는 range1 배열 범위 1부터 5까지 숫자를 더하고
두 번째 스레드는 range2 배열 범위 6부터 10까지 숫자를 더한다
1부터 5까지의 합은 1 + 2 + 3 + 4 + 5 = 15이고
6부터 10까지의 합은 6 + 7 + 8 + 9 + 10 = 40입니다.
두 스레드 각 범위 내의 숫자를 더한 후
sum 변수에 15 + 40 = 55의 값이 누적되어 최종적으로 출력

100개의 스레드를 생성
각 스레드에서 동일한 전역 변수 num을 50000번씩 증가 또는 감소시키는 예제

/*pthread4.c*/
#include <stdio.h>
#include <pthread.h>

#define THREADS 100

void* thread_inc(void*);
void* thread_des(void*);
long long num = 0;
int main()
{
        pthread_t thread_id[THREADS];
        int i;

        printf("sizeof long long: %d\n", sizeof(long long));

        for(i = 0; i < THREADS; i++){
                if(i % 2)
                        pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
                else
                        pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
        }
        for(i = 0; i < THREADS; i++){
                pthread_join(thread_id[i], NULL);
        }
        printf("result: %lld\n", num);

        return 0;
}
void* thread_inc(void* arg)
{
        int i;
        for(i = 0; i < 50000; i++){
                num += 1;
        }
        return NULL;
}
void* thread_des(void* arg)
{
        int i;
        for(i = 0; i < 50000; i++){
                num -= 1;
        }
        return NULL;
}

구현
여러 스레드가 동시에 num 변수를 증가 및 감소시키기 때문에 
스레드 간의 경쟁 조건(race condition)이 발생할 수 있습니다
따라서 결과는 예측하기 어려울 수 있으며
예상치 못한 값이 나올 수 있습니다
또한, num 변수에 대한 동시 접근은 동기화 메커니즘이 없으므로 스레드 안전성 문제가 있습니다

결과
경쟁 조건(Race Condition)
여러 스레드가 동시에 하나의 전역 변수인 num을 수정하는 상황에서 발생
스레드들이 num을 동시에 증가하거나 감소시키기 때문에
스레드 간의 실행 순서 및 동시성에 따라 num 값이 예상치 못한 방식으로 변경될 수 있습니다

동기화 부재
코드에서는 num 변수를 보호하거나 동기화하는 메커니즘이 없습니다
따라서 스레드들이 num에 동시에 접근하여 수정하면서 상호 간섭이 발생할 수 있습니다
이러한 상황에서 예상치 못한 결과가 나타날 수 있습니다

스레드 스케줄링
스레드 스케줄링은 운영체제의 스케줄러에 의해 관리됩니다
스레드들이 CPU 자원을 경쟁적으로 사용하며 실행되기 때문에
각 스레드가 CPU를 사용하는 순서와 시간에 따라 결과가 달라질 수 있습니다

컴파일러 최적화
컴파일러는 코드를 최적화하기 위해 여러 기술을 사용합니다
이러한 최적화는 변수 사용 및 메모리 접근 패턴을 변경할 수 있으므로
결과를 예측하기 어렵게 만들 수 있습니다
