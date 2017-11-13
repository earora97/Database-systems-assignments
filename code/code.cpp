#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include<set>
#include<string>
#include<cstring>
#include<sys/stat.h>
#include<cmath>
#include<vector>
#include<cstring>
#include<stdlib.h>


using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
int m=0;


size_t getFilesize(const std::string& filename) {
	struct stat st;
	if(stat(filename.c_str(), &st) != 0) {
		return 0;
	}
	return st.st_size;   
}

void getnexth(string inp1,string inp2,fstream & op,int ind)
{
	map < string , vector < vector < string > > >  hashit;
	fstream pointer1,pointer2;
	pointer1.open(inp1,fstream::in);
	string line,token;
	int i,j;
	while(getline(pointer1,line))
	{
		vector < string > tempdata;
		stringstream linestream(line);
		while(linestream>>token) tempdata.push_back(token);
		if(ind==0)hashit[tempdata[tempdata.size()-1]].push_back(tempdata);
		else hashit[tempdata[0]].push_back(tempdata);
	}
	pointer1.close();
	remove(inp1.c_str());
	pointer2.open(inp2,fstream::in);
	while(getline(pointer2,line))
	{
		vector < string > tempdata;
		stringstream linestream(line);
		while(linestream>>token) tempdata.push_back(token);
		string s; 
		if(ind==0)
			s=tempdata[0];
		else
			s=tempdata[tempdata.size()-1];
		for(i=0;i<hashit[s].size();i++)
		{
			if(ind==0)
			{
				for(j=0;j<hashit[s][i].size();j++)
					op << hashit[s][i][j] << " ";
				for(j=1;j<tempdata.size()-1;j++)
					op<< tempdata[j]<<" ";
				op  << tempdata[j]<<endl;
			}
			else
			{
				for(j=0;j<tempdata.size();j++)
					op<< tempdata[j]<<" ";
				for(j=1;j<hashit[s][i].size()-1;j++)
					op << hashit[s][i][j] << " ";
				op  << hashit[s][i][j]<<endl;
			}
		}
	}
	pointer2.close();
	remove(inp2.c_str());
}


int hashfunc(string inp)
{
	int i;
	int val=0;
	for(i=0;i<inp.size();i++)
		val=(val+inp[i])%m;
	return val;
}


void closeh(ifstream & infile1,ifstream & infile2,fstream & opfile2)
{
	infile1.close();
	infile2.close();
	opfile2.close();
}


void openh(string inpfile1,string inpfile2,string opfile)
{
	fstream * pointers1[102];
	fstream * pointers2[102];
	string base1="1inpfile";
	string base2="2inpfile";
	stringstream linestream;
	fstream oppointer;
	oppointer.open(opfile,fstream::out);
	string line,token;
	int i,j;
	for(i=0;i<m;i++)
	{
		fstream file11,file22;
		string file1=base1+to_string(i);
		pointers1[i]=new fstream(file1,fstream::out);
		string file2=base2+to_string(i);
		pointers2[i]= new fstream(file2,fstream::out);
	}
	ifstream infile1(inpfile1);
	while(getline(infile1,line))
	{
		vector < string > tempdata;
		stringstream linestream(line);
		while(linestream>>token)
			tempdata.push_back(token);
		int val=hashfunc(tempdata[tempdata.size()-1]);
		string file=base1+to_string(val);
		for(i=0;i<tempdata.size()-1;i++)
			*(pointers1[val]) << tempdata[i]<< " ";
		*(pointers1[val]) << tempdata[i]<<endl;
	}
	ifstream infile2(inpfile2);
	while(getline(infile2,line))
	{
		vector < string > tempdata;
		stringstream linestream(line);
		while(linestream>>token)
			tempdata.push_back(token);
		int val=hashfunc(tempdata[0]);
		string file=base2+to_string(val);
		for(i=0;i<tempdata.size()-1;i++)
			*pointers2[val] << tempdata[i]<<" ";
		*pointers2[val] << tempdata[i]<<endl;
	}
	for(i=0;i<m;i++)
	{
		(*pointers1[i]).close();
		(*pointers2[i]).close();
	}
	for(i=0;i<m;i++)
	{
		string file1=base1+to_string(i);
		size_t s1=getFilesize(file1);
		string file2=base2+to_string(i);
		size_t s2=getFilesize(file2);
		if(s1<s2) getnexth(file1,file2,oppointer,0);
		else  getnexth(file2,file1,oppointer,1);
	}
	closeh(infile1,infile2,oppointer);
}


void markit(vector   < pair < int , vector < string > > >  & array,int mark[])
{
	int i;
	for(i=0;i<array.size();i++)
		mark[array[i].first]=1;
}


