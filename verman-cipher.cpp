#include<iostream>
using namespace std;
char arr[26][26];
char message[22],key[22],emessage[22],retMessage[22];
int findRow(char);
int findColumn(char);
int findDecRow(char,int);
int main() {
	int i=0,j,k,r,c;
	k=96;
	for (i=0;i<26;i++) {
		k++;
		for (j=0;j<26;j++) {
			arr[i][j]=k++;
			if(k==123)
			    k=97;
		}
	}
	cout<<"\nEnter name:";
	cin>>message;
	cout<<"\nEnter the key (same length of name):";
	cin>>key;

	for (i=0;key[i]!=0;i++) {
		c=findRow(key[i]);
		r=findColumn(message[i]);
		emessage[i]=arr[r][c];
	}
	emessage[i]='\0';
	cout<<"\nCipher Text:"<<emessage;
	for (i=0;emessage[i]!=0;i++)
	cout<< emessage[i];

	for (i=0;key[i]!=0;i++) {
		c=findColumn(key[i]);
		r=findDecRow(emessage[i],c);
		retMessage[i]=arr[r][0];
	}
	retMessage[i]='\0';
	cout<<"\nDecrypted text is:";
	for (i=0;retMessage[i]!=0;i++)
	  cout<<retMessage[i];

	return(0);
}

int findRow(char c) {
	int i;
	for (i=0;i<26;i++) {
		if(arr[0][i]==c)
		   return(i);
	}
}
int findColumn(char c) {
	int i;
	for (i=0;i<26;i++) {
		if(arr[i][0]==c)
		   return(i);
	}
}
int findDecRow(char c,int j) {
	int i;
	for (i=0;i<26;i++) {
		if(arr[i][j]==c)
		   return(i);
	}
}
