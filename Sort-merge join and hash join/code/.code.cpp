#include<bits/stdc++.h>
using namespace std;
string rfile, sfile, type;
int b;
vector< vector<string> > h;
vector< vector<string> > outbuff;
int rsize[100000];
int ssize[100000];
map< string, vector<string> > h2;

vector<int> sort_order;
string order;
vector<int> block_line(100000, 0);
vector<int> curr_line(100000, 0);
int line_size = 0;
priority_queue<pair<vector<string>,int>,vector<pair<vector<string>,int> >,greater<pair<vector<string>,int> > > pq;
priority_queue<pair<vector<string>,int>,vector<pair<vector<string>,int> > > pq1;


vector<string> strSplit(string str, char delim)
{
        string token;
        vector<string> tokens;
        int i;
        for(i=0; i<str.size(); i++)
        {
                if(str[i] != delim)
                {
                        token += str[i];
                }
                else
                {
                        tokens.push_back(token);
                        token.clear();
                }
        }
        tokens.push_back(token);
        return tokens;
}

int hfunc(string s)
{
        int sum = 0, i;
        for(i=0; i<s.size(); i++)
        {
                sum += s[i];
        }
        return sum%((b-1)/2);
}

void ropen(string fname)
{
        ifstream file(fname);
        string line;
        vector<string> attr;
        int i, j;
        while(getline(file, line))
        {
                attr = strSplit(line, ' ');
                int bno = hfunc(attr[1]);
                h[bno].push_back(line);
                if(h[bno].size() == 100)
                {
                        ofstream buff("r"+to_string(bno), ofstream::app);
                        for(i=0; i<h[bno].size(); i++)
                        {
                        	rsize[bno]++;
                            buff << h[bno][i] << endl;
                        }
                        buff.close();

                        vector<string> tmp;
                        h[bno] = tmp;
                }
        }
        for(i=0; i<h.size(); i++)
        {
        	if(h[i].size())
        	{
				ofstream buff1("r"+to_string(i), ofstream::app);
				for(j=0; j<h[i].size(); j++)
				{
					rsize[i]++;
					buff1 << h[i][j] << endl;
				}
				buff1.close();
				vector<string> tmp1;
				h[i] = tmp1;
			}
        }
        file.close();
}

void sopen(string fname)
{
        ifstream file(fname);
        string line;
        vector<string> attr;
        int i, j;
        while(getline(file, line))
        {
                attr = strSplit(line, ' ');
                int bno = hfunc(attr[0]);
                h[bno].push_back(line);
                if(h[bno].size() == 100)
                {
                        ofstream buff("s"+to_string(bno), ofstream::app);
                        for(i=0; i<h[bno].size(); i++)
                        {
                        	ssize[bno]++;
                            buff << h[bno][i] << endl;
                        }
                        buff.close();
                        vector<string> tmp;
                        h[bno] = tmp;
                }
        }
        for(i=0; i<h.size(); i++)
        {
        	if(h[i].size())
        	{
				ofstream buff1("s"+to_string(i), ofstream::app);
				for(j=0; j<h[i].size(); j++)
				{
					ssize[i]++;
					buff1 << h[i][j] << endl;
				}
				buff1.close();
				vector<string> tmp1;
				h[i] = tmp1;
			}
        }
        file.close();
}

void join(int iter)
{
	vector<string> outbuff;
	vector<string> attr;
	if(rsize[iter] <= ssize[iter])
	{
		ifstream r1("r"+to_string(iter));
		string line;
		while(getline(r1, line))
		{
			attr = strSplit(line, ' ');
			h2[attr[1]].push_back(line);
		}
		r1.close();
		ifstream s1("s"+to_string(iter));
		while(getline(s1, line))
		{
			attr = strSplit(line, ' ');
			vector<string> list = h2[attr[0]];
			line += attr[1];
			outbuff.push_back(line);
		}
	}
	else
	{
		ifstream s2("s"+to_string(iter));
		string line;
		while(getline(s2, line))
		{
			vector<string> attr = strSplit(line, ' ');
			h2[attr[0]].push_back(line);
		}
		s2.close();
		ifstream r2("r"+to_string(iter));
		while(getline(r2, line))
		{
			attr = strSplit(line, ' ');
			vector<string> list = h2[attr[1]];
			line += attr[0];
			outbuff.push_back(line);
		}
	}
}