void getnexts(fstream & output)
{
	string base1="1inpfile";
	string base2="2inpfile";
	fstream * pointers1[102];
	fstream * pointers2[102];
	int i,j,k;
	for(i=0;i<m-1;i++)
	{
		string file1=base1+to_string(i);
		pointers1[i]=new fstream(file1,fstream::in);
		string file2=base2+to_string(i);
		pointers2[i]= new fstream(file2,fstream::in);
	}
	map < string , vector < pair < int ,vector < string > > > > hash1;
	map < string , vector <  pair < int , vector < string > > >  > hash2;
	string line,token;
	for(i=0;i<m-1;i++)
	{
		if(!getline(*pointers1[i],line)) continue;
		vector < string > tempdata;
		stringstream linestream(line);
		while(linestream>>token)
			tempdata.push_back(token);
		hash1[tempdata[tempdata.size()-1]].push_back(make_pair(i,tempdata));
	}
	for(i=0;i<m-1;i++)
	{
		if(!getline(*pointers2[i],line)) continue;
		vector < string > tempdata;
		stringstream linestream(line);
		while(linestream>>token)
			tempdata.push_back(token);
		hash2[tempdata[0]].push_back(make_pair(i,tempdata));
	}
	while(1)
	{
		int mark1[m-1];
		int mark2[m-1];
		memset(mark1,0,sizeof(mark1));
		memset(mark2,0,sizeof(mark2));
		if(hash1.size()==0 || hash2.size()==0) break;
		if((*hash1.begin()).first==(*hash2.begin()).first)
		{
			string s=(*hash1.begin()).first;
			for(i=0;i<m-1;i++)
			{
				while(getline(*pointers1[i],line))
				{
					vector < string > tempdata;
					stringstream linestream(line);
					while(linestream>>token)
						tempdata.push_back(token);
					hash1[tempdata[tempdata.size()-1]].push_back(make_pair(i,tempdata));
					if(tempdata[tempdata.size()-1]!=(*hash1.begin()).first) break;
				}
			}
			for(i=0;i<m-1;i++)
			{
				while(getline(*pointers2[i],line))
				{	
					vector < string > tempdata;
					stringstream linestream(line);
					while(linestream>>token)
						tempdata.push_back(token);
					hash2[tempdata[0]].push_back(make_pair(i,tempdata));
					if(tempdata[0]!=(*hash2.begin()).first) break;
				}
			}
			for(i=0;i<hash1[s].size();i++)
				for(j=0;j<hash2[s].size();j++)
				{
					for(k=0;k<(hash1[s][i].second).size();k++)
						output  << (hash1[s][i].second)[k] << " ";
					for(k=1;k<(hash2[s][j].second).size()-1;k++)
						output << (hash2[s][j].second)[k]<<" ";
					output<< (hash2[s][j].second)[k]<<endl;
				}
			markit(hash1[s],mark1);
			markit(hash2[s],mark2);
			hash1.erase(hash1.begin());
			hash2.erase(hash2.begin());
		}
		else if((*hash1.begin()).first>(*hash2.begin()).first)
		{ 
			while((*hash1.begin()).first>(*hash2.begin()).first)
			{
				markit(hash2[(*hash2.begin()).first],mark2);
				hash2.erase(hash2.begin());
			}
		}
		else
		{
			while((*hash1.begin()).first<(*hash2.begin()).first)
			{

				markit(hash1[(*hash1.begin()).first],mark1);
				hash1.erase(hash1.begin());
			}
		}
		for(i=0;i<m-1;i++)
		{
			if(!mark1[i]) continue;
			if ( !getline(*pointers1[i],line)) continue;
			vector < string > tempdata;
			stringstream linestream(line);
			while(linestream>>token)
				tempdata.push_back(token);
			hash1[tempdata[tempdata.size()-1]].push_back(make_pair(i,tempdata));
		}
		for(i=0;i<m-1;i++)
		{
			if(!mark2[i]) continue;
			if(!getline(*pointers2[i],line)) continue;
			vector < string > tempdata;
			stringstream linestream(line);
			while(linestream>>token)
				tempdata.push_back(token);
			hash2[tempdata[0]].push_back(make_pair(i,tempdata));
		}
	}
	for(i=0;i<m-1;i++)
	{
		(*pointers1[i]).close();
		(*pointers2[i]).close();
		remove((base1+to_string(i)).c_str());
		remove((base2+to_string(i)).c_str());
	}
}

