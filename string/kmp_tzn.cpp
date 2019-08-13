#include<bits/stdc++.h>
using namespace std;

vector<int> kmp(string s,string t)
{
/*	s - pattern, t - text
	s = "abab", t = "ababab", RETURN: {0,2} */
	int n=s.length();
	vector<int> nxt(n+1,0);
	for(int i=1;i<n;i++)
	{
		int j=i;
		while (j)
		{
			j=nxt[j];
			if (s[i]==s[j])
			{
				nxt[i+1]=j+1;
				break;
			}
		}
	}
	vector<int> pos;
	int m=t.length();
	for(int i=0,j=0;i<m;i++)
	{
		if (j<n && t[i]==s[j]) j++;
		else
		{
			while (j)
			{
				j=nxt[j];
				if (t[i]==s[j])
				{
					j++;
					break;
				}
			}
		}
		if (j==n) pos.push_back(i-n+1);
	}
	return pos;
}

