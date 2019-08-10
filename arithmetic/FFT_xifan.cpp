#include<bits/stdc++.h>

using namespace std;


typedef long long ll;
typedef pair<int,int> pi; 
typedef double db; 


typedef complex<db> cd;

const db PI=acos(-1);
const int Maxn=1e5+5;


// class that performs fast Fourier transform
class FFT
{
public:	
	// helper function that inverse the bit position of a k-bit numer
    static int reverse(int num,int k)
    {
    	int res=0;
    	for(int i=0;i<k;i++)
    	{
    		if((num>>i)&1)
    		{
    			res|=(1<<(k-i-1));
			}
		}
		return res;
	}

	// helper function that performs DFT or iDFT depending on the 
	// boolean flag 'invert'
	// input: complex array 'a', array length n, flag invert
	// output: inplace
    static void transform(cd *a,const int n,bool invert) 
	{
        int k=0;
        while((1<<k)<n) k++;
        for(int i=0;i<n;i++)
        {
        	int x=reverse(i,k);
        	if(i<x)
        	{
        		swap(a[i],a[x]);
			}
		}
		for(int len=2;len<=n;len=(len<<1))
		{
			db ang=2.0*PI/len*(invert?-1:1);
			cd wlen=cd(cos(ang),sin(ang));
			for(int i=0;i<n;i+=len)
			{
				cd w=cd(1);
				for(int j=0;j<len/2;j++)
				{
					cd u=a[i+j],v=a[i+j+len/2]*w;
					a[i+j]=u+v;
					a[i+j+len/2]=u-v;
					w*=wlen;
				}
			}
		}
		if(invert)
		{
			for(int i=0;i<n;i++)
			{
				a[i]/=n;
			}
		}
    }

	// discrete Fourier transform
    static void dft(cd *a,const int n) 
	{
        transform(a,n,false);
    }

	// inverse discrete Fourier transform
    static void idft(cd *a,const int n) {
        transform(a,n,true);
    }
    
    // multiply two integer arrays using FFT
    // input: integer arrays 'a', 'b' with length na, nb
    // 		  array 'c' to store result in
    // output: stored in array 'c'
    static void multiply(int *a,int na,int *b,int nb,int *c) 
	{	    
	    int n=1;
	    while(n<na+nb) n=(n<<1);
	    
	    cd *ta = new cd[n];
	    cd *tb = new cd[n];
	    
	    for(int i=0;i<na;i++) ta[i]=a[i];
	    for(int i=0;i<nb;i++) tb[i]=b[i];
	    
	    for(int i=na;i<n;i++) ta[i]=0;
	    for(int i=nb;i<n;i++) tb[i]=0;
	    
	    dft(ta,n);
	    dft(tb,n);
	    
	    for(int i=0;i<n;i++) ta[i]*=tb[i];
	    idft(ta,n);
	    
		for(int i=0;i<n;i++) c[i]=round(ta[i].real());
		
		delete[] ta;
		delete[] tb;
	}
    
}fft;

int main()
{
	return 0;
}
