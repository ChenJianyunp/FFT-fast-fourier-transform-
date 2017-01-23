/*Name: Fast Fourier Transform
Compiler: Dev-C++ 5.8.0
Coded by: Jianyu Chen
Place: Middelburg, the Netherlands
Function: a program to caculate the FFT and inverse FFT
Time: 23th,Jan,2017 
*/
#include <iostream>  
#include <complex>
#define pi2 6.2831852                           /////PI times 2, you can use a more accurate number
#define NUM 8                                   /////length of the data, it must be 2^N, N=0,1,2,3...., if your data is not of this length, you can add some zeros
using namespace std;
void FFT(complex<double>*Data,int Log2N,int sign);
int main(void){
	complex<double> data[NUM]={0,4,2,6,1,5,3,7};
	//complex<double> data[8]={0,1,2,3,4,5,6,7};
	FFT(&data[0],3,1);
	cout<<"result of FFT"<<endl;
	for(int i=0;i<NUM;i++){
		cout<<data[i]<<" ";
	}
	FFT(&data[0],3,-1);
	cout<<endl<<"result of inverse FFT"<<endl;
	for(int i=0;i<NUM;i++){
		cout<<data[i]<<" ";
	}
	return 0;
}

//////// Data is the pointer to the data, Log2N=log2 NUM, 
////////NUM must be 2^N, N=0,1,2,3...., if your data is not of this length, you can add some zeros
////////sign should ONLY be 1 or -1. 1 means FFT, -1 means inverse FFT
void FFT(complex<double>*Data,int Log2N,int sign){
	complex<double> Wn,Wnk,temp;      ////Wn=e^(2*pi*i*n/N)   Wnk=e^(2*pi*i*k*n/N) 
	const int length=(1<<Log2N);      ////length of the data
	int part,step;
	complex<double> tempdata[length];
	
	/////rearrange the order of data
	for(int i=0;i<Log2N-1;i++){
		part=1<<i;
		step=1<<(Log2N-i-1);
		for(int j=0;j<part;j++){
		    for(int k=0;k<step;k++){
		    	tempdata[j*step*2+k]=Data[j*step*2+k*2];
		    	tempdata[j*step*2+k+step]=Data[j*step*2+k*2+1];
		    }	
		}
		for(int j=0;j<length;j++){
			Data[j]=tempdata[j];
		}
	}
	
	////fast fourier transform
	for(int i=1;i<=Log2N;i++){		
		part=1<<(Log2N-i);
		Wn=complex<double>(cos(pi2/(1<<i)),-sin(pi2/(1<<i)*sign));
		step=1<<(i-1);
		for(int j=0;j<part;j++){
		    Wnk=1;	
			for(int k=0;k<step;k++){
				temp=Data[j*step*2+k];
				Data[j*step*2+k]+=Data[j*step*2+step+k]*Wnk;
				Data[j*step*2+step+k]=temp-Data[j*step*2+step+k]*Wnk;
				Wnk*=Wn;
			}
		}
	}
	
	////check if it is inverse FFT
	if(sign==-1){
		for(int j=0;j<length;j++){
			Data[j]/=length;
		}
	}
}