string getFileName(int num)
{
                stringstream ss;
                ss << num;
                string block_name = "file" + ss.str() + ".txt";
                //ss.close();
                return block_name;
}

void pushLine(int blocknum, int num)
{
        int i;
        if(block_line[blocknum] < num)
        {
                cout << "return" << endl;
                return;
        }
        string line;
        fstream file(getFileName(blocknum).c_str());
        file.seekg((num-1)*(line_size+1));
        getline(file, line);
        file.close();
        vector<string> tmp = strSplit(line, ' ');
        if(order == "asc")
        {
                pq.push(make_pair(tmp, blocknum));
        }
        else if(order == "desc")
        {
                pq1.push(make_pair(tmp, blocknum));
        }
}

void mergeBlocks_asc(int num)
{
        vector<string> tmp;
        string line;
        int i;
        for(i=1;i<=num;i++)
        {
                curr_line[i]++;
                pushLine(i, curr_line[i]);
        }
        cout << "pq created" << endl;
        ofstream output("output.txt");
        while(!pq.empty())
        {
                pair<vector<string>, int>p = pq.top();
                pq.pop();
                tmp = p.first;
                for(i=0; i<tmp.size(); i++)
                {
                        output << tmp[i];
                        if(i != tmp.size()-1)
                                output << " ";
                }output << endl;
                curr_line[p.second]++;
          //      cout << p.second << endl;
                pushLine(p.second, curr_line[p.second]);
        }
        cout << "done" << endl;
}

bool compare(vector<string> a, vector<string> b)
{
        for(int i=0; i<sort_order.size(); i++)
        {
                if(order == "asc")
                {
                        if(a[sort_order[i]] < b[sort_order[i]])
                                return true;
                        else if(a[sort_order[i]] > b[sort_order[i]])
                                return false;
                }
                else if(order == "desc")
                {
                        if(a[sort_order[i]] < b[sort_order[i]])
                                return false;
                        else if(a[sort_order[i]] > b[sort_order[i]])
                                return true;
                }
        }
        return false;
}

void sortBlock(string name)
{
        ifstream b(name.c_str());
        string line;
        int i, count = 0;
        vector<vector<string> > bvec;
        while(getline(b, line))
        {
                vector<string> tmp = strSplit(line, ' ');
                bvec.push_back(tmp);
        }      
        b.close();  
/*        for(i=0; i<bvec.size(); i++)
        {
                for(int j=0; j<bvec[i].size(); j++)
                {
                        cout << bvec[i][j] << " ";
                }cout << endl;
        }cout << endl;*/
        sort(bvec.begin(), bvec.end(), compare);
/*        for(i=0; i<bvec.size(); i++)
        {
                for(int j=0; j<bvec[i].size(); j++)
                {
                        cout << bvec[i][j] << " ";
                }cout << endl;
        }*/

        ofstream b1(name.c_str());
        for(i=0; i<bvec.size(); i++)
        {
                for(int j=0; j<bvec[i].size(); j++)
                {
                        b1 << bvec[i][j];
                        if(j != (bvec[i].size()-1))
                        {
                                b1 << " ";
                        }
                }
                b1 << endl;
        }
        b1.close();
}
	
int main(int argc, char *argv[])
{
    string rfile = argv[1];
    string sfile = argv[2];
    string type = argv[3];
    b = stoi(argv[4]);
    int i, j, k;

    if(type == "hash")
    {
	    int i; 
	    for(i=0; i<b; i++)
	    {
	            vector<string> tmp;
	            h.push_back(tmp);
	    }
	    ropen(rfile);
	    sopen(sfile);
	    for(i=0; i<h.size(); i++)
	    {
	    	ifstream r("r"+to_string(i));
	    	ifstream s("s"+to_string(i));
	    	if(r && s)
	    	{
	    		r.close();
	    		s.close();
	    		join(i);
	    	}
	    }
	}
    return 0;
}
