#include"kernel/types.h"
#include"user/user.h"

void printPrimes(int *input,int num){
    if(!num)return ;
    int fd[2],prime=*input;
    pipe(fd);
    char buf[4];
    printf("prime %d\n",prime);
    //�ӽ���ÿ�ν������е�������ܵ�
    if(fork()==0){
        close(fd[0]);
        for(int i=0;i<num;i++){
            write(fd[1],(char *)(input+i),4);
        } 
        close(fd[1]);
        exit(0);
    }
    //ɸѡ����ÿ�ΰ�prime��������ɸѡ������ͬ��input�����С��
    //������printPrimes�����ӽ��̷���
    else{
        close(fd[1]);
        int count=0;
        while(read(fd[0],buf,4)!=0){
            int temp=*((int *)buf);
            if(temp%prime){
                *input++=temp;
                count++;
            }
        }
      close(fd[0]);
        printPrimes(input-count,count);
        wait(0);
    }
   
}

int main(int argc,char *argv[]){
    int input[34];
    for(int i=0;i<34;i++)
        input[i]=i+2;
    printPrimes(input,34);
    exit(0);
}