void opens(string inpfile1,string inpfile2,string opfile)
{
	fstream * pointers1[102];
	fstream * pointers2[102];
	string base1="1inpfile";
	string base2="2inpfile";
	stringstream linestream;
	fstream oppointer;
	oppointer.open(opfile,fstream::out);
	string line,token;
	int i,j;
	for(i=0;i<m-1;i++)
	{
		string file1=base1+to_string(i);
		pointers1[i]=new fstream(file1,fstream::out);
		string file2=base2+to_string(i);
		pointers2[i]= new fstream(file2,fstream::out);
	}
	ifstream infile1(inpfile1);
	int no=0;
	int iteration=0;
	vector < vector < string > > present;
	int n=0;
	int tuplesa=0;
	int tuplesb=0;
	while(getline(infile1,line))
		tuplesa++;
	infile1.close();
	ifstream infile2(inpfile2);
	while(getline(infile2,line))
		tuplesb++;
	infile2.close();
	tuplesa=(tuplesa+m-2)/(m-1);
	tuplesb=(tuplesb+m-2)/(m-1);
	infile2.close();
	infile1.open(inpfile1);
	while(getline(infile1,line))
	{
		n++;
		no++;
		vector < string > tempdata;
		stringstream linestream(line);
		while(linestream>>token)
			tempdata.push_back(token);
		present.push_back(tempdata);
		//cout<<no<<endl;
		if(no==tuplesa)
		{
			vector < pair < string ,int > > sor;
			for(i=0;i<present.size();i++)
				sor.push_back(make_pair(present[i][present[i].size()-1],i));
			sort(sor.begin(),sor.end());
			vector < vector < string > > temp(sor.size());
			for(i=0;i<sor.size();i++) temp[i]=present[sor[i].second];
			for(i=0;i<sor.size();i++)
				present[i]=temp[i];
			for(i=0;i<present.size();i++)
			{
				for(j=0;j<present[i].size()-1;j++)
					*pointers1[iteration] << present[i][j] << " ";
				*pointers1[iteration] << present[i][j] << endl;	
			}
			iteration++;
			no=0;
			present.clear();
		}
	}
	if(no>0)
	{
		vector < pair < string ,int > > sor;
		for(i=0;i<present.size();i++)
			sor.push_back(make_pair(present[i][present[i].size()-1],i));
		sort(sor.begin(),sor.end());
		vector < vector < string  > > temp(sor.size());
		for(i=0;i<sor.size();i++) temp[i]=present[sor[i].second];
		for(i=0;i<sor.size();i++)
			present[i]=temp[i];
		for(i=0;i<present.size();i++)
		{
			for(j=0;j<present[i].size()-1;j++)
				*pointers1[iteration] << present[i][j] << " ";
			*pointers1[iteration] << present[i][j] << endl;	
		}
		iteration++;
		no=0;
		present.clear();
	}
	infile2.open(inpfile2);
	no=0;
	iteration=0;
	while(getline(infile2,line))
	{
		no++;
		vector < string > tempdata;
		stringstream linestream(line);
		while(linestream>>token)
			tempdata.push_back(token);
		present.push_back(tempdata);
		if(no==tuplesb)
		{
			vector < pair < string ,int > > sor;
			for(i=0;i<present.size();i++)
				sor.push_back(make_pair(present[i][0],i));
			sort(sor.begin(),sor.end());
			vector < vector < string > > temp(sor.size());
			for(i=0;i<sor.size();i++) temp[i]=present[sor[i].second];
			for(i=0;i<sor.size();i++)
				present[i]=temp[i];
			for(i=0;i<present.size();i++)
			{
				for(j=0;j<present[i].size()-1;j++)
					*pointers2[iteration] << present[i][j] << " ";
				*pointers2[iteration] << present[i][j] << endl;	
			}
			iteration++;
			no=0;
			present.clear();
		}
	}
	if(no>0)
	{
		vector < pair < string ,int > > sor;
		for(i=0;i<present.size();i++)
			sor.push_back(make_pair(present[i][0],i));
		sort(sor.begin(),sor.end());
		vector < vector < string > > temp(sor.size());
		for(i=0;i<sor.size();i++) temp[i]=present[sor[i].second];
		for(i=0;i<sor.size();i++)
			present[i]=temp[i];
		for(i=0;i<present.size();i++)
		{
			for(j=0;j<present[i].size()-1;j++)
				*pointers2[iteration] << present[i][j] << " ";
			*pointers2[iteration] << present[i][j] << endl;	
		}
		iteration++;
		no=0;
		present.clear();
	}
	//cout<<"no="<<no<<endl;
	for(i=0;i<m-1;i++)
	{
		(*pointers1[i]).close();
		(*pointers2[i]).close();
	}
	getnexts(oppointer);
	closeh(infile1,infile2,oppointer);
}


int check(string a,string b)
{
	ifstream infile1(a);
	ifstream infile2(b);
	string line;
	int noa=0;
	int nob=0;
	while(getline(infile1,line)) noa++;
	while(getline(infile2,line)) nob++;
	infile1.close();
	infile2.close();
//	cout<<noa<<" "<<nob<<endl;
	if((noa+nob)/100 > 2*m*m ) return 0;
       return 1;	
}


int main(int argc,char * argv[])
{
	string inpfile1;
	string inpfile2;
	inpfile1=argv[1];
	inpfile2=argv[2];
	vector<string> r;
	split(argv[1],'/',r);
	string out_file = r.back();

	out_file += "_";
	vector<string> s;
	split(argv[2],'/',s);
	out_file += s.back();

	out_file += "_join";

	string opfile;
	opfile=out_file;
	m=atoi(argv[4]);
	string index=argv[3];
	if(!check(inpfile1,inpfile2))cout<<"not sufficient memory"<<endl;
	if(index=="sort")
		opens(inpfile1,inpfile2,opfile);
	else if(index=="hash")
		openh(inpfile1,inpfile2,opfile);
	return 0;
}

